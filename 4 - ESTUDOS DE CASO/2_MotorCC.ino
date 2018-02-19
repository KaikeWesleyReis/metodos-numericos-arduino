
//DEFININDO VARIAVEIS GLOBAIS

// Parametros:
float ib = 2.83, La = 3.241, Ra = 1.23, Va = 48, Kb = 0.165, Kt = 0.149, J = 2.32, B = 0.005995;

// Condicoes iniciais
float ia0 = 0, w0 = 0, Tm0 = 0, Eg0 = 0;

void setup() {
  // Inicializando a serial
  Serial.begin(9600);
}


float eEg(float Kb, float w, float ib){  //Forca contra eletromotriz
  return (Kb*w*ib);  //eEg = @(Kb, w, ib) Kb*w*ib;
}

float eTm(float Kt, float ia){  //Torque do motor
  return (Kt*ia);  //eTm = @(Kt, ia) Kt*ia;
}

float dia(float ia, float Va, float Ra, float Eg, float La){  //EDO da corrente (dia(t)/dt)
  return ((Va - (Ra*ia) - Eg)/La);  //dia = @(ia, Va, Ra, Eg, La) (Va - (Ra*ia) - Eg)/La;
}

float dw(float w, float Tm, float B, float J){  //EDO da velocidade (dw(t)/dt)
  return ((Tm - (B*w))/J);  //dw = @(w, Tm, B, J) (Tm - (B*w))/J;
}

