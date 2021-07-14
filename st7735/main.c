/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "st7735.h"
const uint LED_PIN = PICO_DEFAULT_LED_PIN;

int main() {
    lcdst_t *myDisplay = NULL;

	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);

	gpio_put(LED_PIN, 0);
    /* Initialize the display and receive pointer */
	myDisplay = lcdst_init( 4000 * 1000, 17, 26, 22, 128, 128);
   
   /* Fill the display */
	lcdst_drawScreen(0, 0, 255);
	sleep_ms(100);

/*

	lcdst_drawHLine(0, 149, 128, 0, 255, 255);
	lcdst_drawHLine(0, 139, 128, 255, 255, 0);
	lcdst_drawVLine(117, 0, 160, 0, 255, 255);
	lcdst_drawVLine(107, 0, 160, 255, 255, 0);
	
	lcdst_drawRect(10, 10, 10, 10, 0, 255, 255);
	lcdst_drawRect(10, 30, 10, 10, 255, 255, 0);
	lcdst_drawFRect(30, 10, 10, 10, 0, 255, 255);
	lcdst_drawFRect(30, 30, 10, 10, 255, 255, 0);
*/

	//lcdst_drawFRect(1, 0, 128, 128, 255, 255, 0);

	lcdst_drawHLine(0, 0, 128, 255, 0, 0);
	lcdst_drawHLine(0, 127, 128, 255, 0, 0);
	lcdst_drawVLine(0, 0, 128, 255, 0, 0);
	lcdst_drawVLine(127, 0, 128, 255, 0, 0);

	binkLED(2);


}
