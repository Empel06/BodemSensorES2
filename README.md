# BodemSensorES2

## Projectoverzicht

Dit project richt zich op de integratie van de TEROS 12 en ECH20/5TE bodemsensoren met een ESP32-microcontroller. De verzamelde gegevens, zoals bodemvochtigheid, temperatuur en elektrische geleidbaarheid, worden via WiFi naar een Loxone Miniserver gestuurd. Loxone analyseert deze data en stuurt notificaties naar gebruikers via GSM en activeert relevante uitgangen.

---

## Benodigde Hardware

- **Microcontroller**: ESP32
- **Sensormodules**:
  - TEROS 12
  - ECH20/5TE
- **Communicatieprotocol**: SDI-12 (voor TEROS 12 en ECH20/5TE)
- **Server**: Loxone Miniserver
- **Netwerkverbinding**: WiFi
  - Miniserver IP: `192.168.1.77`
  - Poort: `50001`

---

## Softwarevereisten

- **Programmeertaal**: C++
- **Ontwikkelomgeving**: Arduino IDE
- **Gebruikte bibliotheken**:
  - [`SDI12`](https://github.com/EnviroDIY/Arduino-SDI-12)  
  - [`WiFi`](https://www.arduino.cc/en/Reference/WiFi)  
  - [`WiFiUDP`](https://www.arduino.cc/en/Reference/WiFiUDP)

---

## Repositorystructuur

BodemSensorES2/
├── Altium/ # Altium projects files

├── Docs/ # Documentatiebestanden

├── Schema's/ # Schematische diagrammen

├── Src/ # Broncodebestanden

│ ├── 1Sensor.cpp # Uitlezen van 1 senor

│ ├── 2Sensors.cpp # Uitlezen van 2 sensors

│ └── SensorAdressChange.cpp # Sensor adress wijziging

└── README.md 

---

## Functies

- **Sensorcommunicatie**:
  - TEROS 12 via SDI-12
  - ECH20/5TE via SDI-12
- **Dataverwerking**:
  - Watergehalte, temperatuur en geleidbaarheid (TEROS 12)
  - Watergehalte, temperatuur en geleidbaarheid (ECH20/5TE)
- **Data-overdracht naar Loxone via WiFi**
- **Loxone-functionaliteiten**:
  - Analyse van verzamelde data
  - Versturen van notificaties naar gebruikers via GSM
  - Activeren van relevante uitgangen op basis van de data

---

## Installatie

1. **Clone de repository**:

   ```bash
   git clone https://github.com/Empel06/BodemSensorES2.git
   cd BodemSensorES2
   ```

2. **Installeer de benodigde bibliotheken**:

- Open de Arduino IDE.
    
- Ga naar **Sketch** > **Include Library** > **Manage Libraries**.
    
- Zoek en installeer de volgende bibliotheken:
    
    - `SDI12`
        
    - `WiFi`
        
    - `WiFiUDP`

**Configureer de netwerkinstellingen**:
    
  Open `Src/1sensor.cpp`.
        
  - Pas de WiFi-gegevens aan:
      ```bash   
        const char* ssid = "jouw_SSID"; const char* password = "jouw_wachtwoord";
      ```
  - Pas het IP-adres van de Loxone Miniserver aan:
        
      ```bash
        const char* udpIP = "192.168.1.77"; const int udpPort = 50001;
      ```
        
3. **Upload de code naar de ESP32**:
    
    - Selecteer het juiste board en poort in de Arduino IDE.
        
    - Upload het programma naar de ESP32.
        

---

## Gebruik

- **Sensorconfiguratie**:
    
    - Sluit de TEROS 12 en ECH20/5TE sensoren aan op de ESP32 volgens de SDI-12-specificaties.
        
    - Zorg ervoor dat de sensoren correct zijn geïdentificeerd en geconfigureerd.
        
- **Data-acquisitie**:
    
    - Na het opstarten van de ESP32 begint het programma met het verzamelen van gegevens van de sensoren.
        
    - De verzamelde data wordt verwerkt en via WiFi naar de Loxone Miniserver gestuurd.
        
- **Loxone-integratie**:
    
    - Configureer de Loxone Miniserver om de ontvangen data te verwerken.
        
    - Stel notificaties en acties in op basis van de ontvangen gegevens.
        

---

## Testen

- **Sensorfunctionaliteit**:
    
    - Controleer of de sensoren correct reageren op commando's en betrouwbare data leveren.
        
    - Verifieer de nauwkeurigheid van de gemeten waarden.
        
- **WiFi-verbinding**:
    
    - Zorg ervoor dat de ESP32 verbinding maakt met het opgegeven WiFi-netwerk.
        
    - Verifieer de stabiliteit van de verbinding tijdens het dataverkeer.
        
- **UDP-communicatie**:
    
    - Controleer of de data correct wordt verzonden naar de Loxone Miniserver.
        
    - Verifieer of de Miniserver de ontvangen data correct verwerkt.
        

---

## Bestanden en mappen

- **Altium/**: Bevat de PCB-ontwerpen voor de hardware.
    
- **Docs/**: Bevat documentatiebestanden met technische details en handleidingen.
    
- **Schema's/**: Bevat schematische diagrammen van de hardwareconfiguratie.
    
- **Src/**: Bevat de code om de sensorwaardes uit te lezen en te versturen