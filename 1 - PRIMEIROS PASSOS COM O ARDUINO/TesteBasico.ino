/*
  Blink
  Liga o LED por um segundo, depois desliga por um segundo, repetidamente.
*/
void setup() {                
  // inicializa o pino digital 13 como uma saída.
  pinMode(13, OUTPUT);     
}

void loop() {
  digitalWrite(13, HIGH);       // liga o LED
  delay(1000);                        // aguarda um segundo
  digitalWrite(13, LOW);        // desliga o LED
  delay(1000);                        // aguarda um segundo
}

