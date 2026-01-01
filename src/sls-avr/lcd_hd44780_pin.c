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
#include <sls-avr/lcd_hd44780_pin.h>
#include <util/delay.h>

#if LCD_HD44780_PIN_MULTI_MODE
#	define __LCD_MULTIMODE_ONLY_VAR(_n)						(_ ## _n)
#	define __LCD_MULTIMODE_ONLY_VAR_BY_REF(_n)				&__LCD_MULTIMODE_ONLY_VAR(_n)
#	define __LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(_n)			__LCD_MULTIMODE_ONLY_VAR(_n),
#	define __LCD_MULTIMODE_ONLY_VAR_BY_REF_WITH_COMMA(_n)	&__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(_n)

#	define __LCD_MULTIMODE_ONLY_BOOL_ARG(_n)				const bool _ ## _n

#	define __INFO_ROW_COUT				_info->row_cout
#	define __INFO_COL_COUT				_info->col_cout
#	define __INFO_ROW_1_ADDR			_info->row_1_addr
#	define __INFO_ROW_2_ADDR			_info->row_2_addr
#	define __INFO_ROW_3_ADDR			_info->row_3_addr
#	define __INFO_ROW_4_ADDR			_info->row_4_addr

#else
#	define __LCD_MULTIMODE_ONLY_VAR(_n)
#	define __LCD_MULTIMODE_ONLY_VAR_BY_REF(_n)
#	define __LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(_n)
#	define __LCD_MULTIMODE_ONLY_VAR_BY_REF_WITH_COMMA(_n)

#	define __LCD_MULTIMODE_ONLY_BOOL_ARG(_n)				void

#	if !LCD_HD44780_PIN_IDL_8BIT
#		define __INFO_DATA_SHIFT		LCD_HD44780_PIN_DATA_FIRST_PIN
#		define __INFO_PORT_MASK			(_HD44780_HALF_DATA_MASK << LCD_HD44780_PIN_DATA_FIRST_PIN)
#	else
#		define __INFO_PORT_MASK			0xFFU
#	endif

#	if (LCD_HD44780_PIN_DISPLAY_TYPE == HD44780_DISPLAY_8X1)
#		define __INFO_ROW_COUT			1
#		define __INFO_COL_COUT			8
#		define __INFO_ROW_1_ADDR		HD44780_ROW_1_DDRAM_ADR
#	elif (LCD_HD44780_PIN_DISPLAY_TYPE == HD44780_DISPLAY_16X1)
#		define __INFO_ROW_COUT			1
#		define __INFO_COL_COUT			16
#		define __INFO_ROW_1_ADDR		HD44780_ROW_1_DDRAM_ADR
#	elif (LCD_HD44780_PIN_DISPLAY_TYPE == HD44780_DISPLAY_16X2)
#		define __INFO_ROW_COUT			2
#		define __INFO_COL_COUT			16
#		define __INFO_ROW_1_ADDR		HD44780_ROW_1_DDRAM_ADR
#		define __INFO_ROW_2_ADDR		HD44780_ROW_2_DDRAM_ADR
#	elif (LCD_HD44780_PIN_DISPLAY_TYPE == HD44780_DISPLAY_20X2)
#		define __INFO_ROW_COUT			2
#		define __INFO_COL_COUT			20
#		define __INFO_ROW_1_ADDR		HD44780_ROW_1_DDRAM_ADR
#		define __INFO_ROW_2_ADDR		HD44780_ROW_2_DDRAM_ADR
#	elif (LCD_HD44780_PIN_DISPLAY_TYPE == HD44780_DISPLAY_32X2)
#		define __INFO_ROW_COUT			2
#		define __INFO_COL_COUT			32
#		define __INFO_ROW_1_ADDR		HD44780_ROW_1_DDRAM_ADR
#		define __INFO_ROW_2_ADDR		HD44780_ROW_2_DDRAM_ADR
#	elif (LCD_HD44780_PIN_DISPLAY_TYPE == HD44780_DISPLAY_40X2)
#		define __INFO_ROW_COUT			2
#		define __INFO_COL_COUT			40
#		define __INFO_ROW_1_ADDR		HD44780_ROW_1_DDRAM_ADR
#		define __INFO_ROW_2_ADDR		HD44780_ROW_2_DDRAM_ADR
#	elif (LCD_HD44780_PIN_DISPLAY_TYPE == HD44780_DISPLAY_16X4)
#		define __INFO_ROW_COUT			4
#		define __INFO_COL_COUT			16
#		define __INFO_ROW_1_ADDR		HD44780_ROW_1_DDRAM_ADR
#		define __INFO_ROW_2_ADDR		HD44780_ROW_2_DDRAM_ADR
#		define __INFO_ROW_3_ADDR		HD44780_ROW_3_DDRAM_ADR
#		define __INFO_ROW_4_ADDR		HD44780_ROW_4_DDRAM_ADR
#	elif (LCD_HD44780_PIN_DISPLAY_TYPE == HD44780_DISPLAY_20X4)
#		define __INFO_ROW_COUT			4
#		define __INFO_COL_COUT			20
#		define __INFO_ROW_1_ADDR		HD44780_ROW_1_DDRAM_ADR
#		define __INFO_ROW_2_ADDR		HD44780_ROW_2_DDRAM_ADR
#		define __INFO_ROW_3_ADDR		HD44780_ROW_3_20x4_DDRAM_ADR
#		define __INFO_ROW_4_ADDR		HD44780_ROW_4_20x4_DDRAM_ADR
#	elif (LCD_HD44780_PIN_DISPLAY_TYPE == HD44780_DISPLAY_40X4)
#		define __INFO_ROW_COUT			4
#		define __INFO_COL_COUT			40
#		error "Display 40x4 currently unsupported!"
#		error "TODO: Implement: Two E chanels!"
#		define __INFO_ROW_1_ADDR		HD44780_ROW_1_DDRAM_ADR
#		define __INFO_ROW_2_ADDR		HD44780_ROW_2_DDRAM_ADR
#		define __INFO_ROW_3_ADDR		HD44780_ROW_1_DDRAM_ADR
#		define __INFO_ROW_4_ADDR		HD44780_ROW_2_DDRAM_ADR
#	else
#		error "Unsupported display type!"
#	endif
#endif

