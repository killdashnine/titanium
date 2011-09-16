/***************************************************************************
 *            staticallocator.h
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

/*! \file staticallocator.h
 *  \brief Static allocator
 *   
 *  This file defines the Static allocator class. The class allocates static memory.
 *
 */

#ifndef _STATICALLOCATOR_H
#define	_STATICALLOCATOR_H

#include <core/allocator.h>
#include <core/kernelallocator.h>

namespace Core {

/*! \class StaticAllocator
 *\brief StaticAllocator class
 *
 * This class defines an allocator for fixed mapped memory. This allocator doesn't
 * support a function to free memory, thus the name StaticAllocator. Singleton.
 *
 * \see config.h
 */
class StaticAllocator : public Allocator {
    
public:
    
    /*! Function for allocating "static" memory
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
    
    /*! A static function to get the singleton instance for a StaticAllocator
     *
     *\return The StaticAllocator instance
     */
    static StaticAllocator* getInstance();
    
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
    
    friend class KernelAllocator;
    
    /*! A static function to get the singleton instance for a StaticAllocator
     *
     *\param The base address
     *\return The StaticAllocator instance
     */
    static StaticAllocator* getInstance(unsigned long base);
    
    /*! Singleton instance */
    static StaticAllocator* _instance;
    
    /*! The current address to use for allocation */
    unsigned long _pointer;
    
};

} /* namespace Core */

#endif	/* _STATICALLOCATOR_H */


