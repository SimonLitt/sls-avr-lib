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
 * \file		sls-avr/avr.h
 * \brief		AVR lib.
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
 */

#ifndef SLS_AVR_AVR_H_
#define SLS_AVR_AVR_H_

#include <avr/io.h>

#include <sls-avr/defs.h>
#include <sls-avr/gpio.h>

#endif // SLS_AVR_AVR_H_