static void _lcd_send(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const byte_t ch) {
	#if LCD_HD44780_PIN_MULTI_MODE
		if (flag_is_set(_info->flags, __HD44780_CONF_IDL_BIT)) {
			gpio_set(*(_info->data_port), ch);
		} else {
			port_replace(*(_info->data_port), _info->port_mask, ch << _info->data_shift);
		}
		pin_on(*(_info->e_port), _info->e_pin);
		_delay_us(HD44780_ENABLE_PULSE_US);
		pin_off(*(_info->e_port), _info->e_pin);
		_delay_us(HD44780_ENABLE_PULSE_US);
	#else
	#	if LCD_HD44780_PIN_IDL_8BIT
			GPIO_SET(LCD_HD44780_PIN_DATA_PORT, ch);
	#	else
			PORT_REPLACE(LCD_HD44780_PIN_DATA_PORT, __INFO_PORT_MASK, ch << __INFO_DATA_SHIFT);
	#	endif
		PIN_ON(LCD_HD44780_PIN_E_PORT, LCD_HD44780_PIN_E_PIN);
		_delay_us(HD44780_ENABLE_PULSE_US);
		PIN_OFF(LCD_HD44780_PIN_E_PORT, LCD_HD44780_PIN_E_PIN);
		_delay_us(HD44780_ENABLE_PULSE_US);
	#endif
}

static void _lcd_byte(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const byte_t ch) {
	#if LCD_HD44780_PIN_MULTI_MODE
		if (!flag_is_set(_info->flags, __HD44780_CONF_IDL_BIT)) {
			_lcd_send(_info, ch >> 4);
		}
	#else
	#	if !LCD_HD44780_PIN_IDL_8BIT
			_lcd_send(ch >> 4);
	#	endif
	#endif
	_lcd_send(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) ch);
}

void lcd_byte(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const byte_t ch) {
	_lcd_byte(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) ch);
	#if LCD_HD44780_PIN_MULTI_MODE
		if (flag_is_set(_info->flags, __HD44780_CONF_READ_BIT)) {
			lcd_read_busy_and_addr(_info);
		} else {
			_delay_us(HD44780_EXEC_TIME_US);
		}
	#else
	#	if LCD_HD44780_PIN_ALLOW_RW
			lcd_read_busy_and_addr();
	#	else
			_delay_us(HD44780_EXEC_TIME_US);
	#	endif
	#endif
}

