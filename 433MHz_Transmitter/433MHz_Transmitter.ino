// Pin Out:
// Arduino to 433MHz Receiver
// 5V -> VCC
// Gnd -> Gnd
// Out -> 12

#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;

void setup()
{
    Serial.begin(9600);

    if (!driver.init())
        Serial.println("init failed");
}

void loop()
{
    const char *msg = "12,13,14,15";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();

    delay(1000);
}
