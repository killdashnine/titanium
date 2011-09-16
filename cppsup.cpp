/***************************************************************************
 *            cppsup.cpp
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

/*! \file cppsup.cpp
 *  \brief C++ support
 *   
 *  This file includes support routines for C++ with a GCC compiler
 *
 *  \see http://wiki.osdev.org/C_PlusPlus
 */

#include <core/kernelallocator.h>

/*! Function that gets called by GCC when doing a pure virtual function call
 */
extern "C" void __cxa_pure_virtual() {
    
    /*! \todo print error message */
}

/*! Overload function for the C++ "new" operator
 *
 *\param size The size to allocate for the object
 *\return A pointer to the allocated memory
 */
void* operator new (unsigned int size) {

    return reinterpret_cast<void*>(Core::KernelAllocator::getInstance()->allocate(size));
}

/*! Overload function for the C++ "new[]" operator
 *
 *\param size The size to allocate for the object
 *\return A pointer to the allocated memory
 */
void* operator new[] (unsigned int size) {
    
    return reinterpret_cast<void*>(Core::KernelAllocator::getInstance()->allocate(size));
}

/*! Overload function for the C++ "delete" operator
 *
 *\param address A pointer to the memory that needs to be freed
 */
void operator delete (void* address) {
    
    Core::KernelAllocator::getInstance()->free(reinterpret_cast<unsigned long>(address));
}

/*! Overload function for the C++ "delete[]" operator
 *
 *\param address A pointer to the memory that needs to be freed
 */
void operator delete[] (void* address) {
    
    Core::KernelAllocator::getInstance()->free(reinterpret_cast<unsigned long>(address));
}

// declare C-safe callable function headers
extern "C" {
    
        int __cxa_atexit(void (*f)(void *), void *p, void *d);
        void __cxa_finalize(void *d);
};

/*! When the kernel exits we should call:
 *
 * void __cxa_finalize(void *d);
 *
 * with d = 0 in order to destroy all with __cxa_atexit registered objects. 
 * Objects, which were registered first with __cxa_atexit, must be destroyed last by __cxa_finalize. 
 * You must provide the symbol __dso_handle in your executable. 
 * Only the address of this symbol is needed, because GCC calls __cxa_atexit with &__dso_handle. 
 */
void *__dso_handle; 

/*! Maximum numbers of destructors allowed */
#define MAX_DESTRUCTORS         32

/*! \brief Destructor object
 * 
 * A list of destructor-objects used for destructors */
struct object {
    
        /*! A function-pointer to the destructor */
        void (*f)(void*);
        
        /*! The parameter for the destructor */
        void *p;
        
        /*! The "home DSO" (DSO = dynamic shared object) */
        void *d;
        
} object[MAX_DESTRUCTORS] = {{0,0,0}};

/*! reference variable for counting destructors*/
unsigned int iObject = 0;

/*! Function for registering destructors
 *
 *\param f A function-pointer to the destructor
 *\param p The parameter for the destructor
 *\param d The "home DSO" (DSO = dynamic shared object). 
 *\return This function should save all three parameters and if successful return zero, on failure nonzero.
 */
int __cxa_atexit(void (*f)(void *), void *p, void *d) {

    // check if we are out of deconstructor objects
    if (iObject >= MAX_DESTRUCTORS) {
        
        // FIXME: maybe panic here?
        return -1;
    }
    
    // initialize structure
    object[iObject].f = f;
    object[iObject].p = p;
    object[iObject].d = d;
    
    // increase destructor count
    ++iObject;
    
    // all is ok
    return 0;
}

/*! Function for destructing all objects
 *  
 * Objects, which were registered first with __cxa_atexit must 
 * be destroyed last by __cxa_finalize(void *d). 
 *
 *\param d Not used
 */
void __cxa_finalize(void *d) {
    
    // avoid warning
    
    d = 0;
    
    // initialize loop
    unsigned int i = iObject;
    
    // call all destructors
    for (; i > 0; --i) {
            
        // decrease number of registerd destructors
        --iObject;
        
        // call the destructor
        object[iObject].f(object[iObject].p);
    }
}



