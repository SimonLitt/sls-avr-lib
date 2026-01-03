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
 * \file		sls-avr/gpio.h
 * \brief		AVR port register helpers.
 *
 * \details
 * Function naming convention:
 * 		\li \c	gpio_xxx(GPIO_XXX) - the entire port
 * 		\li \c	port_xxx(PORT_XXX) - the port pin set
 * 		\li \c	nibble_lo_xxx(NIBBLE_LO_XXX) - the lower nibble pin set
 *		\li \c	nibble_up_xxx(NIBBLE_HI_XXX) - the upper nibble pin set
 *		\li \c	pin_xxx(PIN_XXX) - the distinct pin
 *
 * Parameters naming convention:
 * 		\li \c	_ddr - AVR Data Direction Register
 * 		\li \c	_port - AVR PORTx Register
 * 		\li \c	_pin - AVR PINx Register
 * 		\li \c	_p - the port name (single char). For example С for DDRC,
 * 				PORTC or for PINC
 * 		\li \c	_b - the port bit as numder from 0 to 7 or as definded macro
 * 				e.g. PC3
 * 		\li \c	_pinset - the port bit set
 * 		\li \c	_val - the transmitted value
 *
 * \code
 * #include <sls-avr/avr.h>
 * int main(void) {
 *		...
 *		GPIO_SET(A, 0xF0);
 *		PORT_SET(A, 0b10100000);
 *		GPIO_SET_OUT_D_HI(B);
 *		PIN_TO_READ(C, PC3);
 *		...
 * }
 * \endcode
 *
 * \code
 * #include <sls-avr/avr.h>
 * int main(void) {
 *		...
 *		gpio_set(DDRA, 0xF0);
 *		port_set(PORTA, 0b10100000);
 *		gpio_set_out_d_hi(DDRB, PORTB);
 *		pin_to_read(DDRC, PC3);
 *		...
 * }
 * \endcode
 * \remark 	Many aliases are defined. They should be used in a way that
 * makes the code self-documenting. For example `gpio_pull_up` makes sense
 * when the AVR port is in input mode. Otherwise, it need to use
 * `gpio_set_hi`.
 */
#ifndef SLS_AVR_GPIO_H_
#define SLS_AVR_GPIO_H_

#ifndef SLS_AVR_AVR_H_
#  error "Include <sls-avr/avr.h> instead of this file."
#endif

#include <sls-common/defines.h>

/** \brief Make PORTx register by by port letter */
#define MAKE_PORT_NAME(_p)		MAKE_GLUE_X2(PORT, _p)
/** \brief Make DDRx register by by port letter */
#define MAKE_DDR_NAME(_p)		MAKE_GLUE_X2(DDR, _p)
/** \brief Make PINx register by by port letter */
#define MAKE_PIN_NAME(_p)		MAKE_GLUE_X2(PIN, _p)

/** \brief No pins selected */
#define MAKE_MASK_x0									0x00
/** \brief Creates a port mask from a single pin bit */
#define MAKE_MASK_x1									_BV
/** \brief Creates a port mask from two pin bits */
#define MAKE_MASK_x2(_b1, _b2)							(_BV((_b1)) | _BV((_b2)))
/** \brief Creates a port mask using three pin bits */
#define MAKE_MASK_x3(_b1, _b2, _b3)						(_BV((_b1)) | _BV((_b2)) | _BV((_b3)))
/** \brief Creates a port mask from four pin bits */
#define MAKE_MASK_x4(_b1, _b2, _b3, _b4)				(_BV((_b1)) | _BV((_b2)) | _BV((_b3)) | _BV((_b4)))
/** \brief Creates a port mask from five pin bits */
#define MAKE_MASK_x5(_b1, _b2, _b3, _b4, _b5)			(_BV((_b1)) | _BV((_b2)) | _BV((_b3)) | _BV((_b4)) | _BV((_b5)))
/** \brief Creates a port mask from six pin bits */
#define MAKE_MASK_x6(_b1, _b2, _b3, _b4, _b5, _b6)		(_BV((_b1)) | _BV((_b2)) | _BV((_b3)) | _BV((_b4)) | _BV((_b5)) | _BV((_b6)))
/** \brief Creates a port mask from seven pin bits */
#define MAKE_MASK_x7(_b1, _b2, _b3, _b4, _b5, _b6, _b7)	(_BV((_b1)) | _BV((_b2)) | _BV((_b3)) | _BV((_b4)) | _BV((_b5)) | _BV((_b6)) | _BV((_b7)))
/** \brief All port pins(entire port). */
#define MAKE_MASK_x8									0xFF

