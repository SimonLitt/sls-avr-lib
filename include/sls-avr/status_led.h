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
 * \file		sls-avr/status_led.h
 * \brief		Control of indicator LEDs.
 *
 * \code
 * #define LED_STAT_PORT			A
 * #define LED_INF_PORT			A
 * #define LED_ERR_PORT			A
 * #define LED_STAT_PIN			PA0
 * #define LED_INF_PIN			PA1
 * #define LED_ERR_PIN			PA2
 * #include <sls-avr/status_led.h>
 * ...
 * ISR (TIMER0_COMP_vect) { // 1Hz timer interrupt
 * 		...
 *		btn_state();
 * 		...
 *}
 *
 * int main(void) {
 *		...
 *		init_status_led();
 *		...
 *		sei();
 *		status_led_ready();
 *		...
 * }
 * \endcode
 */
#ifndef SLS_AVR_STATUS_LED_H_
#define SLS_AVR_STATUS_LED_H_

#include <sls-avr/avr.h>

#define LED_ON		PIN_ON /**< \brief The meaningful name alias for #PIN_ON */
#define LED_OFF		PIN_OFF /**< \brief The meaningful name alias for #PIN_OFF */
#define LED_SWITCH	PIN_SWITCH /**< \brief The meaningful name alias for #PIN_SWITCH */

void init_status_led(void); /**< \brief Initializing ports for indicator LEDs and turning off all but the error LED one. */
void status_led_ready(void); /**< \brief  Switching off additional indicators and turning on the main one. */
#define status_led_clear status_led_ready /**< \brief Alias for #status_led_ready. */

#if (defined LED_STAT_PORT) && (defined LED_STAT_PIN)
#	define led_stat_switch()	LED_SWITCH(LED_STAT_PORT, LED_STAT_PIN) /**< \brief Switches the main status LED. */
#	define led_stat_on()		LED_ON(LED_STAT_PORT, LED_STAT_PIN) /**< \brief Turns on the main status LED. */
#	define led_stat_off()		LED_OFF(LED_STAT_PORT, LED_STAT_PIN) /**< \brief Turns off the main status LED. */
#endif

#if (defined LED_INF_PORT) && (defined LED_INF_PIN)
#	define led_inf_switch()		LED_SWITCH(LED_INF_PORT, LED_INF_PIN) /**< \brief Switches the additional status LED. */
#	define led_inf_on()			LED_ON(LED_INF_PORT, LED_INF_PIN) /**< \brief Turns on the additional status LED. */
#	define led_inf_off()		LED_OFF(LED_INF_PORT, LED_INF_PIN) /**< \brief Turns off the additional status LED. */
#endif

#if (defined LED_ERR_PORT) && (defined LED_ERR_PIN)
#	define led_err_switch()		LED_SWITCH(LED_ERR_PORT, LED_ERR_PIN) /**< \brief Switches the error status LED. */
#	define led_err_on()			LED_ON(LED_ERR_PORT, LED_ERR_PIN) /**< \brief Turns on the error status LED. */
#	define led_err_off()		LED_OFF(LED_ERR_PORT, LED_ERR_PIN) /**< \brief Turns off the error status LED. */
#endif

#endif /* SLS_AVR_STATUS_LED_H_ */
