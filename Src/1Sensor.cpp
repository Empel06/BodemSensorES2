#include <SDI12.h>

#define DATA_PIN 17 // GPIO pin verbonden met de SDI-12 datalijn

SDI12 mySDI12(DATA_PIN);

void setup() {
  Serial.begin(115200);
  delay(500);
  mySDI12.begin();
  delay(500);
  Serial.println("SDI-12 communicatie gestart");
}

void loop() {
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

  delay(1000); // Wacht 10 seconden voor de volgende meting
}