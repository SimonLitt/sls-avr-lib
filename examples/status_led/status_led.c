// ---------------------------------------------------------------------------+
//				  Public Domain License
// ---------------------------------------------------------------------------+
// This is free and unencumbered software released into the public domain.
// Anyone is free to copy, modify, publish, use, compile, sell, or distribute
// this software, either in source code form or as a compiled binary, for any
// purpose, commercial or non-commercial, and by any means.
// In jurisdictions that recognize copyright laws, the author or authors of
// this software dedicate any and all copyright interest in the software to the
// public domain. We make this dedication for the benefit of the public at
// large and to the detriment of our heirs and successors. We intend this
// dedication to be an overt act of relinquishment in perpetuity of all present
// and future rights to this software under copyright law.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// ---------------------------------------------------------------------------+
/**
 * ---------------------------------------------------------------------------+
 *					This file is part of SLS AVR Tools Examples
 *			https://github.com/SimonLitt/sls-avr-lib/tree/main/examples
 * ---------------------------------------------------------------------------+
 *
 * \copyright	Public Domain
 * \author		Simon Litt <simon@1itt.net> https://coding.1itt.net,
 *              							https://github.com/SimonLitt
 * \file		status_led.c
 *
 * ---------------------------------------------------------------------------+
 * \brief		LCD HD44780 quick start example
 *
 * \details     Scheme path:	examples/schemes/base.png
								examples/schemes/base.kicad_sch
				Compiler options required for successful build:
								-include "status_led_def.h"
								or directly (-include "status_led_pins.h")
								-DF_CPU=16000000UL
				Search directories:
								../../include
				Additional compile for link files:
								../../src/sls-avr/status_led.c
 * --------------------------------------------------------------------------+
 */

#include <avr/io.h>
#include <sls-avr/status_led.h>
#include <util/delay.h>

int main(void) {
	init_status_led();
    _delay_ms(500); // Simulation initialization
    status_led_ready();

    uint8_t t = 0;
    uint16_t e = 0;
    while(1) {
		_delay_ms(4);

		if (e == 1023) { // Simulating a error
			e = t = 0;
			led_stat_off();
			led_err_on();
		}

		if (t == 0xFF) { // Simulating a timer
			led_err_off(); // Clear error
			led_stat_switch(); // blinking
		}
		++t;
		++e;
    }

    return 0;
}