String leStringSerial(){
  String conteudo = "";
  char caractere;
  
  // Enquanto receber algo pela serial
  while(Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
    
  return conteudo;
}

void loop() {
    
    Serial.print("Entre com os valores de tempo 't0' e 'tf' e o passo 'h'.\n");
    float t0, tf, h;

    Serial.print("Tempo inicial 't0' = ");
    
    while(1){ //leitura do valor de t0
      if (Serial.available() > 0){
      // Lê toda string recebida
      t0 = leStringSerial().toFloat();
      break;
      }
    }

    Serial.print(t0, 6);
    Serial.println("s");

    Serial.print("Tempo final 'tf' = ");

    while(1){ //leitura do valor de tf
      if (Serial.available() > 0){
      // Lê toda string recebida
      tf = leStringSerial().toFloat();
      break;
      }
    }
    
    Serial.print(tf, 6);
    Serial.println("s");

    Serial.print("Passo 'h' = ");
    
    while(1){  //leitura do valor de h
      if (Serial.available() > 0){
      // Lê toda string recebida
      h = leStringSerial().toFloat();
      break;
      }
    }

    Serial.println(h);

    int N = 1 + fabs(tf - t0)/h;

    Serial.print("\nNumero de pontos 'N' = ");
    Serial.println(N);
    
    float t[N + 1] = {0};
    float w[N + 1] = {0};
    float ia[N + 1] = {0};
    float Tm[N + 1] = {0};
    float Eg[N + 1] = {0};

    t[0] = t0;
    w[0] = w0;
    ia[0] = ia0;
    Tm[0] = Tm0;
    Eg[0] = Eg0;

    Serial.print("\nTecle o numero correspondente ao metodo numerico desejado.\n\n");
    Serial.print("Euller Simples -> 1\n");
    Serial.print("Euller Modificado -> 2\n");
    Serial.print("Runge-Kutta 3ªordem -> 3\n");
    Serial.print("Runge-Kutta 4ªordem -> 4\n");
    
    int key;
    while(1){
      if (Serial.available() > 0){
      // Lê toda string recebida
      key = leStringSerial().toInt();
      break;
      }
    }

    int i = 0;
    if(key == 1){
      for(i = 0; i<N; i++){
        t[i+1] = t[i] + h;
        ia[i+1] = ia[i] + dia(ia[i], Va, Ra, Eg[i+1], La)*h;
        Tm[i+1] = eTm(Kt, ia[i+1]);
        w[i+1] = w[i] + dw(w[i], Tm[i+1], B, J)*h;
        Eg[i+1] = eEg(Kb, w[i], ib);
      }
    }

    if(key == 2){
      float k1;
      for(i = 0; i<N; i++){
        t[i+1] = t[i] + h;
        k1 = ia[i] + dia(ia[i], Va, Ra, Eg[i+1], La)*h;
        ia[i+1] = ia[i] + (dia(ia[i], Va, Ra, Eg[i+1], La) + dia(k1, Va, Ra, Eg[i+1], La))*0.5*h;
        Tm[i+1] = eTm(Kt, ia[i+1]);
        k1 = w[i] + dw(w[i], Tm[i+1], B, J)*h;
        w[i+1] = w[i] + (dw(w[i], Tm[i+1], B, J) + dw(k1, Tm[i+1], B, J))*0.5*h;
        Eg[i+1] = eEg(Kb, w[i], ib);
      }
    }

    if(key == 3){
      float k1, k2, k3;
      for(i = 0; i<N; i++){
        t[i+1] = t[i] + h;
        k1 = dia(ia[i], Va, Ra, Eg[i+1], La);
        k2 = dia(ia[i] + 0.5*k1*h, Va, Ra, Eg[i+1], La);
        k3 = dia(ia[i] - k1*h + 2*k2*h, Va, Ra, Eg[i+1], La);
        ia[i+1] = ia[i] + (k1/6 + ((2*k2)/3) + k3/6)*h;
        Tm[i+1] = eTm(Kt, ia[i+1]);
        k1 = dw(w[i], Tm[i+1], B, J);
        k2 = dw(w[i] + 0.5*k1*h, Tm[i+1], B, J);
        k3 = dw(w[i] - k1*h + 2*k2*h, Tm[i+1], B, J);
        w[i+1] = w[i] + (k1/6 + ((2*k2)/3) + k3/6)*h;
        Eg[i+1] = eEg(Kb, w[i], ib);
      }
    }
    
    if(key == 4){
      float k1, k2, k3, k4;
      for(i = 0; i<N; i++){
        t[i+1] = t[i] + h;
        k1 = dia(ia[i], Va, Ra, Eg[i+1], La);
        k2 = dia(ia[i] + 0.5*k1*h, Va, Ra, Eg[i+1], La);
        k3 = dia(ia[i] + 0.5*k2*h, Va, Ra, Eg[i+1], La);
        k4 = dia(ia[i] + k3*h, Va, Ra, Eg[i+1], La);
        ia[i+1] = ia[i] + (k1 + 2*k2 + 2*k3 + k4)*(h/6);
        Tm[i+1] = eTm(Kt, ia[i+1]);
        k1 = dw(w[i], Tm[i+1], B, J);
        k2 = dw(w[i] + 0.5*k1*h, Tm[i+1], B, J);
        k3 = dw(w[i] + 0.5*k2*h, Tm[i+1], B, J);
        k4 = dw(w[i] + k3*h, Tm[i+1], B, J);
        w[i+1] = w[i] + (k1 + 2*k2 + 2*k3 + k4)*(h/6);
        Eg[i+1] = eEg(Kb, w[i], ib); 
      }
    }
    
    Serial.print("\n|Tempo|\t");
    Serial.print("|Velocidade Angular|\t");
    Serial.print("|Corrente de Armadura|\t");
    Serial.print("|Torque do Motor|\n");
    for (i = 0; i<N; i++){
      if(t[i]<10){
        Serial.print(" ");
        Serial.print(t[i]);
        Serial.print(" s");
        Serial.print("\t");
        Serial.print("  ");
        Serial.print(w[i], 6);
        Serial.print(" rad/s");
        Serial.print("\t\t");
        Serial.print(ia[i]);
        Serial.print(" A");
        Serial.print("\t\t");
        Serial.print("    ");
        Serial.print(Tm[i]);
        Serial.print(" Nm");
        Serial.print("\n");
      }else{
        Serial.print(" ");
        Serial.print(t[i]);
        Serial.print(" s");
        Serial.print("  ");
        Serial.print(w[i], 6);
        Serial.print(" rad/s");
        Serial.print("\t\t");
        Serial.print(ia[i]);
        Serial.print(" A");
        Serial.print("\t\t");
        Serial.print("    ");
        Serial.print(Tm[i]);
        Serial.print(" Nm");
        Serial.print("\n");              
      }
      
    }

    Serial.println("\n");

}
