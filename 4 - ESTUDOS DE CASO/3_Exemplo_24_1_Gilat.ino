// GRUPO 2 - Métodos de integração númerica (ENGD04)

void setup() {
  Serial.begin(9600);
}

float func(float y){  //Funcao que calcula a funcao de interesse
  return (0.132 + 1.56*0.0001*y + 2.64*(0.0001/1000)*(y*y));
}

float mret(float a, float b, int N){  //Funcao que retorna o metodo dos retangulos
  
  int i;
  float h = fabs(a-b)/(N-1);
  Serial.print("O passo 'h' = ");
  Serial.println(h);
  float y[N];
  float r = a;
  for(i = 0; i<N; i++){
    y[i] = r;
    r = r + h; 
  }
  float som = 0;
  for(i = 0; i<N-1; i++){
    som += func(y[i]);
  }
  
  return h*som;
}

float mtra(float a, float b, int N){  //Funcao que retorna o metodo dos trapezios
  
  int i;
  float h = fabs(a-b)/(N-1);
  Serial.print("O passo 'h' = ");
  Serial.println(h);
  float y[N];
  float r = a;
  for(i = 0; i<N; i++){
    y[i] = r;
    r = r + h;
  }
  float som = 0;
  for(i = 0; i<N-1; i++){
    som += func(y[i]) + func(y[i+1]);
  }
  
  return (h*som)/2;
}

float ms13(float a, float b, int N){  //Funcao que retorna o metodo dos Simpson 1/3
  
  int i;
  float h = fabs(a-b)/(N-1);
  Serial.print("O passo 'h' = ");
  Serial.println(h);
  float y[N];
  float r = a;
  for(i = 0; i<N; i++){
    y[i] = r;
    r = r + h;
  }
  float spar = 0, simp = 0;
  for(i = 1; i<N-1; i++){
    if(i%2 != 0){
      spar += func(y[i]);
    }else{
      simp += func(y[i]);
    }
  }
  return ((h/3)*(func(y[0]) + 4*spar + 2*simp + func(y[N-1])));
}

float ms38(float a, float b, int N){  //Funcao que retorna o metodo dos Simpson 3/8
  
  int i;
  float h = fabs(a-b)/(N-1);
  Serial.print("O passo 'h' = ");
  Serial.println(h);
  float y[N];
  float r = a;
  for(i = 1; i<=N; i++){
    y[i] = r;
    r = r + h;
  }
  float si = 0, sj = 0;
  for(i = 2; i<N-1; i++){
    if((i+1)%3 == 0){
      si += func(y[i]) + func(y[i+1]);
    }else{
      if((i-1)%3 == 0){
        sj += func(y[i]);
      }
    }
  }
  return (((3*h)/8)*(func(y[1]) + 3*si + 2*sj + func(y[N])));
}


