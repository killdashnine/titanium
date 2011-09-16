/***************************************************************************
 *            gdt.cpp
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

/*! \file gdt.cpp
 *  \brief GDT Manager
 *   
 * This file defines the GDT class. It handles the i386 Global Descriptor Table 
 *
 */

#include <I386/gdt.h>
#include <errors.h>

// set instance pointer to a null pointer
I386::GDT* I386::GDT::_instance = 0;

I386::GDT* I386::GDT::getInstance() {
    
    // check for exsisting instance
    if(_instance == 0) {
        
        // none found, create new instance
        _instance = new GDT();
        
        // check if we got a valid address
        if(_instance == reinterpret_cast<GDT*>(E_ALLOC_NOMEM)) {
            
            _instance = 0;
            
            // no, major oops here!
            return E_FAILURE;
        }
    }
    
    // auto register
    Core::ResourceManager::getInstance()->registerResource(_instance);
    
    // return the instance
    return _instance;
}

unsigned long I386::GDT::startResource() {
    
    // setup the GDT pointer
    this->_gdtPointer->limit = (sizeof(struct I386::GDTEntry) * GDT_SIZE) - 1;
    this->_gdtPointer->base = reinterpret_cast<unsigned int>(this->_gdtEntries);
    
    // null descriptor
    this->setGate(0, 0, 0, 0, 0);
    
    // code segment for ring0
    this->setGate(KERNEL_CS, 0, 0xffffffff, 0x9a, 0xcf);
    
    // data segment for ring1
    this->setGate(KERNEL_DS, 0, 0xffffffff, 0x92, 0xcf);
    
    // load GDT pointer
    asm volatile ("lgdt %0" : "=m" (*this->_gdtPointer));
    
    // jump to new segment
    asm volatile("ljmp $(0x08), $reload_segments");
    
    // we need to set al non-code segments to KERNEL_DS
    asm volatile("reload_segments:");
    asm volatile("movl $0x10, %eax");
    asm volatile("movl %eax, %ds");
    asm volatile("movl %eax, %es");
    asm volatile("movl %eax, %fs");
    asm volatile("movl %eax, %gs");
    asm volatile("movl %eax, %ss");
     
    return E_SUCCESS;
}

const char* I386::GDT::getResourceName() {
    
    return "Global Descriptor Table";
}

I386::GDT::GDT() {
    
    this->_gdtPointer = new struct I386::GDTPointer();
    this->_gdtEntries = reinterpret_cast<struct I386::GDTEntry*>(new struct I386::GDTEntry[GDT_SIZE]);
}

void I386::GDT::setGate(int segment, unsigned long base, unsigned long limit, unsigned char access, unsigned char granularity) {
    
    int index = segment / 8;
    
    // setup base address
    this->_gdtEntries[index].base_low = (base & 0xffff);
    this->_gdtEntries[index].base_middle = (base >> 16) & 0xff;
    this->_gdtEntries[index].base_high = (base >> 24) & 0xff;
    
    // setup limits
    this->_gdtEntries[index].limit_low = (limit & 0xffff);
    this->_gdtEntries[index].granularity = ((limit >> 16) & 0x0f);
    
    // setup the granularity and access flags
    this->_gdtEntries[index].granularity |= (granularity & 0xf0);
    this->_gdtEntries[index].access = access;
}
