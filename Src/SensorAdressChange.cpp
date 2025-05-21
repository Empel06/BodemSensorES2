#include <SDI12.h>

#define DATA_PIN 17  // Pas aan naar je eigen pin
SDI12 mySDI12(DATA_PIN);

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("Start SDI-12...");
  mySDI12.begin();
  delay(500);

  // Oude en nieuwe adres instellen
  char oldAddress = '0';  // huidig adres van sensor
  char newAddress = '1';  // nieuw gewenst adres

  String changeCmd = String(oldAddress) + "A" + String(newAddress) + "!";

  Serial.print("Verstuur commando: ");
  Serial.println(changeCmd);

  mySDI12.sendCommand(changeCmd);
  delay(300);

  String response = "";
  while (mySDI12.available()) {
    char c = mySDI12.read();
    response += c;
  }

  Serial.print("Respons: ");
  Serial.println(response);

  if (response.startsWith(String(newAddress))) {
    Serial.println("Adreswijziging gelukt!");
  } else {
    Serial.println("Adreswijziging mislukt.");
  }

  mySDI12.end();
}

void loop() {
}
