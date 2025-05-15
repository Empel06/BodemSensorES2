#include <SDI12.h>
#include <WiFi.h>
#include <WiFiUDP.h>

// Replace with your network credentials
const char* ssid = "504F94A12106";      // Your WiFi SSID
const char* password = "";  // Your WiFi Password

// IP and port for sending and receiving UDP packets
const char* udpIP = "192.168.1.77";  // IP to send UDP packets to (Miniserver IP)
const int udpPort = 50001;           // Port to send UDP packets to

WiFiUDP udp;  // Initialize WiFiUDP object

#define DATA_PIN 17 // GPIO pin verbonden met de SDI-12 datalijn

SDI12 mySDI12(DATA_PIN);

void setup() {
  Serial.begin(115200);
  delay(500);
  mySDI12.begin();
  delay(500);
  Serial.println("SDI-12 communicatie gestart");

  WiFi.begin(ssid, password);  // Start connecting to WiFi

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi connected!");

    // Start listening for UDP packets on the specified port
    udp.begin(udpPort);  // Bind to UDP port
  
  
}



void loop() {
  WiFiUDP udp;

  const char * udpAddress = "192.168.1.77";
  const int udpPort = 50001;

  mySDI12.sendCommand("0M!"); // Start meting op adres 0
  delay(1500); // Wacht op meting

  mySDI12.sendCommand("0D0!"); // Vraag meetdata op
  delay(300);

  String response = "";
  while (mySDI12.available()) {
    char c = mySDI12.read();
    response += c;
  }

  // Toon de ruwe respons
  Serial.println("Ruwe data: " + response);

  // Stap 1: Alleen numerieke tekens (+, -, ., cijfers) behouden
  String filteredData = "";
  for (int i = 0; i < response.length(); i++) {
    char c = response[i];
    if (isDigit(c) || c == '.' || c == '+' || c == '-') {
      filteredData += c;
    }
  }

  Serial.println("Gefilterde data: " + filteredData);

  // Stap 2: Verwijder de "000130+" aan het begin van de gefilterde data
  int startIndex = filteredData.indexOf("+"); // Zoek de eerste "+"
  if (startIndex != -1) {
    filteredData = filteredData.substring(startIndex + 1); // Verwijder alles tot en met de eerste "+"
  }

  Serial.println("Na verwijderen van '000130+': " + filteredData);

  // Stap 3: Splitsen op "+" om de meetwaarden te verkrijgen
  int firstPlus = filteredData.indexOf('+');
  int secondPlus = filteredData.indexOf('+', firstPlus + 1);

  if (firstPlus == -1 || secondPlus == -1) {
    Serial.println("Fout: Onvolledige data ontvangen.");
    return;
  }

  // Stap 4: Extract de drie meetwaarden als floats
  float vwc = filteredData.substring(0, firstPlus).toFloat();  // Van start tot eerste "+"
  float temp = filteredData.substring(firstPlus + 1, secondPlus).toFloat(); // Van eerste "+" tot tweede "+"
  float ec = filteredData.substring(secondPlus + 1).toFloat();  // Van tweede "+" naar het einde

  // Print de uitgelezen waarden
  Serial.println("----- Meetwaarden van TEROS-12 Sensor -----");
  Serial.print("🌱 VWC (Volumetric Water Content): ");
  Serial.print(ec, 2);
  Serial.println(" %");

  Serial.print("🌡️ Temperatuur: ");
  Serial.print(temp, 2);
  Serial.println(" °C");

  Serial.print("⚡ Geleidbaarheid (EC): ");
  Serial.print(vwc, 2);
  Serial.println(" µS/cm");
  Serial.println("--------------------------------------");

  


  udp.beginPacket(udpAddress,udpPort);
  udp.printf("VWC: %f, Temp: %f, EC: %f", ec, temp, vwc);
  udp.endPacket();

  delay(1000); // Wacht 10 seconden voor de volgende meting
}