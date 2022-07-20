// Device Details
#define BLYNK_TEMPLATE_ID "TMPLpQvLWDf_"
#define BLYNK_DEVICE_NAME "Design Misting"
#define BLYNK_AUTH_TOKEN "38_nnjkDxoAsPEVSyIkVBa096y_YFu7y"

// Libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "PAMBID_WIFI_2.4GHz";
char pass[] = "PAMBID142528!";

// ESP8266 PINS
#define in1 D5
#define in2 D6
#define in3 D7
#define in4 D8

// JoystickX and JoystickY: Positions
int X = 0;
int Y = 0;

// JoystickX and JoystickY: min and max
int min_range = 0;
int max_range = 100;

// Functions
void move_control(int X, int Y)
{
  int median = (max_range + min_range) / 2;
  int lower = median - median / 1.5;
  int upper = median + median / 1.5;

  // Move Forward
  if (X > lower && X < upper && Y >= upper && Y <= max_range)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }

  // Move Right
  if (Y > lower && Y < upper && X >= upper && X <= max_range)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }

  // Move Backward
  if (X > lower && X < upper && Y >= min_range && Y <= lower)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }

  // Move Left
  if (Y > lower && Y < upper && X >= min_range && X <= lower)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }

  // Stop
  if (X == median && Y == median)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}
void setup()
{
  // Set as OUTPUT
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop()
{
  Blynk.run();
}

// JoystickX
BLYNK_WRITE(V0)
{
  X = param.asInt();
  move_control(X, Y);
}

// JoystickY
BLYNK_WRITE(V1)
{
  Y = param.asInt();
  move_control(X, Y);
}

BLYNK_CONNECTED()
{
  Blynk.syncAll();
}