// ---------------------------------------------------------------------------+
//		The entire port
// ---------------------------------------------------------------------------+
/** \brief Writes the specified value to the DDRx register.
 * \param _ddr	The DDRx register.
 * \param _val	The value being passed.
 */
#define gpio_init(_ddr, _val)						((_ddr) = (_val))
#define GPIO_INIT(_p, _val)							gpio_init(MAKE_DDR_NAME(_p), (_val)) /**< \brief A wrapper for short register naming for #gpio_init() */

/** \brief Writes the specified value to the PORTx register.
 * \param _port	The PORTx register.
 * \param _val	The value being passed.
 */
#define gpio_set(_port, _val)						((_port) = (_val))
#define GPIO_SET(_p, _val)							gpio_set(MAKE_PORT_NAME(_p), (_val)) /**< \brief A wrapper for short register naming for #gpio_set() */


/** \brief Inverts the bits in a PORTx register.
 * \param _port	The PORTx register.
 */
#define gpio_switch(_port)							((_port) = ~(_port))
#define GPIO_SWITCH(_p)								gpio_switch(MAKE_PORT_NAME(_p)) /**< \brief A wrapper for short register naming for #gpio_switch() */

/** \brief Returns PINx register.
 *
 * \param _pin	The PINx register.
 *
 */
#define gpio_byte(_pin)								(_pin)
#define GPIO_BYTE(_p)								gpio_byte(MAKE_PIN_NAME(_p)) /**< \brief A wrapper for short register naming for #gpio_byte() */

/** \brief Sets a entire port to input state.
 * \param _ddr	The DDRx register.
 */
#define gpio_set_in(_ddr)							gpio_init((_ddr), 0x00);
#define GPIO_SET_IN(_p)								gpio_set_in(MAKE_DDR_NAME(_p)) /**< \brief A wrapper for short register naming for #gpio_set_in() */

/** \brief Sets a entire port to high Z input state.
 * \param _ddr	The DDRx register.
 * \param _port	The PORTx register.
 */
#define gpio_set_in_z(_ddr, _port)					gpio_set_in((_ddr)); gpio_set_lo((_port))
#define GPIO_SET_IN_Z(_p)							gpio_set_in_z(MAKE_DDR_NAME(_p), MAKE_PORT_NAME(_p)) /**< \brief A wrapper for short register naming for #gpio_set_in_z() */

/** \brief Sets a entire port to input state with use internal pull-up resistor.
 * \param _ddr	The DDRx register.
 * \param _port	The PORTx register.
 */
#define gpio_set_in_pu(_ddr, _port)					gpio_set_in((_ddr)); gpio_pull_up((_port))
#define GPIO_SET_IN_PU(_p)							gpio_set_in_pu(MAKE_DDR_NAME(_p), MAKE_PORT_NAME(_p)) /**< \brief A wrapper for short register naming for #gpio_set_in_pu() */

/** \brief Sets a entire port to output state.
 * \param _ddr	The DDRx register.
 */
#define gpio_set_out(_ddr)							gpio_init((_ddr), 0xFF);
#define GPIO_SET_OUT(_p)							gpio_set_out(MAKE_DDR_NAME(_p)) /**< \brief A wrapper for short register naming for #gpio_set_out() */

/** \brief Sets port out driving low
 *
 * \param _ddr	The DDRx register.
 * \param _port	The PORTx register.
 *
 */
#define gpio_set_out_d_lo(_ddr, _port)				gpio_set_out((_ddr)); gpio_set_lo((_port))
#define GPIO_SET_OUT_D_LO(_p)						gpio_set_out_d_lo(MAKE_DDR_NAME(_p), MAKE_PORT_NAME(_p)) /**< \brief A wrapper for short register naming for #gpio_set_out_d_lo() */

/** \brief Sets port out driving hi
 *
 * \param _ddr	The DDRx register.
 * \param _port	The PORTx register.
 *
 */
