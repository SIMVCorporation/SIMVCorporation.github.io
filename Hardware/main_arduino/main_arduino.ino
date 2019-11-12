  
#include <Keypad.h> //BIBLIOTECA TECLADO
#include <Ultrasonic.h> //BIBLIOTECA SENSOR ULTRASSONICO


//CONFIG*ULTRASONIC*******************************
Ultrasonic ultrasonic(8, 9); //Parametro do pino trigger e echo, respectivamente
//***********************************************
 
const byte qtdLinhas = 4; //QUANTIDADE DE LINHAS DO TECLADO
const byte qtdColunas = 4; //QUANTIDADE DE COLUNAS DO TECLADO
int distancia;
 
//CONSTRUÇÃO DA MATRIZ DE CARACTERES
char matriz_teclas[qtdLinhas][qtdColunas] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
 
 
byte PinosqtdLinhas[qtdLinhas] = {3, 4, 5, 6}; //PINOS UTILIZADOS PELAS LINHAS
byte PinosqtdColunas[qtdColunas] = {8, 9, 10,11}; //PINOS UTILIZADOS PELAS COLUNAS
  
//INICIALIZAÇÃO DO TECLADO
Keypad meuteclado = Keypad( makeKeymap(matriz_teclas), PinosqtdLinhas, PinosqtdColunas, qtdLinhas, qtdColunas);
 
void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600); //INICIALIZA A SERIAL
  Serial.println("Aperte uma tecla..."); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.println(); //QUEBRA UMA LINHA NO MONITOR SERIAL
}
  
void loop(){
  char tecla_pressionada = meuteclado.getKey(); //VERIFICA SE ALGUMA DAS TECLAS FOI PRESSIONADA
  if (tecla_pressionada){ //SE ALGUMA TECLA FOR PRESSIONADA, FAZ
    Serial.print("Tecla pressionada : "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.println(tecla_pressionada); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA
  }
  distancia = ultrasonic.distanceRead();
  if (tecla_pressionada == '1'){
    digitalWrite(LED_BUILTIN, HIGH);
      if(distancia < 30){
        digitalWrite(LED_BUILTIN, LOW); 
      }
  } else if (tecla_pressionada == '2'){
    digitalWrite(LED_BUILTIN, HIGH);
      if(distancia < 30){
        digitalWrite(LED_BUILTIN, LOW);
      }
  }
}
