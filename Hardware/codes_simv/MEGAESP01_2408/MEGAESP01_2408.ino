#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
#include <WiFiEsp.h>

//Pinos onde estão os sensores
#define PIN_DS18B20 7 
#define PIN_DHT22 8
#define PIN_LUMINOSITY A0

#define FIRST_PIN 36 //Pino onde está o primeiro relê
#define PINS_COUNT 16 //Quantos pinos a partir do primeiro serão utilizados

//Sensor de Temperatura DS18B20
OneWire oneWire(PIN_DS18B20);
DallasTemperature sensors(&oneWire);
DeviceAddress sensor;

//Sensor de temperatura e umidade DHT22
DHT dht(PIN_DHT22, DHT22);

//SSID e senha da rede wifi para o ESP se conectar
char ssid[] = "SSID";
char pass[] = "12345678";
char ip[] = "192.168.0.154";

//Servidor que receberá as requisições na porta 80 (porta padrão http)
WiFiEspServer server(80);

//Variáveis para armazenar os valores dos sensores
float temperatureDS18B20 = 0;
float temperatureDHT22 = 0;
float humidityDHT22 = 0;
int luminosity = 0;

//Mantém o estado atual dos pinos (HIGH ou LOW)
int pinsStatus[PINS_COUNT];

void setup()
{
    //Serial para o monitor serial
    Serial.begin(115200);

    //Serial onde está o ESP-01 com firmware AT
    Serial1.begin(115200);

    //Inicializa os pinos
    setupPins();

    //Inicializa o sensor DS18B20
    setupDS18B20();

    //Inicializa o sensor DHT22
    dht.begin();

    //Para o sensor de luminosidade apenas precisamos ler o pino analógico
    pinMode(A0, INPUT);

    //Inicializa WiFi e conecta à rede
    setupWiFi();

    //Inicializa o server
    server.begin();
}

void setupPins()
{
    //Coloca os pinos que estão ligados os relês como saída
    for(int i=0; i<PINS_COUNT; i++)
    {
        pinsStatus[i] = LOW;
        int pinNumber = FIRST_PIN + i;
        pinMode(pinNumber, OUTPUT);
        digitalWrite(pinNumber, pinsStatus[i]);
    }
}

void setupWiFi()
{
    //Serial onde está o ESP-01 com o firmware AT já instalado
    WiFi.init(&Serial1);

    Serial.print("Conectando a ");
    Serial.println(ssid);

    int status = WL_IDLE_STATUS;

    //Aguarda conectar à rede WiFi
    while (status != WL_CONNECTED)
    {
        status = WiFi.begin(ssid, pass);
    }

    Serial.println();
    Serial.println("Conectado");

    //Configura o IP
    IPAddress ipAddress;
    ipAddress.fromString(ip);
    WiFi.config(ipAddress);

    //Veririca o IP
    IPAddress localIP = WiFi.localIP();
    Serial.print("IP: ");
    Serial.println(localIP);
}

//Inicializa o sensor DS18B20
void setupDS18B20()
{
    sensors.begin();   

    if (!sensors.getAddress(sensor, 0)) 
    {
        Serial.println("Sensor não encontrado!");
    }
}

void loop()
{
    WiFiEspClient client = server.available();

    //Verifica se há um novo cliente
    if (client)
    {
        Serial.println("Novo cliente conectou");
        
        //Faz a leitura da requisição
        char* request = readRequest(client); 

        //Se a requisição não for para o favicon
        if(strstr(request, "favicon") == NULL)
        {
            //Executamos a ação com o valor passado na requisição
            execute(getAction(request), getValue(request));

            //Faz a leitura dos sensores
            readSensorDS18B20();
            readSensorDHT22();
            readSensorLuminosity();

            //Envia a resposta ao cliente
            sendResponse(client);

            //Tempo para o navegador receber os dados
            delay(100);
        }
        
        //Fecha a conexão com o cliente
        client.stop();
    }
}

//Faz a leitura da primeira linha da requisição
char* readRequest(WiFiEspClient client)
{
    bool currentLineIsBlank = true;
    char request[50];
    int i = 0;
    bool firstLine = true;

    while (client.connected()){
        if(client.available()){
            char c = client.read();
            Serial.write(c);
            
            //Apenas a primeira linha da requisição nos interessa

            if(firstLine){
                request[i] = c;
                i++;
            }

            if (c == '\n'){
                //A última linha da requisição é um \r\n sozinho, após o \r\n da linha anterior
                if(currentLineIsBlank){
                    //Se chegou aqui é porque a requisição foi lida por completo
                    break;
                }

                currentLineIsBlank = true;
                firstLine = false;
            }
            else if (c != '\r'){
                //Se leu qualquer caracter que não for \n e \r significa que a linha não está em branco
                currentLineIsBlank = false;
            }
        }
    }

    return request;
}

