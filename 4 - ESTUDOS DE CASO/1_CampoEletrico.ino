// Computing Electric field of a double dipole by solving Poisson's Equation

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
  Serial.print("Metodos Numericos Aplicados a Engenharia - Grupo 2\n");
  Serial.print("Aplicacao: Embarcar algortimo de resolucao de EDP\n");
  Serial.print("Estudo de Caso: Utilizacao da Equacao de Poisson para descrever um Campo Eletrico Bidimensional\n");
  
  Serial.print("\n");
  Serial.print("Discretizacao do Campo. \n");
  Serial.print("Entre com a quantidade de pontos na direção 'X': ");
  int Nx;
  while(1){ //leitura do valor de a
    if (Serial.available() > 0){
    // Lê toda string recebida
    Nx = leStringSerial().toInt();
    break;
    }
  }
  Serial.print(Nx);
  Serial.println("\n");
  
  Serial.print("Entre com a quantidade de pontos na direção 'Y': ");
  int Ny;
  while(1){ //leitura do valor de a
    if (Serial.available() > 0){
    // Lê toda string recebida
    Ny = leStringSerial().toInt();
    break;
    }
  }
  Serial.print(Ny);
  Serial.println("\n");

  Serial.print("Entre com a quantidade de interacoes (precisao): ");
  int Ni;
  while(1){ //leitura do valor de a
    if (Serial.available() > 0){
    // Lê toda string recebida
    Ni = leStringSerial().toInt();
    break;
    }
  }
  Serial.print(Ni);
  Serial.println("\n");

  float mpx = ceil(Nx/1.9999); //% Mid-point of x
  float mpy = ceil(Ny/1.9999); //% Mid point of y

  float V[Ny][Nx];   //% Potential (Voltage) matrix
  int i = 0, j = 0;
  for(j = 0; j<Nx; j++){
    for(i = 0; i<Ny; i++){
      V[j][i] = 0;
    }
  }

  Serial.print("Condicoes de Contorno.\n");
  
  Serial.print("Potencial Superior: ");
  float T;
  while(1){ //leitura do valor de a
    if (Serial.available() > 0){
    // Lê toda string recebida
    T = leStringSerial().toFloat();
    break;
    }
  }
  Serial.print(T);
  Serial.print("V");
  Serial.println("\n");

  Serial.print("Potencial Inferior: ");
  float B;
  while(1){ //leitura do valor de a
    if (Serial.available() > 0){
    // Lê toda string recebida
    B = leStringSerial().toFloat();
    break;
    }
  }
  Serial.print(B);
  Serial.print("V");
  Serial.println("\n");

  Serial.print("Potencial Esquerdo: ");
  float L;
  while(1){ //leitura do valor de a
    if (Serial.available() > 0){
    // Lê toda string recebida
    L = leStringSerial().toFloat();
    break;
    }
  }
  Serial.print(L);
  Serial.print("V");
  Serial.println("\n");

  Serial.print("Potencial Direito: ");
  float R;
  while(1){ //leitura do valor de a
    if (Serial.available() > 0){
    // Lê toda string recebida
    R = leStringSerial().toFloat();
    break;
    }
  }
  Serial.print(R);
  Serial.print("V");
  Serial.println("\n");
  
  for(j = 0; j<Nx; j++){
    for(i = 0; i<Ny; i++){
      V[j][0] = L;
      V[j][Nx-1] = R;
      V[0][i] = B;
      V[Ny-1][i] = T;
    }
  }

  V[0][0] = 0.5*(V[0][1] + V[1][0]);
  V[0][Nx-1] = 0.5*(V[0][Nx-2] + V[1][Nx-1]);
  V[Ny-1][0] = 0.5*(V[Ny-2][0] + V[Ny-1][1]);
  V[Ny-1][Nx-1] = 0.5*(V[Ny-2][Nx-1] + V[Ny-1][Nx-2]);

  Serial.print("Matriz com as condicoes de contorno:\n\n");
  
  for(j = 0; j<Nx; j++){
    for(i = 0; i<Ny; i++){
      Serial.print(" ");
      Serial.print(V[j][i], 0);
      Serial.print(" ");
    }
    Serial.print("\n");
  }

  Serial.print("\n");
  
  Serial.print("Entre com a permissividade absoluta do meio de interesse (ԑ): ");
  float eabs;
  while(1){ //leitura do valor de a
    if (Serial.available() > 0){
    // Lê toda string recebida
    eabs = leStringSerial().toFloat();
    break;
    }
  }
  Serial.print(eabs,2);
  Serial.print("F/m");
  Serial.println("\n");
  
  float eps_0 = eabs*(0.000000000001); //% Absolute permittivity (of free space)
  float eps_r = 1;              //% Relative permittivity of the medium
  float eps = eps_0*eps_r;
  float charge_order = 0.000000001;   //% milli, micro, nano etc..

  int n = 4; //% How many charges?
  
  float Q[n];
  Q[0] = 2*charge_order;    //What are the charges?
  Q[1] = -2*charge_order;
  Q[2] = -2*charge_order;
  Q[3] = 2*charge_order;
  
  int X[] = {5+(mpx-1),5+(mpx-1),-5+(mpx-1),-5+(mpx-1)}; //% Where are the charges located?
  int Y[] = {5+(mpy-1),-5+(mpy-1),5+(mpy-1),-5+(mpy-1)};
  
  float rho[Ny][Nx];
  for(j = 0; j<Nx; j++){
    for(i = 0; i<Ny; i++){
      rho[j][i] = 0;
    }
  }

  for(i=0; i<n; i++){
    rho[X[i]][Y[i]] = Q[i]/eps;
  }
  
  int c=0, a=0;
  
  for(c=0; c<n; c++){
    for(a=0; a<Ni; a++){
      for(j = 1; j<(Ny-1); j++){
        for(i = 1; i<(Nx-1); i++){
          V[j][i] = 0.25*(V[j][i+1] + V[j][i-1] + V[j+1][i] + V[j-1][i] + rho[j][i]);
        }
      }
    }
  }

  Serial.print("Potencial Resultante do Campo Eletrico.\n\n");
  
  for(j = 0; j<Nx; j++){
    for(i = 0; i<Ny; i++){
      Serial.print(" ");
      Serial.print(V[j][i], 1);
      Serial.print(" ");
    }
    Serial.print("\n");
  }

  Serial.println("\n");
}
