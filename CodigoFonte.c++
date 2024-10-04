//Bibliotecas
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Configurações - variáveis editáveis
const char* default_SSID = "FIAP-IBM"; 
const char* default_PASSWORD = "Challenge@24!"; 
const char* default_BROKER_MQTT = "18.208.160.16"; 
const int default_BROKER_PORT = 1883; 
const char* default_TOPICO_SUBSCRIBE = "/TEF/device200/cmd"; 
const char* default_TOPICO_PUBLISH_1 = "/TEF/device200/attrs"; 
const char* default_TOPICO_PUBLISH_2 = "/TEF/device200/attrs/p"; 
const char* default_TOPICO_PUBLISH_TEMP = "/TEF/device200/attrs/temp"; 
const char* default_TOPICO_PUBLISH_HUM = "/TEF/device200/attrs/hum";
const char* default_ID_MQTT = "fiware_200"; 
const int default_D4 = 2; 
const int LDRPin = 34; 
#define DHTPIN 4 // Pino para DHT
#define DHTTYPE DHT11 // DHT11 ou DHT22
const char* topicPrefix = "device200";

// Sensor DHT
DHT dht(DHTPIN, DHTTYPE);

char* SSID = const_cast<char*>(default_SSID);
char* PASSWORD = const_cast<char*>(default_PASSWORD);
char* BROKER_MQTT = const_cast<char*>(default_BROKER_MQTT);
int BROKER_PORT = default_BROKER_PORT;
char* TOPICO_SUBSCRIBE = const_cast<char*>(default_TOPICO_SUBSCRIBE);
char* TOPICO_PUBLISH_1 = const_cast<char*>(default_TOPICO_PUBLISH_1);
char* TOPICO_PUBLISH_2 = const_cast<char*>(default_TOPICO_PUBLISH_2);
char* TOPICO_PUBLISH_TEMP = const_cast<char*>(default_TOPICO_PUBLISH_TEMP);
char* TOPICO_PUBLISH_HUM = const_cast<char*>(default_TOPICO_PUBLISH_HUM);
char* ID_MQTT = const_cast<char*>(default_ID_MQTT);
int D4 = default_D4;

WiFiClient espClient;
PubSubClient MQTT(espClient);
char EstadoSaida = '0';

void setup() {
    pinMode(D4, OUTPUT);
    InitOutput();
    initSerial();
    initWiFi();
    initMQTT();
    dht.begin(); // Inicia o sensor DHT
    delay(5000);
    MQTT.publish(TOPICO_PUBLISH_1, "s|on");
}

void loop() {
    VerificaConexoesWiFIEMQTT();
    EnviaEstadoOutputMQTT();
    handleLuminosity();
    handleDHT();
    MQTT.loop();
}

void initSerial() {
    Serial.begin(115200);
}

void initWiFi() {
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(SSID);
    Serial.println("Aguarde");
    reconectWiFi();
}

void initMQTT() {
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);
    MQTT.setCallback(mqtt_callback);
}

void reconectWiFi() {
    if (WiFi.status() == WL_CONNECTED) return;
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("Conectado com sucesso na rede ");
    Serial.print(SSID);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
    digitalWrite(D4, LOW);
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    String msg;
    for (int i = 0; i < length; i++) {
        char c = (char)payload[i];
        msg += c;
    }
    Serial.print("- Mensagem recebida: ");
    Serial.println(msg);

    String onTopic = String(topicPrefix) + "@on|";
    String offTopic = String(topicPrefix) + "@off|";

    if (msg.equals(onTopic)) {
        digitalWrite(D4, HIGH);
        EstadoSaida = '1';
    }
    if (msg.equals(offTopic)) {
        digitalWrite(D4, LOW);
        EstadoSaida = '0';
    }
}

void VerificaConexoesWiFIEMQTT() {
    if (!MQTT.connected()) reconnectMQTT();
    reconectWiFi();
}

void EnviaEstadoOutputMQTT() {
    if (EstadoSaida == '1') {
        MQTT.publish(TOPICO_PUBLISH_1, "s|on");
        Serial.println("- Led Ligado");
    }

    if (EstadoSaida == '0') {
        MQTT.publish(TOPICO_PUBLISH_1, "s|off");
        Serial.println("- Led Desligado");
    }
    Serial.println("- Estado do LED onboard enviado ao broker!");
    delay(1000);
}

void InitOutput() {
    pinMode(D4, OUTPUT);
    digitalWrite(D4, HIGH);
    boolean toggle = false;

    for (int i = 0; i <= 10; i++) {
        toggle = !toggle;
        digitalWrite(D4, toggle);
        delay(200);
    }
}

void reconnectMQTT() {
    while (!MQTT.connected()) {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(TOPICO_SUBSCRIBE);
        } else {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Haverá nova tentativa de conexão em 2s");
            delay(2000);
        }
    }
}

void handleLuminosity() {
    int sensorValue = analogRead(LDRPin);
    int luminosity = map(sensorValue, 0, 4095, 0, 100);
    String mensagem = String(luminosity);
    Serial.print("Valor da luminosidade: ");
    Serial.println(mensagem.c_str());
    MQTT.publish(TOPICO_PUBLISH_2, mensagem.c_str());
}
void handleDHT() {
    // Leitura do DHT
    float temperatura = dht.readTemperature();
    float umidade = dht.readHumidity();

    // Verifica se a leitura é válida
    if (isnan(temperatura) || isnan(umidade)) {
        Serial.println("Falha ao ler do sensor DHT! Verifique a conexão e o sensor.");
        return;
    }

    // Publica os valores de temperatura e umidade
    String tempMsg = String(temperatura);
    String humMsg = String(umidade);

    Serial.print("Temperatura: ");
    Serial.println(tempMsg);
    Serial.print("Umidade: ");
    Serial.println(humMsg);

    MQTT.publish(TOPICO_PUBLISH_TEMP, tempMsg.c_str());
    MQTT.publish(TOPICO_PUBLISH_HUM, humMsg.c_str());
}

