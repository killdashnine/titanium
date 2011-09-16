/***************************************************************************
 *            resource.h
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

/*! \file resource.h
 *  \brief  ResourceManager
 *   
 *  This file defines the ResourceManager class and the Resource interface.
 *
 */

#ifndef _RESOURCE_H
#define	_RESOURCE_H

namespace Core {

/*! \class Resource
 *\brief Resource class
 *
 * The resource class is an interface to implement for resources
 *
 */
class Resource {
    
public:
    
    /*! Function for starting a resource
     *
     *\return A status indicating E_SUCCES or E_FAILURE
     */
    virtual unsigned long startResource() = 0;
    
    /*! Function for getting the name of a resource
     *
     *\return The resource's name
     */
    virtual const char* getResourceName() = 0;
};


/*! \class ResourceManager
 *\brief ResourceManager class
 *
 * The ResourceManager class registers Resources and manages them.
 *
 */
class ResourceManager {
    
public:
    
    /*! Function to register and start a resource. Will not register when not able to start the resource
     *
     *\param resource The to be registered resource
     *\return E_SUCCESS or E_FAILURE
     */
    unsigned long registerResource(Resource* resource);
    
    /*! A static function to get the singleton instance for a ResourceManager
     *
     *\return The ResourceManager instance
     */
    static ResourceManager* getInstance();
    
private:
    
    /*! Singleton instance */
    static ResourceManager* _instance;
    
protected:
    
    /*! Singleton Constructor for the ResourceManager class */
    ResourceManager();
};

} /* namespace Core */

#endif	/* _RESOURCE_H */


