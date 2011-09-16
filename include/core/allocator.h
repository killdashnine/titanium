/***************************************************************************
 *            allocator.h
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

/*! \file allocator.h
 *  \brief  Allocator
 *   
 *  This file defines the Allocator class. The allocator class is an interface to implement for allocators.
 *
 */

#ifndef _ALLOCATOR_H
#define	_ALLOCATOR_H

#include <core/resource.h>

namespace Core {

/*! \class Allocator
 *\brief Allocator class
 *
 * The allocator class is an interface to implement for allocators
 *
 */
class Allocator : public Resource {
    
public:
    
    /*! Function for allocating memory
     *
     *\param size The amount of bytes to allocate for the object
     *\return The address or E_ALLOC_NOMEM when out of memory
     */
    virtual unsigned long allocate(unsigned long size) = 0;
    
    /*! Function for freeing memory
     *
     *\param address The address to free
     */
    virtual void free(unsigned long address) = 0;
    
};

} /* namespace Core */

#endif	/* _ALLOCATOR_H */


