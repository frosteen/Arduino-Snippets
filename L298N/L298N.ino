const int en_A = 9;
const int in1 = 3;
const int in2 = 4;

const int en_B = 10;
const int in3 = 6;
const int in4 = 7;

const int pwm_motor_speed = 70;

// One set of motor will rotate if its enable pins
// are different, one is high and the other is low.
// To reverse it, just invert the high and low.

// The enable pin of each set is shorted to
// 5V, it will run at max speed. If you want
// to control the speed, remove the short
// and connect the enable pin to a PWM pin.

void setup()
{
  Serial.begin(9600);

  pinMode(en_A, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(en_B, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  analogWrite(en_A, pwm_motor_speed);
  analogWrite(en_B, pwm_motor_speed);
}

void loop()
{
  forward();
  delay(3000);
  backward();
  delay(3000);
  left();
  delay(3000);
  right();
  delay(3000);
}

void stop_motor()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void forward()
{
  // Tested using two motors of robot car.
  // Motor of left and right robot are inverted so direction of forward of other motor is inverted as well.
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void backward()
{
  // Tested using two motors of robot car.
  // Motor of left and right robot are inverted so direction of backward of other motor is inverted as well.
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void left()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void right()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
