#include "HX711.h"

#define DOUT 24
#define DCLK 6

HX711 scale;

float calibration_factor = -28.5; // this calibration factor is adjusted according to my load cell
float units = 0;

void setup() {
  Serial.begin(9600);
  scale.begin(DOUT, DCLK);
  scale.set_scale(calibration_factor);
  scale.tare();
}

void loop() {
  Serial.print("Reading: ");
  units = scale.get_units(), 10;
  if (units < 0)
  {
    units = 0.00;
  }
  Serial.print(units);
  Serial.print(" grams");
  Serial.println();
}