static void _lcd_command(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const byte_t ch) {
	#if LCD_HD44780_PIN_MULTI_MODE
		pin_off(*(_info->rs_port), _info->rs_pin);
	#else
		PIN_OFF(LCD_HD44780_PIN_RS_PORT, LCD_HD44780_PIN_RS_PIN);
	#endif
	lcd_byte(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) ch);
	#if LCD_HD44780_PIN_MULTI_MODE
		pin_on(*(_info->rs_port), _info->rs_pin);// Default on - data
	#else
		PIN_ON(LCD_HD44780_PIN_RS_PORT, LCD_HD44780_PIN_RS_PIN);// Default on - data
	#endif
}

static void _lcd_long_command(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const byte_t ch) {
	#if LCD_HD44780_PIN_MULTI_MODE
		pin_off(*(_info->rs_port), _info->rs_pin);
		_lcd_byte(_info, ch);
		pin_on(*(_info->rs_port), _info->rs_pin);// Default on - data
		if (flag_is_set(_info->flags, __HD44780_CONF_READ_BIT)) {
			lcd_read_busy_and_addr(_info);
		} else {
			_delay_us(HD44780_LONG_EXEC_TIME_US);
		}
	#else
		PIN_OFF(LCD_HD44780_PIN_RS_PORT, LCD_HD44780_PIN_RS_PIN);
		_lcd_byte(ch);
		PIN_ON(LCD_HD44780_PIN_RS_PORT, LCD_HD44780_PIN_RS_PIN);// Default on - data
	#	if LCD_HD44780_PIN_ALLOW_RW
			lcd_read_busy_and_addr();
	#	else
			_delay_us(HD44780_LONG_EXEC_TIME_US);
	#	endif
	#endif
}

void lcd_custom_char(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const byte_t char_pos, const byte_t custom_char[8]) {
	if (char_pos < 8) {
		lcd_cgr_adr(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) (char_pos * 8));
		for(byte_t char_byte = 0; char_byte < 8; char_byte++) {
			lcd_byte(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) custom_char[char_byte]);
		}
    }
}

