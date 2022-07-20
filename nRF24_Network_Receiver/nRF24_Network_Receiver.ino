#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>
#include <Wire.h>
#include <SoftwareSerial.h>

RF24 radio(7, 8);              // nRF24L01 (CE,CSN)
RF24Network network(radio);    // Include the radio in the network
const uint16_t this_node = 00; // Address of our node in Octal format ( 04,031, etc)

const int max_char = 24;
char to_receive[max_char];
int receive_counter = 0;

void setup()
{
  Serial.begin(9600);

  SPI.begin();
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  network.begin(90, this_node); //(channel, node address)
}

void loop()
{

  network.update();

  // Is there any incoming data?
  while (network.available())
  {
    RF24NetworkHeader header;
    network.read(header, &to_receive, sizeof(to_receive)); // Read the incoming data

    String data_in = String(to_receive);

    Serial.println(data_in);
  }

  delay(1000);
}
