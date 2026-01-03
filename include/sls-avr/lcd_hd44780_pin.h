// ---------------------------------------------------------------------------+
//					This file is part of SLS AVR Library
//				https://github.com/SimonLitt/sls-avr-lib
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
 * \file		sls-avr/lcd_hd44780_pin.h
 * \brief		The dot-matrix liquid crystal display lib for HD44780 compatible controller, connected by 6, 7, 10 or 11 pins.
 * \details		For a 4-bit interface, the data bus connection pins should be connected in series; for an 8-bit interface, the data bus should occupy the entire port. The remaining 2 or 3 pins can be selected separately.
 *
 * \code #include <sls-avr/lcd_hd44780_pin.h>\endcode
 */
#ifndef SLS_AVR_LCD_HD44780_PIN_H_
#define SLS_AVR_LCD_HD44780_PIN_H_

#include <stdbool.h>
#include <stdint.h>

#include <sls-avr/avr.h>
#include <sls-lcd/dm_hd44780.h>

#ifndef LCD_HD44780_PIN_SINGLE_SOME_CODE
#	define LCD_HD44780_PIN_SINGLE_SOME_CODE 		0 /**< \brief This allows for the same code to be achieved with the macro #LCD_HD44780_PIN_MULTI_MODE on and off. */
#endif // BTN_FAST_SOME_CODE

#if LCD_HD44780_PIN_MULTI_MODE

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

typedef volatile lcd_info_struct lcd_info_t;

#	define __LCD_MULTIMODE_ONLY_INFO_ARG(_n)			const lcd_info_t *const _ ## _n
#	define __LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(_n) __LCD_MULTIMODE_ONLY_INFO_ARG(_n),

#else
#	define LCD_HD44780_PIN_MULTI_MODE 		0 /**< \brief Multidisplay display mode */

#	ifndef LCD_HD44780_PIN_DISPLAY_TYPE
#		define LCD_HD44780_PIN_DISPLAY_TYPE /**< \brief Display type. \details One of: #HD44780_DISPLAY_8X1, #HD44780_DISPLAY_16X1, #HD44780_DISPLAY_16X2, #HD44780_DISPLAY_20X2, #HD44780_DISPLAY_32X2, #HD44780_DISPLAY_40X2, #HD44780_DISPLAY_16X4, #HD44780_DISPLAY_20X4. */
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
/** \cond NO_DOC */
#	if LCD_HD44780_PIN_SINGLE_SOME_CODE
#		define lcd_info_t										byte_t
#	else
#		define lcd_info_t										void
#	endif // LCD_HD44780_PIN_SINGLE_SOME_CODE
#	define __LCD_MULTIMODE_ONLY_INFO_ARG(_n)				void
#	define __LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(_n)
/** \endcond */
#endif // LCD_HD44780_PIN_MULTI_MODE

#if __DOXYGEN__
/** \brief Information to distinguish a specific display from several connected ones.\details This parameter is set during LCD initialization and should not be changed manually later. */
typedef volatile lcd_info_struct lcd_info_t;
#endif // __DOXYGEN__

