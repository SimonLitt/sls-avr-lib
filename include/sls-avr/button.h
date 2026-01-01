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
 * \file		sls-avr/button.h
 *
 * \brief		A AVR helper for working with individual buttons.
 *
 * \code
 * #include <sls-avr/avr.h>
 * ...
 * void init_buttons(void) {
 *		PIN_TO_READ(BTN_1_PORT, BTN_1_PIN);
 *		PIN_TO_READ(BTN_2_PORT, BTN_2_PIN);
 * }
 *
 * void buttons_loop(void) {
 *		static btn_info_t btn_1_info = BTN_INFO_STRUCT_DEFAULT;
 *		btn_proc(&btn_1_info, !(PIN_READ(BTN_1_PORT, BTN_1_PIN)));
 *		if (btn_is_clicked(btn_1_info.state)) {
 *			on_click1();
 *			btn_reset(&btn_1_info);
 *		}
 *
 *		static btn_info_t btn_2_info = BTN_INFO_STRUCT_DEFAULT;
 *		btn_proc(&btn_2_info, !(PIN_READ(BTN_2_PORT, BTN_2_PIN)));
 *		if (btn_is_clicked(btn_2_info.state)) {
 *			on_click2();
 *			btn_reset(&btn_2_info);
 *		}
 * }
 * ...
 * \endcode
 */
#ifndef SLS_AVR_SINGLE_BUTTON_H_
#define SLS_AVR_SINGLE_BUTTON_H_

#include <string.h>
#include <stdint.h>
#include <util/atomic.h>
#include <sls-avr/avr.h>

#define BTN_MAX_SCAN_COUNT 254U /**< \brief Limit on the number of cycles for which a press is considered complete */

#ifndef BTN_LONG_COUNT
#	define BTN_LONG_COUNT 40U /**< \brief The number that is compared to the counter of inputs to the #btn_proc function in the pressed state 2-254. When the set value is reached, the button can receive the long pressed status.*/
#	if (BTN_LONG_COUNT > BTN_MAX_SCAN_COUNT)
#		error "Long Pressed state counter should be less or equal to 254!"
#	endif
#	if (BTN_LONG_COUNT <= BTN_DOWN_COUNT)
#		error "Long Pressed state counter should be more then #BTN_DOWN_COUNT!"
#	endif
#endif // BTN_LONG_COUNT

#ifndef BTN_ALLOW_LONG
#	define BTN_ALLOW_LONG 0 /**< \brief Allows long pressed status.*/
#endif // BTN_ALLOW_LONG

#ifndef BTN_RESET_UNUSED_COUNT
#	define BTN_RESET_UNUSED_COUNT 0 /**< \brief The number that is compared to the counter of unused click 0-254. When the set value is reached, the #btn_info_struct structure is reset to its default state. */
#endif // BTN_RESET_UNUSED_COUNT
#if (BTN_RESET_UNUSED_COUNT < 0) || (BTN_RESET_UNUSED_COUNT > BTN_MAX_SCAN_COUNT)
#	error "Reset counter should be in range 0-254!"
#endif

#ifndef BTN_DOWN_COUNT
#define BTN_DOWN_COUNT 3U /**< \brief The number that is compared to the counter of inputs to the #btn_proc function in the pressed state 1-254. When the set value is reached, the button can receive the pressed status.*/
#endif // BTN_DOWN_COUNT

#if (BTN_DOWN_COUNT < 1) || (BTN_DOWN_COUNT > BTN_MAX_SCAN_COUNT)
#	error "Pressed state counter should be in range 2-254!"
#endif

#ifndef BTN_UP_COUNT
#	define BTN_UP_COUNT 2U /**< \brief The number that is compared to the counter of inputs to the #btn_proc function in the unpressed state 0-254. When the set value is reached, the button takes on the triggered status. \remark If the value is O then the click is considered to have been counted even before the button is released. In this case, resetting the state will lead to a re-trigger, if this is undesirable, it needs to set the processing flag see #btn_set_processed. */
#endif // BTN_UP_COUNT
#if (BTN_UP_COUNT < 0) || (BTN_UP_COUNT > BTN_MAX_SCAN_COUNT)
#	error "Released state counter should be in range 1-254!"
#endif

/** \cond NO_DOC */
#if !BTN_UP_COUNT
#	if BTN_ALLOW_LONG
#		error "Long presses are incompatible with fast processing!"
#	endif
#	define __BTN_ALLOW_FAST_SCAN
#endif
/** \endcond */

#ifndef BTN_FAST_SOME_CODE
#	define BTN_FAST_SOME_CODE 0 /**< \brief \brief If enabled then in the #btn_reset and #btn_reset_fegi functions, instead of resetting, only the processing flag is set.  \remark This allows for the same code to be achieved with the flag on and off, but disables re-triggering.*/
#endif // BTN_FAST_SOME_CODE

