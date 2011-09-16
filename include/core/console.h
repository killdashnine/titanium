/***************************************************************************
 *            console.h
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

/*! \file console.h
 *  \brief Console Driver
 *   
 *  This file defines the Console class. The console class handles I/O to Character Devices and Terminals.
 *  The class uses a Sigleton design pattern.
 *
 */

#ifndef _CONSOLE_H
#define	_CONSOLE_H

#include <core/terminal.h>
#include <core/resource.h>

namespace Core {

/*! \class Console
 *\brief Console class
 *
 * The console class handles I/O to Character Devices and Terminals.
 * It uses a singleton pattern to ensure only one console exists at a time.
 */
class Console : public Resource {
    
public:
    
    /*! A static function to get the singleton instance for the console driver
     *
     *\return The Console instance
     */
    static Console* getInstance();
    
    /*! Function to switch to another virtual terminal
     *
     *\param terminal The terminal to switch to
     */
    void switchTerminal(Terminal* terminal);
    
    /*! Function to get the current active virtual terminal
     *
     *\return The current active virtual terminal
     */ 
    Terminal* getActiveTerminal();
    
    /*! Function to put a single character on the current active virtual terminal
     *
     *\param x The x location of the character
     *\param y The y location of the character
     *\param c The character
     */
    void put(int x, int y, char c);
    
    /*! Function to write a sequence of characters to the current active virtual terminal
     *
     *\param sequence The sequence of chars to write
     */
    void write(const char* sequence);
    
    /*! Function to write a sequence of characters to the current active virtual terminal
     *
     *\param sequence The sequence of chars to write
     *\param color The color to use
     */
    void write(const char* sequence, short color);
    
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
    Console();
    
private:
    
    /*! Function to copy the Terminal's buffer to the Character Device's buffer */
    void copyBuffer();
    
   /*! A static instance of the class for singleton usage */ 
    static Console* _instance; 
    
    /*! The instance of the current active terminal */
    Terminal* _activeTerminal;
    
};

} /* namespace Core */

#endif	/* _CONSOLE_H */
