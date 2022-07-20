const byte led_pin = 13;
const byte interrupt_pin = 2;
volatile byte state = LOW;

void setup()
{
  pinMode(led_pin, OUTPUT);
  pinMode(interrupt_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin), blink, CHANGE);
}

void loop()
{
  digitalWrite(led_pin, state);
}

void blink()
{
  state = !state;
}