#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <DHT.h>

// Setup for the DHT11 sensor:
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22 // DHT 11
DHT dht(DHTPIN, DHTTYPE);

// Setup for the nRF24L01:
RF24 radio(9, 8); // CE, CSN pins
const byte address[6] = "00001";

struct SensorData {
  float humidity;
  float temp_c;
  float temp_f;
  float temp_k;
} sensorData;

void setup() {
  Serial.begin(9600);
  dht.begin();
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
}

void loop() {
  // Reading humidity and temperature
  sensorData.humidity = dht.readHumidity();
  sensorData.temp_c = dht.readTemperature(); // Celsius
  sensorData.temp_f = dht.readTemperature(true); // Fahrenheit
  sensorData.temp_k = sensorData.temp_c + 273.15; // Kelvin
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(sensorData.humidity) || isnan(sensorData.temp_c) || isnan(sensorData.temp_f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  // Print the values to the Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(sensorData.humidity);
  Serial.print("%  Temperature: ");
  Serial.print(sensorData.temp_c);
  Serial.print("°C ");
  Serial.print(sensorData.temp_f);
  Serial.print("°F ");
  Serial.print(sensorData.temp_k);
  Serial.println("°K ");

  // Send the data
  radio.write(&sensorData, sizeof(sensorData));
  
  // Delay between measurements
  delay(2000);
}