#define gpio_set_out_d_hi(_ddr, _port)				gpio_set_out((_ddr)); gpio_set_hi((_port))
#define GPIO_SET_OUT_D_HI(_p)						gpio_set_out_d_hi(MAKE_DDR_NAME(_p), MAKE_PORT_NAME(_p)) /**< \brief A wrapper for short register naming for #gpio_set_out_d_hi() */

/** \brief Sets entire PORTx register to high state.
 *
 * \param _port	The PORTx register.
 *
 */
#define gpio_set_hi(_port)							gpio_set((_port), 0xFF)
#define GPIO_SET_HI(_p)								gpio_set_hi(MAKE_PORT_NAME(_p)) /**< \brief A wrapper for short register naming for #gpio_set_hi() */

/** \brief Sets entire PORTx register to low state.
 *
 * \param _port	The PORTx register.
 *
 */
#define gpio_set_lo(_port)							gpio_set((_port), 0x00)
#define GPIO_SET_LO(_p)								gpio_set_lo(MAKE_PORT_NAME(_p)) /**< \brief A wrapper for short register naming for #gpio_set_lo() */

// ---------------------------------------------------------------------------+
//		The entire port aliases
// ---------------------------------------------------------------------------+
#define gpio_read									gpio_byte /**< \brief The meaningful name alias for #gpio_byte */
#define GPIO_READ									GPIO_BYTE /**< \brief The meaningful name alias for #GPIO_BYTE */

#define read_byte									gpio_byte /**< \brief The meaningful name alias for #gpio_byte */
#define READ_BYTE									GPIO_BYTE /**< \brief The meaningful name alias for #GPIO_BYTE */

#define gpio_to_read								gpio_set_in /**< \brief The meaningful name alias for #gpio_set_in */
#define GPIO_TO_READ								GPIO_SET_IN /**< \brief The meaningful name alias for #GPIO_SET_IN */

#define gpio_to_read_z								gpio_set_in_z /**< \brief The meaningful name alias for #gpio_set_in_z */
#define GPIO_TO_READ_Z								GPIO_SET_IN_Z /**< \brief The meaningful name alias for #GPIO_SET_IN_Z */

#define gpio_to_read_pu								gpio_set_in_pu /**< \brief The meaningful name alias for #gpio_set_in_pu */
#define GPIO_TO_READ_PU								GPIO_SET_IN_PU /**< \brief The meaningful name alias for #GPIO_SET_IN_PU */

#define gpio_pull_up								gpio_set_hi /**< \brief The meaningful name alias for #gpio_set_hi */
#define GPIO_PULL_UP								GPIO_SET_HI /**< \brief The meaningful name alias for #GPIO_SET_HI */

#define gpio_to_write								gpio_set_out /**< \brief The meaningful name alias for #gpio_set_out */
#define GPIO_TO_WRITE								GPIO_SET_OUT /**< \brief The meaningful name alias for #GPIO_SET_OUT */

#define gpio_to_write_d_lo							gpio_set_out_d_lo /**< \brief The meaningful name alias for #gpio_set_out_d_lo */
#define GPIO_TO_WRITE_D_LO							GPIO_SET_OUT_D_LO /**< \brief The meaningful name alias for #GPIO_SET_OUT_D_LO */

#define gpio_to_write_d_hi							gpio_set_out_d_hi /**< \brief The meaningful name alias for #gpio_set_out_d_hi */
#define GPIO_TO_WRITE_D_HI							GPIO_SET_OUT_D_HI /**< \brief The meaningful name alias for #GPIO_SET_OUT_D_HI */

#define gpio_write									gpio_set /**< \brief The meaningful name alias for #gpio_set */
#define GPIO_WRITE									GPIO_SET /**< \brief The meaningful name alias for #GPIO_SET */

#define write_byte									gpio_set /**< \brief The meaningful name alias for #gpio_set */
#define WRITE_BYTE									GPIO_SET /**< \brief The meaningful name alias for #GPIO_SET */

// ---------------------------------------------------------------------------+
//		The port pin set
// ---------------------------------------------------------------------------+
#define port_set_in(_ddr, _pinset) 					((_ddr) &= ~(_pinset))
#define PORT_SET_IN(_p, _pinset) 					port_set_in(MAKE_DDR_NAME(_p), (_pinset))

#define port_set_out(_ddr, _pinset) 				((_ddr) |= (_pinset))
#define PORT_SET_OUT(_p, _pinset) 					port_set_out(MAKE_DDR_NAME(_p), (_pinset))

