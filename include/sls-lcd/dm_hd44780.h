// ---------------------------------------------------------------------------+
//					This file is part of SLS LCD Library
// ---------------------------------------------------------------------------+
// Copyright (C) 2025 Simon Litt <simon@1itt.net> https://coding.1itt.net,
// 												  https://github.com/SimonLitt
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, version 3.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along
// with this program. If not, see <https://www.gnu.org/licenses/>.
// ---------------------------------------------------------------------------+
/**
 * \author		Simon Litt <simon@1itt.net> https://coding.1itt.net,
 *              							https://github.com/SimonLitt
 * \copyright	GNU General Public License v3.0
 * \file		sls-lcd/dm_hd44780.h
 * \brief		The HD44780 compatible dot-matrix liquid crystal display lib.
 *
 * \code #include <sls-lcd/dm_hd44780.h>\endcode
 */
#ifndef SLS_LCD_DM_HD44780_H_
#define SLS_LCD_DM_HD44780_H_

#ifdef SLS_AVR_AVR_H_
#	if !(defined SLS_AVR_LCD_HD44780_PIN_H_)
# 		error "Include <sls-avr/lcd_hd44780_pin.h> instead of this file!"
		//TODO i2c support "Include <sls-avr/lcd_hd44780_pin.h> or <sls-avr/lcd_hd44780_i2c.h> instead of this file!"
#	endif
#else
#  error "First, enable the target microcontroller header!"
#endif

// ---------------------------------------------------------------------------+
// Delays. Default from HD44780 and analogs datasheets. Universal settings.
// ---------------------------------------------------------------------------+

#ifndef HD44780_WAIT_INIT_MS
/** \remark This and other and other customizable options can be defined in compiler symbol setup with -D option (preferred) or via global or PCH header using -include option. E.g. -DHD44780_WAIT_INIT_MS=20 or -include "config.h" */
#	define HD44780_WAIT_INIT_MS			18 /**< \brief Waiting before initialization, ms. */
#endif

#ifndef HD44780_EXEC_TIME_US
#	define HD44780_EXEC_TIME_US			50 /**< \brief Waiting after command, us. */
#endif

#ifndef HD44780_LONG_EXEC_TIME_US
#	define HD44780_LONG_EXEC_TIME_US	1760 /**< \brief Waiting after long command, us. */
#endif

#ifndef HD44780_ENABLE_PULSE_US			// 1.5/250000 = 0.6 us
#	define HD44780_ENABLE_PULSE_US		0.8 /**< \brief Duration of E(enable) pulsation, us. */
#endif

#ifndef HD44780_WAIT_BF_LOOP_US
#	define HD44780_WAIT_BF_LOOP_US		0 /**< \brief Additional waiting in wait BF loop, us. 0 - waint only 2 x #HD44780_ENABLE_PULSE_US for 8-bit IDL and 4 x #HD44780_ENABLE_PULSE_US for 4-bit IDL */
#endif

#ifndef HD44780_INIT_1_MS
#	define HD44780_INIT_1_MS 			5 /**< \brief Waiting after first initialization command, ms. */
#endif

#ifndef HD44780_INIT_2_US
#	define HD44780_INIT_2_US			120 /**< \brief Waiting after second initialization command, us. */
#endif

#ifndef HD44780_INIT_3_US
#	define HD44780_INIT_3_US			50 /**< \brief Waiting after third initialization command, us. */
#endif

#ifndef HD44780_INIT_4_4_US
#	define HD44780_INIT_4_4_US			50 /**< \brief Waiting after the fourth initialization command for a 4-bit interface, us. */
#endif

#ifndef HD44780_INIT_OTHER_ADD_US
#	define HD44780_INIT_OTHER_ADD_US	10 /**< \brief Waiting after other initialization command, us. */
#endif

// ---------------------------------------------------------------------------+
// Init commands
// ---------------------------------------------------------------------------+
/** \cond NO_DOC */
#define _HD44780_INIT_8_1_CMD			0b00110000
#define _HD44780_INIT_8_2_CMD			0b00110000
#define _HD44780_INIT_8_3_CMD			0b00110000

