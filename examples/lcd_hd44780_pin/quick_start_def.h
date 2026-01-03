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
 * \file		quick_start_def.h
 *
 * ---------------------------------------------------------------------------+
 * \brief		Example global definitions
 * --------------------------------------------------------------------------+
 */
#ifndef QUICK_START_DEF_H_INCLUDED
#define QUICK_START_DEF_H_INCLUDED

#include "quick_start_pins.h"

#define LCD_HD44780_PIN_DISPLAY_TYPE		HD44780_DISPLAY_20X4
#define LCD_HD44780_PIN_DATA_PORT			LCD_DATA_PORT
#define LCD_HD44780_PIN_DATA_FIRST_PIN		LCD_DATA_1_PIN
#define LCD_HD44780_PIN_RS_PORT				LCD_RS_PORT
#define LCD_HD44780_PIN_RS_PIN				LCD_RS_PIN
#define LCD_HD44780_PIN_E_PORT				LCD_E_PORT
#define LCD_HD44780_PIN_E_PIN				LCD_E_PIN
#define LCD_HD44780_PIN_RW_PORT				LCD_RW_PORT
#define LCD_HD44780_PIN_RW_PIN				LCD_RW_PIN

#endif // QUICK_START_DEF_H_INCLUDED
