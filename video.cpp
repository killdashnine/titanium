/***************************************************************************
 *            video.cpp
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

/*! \file video.cpp
 *  \brief Video Driver
 *   
 *  This file implements the Video class. The video class handles I/O to the screen.
 *  The class uses a Sigleton design pattern.
 *
 */

#include <core/video.h>
#include <core/terminal.h>
#include <config.h>
#include <errors.h>

// set instance pointer to a null pointer
Core::Video* Core::Video::_instance = 0;

// set default location for the video buffer
short* Core::Video::_buffer = reinterpret_cast<short*>(VIDEO_BASE);

Core::Video* Core::Video::getInstance() {
    
    // check for exsisting instance
    if(_instance == 0) {
        
        // none found, create new instance
        _instance = new Video();
        
        // check if we got a valid address
        if(_instance == reinterpret_cast<Video*>(E_ALLOC_NOMEM)) {
            
            _instance = 0;
            
            // no, major oops here!
            return E_FAILURE;
        }
    }
    
    // return the instance
    return _instance;
}

Core::Video::Video() {
    
    // clear screen from output
    this->clearBuffer();
}

void Core::Video::clearBuffer() {
    
    // loop through the buffer
    for(int n = 0; n < VIDEO_SIZE; n++) {
        
        // and clear data
        this->_buffer[n] = 0;
    }
}

unsigned long Core::Video::write(void* buffer, unsigned long size) {
    
    // check for buffer overflow
    if(size != VIDEO_SIZE) {
        
        return E_BUFFER_OVERFLOW;
    }
    
    short* sourceBuffer = static_cast<short*>(buffer);
    
    // copy memory
    for(unsigned int n = 0; n < size; n++) {
        
        this->_buffer[n] = sourceBuffer[n];
    }
    
    return E_SUCCESS;
}

unsigned long Core::Video::getTerminalType() {
    
    return TERMINAL_TYPE_VIDEO;
}

unsigned long Core::Video::startResource() {
    
    return E_SUCCESS;
}

const char* Core::Video::getResourceName() {
    
    return "Video";
}

