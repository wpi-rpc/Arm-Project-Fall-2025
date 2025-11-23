#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"

#include "stepper-module/stepper-module.h"

// SPI Defines
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19

// I2C defines
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9



void SPI_init() {
    spi_init         (SPI_PORT, 1000*1000    );
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS  , GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK , GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
}

void I2C_init() {
    i2c_init         (I2C_PORT, 400*1000     );
    gpio_set_function(I2C_SDA , GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL , GPIO_FUNC_I2C);
    gpio_pull_up     (I2C_SDA                );
    gpio_pull_up     (I2C_SCL                );
}


int main() {
    stdio_init_all();
    SPI_init      ();
    I2C_init      ();
    
    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_set_dir(PIN_CS, true);
    gpio_put(PIN_CS, 1);
}
