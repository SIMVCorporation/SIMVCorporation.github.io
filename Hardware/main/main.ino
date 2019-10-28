#include <WiFi.h> // Biblioteca do ESP32
#include <PubSubClient.h> // Biblioteca do MQTT
#include "DHT.h"

#define DHTPIN  27// pino que dht11 eh concectado
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);

// Variáveis
const char* ssid = "VIVOFIBRA-25F2"; // Usuário do WiFi
const char* password = "mTZuCPVDtb"; // Senha do WiFI
const char* mqttServer = "postman.cloudmqtt.com"; // Endereço do servidor
const int mqttPort = 10281; // Porta do servidor
const char* mqttUser = "ESP32"; // Usuário (se houver)
const char* mqttPassword = "teste"; // Senha (se houver)

WiFiClient espClient; // Definição do cliente (WiFi)
PubSubClient client(espClient); // Definição do cliente (MQTT -> ESP)

int i;
int LED_BUILTIN = 2;
int contador = 1; // Contador
char mensagem[30]; // Mensagem

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password); // Conectar ao WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Iniciando conexao com a rede WiFi.."); // Mensagem no Console
  }
  Serial.println("Conectado na rede WiFi!"); // Mensagem no console
}

void loop() {
  // Conexão com MQTT
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  reconectabroker(); // Função de conectar

  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT");
    delay(1000);
  }
  sprintf(mensagem, "Temperatura %.2f ºC", t); //Mostrar mensagem

  Serial.print("Mensagem enviada: "); // Mensagem no Console
  Serial.println(mensagem); // Mensagem

  //Enviar mensagem para o broker
  client.publish("SIMV/relatorio", mensagem);
  digitalWrite(LED_BUILTIN, HIGH); //led high quando enviar msg
  Serial.println("Mensagem enviada com sucesso...");
  
  contador++; //Adciona o contador

  //Aguarda 30 segundos para enviar mensagem
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW); //desliga led
  delay(29000);
}
//Conexao ao broker MQTT
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