float msc(float a, float b, int N) { //Funcao que retorna uma combinacao entre os metodos Simpson 1/3 e 3/8

  int i;
  float h = fabs(a-b)/(N-1);
  Serial.print("O passo 'h' = ");
  Serial.println(h);
  float y[N];
  float r = a;
  for(i = 1; i<=N; i++){
    y[i] = r;
    r = r + h;
  }
  
  float spar = 0, simp =0;
  for(i=5; i<N; i++){
     if(i%2!=0){
        spar += func(y[i]);
     }
     if(i%2==0){
        simp += func(y[i]);
     }
  }
  return (((3*h)/8)*(func(y[1])+ 3*func(y[2])+ 3*func(y[3])+ func(y[4])) + (h/3)*(func(y[4])+ func(y[N])+ 4*spar+ 2*simp));

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
       
    Serial.println("\nResolucao do exemplo 24.1 do Chapra.\n");
    Serial.print("INTEGRACAO PARA DETERMINAR A QUANTIDADE DE CALOR\n\n");
    Serial.print("Funcao de interesse: c(T) = 0,132 + 1,56.10^-4 + 2,64.10^-7*T^2\n\n");
    
    Serial.print("Entre com os valores de temperatura 'T0' e 'Tf' e a quantidade 'N' de pontos.\n");
    float a, b;
    int N;

    Serial.print("Temperatura inicial 'T0' = ");
    
    while(1){ //leitura do valor de a
      if (Serial.available() > 0){
      // Lê toda string recebida
      a = leStringSerial().toFloat();
      break;
      }
    }
    
    Serial.print(a, 6);
    Serial.println("°C");

    Serial.print("Temperatura final 'Tf' = ");

    while(1){ //leitura do valor de b
      if (Serial.available() > 0){
      // Lê toda string recebida
      b = leStringSerial().toFloat();
      break;
      }
    }
    
    Serial.print(b, 6);
    Serial.println("°C");

    Serial.print("Quantidade de pontos 'N' = ");
    
    while(1){  //leitura do valor de N
      if (Serial.available() > 0){
      // Lê toda string recebida
      N = leStringSerial().toInt();
      break;
      }
    }

    Serial.println(N);

    Serial.print("Entre com o valor da massa do material, m = ");
    float m; 
    while(1){
     if (Serial.available() > 0){
     // Lê toda string recebida
     m = leStringSerial().toFloat();
     break;
     }
    }

    Serial.print(m, 6);
    Serial.println(" g");
  
    //Mostrar apenas os metodos que podem ser usados a partir do numero de pontos escolhido
    
    Serial.print("\nTecle o numero correspondente ao metodo numerico desejado.\n\n");
    Serial.print("Metodo dos retangulos -> 1\n");
    Serial.print("Metodo dos trapezios -> 2\n");

    if(N%2 != 0){
       Serial.print("Metodo de Simpson 1/3 -> 3\n");
    }
    if((N-1)%3 == 0 && N>2){
       Serial.print("Metodo de Simpson 3/8 -> 4\n");
    }
    if(N%2 == 0 && N>2){
       Serial.print("Metodos de Simpson 1/3 e 3/8 combinados -> 5\n");
    }
    if(N%2 == 0){
      Serial.print("*O metodo de Simpson 1/3 so pode ser usado quando o numero 'N' de pontos for ímpar!\n");
    }
    if((N-1)%3 != 0){
      Serial.print("*O metodo de Simpson 3/8 so pode ser usado quando o numero 'N-1' de subintervalos for multiplo de 3!\n"); 
    }
    
    int key;
    while(1){
      if (Serial.available() > 0){
      // Lê toda string recebida
      key = leStringSerial().toInt();
      break;
      }
    }

      int k = key;      
    for (int c = 0; c < 4; c++){
      key = k%10;
      k = k/10;
        if(key >= 1 && key <= 5){
          //INICIO

          Serial.print("\nRESULTADOS:\n");
    
    
          float resultado;
          int flag = 0;
    
          if(key == 1){
            Serial.print("Metodo dos Retangulos\n");
            resultado = mret(a, b, N);
          }
          if(key == 2){
            Serial.print("Metodo dos Trapezios\n");
            resultado = mtra(a, b, N);
          }
          if(key == 3){
            
            if(N%2 == 0){
              flag = 1;
              }else{
                Serial.print("Metodo de Simpson 1/3\n");
                resultado = ms13(a, b, N);
                flag = 0;
                }
          }
          if(key == 4){
            
            if((N-1)%3 != 0){
              flag = 1;
              }else{
                Serial.print("Metodo de Simpson 3/8\n");
                resultado = ms38(a, b, N);
                flag = 0;
                }
          }
          
        if(key == 5){

            if((N-1)%2 == 0 || N<6){
              flag = 1;
              }else{
                Serial.print("Metodos de Simpson 1/3 e 3/8 combinados\n");
                resultado = msc(a, b, N);
                flag = 0;
                }
          }

    

          if(flag == 0){
            Serial.print("Erro: ");
            Serial.print((fabs(resultado - 42.732)*100)/42.732, 6);
            Serial.println("%");
            Serial.print("c(T) = ");
            Serial.print(resultado, 5);
            Serial.println(" cal/(g.C°)");
            Serial.print("A quantidade de calor 'Q': ");
            Serial.print(m*resultado);
            Serial.println(" cal");
         }
         else{
          Serial.println("Opcao invalida!");
         }
         
        }
          //FIM
      }

    Serial.println("\nEnvie qualquer caracter para continuar!!\n");
      
    while(1){
      if (Serial.available() > 0){
      // Lê toda string recebida
      key = leStringSerial().toInt();
      break;
      }
   }
    
}
