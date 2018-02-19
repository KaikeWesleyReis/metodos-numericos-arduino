// Traduzindo codigos de Matlab para o Arduino

//Exemplo Derivacao

/*
Exemplo Proposto:

Observar o comportamento das derivadas (primeira e segunda)da funcao f = x.^3 - 12*x
     Intervalo: [0,20]
     Comparar resultado analitico com o resultado por diferencas finitas
*/

void setup() {
  Serial.begin(9600);
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

    float L = 10;     // Comprimento [cm]
    float k = 0.163 ;   // Condutividade termica do ferro [cal/(s*cm*C)]
    float C = 0.110; // Calor especifico do ferro [cal/(g*C)]
    float rho =  7.87;  // massa especifica ferro [g/cm3]
    float K = (k/C/rho);

    float Tt0 = 25; // C temperatura da barra para t=0;
    
    // Condicao de contorno
    float x0 = 0; 
    float xf = L;
    float Ti = 100;
    float Tf = 100;        
    float tf = 5;
    float t0 = 0;

    int i = 0;

    float dx;

    Serial.print("Entre com o valor do passo 'dx': ");
    
    while(1){ //leitura do valor de reset
      if (Serial.available() > 0){
      // Lê toda string recebida
      dx = leStringSerial().toFloat();
      break;
      }
    }
    Serial.println(dx);

    float dt;

    Serial.print("Entre com o valor do passo 'dt': ");
    
    while(1){ //leitura do valor de reset
      if (Serial.available() > 0){
      // Lê toda string recebida
      dt = leStringSerial().toFloat();
      break;
      }
    }
    Serial.println(dt);

    int Nx = 0;
    float somx = x0;

    while(1){
      Nx = Nx + 1;
      somx = somx + dx;
      if(somx == xf){
        break;
        }
    }

    Nx = Nx + 1;
    Serial.print("Numero de pontos em x = ");
    Serial.println(Nx);

    float x[Nx];
    somx = x0;
    for(i = 1; i<=Nx; i++){
      x[i] = somx;
      somx = somx + dx;
      Serial.println(x[i]);
    }

    int Nt = 0;
    float somt = t0;

    while(1){
      Nt = Nt + 1;
      somt = somt + dt;
      if(somt == tf){
        break;
        }
    }

    Nt = Nt + 1;
    Serial.print("Numero de pontos no t = ");
    Serial.println(Nt);
    
    float t[Nt];
    somt = t0;
    for(i = 1; i<=Nt; i++){
      t[i] = somt;
      somt = somt + dt;
    }
    
    float T[Nt][Nx];

    for(i = 1; i<=Nt; i++){
      T[i][1] = Ti;
      T[i][Nx] = Tf;
    }

    for(i = 2; i<=(Nx-1); i++){
      T[1][i] = Tt0;
    }

    int j = 0;
    for(j = 1; j<=(Nt-1); j++){
      for(i = 2; i<=(Nx-1); i++){
          T[j+1][i] = T[j][i] + K*dt*(T[j][i+1] - 2*T[j][i] + T[j][i-1])/(dx*dx); // Metodo de Euller explicito para a resolucao da EDP parabolica
      }  
    }

    for(j = 1; j<=(Nt); j++){
      Serial.print("\nTempo = ");
      Serial.println(j);
      for(i = 1; i<=(Nx); i++){
          Serial.print("\nPosicao = ");
          Serial.print(x[i]);
          Serial.print(" Temperatura = ");
          Serial.println(T[j][i]);
      }  
    }
        
    float reset;

    Serial.println("\nEnvie qualquer caracter para reiniciar o codigo!!!\n");
    
    while(1){ //leitura do valor de reset
      if (Serial.available() > 0){
      // Lê toda string recebida
      reset = leStringSerial().toFloat();
      break;
      }
    }
    
}
