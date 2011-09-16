/***************************************************************************
 *            kernelallocator.cpp
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

/*! \file kernelallocator.cpp
 *  \brief Kernel allocator
 *   
 *  This file implements the Kernel allocator class. The class manages all other Allocators and should be used
 *  to allocate memory. The KernelAllocator class will choose wich Allocator should be used for the request.
 *
 */

#include <config.h>
#include <errors.h>
#include <core/kernelallocator.h>
#include <core/staticallocator.h>

// placement new function
inline void* operator new(unsigned int n, void* p)  throw() {
    
    // avoid warning
    n = 0;

    return p;
}

// set instance pointer to a null pointer
Core::KernelAllocator* Core::KernelAllocator::_instance = 0;

Core::KernelAllocator* Core::KernelAllocator::getInstance() {
    
    // check for exsisting instance
    if(_instance == 0) {
        
        // none found, create new instance (with placement new)
        _instance = new (reinterpret_cast<Core::KernelAllocator*>(STATIC_ALLOC_BASE)) Core::KernelAllocator();
        
        // get the default allocator
        _instance->_allocator = Core::StaticAllocator::getInstance(STATIC_ALLOC_BASE + sizeof(KernelAllocator));  
    }
    
    // return the instance
    return _instance;
}

unsigned long Core::KernelAllocator::allocate(unsigned long size) {

#ifdef DEBUG
    this->allocations++;
#endif
    
    return this->_allocator->allocate(size);
}

void Core::KernelAllocator::free(unsigned long address) {
 
#ifdef DEBUG
    this->frees++;
#endif
    
    this->_allocator->free(address);
}

Core::KernelAllocator::KernelAllocator() {
    
    // dummy constructor
}

#ifdef DEBUG
void Core::KernelAllocator::printDebug() {
    
    // TODO: implement me
}
#endif

unsigned long Core::KernelAllocator::startResource() {
    
    return E_SUCCESS;
}

const char* Core::KernelAllocator::getResourceName() {
    
    return "KernelAllocator";
}
