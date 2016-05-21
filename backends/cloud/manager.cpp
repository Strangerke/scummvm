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

#include "backends/cloud/manager.h"
#include "backends/cloud/dropbox/dropboxstorage.h"
#include "common/config-manager.h"

namespace Cloud {

Manager::Manager(): _currentStorage(0) {}

Manager::~Manager() { delete _currentStorage; }

void Manager::init() {
	if (ConfMan.hasKey("current_storage_type", "cloud")) {
		Common::String storageType = ConfMan.get("current_storage_type", "cloud");
		if (storageType == "Dropbox") _currentStorage = Dropbox::DropboxStorage::loadFromConfig();
		else warning("Unknown cloud storage type '%s' passed", storageType.c_str());
	}
	else {
		//this is temporary console offer to auth with Dropbox (because there is no other storage type yet anyway)
		Dropbox::DropboxStorage::authThroughConsole();
	}
}

Storage* Manager::getCurrentStorage() {
	return _currentStorage;
}

void Manager::syncSaves(Storage::BoolCallback callback) {
	Storage* storage = getCurrentStorage();
	if (storage) storage->syncSaves(callback);
}

} //end of namespace Cloud
