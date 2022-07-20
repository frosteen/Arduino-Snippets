#include <EEPROM.h>

String write_EEPROM = "Pambs";
String read_EEProm = "";

void setup()
{
  Serial.begin(9600);

  // Writing in EEPROM Start //

  Serial.println("Writing in EEPROM...");

  for (int i = 0; i < write_EEPROM.length(); i++)
  {
    EEPROM.write(i, write_EEPROM[i]);
  }

  // Writing in EEPROM End //

  // Reading in EEPROM Start //

  Serial.print("Read from EEPROM: ");

  for (int i = 0; i < write_EEPROM.length(); i++)
  {
    byte myByte = EEPROM.read(i);
    read_EEProm += myByte;
  }

  Serial.println(read_EEProm);

  // Reading in EEPROM End //
}

void loop()
{
}