lcd_info_t lcd_init(const lcd_init_t *const config) {
	#if LCD_HD44780_PIN_MULTI_MODE
		lcd_info_t _info;
		_info.flags = 0x00;
		_info.data_ddr = config->data_ddr;
		_info.data_port = config->data_port;
		_info.data_pin = config->data_pin;
		_info.rs_port = config->rs_port;
		_info.rs_pin = config->rs_pin;
		_info.e_port = config->e_port;
		_info.e_pin = config->e_pin;
		_info.rw_port = config->rw_port;
		_info.rw_pin = config->rw_pin;

		bool interface_dl_is_full = flag_is_set(config->flags, __HD44780_INIT_IDL_BIT);

		pin_to_write_d_lo(*(config->rs_ddr), *(config->rs_port), config->rs_pin);
		pin_to_write_d_lo(*(config->e_ddr), *(config->e_port), config->e_pin);
		bool is_read_enable = flag_is_set(config->flags, __HD44780_INIT_READ_BIT);
		if (is_read_enable) {
			pin_to_write_d_lo(*(config->rw_ddr), *(config->rw_port), config->rw_pin); // Default off
		} else {
			_info.data_ddr = 0;
			_info.data_pin = 0;
			_info.rw_port = 0;
			_info.rw_pin = 0;
			_info.flags |= _HD44780_CONF_READ_OFF;
		}

		if (interface_dl_is_full) {
			_info.port_mask = 0xFF;
		} else {
			_info.port_mask = _HD44780_HALF_DATA_MASK << (config->data_shift);
		}

		port_to_write(*(config->data_ddr), _info.port_mask);
	#else
		PIN_TO_WRITE_D_LO(LCD_HD44780_PIN_RS_PORT, LCD_HD44780_PIN_RS_PIN);
		PIN_TO_WRITE_D_LO(LCD_HD44780_PIN_E_PORT, LCD_HD44780_PIN_E_PIN);
	#	if LCD_HD44780_PIN_ALLOW_RW
			PIN_TO_WRITE_D_LO(LCD_HD44780_PIN_RW_PORT, LCD_HD44780_PIN_RW_PIN); // Default off
	#	endif
		PORT_TO_WRITE(LCD_HD44780_PIN_DATA_PORT, __INFO_PORT_MASK);
	#endif
	_delay_ms(HD44780_WAIT_INIT_MS+3);

	uint8_t set_flags = flag_is_set(config->flags, __HD44780_INIT_FONT_BIT) ? HD44780_F_BIG : HD44780_F_NORMAL;
	#if LCD_HD44780_PIN_MULTI_MODE
	switch(config->display_type) {
		case LCD_8X1:
			set_flags |= HD44780_N_1L;
			_info.row_cout = 1;
			_info.col_cout = 16;
			_info.row_1_addr = HD44780_ROW_1_DDRAM_ADR;
			break;
		case LCD_16X1:
			set_flags |= HD44780_N_1L;
			_info.row_cout = 1;
			_info.col_cout = 16;
			_info.row_1_addr = HD44780_ROW_1_DDRAM_ADR;
			break;
		case LCD_16X2:
			set_flags |= HD44780_N_2L;
			_info.row_cout = 2;
			_info.col_cout = 16;
			_info.row_1_addr = HD44780_ROW_1_DDRAM_ADR;
			_info.row_2_addr = HD44780_ROW_2_DDRAM_ADR;
			break;
		case LCD_20X2:
			set_flags |= HD44780_N_2L;
			_info.row_cout = 2;
			_info.col_cout = 20;
			_info.row_1_addr = HD44780_ROW_1_DDRAM_ADR;
			_info.row_2_addr = HD44780_ROW_2_DDRAM_ADR;
			break;
		case LCD_32X2:
			set_flags |= HD44780_N_2L;
			_info.row_cout = 2;
			_info.col_cout = 32;
			_info.row_1_addr = HD44780_ROW_1_DDRAM_ADR;
			_info.row_2_addr = HD44780_ROW_2_DDRAM_ADR;
			break;
		case LCD_40X2:
			set_flags |= HD44780_N_2L;
			_info.row_cout = 2;
			_info.col_cout = 40;
			_info.row_1_addr = HD44780_ROW_1_DDRAM_ADR;
			_info.row_2_addr = HD44780_ROW_2_DDRAM_ADR;
			break;
		case LCD_16X4:
			set_flags |= HD44780_N_2L;
			_info.row_cout = 4;
			_info.col_cout = 16;
			_info.row_1_addr = HD44780_ROW_1_DDRAM_ADR;
			_info.row_2_addr = HD44780_ROW_2_DDRAM_ADR;
			_info.row_3_addr = HD44780_ROW_3_DDRAM_ADR;
			_info.row_4_addr = HD44780_ROW_4_DDRAM_ADR;
			break;
		case LCD_20X4:
			set_flags |= HD44780_N_2L;
			_info.row_cout = 4;
			_info.col_cout = 20;
			_info.row_1_addr = HD44780_ROW_1_DDRAM_ADR;
			_info.row_2_addr = HD44780_ROW_2_DDRAM_ADR;
			_info.row_3_addr = HD44780_ROW_3_20x4_DDRAM_ADR;
			_info.row_4_addr = HD44780_ROW_4_20x4_DDRAM_ADR;
			break;
		/*case LCD_40X4:
			set_flags |= HD44780_N_2L;
			_info.row_cout = 4;
			_info.col_cout = 40;
			_info.row_1_addr = HD44780_ROW_1_DDRAM_ADR;
			_info.row_2_addr = HD44780_ROW_2_DDRAM_ADR;
			_info.row_3_addr = HD44780_ROW_1_DDRAM_ADR;
			_info.row_4_addr = HD44780_ROW_2_DDRAM_ADR;
			break;*/
	}
	#else
	#	if (LCD_HD44780_PIN_DISPLAY_TYPE == HD44780_DISPLAY_8X1) || (LCD_HD44780_PIN_DISPLAY_TYPE == HD44780_DISPLAY_16X1)
			set_flags |= HD44780_N_1L;
	#	else
			set_flags |= HD44780_N_2L;
	#	endif
	#endif

	#if LCD_HD44780_PIN_MULTI_MODE
		if (interface_dl_is_full) {
			_info.flags |= _HD44780_CONF_IDL_8BIT;

			_lcd_send(&_info, _HD44780_INIT_8_1_CMD);
			_delay_ms(HD44780_INIT_1_MS);

			_lcd_send(&_info, _HD44780_INIT_8_2_CMD);
			_delay_us(HD44780_INIT_2_US);

			_lcd_send(&_info, _HD44780_INIT_8_3_CMD);
			_delay_us(HD44780_INIT_3_US);

			_info.data_shift = 0;
			set_flags |= HD44780_DL_8BIT;
		} else {
			_lcd_send(&_info, _HD44780_INIT_4_1_CMD);
			_delay_ms(HD44780_INIT_1_MS);

			_lcd_send(&_info, _HD44780_INIT_4_2_CMD);
			_delay_us(HD44780_INIT_2_US);

			_lcd_send(&_info, _HD44780_INIT_4_3_CMD);
			_delay_us(HD44780_INIT_3_US);

			_lcd_send(&_info, _HD44780_INIT_4_4_CMD);
			_delay_us(HD44780_INIT_4_4_US);

			_info.data_shift = config->data_shift;
			set_flags |= HD44780_DL_4BIT;
			_info.flags |= _HD44780_CONF_IDL_4BIT;
		}
		if (is_read_enable) {
			_info.flags |= _HD44780_CONF_READ_ON;
		}
	#else
	#	if LCD_HD44780_PIN_IDL_8BIT
			_lcd_send(_HD44780_INIT_8_1_CMD);
			_delay_ms(HD44780_INIT_1_MS);

			_lcd_send(_HD44780_INIT_8_2_CMD);
			_delay_us(HD44780_INIT_2_US);

			_lcd_send(_HD44780_INIT_8_3_CMD);
			_delay_us(HD44780_INIT_3_US);

			set_flags |= HD44780_DL_8BIT;
	#	else
			_lcd_send(_HD44780_INIT_4_1_CMD);
			_delay_ms(HD44780_INIT_1_MS);

			_lcd_send(_HD44780_INIT_4_2_CMD);
			_delay_us(HD44780_INIT_2_US);

			_lcd_send(_HD44780_INIT_4_3_CMD);
			_delay_us(HD44780_INIT_3_US);

			_lcd_send(_HD44780_INIT_4_4_CMD);
			_delay_us(HD44780_INIT_4_4_US);

			set_flags |= HD44780_DL_4BIT;
	#	endif
	#endif

	lcd_func_set(__LCD_MULTIMODE_ONLY_VAR_BY_REF_WITH_COMMA(info) set_flags);
	#if LCD_HD44780_PIN_MULTI_MODE
		if (!is_read_enable) {
			_delay_us(HD44780_INIT_OTHER_ADD_US);
		}
	#else
	#	if !LCD_HD44780_PIN_ALLOW_RW
			_delay_us(HD44780_INIT_OTHER_ADD_US);
	#	endif
	#endif

	lcd_display_ctrl(__LCD_MULTIMODE_ONLY_VAR_BY_REF_WITH_COMMA(info) HD44780_D_OFF | HD44780_C_OFF | HD44780_B_OFF);
	#if LCD_HD44780_PIN_MULTI_MODE
		if (!is_read_enable) {
			_delay_us(HD44780_INIT_OTHER_ADD_US);
		}
	#else
	#	if !LCD_HD44780_PIN_ALLOW_RW
			_delay_us(HD44780_INIT_OTHER_ADD_US);
	#	endif
	#endif

	_delay_us(1500);

	lcd_clear(__LCD_MULTIMODE_ONLY_VAR_BY_REF(info));
	#if LCD_HD44780_PIN_MULTI_MODE
		if (!is_read_enable) {
			_delay_us(HD44780_INIT_OTHER_ADD_US);
		}
	#else
	#	if !LCD_HD44780_PIN_ALLOW_RW
			_delay_us(HD44780_INIT_OTHER_ADD_US);
	#	endif
	#endif

	lcd_entry_mode(__LCD_MULTIMODE_ONLY_VAR_BY_REF_WITH_COMMA(info) (flag_is_set(config->flags, __HD44780_INIT_MOV_DIR_BIT) ? HD44780_ID_INC : HD44780_ID_DEC) | (flag_is_set(config->flags, __HD44780_INIT_SHIFT_BIT) ? HD44780_S_ON : HD44780_S_OFF));
	#if LCD_HD44780_PIN_MULTI_MODE
		if (!is_read_enable) {
			_delay_us(HD44780_INIT_OTHER_ADD_US);
		}
	#else
	#	if !LCD_HD44780_PIN_ALLOW_RW
			_delay_us(HD44780_INIT_OTHER_ADD_US);
	#	endif
	#endif

	if (flag_is_set(config->flags, __HD44780_INIT_DISP_BIT)) {
		lcd_display_ctrl(__LCD_MULTIMODE_ONLY_VAR_BY_REF_WITH_COMMA(info) HD44780_D_ON | (flag_is_set(config->flags, __HD44780_INIT_CURSOR_BIT) ? HD44780_C_ON : HD44780_C_OFF) | (flag_is_set(config->flags, __HD44780_INIT_BLINKING_BIT) ? HD44780_B_ON : HD44780_B_OFF));
	}
	#if LCD_HD44780_PIN_MULTI_MODE
	return _info;
	#endif
}

