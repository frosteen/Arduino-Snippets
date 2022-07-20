#include <SoftwareSerial.h>
#include <NMEAGPS.h>

#define serial_GPS_RX 8
#define serial_GPS_TX 9

SoftwareSerial serial_GPS(serial_GPS_RX, serial_GPS_TX);
NMEAGPS  nmea_gps;
gps_fix  fix;

void setup() {
  Serial.begin(9600);
  serial_GPS.begin(9600);
}

void loop() {
  while (nmea_gps.available(serial_GPS)) {
    fix = nmea_gps.read();

    Serial.print( F("Location: ") );
    if (fix.valid.location) {
      Serial.print( fix.latitude(), 6 );
      Serial.print( ',' );
      Serial.print( fix.longitude(), 6 );
    }

    Serial.print( F(", Altitude: ") );
    if (fix.valid.altitude)
      Serial.print( fix.altitude() );

    Serial.println();
  }
}
