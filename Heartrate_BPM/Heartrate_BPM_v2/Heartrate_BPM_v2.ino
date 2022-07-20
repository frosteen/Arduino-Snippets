#define MAX_HISTORY 300
int pulse_sensor_pin = A0;

int history[MAX_HISTORY];
bool is_non_zero = false;
int last_time = 0;
bool bpm_timing = false;
bool beat_complete = false;
int bpm = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int Signal = analogRead(pulse_sensor_pin);
  history[MAX_HISTORY - 1] = Signal;
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
    if (Signal > threshold_on)
    {
      if (beat_complete)
      {
        bpm = millis() - last_time;
        bpm = int(60 / (float(bpm) / 1000));
        bpm_timing = false;
        beat_complete = false;
      }
      if (bpm_timing == false)
      {
        last_time = millis();
        bpm_timing = true;
      }
    }
    if ((Signal < threshold_off) & (bpm_timing))
      beat_complete = true;
  }
  Serial.println(bpm);
}
