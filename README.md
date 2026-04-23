# 📡 Arquitectura IoT con MQTT usando Raspberry Pi y ESP32

![IoT](https://img.shields.io/badge/IoT-MQTT-blue)
![Plataforma](https://img.shields.io/badge/Plataforma-Raspberry%20Pi%20%7C%20ESP32-green)
![Protocolo](https://img.shields.io/badge/Protocolo-MQTT-orange)
![Estado](https://img.shields.io/badge/Estado-Funcionando-success)

---

## 📌 Descripción General

Este proyecto implementa una arquitectura básica de comunicación para aplicaciones de **Internet de las Cosas (IoT)** utilizando el protocolo **MQTT**.

* Una **Raspberry Pi 3B+** funciona como **Broker MQTT**.
* Un **ESP32** actúa como **Publisher**, enviando datos de forma periódica.
* La comunicación se realiza a través de una **red Wi-Fi local**.

Este modelo demuestra el uso del paradigma **publish/subscribe**, ideal para sistemas distribuidos y de bajo consumo.

---

## 🧰 Requisitos de Hardware

| Componente   | Descripción                          |
| ------------ | ------------------------------------ |
| 🖥️ Broker   | Raspberry Pi 3B+ (fuente de 5V / 3A) |
| 📡 Publisher | ESP32 DevKit V1                      |
| 🌐 Red       | Conexión Wi-Fi local                 |

---

## ⚙️ Configuración del Broker (Raspberry Pi)

### 1. Instalación de Mosquitto

Ejecutar los siguientes comandos para actualizar el sistema e instalar el broker MQTT:

```bash
sudo apt update && sudo apt upgrade -y
sudo apt install mosquitto mosquitto-clients -y
sudo systemctl enable mosquitto
```

---

### 2. Habilitar conexiones externas

Editar (o crear) el archivo de configuración:

```bash
/etc/mosquitto/conf.d/external.conf
```

Agregar el siguiente contenido:

```conf
listener 1883
allow_anonymous true
```

Reiniciar el servicio para aplicar cambios:

```bash
sudo systemctl restart mosquitto
```

---

## 📡 Configuración del Publisher (ESP32)

El firmware del ESP32 fue desarrollado en **Arduino IDE** utilizando la librería `PubSubClient`.

* Publicación de mensajes cada **5 segundos**
* Tópico utilizado: `escom/test`

### 🔧 Código fuente

```cpp
#include <WiFi.h>
#include <PubSubClient.h>

// Credenciales Wi-Fi
const char* ssid = "INFINITUM4DD4";
const char* password = "Kh7Sq8Qp6g";

// Dirección IP del broker
const char* mqtt_server = "192.168.1.72"; 

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado");

  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    Serial.print("Conectando al broker MQTT...");
    if (client.connect("ESP32_ESCOM")) {
      Serial.println("Conectado correctamente");
    } else {
      Serial.print("Error: ");
      Serial.println(client.state());
      delay(5000);
    }
  }

  client.loop();

  static unsigned long lastMsg = 0;
  if (millis() - lastMsg > 5000) {
    lastMsg = millis();
    client.publish("escom/test", "Hola desde el ESP32");
    Serial.println("Mensaje enviado");
  }
}
```

---

## 📊 Resultados

### ✅ Conexión exitosa

* El ESP32 logra conectarse a la red Wi-Fi y al broker MQTT.
* Esto se verifica mediante el monitor serie.
<img width="554" height="107" alt="Publisher en ESP32" src="https://github.com/user-attachments/assets/cbb22674-924a-40b1-9387-0e74e05be4a9" />  

### 📥 Recepción de mensajes

Ejecutar en la Raspberry Pi:

```bash
mosquitto_sub -h localhost -t "escom/test" -v
```
<img width="443" height="107" alt="Captura de pantalla 2026-04-22 172126" src="https://github.com/user-attachments/assets/1cf563e0-081c-4236-9238-192d735b086f" />
Se pueden observar los mensajes enviados desde el ESP32 en tiempo real.

---

## 👥 Autores

* **Kendra Lizeth Torres Gómez**
* **Angélica Alejandra Quevedo Hernández**
* **Mario David Fabela Flores**

---

## 🏫 Institución

**Escuela Superior de Cómputo (ESCOM - IPN)**
**Materia:** Internet de las Cosas / Embedded Systems (6CM3 26-1)

---

## ⭐ Notas

* Se utiliza acceso anónimo (`allow_anonymous true`) únicamente con fines educativos.
* Para entornos reales se recomienda:

  * Autenticación con usuario y contraseña
  * Uso de TLS/SSL
  * Configuración de firewall