void lcd_clear(__LCD_MULTIMODE_ONLY_INFO_ARG(info)) {
	_lcd_long_command(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) _HD44780_CLEAR);
}

void lcd_home(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const uint8_t flags) {
	_lcd_long_command(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) _HD44780_HOME | (flags & _HD44780_HOME_MASK));
}

void lcd_entry_mode(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const uint8_t flags) {
	_lcd_command(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) _HD44780_ENTRY | (flags & _HD44780_ENTRY_MASK));
}

void lcd_display_ctrl(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const uint8_t flags) {
	_lcd_command(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) _HD44780_DISPLAY | (flags & _HD44780_DISPLAY_MASK));
}

void lcd_cursor(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const uint8_t flags) {
	_lcd_command(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) _HD44780_CURSOR | (flags & _HD44780_CURSOR_MASK));
}

void lcd_func_set(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const uint8_t flags) {
	_lcd_command(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) _HD44780_FUNC | (flags & _HD44780_FUNC_MASK));
}

void lcd_cgr_adr(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const uint8_t flags) {
	_lcd_command(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) _HD44780_CGRAM | (flags & _HD44780_CGRAM_MASK));
}

void lcd_ddr_adr(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const uint8_t flags) {
	_lcd_command(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) _HD44780_DDRAM | (flags & _HD44780_DDRAM_MASK));
}

