// ---------------------------------------------------------------------------+
//					This file is part of SLS AVR Tools
// ---------------------------------------------------------------------------+
// Copyright (C) 2026 Simon Litt
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
 */

#ifndef SLS_AVR_ASSERT_H_
#define SLS_AVR_ASSERT_H_

#include <assert.h>

#if defined(NDEBUG)
#	define assert_na(e)	((void)0)
#else // !NDEBUG
/**
 * \brief The assert_na() macro tests the given expression, like standard assert macro with __ASSERT_USE_STDERR definition, but don't call abort().
 * \param expression Expression to test for.
 * \remark See https://www.nongnu.org/avr-libc/user-manual/group__avr__assert.html
 * \remark The macro may be removed at compile time by defining NDEBUG as a macro (e.g., by using the compiler option -DNDEBUG).
 */
#	define assert_na(e)	((e) ? (void)0 : \
					fprintf(stderr, "Assertion failed: (%s), function %s, file %s, line %u.\n", #e, __func__ , __FILE__, __LINE__))
#endif // NDEBUG

#endif // SLS_AVR_ASSERT_H_
