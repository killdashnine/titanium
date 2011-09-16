/***************************************************************************
 *            kernelallocator.h
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

/*! \file kernelallocator.h
 *  \brief Kernel allocator
 *   
 *  This file defines the KernelAllocator class. The class manages all other Allocators and should be used
 *  to allocate memory. The KernelAllocator class will choose wich Allocator should be used for the request.
 *
 */

#ifndef _KERNELALLOCATOR_H
#define	_KERNELALLOCATOR_H

#include <core/allocator.h>

namespace Core {

/*! \class KernelAllocator
 *\brief KernelAllocator class
 *
 * The allocator class will choose wich allocator should be used for a request. Singleton class.
 *
 */
class KernelAllocator : public Allocator {
    
public:
    
    /*! Function for allocating memory
     *
     *\param size The amount of bytes to allocate for the object
     *\return The address or E_ALLOC_NOMEM when out of memory
     */
    unsigned long allocate(unsigned long size);
    
    /*! Function for freeing memory
     *
     *\param address The address to free
     */
    void free(unsigned long address);
    
    /*! A static function to get the singleton instance for a KernelAllocator
     *
     *\return The KernelAllocator instance
     */
    static KernelAllocator* getInstance();
    
    /*! Function for starting a resource
     *
     *\return A status indicating E_SUCCES or E_FAILURE
     */
    unsigned long startResource();
    
    /*! Function for getting the name of a resource
     *
     *\return The resource's name
     */
    const char* getResourceName();
    
#ifdef DEBUG
    
    /*! Function to output debug counters on the screen */
    void printDebug();
    
#endif
    
private:
    
#ifdef DEBUG
    
    /*! Debug variable to count number of allocations through this allocator */
    int allocations;
    
    /*! Debug variable to count number of free through this allocator */
    int frees;

#endif
    
    /*! Singleton instance */
    static KernelAllocator* _instance;
    
    /*! The current default allocator */
    Allocator* _allocator;
    
protected:
    
    /*! Constructor for the KernelAllocator class */
    KernelAllocator();
    
};

} /* namespace Core */

#endif	/* _KERNELALLOCATOR_H */


