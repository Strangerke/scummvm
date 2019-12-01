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

#ifndef ULTIMA8_WORLD_FIREBALLPROCESS_H
#define ULTIMA8_WORLD_FIREBALLPROCESS_H

#include "ultima8/kernel/process.h"
#include "ultima8/usecode/intrinsics.h"

namespace Ultima8 {

class Item;

class FireballProcess : public Process {
public:
	FireballProcess();
	FireballProcess(Item *item, Item *target);

	// p_dynamic_cast stuff
	ENABLE_RUNTIME_CLASSTYPE();

	virtual void run();

	virtual void terminate();

	INTRINSIC(I_TonysBalls);

	bool loadData(IDataSource *ids, uint32 version);
protected:
	virtual void saveData(ODataSource *ods);

	void explode();

	int xspeed, yspeed;
	ObjId tail[3];
	ObjId target;
	uint16 age;
};

} // End of namespace Ultima8

#endif
