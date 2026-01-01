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
 * \file		sls-avr/uart_stdio.h
 *
 * \brief		Standard IO thouth USART.
 */
#ifndef SLS_AVR_UART_STDIO_H_
#define SLS_AVR_UART_STDIO_H_

#include <stdio.h>
#include <avr-uart/uart.h>
#include <avr/pgmspace.h>

#ifdef USART0_ENABLED
void stdout_set_to_uart0(void);
void stderr_set_to_uart0(void);
void stdin_set_from_uart0(void);

#	ifndef stdout_set_to_uart
#		define stdout_set_to_uart() stdout_set_to_uart0()
#	endif
#	ifndef stderr_set_to_uart
#		define stderr_set_to_uart() stderr_set_to_uart0()
#	endif
#	ifndef stdin_set_from_uart
#		define stdin_set_from_uart() stdin_set_from_uart0()
#	endif

#endif // USART0_ENABLED

#ifdef USART1_ENABLED
void stdout_set_to_uart1(void);
void stderr_set_to_uart1(void);
void stdin_set_from_uart1(void);
#endif // USART1_ENABLED

#ifdef USART2_ENABLED
void stdout_set_to_uart2(void);
void stderr_set_to_uart2(void);
void stdin_set_from_uart2(void);
#endif // USART2_ENABLED

#ifdef USART3_ENABLED
void stdout_set_to_uart3(void);
void stderr_set_to_uart3(void);
void stdin_set_from_uart3(void);
#endif // USART3_ENABLED

#endif /* SLS_AVR_UART_STDIO_H_ */