void lcd_set_pos(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const lcd_line_t line, const uint8_t pos) {
	#if LCD_HD44780_PIN_MULTI_MODE
	// TODO 40X4 support
	switch(_info->row_cout) {
		case 1:
			lcd_ddr_adr(_info, __INFO_ROW_1_ADDR + pos);
			return;
		case 2:
	#		pragma GCC diagnostic push
	#		pragma GCC diagnostic ignored "-Wswitch"
			switch(line) {
				case LCD_ROW_1:
					lcd_ddr_adr(_info, __INFO_ROW_1_ADDR + pos);
					return;
				case LCD_ROW_2:
					lcd_ddr_adr(_info, __INFO_ROW_2_ADDR + pos);
					return;
			}
	#		pragma GCC diagnostic pop
			return;
		case 4:
			switch(line) {
				case LCD_ROW_1:
					lcd_ddr_adr(_info, __INFO_ROW_1_ADDR + pos);
					return;
				case LCD_ROW_2:
					lcd_ddr_adr(_info, __INFO_ROW_2_ADDR + pos);
					return;
				case LCD_ROW_3:
					lcd_ddr_adr(_info, __INFO_ROW_3_ADDR + pos);
					return;
				case LCD_ROW_4:
					lcd_ddr_adr(_info, __INFO_ROW_4_ADDR + pos);
					return;
			}
			return;
	};
	#else
	// TODO 40X4 support

	#	if __INFO_ROW_COUT == 1
			lcd_ddr_adr(__INFO_ROW_1_ADDR + pos);
	#	else
	#		pragma GCC diagnostic push
	#		pragma GCC diagnostic ignored "-Wswitch"
			switch(line) {
				case LCD_ROW_1:
					lcd_ddr_adr(__INFO_ROW_1_ADDR + pos);
					return;
	#			if __INFO_ROW_COUT >= 2
				case LCD_ROW_2:
					lcd_ddr_adr(__INFO_ROW_2_ADDR + pos);
					return;
	#			endif
	#			if __INFO_ROW_COUT >= 3
				case LCD_ROW_3:
					lcd_ddr_adr(__INFO_ROW_3_ADDR + pos);
					return;
	#			endif
	#			if __INFO_ROW_COUT >= 4
				case LCD_ROW_4:
					lcd_ddr_adr(__INFO_ROW_4_ADDR + pos);
					return;
	#			endif
			}
	#		pragma GCC diagnostic pop
	#	endif
	#endif
}

