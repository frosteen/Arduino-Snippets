#include <Wire.h>

long accel_x, accel_y, accel_z;
float g_force_x, g_force_y, g_force_z;

long gyro_x, gyro_y, gyro_z;
float rot_x, rot_y, rot_z;

void setup()
{
  Serial.begin(9600);
  Serial.println("Test");
  Wire.begin();
  setup_mpu();
}

void loop()
{

  record_accel_registers();
  record_gyro_registers();
  print_data();
  delay(1000);
}

void setup_mpu()
{
  Wire.beginTransmission(0b1101001); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B);                  //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000);            //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1B);                  //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4)
  Wire.write(0x00000000);            //Setting the gyro to full scale +/- 250deg./s
  Wire.endTransmission();
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1C);                  //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5)
  Wire.write(0b00000000);            //Setting the accel to +/- 2g
  Wire.endTransmission();
}

void record_accel_registers()
{
  Wire.beginTransmission(0b1101001); //I2C address of the MPU
  Wire.write(0x3B);                  //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6); //Request Accel Registers (3B - 40)
  while (Wire.available() < 6)
    ;
  accel_x = Wire.read() << 8 | Wire.read(); //Store first two bytes into accelX
  accel_y = Wire.read() << 8 | Wire.read(); //Store middle two bytes into accelY
  accel_z = Wire.read() << 8 | Wire.read(); //Store last two bytes into accelZ
  process_accel_data();
}

void process_accel_data()
{
  g_force_x = accel_x / 16384.0;
  g_force_y = accel_y / 16384.0;
  g_force_z = accel_z / 16384.0;
}

void record_gyro_registers()
{
  Wire.beginTransmission(0b1101001); //I2C address of the MPU
  Wire.write(0x43);                  //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6); //Request Gyro Registers (43 - 48)
  while (Wire.available() < 6)
    ;
  gyro_x = Wire.read() << 8 | Wire.read(); //Store first two bytes into accelX
  gyro_y = Wire.read() << 8 | Wire.read(); //Store middle two bytes into accelY
  gyro_z = Wire.read() << 8 | Wire.read(); //Store last two bytes into accelZ
  process_gyro_data();
}

void process_gyro_data()
{
  rot_x = gyro_x / 131.0;
  rot_y = gyro_y / 131.0;
  rot_z = gyro_z / 131.0;
}

void print_data()
{
  Serial.print("Gyro (deg)");
  Serial.print(" X=");
  Serial.print(rot_x);
  Serial.print(" Y=");
  Serial.print(rot_y);
  Serial.print(" Z=");
  Serial.print(rot_z);
  Serial.print(" Accel (g)");
  Serial.print(" X=");
  Serial.print(g_force_x);
  Serial.print(" Y=");
  Serial.print(g_force_y);
  Serial.print(" Z=");
  Serial.println(g_force_z);
}
