#include <SoftwareSerial.h>

SoftwareSerial SIM800x(3, 2);
String received_text;
String phone_number = "+639171709038";

void setup()
{
  Serial.begin(9600);
  init_SIM800x();
  send_sms("Testing");
}

void loop()
{
  receive_sms();
  //send_sms("Testing");

  delay(1000);
}

void init_SIM800x()
{
  SIM800x.begin(9600);

  while (!SIM800x.available())
  {
    SIM800x.println("AT");
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.println("Connected!");
  SIM800x.println("AT+CMGF=1");
  update_serial_monitor();

  SIM800x.println("AT + CMGS = \"" + phone_number + "\"");
  update_serial_monitor();

  SIM800x.print("GSM initialized.");
  update_serial_monitor();

  SIM800x.write((char)26);
  update_serial_monitor();

  // Receive mode.
  SIM800x.print("AT+CNMI=1,2,0,0,0\r");
  delay(1000);
}

void send_sms(String message)
{
  SIM800x.println("AT+CMGF=1");
  update_serial_monitor();

  SIM800x.println("AT + CMGS = \"" + phone_number + "\"");
  update_serial_monitor();

  SIM800x.print(message);
  update_serial_monitor();

  SIM800x.write((char)26);
  update_serial_monitor();

  // Receive mode.
  SIM800x.print("AT+CNMI=1,2,0,0,0\r");
  update_serial_monitor();
}

void receive_sms()
{
  if (SIM800x.available() > 0)
  {
    //Get the character from the cellular serial port
    received_text = SIM800x.readString();

    Serial.println("Received Text: ");
    Serial.println(received_text);

    received_text = "";
  }
}

void update_serial_monitor()
{
  delay(500);

  while (Serial.available())
  {
    SIM800x.write(Serial.read()); //Forward what Serial received to Software Serial Port
  }
  while (SIM800x.available())
  {
    Serial.write(SIM800x.read()); //Forward what Software Serial received to Serial Port
  }
}
