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

void setup()
{
  Serial.begin(9600);
   
  Serial.println("Setup...");
}


void loop()
{
  verificarDistancia();
  delay(INTERVALO_LEITURA);
}

/*
  VERIFICA A DISTANCIA ATUAL QUE O SENSOR ULTRASONIC ESTA LENDO
  E EM SEGUIDA, IMPRIME O VALOR NO DISPLAY, E ACENDE O LED CORRESPONDENTE
*/
void verificarDistancia()
{

    //recupera a distância atual lida pelo sensor
    distancia = getDistance();
  
  Serial.print("Distancia: ");
  Serial.println(distancia);
}
/*
  //caso a distancia lida seja menor ou igual a 5, tomaremos como uma distância de perigo
  //então acenderemos o LED VERMELHO e ligaremos o BUZZER
  if( distancia <= 5 )
  {
    digitalWrite(PIN_RED_LED, HIGH);
    digitalWrite(PIN_BUZZER, HIGH);
  }
  //caso a distancia seja maior que 5 e menor ou igual a 20,
  //tomaremos como uma distância de atenção, e ligaremos o LED AMARELO
  else if(distancia <=20)
  {
    digitalWrite(PIN_YELLOW_LED, HIGH);
  }
  //caso a distancia seja maior que 20 e menor ou igual a 40,
  //tomaremos como uma distância segura, e ligaremos o LED VERDE
  else if(distancia <= 40)
  {
    digitalWrite(PIN_GREEN_LED, HIGH);
  }
  //para distâncias maiores que 40, tomaremos como uma distância sem perigo
  //acenderemos o LED AZUL para indicar
  else
  {
    digitalWrite(PIN_BLUE_LED, HIGH);
  }
}

*/

// FAZ A LEITURA DA DISTANCIA ATUAL CALCULADA PELO SENSOR

int getDistance()
{
    //faz a leitura das informacoes do sensor (em cm)
    int distanciaCM;
    long microsec = ultrasonic.timing();
    distanciaCM = ultrasonic.convert(microsec, Ultrasonic::CM);

    return distanciaCM;
}
