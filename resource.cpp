/***************************************************************************
 *            resource.cpp
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

/*! \file resource.cpp
 *  \brief  ResourceManager
 *   
 *  This file implements the ResourceManager class.
 *
 */

#include <core/resource.h>
#include <core/console.h>
#include <errors.h>

Core::ResourceManager::ResourceManager() {
    
    Core::Console* console = Core::Console::getInstance();
    
    /*! \todo: implement me */
    
    console->write("Initialised resource manager\n");
}

unsigned long Core::ResourceManager::registerResource(Resource* resource) {
    
    Core::Console* console = Core::Console::getInstance();
    
    console->write("Registering resource: ");
    console->write(resource->getResourceName());
    console->write("...");
    
    unsigned long status = resource->startResource();
    
    switch(status) {
        
        case E_SUCCESS:
            console->write("OK\n", MAKE_COLOR(TERMINAL_BLACK, TERMINAL_GREEN, FALSE));
            
            /*! \todo register resource */
            break;
            
        case E_FAILURE:
            console->write("FAILED\n", MAKE_COLOR(TERMINAL_BLACK, TERMINAL_RED, FALSE));
            break;
            
        case E_PANIC:
            console->write("PANIC\n", MAKE_COLOR(TERMINAL_BLACK, TERMINAL_RED, FALSE));
            
            /*! \todo clean panic handling */
            asm("hlt");
            break;
        
        case E_WARNING:
            console->write("WARNING\n", MAKE_COLOR(TERMINAL_BLACK, TERMINAL_YELLOW, FALSE));
            break;
            
        default:
            console->write("UNKNOWN\n", MAKE_COLOR(TERMINAL_BLACK, TERMINAL_YELLOW, FALSE));
            break;
            
    }
    
    return status;
}

// set instance pointer to a null pointer
Core::ResourceManager* Core::ResourceManager::_instance = 0;

Core::ResourceManager* Core::ResourceManager::getInstance() {
    
    // check for exsisting instance
    if(_instance == 0) {
        
        // none found, create new instance
        _instance = new ResourceManager();
        
        // check if we got a valid address
        if(_instance == reinterpret_cast<ResourceManager*>(E_ALLOC_NOMEM)) {
            
            _instance = 0;
            
            // no, major oops here!
            return E_FAILURE;
        }
    }
    
    // return the instance
    return _instance;
}
