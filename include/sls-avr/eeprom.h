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
 * \file		sls-avr/eeprom.h
 * \brief		AVR EEPROM helper.
 * \code
 * #include <sls-avr/eeprom.h>
 * \endcode
 */

#ifndef SLS_AVR_EEPROM_H_
#define SLS_AVR_EEPROM_H_

#include <avr/eeprom.h>
//#include <sls-avr/avr.h>

typedef	void *					eeprom_adr_t;

/**
 * \brief Reads a string from EEPROM.
 * \param[out] str	destination string buffer
 * \param[in] adr		EEPROM address
 * \param[in] sz		number of characters to read
 * \remark The size of the string buffer \p str should be at least (\p sz + 1)!
 */
static inline void eeprom_read_str(char str[], const eeprom_adr_t adr, const size_t sz) {
	for (size_t sz_counter = 0; sz_counter < sz; ++sz_counter) {
		str[sz_counter] = eeprom_read_byte(adr + sz_counter);
		if (!str[sz_counter]) {
			break;
		}
	}
	str[sz] = '\0'; //Always - it's faster then check
}

/**
 * \brief eeprom_read_block wrapper
 * \param[out] data	destination data address
 * \param[in] adr		EEPROM address
 * \param[in] sz		number of bytes to read
 * \remark See https://www.nongnu.org/avr-libc/user-manual/group__avr__eeprom.html
 */
static inline void eeprom_read(void *const data, const eeprom_adr_t adr, const size_t sz) {
	eeprom_read_block(data, adr, sz);
}

/**
 * \brief Writes a string to EEPROM.
 * \param[in] str		source string
 * \param[out] adr	EEPROM address
 * \param[in] sz		number of characters to write
 * \remark In order not to write an extra byte, the writed characters length \p sz can be equal to the length of the \p str string(terminal null will not be written), but then it needs to use the #eeprom_read_str function to correctly read it.
 */
static inline void eeprom_write_str(const char str[], eeprom_adr_t adr, const size_t sz) {
	for (size_t sz_counter = 0; sz_counter < sz; ++sz_counter) {
		eeprom_update_byte(adr + sz_counter, str[sz_counter]);
		if (!str[sz_counter]) {
			break;
		}
	}
}

/**
 * \brief eeprom_update_block wrapper
 * \param[in] data		source data address
 * \param[out] adr	EEPROM address
 * \param[in] sz		number of bytes to read
 * \remark See https://www.nongnu.org/avr-libc/user-manual/group__avr__eeprom.html
 */
static inline void eeprom_write(const void *const data, eeprom_adr_t adr, const size_t sz) {
	eeprom_update_block(data, adr, sz);
}

#endif // SLS_AVR_EEPROM_H_
