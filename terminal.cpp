/***************************************************************************
 *            terminal.cpp
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

/*! \file terminal.cpp
 *  \brief Terminal Driver
 *   
 *  This file implements the Terminal class. The terminal class handles I/O to a virtual terminal.
 *
 */

#include <config.h>
#include <errors.h>
#include <core/terminal.h>

Core::Terminal::Terminal(CharacterDevice* device) {
    
    // assign local data
    this->_device = device;
    this->_type = device->getTerminalType();
    
    if(this->_type == TERMINAL_TYPE_VIDEO) {
        
        // set default terminal color
        this->_color = MAKE_COLOR(TERMINAL_BLACK, TERMINAL_LIGHTGRAY, FALSE);
    
        // get memory for the buffer
        this->_buffer = new short[VIDEO_SIZE * 2];
        this->_bufferSize = VIDEO_SIZE;
        
        // "zero" the buffer
        for(int n = 0; n < VIDEO_SIZE; n++) {
            
            this->_buffer[n] = 0 | this->_color;
        }
    }
}

unsigned long Core::Terminal::put(int x, int y, char c) {
    
    // check on which device to put it
    if(this->_type == TERMINAL_TYPE_VIDEO) {
        
        // copy into the buffer
        this->_buffer[(y * 80 + x)] = c | this->_color;
        
        return E_SUCCESS;
    }
    
    return E_INVALID_TERMINAL;
}

unsigned long Core::Terminal::put(int x, int y, char c, short color) {
    
    // check on which device to put it
    if(this->_type == TERMINAL_TYPE_VIDEO) {
        
        // copy into the buffer
        this->_buffer[(y * 80 + x)] = c | color;
        
        return E_SUCCESS;
    }
    
    return E_INVALID_TERMINAL;
}

unsigned long Core::Terminal::setColor(short color) {
    
    if(this->_type == TERMINAL_TYPE_VIDEO) {
        
        this->_color = color;
        
        return E_SUCCESS;
    }
    
    return E_INVALID_TERMINAL;
}

unsigned long Core::Terminal::write(const char* sequence) {
    
    if(this->_type == TERMINAL_TYPE_VIDEO) {
        
        // loop through the sequence (halt when string gets too big or ends)
        for(int n = 0; n < VIDEO_SIZE && sequence[n] != 0; n++) {
            
            // and copy
            this->put(sequence[n]);
        }
        
        return E_SUCCESS;
    }
    
    return E_FAILURE;
}

void Core::Terminal::put(char c) {
    
    // Handle a backspace, by moving the cursor back one space
    if(c == 0x08)
    {
        if(this->_x != 0) {
	
            this->_x--;
            this->_buffer[this->_y * 80 + this->_x] = ' ';
	}
    }
    
    // a tab
    else if(c == 0x09) {
        
        this->_x = this->_x + 8;
    }
    // Handles a 'Carriage Return', which simply brings the cursor back to the margin
    else if(c == '\r') {
        
        this->_x = 0;
    }
    
    // new line
    else if(c == '\n') {
        
        this->_x = 0;
        this->_y++;
    }
    // normal char
    else if(c >= ' ') {
        
        this->_buffer[this->_y * 80 + this->_x] = c | this->_color;
        
        this->_x++;
    }

    // end of line detection
    if(this->_x >= 80) {
        
        this->_x = 0;
        this->_y++;
    }

    // Scroll the screen if needed
    this->scroll();
}

void Core::Terminal::scroll() {
    
    // TODO: fixme
}

unsigned long Core::Terminal::startResource() {
    
    return E_SUCCESS;
}

const char* Core::Terminal::getResourceName() {
    
    /*! \todo Terminal name */
    return "Terminal";
}
