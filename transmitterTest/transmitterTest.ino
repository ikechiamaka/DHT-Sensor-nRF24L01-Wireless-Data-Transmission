#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8); // CE, CSN pins
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
}

void loop() {
  for (int number = 0; number <= 10; number++) {
    radio.write(&number, sizeof(number));
    Serial.println(number);
    delay(1000); // Send a number every second
  }
}
