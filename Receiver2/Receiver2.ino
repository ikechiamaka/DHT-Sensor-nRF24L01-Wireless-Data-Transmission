#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal.h>

// Setup for the nRF24L01:
RF24 radio(9, 8); // CE, CSN pins
const byte address[6] = "00001";

// Setup for the standard LCD:
// the LCD's interface pins (rs, en, d4, d5, d6, d7)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

struct SensorData {
  float humidity;
  float temp_c;
  float temp_f;
  float temp_k;
} sensorData;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();

  // Initialize the standard LCD
  lcd.begin(20, 4);
}

void loop() {
  if (radio.available()) {
    // Read the data
    radio.read(&sensorData, sizeof(sensorData));

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
    
    // Write the data to the standard LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Humidity: ");
    lcd.print(sensorData.humidity, 1);
    lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print("Temp in Cel: ");
    lcd.print(sensorData.temp_c, 1);
    lcd.print("C");
    lcd.setCursor(0, 2);
    lcd.print("Temp in F: ");
    lcd.print(sensorData.temp_f, 1);
    lcd.print("F");
    lcd.setCursor(0, 3);
    lcd.print("Temp in K: ");
    lcd.print(sensorData.temp_k, 1);
    lcd.print("K");
  }
}