#define port_set(_port, _pinset)					((_port) |= (_pinset))
#define PORT_SET(_p, _pinset)						port_set(MAKE_PORT_NAME(_p), (_pinset))

#define port_clear(_port, _pinset)					((_port) &= ~(_pinset))
#define PORT_CLEAR(_p, _pinset)						port_clear(MAKE_PORT_NAME(_p), (_pinset))

#define port_switch(_port, _pinset)					((_port) ^= (_pinset))
#define PORT_SWITCH(_p, _pinset)					port_switch(MAKE_PORT_NAME(_p), (_pinset))

#define port_replace(_port, _pinset, _val)			((_port) = ((_port) & (~(_pinset))) | ((_val) & (_pinset)))
#define PORT_REPLACE(_p, _pinset, _val)				port_replace(MAKE_PORT_NAME(_p), (_pinset), (_val))

#define port_read(_pin, _pinset)					(read_byte((_pin)) & (_pinset))
#define PORT_READ(_p, _pinset)						port_read(MAKE_PIN_NAME(_p), (_pinset))

#define port_set_in_z(_ddr, _port, _pinset)			port_set_in((_ddr), (_pinset)); port_clear((_port), (_pinset))
#define PORT_SET_IN_Z(_p, _pinset)					port_set_in_z(MAKE_DDR_NAME(_p), MAKE_PORT_NAME(_p), (_pinset))

#define port_set_in_pu(_ddr, _port, _pinset)		port_set_in((_ddr), (_pinset)); port_pull_up((_port), (_pinset))
#define PORT_SET_IN_PU(_p, _pinset)					port_set_in_pu(MAKE_DDR_NAME(_p), MAKE_PORT_NAME(_p), (_pinset))

#define port_set_out_d_lo(_ddr, _port, _pinset)		port_set_out((_ddr), (_pinset)); port_clear((_port), (_pinset))
#define PORT_SET_OUT_D_LO(_p, _pinset)				port_set_out_d_lo(MAKE_DDR_NAME(_p), MAKE_PORT_NAME(_p), (_pinset))

#define port_set_out_d_hi(_ddr, _port, _pinset)		port_set_out((_ddr), (_pinset)); port_set((_port), (_pinset))
#define PORT_SET_OUT_D_HI(_p, _pinset)				port_set_out_d_hi(MAKE_DDR_NAME(_p), MAKE_PORT_NAME(_p), (_pinset))

// ---------------------------------------------------------------------------+
//		The port pin set aliases
// ---------------------------------------------------------------------------+
#define port_set_hi									port_set
#define PORT_SET_HI									PORT_SET

#define port_pull_up								port_set
#define PORT_PULL_UP								PORT_SET

#define port_set_lo									port_clear
#define PORT_SET_LO									PORT_CLEAR

#define port_to_read								port_set_in
#define PORT_TO_READ								PORT_SET_IN

#define port_to_read_pu								port_set_in_pu
#define PORT_TO_READ_PU								PORT_SET_IN_PU

#define port_to_read_z								port_set_in_z
#define PORT_TO_READ_Z								PORT_SET_IN_Z

#define port_to_write								port_set_out
#define PORT_TO_WRITE								PORT_SET_OUT

#define port_write									port_replace
#define PORT_WRITE									PORT_REPLACE

#define port_to_write_d_lo							port_set_out_d_lo
#define PORT_TO_WRITE_D_LO							PORT_SET_OUT_D_LO

#define port_to_write_d_hi							port_set_out_d_hi
#define PORT_TO_WRITE_D_HI							PORT_SET_OUT_D_HI

#define NIBBLE_LO_PINSET							0x0F /**< \brief The lower nibble port mask */

#define nibble_lo_set_in(_ddr) 						port_set_in((_ddr), NIBBLE_LO_PINSET)
#define NIBBLE_LO_SET_IN(_p) 						nibble_lo_set_in(MAKE_DDR_NAME(_p))

#define nibble_lo_set_out(_ddr) 					port_set_out((_ddr), NIBBLE_LO_PINSET)
#define NIBBLE_LO_SET_OUT(_p) 						nibble_lo_set_out(MAKE_DDR_NAME(_p))

#define nibble_lo_set(_port)						port_set((_port), NIBBLE_LO_PINSET)
#define NIBBLE_LO_SET(_p)							nibble_lo_set(MAKE_PORT_NAME(_p))

