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
 * \file		sls-avr/uart_stdio.h
 *
 * \brief		Standard IO thouth USART.
 *
 * \code
 * #include <sls-avr/uart_stdio.h>
 * #define UART_BAUD_RATE 9600
 * ...
 * int main(void) {
 *		...
 *		uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
 *		stdout_set_to_uart();
 *		stderr_set_to_uart();
 *		printf("OK!\n");
 *		fprintf(stderr, "Error!");
 *		...
 * }
 * \endcode
 *
 * \code
 * #include <sls-avr/uart_stdio.h>
 * #define UART_BAUD_RATE 9600
 * ...
 * int main(void) {
 *		...
 *		uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
 *		stdout_set_to_uart();
 *		stdin_set_from_uart();
 *		int ch = getchar();
 *		if (ch != EOF) {
 *			printf("GET: `%s`!\n", ch);
 *		}
 *		...
 * }
 * \endcode
 */

#ifndef SLS_AVR_UART_STDIO_H_
#define SLS_AVR_UART_STDIO_H_

#include <stdio.h>
#include <avr-uart/uart.h>

#ifdef USART0_ENABLED || defined(__DOXYGEN__)
void stdout_set_to_uart0(void);		/**< \brief Sets standard output via USART0 */
void stderr_set_to_uart0(void);		/**< \brief Sets standard error output via USART0 */
void stdin_set_from_uart0(void);	/**< \brief Sets standard input via USART0 */

#	ifndef stdout_set_to_uart
#		define stdout_set_to_uart() stdout_set_to_uart0() /**< \brief Sets standard output via UART, by default alias for #stdout_set_to_uart0 \see stdout_set_to_uart0 */
#	endif
#	ifndef stderr_set_to_uart
#		define stderr_set_to_uart() stderr_set_to_uart0() /**< \brief Sets standard error output via UART, by default alias for #stdout_set_to_uart0 \see stdout_set_to_uart0 */
#	endif
#	ifndef stdin_set_from_uart
#		define stdin_set_from_uart() stdin_set_from_uart0() /**< \brief Sets standard input via UART, by default alias for #stdout_set_to_uart0 \see stdout_set_to_uart0 */
#	endif

#endif // USART0_ENABLED

#ifdef USART1_ENABLED || defined(__DOXYGEN__)
void stdout_set_to_uart1(void);		/**< \brief Sets standard output via USART1 */
void stderr_set_to_uart1(void);		/**< \brief Sets standard error output via USART1 */
void stdin_set_from_uart1(void);	/**< \brief Sets standard input via USART1 */
#endif // USART1_ENABLED

#ifdef USART2_ENABLED || defined(__DOXYGEN__)
void stdout_set_to_uart2(void);		/**< \brief Sets standard output via USART2 */
void stderr_set_to_uart2(void);		/**< \brief Sets standard error output via USART2 */
void stdin_set_from_uart2(void);	/**< \brief Sets standard input via USART2 */
#endif // USART2_ENABLED

#ifdef USART3_ENABLED || defined(__DOXYGEN__)
void stdout_set_to_uart3(void);		/**< \brief Sets standard output via USART3 */
void stderr_set_to_uart3(void);		/**< \brief Sets standard error output via USART3 */
void stdin_set_from_uart3(void);	/**< \brief Sets standard input via USART3 */
#endif // USART3_ENABLED

#endif /* SLS_AVR_UART_STDIO_H_ */
