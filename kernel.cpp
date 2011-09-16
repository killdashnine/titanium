/***************************************************************************
 *            kernel.cpp
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

/*! \file kernel.cpp
 *  \brief Kernel initialisation
 *   
 *  This file includes the initialisation methods for booting the kernel's features.
 */

#include <config.h>
#include <errors.h>
#include <core/video.h>
#include <grub/multiboot.h>

#include <core/staticallocator.h>
#include <core/kernelallocator.h>

#include <core/console.h>
#include <core/terminal.h>

#include <core/resource.h>
#include <grub/grub.h>

#include <core/architecture.h>

/*! High level code entrypoint
 *
 *\param magic GRUB magic number
 *\param address Pointer to to the GRUB multiboot information structure
 *\return The result of the initialization routines. Only on failure.
 */
extern "C" int kernel(unsigned long magic, unsigned long address) {
    
    // create a new terminal
    Core::Terminal* terminal = new Core::Terminal(Core::Video::getInstance());
    
    // set new colors
    terminal->setColor(MAKE_COLOR(TERMINAL_BLACK, TERMINAL_WHITE, FALSE));
    
    Core::Console* console = Core::Console::getInstance();
    
    // switch to it
    console->switchTerminal(terminal);
    
    // write welcome message
    console->write("Titanium kernel version: ");
    console->write(VERSION_STRING);
    console->write("\nCopyright Matthias van der Vlies <matthias@eenweiland.nl> 2008-");
    console->write(YEAR_STRING);
    console->write("\nCompiled by ");
    console->write(USER);
    console->write("@");
    console->write(HOST);
    console->write(" on ");
    console->write(__DATE__);
    console->write(" ");
    console->write(__TIME__);
    console->write(" using GCC ");
    console->write(__VERSION__);
    console->write("\n");
    
    // back to normal coloring scheme
    terminal->setColor(MAKE_COLOR(TERMINAL_BLACK, TERMINAL_LIGHTGRAY, FALSE));
    
    Core::ResourceManager* manager = Core::ResourceManager::getInstance();
    
    // static resource initialisation
    manager->registerResource(Core::KernelAllocator::getInstance());
    manager->registerResource(Core::StaticAllocator::getInstance());
    manager->registerResource(Core::Video::getInstance());
    manager->registerResource(console);
    manager->registerResource(terminal);
    
    // check grub
    Grub::GrubChecker* grubChecker = new Grub::GrubChecker(magic, address);
    
    /*!\todo print memory size */
    grubChecker->getMemorySize();

    Core::Architecture::detectArchitecture();
    
    // infinite loop
    for(;;);
    
    return E_SUCCESS;
}
