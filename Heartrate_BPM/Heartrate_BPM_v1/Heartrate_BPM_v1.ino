#define MAX_HISTORY 100
#define TOTAL_BEATS 30
int pulse_sensor_pin = 0;

int history[MAX_HISTORY];
float beats[TOTAL_BEATS];
bool beat = false;
float bpm = 0;
bool is_non_zero = false;

void setup()
{
  Serial.begin(9600);
}

float calculate_bpm(float beats[TOTAL_BEATS])
{
  float beat_time = beats[TOTAL_BEATS - 1] - beats[0];
  return (TOTAL_BEATS / beat_time) * 60;
}

void loop()
{
  int v = analogRead(pulse_sensor_pin);
  history[MAX_HISTORY - 1] = v;
  for (int i = 0; i < MAX_HISTORY - 1; i++)
  {
    history[i] = history[i + 1];
  }
  for (int i = 0; i < MAX_HISTORY; i++)
  {
    if (history[i] == 0)
    {
      is_non_zero = false;
      break;
    }
    else
    {
      is_non_zero = true;
    }
  }
  if (is_non_zero)
  {
    int maxima = history[0];
    int minima = history[0];
    for (int i = 0; i < MAX_HISTORY; i++)
    {
      maxima = max(history[i], maxima);
      minima = min(history[i], minima);
    }
    int threshold_on = (minima + maxima * 3) / 4; // 3/4
    int threshold_off = (minima + maxima) / 2;    // 1/2
    if (v > threshold_on && beat == false)
    {
      beat = true;
      beats[TOTAL_BEATS - 1] = millis() / 100;
      for (int i = 0; i < TOTAL_BEATS - 1; i++)
      {
        beats[i] = beats[i + 1];
      }
      bpm = calculate_bpm(beats);
      Serial.println(bpm);
    }
    if (v < threshold_off && beat == true)
    {
      beat = false;
    }
  }
}
