#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

#define serial_GPS_RX 8
#define serial_GPS_TX 9
#define GPS_BAUD 9600

TinyGPSPlus gps;
SoftwareSerial serial_GPS(serial_GPS_RX, serial_GPS_TX);

void display_GPS()
{
  Serial.print(F("Location: "));
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F("N"));
    Serial.print(gps.location.lng(), 6);
    Serial.print(F("E"));
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  Serial.println();
}

void setup()
{
  Serial.begin(9600);
  serial_GPS.begin(GPS_BAUD);
}

void loop()
{
  while (serial_GPS.available() > 0)
    if (gps.encode(serial_GPS.read()))
      display_GPS();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while (true)
      ;
  }
}