#define nibble_lo_clear(_port)						port_clear((_port), NIBBLE_LO_PINSET)
#define NIBBLE_LO_CLEAR(_p)							nibble_lo_clear(MAKE_PORT_NAME(_p))

#define nibble_lo_switch(_port)						port_switch((_port), NIBBLE_LO_PINSET)
#define NIBBLE_LO_SWITCH(_p)						nibble_lo_switch(MAKE_PORT_NAME(_p)))

#define nibble_lo_replace(_port, _val)				port_replace(MAKE_PORT_NAME(_p), NIBBLE_LO_PINSET, (_val))
#define NIBBLE_LO_REPLACE(_p, _val)					nibble_lo_replace(MAKE_PORT_NAME(_p), (_val))

#define nibble_lo_read(_pin)						port_read((_pin), (NIBBLE_LO_PINSET))
#define NIBBLE_LO_READ(_p)							nibble_lo_read(MAKE_PIN_NAME(_p))

#define nibble_lo_set_in_z(_ddr, _port)				port_set_in_z((_ddr), (_port), NIBBLE_LO_PINSET)
#define NIBBLE_LO_SET_IN_Z(_p)						nibble_lo_set_in_z(MAKE_DDR_NAME(_p), MAKE_PORT_NAME(_p))

#define nibble_lo_set_in_pu(_ddr, _port)			port_set_in_pu((_ddr), (_port), NIBBLE_LO_PINSET)
#define NIBBLE_LO_SET_IN_PU(_p)						nibble_lo_set_in_pu(MAKE_DDR_NAME(_p), MAKE_PORT_NAME(_p))

#define nibble_lo_set_out_d_lo(_ddr, _port)			port_set_out_d_lo((_ddr), (_port), NIBBLE_LO_PINSET)
#define NIBBLE_LO_SET_OUT_D_LO(_p)					nibble_lo_set_out_d_lo(MAKE_DDR_NAME(_p), MAKE_PORT_NAME(_p))

#define nibble_lo_set_out_d_hi(_ddr, _port)			port_set_out_d_hi((_ddr), (_port), NIBBLE_LO_PINSET)
#define NIBBLE_LO_SET_OUT_D_HI(_p)					nibble_lo_set_out_d_hi(MAKE_DDR_NAME(_p), MAKE_PORT_NAME(_p))

// ---------------------------------------------------------------------------+
//		The lower nibble pin set aliases
// ---------------------------------------------------------------------------+
#define nibble_lo_set_hi							nibble_lo_set
#define NIBBLE_LO_SET_HI							NIBBLE_LO_SET

#define nibble_lo_pull_up							nibble_lo_set
#define NIBBLE_LO_PULL_UP							NIBBLE_LO_SET

#define nibble_lo_set_lo							nibble_lo_clear
#define NIBBLE_LO_SET_LO							NIBBLE_LO_CLEAR

#define nibble_lo_to_read							nibble_lo_set_in
#define NIBBLE_LO_TO_READ							NIBBLE_LO_SET_IN

#define nibble_lo_to_read_pu						nibble_lo_set_in_pu
#define NIBBLE_LO_TO_READ_PU						NIBBLE_LO_SET_IN_PU

#define nibble_lo_to_read_z							nibble_lo_set_in_z
#define NIBBLE_LO_TO_READ_Z							NIBBLE_LO_SET_IN_Z

#define nibble_lo_to_write							nibble_lo_set_out
#define NIBBLE_LO_TO_WRITE							NIBBLE_LO_SET_OUT

#define nibble_lo_write								nibble_lo_replace
#define NIBBLE_LO_WRITE								NIBBLE_LO_REPLACE

#define nibble_lo_to_write_d_lo						nibble_lo_set_out_d_lo
#define NIBBLE_LO_TO_WRITE_D_LO						NIBBLE_LO_SET_OUT_D_LO

#define nibble_lo_to_write_d_hi						nibble_lo_set_out_d_hi
#define NIBBLE_LO_TO_WRITE_D_HI						NIBBLE_LO_SET_OUT_D_HI

#define NIBBLE_UP_PINSET							0xF0 /**< \brief The upper nibble port mask */

#define nibble_up_set_in(_ddr) 						port_set_in((_ddr), NIBBLE_UP_PINSET)
#define NIBBLE_UP_SET_IN(_p) 						nibble_up_set_in(MAKE_DDR_NAME(_p))

