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
 * \file		sls-avr/defs.h
 * \brief		AVR common types and functions.
 */
#ifndef SLS_AVR_DEFS_H_
#define SLS_AVR_DEFS_H_

#ifndef SLS_AVR_AVR_H_
#  error "Include <sls-avr/avr.h> instead of this file."
#endif

typedef unsigned char byte_t;
typedef struct {
	byte_t lo : 4;
	byte_t up : 4;
} nibble_t;
typedef struct {
	byte_t b0 : 1;
	byte_t b1 : 1;
	byte_t b2 : 1;
	byte_t b3 : 1;
	byte_t b4 : 1;
	byte_t b5 : 1;
	byte_t b6 : 1;
	byte_t b7 : 1;
} flags_t;

typedef union {
	byte_t byte;
	nibble_t nibble;
	flags_t flags;
} byte_flags_t;

/** \brief The type for specifying the pin bit. It is defined to ensure that the port bit is being transmitted. */
typedef byte_t pin_bit_t;
typedef byte_t port_mask_t;
typedef volatile byte_t *const ddr_t;
typedef volatile byte_t *const port_t;
typedef volatile byte_t *const pin_t;

/**
Ref example:

void init_ddr(ddr_t ddr, ddr_state state) {
	*ddr = state;
}

init_ddr(&DDRA, 0xFF);

*/

// Creating missing references
#define pin_2_ddr(_ref)		*((_ref) + 1)
#define pin_2_port(_ref)	*((_ref) + 2)

#define ddr_2_pin(_ref)		*((_ref) - 1)
#define ddr_2_port(_ref)	*((_ref) + 1)

#define port_2_ddr(_ref)	*((_ref) - 1)
#define port_2_pin(_ref)	*((_ref) - 2)

/**
Convert example:

void init_ddr(port_t port) {
	port_2_ddr(port) = 0xF0;
	*port = 0x0F;
	byte_t ri = port_2_pin(port);
}

init_ddr(&DDRA, 0xFF);

*/

#define NIBBLE_SWAP(_ch) ((_ch << 4) | (_ch >> 4))
#if (__BUILTIN_AVR_SWAP == 1)
#	define nibble_swap(_ch) __builtin_avr_swap((_ch))
#else
#	define nibble_swap(_ch) NIBBLE_SWAP((_ch))
#endif // __BUILTIN_AVR_SWAP

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
 * \brief Make port mask
 * \return Port mask
 */
#define make_port_mask1(_p0)									(_BV((_p0)))
#define make_port_mask2(_p0, _p1)								(_BV((_p0)) & _BV((_p1)))
#define make_port_mask3(_p0, _p1, _p2)							(_BV((_p0)) & _BV((_p1)) & _BV((_p2)))
#define make_port_mask4(_p0, _p1, _p2, _p3)						(_BV((_p0)) & _BV((_p1)) & _BV((_p2)) & _BV((_p3)))
#define make_port_mask5(_p0, _p1, _p2, _p3, _p4)				(_BV((_p0)) & _BV((_p1)) & _BV((_p2)) & _BV((_p3)) & _BV((_p4)))
#define make_port_mask6(_p0, _p1, _p2, _p3, _p4, _p5)			(_BV((_p0)) & _BV((_p1)) & _BV((_p2)) & _BV((_p3)) & _BV((_p4)) & _BV((_p5)))
#define make_port_mask7(_p0, _p1, _p2, _p3, _p4, _p5, _p6)		(_BV((_p0)) & _BV((_p1)) & _BV((_p2)) & _BV((_p3)) & _BV((_p4)) & _BV((_p5)) & _BV((_p6)))
#define make_port_mask8(_p0, _p1, _p2, _p3, _p4, _p5, _p6, _p7)	(_BV((_p0)) & _BV((_p1)) & _BV((_p2)) & _BV((_p3)) & _BV((_p4)) & _BV((_p5)) & _BV((_p6)) & _BV((_p7)))

#endif // SLS_AVR_DEFS_H_
