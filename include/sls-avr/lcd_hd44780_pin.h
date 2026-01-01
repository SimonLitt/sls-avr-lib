// ---------------------------------------------------------------------------+
//					This file is part of SLS AVR Tools
// ---------------------------------------------------------------------------+
// Copyright (C) 2025 Simon Litt
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
 * \author		Simon Litt
 * \copyright	GNU General Public License v3.0
 * \file		sls-avr/lcd_hd44780_pin.h
 * \brief		The dot-matrix liquid crystal display lib for HD44780 compatible controller, connected by 6, 7, 10 or 11 pins.
 */
#ifndef SLS_AVR_LCD_HD44780_PIN_H_
#define SLS_AVR_LCD_HD44780_PIN_H_

#include <stdbool.h>
#include <stdint.h>

#include <sls-avr/avr.h>
#include <sls-lcd/dm_hd44780.h>

#if LCD_HD44780_PIN_MULTI_MODE
/** \cond NO_DOC */
typedef uint8_t lcd_addr_t;
typedef struct {
	uint8_t flags;
	uint8_t row_cout;
	uint8_t col_cout;

	ddr_t data_ddr;
	port_t data_port;
	pin_t data_pin;
	uint8_t data_shift; // For 4-bit IDL
	uint8_t port_mask;

	port_t rs_port;
	pin_bit_t rs_pin;

	port_t e_port;
	pin_bit_t e_pin;

	//port_t e2_port; // LCD 40x4
	//pin_bit_t e2_pin; // LCD 40x4

	port_t rw_port;
	pin_bit_t rw_pin;

	lcd_addr_t row_1_addr;
	lcd_addr_t row_2_addr;
	lcd_addr_t row_3_addr;
	lcd_addr_t row_4_addr;
} lcd_info_struct;
/** \endcond */
/** \brief Information to distinguish a specific display from several connected ones. It is set during initialization and should not be changed manually later. */
typedef volatile lcd_info_struct lcd_info_t;
/** \cond NO_DOC */

#	define __LCD_MULTIMODE_ONLY_INFO_ARG(_n)			const lcd_info_t *const _ ## _n
#	define __LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(_n) __LCD_MULTIMODE_ONLY_INFO_ARG(_n),
/** \endcond */

#else
#	define LCD_HD44780_PIN_MULTI_MODE 		0 /**< \brief Multidisplay display mode */

#	ifndef LCD_HD44780_PIN_DISPLAY_TYPE
#		define LCD_HD44780_PIN_DISPLAY_TYPE /**< \brief Display type. One of: #HD44780_DISPLAY_8X1, #HD44780_DISPLAY_16X1, #HD44780_DISPLAY_16X2, #HD44780_DISPLAY_20X2, #HD44780_DISPLAY_32X2, #HD44780_DISPLAY_40X2, #HD44780_DISPLAY_16X4, #HD44780_DISPLAY_20X4. */
#		error "LCD_HD44780_PIN_DISPLAY_TYPE should be specified"
#	endif

#	ifndef LCD_HD44780_PIN_DATA_PORT
#		error "LCD_HD44780_PIN_DATA_PORT should be specified"
#	endif

#	if !LCD_HD44780_PIN_IDL_8BIT
#		ifndef LCD_HD44780_PIN_DATA_FIRST_PIN
#			error "For 4-bit IDL the LCD_HD44780_PIN_DATA_FIRST_PIN should be specified!"
#		endif
#	endif

#	if (!defined(LCD_HD44780_PIN_RS_PORT)) || (!defined(LCD_HD44780_PIN_RS_PIN))
#		error "LCD_HD44780_PIN_RS_PORT and LCD_HD44780_PIN_RS_PIN should be specified!"
#	endif

#	if (!defined(LCD_HD44780_PIN_E_PORT)) || (!defined(LCD_HD44780_PIN_E_PIN))
#		error "LCD_HD44780_PIN_E_PORT and LCD_HD44780_PIN_E_PIN should be specified!"
#	endif

#	if defined(LCD_HD44780_PIN_RW_PORT) && defined(LCD_HD44780_PIN_RW_PIN)
#		define LCD_HD44780_PIN_ALLOW_RW		1
#	endif

#	define lcd_info_t										void
#	define __LCD_MULTIMODE_ONLY_INFO_ARG(_n)				void
#	define __LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(_n)
#endif // LCD_HD44780_PIN_MULTI_MODE