// It's possible to pass a single port pointer, such as PINA, and receive DDRA and PORTA as a pointer offset. However, multi-screen mode is an exception, mostly for testing, so we'll leave it as is.
/** \brief Initialization information. */
typedef struct {
	uint8_t flags; /**< \brief Config flags */
	#if LCD_HD44780_PIN_MULTI_MODE || __DOXYGEN__
	lcd_display_t display_type; /**< \brief Display type, see #lcd_display_t */

	ddr_t data_ddr; /**< \brief Data DDRx register \details Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE */
	port_t data_port; /**< \brief Data PORTx register \details Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE */
	pin_t data_pin; /**< \brief This is only necessary if reading is enabled. \details Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE */
	uint8_t data_shift; /**< \brief It is only necessary for 4-bit IDL. \details Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE */

	ddr_t rs_ddr; /**< \brief RS DDRx register \details Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE*/
	port_t rs_port; /**< \brief RS PORTx register \details Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE */
	pin_bit_t rs_pin; /**< \brief RS pin bit \details Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE */

	ddr_t e_ddr; /**< \brief E(enable) DDRx register \details Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE */
	port_t e_port; /**< \brief E(enable) PORTx register \details Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE */
	pin_bit_t e_pin; /**< \brief E(enable) pin bit \details Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE */

	ddr_t rw_ddr; /**< \brief RW DDRx register. This is only necessary if reading is enabled. \details Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE */
	port_t rw_port; /**< \brief RW PORTx register. This is only necessary if reading is enabled. \details Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE */
	pin_bit_t rw_pin; /**< \brief RW pin bit. This is only necessary if reading is enabled. \details Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE */
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

#if LCD_HD44780_PIN_MULTI_MODE || __DOXYGEN__
/**
 * \section multi lcd_info_t lcd_init(const lcd_init_t *const config)
 * \brief Initializes the display
 *
 *  Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE
 * \param config #lcd_init_t structure
 * \return #lcd_info_t structure. Should be used for further access to the same display.
 */
lcd_info_t lcd_init(const lcd_init_t *const config);

/**
 * \brief Clears the display
 *
 *  Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE
 * \param info #lcd_info_t reference.
 */
void lcd_clear(const lcd_info_t *const info);

/**
 * \brief Sets DDRAM address 0 in a ddress counter.
 *
 *  *  Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE
 * \param info #lcd_info_t reference.
 * \param flags Options flags
 */
void lcd_home(const lcd_info_t *const info, const uint8_t flags);

/**
 * \brief Sets cursor move direction and specifies display shift.
 *
 * Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE
 * \param info #lcd_info_t reference.
 * \param flags Options flags
 */
void lcd_entry_mode(const lcd_info_t *const info, const uint8_t flags);

/**
 * \brief Sets diplay options
 *
 * Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE
 * \param info #lcd_info_t reference.
 * \param flags Options flags
 */
void lcd_display_ctrl(const lcd_info_t *const info, const uint8_t flags);

/**
 * \brief Moves the cursor or shifts the display
 *
 * Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE
 * \param info #lcd_info_t reference.
 * \param flags Options flags
 */
void lcd_cursor(const lcd_info_t *const info, const uint8_t flags);

/**
 * \brief Sets options
 *
 * Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE
 * \param info #lcd_info_t reference.
 * \param flags Options flags
 */
void lcd_func_set(const lcd_info_t *const info, const uint8_t flags);

/**
 * \brief Sets CGRAM address
 *
 * Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE
 * \param info #lcd_info_t reference.
 * \param flags CGRAM address
 */
void lcd_cgr_adr(const lcd_info_t *const info, const uint8_t flags);

/**
 * \brief Sets DDRAM address
 *
 * Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE
 * \param info #lcd_info_t reference.
 * \param flags	DDRAM address
 */
void lcd_ddr_adr(const lcd_info_t *const info, const uint8_t flags);

/**
 * \brief Sets DDRAM address to a given position
 *
 * Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE
 * \param info #lcd_info_t reference.
 * \param line Display row
 * \param pos Display column
 */
void lcd_set_pos(const lcd_info_t *const info, const lcd_line_t line, const uint8_t pos);

/**
 * \brief Outputs a symbol
 *
 * Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE
 * \param info #lcd_info_t reference.
 * \param ch Symbol code
 */
void lcd_byte(const lcd_info_t *const info, const byte_t ch);

/**
 * \brief Outputs a string on entry line
 *
 * Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE
 * \param info #lcd_info_t reference.
 * \param str A string
 * \param line Display row
 * \param start_pos Starts with the display column
 */
void lcd_line(const lcd_info_t *const info, const char str[], const lcd_line_t line, const uint8_t start_pos);

/**
 * \brief Outputs a string to buffer.
 *
 * Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE
 * \details No line overflow control. The CR character will be skipped.
 * \param info #lcd_info_t reference.
 * \param str A string
 */
void lcd_print(const lcd_info_t *const info, const char str[]);

/**
 * \brief Outputs a string on all lines
 *
 * Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE
 * \param info #lcd_info_t reference.
 * \param str A string
 */
void lcd_refresh_ml(const lcd_info_t *const info, const char str[]);

/**
 * \brief Creates a custom symbol.
 *
 * Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE
 * \param char_pos Char position 0-7.
 * \param custom_char 8-byte array with symbol information.
 * \param info #lcd_info_t reference.
 * \remark Once executed, no output will be possible until the DDRAM address is set. The DDRAM address can be set using the following methods: #lcd_ddr_adr(), #lcd_set_pos() and #lcd_clear().
 */
void lcd_custom_char(const lcd_info_t *const info, const byte_t char_pos, const byte_t custom_char[8]);

/**
 * \brief Waits until display is buisy and returns address counter contents.
 *
 * Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE
 * \param info #lcd_info_t reference.
 * \return Address counter contents.
 */
byte_t lcd_read_busy_and_addr(const lcd_info_t *const info);

/**
 * \brief Reads data from CGRAM or from DDRAM
 *
 * Multidisplay or some code modes only. See #LCD_HD44780_PIN_MULTI_MODE , #LCD_HD44780_PIN_SINGLE_SOME_CODE
 * \param info #lcd_info_t reference.
 * \return Readed byte
 */
byte_t lcd_read_data(const lcd_info_t *const info);
#endif // LCD_HD44780_PIN_MULTI_MODE

#if !LCD_HD44780_PIN_MULTI_MODE
#	if !LCD_HD44780_PIN_SINGLE_SOME_CODE
/**
 * \section single void lcd_init(const lcd_init_t *const config)
 * \brief Initializes the display
 * \param config #lcd_init_t structure
 */
void lcd_init(const lcd_init_t *const config);
#	else
lcd_info_t lcd_init(const lcd_init_t *const config);
#	endif // LCD_HD44780_PIN_SINGLE_SOME_CODE

#	if LCD_HD44780_PIN_SINGLE_SOME_CODE
		#error "TODO: implement"
		void _sc_lcd_clear(void);
		void _sc_lcd_home(const uint8_t flags);
		void _sc_lcd_entry_mode(const uint8_t flags);
		void _sc_lcd_display_ctrl(const uint8_t flags);
		void _sc_lcd_cursor(const uint8_t flags);
		void _sc_lcd_func_set(const uint8_t flags);
		void _sc_lcd_cgr_adr(const uint8_t flags);
		void _sc_lcd_ddr_adr(const uint8_t flags);
		void _sc_lcd_set_pos(const lcd_line_t line, const uint8_t pos);
		void _sc_lcd_byte(const byte_t ch);
		void _sc_lcd_line(const char str[], const lcd_line_t line, const uint8_t start_pos);
		void _sc_lcd_print(const char str[]);
		void _sc_lcd_refresh_ml(const char str[]);
		void _sc_lcd_custom_char(const byte_t char_pos, const byte_t custom_char[8]);
		byte_t _sc_lcd_read_busy_and_addr();
		byte_t _sc_lcd_read_data();
#		define lcd_clear(_i)				_sc_lcd_clear()
#		define lcd_home(_i, flags)			_sc_lcd_home((flags))
#		define lcd_entry_mode(_i, flags)	_sc_lcd_entry_mode((flags))
#		define lcd_display_ctrl(_i, flags)	_sc_lcd_entry_mode((flags))
#		define lcd_cursor(_i, flags)		_sc_lcd_entry_mode((flags))
#		define lcd_func_set(_i, flags)		_sc_lcd_entry_mode((flags))
#		define lcd_cgr_adr(_i, flags)		_sc_lcd_entry_mode((flags))
#		define lcd_ddr_adr(_i, flags)		_sc_lcd_entry_mode((flags))
#		define lcd_set_pos(_i, line, pos)	_sc_lcd_set_pos((line), (pos))
#		define lcd_byte(_i, ch)				_sc_lcd_byte((ch))
#		define lcd_line(_i, str, line, sp)	_sc_lcd_line((str), (line), (sp))
#		define lcd_print(_i, str)			_sc_lcd_print((str))
#		define lcd_refresh_ml(_i, str)		_sc_lcd_refresh_ml((str))
#		define lcd_custom_char(_i, pos, s)	_sc_lcd_custom_char((pos), (s))
#		define lcd_read_busy_and_addr(_i)	_sc_lcd_read_busy_and_addr()
#		define lcd_read_data(_i)			_sc_lcd_read_data()
#	else
/**
 * \brief Clears the display
 */
void lcd_clear(void);

/**
 * \brief Sets DDRAM address 0 in a ddress counter.
 * \param flags Options flags
 */
void lcd_home(const uint8_t flags);

/**
 * \brief Sets cursor move direction and specifies display shift.
 * \param flags Options flags
 */
void lcd_entry_mode(const uint8_t flags);

/**
 * \brief Sets diplay options
 * \param flags Options flags
 */
void lcd_display_ctrl(const uint8_t flags);

/**
 * \brief Moves the cursor or shifts the display
 * \param flags Options flags
 */
void lcd_cursor(const uint8_t flags);

/**
 * \brief Sets options
 * \param flags Options flags
 */
void lcd_func_set(const uint8_t flags);

/**
 * \brief Sets CGRAM address
 * \param flags CGRAM address
 */
void lcd_cgr_adr(const uint8_t flags);

/**
 * \brief Sets DDRAM address
 * \param flags	DDRAM address
 */
void lcd_ddr_adr(const uint8_t flags);

/**
 * \brief Sets DDRAM address to a given position
 * \param line Display row
 * \param pos Display column
 */
void lcd_set_pos(const lcd_line_t line, const uint8_t pos);

/**
 * \brief Outputs a symbol
 * \param ch Symbol code
 */
void lcd_byte(const byte_t ch);

/**
 * \brief Outputs a string on entry line
 * \param str A string
 * \param line Display row
 * \param start_pos Starts with the display column
 */
void lcd_line(const char str[], const lcd_line_t line, const uint8_t start_pos);

/**
 * \brief Outputs a string to buffer.
 * \details No line overflow control. The CR character will be skipped.
 * \param str A string
 */
void lcd_print(const char str[]);

/**
 * \brief Outputs a string on all lines
 * \param str A string
 */
void lcd_refresh_ml(const char str[]);

#		if LCD_HD44780_PIN_ALLOW_RW || __DOXYGEN__
/**
 * \brief Waits until display is buisy and returns address counter contents.
 * \return Address counter contents.
 */
byte_t lcd_read_busy_and_addr();

/**
 * \brief Reads data from CGRAM or from DDRAM
 * \return Readed byte
 */
byte_t lcd_read_data();
#		endif
#	endif // LCD_HD44780_PIN_SINGLE_SOME_CODE
#endif // LCD_HD44780_PIN_MULTI_MODE

#endif // SLS_AVR_LCD_HD44780_PIN_H_
