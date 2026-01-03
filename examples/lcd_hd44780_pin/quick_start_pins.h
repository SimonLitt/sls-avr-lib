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
 * \file		quick_start_pins.h
 *
 * ---------------------------------------------------------------------------+
 * \brief		AVR port definition
 * --------------------------------------------------------------------------+
 */
#ifndef PINS_H_INCLUDED
#define PINS_H_INCLUDED

/*		Port B */
#define LCD_RS_PORT			B
#define LCD_RW_PORT			B

//#define __PB0_PURPOSE		PB0
//#define __PB1_PURPOSE		PB1
#define LCD_RS_PIN			PB2
#define LCD_RW_PIN			PB3
//#define __PB4_PURPOSE		PB4
//#define __PB5_PURPOSE		PB5
//#define __PB6_PURPOSE		PB6
//#define __PB7_PURPOSE		PB7

/*		Port C */
#define LCD_E_PORT			C

#define LCD_E_PIN			PC0
//#define __PC1_PURPOSE		PC1
//#define __PC2_PURPOSE		PC2
//#define __PC3_PURPOSE		PC3
//#define __PC4_PURPOSE		PC4
//#define __PC5_PURPOSE		PC5
//#define __PC6_PURPOSE		PC6

/*		Port D */
#define LCD_DATA_PORT		D

//#define __PD0_PURPOSE		PD0
//#define __PD1_PURPOSE		PD1
//#define __PD2_PURPOSE		PD2
#define LCD_DATA_1_PIN		PD3
#define __LCD_DATA_5		PD4
#define __LCD_DATA_6		PD5
#define __LCD_DATA_7		PD6
//#define __PD7_PURPOSE		PD7

#endif // PINS_H_INCLUDED
