/***************************************************************************
 *            config.h
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

/*! \file config.h
 *  \brief Compile-time kernel configuration
 *   
 *  This file includes constants to use for kernel compilation. These values
 *  cannot be changed at run-time. These include various memory addresses for
 *  the i386 architecture. Also some variables are included to reference the
 *  size of the kernel etc.
 *
 */

#ifndef _CONFIG_H
#define	_CONFIG_H

#define STRING_VALUE(arg)      #arg
#define MAKEFILE_ARGUMENT_VALUE(name) STRING_VALUE(name)

#define VERSION_STRING MAKEFILE_ARGUMENT_VALUE(SVN_REVISION)
#define YEAR_STRING MAKEFILE_ARGUMENT_VALUE(YEAR)
#define USER MAKEFILE_ARGUMENT_VALUE(COMPILED_BY)
#define HOST MAKEFILE_ARGUMENT_VALUE(COMPILEHOST)

/*! Address of the BIOS video RAM 
 *
 *\see http://wiki.osdev.org/Printing_to_Screen
 */
#define VIDEO_BASE                  0xb8000

/*! size of the video memory (80 * 25 ) in words */
#define VIDEO_SIZE                  0x7d0

/*! End of video memory */
#define VIDEO_END                   VIDEO_BASE + (VIDEO_SIZE * 2)

/*! Base address of the kernel (1 Megabyte) */
#define KERNEL_BASE                 0x100000

/*! Pointer to the end of the kernel's code, used to determine kernel size */
extern "C" const unsigned long end;

/*! Alias for the end variable to know the kernel's end 
 * TODO: end variable doesn't seem to work!
 */
#define KERNEL_END                  0x200000

/*! Size of the kernel */
#define KERNEL_SIZE                 KERNEL_END - KERNEL_BASE

/*! start address for the static memory allocator */
#define STATIC_ALLOC_BASE           KERNEL_END

/*! size of the static memory region */
#define STATIC_ALLOC_SIZE           0x10000

/*! end of the static memory region */
#define STATIC_ALLOC_END            STATIC_ALLOC_BASE + STATIC_ALLOC_SIZE

/*! True alias */
#define TRUE                        1

/*! False alias */
#define FALSE                       0

#endif	/* _CONFIG_H */