#define nibble_up_set_out(_ddr) 					port_set_out((_ddr), NIBBLE_UP_PINSET)
#define NIBBLE_UP_SET_OUT(_p) 						nibble_up_set_out(MAKE_DDR_NAME(_p))

#define nibble_up_set(_port)						port_set((_port), NIBBLE_UP_PINSET)
#define NIBBLE_UP_SET(_p)							nibble_up_set(MAKE_PORT_NAME(_p))

#define nibble_up_clear(_port)						port_clear((_port), NIBBLE_UP_PINSET)
#define NIBBLE_UP_CLEAR(_p)							nibble_up_clear(MAKE_PORT_NAME(_p))

#define nibble_up_switch(_port)						port_switch((_port), NIBBLE_UP_PINSET)
#define NIBBLE_UP_SWITCH(_p)						nibble_up_switch(MAKE_PORT_NAME(_p)))

#define nibble_up_replace(_port, _val)				port_replace(MAKE_PORT_NAME(_p), NIBBLE_UP_PINSET, (_val))
#define NIBBLE_UP_REPLACE(_p, _val)					nibble_up_replace(MAKE_PORT_NAME(_p), (_val))

#define nibble_up_read(_pin)						port_read((_pin), (NIBBLE_UP_PINSET))
#define NIBBLE_UP_READ(_p)							nibble_up_read(MAKE_PIN_NAME(_p))

#define nibble_up_set_in_z(_ddr, _port)				port_set_in_z((_ddr), (_port), NIBBLE_UP_PINSET)
#define NIBBLE_UP_SET_IN_Z(_p)						nibble_up_set_in_z(MAKE_DDR_NAME(_p), MAKE_PORT_NAME(_p))

#define nibble_up_set_in_pu(_ddr, _port)			port_set_in_pu((_ddr), (_port), NIBBLE_UP_PINSET)
#define NIBBLE_UP_SET_IN_PU(_p)						nibble_up_set_in_pu(MAKE_DDR_NAME(_p), MAKE_PORT_NAME(_p))

#define nibble_up_set_out_d_lo(_ddr, _port)			port_set_out_d_lo((_ddr), (_port), NIBBLE_UP_PINSET)
#define NIBBLE_UP_SET_OUT_D_LO(_p)					nibble_up_set_out_d_lo(MAKE_DDR_NAME(_p), MAKE_PORT_NAME(_p))

#define nibble_up_set_out_d_hi(_ddr, _port)			port_set_out_d_hi((_ddr), (_port), NIBBLE_UP_PINSET)
#define NIBBLE_UP_SET_OUT_D_HI(_p)					nibble_up_set_out_d_hi(MAKE_DDR_NAME(_p), MAKE_PORT_NAME(_p))

// ---------------------------------------------------------------------------+
//		The upper nibble pin set aliases
// ---------------------------------------------------------------------------+
#define nibble_up_set_hi							nibble_up_set
#define NIBBLE_UP_SET_HI							NIBBLE_UP_SET

#define nibble_up_pull_up							nibble_up_set
#define NIBBLE_UP_PULL_UP							NIBBLE_UP_SET

#define nibble_up_set_lo							nibble_up_clear
#define NIBBLE_UP_SET_LO							NIBBLE_UP_CLEAR

#define nibble_up_to_read							nibble_up_set_in
#define NIBBLE_UP_TO_READ							NIBBLE_UP_SET_IN

#define nibble_up_to_read_pu						nibble_up_set_in_pu
#define NIBBLE_UP_TO_READ_PU						NIBBLE_UP_SET_IN_PU

#define nibble_up_to_read_z							nibble_up_set_in_z
#define NIBBLE_UP_TO_READ_Z							NIBBLE_UP_SET_IN_Z

#define nibble_up_to_write							nibble_up_set_out
#define NIBBLE_UP_TO_WRITE							NIBBLE_UP_SET_OUT

#define nibble_up_write								nibble_up_replace
#define NIBBLE_UP_WRITE								NIBBLE_UP_REPLACE

#define nibble_up_to_write_d_lo						nibble_up_set_out_d_lo
#define NIBBLE_UP_TO_WRITE_D_LO						NIBBLE_UP_SET_OUT_D_LO

