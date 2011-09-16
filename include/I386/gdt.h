/***************************************************************************
 *            gdt.h
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

/*! \file gdt.h
 *  \brief Manager for the I386 Global Descriptor Table
 *   
 *  This file defines the GDT Singleton class and GDT support structures.
 *
 */

#ifndef _GDT_H
#define	_GDT_H

#include <core/resource.h>

namespace I386 {
    
    /*! Number of descriptors we need */
    #define GDT_SIZE                    3
    
    /*! Code segment */
    #define KERNEL_CS                  0x08
    
    /*! Data segment */
    #define KERNEL_DS                  0x10
    
    /*!\todo: define flags */

    /*! \struct GDTEntry
     *\brief GDTEntry
     *
     * This struct defines a GDT entry
     */
    struct GDTEntry {
        
        /*! The lower part of the limit */
        unsigned short limit_low;
        
        /*! The lower part of the base address */
        unsigned short base_low;
        
        /*! The middle part of tthe base address */
        unsigned char base_middle;
        
        /*! Access type */
        unsigned char access;
        
        /*! Granularity */
        unsigned char granularity;
        
        /*! The higher part of the base */
        unsigned char base_high;

    } __attribute__((packed));

    /*! \struct GDTPointer
     *\brief GDTPointer
     *
     * This struct defines the GDT Pointer type
     */
    struct GDTPointer {
        
        /*! The limit i.e number of descriptors in GDT table */
        unsigned short limit;
        
        /*! Base address of the GDT Table */
        unsigned int base;

    } __attribute__((packed));

    
    /*! \class GDT
     *\brief GDT Manager
     *
     * This class handles the Global Descriptor Table for the i386 CPU
     */
    class GDT : public Core::Resource {
        
    public:
        
        /*! A static function to get the singleton instance for the GDT manager
        *
        *\return The GDT instance
        */
        static GDT* getInstance();
        
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
        GDT();
        
    private:
        
        /*! Function for setting a gate to the Global Descriptor Table
         *
         *\param segment The index of the GDTEntry in the GDT table
         *\param base The base address of the segment
         *\param limit The limit of the segment
         *\param access The access type
         *\param granularity The type of granularity 
         */
        void setGate(int segment, unsigned long base, unsigned long limit, unsigned char access, unsigned char granularity);
        
        /*! A static instance of the class for singleton usage */ 
        static GDT* _instance;
        
        /*! The entries for the Global Descriptor Table */
        struct GDTEntry* _gdtEntries;
 
        /*! The pointer to the Global Descriptor Table */
        struct GDTPointer* _gdtPointer;
        
    };
}
#endif	/* _GDT_H */

