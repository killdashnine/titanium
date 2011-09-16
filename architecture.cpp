/* 
 * File:   Architecture.cpp
 * Author: matthias
 * 
 * Created on January 22, 2011, 3:44 PM
 */

#include <core/console.h>
#include <core/architecture.h>
#include <I386/gdt.h>

void Core::Architecture::detectArchitecture() {
    Console* console = Core::Console::getInstance();
    console->write("Detected architecture: ");
#ifdef __i386__
    console->write("i386\n");
    I386::GDT::getInstance();
#endif
}
