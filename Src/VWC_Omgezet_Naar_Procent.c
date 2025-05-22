#include <SDI12.h>
#include <WiFi.h>
#include <WiFiUDP.h>

// WiFi instellingen
const char* ssid = "504F94A12106";  // Jouw WiFi SSID
const char* password = "";          // Jouw WiFi wachtwoord

// IP en poort voor UDP verzending
const char* udpAddress = "192.168.1.77";  // IP van Miniserver
const int udpPort = 50001;               // UDP-poort

WiFiUDP udp;

#define DATA_PIN 17  // GPIO-pin verbonden met SDI-12 datalijn
SDI12 mySDI12(DATA_PIN);

void setup() {
  Serial.begin(115200);
  delay(500);

  mySDI12.begin();
  delay(500);
  Serial.println("✅ SDI-12 communicatie gestart");

  WiFi.begin(ssid, password);

  // Verbinden met WiFi
  Serial.print("🔌 Verbinden met WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("✅ WiFi verbonden!");

  // Start UDP
  udp.begin(udpPort);
}

void loop() {
  // Start meting op adres 0
  mySDI12.sendCommand("0M!");
  delay(1500);

  // Vraag meetgegevens op
  mySDI12.sendCommand("0D0!");
  delay(300);

  // Lees ruwe sensorrespons
  String response = "";
  while (mySDI12.available()) {
    char c = mySDI12.read();
    response += c;
  }

  Serial.println("📨 Ruwe data: " + response);

  // Stap 1: Filter alleen geldige tekens
  String filteredData = "";
  for (int i = 0; i < response.length(); i++) {
    char c = response[i];
    if (isDigit(c) || c == '.' || c == '+' || c == '-') {
      filteredData += c;
    }
  }

  Serial.println("🔍 Gefilterde data: " + filteredData);

  // Stap 2: Verwijder eventuele prefix tot aan eerste "+"
  int startIndex = filteredData.indexOf("+");
  if (startIndex != -1) {
    filteredData = filteredData.substring(startIndex + 1);
  }

  Serial.println("🎯 Gezuiverde data: " + filteredData);

  // Stap 3: Vind posities van de '+' tekens
  int firstPlus = filteredData.indexOf('+');
  int secondPlus = filteredData.indexOf('+', firstPlus + 1);

  if (firstPlus == -1 || secondPlus == -1) {
    Serial.println("⚠️ Fout: Onvolledige data ontvangen.");
    return;
  }

  // Stap 4: Parse en normaliseer
  float rawVWC = filteredData.substring(0, firstPlus).toFloat();  // VWC (ruwe waarde)
  float temp = filteredData.substring(firstPlus + 1, secondPlus).toFloat(); // Temperatuur
  float ec = filteredData.substring(secondPlus + 1).toFloat();  // EC

  // Normaliseer VWC naar 0–100% (aangenomen max = 0.7)
  float vwcPercent = ((rawVWC - 0.0) / (0.7 - 0.0)) * 100.0;
  vwcPercent = constrain(vwcPercent, 0.0, 100.0);  // Beperk tot 0–100%

  // Print meetwaarden
  Serial.println("----- 📊 TEROS-12 Meetwaarden -----");
  Serial.printf("🌱 VWC (Watergehalte): %.2f %%\n", vwcPercent);
  Serial.printf("🌡️ Temperatuur: %.2f °C\n", temp);
  Serial.printf("⚡ Geleidbaarheid (EC): %.2f µS/cm\n", ec);
  Serial.println("-----------------------------------");

  // Verstuur via UDP
  udp.beginPacket(udpAddress, udpPort);
  udp.printf("VWC: %.2f%%, Temp: %.2f°C, EC: %.2f µS/cm", vwcPercent, temp, ec);
  udp.endPacket();

  delay(10000);  // Wacht 10 seconden voor volgende meting
}
