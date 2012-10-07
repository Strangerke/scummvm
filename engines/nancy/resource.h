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

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef NANCY_RESOURCE_H
#define NANCY_RESOURCE_H

namespace Common {
class MemoryReadStream;
class String;
}

namespace Graphics {
class Surface;
}

namespace Nancy {

class NancyEngine;

class ResourceManager {
public:
	ResourceManager(NancyEngine *vm);
	~ResourceManager();

	void initialize();
	byte *loadResource(const Common::String name, uint &size);
	bool loadImage(const Common::String name, Graphics::Surface &surf);

	// Debugger functions
	void listResources(Common::Array<Common::String> &list);
	Common::String getResourceDesc(const Common::String name);
private:
	struct ResInfo {
		Common::String name;
		uint16 width, pitch, height;
		byte flag;
		uint32 compressedSize, size;
		uint32 dataOffset;
		uint16 next;
	};

	enum {
		kHashMapSize = 1024
	};

	NancyEngine *_vm;
	uint16 _hashMap[kHashMapSize];
	Common::Array<ResInfo> _resInfo;

	const ResInfo *findResource(const Common::String name);
	byte *decompress(const ResInfo &res, uint &size);
};

} // End of namespace Nancy

#endif
