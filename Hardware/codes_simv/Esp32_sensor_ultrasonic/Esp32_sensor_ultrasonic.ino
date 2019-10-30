//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>

#define INTERVALO_LEITURA 500 //(ms)

//conexão dos pinos para o sensor ultrasonico
#define PIN_TRIGGER   4
#define PIN_ECHO      5

//variável responsável
unsigned int distancia = 0;


//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(PIN_TRIGGER, PIN_ECHO);

void setup()  {
  Serial.begin(9600);

  Serial.println("Setup...");
}


void loop() {
  verificarDistancia();
  delay(INTERVALO_LEITURA);
}

/*
  VERIFICA A DISTANCIA ATUAL QUE O SENSOR ULTRASONIC ESTA LENDO
  E EM SEGUIDA, IMPRIME O VALOR NO DISPLAY, E ACENDE O LED CORRESPONDENTE
*/
void verificarDistancia() {

  //recupera a distância atual lida pelo sensor
  distancia = getDistance();

  Serial.print("Distancia: ");
  Serial.println(distancia);
}

void vendas() {
  int x, y, prod1, prod2;
  if(distancia < 30 && distancia > 15){
    x = 2;
    prod1 ++;
  }
  else if ( distancia <= 15 && distancia >= 3){
    y = 2;
    prod2 ++;
  }
}

// FAZ A LEITURA DA DISTANCIA ATUAL CALCULADA PELO SENSOR
int getDistance() {
  //faz a leitura das informacoes do sensor (em cm)
  int distanciaCM;
  long microsec = ultrasonic.timing();
  distanciaCM = ultrasonic.convert(microsec, Ultrasonic::CM);

  return distanciaCM;
}
