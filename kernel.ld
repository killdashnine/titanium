/***************************************************************************
 *            kernel.ld
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

OUTPUT_FORMAT("elf32-i386")
INPUT("build/loader.o")
ENTRY(start)
SECTIONS
{
    .text 0x100000 :
    {
        code = .; _code = .; __code = .;
        *(.text)
        . = ALIGN(32);
    }

    .rodata :
    {
        rodata = .; _rodata = .; __rodata = .;
        *(.data)
        . = ALIGN(32);
    }

    .data :
    {
        __CTOR_LIST__ = .; LONG((__CTOR_END__ - __CTOR_LIST__) / 4 - 2) *(.ctors)   LONG(0) __CTOR_END__ = .;  
        __DTOR_LIST__ = .; LONG((__DTOR_END__ - __DTOR_LIST__) / 4 - 2) *(.dtors) LONG(0) __DTOR_END__ = .; 

        data = .; _data = .; __data = .;
        *(.data)
        . = ALIGN(32);
    }

    .bss :
    {
        bss = .; _bss = .; __bss = .;
        *(.bss)
        . = ALIGN(32);
    }


    end = .; _end = .; __end = .;
}
