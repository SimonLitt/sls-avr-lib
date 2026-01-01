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
#include "sls-avr/status_led.h"

void init_status_led(void) {
    #if (defined LED_STAT_PORT) && (defined LED_STAT_PIN)
	PIN_TO_WRITE_D_LO(LED_STAT_PORT, LED_STAT_PIN);

    #endif

    #if (defined LED_INF_PORT) && (defined LED_INF_PIN)
	PIN_TO_WRITE_D_HI(LED_INF_PORT, LED_INF_PIN);
    #endif

    #if (defined LED_ERR_PORT) && (defined LED_ERR_PIN)
	PIN_TO_WRITE_D_HI(LED_ERR_PORT, LED_ERR_PIN);
    #endif
}

void status_led_ready(void) {
    #if (defined LED_STAT_PORT) && (defined LED_STAT_PIN)
	led_stat_on();
    #endif

    #if (defined LED_INF_PORT) && (defined LED_INF_PIN)
	led_inf_off();
    #endif

    #if (defined LED_ERR_PORT) && (defined LED_ERR_PIN)
	led_err_off();
    #endif
}
