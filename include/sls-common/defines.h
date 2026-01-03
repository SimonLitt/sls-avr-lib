// ---------------------------------------------------------------------------+
//					This file is part of SLS СС Library
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
 * \file		sls-common/defines.h
 * \brief		SLS СС Library.
 * \code #include <sls-common/defines.h>\endcode
 */

#ifndef SLS_COMMON_DEFINES_H_
#define SLS_COMMON_DEFINES_H_

/** \brief Glues 2 components together */
#define MAKE_GLUE_X2(a,b) a ## b


/** \brief Glues 3 components together */
#define MAKE_GLUE_X3(a,b,c) a ## b ## c

#endif /* SLS_COMMON_DEFINES_H_ */
