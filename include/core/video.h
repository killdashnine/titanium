/***************************************************************************
 *            video.h
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

/*! \file video.h
 *  \brief Video Driver
 *   
 *  This file defines the Video class. The video class handles I/O to the screen.
 *  The class uses a Sigleton design pattern.
 *
 */

#ifndef _VIDEO_H
#define	_VIDEO_H

#include <core/characterdevice.h>
#include <core/resource.h>

namespace Core {

/*! \class Video
 *\brief Video class
 *
 * This class handles basic I/O to the video RAM.
 * It uses the Singleton Pattern to ensure there is only one instance. To get
 * the instance you should use the getInstance() method.
 */
class Video : public CharacterDevice {
    
public:
    
    /*! A static function to get the singleton instance for the video driver
     *
     *\return The Video instance
     */
    static Video* getInstance();
    
    /*! Function for what kind of terminal is supported for this CharacterDevice
     *
     *\return The type of terminal
     *\see terminal.h
     */
    unsigned long getTerminalType();
    
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
    
protected:
    
    /*! Protected constructor to ensure singleton usage */
    Video();
    
private:
    
    // we only want the Console class to I/O with this class
    friend class Console;
    
    /*! Function to clear the screen's contents */
    void clearBuffer();
    
    /*! Function for writing to a Character Device's buffer 
     *
     *\param buffer The buffer to copy
     *\param size The size of the buffer
     *\return An error code or E_SUCCESS
     */
    unsigned long write(void* buffer, unsigned long size);
    
    /*! A static instance of the class for singleton usage */ 
    static Video* _instance;
    
    /*! The video buffer */
    static short* _buffer;
    
};

} /* namespace Core */

#endif	/* _VIDEO_H */

