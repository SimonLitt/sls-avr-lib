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
 * \file		sls-avr/defs.h
 * \brief		AVR common types and functions.
 *
 * \code
 * //Ref example:
 * void init_ddr(ddr_t ddr, ddr_state state) {
 *		*ddr = state;
 * }
 *
 * int main(void) {
 *		...
 *		init_ddr(&DDRA, 0xFF);
 * 		...
 * }
 * \endcode
 *
 * \code
 * //Convert example:
 * void init_ddr(port_t port) {
 *		port_2_ddr(port) = 0xF0;
 *		*port = 0x0F;
 *		byte_t ri = port_2_pin(port);
 * }
 *
 * int main(void) {
 *		...
 *		init_ddr(&DDRA, 0xFF);
 *		...
 * }
 * \endcode
 */
#include <stdint.h>

#ifndef SLS_AVR_DEFS_H_
#	define SLS_AVR_DEFS_H_

#ifndef SLS_AVR_AVR_H_
#	error "Include <sls-avr/avr.h> instead of this file."
#endif

typedef uint8_t byte_t; /**< \brief 8-bit type */

/** \brief Structure for working with upper and lower nibbles */
typedef struct {
	byte_t lo : 4; /**< \brief The lower nibble */
	byte_t up : 4; /**< \brief The upper nibble */
} nibble_t;

/** \brief Structure for working with bits */
typedef struct {
	byte_t b0 : 1; /**< \brief The lowest 0-bit */
	byte_t b1 : 1; /**< \brief The 1-bit */
	byte_t b2 : 1; /**< \brief The 2-bit */
	byte_t b3 : 1; /**< \brief The 3-bit */
	byte_t b4 : 1; /**< \brief The 4-bit */
	byte_t b5 : 1; /**< \brief The 5-bit */
	byte_t b6 : 1; /**< \brief The 6-bit */
	byte_t b7 : 1; /**< \brief The highest 7-bit */
} flags_t;

/** \brief Universal type for byte */
typedef union {
	byte_t byte;		/**< \brief Directly byte */
	nibble_t nibble;	/**< \brief Nibbles */
	flags_t flags;		/**< \brief Bits */
} byte_flags_t;

typedef byte_t pin_bit_t;	/**< \brief The type for specifying the pin bit. \details This is defined to transmit the port bit. */
typedef byte_t port_mask_t;	/**< \brief The type for specifying the port mask. \details It is defined to transmit the port mask. */
typedef volatile byte_t *const ddr_t;	/**< \brief Type for passing a reference to a direct register. */
typedef volatile byte_t *const port_t;	/**< \brief Type for passing a reference to a port register. */
typedef volatile byte_t *const pin_t;	/**< \brief Type for passing a reference to a pin register. */

// ---------------------------------------------------------------------------+
// Creating missing references
// ---------------------------------------------------------------------------+

#define pin_2_ddr(_ref)		*((_ref) + 1) /**< \brief Calculates the direct register from the pin register. */
#define pin_2_port(_ref)	*((_ref) + 2) /**< \brief Calculates the port register from the pin register. */

#define ddr_2_pin(_ref)		*((_ref) - 1) /**< \brief Calculates the pin register from the direct register. */
#define ddr_2_port(_ref)	*((_ref) + 1) /**< \brief Calculates the port register from the direct register. */

#define port_2_ddr(_ref)	*((_ref) - 1) /**< \brief Calculates the direct register from the port register. */
#define port_2_pin(_ref)	*((_ref) - 2) /**< \brief Calculates the pin register from the port register. */

// ---------------------------------------------------------------------------+
// Helpers
// ---------------------------------------------------------------------------+
/**
 * \brief Swaps the high and low nibbles (half bytes) of a byte.
 * \param _b	The byte.
 * \return Modified byte
 */
#define NIBBLE_SWAP(_b)		(((_b) << 4) | ((_b) >> 4))

/**
 * \brief Swaps the high and low nibbles (half bytes) of a byte.
 * \details If available, uses the SWAP instruction.
 * \param byte	The byte.
 * \return Modified byte
 */
static inline byte_t nibble_swap(byte_t byte) {
	return
	#if (__BUILTIN_AVR_SWAP == 1)
		__builtin_avr_swap(byte);
	#else
		NIBBLE_SWAP(byte);
	#endif // __BUILTIN_AVR_SWAP
}

/**
 * \brief Test whether bit \c _b in flags \c _val is set.
 * \param _val	The flags value.
 * \param _b	The flag bit.
 * \remark For working with registers, use `bit_is_set()` from \<avr/sfr_defs.h\>.
*/
#define flag_is_set(_val, _b) ((_val) & _BV((_b)))

/**
 * \brief Test whether bit \c _b in flags \c _val is set.
 * \param _val	The flags value.
 * \param _b	The flag bit.
 * \remark For working with registers, use `bit_is_set()` from \<avr/sfr_defs.h\>.
 */
#define flag_is_clear(_val, _b) (!((_val) & _BV((_b))))

/**
 * \brief Makes port mask
 * \return Port mask
 */
#define make_port_mask1(_p0)									(_BV((_p0)))

/**
 * \brief Makes port mask
 * \return Port mask
 */
#define make_port_mask2(_p0, _p1)								(_BV((_p0)) & _BV((_p1)))

/**
 * \brief Makes port mask
 * \return Port mask
 */
#define make_port_mask3(_p0, _p1, _p2)							(_BV((_p0)) & _BV((_p1)) & _BV((_p2)))

/**
 * \brief Makes port mask
 * \return Port mask
 */
#define make_port_mask4(_p0, _p1, _p2, _p3)						(_BV((_p0)) & _BV((_p1)) & _BV((_p2)) & _BV((_p3)))

/**
 * \brief Makes port mask
 * \return Port mask
 */
#define make_port_mask5(_p0, _p1, _p2, _p3, _p4)				(_BV((_p0)) & _BV((_p1)) & _BV((_p2)) & _BV((_p3)) & _BV((_p4)))

/**
 * \brief Makes port mask
 * \return Port mask
 */
#define make_port_mask6(_p0, _p1, _p2, _p3, _p4, _p5)			(_BV((_p0)) & _BV((_p1)) & _BV((_p2)) & _BV((_p3)) & _BV((_p4)) & _BV((_p5)))

/**
 * \brief Makes port mask
 * \return Port mask
 */
#define make_port_mask7(_p0, _p1, _p2, _p3, _p4, _p5, _p6)		(_BV((_p0)) & _BV((_p1)) & _BV((_p2)) & _BV((_p3)) & _BV((_p4)) & _BV((_p5)) & _BV((_p6)))

/**
 * \brief Makes port mask
 * \return Port mask
 */
#define make_port_mask8(_p0, _p1, _p2, _p3, _p4, _p5, _p6, _p7)	(_BV((_p0)) & _BV((_p1)) & _BV((_p2)) & _BV((_p3)) & _BV((_p4)) & _BV((_p5)) & _BV((_p6)) & _BV((_p7)))

#endif // SLS_AVR_DEFS_H_
