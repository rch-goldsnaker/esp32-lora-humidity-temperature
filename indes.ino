#include "LoRaWan_APP.h"
#include "DHT.h"
#include <Wire.h>
#include "HT_SSD1306Wire.h"

// Initialize the OLED display with the reference configuration
SSD1306Wire factory_display(0x3C, 500000, SDA_OLED, SCL_OLED, GEOMETRY_128_64, RST_OLED);

// ADC pin definition for the soil moisture sensor
const int adcPin = 3;  // Valid ADC pin on ESP32
const int dhtPin = 5;  // Pin for the DHT11 sensor

// Calibration values for dry and wet soil
const int DRY = 3086;
const int WET = 1212;

// Initialize the DHT11 sensor
#define DHTTYPE DHT11
DHT dht(dhtPin, DHTTYPE);

/* OTAA parameters */
uint8_t devEui[] = { 0x70, 0xB3, 0xD5, 0x7E, 0xD8, 0x00, 0x3E, 0xFB };
uint8_t appEui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t appKey[] = { 0xF6, 0x5D, 0x70, 0x6B, 0xDF, 0x25, 0x45, 0x9E, 0x17, 0x8C, 0x21, 0x98, 0xE3, 0xC2, 0x8D, 0x02 };

/* ABP parameters */
uint8_t nwkSKey[] = { 0x15, 0xB1, 0xD0, 0xEF, 0xA4, 0x63, 0xDF, 0xBE, 0x3D, 0x11, 0x18, 0x1E, 0x1E, 0xC7, 0xDA, 0x85 };
uint8_t appSKey[] = { 0xD7, 0x2C, 0x78, 0x75, 0x8C, 0xDC, 0xCA, 0xBF, 0x55, 0xEE, 0x4A, 0x77, 0x8D, 0x16, 0xEF, 0x67 };
uint32_t devAddr = (uint32_t)0x007e6ae1;

uint16_t userChannelsMask[6] = { 0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };
LoRaMacRegion_t loraWanRegion = ACTIVE_REGION;
DeviceClass_t loraWanClass = CLASS_A;
uint32_t appTxDutyCycle = 15000;
bool overTheAirActivation = true;
bool loraWanAdr = true;
bool isTxConfirmed = true;
uint8_t appPort = 2;
uint8_t confirmedNbTrials = 4;

// Function to read the soil moisture and convert it to a percentage
int getSoilMoisture() {
  int sensorVal = analogRead(adcPin);
  int percentage = map(sensorVal, WET, DRY, 100, 0);
  return constrain(percentage, 0, 100);
}

float getTemperature() {
  return dht.readTemperature();
}

float getHumidity() {
  return dht.readHumidity();
}

// Function that prepares the packet to send and updates the OLED display with sensor values
static void prepareTxFrame(uint8_t port) {
  int soilMoisture = getSoilMoisture();
  float temperature = getTemperature();
  float airHumidity = getHumidity();
  
  // Convert air humidity to an integer to remove decimals
  int airHumidityInt = (int)airHumidity;
  
  uint8_t soilMoistureHex = (uint8_t)soilMoisture;
  uint8_t temperatureHex = (uint8_t)temperature;
  uint8_t airHumidityHex = (uint8_t)airHumidityInt;  // Using integer value for air humidity

  appDataSize = 3;
  appData[0] = soilMoistureHex;
  appData[1] = temperatureHex;
  appData[2] = airHumidityHex;

  // Print sensor values to the serial monitor
  Serial.printf("Soil Moisture: %d%%, Hex: 0x%X\n", soilMoisture, appData[0]);
  Serial.printf("Temperature: %.1f°C, Hex: 0x%X\n", temperature, appData[1]);
  Serial.printf("Air Humidity: %d%%, Hex: 0x%X\n", airHumidityInt, appData[2]);

  // Update the OLED display with sensor values
  factory_display.clear();
  factory_display.setFont(ArialMT_Plain_16);
  factory_display.drawString(0, 0, "Soil Moisture: " + String(soilMoisture) + "%");
  factory_display.drawString(0, 20, "Temp: " + String(temperature, 1) + " C");
  factory_display.drawString(0, 40, "Air Humidity: " + String(airHumidityInt) + "%");
  factory_display.display();
}

// Function to activate the OLED power supply
void VextON() {
  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, LOW);  // Activate power supply
}

void setup() {
  Serial.begin(115200);
  VextON();  // Turn on the OLED display power
  delay(100);

  // Initialize the OLED display
  factory_display.init();
  factory_display.clear();
  factory_display.setFont(ArialMT_Plain_16);
  factory_display.drawString(10, 25, "Initializing...");
  factory_display.display();

  pinMode(adcPin, INPUT);
  dht.begin();
  Mcu.begin();
  deviceState = DEVICE_STATE_INIT;
}

void loop() {
  switch (deviceState) {
    case DEVICE_STATE_INIT:
      LoRaWAN.init(loraWanClass, loraWanRegion);
      break;
    case DEVICE_STATE_JOIN:
      LoRaWAN.join();
      break;
    case DEVICE_STATE_SEND:
      prepareTxFrame(appPort);  // Read sensors, update OLED, and prepare the LoRaWAN packet
      LoRaWAN.send();
      deviceState = DEVICE_STATE_CYCLE;
      break;
    case DEVICE_STATE_CYCLE:
      txDutyCycleTime = appTxDutyCycle + randr(-APP_TX_DUTYCYCLE_RND, APP_TX_DUTYCYCLE_RND);
      LoRaWAN.cycle(txDutyCycleTime);
      deviceState = DEVICE_STATE_SLEEP;
      break;
    case DEVICE_STATE_SLEEP:
      LoRaWAN.sleep(loraWanClass);
      break;
    default:
      deviceState = DEVICE_STATE_INIT;
      break;
  }
}
