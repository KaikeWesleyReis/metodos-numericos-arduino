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

float func(float x){  //Funcao que calcula a funcao de interesse
  return ((x*x*x) - 4*(x*x));
}

float analitica_1(float x){  //Funcao que calcula as derivadas analiticas de primeira ord
  return (3*(x*x) - 8*x);
}

float analitica_2(float x){  //Funcao que calcula as derivadas analiticas de segunda ord
  return (6*x - 8);
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

    float h;

    Serial.print("Entre com o valor do passo 'h': ");
    
    while(1){ //leitura do valor de reset
      if (Serial.available() > 0){
      // Lê toda string recebida
      h = leStringSerial().toFloat();
      break;
      }
    }
    Serial.println(h);

    float x0 = 0;
    float xf = 20;
    int N = 0;
    float som = x0;

    while(1){
      N = N + 1;
      som = som + h;
      if(som == xf){
        break;
        }
    }

    N = N + 1;
    Serial.print("Numero de pontos = ");
    Serial.println(N);
    float x[N];
    float y[N];
    float y1[N];
    float y2[N];
    float ydf1[N];
    float ydf2[N];
    int i = 0;
    
    som = x0;    

    for(i = 1; i<=N; i++){
      x[i] = som;
      y[i] = func(x[i]);
      y1[i] = analitica_1(x[i]);
      y2[i] = analitica_2(x[i]);
      som = som + h;
    }

    // CALCULANDO POR DIFERENCAS FINITAS DE ORDEM 1

    // Progressiva 3pts
    ydf1[1] = (-3*y[1] + 4*y[2] - y[3])/(x[3] - x[1]);
  
    // Central
    for (i = 2; i<=(N-1); i++){
      ydf1[i] = (y[i+1] - y[i-1])/(x[i+1]-x[i-1]);
    }
  
    // Regressiva 3pts
    ydf1[N] = (3*y[N] - 4*y[N-1] + y[N-2])/(x[N]-x[N-2]);

    // CALCULANDO POR DIFERENCAS FINITAS DE ORDEM 2

    // Primeiro Ponto
    ydf2[1] = (y[3]- 2*y[2]+ y[1])/((x[2]-x[1])*(x[2]-x[1]));
    // Pontos 2 ao N-1
    for (i = 2; i<=(N-1); i++){
        ydf2[i] = (y[i+1]- 2*y[i]+ y[i-1])/((x[i+1]-x[i])*(x[i+1]-x[i]));
    }
    // Ultimo ponto
    ydf2[N] = (y[N]- 2*y[N-1] +y[N-2])/((x[N]-x[N-1])*(x[N]-x[N-1]));
    
    for(i = 1; i<=N; i++){
      Serial.print("\nVariavel idenpendente 'x' = ");
      Serial.println(x[i]);
      Serial.print("Funcao 'y' = ");
      Serial.println(y[i]);
      Serial.print("1ª derivada analitica = ");
      Serial.println(y1[i]);
      Serial.print("1ª derivada diferencas finitas = ");
      Serial.println(ydf1[i]);
      Serial.print("2ª derivada analitica = ");
      Serial.println(y2[i]);
      Serial.print("2ª derivada diferencas finitas = ");
      Serial.println(ydf2[i]);
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