//Envia o HTML para o cliente
void sendResponse(WiFiEspClient client)
{
    //Envia o cabeçalho HTTP
    client.print(
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html; charset=UTF-8\r\n"
    "Connection: close\r\n"
    "Refresh: 10; URL=/\r\n" //Para fazer requisação a raiz do server a cada 10 segundos
    "\r\n");

    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    head(client);//Envia o cabeçalho do HTML
    body(client);//Envia o corpo do HTML
    client.println("</html>");
}

//Envia o CSS para modificar a aparência da página
void head(WiFiEspClient client)
{
    client.println(F("<head>"
    "<style>"
        "body{"
            "text-align: center;"
            "font-family: sans-serif;"
            "font-size: 14px;"
        "}"
        "p{"
            "color:#555;"
            "font-size: 12px;"
        "}"
        ".button{"
            "outline: none;"
            "display: block;"
            "border: 1px solid #555;"
            "border-radius:18px;"
            "width: 150px;"
            "height: 30px;"
            "margin: 10px;"
            "margin-left: auto;"
            "margin-right: auto;"
            "cursor: pointer;"
        "}"
        ".button_off{"
            "background-color:#FFF;"
            "color: #555;"
        "}"
        ".button_on{"
            "background-color:#2C5;"
            "color: #fff;"
        "}"
    "</style>"
"</head>"));
}

//Exibe os dados dos sensores e cria os botões
void body(WiFiEspClient client)
{
    client.println(
    "<body>"
    "DS18B20 Temperature: " + String(temperatureDS18B20) + " °C"
    "<br>"
    "DHT22 Temperature: " + String(temperatureDHT22) + " °C"
    "<br>"
    "DHT22 Humidity: " + String(humidityDHT22) + "%"
    "<br>"
    "Luminosity: " + String(luminosity) + "<br>");

    String buttons = "";

    //Cria um botão para cada pino que possui um relê
    for(int i=0; i<PINS_COUNT; i++)
    {
        buttons.concat(button(i));
    }

    client.println(buttons);
    client.println("</body>");
}

//Cria um botão com a aparência e ação correspondente ao estado atual do relê
String button(int number)
{
    String label = String(number + 1);
    String className = "button ";
    className += pinsStatus[number] == HIGH ? "button_on" : "button_off";
    String action = pinsStatus[number] == HIGH ? "off" : "on";
    return "<button class=\"" + className + "\"onclick=\"location.href='?" + action + "=" + label + "'\">" + label + "</button>";
}

//Faz a leitura do sensor DS18B20
void readSensorDS18B20()
{
  sensors.requestTemperatures();
  temperatureDS18B20 = sensors.getTempC(sensor);
}

//Faz a leitura  do sensor DHT
void readSensorDHT22()
{
    humidityDHT22 = dht.readHumidity();
    temperatureDHT22 = dht.readTemperature();
}

//Faz a leitura do sensor de luminosidade
void readSensorLuminosity()
{
    luminosity = analogRead(PIN_LUMINOSITY);
}

//Retorna a ação que o cliente deseja executar (on off)
String getAction(char *request)
{
    return getStringBetween(request, '?', '=');
}

//Retorna o valor (numero do relê) que a ação será executada
String getValue(char *request)
{
    return getStringBetween(request, '=', ' ');
}

//Retorna a string que fica entre o primeiro caractere 'start' e o primeiro caractere 'end'
String getStringBetween(char* input, char start, char end)
{
    String str = "";
    //retorna o endereço de memória do caractere 'start'
    char* c = strchr(input, start);

    //Se não achou o caractere
    if(c == NULL)
    {
        return "";
    }

    //Vai para o próximo caractere
    c++;

    //Enquanto não chegar ao caractere 'end' ou ao final da string
    while(*c != end && *c!='\0')
    {
        str += *c;
        c++;
    }

    return str;
}

//Executada a ação junto ao valor (número do relê)
void execute(String action, String value)
{
    //Se é uma das duas ações que esperamos
    if(action == "on" || action == "off")
    {
        //Os relês são numerados a partir do 1, max o array começa do 0
        //então tiramos 1
        int index = value.toInt() - 1;
        //O número do pino será o índice mais o número do pino onde os relês
        //começam. Os relês devem estar em sequência a partir do pino inicial (FIRST_PIN)
        int pinNumber = FIRST_PIN + index;
        int status = action == "on" ? HIGH : LOW;
        digitalWrite(pinNumber, status);
        pinsStatus[index] = status;
    }
}