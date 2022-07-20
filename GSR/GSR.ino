const int GSR = A1;
int gsr_average = 0;
long human_resistance = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  unsigned long sum = 0;

  for (int i = 0; i < 500; i++) //Average the 10 measurements to remove the glitch
  {
    int sensor_value = analogRead(GSR);
    sum += sensor_value;
    delay(5);
  }

  gsr_average = sum / 500;

  Serial.println("GSR Average: " + String(gsr_average));

  human_resistance = ((1024 + 2 * gsr_average) * 10000) / (512 - gsr_average);

  Serial.println("Human Resistance: " + String(human_resistance));
}
