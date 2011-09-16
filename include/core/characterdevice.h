/***************************************************************************
 *            characterdevice.h
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

/*! \file characterdevice.h
 *  \brief Character Device interface
 *   
 *  This file defines the CharacterDevice interface for character device I/O
 *
 */

#ifndef _CHARACTERDEVICE_H
#define	_CHARACTERDEVICE_H

#include <core/resource.h>

namespace Core {

/*! \class CharacterDevice
 *\brief CharacterDevice class
 *
 * This class is an interface (pure virtual class) to implement for character devices
 */
class CharacterDevice : public Resource {
    
private:
    
    // we only want the Console class to I/O with this class
    friend class Console;
    
    /*! Function to clear the screen's contents */
    virtual void clearBuffer() = 0;
    
    /*! Function for writing to a Character Device's buffer 
     *
     *\param buffer The buffer to copy
     *\param size The size of the buffer
     *\return An error code or E_SUCCESS
     */
    virtual unsigned long write(void* buffer, unsigned long size) = 0;
    
public:
    
    /*! Function for what kind of terminal is supported for this CharacterDevice
     *
     *\return The type of terminal
     *\see terminal.h
     */
    virtual unsigned long getTerminalType() = 0;
     
};

} /* namespace Core */

#endif	/* _CHARACTERDEVICE_H */

