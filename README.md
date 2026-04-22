# Instalación y Configuración de Mosquitto MQTT en Raspberry Pi con Publisher ESP32

Este proyecto demuestra la implementación de una arquitectura de mensajería **IoT** utilizando el protocolo **MQTT**. Se configuró una **Raspberry Pi 3B+** como Broker (servidor) y un **ESP32** como Publisher (cliente) para la transmisión de datos en tiempo real.

## 🚀 Requisitos de Hardware
- **Broker:** Raspberry Pi 3B+ (con fuente de poder de 5V @ 3A).
- **Publisher:** ESP32 DevKit V1.
- **Red:** Conexión local Wi-Fi (2.4 GHz).

## 🛠️ 1. Configuración del Broker (Raspberry Pi)

### Instalación de Mosquitto
En la terminal de la Raspberry Pi, se ejecutaron los siguientes comandos para actualizar el sistema e instalar el broker:

```bash
sudo apt update && sudo apt upgrade -y
sudo apt install mosquitto mosquitto-clients -y
sudo systemctl enable mosquitto

###Configuración de Acceso Externo
Para permitir que el ESP32 se conecte desde fuera de la Raspberry, se editó el archivo de configuración en /etc/mosquitto/conf.d/external.conf:

Plaintext
listener 1883
allow_anonymous true
Se reinició el servicio para aplicar los cambios:
sudo systemctl restart mosquitto

📡 2. Configuración del Publisher (ESP32)
El desarrollo del firmware se realizó en Arduino IDE utilizando la librería PubSubClient. El ESP32 publica mensajes cada 5 segundos al tópico escom/test.

Parámetros de Conexión
MQTT Broker IP: 192.168.1.72

Puerto: 1883

Tópico: escom/test

📊 3. Evidencias de Funcionamiento
Las capturas de pantalla adjuntas en el repositorio muestran:

Conexión exitosa: Log del Monitor Serie del ESP32 confirmando la conexión al Wi-Fi y al Broker.

Recepción de datos: Terminal de la Raspberry Pi ejecutando mosquitto_sub y mostrando los mensajes recibidos en tiempo real.

Desarrollado por: Mario Fabela

Institución: Escuela Superior de Cómputo (ESCOM - IPN)

Materia: Sistemas en Red / Internet de las Cosas (IoT)