#define nibble_up_to_write_d_hi						nibble_up_set_out_d_hi
#define NIBBLE_UP_TO_WRITE_D_HI						NIBBLE_UP_SET_OUT_D_HI

// ---------------------------------------------------------------------------+
//		The distinct pin set
// ---------------------------------------------------------------------------+
#define pin_set_in(_ddr, _b) 						port_set_in((_ddr), _BV((_b)))
#define PIN_SET_IN(_p, _b) 							pin_set_in(MAKE_DDR_NAME(_p), (_b))

#define pin_set_out(_ddr, _b) 						port_set_out((_ddr), _BV((_b)))
#define PIN_SET_OUT(_p, _b) 						pin_set_out(MAKE_DDR_NAME(_p), (_b))

#define pin_set(_port, _b)							port_set((_port), _BV((_b)))
#define PIN_SET(_p, _b)								pin_set(MAKE_PORT_NAME(_p), (_b))

#define pin_clear(_port, _b)						port_clear((_port), _BV((_b)))
#define PIN_CLEAR(_p, _b)							pin_clear(MAKE_PORT_NAME(_p), (_b))

#define pin_switch(_port, _b)						port_switch((_port), _BV((_b)))
#define PIN_SWITCH(_p, _b)							pin_switch(MAKE_PORT_NAME(_p), (_b))

#define pin_replace(_port, _b,  _val)				port_replace((_port), _BV((_b)), (_val))
#define PIN_REPLACE(_p, _b, _val)					pin_replace(MAKE_PORT_NAME(_p), (_b), (_val))

#define pin_read(_pin, _b)							port_read((_pin), (_BV((_b))))
#define PIN_READ(_p, _b)							pin_read(MAKE_PIN_NAME(_p), (_b))

#define pin_set_in_z(_ddr, _port, _b)				port_set_in_z((_ddr), (_port), _BV((_b)))
#define PIN_SET_IN_Z(_p, _b)						pin_set_in_z(MAKE_DDR_NAME(_p), MAKE_PORT_NAME(_p), (_b))

#define pin_set_in_pu(_ddr, _port, _b)				port_set_in_pu((_ddr), (_port), _BV((_b)))
#define PIN_SET_IN_PU(_p, _b)						pin_set_in_pu(MAKE_DDR_NAME(_p), MAKE_PORT_NAME(_p), (_b))

#define pin_set_out_d_lo(_ddr, _port, _b)			port_set_out_d_lo((_ddr), (_port), _BV((_b)))
#define PIN_SET_OUT_D_LO(_p, _b)					pin_set_out_d_lo(MAKE_DDR_NAME(_p), MAKE_PORT_NAME(_p), (_b))

#define pin_set_out_d_hi(_ddr, _port, _b)			port_set_out_d_hi((_ddr), (_port), _BV((_b)))
#define PIN_SET_OUT_D_HI(_p, _b)					pin_set_out_d_hi(MAKE_DDR_NAME(_p), MAKE_PORT_NAME(_p), (_b))

// ---------------------------------------------------------------------------+
//		The distinct pin aliases
// ---------------------------------------------------------------------------+
#define pin_set_hi									pin_set
#define PIN_SET_HI									PIN_SET

#define pin_on										pin_set
#define PIN_ON										PIN_SET

#define pin_pull_up									pin_set
#define PIN_PULL_UP									PIN_SET

#define pin_set_lo									pin_clear
#define PIN_SET_LO									PIN_CLEAR

#define pin_off										pin_clear
#define PIN_OFF										PIN_CLEAR

#define pin_to_read									pin_set_in
#define PIN_TO_READ									PIN_SET_IN

#define pin_to_read_pu								pin_set_in_pu
#define PIN_TO_READ_PU								PIN_SET_IN_PU

#define pin_to_read_z								pin_set_in_z
#define PIN_TO_READ_Z								PIN_SET_IN_Z

#define pin_to_write								pin_set_out
#define PIN_TO_WRITE								PIN_SET_OUT

#define pin_write									pin_replace
#define PIN_WRITE									PIN_REPLACE

#define pin_to_write_d_lo							pin_set_out_d_lo
#define PIN_TO_WRITE_D_LO							PIN_SET_OUT_D_LO

#define pin_to_write_d_hi							pin_set_out_d_hi
#define PIN_TO_WRITE_D_HI							PIN_SET_OUT_D_HI

#endif /* SLS_AVR_GPIO_H_ */
