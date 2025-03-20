# ESP32 WiFi Setup for Teros-12 and 5TE-ECH20 Sensors

## Project Overview
For this project, we use the **ESP-WROOM32** to receive data from the **Teros-12** sensor and the **5TE-ECH20** sensor.

We need to receive the data from these sensors and send them over WiFi to our other classmates using the built-in WiFi functionality of the ESP-WROOM32. This document covers all the necessary steps to achieve this. After configuration, the ESP-WROOM32 will be able to send the received data to the server of our classmates.

---

## ESP32 WiFi Library
By default, the **ESP32 WiFi** library is already built into the **Arduino Core for ESP32**, so no external library installation is required. This library provides the fundamental operations needed for any Wi-Fi-based application.

We will use the `WiFi.h` Arduino library to leverage the hardware WiFi capabilities of the ESP32 microcontroller. Since the ESP32 WiFi library is already included in the Arduino Core, the next step is to include it in our code before using WiFi functionalities with ESP32:

```cpp
#include <WiFi.h>
```

---

## ESP32 WiFi Modes
The ESP32 WiFi can run in one of the following modes:

- **WiFi Station (STA):** The ESP32 connects to an existing network (like a home router or another access point).
  ```cpp
  WiFi.mode(WIFI_STA);
  ```
- **Access Point (AP):** The ESP32 creates its own network, acting as an access point.
  ```cpp
  WiFi.mode(WIFI_AP);
  ```
- **Access Point + Station (AP_STA):** The ESP32 acts as both an access point and a station simultaneously.
  ```cpp
  WiFi.mode(WIFI_AP_STA);
  ```

Additionally, there is a **Promiscuous Mode**, where the ESP32 functions as a WiFi sniffer. However, the default ESP32 Library supports only the first three modes.

Since we want to connect to an **existing network** provided by our classmates, we will use **Station Mode (STA)**.

---

## WiFi Station Mode
When the ESP32 is set to **WiFi Station Mode**, it can connect to an existing Wi-Fi network (e.g., a home router) and send or receive data with other devices on the same network using its unique IP address.

The **router (AP)** establishes the network, and the ESP32 joins as a client, receiving a unique **IP address** for communication.

### Set ESP32 to Station Mode (STA)
To set your ESP32 to **Station Mode**, use the following code:

```cpp
WiFi.mode(WIFI_STA);
```

Next, define the **WiFi credentials**:

```cpp
// Replace with your own network credentials
const char* ssid = "yourNetworkSSID";
const char* password = "yourNetworkPassword";
```

Then, connect to the network:

```cpp
WiFi.begin(ssid, password);
```

---

## ESP32 WiFi Networking
To connect the ESP32 to an existing network:

1. Set **WiFi mode** to STA:
   ```cpp
   WiFi.mode(WIFI_STA);
   ```
2. Start the connection:
   ```cpp
   WiFi.begin(ssid, password);
   ```
3. Monitor connection status:
   ```cpp
   while (WiFi.status() != WL_CONNECTED) {
       Serial.print(".");
       delay(100);
   }
   Serial.println("\nConnected to the WiFi network");
   ```

Once successfully connected, the ESP32 can communicate over the network.

---

## ESP32 UDP
**UDP (User Datagram Protocol)** is a connectionless protocol that allows devices to send and receive data without establishing a dedicated connection. This is useful for applications requiring low-latency communication, such as real-time control systems or sensor networks.

However, **UDP is less reliable** than other communication protocols as it does not guarantee that the sent data is received correctly. It simply transmits data as quickly as possible without acknowledgment.

To use **UDP with ESP32**, you can use the built-in `WiFiUDP.h` library or the `AsyncUDP` library for asynchronous operations.

---

This document provides a foundation for configuring ESP32 WiFi connectivity for sensor data transmission. Further implementation will involve setting up UDP communication to send data efficiently over the network.
