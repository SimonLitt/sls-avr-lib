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

#include "sls-avr/uart_stdio.h"
#include <sls-common/defines.h>

#define __OUT_TO_UART_(_unum)	\
static int MAKE_GLUE_X3(_ud_uart, _unum, _putc)(char ch, FILE *stream) { \
	if (ch == '\n') { MAKE_GLUE_X3(uart, _unum, _putc)('\r'); } \
	MAKE_GLUE_X3(uart, _unum, _putc)(ch); \
	return 0; \
} \
static FILE MAKE_GLUE_X3(_ud_uart, _unum, _out) = FDEV_SETUP_STREAM(MAKE_GLUE_X3(_ud_uart, _unum, _putc), NULL, _FDEV_SETUP_WRITE); \
void MAKE_GLUE_X2(stdout_set_to_uart, _unum)(void) { stdout = &MAKE_GLUE_X3(_ud_uart, _unum, _out); }

#define __ERR_TO_UART_(_unum) \
void MAKE_GLUE_X2(stderr_set_to_uart, _unum)(void) { stderr = &MAKE_GLUE_X3(_ud_uart, _unum, _out); }


#define __IN_FROM_UART_(_unum) \
static int MAKE_GLUE_X3(_ud_uart, _unum, _getc)(FILE *stream) { \
	uint16_t ur; \
	do { ur = MAKE_GLUE_X3(uart, _unum, _getc)(); } while (ur & UART_NO_DATA); \
	if (ur & (UART_FRAME_ERROR | UART_OVERRUN_ERROR)) { /* Ignore UART_BUFFER_OVERFLOW */ \
		return EOF; \
	} \
	return (int)(ur & 0x00FF); \
} \
static FILE MAKE_GLUE_X3(_ud_uart, _unum, _in) = FDEV_SETUP_STREAM(NULL, MAKE_GLUE_X3(_ud_uart, _unum, _getc), _FDEV_SETUP_READ); \
void MAKE_GLUE_X2(stdin_set_from_uart, _unum)(void) { stdin = &MAKE_GLUE_X3(_ud_uart, _unum, _in); }

#ifdef USART0_ENABLED
__OUT_TO_UART_(0)
__ERR_TO_UART_(0)
__IN_FROM_UART_(0)
#endif // USART0_ENABLED

#ifdef USART1_ENABLED
__OUT_TO_UART_(1)
__ERR_TO_UART_(1)
__IN_FROM_UART_(1)
#endif // USART1_ENABLED

#ifdef USART2_ENABLED
__OUT_TO_UART_(2)
__ERR_TO_UART_(2)
__IN_FROM_UART_(2)
#endif // USART2_ENABLED

#ifdef USART3_ENABLED
__OUT_TO_UART_(3)
__ERR_TO_UART_(3)
__IN_FROM_UART_(3)
#endif // USART3_ENABLED