#define _HD44780_INIT_4_1_CMD			0b00000011
#define _HD44780_INIT_4_2_CMD			0b00000011
#define _HD44780_INIT_4_3_CMD			0b00000011
#define _HD44780_INIT_4_4_CMD			0b00000010
/** \endcond */

// ---------------------------------------------------------------------------+
// Clear display instruction
// ---------------------------------------------------------------------------+
/** \cond NO_DOC */
#define _HD44780_CLEAR					0b00000001
/** \endcond */

// ---------------------------------------------------------------------------+
// Return home instruction
// ---------------------------------------------------------------------------+
/** \cond NO_DOC */
#define _HD44780_HOME					0b00000010
#define _HD44780_HOME_MASK				0b00000001

#define __HD44780_UNUSED_HOME_0_BIT 	0 // Used by some compatible controllers
#define _HD44780_UNUSED_HOME_0_OFF		0x00
#define _HD44780_UNUSED_HOME_0_ON		(_BV(__HD44780_UNUSED_HOME_0_BIT))
/** \endcond */

// ---------------------------------------------------------------------------+
// Entry mode
// ---------------------------------------------------------------------------+
/** \cond NO_DOC */
#define _HD44780_ENTRY					0b00000100
#define _HD44780_ENTRY_MASK				0b00000011

#define HD44780_S_BIT 					0
#define HD44780_ID_BIT 					1
/** \endcond */

#define HD44780_S_OFF					0x00 /**< \brief Shift disable */
#define HD44780_S_ON					(_BV(HD44780_S_BIT)) /**< \brief Shift enable */

#define HD44780_ID_DEC					0x00 /**< \brief Cursor decrement direction */
#define HD44780_ID_INC					(_BV(HD44780_ID_BIT)) /**< \brief Cursor increment direction */

// ---------------------------------------------------------------------------+
// Display on/off instruction
// ---------------------------------------------------------------------------+
/** \cond NO_DOC */
#define _HD44780_DISPLAY				0b00001000
#define _HD44780_DISPLAY_MASK			0b00000111

#define __HD44780_B_BIT 				0
#define __HD44780_C_BIT 				1
#define __HD44780_D_BIT 				2
/** \endcond */

#define HD44780_B_OFF					0x00 /**< \brief Blinking off */
#define HD44780_B_ON					(_BV(__HD44780_B_BIT)) /**< \brief Blinking on */

#define HD44780_C_OFF					0x00 /**< \brief Cursor off */
#define HD44780_C_ON					(_BV(__HD44780_C_BIT)) /**< \brief Cursor on */

#define HD44780_D_OFF					0x00 /**< \brief Display off */
#define HD44780_D_ON					(_BV(__HD44780_D_BIT)) /**< \brief Display on */

// ---------------------------------------------------------------------------+
// Cursor / shift
// ---------------------------------------------------------------------------+
/** \cond NO_DOC */
#define _HD44780_CURSOR					0b00010000
#define _HD44780_CURSOR_MASK			0b00001111

#define __HD44780_UNUSED_CURSOR_0_BIT 	0 // Used by some compatible controllers
#define __HD44780_UNUSED_CURSOR_1_BIT 	1 // Used by some compatible controllers
#define __HD44780_RL_BIT 				2
#define __HD44780_SCN_BIT 				3

#define _HD44780_UNUSED_CURSOR_0_OFF	0x00
#define _HD44780_UNUSED_CURSOR_0_ON		(_BV(__HD44780_UNUSED_CURSOR_0_BIT))

#define _HD44780_UNUSED_CURSOR_1_OFF	0x00
#define _HD44780_UNUSED_CURSOR_1_ON		(_BV(__HD44780_UNUSED_CURSOR_1_BIT))
/** \endcond */

#define HD44780_RL_LEFT					0x00 /**< \brief Display shift to left */
#define HD44780_RL_RIGHT 				(_BV(__HD44780_RL_BIT)) /**< \brief Display shift to right */

