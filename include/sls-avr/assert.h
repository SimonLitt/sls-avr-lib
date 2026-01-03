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
 * \file		sls-avr/assert.h
 * \brief		Alternative AVR assert.
 *
 * Because standard __assert calls abort() function.
 * \code
 * #include <sls-avr/assert.h>
 * int main(void) {
 *		...
 *		assert_na(PIND == 0xF0);
 *		...
 * }
 * \endcode
 *
 * \code
 * #define ASSERT_USE_ABORT
 * #include <sls-avr/assert.h>
 * int main(void) {
 *		...
 *		ASSERT(PIND == 0xF0);
 *		...
 * }
 * \endcode
 */

#ifndef SLS_AVR_ASSERT_H_
#define SLS_AVR_ASSERT_H_

#include <assert.h>

#if defined(NDEBUG)
#	define assert_na(e)	((void)0)
#else // !NDEBUG
/**
 * \brief The assert_na() macro tests the given expression, like standard assert macro with __ASSERT_USE_STDERR definition, but don't call abort().
 * \details The macro may be removed at compile time by defining NDEBUG as a macro (e.g., by using the compiler option -DNDEBUG).
 * \param expression Expression to test for.
 * \see https://www.nongnu.org/avr-libc/user-manual/group__avr__assert.html
 */
#	define assert_na(expression)	((expression) ? (void)0 : \
					fprintf(stderr, "Assertion failed: (%s), function %s, file %s, line %u.\n", #expression, __func__ , __FILE__, __LINE__))
#endif // NDEBUG


#if defined(__DOXYGEN__)
#	define ASSERT_USE_ABORT /**< \brief Replaces the behavior of the #ASSERT macro with the standard one.\attention If the macro is defined, it also defines the __ASSERT_USE_STDERR macro.  * \see ASSERT */
/**
 * \brief The macro tests the given expression.
 * \details Depending on the #ASSERT_USE_ABORT macro, it calls standard assert() or #assert_na()
 * \param expression Expression to test for.
 * \see ASSERT_USE_ABORT \see assert_na \see https://www.nongnu.org/avr-libc/user-manual/group__avr__assert.html
 */
#	define ASSERT(expression)
#endif // __DOXYGEN__

/** \cond NO_DOC */
#ifdef ASSERT_USE_ABORT
#	ifndef __ASSERT_USE_STDERR
#		define __ASSERT_USE_STDERR
#	endif // __ASSERT_USE_STDERR
#	define ASSERT(e)	assert((e))
#else
#	define ASSERT(e)	assert_na((e))
#endif // ASSERT_USE_ABORT
/** \endcond */

#endif // SLS_AVR_ASSERT_H_
