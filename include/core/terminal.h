/***************************************************************************
 *            terminal.h
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

/*! \file terminal.h
 *  \brief Terminal Driver
 *   
 *  This file defines the Terminal class. The terminal class handles I/O to a console.
 *
 */

#ifndef _TERMINAL_H
#define	_TERMINAL_H

#include <config.h>
#include <core/characterdevice.h>
#include <core/resource.h>

namespace Core {

/*! Use screen as ouput */
#define TERMINAL_TYPE_VIDEO                     0x01

/*! Use serial port as output */
#define TERMINAL_TYPE_SERIAL                    0x02

// background and foreground colors        

/*! Black background/foreground color for use on terminal */
#define TERMINAL_BLACK                          0x00

/*! Blue background/foreground color for use on terminal */
#define TERMINAL_BLUE                           0x01

/*! Green background/foreground color for use on terminal */
#define TERMINAL_GREEN                          0x02

/*! Cyan background/foreground color for use on terminal */
#define TERMINAL_CYAN                           0x03

/*! Red background/foreground color for use on terminal */
#define TERMINAL_RED                            0x04

/*! Magenta background/foreground color for use on terminal */
#define TERMINAL_MAGENTA                        0x05

/*! Brown background/foreground color for use on terminal */
#define TERMINAL_BROWN                          0x06

/*! Lightgray background/foreground color for use on terminal */
#define TERMINAL_LIGHTGRAY                      0x07

// foreground colors

/*! Darkgray foreground color for use on terminal */
#define TERMINAL_DARKGRAY                       0x08

/*! Lightblue foreground color for use on terminal */
#define TERMINAL_LIGHTBLUE                      0x09

/*! Lightgreen foreground color for use on terminal */
#define TERMINAL_LIGHTGREEN                     0x0a

/*! Lightcyan foreground color for use on terminal */
#define TERMINAL_LIGHTCYAN                      0x0b

/*! Lightred foreground color for use on terminal */
#define TERMINAL_LIGHTRED                       0x0c

/*! Lightmagenta foreground color for use on terminal */
#define TERMINAL_LIGHTMAGENTA                   0x0d

/*! Lightyellow foreground color for use on terminal */
#define TERMINAL_YELLOW                         0x0e

/*! White foreground color for use on terminal */
#define TERMINAL_WHITE                          0x0f

/*! Macro for generating a console color attribute
 *
 *\param background The background color
 *\param foreground The foreground color
 *\param blink Wether to blink or not
 *\return A short attribute
 */
#define MAKE_COLOR(background, foreground, blink)       ((background << 4) | (foreground & 0x0F) | (~blink << 7)) << 8 
    
/*! \class Terminal
 *\brief Terminal class
 *
 * This class is a control structure for virtual terminals
 */
class Terminal : public Resource {
    
public:
    
    /*! Constructor for the Terminal class
     *
     *\param device An instance of a CharacterDevice to use as output
     *
     */
    Terminal(CharacterDevice* device);
    
    /*! Function for write a sequence of chars to a virtual terminal
     *
     *\param sequence The sequence to write
     *\return Status of the I/O operation
     */
    unsigned long write(const char* sequence);
    
    /*! Function to put a single character in the Virtual terminal's buffer
     *
     *\param x The x position
     *\param y The y position
     *\param c The character to write
     *\return Status of the I/O operation
     */
    unsigned long put(int x, int y, char c);
    
    /*! Function to put a single character in the Virtual terminal's buffer
     *
     *\param x The x position
     *\param y The y position
     *\param c The character to write
     *\param color The color to use
     *\return Status of the I/O operation
     */
    unsigned long put(int x, int y, char c, short color);
    
    /*! Function to set the current color for the text.
     *  Only valid when the Terminal type is TERMINAL_TYPE_VIDEO
     *
     *\param color The color created by MAKE_COLOR
     *\return Status of the operation (E_INVALID_TERMINAL when not TERMINAL_TYPE_VIDEO)
     */
    unsigned long setColor(short color);
    
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
    
private:
    
    // we only want the Console class to I/O with this class
    friend class Console;
    
    /*! instance of the character device to write to */
    CharacterDevice* _device;
    
    /*! current x position of the cursor */
    int _x;
    
    /*! current y position of the cursor */
    int _y;
    
    /*! type of terminal */
    int _type;
    
    /*! The internal buffer */
    short* _buffer;
    
    /*! The size of the internal buffer */
    int _bufferSize;
    
    /*! The color for writing text, unused when type is TERMINAL_TYPE_SERIAL */
    short _color;
    
    /*! Function for scrolling the buffer */
    void scroll();
    
    /*! Function for putting one character in the buffer
     *
     *\param c The character to put
     */
    void put(char c);
};

} /* namespace Core */

#endif	/* _TERMINAL_H */