// It's possible to pass a single port pointer, such as PINA, and receive DDRA and PORTA as a pointer offset. However, multi-screen mode is an exception, mostly for testing, so we'll leave it as is.
/** \brief Initialization information. */
typedef struct {
	uint8_t flags;
	#if LCD_HD44780_PIN_MULTI_MODE
	lcd_display_t display_type;

	ddr_t data_ddr; /**< \brief Data DDRx register */
	port_t data_port; /**< \brief Data PORTx register */
	pin_t data_pin; /**< \brief This is only necessary if reading is enabled. See #HD44780_INIT_READ_ON */
	uint8_t data_shift; /**< \brief It is only necessary for 4-bit IDL. See #HD44780_INIT_IDL_4BIT */

	ddr_t rs_ddr; /**< \brief RS DDRx register */
	port_t rs_port; /**< \brief RS PORTx register */
	pin_bit_t rs_pin; /**< \brief RS pin bit */

	ddr_t e_ddr; /**< \brief E(enable) DDRx register */
	port_t e_port; /**< \brief E(enable) PORTx register */
	pin_bit_t e_pin; /**< \brief E(enable) pin bit */

	ddr_t rw_ddr; /**< \brief RW DDRx register. This is only necessary if reading is enabled. See #HD44780_INIT_READ_ON */
	port_t rw_port; /**< \brief RW PORTx register. This is only necessary if reading is enabled. See #HD44780_INIT_READ_ON */
	pin_bit_t rw_pin; /**< \brief RW pin bit. This is only necessary if reading is enabled. See #HD44780_INIT_READ_ON */
	#endif // LCD_HD44780_PIN_MULTI_MODE
} lcd_init_t;

// ---------------------------------------------------------------------------+
// Init flags
// ---------------------------------------------------------------------------+
/** \cond NO_DOC */
#define __HD44780_INIT_IDL_BIT			0
#define __HD44780_INIT_READ_BIT			1
#define __HD44780_INIT_MOV_DIR_BIT		2
#define __HD44780_INIT_SHIFT_BIT		3
#define __HD44780_INIT_BLINKING_BIT		4
#define __HD44780_INIT_CURSOR_BIT		5
#define __HD44780_INIT_FONT_BIT			6
#define __HD44780_INIT_DISP_BIT			7
/** \endcond */

#define HD44780_INIT_IDL_4BIT			0x00 /**< \brief Initialization with 4-bit interface data length. Ignored for single display mode. */
#define HD44780_INIT_IDL_8BIT			(_BV(__HD44780_INIT_IDL_BIT)) /**< \brief Initialization with 8-bit interface data length. Ignored for single display mode. */

#define HD44780_INIT_READ_OFF			0x00 /**< \brief Initialization without controller read support. Ignored for single display mode. */
#define HD44780_INIT_READ_ON			(_BV(__HD44780_INIT_READ_BIT)) /**< \brief Initialization with controller read support. Ignored for single display mode. */

#define HD44780_INIT_MOV_DIR_DEC		0x00 /**< \brief Initialization with cursor moving direction decrement. */
#define HD44780_INIT_MOV_DIR_INC		(_BV(__HD44780_INIT_MOV_DIR_BIT)) /**< \brief Initialization with cursor moving direction increment. */

#define HD44780_INIT_SHIFT_OFF			0x00 /**< \brief Initialization with shift disabled. */
#define HD44780_INIT_SHIFT_ON			(_BV(__HD44780_INIT_SHIFT_BIT)) /**< \brief Initialization with shift enabled. */

#define HD44780_INIT_BLINKING_OFF		0x00 /**< \brief Initialization with the blinking off. */
#define HD44780_INIT_BLINKING_ON		(_BV(__HD44780_INIT_BLINKING_BIT)) /**< \brief Initialization with the blinking on. */

#define HD44780_INIT_CURSOR_OFF			0x00 /**< \brief Initialization with the cursor off. */
#define HD44780_INIT_CURSOR_ON			(_BV(__HD44780_INIT_CURSOR_BIT)) /**< \brief Initialization with the cursor on. */

#define HD44780_INIT_FONT_NORMAL		0x00 /**< \brief Initialization with normal(5x8) font. */
#define HD44780_INIT_FONT_BIG			(_BV(__HD44780_INIT_FONT_BIT)) /**< \brief Initialization with the big font. */

#define HD44780_INIT_DISP_OFF			0x00 /**< \brief Initialization with the display off. */
#define HD44780_INIT_DISP_ON			(_BV(__HD44780_INIT_DISP_BIT)) /**< \brief Initialization with the display on. */

/** \cond NO_DOC */
#define __HD44780_CONF_IDL_BIT			0
#define __HD44780_CONF_READ_BIT			1

#define _HD44780_CONF_IDL_4BIT			0x00 // 4-bit interface data length.
#define _HD44780_CONF_IDL_8BIT			(_BV(__HD44780_CONF_IDL_BIT)) // 8-bit interface data length.

#define _HD44780_CONF_READ_OFF			0x00 // Read disable.
#define _HD44780_CONF_READ_ON			(_BV(__HD44780_CONF_READ_BIT)) // Read enable.

#define _HD44780_HALF_DATA_MASK			0x0F // 4-bit interface default mask
/** \endcond */

/**
 * \brief Initializes the display
 * \param config #lcd_init_t structure
 * \return #lcd_info_t structure. Multidisplay mode only. Should be used for further access to the same display. See #LCD_HD44780_PIN_MULTI_MODE
 */
lcd_info_t lcd_init(const lcd_init_t *const config);

