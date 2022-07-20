#include <SoftwareSerial.h>

#define PIN_TX_OF_SIM808 2
#define PIN_RX_OF_SIM808 3
String phone_number = "+639476207065";
SoftwareSerial sim808(PIN_TX_OF_SIM808, PIN_RX_OF_SIM808);

void send_command(SoftwareSerial serial, String command)
{
  serial.println(command);
  delay(100);
  while (serial.available())
    serial.read();
}

void send_command(SoftwareSerial serial, char command)
{
  serial.println(command);
  delay(100);
  while (serial.available())
    serial.read();
}

void init_sim808()
{
  while (!sim808.available())
  {
    sim808.println("AT");
    delay(1000);
    Serial.println("Connecting SIM808...");
  }
  Serial.println("Connected SIM808!");

  while (!sim808.available())
  {
    sim808.println("AT+CMGF=1");
    delay(1000);
    Serial.println("Checking GSM...");
  }
  Serial.println("Successful GSM!");

  while (!sim808.available())
  {
    sim808.println("AT+CGNSPWR=1");
    delay(1000);
    Serial.println("Checking GPS...");
  }
  Serial.println("Successful GPS!");

  while (!sim808.available())
  {
    sim808.println("AT+CGNSSEQ=RMC");
    delay(1000);
    Serial.println("Checking GPS_RMC...");
  }
  Serial.println("Successful GPS_RMC!");
}

void send_sms(String message)
{
  send_command(sim808, "AT+CMGF=1");
  send_command(sim808, "AT+CMGS=\"" + phone_number + "\"");
  send_command(sim808, message);
  send_command(sim808, (char)26);
}

String *get_gps()
{
  // data[2] - timestamp
  // data[3] - latitude
  // data[4] - longitude
  // data[5] - altitude
  const int data_size = 6;
  static String data[data_size];
  int i = 0;

  for (int i = 0; i < data_size; i++)
    data[i] = "";

  send_command(sim808, "AT+CGNSPWR=1");

  send_command(sim808, "AT+CGNSSEQ=RMC");

  sim808.println("AT+CGNSINF");
  delay(100);
  while (sim808.available() && i < data_size)
  {
    char c = sim808.read();
    if (c != ',')
      data[i] += c;
    else
      i++;
  }
  return data;
}

void setup()
{
  sim808.begin(9600);
  Serial.begin(9600);
  init_sim808();
}

void loop()
{
  String *data = get_gps();
  String get_data = *(data + 1);
  if (get_data != "")
  {
    String timestamp = *(data + 2);
    String latitude = *(data + 3);
    String longitude = *(data + 4);
    String altitude = *(data + 4);
    Serial.println(timestamp);
    Serial.println(latitude);
    Serial.println(longitude);
    Serial.println(altitude);
  }
}
