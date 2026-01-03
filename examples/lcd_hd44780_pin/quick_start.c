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
 * \file		quick_start.c
 *
 * ---------------------------------------------------------------------------+
 * \brief		LCD HD44780 quick start example
 *
 * \details     Scheme path:	examples/schemes/base.png
								examples/schemes/base.kicad_sch
				Compiler options required for successful build:
								-include "quick_start_def.h"
								-DF_CPU=16000000UL
 * --------------------------------------------------------------------------+
 */

#include <sls-avr/lcd_hd44780_pin.h>
#include <util/delay.h>

int main(void) {
	lcd_init_t config = {
		.flags = HD44780_INIT_DISP_ON | HD44780_INIT_FONT_NORMAL | HD44780_INIT_CURSOR_OFF | HD44780_INIT_BLINKING_OFF | HD44780_INIT_SHIFT_OFF | HD44780_INIT_MOV_DIR_INC,
	};
	lcd_init(&config);
	lcd_print("Initialization...");
	_delay_ms(1500);
	lcd_line("Quick start example:", LCD_ROW_1, 0);
	lcd_line("line 2", LCD_ROW_2, 4);
	lcd_line("line 3", LCD_ROW_3, 4);
	lcd_line("It's OK!", LCD_ROW_4, 10);
    while(1) {

    }

    return 0;
}
