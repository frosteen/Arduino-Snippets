#include "mbed.h"

I2C i2c(I2C_SDA, I2C_SCL);
const int addr = 0xA0;

int main()
{
    char heart_rate;
    while (1)
    {
        i2c.read(addr, &heart_rate, 1);
        printf("heart rate: = %d\r\n", heart_rate);
    }
}