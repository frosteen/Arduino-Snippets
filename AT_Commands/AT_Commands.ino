// UART Communication for AT Commands.
// Pinout:
// Arduino to module.
// TX -> RX
// RX -> TX
// Gnd -> Gnd
// Power supply maybe from the same source
// or not depending on the module.

#include <SoftwareSerial.h>

SoftwareSerial AT_Serial(2, 3); // RX_OF_ARDUINO, TX_OF_ARDUINO

void setup()
{
  Serial.begin(9600);
  AT_Serial.begin(9600);

  Serial.println("Begin sending AT Commands.");
}

void loop()
{
  while (Serial.available())
  {
    AT_Serial.write(Serial.read());
  }

  while (AT_Serial.available())
  {
    Serial.write(AT_Serial.read());
  }
}
