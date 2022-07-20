int pulse_sensor_pin = A0;
int builtin_led = 13;

int signal;
int threshold = 358;

void setup()
{
  pinMode(builtin_led, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  signal = analogRead(pulse_sensor_pin);

  Serial.println(signal);

  if (signal > threshold)
  {
    digitalWrite(builtin_led, HIGH);
  }
  else
  {
    digitalWrite(builtin_led, LOW);
  }

  delay(20);
}
