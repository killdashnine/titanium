/***************************************************************************
 *            i386.h
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

/*! \file i386.h
 *  \brief Support functions for the i386 platform
 *   
 *  This file includes functions to interface with i386 specific ports/registers
 *
 */

#ifndef _I386_H
#define	_I386_H

namespace I386 {
    
    /*! Inline function for reading a byte from a port
     *
     *\param port The hardware port to read from
     *\return The read byte
     */
    inline unsigned char readPortByte (unsigned short port) {
        
        unsigned char readByte;
    
        __asm__ __volatile__ ("inb %1, %0" : "=a" (readByte) : "dN" (port));
    
        return readByte;
    }

    /*! Inline function for writing a byte to a port
     *
     *\param port The hardware port to write to
     *\param data The data to write to the port
     */
    inline void writePortByte (unsigned short port, unsigned char data) {
        
        __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
    }


}

#endif	/* _I386_H */

