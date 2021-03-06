//BIBLIOTECAS*************************************
#include <WiFi.h> // Biblioteca do ESP32
#include <PubSubClient.h> // Biblioteca do MQTT
#include "DHT.h"
#include <Ultrasonic.h> // Biblioteca Ultrasonic
//************************************************

//CONFIG*DHT11************************************
#define DHTPIN  27// pino que dht11 eh concectado
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);
unsigned int distancia = 0;
//************************************************

//CONFIG*ULTRASONIC*******************************
Ultrasonic ultrasonic(5, 17);
//***********************************************

#define arduino 2

// VARIAVEIS*PARA*CONEXAO***********************************************
const char* ssid = "VIVOFIBRA-25F2"; // Usuário do WiFi
const char* password = "mTZuCPVDtb"; // Senha do WiFI
const char* mqttServer = "postman.cloudmqtt.com"; // Endereço do servidor
const int mqttPort = 10281; // Porta do servidor
const char* mqttUser = "ESP32"; // Usuário (se houver)
const char* mqttPassword = "teste"; // Senha (se houver)
//**********************************************************************

WiFiClient espClient; // Definição do cliente (WiFi)
PubSubClient client(espClient); // Definição do cliente (MQTT -> ESP)

int i;
int v;
int LED_BUILTIN = 2; //config led interno
int contador = 1; // Contador
char mensagem[30]; // Mensagem


void setup() {
  pinMode(arduino, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password); // Conecta ao WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Iniciando conexao com a rede WiFi.."); // Mensagem no Console
  }
  Serial.println("Conectado na rede WiFi!"); // Mensagem no console
}


void loop() {
  for(i=0; i<60; i++){
    verificarDistancia();
    delay(500);
  }
  reconectabroker(); // Conecta ao broker 
  atualiza_temp(); // Atualiza temp e umidade no site
  
  //Serial.println(mensagem); // Mensagem pro serial  
  contador++; //Adciona o contador

  //Aguarda 1 segundos para recomecar
  digitalWrite(LED_BUILTIN, HIGH); //led high quando enviar msg
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW); //desliga led
}
//Conexao ao broker MQTT


void verificarDistancia() {
  //recupera a distância atual lida pelo sensor
  distancia = ultrasonic.distanceRead();
  if(distancia < 30){
    v++;
    sprintf(mensagem, "Venda %d confirmada", v); //salva msg
    client.publish("SIMV/relatorio", mensagem); //Envia variavel mensagem ao broker
    Serial.print("Distancia: ");
    Serial.println(distancia);
    Serial.println(v);
    while(distancia<30){
      distancia = ultrasonic.distanceRead();
      digitalWrite(arduino, HIGH);
      delay(200);
    }
  }
}

void atualiza_temp(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT");
    delay(1000);
  }
  sprintf(mensagem, "Temperatura: %.1f ºC", t); //salva msg
  client.publish("SIMV/relatorio", mensagem); //Envia variavel mensagem ao broker
  sprintf(mensagem, "Umidade: %.0f%%", h); //salva msg
  client.publish("SIMV/relatorio", mensagem); //Envia variavel mensagem ao broker
  
  Serial.print("Mensagem enviada: "); // Mensagem no Console
  Serial.println("Temperatura e umidade atualizados...");
}


void reconectabroker() { 
  client.setServer(mqttServer, mqttPort);
  while (!client.connected()) {
    Serial.println("Conectando ao broker MQTT...");
    if (client.connect("SIMV/relatorio", mqttUser, mqttPassword )) { // Conexão
      Serial.println("Conectado ao broker!");
    }
    else {
      Serial.print("Falha na conexao ao broker - Estado: ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}
