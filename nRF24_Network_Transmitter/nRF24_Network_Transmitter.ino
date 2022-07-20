#include <RF24.h>
#include <RF24Network.h>
#include <SPI.h>

RF24 radio(7, 8);              // nRF24L01 (CE,CSN)
RF24Network network(radio);    // Include the radio in the network
const uint16_t this_node = 01; // Address of this node in Octal format ( 04,031, etc)
const uint16_t node00 = 00;
char to_send[24];

void setup()
{
  Serial.begin(9600);

  SPI.begin();
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  network.begin(90, this_node); //(channel, node address)
}
void loop()
{
  network.update();
  RF24NetworkHeader header(node00); // (Address where the data is going)
  String message = "Hi from node 01";
  message.toCharArray(to_send, 24);

  bool is_sent = network.write(header, &to_send, sizeof(to_send)); // Send the data

  if (is_sent)
  {
    Serial.println(message);
  }
  else
  {
    Serial.println("Message not sent.");
  }

  delay(1000);
}
