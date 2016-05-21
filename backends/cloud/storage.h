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

#ifndef BACKENDS_CLOUD_STORAGE_H
#define BACKENDS_CLOUD_STORAGE_H

#include "common/array.h"
#include "common/stream.h"
#include "common/str.h"
#include "common/callback.h"
#include "backends/cloud/storagefile.h"
#include "backends/cloud/storageinfo.h"

namespace Cloud {

class Storage {
public:
	typedef Common::BaseCallback< Common::Array<StorageFile> > *FileArrayCallback;
	typedef Common::BaseCallback<Common::ReadStream *> *ReadStreamCallback;
	typedef Common::BaseCallback<StorageInfo> *StorageInfoCallback;
	typedef Common::BaseCallback<bool> *BoolCallback;

	Storage() {}
	virtual ~Storage() {}

	/** Returns Common::Array<StorageFile>. */
	virtual void listDirectory(Common::String path, FileArrayCallback callback) = 0;

	/** Calls the callback when finished. */
	virtual void upload(Common::String path, Common::ReadStream* contents, BoolCallback callback) = 0;

	/** Returns pointer to Common::ReadStream. */
	virtual void download(Common::String path, ReadStreamCallback callback) = 0;

	/** Calls the callback when finished. */
	virtual void remove(Common::String path, BoolCallback callback) = 0;

	/** Calls the callback when finished. */
	virtual void syncSaves(BoolCallback callback) = 0;

	/** Calls the callback when finished. */
	virtual void createDirectory(Common::String path, BoolCallback callback) = 0;

	/** Calls the callback when finished. */
	virtual void touch(Common::String path, BoolCallback callback) = 0;

	/** Returns the StorageInfo struct. */
	virtual void info(StorageInfoCallback callback) = 0;

	/** Returns whether saves sync process is running. */
	virtual bool isSyncing() = 0;

	/** Returns whether there are any requests running. */
	virtual bool isWorking() = 0;
};

} //end of namespace Cloud

#endif
