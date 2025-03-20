#include <SDI12.h>

#define DATA_PIN 17 // GPIO pin verbonden met de SDI-12 datalijn

SDI12 mySDI12(DATA_PIN);

void setup() {
  Serial.begin(115200);
  delay(500);
  mySDI12.begin();
  delay(500);
  Serial.println("SDI-12 communicatie gestart voor twee TEROS-12 sensoren");
}

void meetSensor(String sensorAdres) {
  Serial.println("\n🌍 Sensor " + sensorAdres + " wordt uitgelezen...");

  // Start meting
  mySDI12.sendCommand(sensorAdres + "M!");
  delay(1500); // Wacht op meting

  // Vraag meetdata op
  mySDI12.sendCommand(sensorAdres + "D0!");
  delay(300);

  String response = "";
  while (mySDI12.available()) {
    char c = mySDI12.read();
    response += c;
  }

  Serial.println("📡 Ruwe data van sensor " + sensorAdres + ": " + response);

  // Controleer of er data is ontvangen
  if (response.length() < 5) {
    Serial.println("❌ Fout: Geen of onvolledige data ontvangen van sensor " + sensorAdres);
    return;
  }

  // Alleen numerieke tekens behouden
  String filteredData = "";
  for (int i = 0; i < response.length(); i++) {
    char c = response[i];
    if (isDigit(c) || c == '.' || c == '+' || c == '-') {
      filteredData += c;
    }
  }

  Serial.println("🔍 Gefilterde data: " + filteredData);

  // Zoek de eerste '+' als scheidingsteken voor data
  int startIndex = filteredData.indexOf("+");
  if (startIndex != -1) {
    filteredData = filteredData.substring(startIndex + 1);
  }

  Serial.println("🛠️ Data na verwijderen prefix: " + filteredData);

  // Splitsen op '+' om de meetwaarden te verkrijgen
  int firstPlus = filteredData.indexOf('+');
  int secondPlus = filteredData.indexOf('+', firstPlus + 1);

  if (firstPlus == -1 || secondPlus == -1) {
    Serial.println("❌ Fout: Onvolledige of incorrecte data van sensor " + sensorAdres);
    return;
  }

  // Extract de drie meetwaarden
  float vwc = filteredData.substring(0, firstPlus).toFloat();
  float temp = filteredData.substring(firstPlus + 1, secondPlus).toFloat();
  float ec = filteredData.substring(secondPlus + 1).toFloat();

  // Print de uitgelezen waarden
  Serial.println("----- Meetwaarden van TEROS-12 Sensor " + sensorAdres + " -----");
  Serial.print("🌱 VWC (Bodemvocht): ");
  Serial.print(vwc, 2);
  Serial.println(" %");

  Serial.print("🌡️ Temperatuur: ");
  Serial.print(temp, 2);
  Serial.println(" °C");

  Serial.print("⚡ Geleidbaarheid (EC): ");
  Serial.print(ec, 2);
  Serial.println(" µS/cm");
  Serial.println("--------------------------------------");
}

void loop() {
  meetSensor("0"); // Meet sensor met adres 0
  delay(3000); // Korte pauze tussen de sensoren
  meetSensor("1"); // Meet sensor met adres 1
  delay(10000); // Wacht 10 seconden voor de volgende meetronde
}