/** \cond NO_DOC */
#if BTN_FAST_SOME_CODE && (defined(__BTN_ALLOW_FAST_SCAN) || !BTN_ALLOW_LONG)
#	define	__BTN_LONG_DEFINITIONS
#endif
/** \endcond */

/** \cond NO_DOC */
// ---------------------------------------------------------------------------+
// state flags
// ---------------------------------------------------------------------------+
#define	__BTN_STAGE_MAY_SHORT_BIT			0
#if BTN_ALLOW_LONG
#	define	__BTN_STAGE_MAY_LONG_BIT		1
#endif // BTN_ALLOW_LONG
#define	__BTN_STAGE_PROCESSED_BIT			2
//#define	__BTN_STAGE_UNUSED_BIT			3
#define	__BTN_STATE_SHORT_CLICK_BIT			4
#if BTN_ALLOW_LONG
#	define	__BTN_STATE_LONG_CLICK_BIT		5
#endif // BTN_ALLOW_LONG
//#define	__BTN_STAGE_UNUSED_BIT			6
//#define	__BTN_STAGE_UNUSED_BIT			7

// Stages of click processing
#define _BTN_STAGE_MAY_SHORT				(_BV(__BTN_STAGE_MAY_SHORT_BIT)) /**< Normal pressing is possible */
#define _BTN_STAGE_MAY_LONG					(_BV(__BTN_STAGE_MAY_LONG_BIT)) /**< Long pressing is possible */
#define _BTN_STAGE_PROCESSED				(_BV(__BTN_STAGE_PROCESSED_BIT)) /**< The button press has been processed, and the state of this button will not be used further until it is released. */

// States of a button
#define _BTN_STATE_SHORT_CLICK				(_BV(__BTN_STATE_SHORT_CLICK_BIT)) /**< Short press detected */
#if BTN_ALLOW_LONG
#	define _BTN_STATE_LONG_CLICK			(_BV(__BTN_STATE_LONG_CLICK_BIT)) /**< Long press detected */
#endif // BTN_ALLOW_LONG

#if BTN_ALLOW_LONG
#	define __BTN_IS_CLICKED					(_BTN_STATE_SHORT_CLICK | _BTN_STATE_LONG_CLICK)
#	define __BTN_IS_HOLDED					(_BTN_STAGE_MAY_SHORT | _BTN_STAGE_MAY_LONG)
#else
#	define __BTN_IS_CLICKED					_BTN_STATE_SHORT_CLICK
#	define __BTN_IS_HOLDED					_BTN_STAGE_MAY_SHORT
#endif // BTN_ALLOW_LONG

/** \endcond */

/** \brief Information about a button */
typedef struct {
	uint8_t _counter;	/**< \brief Clamped or released state cycle counter. \remark Internal use only! */
	#ifndef __BTN_ALLOW_FAST_SCAN
	uint8_t _up_counter; /**< \brief Counter of cycles of released state after pressing. \remark Internal use only! */
	#endif // __BTN_ALLOW_FAST_SCAN
	byte_t state;		/**< \brief Stages and states flags of click processing */
} btn_info_struct;

typedef volatile btn_info_struct btn_info_t; /**< \brief Information about a button type. See #btn_info_struct */

#define BTN_INFO_STATE_DEFAULT 0 /**< \brief Default state value. See #btn_info_struct */

#ifndef __BTN_ALLOW_FAST_SCAN
#	define BTN_INFO_STRUCT_DEFAULT {._counter = 0, ._up_counter = 0, .state = BTN_INFO_STATE_DEFAULT} /**< \brief Default button information structure #btn_info_struct */
#else
#	define BTN_INFO_STRUCT_DEFAULT {._counter = 0, .state = BTN_INFO_STATE_DEFAULT}
#endif // __BTN_ALLOW_FAST_SCAN
/** \brief Is button holded.
 * \param _state Stages of click processing
 * \return Is holded
 */
#define btn_is_holded(_state) ((_state) & (__BTN_IS_HOLDED))

/** \brief Completed but unprocessed click
 * \param _state Stages of click processing
 * \return Is clicked
 */
#define btn_is_ready(_state) ((_state) & (__BTN_IS_CLICKED))
/** \brief Tests normal click
 * \param _state Stages of click processing
 * \return Is clicked
 */
#define btn_is_clicked(_state) (flag_is_set((_state), __BTN_STATE_SHORT_CLICK_BIT))

#if defined(__DOXYGEN__)
/** \brief Tests long click
 * \param _state Stages of click processing
 * \return Is long clicked
 */
#	define btn_is_long_clicked(_state)
#endif // __DOXYGEN__

#if BTN_ALLOW_LONG
#	define btn_is_long_clicked(_state) (flag_is_set((_state), __BTN_STATE_LONG_CLICK_BIT))
#elifdef __BTN_LONG_DEFINITIONS
#	define btn_is_long_clicked(_state) false
#endif // BTN_ALLOW_LONG
/** \brief Is the button taken into account
 *
 * It is necessary so that when released, the status does not change to clicked. Used when the button can be a macro button(function modifier).
 * \param _state Stages of click processing
 */
