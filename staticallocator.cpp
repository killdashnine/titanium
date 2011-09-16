/***************************************************************************
 *            staticallocator.cpp
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

/*! \file staticallocator.cpp
 *  \brief Static allocator
 *   
 *  This file implements the Static allocator class. The class allocates static memory.
 *
 */

#include <config.h>
#include <errors.h>
#include <core/staticallocator.h>

// placement new function
inline void* operator new(unsigned int n, void* p)  throw() {

    // avoid warning
    n = 0;
    
    return p;
}

// set instance pointer to a null pointer
Core::StaticAllocator* Core::StaticAllocator::_instance = 0;

Core::StaticAllocator* Core::StaticAllocator::getInstance(unsigned long base) {
     
    // none found, create new instance (with placement new)
    _instance = new (reinterpret_cast<Core::StaticAllocator*>(base)) Core::StaticAllocator();
    
    // get the default allocator
    _instance->_pointer = base + sizeof(StaticAllocator);  
    
    // return the instance
    return _instance;
}

Core::StaticAllocator* Core::StaticAllocator::getInstance() {
    
    // this is safe, because the other one gets called first anyway
    return _instance;
}

unsigned long Core::StaticAllocator::allocate(unsigned long size) {

#ifdef DEBUG
    this->allocations++;
#endif
    
    // check if we have enough memory left
    if(this->_pointer + size > STATIC_ALLOC_END) {
        
        // no, return error
        return E_ALLOC_NOMEM;
    }
    
    // save old address
    unsigned long oldPointer = this->_pointer;
    
    // allocate
    this->_pointer = oldPointer + size;
    
    // return the address
    return oldPointer;
}

void Core::StaticAllocator::free(unsigned long address) {
 
    // not supported
    address = 0;
    
    /*! \todo print address when debugging */
    
#ifdef DEBUG
    this->frees++; // do record this occurance
#endif
    
}

#ifdef DEBUG
void Core::StaticAllocator::printDebug() {
    
    /* TODO: implement me */
}
#endif

unsigned long Core::StaticAllocator::startResource() {
    
    return E_SUCCESS;
}

const char* Core::StaticAllocator::getResourceName() {
    
    return "StaticAllocator";
}