#define HD44780_SCN_CURS	 			0x00 /**< \brief Moves the cursor */
#define HD44780_SCN_DISP 				(_BV(__HD44780_SCN_BIT)) /**< \brief Shifts the display */

// ---------------------------------------------------------------------------+
// Function set instruction
// ---------------------------------------------------------------------------+
/** \cond NO_DOC */
#define _HD44780_FUNC					0b00100000
#define _HD44780_FUNC_MASK				0b00011111

#define __HD44780_UNUSED_FUNC_0_BIT 	0 // Used by some compatible controllers
#define __HD44780_UNUSED_FUNC_1_BIT 	1 // Used by some compatible controllers
#define __HD44780_F_BIT 				2
#define __HD44780_N_BIT 				3
#define __HD44780_DL_BIT 				4

#define _HD44780_UNUSED_FUNC_0_OFF		0x00
#define _HD44780_UNUSED_FUNC_0_ON		(_BV(__HD44780_UNUSED_FUNC_0_BIT))

#define _HD44780_UNUSED_FUNC_1_OFF		0x00
#define _HD44780_UNUSED_FUNC_1_ON		(_BV(__HD44780_UNUSED_FUNC_1_BIT))
/** \endcond */

#define HD44780_F_NORMAL				0x00 /**< \brief font 5x8 */
#define HD44780_F_BIG 					(_BV(__HD44780_F_BIT)) /**< \brief big font */

#define HD44780_N_1L 					0x00 /**< \brief 1 line */
#define HD44780_N_2L 					(_BV(__HD44780_N_BIT)) /**< \brief 2 line */

#define HD44780_DL_4BIT 				0x00 /**< \brief half port */
#define HD44780_DL_8BIT 				(_BV(__HD44780_DL_BIT)) /**< \brief full port */


// ---------------------------------------------------------------------------+
// CGRAM Address Set
// ---------------------------------------------------------------------------+
/** \cond NO_DOC */
#define _HD44780_CGRAM					0b01000000
#define _HD44780_CGRAM_MASK				0b00111111
/** \endcond */

// ---------------------------------------------------------------------------+
// Set DDRAM Address Set
// ---------------------------------------------------------------------------+
/** \cond NO_DOC */
#define _HD44780_DDRAM					0b10000000
#define _HD44780_DDRAM_MASK				0b01111111
/** \endcond */

/** \cond NO_DOC */
#define __HD44780_ROW_1_DDRAM_ADR		0x00
#define __HD44780_ROW_2_DDRAM_ADR		0x40
#define __HD44780_ROW_3_DDRAM_ADR		0x10
#define __HD44780_ROW_4_DDRAM_ADR		0x50

#define __HD44780_ROW_3_20x4_DDRAM_ADR	0x14
#define __HD44780_ROW_4_20x4_DDRAM_ADR	0x54
/** \endcond */
#	ifndef HD44780_ROW_1_DDRAM_ADR
#		define HD44780_ROW_1_DDRAM_ADR __HD44780_ROW_1_DDRAM_ADR /**< \brief Default row 1 DDRAM adress. */
#	endif
#	ifndef HD44780_ROW_2_DDRAM_ADR
#		define HD44780_ROW_2_DDRAM_ADR __HD44780_ROW_2_DDRAM_ADR /**< \brief Default row 2 DDRAM adress. */
#	endif
#	ifndef HD44780_ROW_3_DDRAM_ADR
#		define HD44780_ROW_3_DDRAM_ADR __HD44780_ROW_3_DDRAM_ADR /**< \brief Default row 3 DDRAM adress. */
#	endif
#	ifndef HD44780_ROW_4_DDRAM_ADR
#		define HD44780_ROW_4_DDRAM_ADR __HD44780_ROW_4_DDRAM_ADR /**< \brief Default row 4 DDRAM adress. */
#	endif