void lcd_line(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const char str[], const lcd_line_t line, const uint8_t start_pos) {
	lcd_set_pos(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) line, 0);
	uint8_t fill_pos = start_pos;
	uint8_t spring_pos = 0;
	for(uint8_t pos = __INFO_COL_COUT; pos != 0; pos--) {
		if (fill_pos != 0) {
			lcd_byte(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) ' ');
			fill_pos--;
		} else {
			if (str[spring_pos] != '\0') {
				lcd_byte(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) str[spring_pos]);
				spring_pos++;
			} else {
				lcd_byte(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) ' ');
			}
		}
	}
}

void lcd_print(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const char str[]) {
	for(uint8_t pos = 0; str[pos] != '\0'; pos++) {
		if (str[pos] == '\n') {
			continue;
		}
		lcd_byte(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) str[pos]);
	}
}

bool _go_next_line(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) lcd_line_t* line, byte_t* line_remnant) {
	*line_remnant = __INFO_COL_COUT;
	switch(*line) {
		case LCD_ROW_1:
			*line = LCD_ROW_2;
			break;
		case LCD_ROW_2:
			*line = LCD_ROW_3;
			break;
		case LCD_ROW_3:
			*line = LCD_ROW_4;
			break;
		case LCD_ROW_4:
			return false;
	}
	if ((*line) > (__INFO_ROW_COUT - 1)) {
		return false;
	}
	return true;
}

void lcd_refresh_ml(__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info) const char str[]) {
	byte_t max_count = __INFO_ROW_COUT * __INFO_COL_COUT;
	lcd_line_t line = LCD_ROW_1;
	lcd_ddr_adr(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) __INFO_ROW_1_ADDR); // It's faster, then lcd_set_pos([info,] line, 0)
	byte_t counter = max_count;
	byte_t line_remnant = __INFO_COL_COUT;
	for(uint8_t pos = 0; counter && str[pos] != '\0'; pos++) {
		if (!max_count) {
			break;
		}
		if (!line_remnant) {
			if (!_go_next_line(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) &line, &line_remnant)) {
				lcd_set_pos(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) line, 0);
				break;
			}
		}
		if (str[pos] == '\n') {
			for (; line_remnant; line_remnant--) {
				lcd_byte(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) ' ');
				counter--;
			}
			if (!_go_next_line(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) &line, &line_remnant)) {
				lcd_set_pos(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) line, 0);
				break;
			}
			continue;
		}
		lcd_byte(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) str[pos]);
		counter--;
		line_remnant--;
	}
	for (; line_remnant; line_remnant--) {
		lcd_byte(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) ' ');
		counter--;
	}
	while (_go_next_line(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) &line, &line_remnant)) {
		lcd_line(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) "", line, 0);
	}
}

#if LCD_HD44780_PIN_MULTI_MODE || LCD_HD44780_PIN_ALLOW_RW
static byte_t _lcd_read_byte(
						__LCD_MULTIMODE_ONLY_INFO_ARG_WITH_COMMA(info)
						__LCD_MULTIMODE_ONLY_BOOL_ARG(is_8bit)
					) {
	#if LCD_HD44780_PIN_MULTI_MODE
		pin_on(*(_info->e_port), _info->e_pin);
	#else
		PIN_ON(LCD_HD44780_PIN_E_PORT, LCD_HD44780_PIN_E_PIN);
	#endif
	_delay_us(HD44780_ENABLE_PULSE_US);
	byte_t rdata;
	#if LCD_HD44780_PIN_MULTI_MODE
		if (_is_8bit) {
			rdata = read_byte(*(_info->data_pin));
		} else {
			rdata = (port_read(*(_info->data_pin), _info->port_mask) >> _info->data_shift) << 4; // read upper nibble
			pin_off(*(_info->e_port), _info->e_pin);
			_delay_us(HD44780_ENABLE_PULSE_US);

			pin_on(*(_info->e_port), _info->e_pin);
			_delay_us(HD44780_ENABLE_PULSE_US);
			rdata |= port_read(*(_info->data_pin), _info->port_mask) >> _info->data_shift; //read lower nibble
		}
	#else
	#	if LCD_HD44780_PIN_IDL_8BIT
			rdata = READ_BYTE(LCD_HD44780_PIN_DATA_PORT);
	#	else
			rdata = (PORT_READ(LCD_HD44780_PIN_DATA_PORT, __INFO_PORT_MASK) >> __INFO_DATA_SHIFT) << 4; // read upper nibble
			PIN_OFF(LCD_HD44780_PIN_E_PORT, LCD_HD44780_PIN_E_PIN);
			_delay_us(HD44780_ENABLE_PULSE_US);

			PIN_ON(LCD_HD44780_PIN_E_PORT, LCD_HD44780_PIN_E_PIN);
			_delay_us(HD44780_ENABLE_PULSE_US);
			rdata |= PORT_READ(LCD_HD44780_PIN_DATA_PORT, __INFO_PORT_MASK) >> __INFO_DATA_SHIFT; //read lower nibble
	#	endif
	#endif
	#if LCD_HD44780_PIN_MULTI_MODE
		pin_off(*(_info->e_port), _info->e_pin);
	#else
		PIN_OFF(LCD_HD44780_PIN_E_PORT, LCD_HD44780_PIN_E_PIN);
	#endif
	_delay_us(HD44780_ENABLE_PULSE_US);
	return rdata;
}

