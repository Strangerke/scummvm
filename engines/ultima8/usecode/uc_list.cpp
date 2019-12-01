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

#include "ultima8/misc/pent_include.h"

#include "ultima8/usecode/UCList.h"
#include "ultima8/usecode/uc_machine.h"
#include "ultima8/filesys/idata_source.h"
#include "ultima8/filesys/odata_source.h"

namespace Ultima8 {

uint16 UCList::getStringIndex(uint32 index) {
	return elements[index * 2] + (elements[index * 2 + 1] << 8);
}

std::string &UCList::getString(uint32 index) {
	uint16 sindex = getStringIndex(index);
	return UCMachine::get_instance()->getString(sindex);
}

void UCList::freeStrings() {
	UCMachine *ucm = UCMachine::get_instance();
	for (unsigned int i = 0; i < size; i++) {
		ucm->freeString(getStringIndex(i));
	}
	free();
}

void UCList::copyStringList(UCList &l) {
	UCMachine *ucm = UCMachine::get_instance();
	freeStrings();
	for (unsigned int i = 0; i < l.size; i++) {
		uint16 s = ucm->duplicateString(l.getStringIndex(i));
		uint8 tmp[2]; // ugly...
		tmp[0] = static_cast<uint8>(s & 0xFF);
		tmp[1] = static_cast<uint8>(s >> 8);
		append(tmp);
	}
}

void UCList::unionStringList(UCList &l) {
	UCMachine *ucm = UCMachine::get_instance();
	// take the union of two stringlists
	// i.e., append the second to this one, removing any duplicates
	for (unsigned int i = 0; i < l.size; i++) {
		if (!stringInList(l.getStringIndex(i))) {
			append(l[i]);
		} else {
			// free it if we're not keeping it
			ucm->freeString(l.getStringIndex(i));
		}
	}
	l.free(); // NB: do _not_ free the strings in l, since they're in this one
}

void UCList::substractStringList(UCList &l) {
	for (unsigned int i = 0; i < l.size; i++)
		removeString(l.getStringIndex(i));
}

bool UCList::stringInList(uint16 s) {
	std::string str = UCMachine::get_instance()->getString(s);
	for (unsigned int i = 0; i < size; i++)
		if (getString(i) == str)
			return true;

	return false;
}

void UCList::assignString(uint32 index, uint16 str) {
	// assign string str to element index
	// free old contents of element index; take ownership of str(?)

	UCMachine::get_instance()->freeString(getStringIndex(index));
	elements[index * elementsize] = static_cast<uint8>(str & 0xFF);
	elements[index * elementsize + 1] = static_cast<uint8>(str >> 8);
}

void UCList::removeString(uint16 s, bool nodel) {
	// do we need to erase all occurences of str or just the first one?
	// (deleting all, currently)
	std::string str = UCMachine::get_instance()->getString(s);
	for (unsigned int i = 0; i < size; i++) {
		if (getString(i) == str) {
			// free string
			if (!nodel)
				UCMachine::get_instance()->freeString(getStringIndex(i));

			// remove string from list
			elements.erase(elements.begin() + i * elementsize,
			               elements.begin() + (i + 1)*elementsize);
			size--;
			i--; // back up a bit
		}
	}
}

void UCList::save(ODataSource *ods) {
	ods->write4(elementsize);
	ods->write4(size);
	ods->write(&(elements[0]), size * elementsize);
}


bool UCList::load(IDataSource *ids, uint32 version) {
	elementsize = ids->read4();
	size = ids->read4();
	elements.resize(size * elementsize);
	ids->read(&(elements[0]), size * elementsize);

	return true;
}

} // End of namespace Ultima8
