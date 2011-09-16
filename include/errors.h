/***************************************************************************
 *            errors.h
 *
 *  Copyright  2008  Matthias v.d. Vlies
 *  matthias@mserver.nl
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/*! \file errors.h
 *  \brief Kernel errors
 *   
 *  This file includes constants to use as error codes.
 *
 */

#ifndef _ERRORS_H
#define	_ERRORS_H

/*! Failure for unknown reason */
#define E_FAILURE                           0x00

/*! Success for unknown reason */
#define E_SUCCESS                           0x01

/*! Out of static memory */
#define E_ALLOC_NOMEM                       0x02

/*! Possible buffer overflow */
#define E_BUFFER_OVERFLOW                   0x03

/*! Invalid terminal */
#define E_INVALID_TERMINAL                  0x04

/*! Kernel panic status */
#define E_PANIC                             0x05

/*! Kernel warning status */
#define E_WARNING                           0x06

#endif	/* _ERRORS_H */

