# Instalación y Configuración de Mosquitto MQTT en Raspberry Pi con Publisher ESP32

Este proyecto demuestra la implementación de una arquitectura de mensajería **IoT** utilizando el protocolo **MQTT**. Se configuró una **Raspberry Pi 3B+** como Broker (servidor) y un **ESP32** como Publisher (cliente) para la transmisión de datos en tiempo real.

## 🚀 Requisitos de Hardware
- **Broker:** Raspberry Pi 3B+ (con fuente de poder de 5V a 3A).
- **Publisher:** ESP32 DevKit V1.
- **Red:** Conexión local Wi-Fi.

## 🛠️ 1. Configuración del Broker (Raspberry Pi)

### Instalación de Mosquitto
En la terminal de la Raspberry Pi, se ejecutaron los siguientes comandos para actualizar el sistema e instalar el broker:

```
sudo apt update && sudo apt upgrade -y
sudo apt install mosquitto mosquitto-clients -y
sudo systemctl enable mosquitto
```

### Configuración de Acceso Externo
Para permitir que el ESP32 se conecte desde fuera de la Raspberry, se editó el archivo de configuración en /etc/mosquitto/conf.d/external.conf:

```
listener 1883
allow_anonymous true
```
Se reinició el servicio para aplicar los cambios:

```
sudo systemctl restart mosquitto
```
## 📡 2. Configuración del Publisher (ESP32)
El firmware se desarrolló en Arduino IDE utilizando la librería PubSubClient. El dispositivo publica un mensaje cada 5 segundos al tópico escom/test.

Código Fuente (Firmware)
```
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
    client.publish("escom/test", "Hola desde el ESP32");
    Serial.println("Mensaje enviado a la Raspberry");
  }
}
```
## 📊 3. Evidencias de Funcionamiento
Las capturas de pantalla adjuntas en el repositorio muestran:

Conexión exitosa: Log del Monitor Serie del ESP32 confirmando la conexión al Wi-Fi y al Broker.
<img width="554" height="107" alt="Publisher en ESP32" src="https://github.com/user-attachments/assets/cbb22674-924a-40b1-9387-0e74e05be4a9" />

Recepción de datos: Terminal de la Raspberry Pi ejecutando mosquitto_sub -h localhost -t "escom/test" -v y mostrando los mensajes recibidos en tiempo real.
<img width="443" height="107" alt="Captura de pantalla 2026-04-22 172126" src="https://github.com/user-attachments/assets/1cf563e0-081c-4236-9238-192d735b086f" />


##

Desarrollado por: 
   
   -Kendra Lizeth Torres Gomez
  
   -Angélica Alejandra Quevedo Hernández
  
   -Mario David Fabela Flores

Institución: Escuela Superior de Cómputo (ESCOM - IPN)

Materia: Internet de las cosas/Embedded Systems 6CM3 26-1
