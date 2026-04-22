#include <WiFi.h>
#include <PubSubClient.h>

// DATOS DE RED
const char* ssid = "INFINITUM4DD4";
const char* password = "Kh7Sq8Qp6g";

// IP DE RASPBERRY 
const char* mqtt_server = "192.168.1.72"; 

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  
  // Conectar al Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");

  // Configurar el Broker
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    Serial.print("Intentando conexión MQTT...");
    if (client.connect("ESP32_ESCOM")) {
      Serial.println("¡Conectado al Broker de la Pi!");
    } else {
      Serial.print("Falló, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
  client.loop();

  // Publicar un mensaje cada 5 segundos
  static unsigned long lastMsg = 0;
  if (millis() - lastMsg > 5000) {
    lastMsg = millis();
    client.publish("escom/test", "Hola desde el ESP32 del inge");
    Serial.println("Mensaje enviado a la Raspberry");
  }
}
