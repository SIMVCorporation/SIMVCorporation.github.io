#include <WiFi.h> // Biblioteca do ESP32
#include <PubSubClient.h> // Biblioteca do MQTT

// Variáveis
const char* ssid = "VIVOFIBRA-25F2"; // Usuário do WiFi
const char* password = "mTZuCPVDtb"; // Senha do WiFI
const char* mqttServer = "mqtt.dioty.co"; // Endereço do servidor
const int mqttPort = 1883; // Porta do servidor
const char* mqttUser = "simvcorporation@gmail.com"; // Usuário (se houver)
const char* mqttPassword = "dad74363"; // Senha (se houver)

WiFiClient espClient; // Definição do cliente (WiFi)
PubSubClient client(espClient); // Definição do cliente (MQTT -> ESP)

int i;
int LED_BUILTIN = 2;
int contador = 1; // Contador
char mensagem[30]; // Mensagem

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password); // Conectar ao WiFi
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("Iniciando conexao com a rede WiFi.."); // Mensagem no Console
  }
  Serial.println("Conectado na rede WiFi!"); // Mensagem no console
}

void loop(){
  // Conexão com MQTT
  reconectabroker(); // Função de conectar
  sprintf(mensagem, "MQTT ESP32 - Mensagem n. %d", contador); //Mostrar mensagem
  
  Serial.print("Mensagem enviada: "); // Mensagem no Console
  Serial.println(mensagem); // Mensagem

  //Enviar mensagem para o broker
  client.publish("/simvcorporation@gmail.com/testes/mqtt", mensagem);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Mensagem enviada com sucesso...");
  //Adciona o contador
  contador++;

  //Aguarda 3 segundos para enviar mensagem
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(2000);
}

void reconectabroker(){ //Conexao ao broker MQTT
  client.setServer(mqttServer, mqttPort);
  while (!client.connected()){
    Serial.println("Conectando ao broker MQTT...");
    if (client.connect("SENAISPTCC/40/SIMV/Vendas", mqttUser, mqttPassword )){ // Conexão
      Serial.println("Conectado ao broker!");
    }
    else{
      Serial.print("Falha na conexao ao broker - Estado: ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}
