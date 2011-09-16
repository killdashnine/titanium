/***************************************************************************
 *            console.cpp
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

/*! \file console.cpp
 *  \brief Console Driver
 *   
 *  This file implements the Console class. The console class handles I/O to a Character device.
 *  The class uses a Sigleton design pattern.
 *
 */

#include <core/console.h>
#include <config.h>
#include <errors.h>
#include <I386/i386.h>

// set instance pointer to a null pointer
Core::Console* Core::Console::_instance = 0;

Core::Console* Core::Console::getInstance() {
    
    // check for exsisting instance
    if(_instance == 0) {
        
        // none found, create new instance
        _instance = new Console();
        
        // check if we got a valid address
        if(_instance == reinterpret_cast<Console*>(E_ALLOC_NOMEM)) {
            
            _instance = 0;
            
            // no, major oops here!
            return E_FAILURE;
        }
    }
    
    // return the instance
    return _instance;
}

Core::Console::Console() {
    
    // do nothing
}

Core::Terminal* Core::Console::getActiveTerminal() {
    
    return this->_activeTerminal;
}

void Core::Console::switchTerminal(Terminal* terminal) {
    
    this->_activeTerminal = terminal;
    
    // clear screen
    this->_activeTerminal->_device->clearBuffer();
   
    // copy new contents
    this->copyBuffer();
}

void Core::Console::put(int x, int y, char c) {
    
    this->_activeTerminal->put(x, y, c);
    
    // copy new contents
    this->copyBuffer();
}

void Core::Console::copyBuffer() {
    
    // copy buffer from Terminal to CharacterDevice
    this->_activeTerminal->_device->write(this->_activeTerminal->_buffer, this->_activeTerminal->_bufferSize);
}

void Core::Console::write(const char* sequence) {
    
    this->_activeTerminal->write(sequence);
    
    // do we need to update a cursor?
    if(this->_activeTerminal->_type == TERMINAL_TYPE_VIDEO) {
        
        // put blinking character
        this->_activeTerminal->put(this->_activeTerminal->_x, this->_activeTerminal->_y, ' ', this->_activeTerminal->_color | 1 << 15);
        
        unsigned position = this->_activeTerminal->_y * 80 + this->_activeTerminal->_x;
        
        I386::writePortByte(0x3d4, 14);
        I386::writePortByte(0x3d5, position >> 8);
        I386::writePortByte(0x3d4, 15);
        I386::writePortByte(0x3d5, position);
    }
    
    // copy new contents
    this->copyBuffer();
}

void Core::Console::write(const char* sequence, short color) {
    
    short oldColor = this->_activeTerminal->_color;
    
    this->_activeTerminal->setColor(color);
    
    this->_activeTerminal->write(sequence);
    
    this->_activeTerminal->setColor(oldColor);
    
    // do we need to update a cursor?
    if(this->_activeTerminal->_type == TERMINAL_TYPE_VIDEO) {
        
        // put blinking character
        this->_activeTerminal->put(this->_activeTerminal->_x, this->_activeTerminal->_y, ' ', this->_activeTerminal->_color | 1 << 15);
        
        unsigned position = this->_activeTerminal->_y * 80 + this->_activeTerminal->_x;
        
        I386::writePortByte(0x3d4, 14);
        I386::writePortByte(0x3d5, position >> 8);
        I386::writePortByte(0x3d4, 15);
        I386::writePortByte(0x3d5, position);
    }
    
    // copy new contents
    this->copyBuffer();
}

unsigned long Core::Console::startResource() {
    
    return E_SUCCESS;
}

const char* Core::Console::getResourceName() {
    
    return "Console";
}
