/*
 This file is part of MMOServer. For more information, visit http://swganh.com
 
 Copyright (c) 2006 - 2010 The SWG:ANH Team

 MMOServer is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 MMOServer is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with MMOServer.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LIBANH_COMPONENT_COMPONENT_LOADER_INTERFACE_H_
#define LIBANH_COMPONENT_COMPONENT_LOADER_INTERFACE_H_

#include <memory>
#include <anh/component/component_interface.h>

namespace anh {
namespace component {

class ComponentLoaderInterface
{
public:
	virtual bool Load(std::shared_ptr<ComponentInterface> comp) = 0;
	virtual void Unload(std::shared_ptr<ComponentInterface> comp) = 0;
};

}
}

#endif // LIBANH_COMPONENT_LOADER_FACTORY_INTERFACE_H_