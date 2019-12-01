/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef ULTIMA8_GRAPHICS_TYPEFLAGS_H
#define ULTIMA8_GRAPHICS_TYPEFLAGS_H

#include "ultima8/std/containers.h"
#include "ultima8/graphics/shape_info.h"

namespace Ultima8 {

class IDataSource;

class TypeFlags {
public:
	TypeFlags();
	~TypeFlags();

	void load(IDataSource *ds);
	ShapeInfo *getShapeInfo(uint32 shape);

private:
	void loadWeaponInfo();
	void loadArmourInfo();
	void loadMonsterInfo();

	std::vector<ShapeInfo> shapeInfo;
};

} // End of namespace Ultima8

#endif