#	ifndef HD44780_ROW_3_20x4_DDRAM_ADR
#		define HD44780_ROW_3_20x4_DDRAM_ADR __HD44780_ROW_3_20x4_DDRAM_ADR /**< \brief Row 3 DDRAM adress  for 20x4 display. */
#	endif
#	ifndef HD44780_ROW_4_20x4_DDRAM_ADR
#		define HD44780_ROW_4_20x4_DDRAM_ADR __HD44780_ROW_4_20x4_DDRAM_ADR /**< \brief Row 4 DDRAM adress  for 20x4 display. */
#	endif

// ---------------------------------------------------------------------------+
// Busy Flag / Address Read
// ---------------------------------------------------------------------------+
/** \cond NO_DOC */
#define __HD44780_BF_BIT				7
#define _HD44780_ADDR_MASK				0b01111111

/** \endcond */

// ---------------------------------------------------------------------------+
#define HD44780_CUSTOM_CHAR_0			0 /**< \brief Custom char 0. */
#define HD44780_CUSTOM_CHAR_1			1 /**< \brief Custom char 1. */
#define HD44780_CUSTOM_CHAR_2			2 /**< \brief Custom char 2. */
#define HD44780_CUSTOM_CHAR_3			3 /**< \brief Custom char 3. */
#define HD44780_CUSTOM_CHAR_4			4 /**< \brief Custom char 4. */
#define HD44780_CUSTOM_CHAR_5			5 /**< \brief Custom char 5. */
#define HD44780_CUSTOM_CHAR_6			6 /**< \brief Custom char 6. */
#define HD44780_CUSTOM_CHAR_7			7 /**< \brief Custom char 7. */

// ---------------------------------------------------------------------------+
/** \brief LCD row. */
typedef enum {
	LCD_ROW_1 = 0,	/**< \brief 1-st display row */
	LCD_ROW_2,		/**< \brief 2-nd display row */
	LCD_ROW_3,		/**< \brief 3-rd display row */
	LCD_ROW_4,		/**< \brief 4-th display row */
} lcd_line_t;

#define HD44780_DISPLAY_8X1				1 /**< \brief LCD display 8x1 */
#define HD44780_DISPLAY_16X1			2 /**< \brief LCD display 16x1 */

#define HD44780_DISPLAY_16X2			12 /**< \brief LCD display 16x2 */
#define HD44780_DISPLAY_20X2			13 /**< \brief LCD display 20x2 */
#define HD44780_DISPLAY_32X2			14 /**< \brief LCD display 32x2 */
#define HD44780_DISPLAY_40X2			15 /**< \brief LCD display 40x2 */

#define HD44780_DISPLAY_16X4			22 /**< \brief LCD display 16x4 */
#define HD44780_DISPLAY_20X4			23 /**< \brief LCD display 20x4 */
#define HD44780_DISPLAY_40X4			25 /**< \brief LCD display 40x4 */

/** \brief LCD display type. */
typedef enum {
	LCD_8X1		= HD44780_DISPLAY_8X1,  /**< \brief Resolution 8х1 characters */
	LCD_16X1	= HD44780_DISPLAY_16X1, /**< \brief Resolution 16х1 characters */
	LCD_16X2	= HD44780_DISPLAY_16X2, /**< \brief Resolution 16х2 characters */
	LCD_20X2	= HD44780_DISPLAY_20X2, /**< \brief Resolution 20х2 characters */
	LCD_32X2	= HD44780_DISPLAY_32X2, /**< \brief Resolution 32х2 characters */
	LCD_40X2	= HD44780_DISPLAY_40X2, /**< \brief Resolution 40х2 characters */
	LCD_16X4	= HD44780_DISPLAY_16X4, /**< \brief Resolution 16х4 characters */
	LCD_20X4	= HD44780_DISPLAY_20X4, /**< \brief Resolution 20х4 characters */
	//LCD_40X4	= HD44780_DISPLAY_40X4, /**< \brief Resolution 40х4 characters */
} lcd_display_t;

#endif // SLS_LCD_DM_HD44780_H_