byte_t lcd_read_busy_and_addr(__LCD_MULTIMODE_ONLY_INFO_ARG(info)) {
	#if LCD_HD44780_PIN_MULTI_MODE
		port_to_read_pu(*(_info->data_ddr), *(_info->data_port), _info->port_mask);
		pin_off(*(_info->rs_port), _info->rs_pin);
		pin_on(*(_info->rw_port), _info->rw_pin);

		bool _is_8bit = flag_is_set(_info->flags, __HD44780_CONF_IDL_BIT);
	#else
		PORT_TO_READ_PU(LCD_HD44780_PIN_DATA_PORT, __INFO_PORT_MASK);
		PIN_OFF(LCD_HD44780_PIN_RS_PORT, LCD_HD44780_PIN_RS_PIN);
		PIN_ON(LCD_HD44780_PIN_RW_PORT, LCD_HD44780_PIN_RW_PIN);
	#endif
	bool is_buisy;
	byte_t rdata;
	do {
		rdata = _lcd_read_byte(__LCD_MULTIMODE_ONLY_VAR_WITH_COMMA(info) __LCD_MULTIMODE_ONLY_VAR(is_8bit));
		is_buisy = flag_is_set(rdata, __HD44780_BF_BIT);
		#if HD44780_WAIT_BF_LOOP_US
		if (is_buisy) {
			_delay_us(HD44780_WAIT_BF_LOOP_US);
		}
		#endif
	} while (is_buisy);

	#if LCD_HD44780_PIN_MULTI_MODE
		pin_off(*(_info->rw_port), _info->rw_pin);
		port_to_write(*(_info->data_ddr), _info->port_mask);
		pin_on(*(_info->rs_port), _info->rs_pin);// Default on - data
	#else
		PIN_OFF(LCD_HD44780_PIN_RW_PORT, LCD_HD44780_PIN_RW_PIN);
		PORT_TO_WRITE(LCD_HD44780_PIN_DATA_PORT, __INFO_PORT_MASK);
		PIN_ON(LCD_HD44780_PIN_RS_PORT, LCD_HD44780_PIN_RS_PIN);// Default on - data
	#endif
	return rdata & _HD44780_ADDR_MASK;
}

byte_t lcd_read_data(__LCD_MULTIMODE_ONLY_INFO_ARG(info)) {
	#if LCD_HD44780_PIN_MULTI_MODE
	port_to_read_pu(*(_info->data_ddr), *(_info->data_port), _info->port_mask);
	pin_on(*(_info->rw_port), _info->rw_pin);

	byte_t rdata = _lcd_read_byte(_info, flag_is_set(_info->flags, __HD44780_CONF_IDL_BIT));

	pin_off(*(_info->rw_port), _info->rw_pin);
	port_to_write(*(_info->data_ddr), _info->port_mask);
	#else
	PORT_TO_READ_PU(LCD_HD44780_PIN_DATA_PORT, __INFO_PORT_MASK);
	PIN_ON(LCD_HD44780_PIN_RW_PORT, LCD_HD44780_PIN_RW_PIN);

	byte_t rdata = _lcd_read_byte();

	PIN_OFF(LCD_HD44780_PIN_RW_PORT, LCD_HD44780_PIN_RW_PIN);
	PORT_TO_WRITE(LCD_HD44780_PIN_DATA_PORT, __INFO_PORT_MASK);
	#endif
	return rdata;
}
#endif // Read
