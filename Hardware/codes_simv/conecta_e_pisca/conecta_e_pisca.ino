#include <WiFi.h> // Biblioteca do ESP32

const char* ssid = "BLOCO B_PISO SUPERIOR_BV"; // Usuário do WiFi
const char* password =  "WiFiSen@i123"; // Senha do WiFI

WiFiClient espClient; // Definição do cliente (WiFi)

int LED_BUILTIN = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password); // Conectar ao WiFi

 while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  

  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500);
    
  }
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  Serial.println("Conectado"); // Mensagem no console
}

void loop() {
  // put your main code here, to run repeatedly:
   // Mensagem no console
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500);
}
