///
/// Example code for interfacing with the BH1750 light sensor.
///
/// Created by Michael Hogue.
///

#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "bh1750_light_sensor.h"

#define I2C_INSTANCE i2c0
#define I2C_SCL_PIN 17
#define I2C_SDA_PIN 16

int main() {
    stdio_init_all();

    i2c_init(I2C_INSTANCE, 100000);
    
    // Setup I2C bus
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SCL_PIN);
    gpio_pull_up(I2C_SDA_PIN);

    // Power on device
    bh1750_power_on(I2C_INSTANCE);

    // Continuously read ambient light
    while(1) {
        uint16_t lux = bh1750_read_measurement(I2C_INSTANCE);

        printf("Ambient light: %d lux\n");

        sleep_ms(500);
    }

    return 0;
}