/**
 * \brief Clears the display
 * \param info #lcd_info_t reference. Multidisplay mode only. See #LCD_HD44780_PIN_MULTI_MODE
 */
void lcd_clear(__LCD_MULTIMODE_ONLY_INFO_ARG(info));

/**
 * \brief Sets DDRAM address 0 in a ddress counter.
 * \param info #lcd_info_t reference. Multidisplay mode only. See #LCD_HD44780_PIN_MULTI_MODE
 * \param flags Options flags
 */
void lcd_home(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const uint8_t flags);

/**
 * \brief Sets cursor move direction and specifies display shift.
 * \param info #lcd_info_t reference. Multidisplay mode only. See #LCD_HD44780_PIN_MULTI_MODE
 * \param flags Options flags
 */
void lcd_entry_mode(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const uint8_t flags);

/**
 * \brief Sets diplay options
 * \param info #lcd_info_t reference. Multidisplay mode only. See #LCD_HD44780_PIN_MULTI_MODE
 * \param flags Options flags
 */
void lcd_display_ctrl(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const uint8_t flags);

/**
 * \brief Moves the cursor or shifts the display
 * \param info #lcd_info_t reference. Multidisplay mode only. See #LCD_HD44780_PIN_MULTI_MODE
 * \param flags Options flags
 */
void lcd_cursor(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const uint8_t flags);

/**
 * \brief Sets options
 * \param info #lcd_info_t reference. Multidisplay mode only. See #LCD_HD44780_PIN_MULTI_MODE
 * \param flags Options flags
 */
void lcd_func_set(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const uint8_t flags);

/**
 * \brief Sets CGRAM address
 * \param info #lcd_info_t reference. Multidisplay mode only. See #LCD_HD44780_PIN_MULTI_MODE
 * \param flags CGRAM address
 */
void lcd_cgr_adr(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const uint8_t flags);

/**
 * \brief Sets DDRAM address
 * \param info #lcd_info_t reference. Multidisplay mode only. See #LCD_HD44780_PIN_MULTI_MODE
 * \param flags	DDRAM address
 */
void lcd_ddr_adr(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const uint8_t flags);

/**
 * \brief Sets DDRAM address to a given position
 * \param info #lcd_info_t reference. Multidisplay mode only. See #LCD_HD44780_PIN_MULTI_MODE
 * \param line Display row
 * \param pos Display column
 */
void lcd_set_pos(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const lcd_line_t line, const uint8_t pos);

/**
 * \brief Outputs a symbol
 * \param info #lcd_info_t reference. Multidisplay mode only. See #LCD_HD44780_PIN_MULTI_MODE
 * \param ch Symbol code
 */
void lcd_byte(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const byte_t ch);

/**
 * \brief Outputs a string on entry line
 * \param info #lcd_info_t reference. Multidisplay mode only. See #LCD_HD44780_PIN_MULTI_MODE
 * \param str A string
 * \param line Display row
 * \param pos Starts with the display column
 */
void lcd_line(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const char str[], const lcd_line_t line, const uint8_t start_pos);

/**
 * \brief Outputs a string to buffer.
 * \details No line overflow control. The CR character will be skipped.
 * \param info #lcd_info_t reference. Multidisplay mode only. See #LCD_HD44780_PIN_MULTI_MODE
 * \param str A string
 */
void lcd_print(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const char str[]);

/**
 * \brief Outputs a string on all lines
 * \param info #lcd_info_t reference. Multidisplay mode only. See #LCD_HD44780_PIN_MULTI_MODE
 * \param str A string
 */
void lcd_refresh_ml(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const char str[]);

#if LCD_HD44780_PIN_MULTI_MODE || LCD_HD44780_PIN_ALLOW_RW
/**
 * \brief Waits until display is buisy and returns address counter contents.
 * \param info #lcd_info_t reference. Multidisplay mode only. See #LCD_HD44780_PIN_MULTI_MODE
 * \return Address counter contents.
 */
byte_t lcd_read_busy_and_addr(__LCD_MULTIMODE_ONLY_INFO_ARG(info));

/**
 * \brief Reads data from CGRAM or from DDRAM
 * \param info #lcd_info_t reference. Multidisplay mode only. See #LCD_HD44780_PIN_MULTI_MODE
 * \return Readed byte
 */
byte_t lcd_read_data(__LCD_MULTIMODE_ONLY_INFO_ARG(info));
#endif
/**
 * \brief Creates a custom symbol.
 * \param char_pos Char position 0-7.
 * \param custom_char 8-byte array with symbol information.
 * \param info #lcd_info_t reference. Multidisplay mode only. See #LCD_HD44780_PIN_MULTI_MODE
 * \remark Once executed, no output will be possible until the DDRAM address is set. The DDRAM address can be set using the following methods: #lcd_ddr_adr(), #lcd_set_pos() and #lcd_clear().
 */
void lcd_custom_char(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const byte_t char_pos, const byte_t custom_char[8]);
#endif // SLS_AVR_LCD_HD44780_PIN_H_