#define btn_set_processed(_state) ((_state) = ((_state) & ~(__BTN_IS_CLICKED)) | _BTN_STAGE_PROCESSED)

#ifndef BTN_ATOMIC_FUNCTIONS
#	define BTN_ATOMIC_FUNCTIONS 0 /**< \brief Allow ATOMIC_BLOCK wrappers for button processing. \remark Sometimes it's more convenient to handle keystrokes within an interrupt. However, it's not recommended to linger in an interrupt for too long. */
#endif // BTN_ATOMIC_FUNCTIONS

/** \cond NO_DOC */
static inline void _btn_reset(btn_info_t *const btn_info) {
	static const btn_info_struct _def_btn_info_struct = BTN_INFO_STRUCT_DEFAULT;
	(*btn_info) = _def_btn_info_struct;
}
/** \endcond */

/** \brief Resets the button state to default.
 * \param btn_info[out] Information about a button.
 */
static inline void btn_reset(btn_info_t *const btn_info) {
	#if defined(__BTN_ALLOW_FAST_SCAN) && BTN_FAST_SOME_CODE
	btn_set_processed(btn_info->state);
	#else
	_btn_reset(btn_info);
	#endif // __BTN_ALLOW_FAST_SCAN
}

/** \brief Update counters and button press stages for a button information structure.
 *
 * If not called from an interrupt, or if other interrupts are enabled in the interrupt, then it should be executed atomically.
 * \param btn_info[out] Information about a button.
 * \param is_now_hold[in] Is the button currently pressed?
 */
void btn_proc(btn_info_t *const btn_info, const bool is_now_hold);

#if defined(__DOXYGEN__)

/** \brief Such as the #btn_reset, but executed atomically.
 * \param btn_info[out] Information about a button.
 */
static inline void btn_reset_atomic(btn_info_t *const btn_info);

/** \brief Such as the #btn_reset, but executed atomically with force enabling ot the global interrupts.
 * \param btn_info[out] Information about a button.
 */
static inline void btn_reset_atomic_fegi(btn_info_t *const btn_info);

/** \brief Such as the #btn_proc, but executed atomically.
 * \param btn_info[out] Information about a button.
 * \param is_now_hold[in] Is the button currently pressed?
 */
static inline void btn_proc_atomic(btn_info_t *const btn_info, const bool is_now_hold);

/** \brief Such as the #btn_proc, but executed atomically with force enabling ot the global interrupts.
 * \param btn_info[out] Information about a button.
 * \param is_now_hold[in] Is the button currently pressed?
 */
static inline void btn_proc_atomic_fegi(btn_info_t *const btn_info, const bool is_now_hold);

/** \brief Actions before events proc.
 * \param btn_info[out] Information about a button.
 * \return Currently copy of #btn_info_struct
 */
static inline btn_info_struct btn_get_info(btn_info_t *const btn_info);

/** \brief Such as the #btn_get_info, but with force enabling ot the global interrupts.
 * \param btn_info[out] Information about a button. */
static inline btn_info_struct btn_get_info_fegi(btn_info_t *const btn_info);
#endif // __DOXYGEN__

#if BTN_ATOMIC_FUNCTIONS
static inline void btn_reset_atomic(btn_info_t *const btn_info) {
	#if defined(__BTN_ALLOW_FAST_SCAN) && BTN_FAST_SOME_CODE
	btn_set_processed(btn_info->state); //8-bit - no atomic
	#else
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		_btn_reset(btn_info);
	}
	#endif // __BTN_ALLOW_FAST_SCAN
}

static inline void btn_reset_atomic_fegi(btn_info_t *const btn_info) {
	#if defined(__BTN_ALLOW_FAST_SCAN) && BTN_FAST_SOME_CODE
	btn_set_processed(btn_info->state); //8-bit - no atomic
	#else
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		_btn_reset(btn_info);
	}
	#endif // __BTN_ALLOW_FAST_SCAN
}

static inline void btn_proc_atomic(btn_info_t *const btn_info, const bool is_now_hold) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		btn_proc(btn_info, is_now_hold);
	}
}

static inline void btn_proc_atomic_fegi(btn_info_t *const btn_info, const bool is_now_hold) {
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		btn_proc(btn_info, is_now_hold);
	}
}

static inline btn_info_struct btn_get_info(btn_info_t *const btn_info) {
	btn_info_struct info_struct;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		info_struct = *btn_info;
	}
	return info_struct;
}

static inline btn_info_struct btn_get_info_fegi(btn_info_t *const btn_info) {
	btn_info_struct info_struct;
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		info_struct = *btn_info;
	}
	return info_struct;
}
#endif // BTN_ATOMIC_FUNCTIONS

#endif /* SLS_AVR_SINGLE_BUTTON_H_ */
