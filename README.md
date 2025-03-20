# Opdracht Teros 12 _ ECH20/5TE versie 1

## Overzicht
Dit project richt zich op de integratie van de **TEROS 12** en **ECH20/5TE** sensoren met een **ESP32**. De verzamelde data wordt gecommuniceerd via **WiFi** naar een **Loxone** smart home systeem. Loxone analyseert de data en stuurt notificaties naar gebruikers via **GSM** en activeert relevante uitgangen.

## Hardware
- **Sensormodules**: TEROS 12, ECH20/5TE
- **Microcontroller**: ESP32 
- **Communicatieprotocol**: SDI-12 (voor TEROS 12 en ECH20/5TE)
- **Server**: Loxone
- **Netwerkverbinding**: WiFi : Miniserver IP: 192.168.1.77 : 50001


## Software
- **Programmeertaal**: C++
- **IDE**: Arduino IDE 
- **SDI-12 en I2C bibliotheken**

## Functionaliteiten
- **Sensorcommunicatie**:
  - TEROS 12 via SDI-12
  - ECH20/5TE via SDI-12
- **Dataverwerking**:
  - Watergehalte, temperatuur en geleidbaarheid (TEROS 12)
  - Watergehalte, temperatuur en geleidbaarheid (ECH20/5TE)
(ECH20/5TE)
- **Data-overdracht naar Loxone via WiFi**
- **Loxone functionaliteiten**:
  - Analyseren van binnenkomende data
  - Notificaties sturen via GSM
  - Uitgangen activeren op basis van sensorwaarden

## Testprocedure
1. **Hardwareconfiguratie**
   - Sluit de TEROS 12 sensor correct aan op de ESP32
   - Verbind de ECH20/5TE sensor correct aan op de ESP32
   - Zorg voor een stabiele WiFi-verbinding
2. **Software-instellingen**
   - Controleer de juiste SDI-12 en I2C communicatie
   - Test data-acquisitie en verwerking
3. **Communicatietest met Loxone**
   - Stuur testdata en controleer verwerking
   - Verifieer of notificaties correct worden verzonden
   - Controleer of de juiste uitgangen worden geactiveerd

## Contributors
- **Kobe**
- **Emiel**
