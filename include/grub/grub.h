/***************************************************************************
 *            grub.h
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

/*! \file grub.h
 *  \brief GrubChecker
 *   
 * This file defines the GrubChecker class. This class checks if the Multiboot info header provided by GRUB is correct.
 * It also parses the memory size of the system.
 *
 */

#ifndef _GRUB_H
#define	_GRUB_H

#include <core/resource.h>

namespace Grub {

/*! \class GrubChecker
 *\brief GrubChecker class
 *
 * This class checks if the Multiboot info header provided by GRUB is correct.
 * It also parses the memory size of the system.
 */
class GrubChecker : public Core::Resource {
    
public:
    
    /*! Constructor for the GrubChecker class.
     *  Auto registers with ResourceManager.
     *  \param magic The magic provided by GRUB
     *  \param address The memory address of the GRUB multiboot info header
     */
    GrubChecker(unsigned long magic, unsigned long address);
    
    unsigned long startResource();
    
    /*! Function for getting the name of a resource
     *
     *\return The resource's name
     */
    const char* getResourceName();
    
    /*! Function to get the memory size
     *
     *\return Memory size in kB
     */
    unsigned long getMemorySize();
    
private:
    
    /*! The magic provided by GRUB */
    unsigned long _magic;
    
    /*! The memory address of the GRUB multiboot info header */
    unsigned long _address;
    
    /*! The memory size in kB */
    unsigned long _memorySize;
    
};

} /* namespace Grub */

#endif	/* _GRUB_H */



