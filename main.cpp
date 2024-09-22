#include "VL53L0X.h"
#include "pico/stdlib.h"
#include <stdio.h>

#define I2C_SDA 8
#define I2C_SCL 9

int main()
{

    // Initialize standard I/O over USB
    stdio_init_all();

    // Initialize I2C0 at 400kHz
    i2c_init(i2c0, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Initialize VL53L0X sensor
    VL53L0X sensor;
    sensor.init();
    sensor.setTimeout(500);

    // Start continuous back-to-back mode (take readings as fast as possible)
    sensor.startContinuous();

    // Keep the program running
    while (1)
    {
        uint16_t distance = sensor.readRangeContinuousMillimeters();
        if (sensor.timeoutOccurred())
        {
            printf("Measurement timed out\n");
        }
        else
        {
            printf("Distance: %d mm\n", distance);
        }
        sleep_ms(100); // Adjust as needed
    }
}
