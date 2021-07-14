#include <stdint.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"
const int LOW = 0;
const int HIGH = 1;
const int OUTPUT = 1;

#ifdef PICO_DEFAULT_SPI_CSN_PIN

void binkLED(int times) {
    for (int i = 0; i < times; i++) {
        gpio_put(PICO_DEFAULT_LED_PIN, 0);  
        sleep_ms(1000);
	    gpio_put(PICO_DEFAULT_LED_PIN, 1);  
        sleep_ms(1000);
    }
    
}
static inline void cs_select() {
    asm volatile("nop \n nop \n nop");
    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 0); 
    asm volatile("nop \n nop \n nop");
}

static inline void cs_deselect() {
    asm volatile("nop \n nop \n nop");
    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);
    asm volatile("nop \n nop \n nop");
}
#endif

void delay(unsigned int milliseconds) {
    sleep_ms(milliseconds);
};
void pinMode(int pin, int mode) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
};
void digitalWrite(int pin, int value) {
    gpio_put(pin, value);
};
int  spiSetup(int channel, int speed) {
    spi_init(spi_default, speed);
    gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
    // Make the SPI pins available to picotool
    bi_decl(bi_3pins_with_func(PICO_DEFAULT_SPI_RX_PIN, PICO_DEFAULT_SPI_TX_PIN, PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI));

    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_init(PICO_DEFAULT_SPI_CSN_PIN);
    gpio_set_dir(PICO_DEFAULT_SPI_CSN_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);
    // Make the CS pin available to picotool
    bi_decl(bi_1pin_with_name(PICO_DEFAULT_SPI_CSN_PIN, "SPI CS"));
    return 0;
};
int  spiDataRW(int channel, uint8 *data, int length) {
    cs_select();
    spi_write_blocking(spi_default, data, length);
    cs_deselect();
    return 0;
};