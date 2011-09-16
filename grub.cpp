/***************************************************************************
 *            grub.cpp
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

/*! \file grub.cpp
 *  \brief GrubChecker
 *   
 * This file defines the GrubChecker class. This class checks if the Multiboot info header provided by GRUB is correct.
 * It also parses the memory size of the system.
 *
 *\see http://www.gnu.org/software/grub/manual/multiboot/html_node/kernel_002ec.html#kernel_002ec
 */

#include <grub/grub.h>
#include <grub/multiboot.h>

#include <core/console.h>

#include <errors.h>

Grub::GrubChecker::GrubChecker(unsigned long magic, unsigned long address) {
    
    this->_address = address;
    this->_magic = magic;
    
    // auto register
    Core::ResourceManager::getInstance()->registerResource(this);
}

/*! Macro for checking if a flag-bit is set in a grub multibootheader
 *
 *\param flags The flag to check
 *\param bit The bit number of the bit to check */
#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

unsigned long Grub::GrubChecker::startResource() {
    
    bool valid = true;
    bool warning = false;
    
    Core::Console* console = Core::Console::getInstance();
    
    // Am I booted by a Multiboot-compliant boot loader?
    if (this->_magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        
        console->write("\nInvalid bootloader magic!!!");
        
        valid = false;
    }

    multiboot_info_t* multibootInfo = reinterpret_cast<multiboot_info_t*>(this->_address);
    
    // Are mem_* valid? 
    if (!CHECK_FLAG (multibootInfo->flags, 0)) {
        
        console->write("\nInvalid memory area");
        
        valid = false;
    }
    else {
        
        this->_memorySize = multibootInfo->mem_lower + multibootInfo->mem_upper;
    }
    
    // valid boot device?
    if (!CHECK_FLAG (multibootInfo->flags, 1)) {
        
        console->write("\nInvalid boot device");
        
        valid = false;
    }
    
    // Is the command line passed? 
    if (!CHECK_FLAG (multibootInfo->flags, 2)) {
        
        console->write("\nNo command line passed");
        
        valid = false;
    }
    
#ifdef DEBUG    
    // Are mods_* valid? 
    if (!CHECK_FLAG (multibootInfo->flags, 3)) {
        
        // just warn
        console->write("\nInvalid modules");
        
        warning = true;
    }
#endif
    
    // Bits 4 and 5 are mutually exclusive!
    if (CHECK_FLAG (multibootInfo->flags, 4) && CHECK_FLAG (multibootInfo->flags, 5)) {
        
        console->write("\nNo mutual exclusion on bit 4 and 6");
        
        valid = false;
    }

#ifdef DEBUG 
    // Is the symbol table of a.out valid? 
    if (!CHECK_FLAG (multibootInfo->flags, 4)) {
        
        // just warn
        console->write("\nInvalid a.out symble table");
        
        warning = true;
    }
    
    // Is the section header table of ELF valid?
    if (!CHECK_FLAG (multibootInfo->flags, 5)) {
        
        // just warn
        console->write("\nInvalid ELF section header");
        
        warning = true;
    }
#endif
    
    // Are mmap_* valid?
    if (!CHECK_FLAG (multibootInfo->flags, 6)) {
        
        console->write("\nInvalid mmap");
        
        valid = false;
    }

#ifdef DEBUG
    if(warning && valid) {
     
        console->write("\n");
        return E_WARNING;
        
    }
#endif
    
    if(valid)
        return E_SUCCESS;
    
    console->write("\n");
    
    // something really wrong!
    return E_PANIC;
}

const char* Grub::GrubChecker::getResourceName() {
    
    return "GRUB multiboot header";
}

unsigned long Grub::GrubChecker::getMemorySize() {
    
    return this->_memorySize;
}
