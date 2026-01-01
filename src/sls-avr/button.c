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
#include "sls-avr/button.h"
#include <string.h>

void btn_proc(btn_info_t *const btn_info, const bool is_now_hold) {
	bool is_holded = btn_is_holded(btn_info->state);
	if (is_holded) {
		if (is_now_hold) {
			#if BTN_ALLOW_LONG
			if (btn_info->_counter != 0xFF) { // overflow protect
				btn_info->_counter++; // As down long counter
				if (btn_info->_counter == BTN_LONG_COUNT) {
					btn_info->state |= _BTN_STAGE_MAY_LONG;
				}
			}
			#endif // BTN_ALLOW_LONG
			#ifndef __BTN_ALLOW_FAST_SCAN
			if (btn_info->_up_counter) { // is more then 0 & overflow protect
				btn_info->_up_counter--; // As up counter or unused counter
			}
			#endif // __BTN_ALLOW_FAST_SCAN
		} else {
			if (flag_is_set(btn_info->state, __BTN_STAGE_PROCESSED_BIT)) { // If the button was a modifier. Prevent action on unhold
				_btn_reset(btn_info); // On first unhold loop
				return;
			} else if (btn_is_ready(btn_info->state)) {
				#if BTN_RESET_UNUSED_COUNT  // If these events were not required
				if (btn_info->_counter) { // is more then 0 & overflow protect
					btn_info->_counter--; // As up counter or unused counter
					if (!btn_info->_counter) {
						_btn_reset(btn_info);
					}
				}
				#endif // BTN_RESET_UNUSED_COUNT
				return;
			}
			#ifndef __BTN_ALLOW_FAST_SCAN
			else if (btn_info->_up_counter != 0xFF) {
				btn_info->_up_counter++;

				if (btn_info->_up_counter == BTN_UP_COUNT) {
					#if BTN_ALLOW_LONG
					if (flag_is_set(btn_info->state, __BTN_STAGE_MAY_LONG_BIT)) {
						btn_info->state |= _BTN_STATE_LONG_CLICK;
						btn_info->_up_counter = 0xFF;
						#if BTN_RESET_UNUSED_COUNT
						btn_info->_counter = BTN_RESET_UNUSED_COUNT;
						#endif // BTN_RESET_UNUSED_COUNT
					} else
					#endif // BTN_ALLOW_LONG
					if (flag_is_set(btn_info->state, __BTN_STAGE_MAY_SHORT_BIT)) {
						btn_info->state |= _BTN_STATE_SHORT_CLICK;
						btn_info->_up_counter = 0xFF;
						#if BTN_RESET_UNUSED_COUNT
						btn_info->_counter = BTN_RESET_UNUSED_COUNT;
						#endif // BTN_RESET_UNUSED_COUNT
					}
				}
			}
			#endif // __BTN_ALLOW_FAST_SCAN
		}
	} else {
		if (is_now_hold) {
			if (btn_info->_counter != 0xFF) { // overflow protect
				btn_info->_counter++; // As down counter
				if (btn_info->_counter == BTN_DOWN_COUNT) {
					btn_info->state |= _BTN_STAGE_MAY_SHORT
					#ifdef __BTN_ALLOW_FAST_SCAN
					| _BTN_STATE_SHORT_CLICK
					#endif //!BTN_UP_COUNT
					;
					#if defined(__BTN_ALLOW_FAST_SCAN) && BTN_RESET_UNUSED_COUNT
					btn_info->_counter = BTN_RESET_UNUSED_COUNT;
					#endif // BTN_RESET_UNUSED_COUNT
				}
			}
		} else if (btn_info->_counter) {
			if (btn_info->_counter) { // is more then 0 & overflow protect
				btn_info->_counter--; // As down counter
			}
		}
	}
}

