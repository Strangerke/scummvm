/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "castlx/castlx.h"
#include "castlx/detection.h"
#include "castlx/console.h"
#include "common/scummsys.h"
#include "common/config-manager.h"
#include "common/debug-channels.h"
#include "common/events.h"
#include "common/file.h"
#include "common/system.h"
#include "engines/util.h"
#include "graphics/palette.h"

namespace Castlx {

CastlxEngine *g_engine;

CastlxEngine::CastlxEngine(OSystem *syst, const ADGameDescription *gameDesc) : Engine(syst),
	_gameDescription(gameDesc), _randomSource("Castlx") {
	g_engine = this;

	// Add the game folder to the search manager path variable
	const Common::FSNode gameDataDir(ConfMan.get("path"));
	SearchMan.addSubDirectoryMatching(gameDataDir, "SONG1");
	SearchMan.addSubDirectoryMatching(gameDataDir, "GESTION1");
	SearchMan.addSubDirectoryMatching(gameDataDir, "SPRIT1/PC");

	_gstPtr = nullptr;
	_song0 = _song1 = nullptr;
	_lastFileSize = 0;
	_mouseCursorVisible = false;
}

CastlxEngine::~CastlxEngine() {
	delete _screen;
	delete[] _gstPtr;
	delete[] _song0;
	delete[] _song1;
}

uint32 CastlxEngine::getFeatures() const {
	return _gameDescription->flags;
}

Common::String CastlxEngine::getGameId() const {
	return _gameDescription->gameId;
}

void CastlxEngine::loadGst(int fileNumber) {
	Common::String filename = Common::String::format("%02d.GST", fileNumber);
	_gstPtr = loadFile(filename);
/*
	word1E7DB = _gstPtr + _decompFileSize;
	word2A302 = 0;
	word2A304 = _decompFileSize * 16;
	word2A306 = 0;

	word1E7D9 = word1E0C0 = word1E0C2 = word1E0C4 = word1E0C6 = word1E0C8 = word1E7DB;
*/
	setDisplayStringQueueIdTo0();
	_mouseCursorVisible = false;
}

byte *CastlxEngine::resize(byte *buffer, int oldSize, int newSize) {
	byte *newArr = new byte[newSize];

	memset(newArr, 9, newSize);
	memcpy(newArr, buffer, oldSize);

	delete[] buffer;
	buffer = newArr;
	return buffer;
}

byte *CastlxEngine::loadFile(Common::String &filename) {
	Common::File f;
	f.open(filename);

	if (!f.isOpen()) {
		_lastFileSize = 0;
		return nullptr;
	}

	uint32 sign = f.readUint32BE();
	uint32 tag = MKTAG('C', 'P', 'X', ' ');

	if (sign != tag) {
		_lastFileSize = f.size();
		f.seek(0);
		byte *srcBuffer = new byte[_lastFileSize];
		f.read(srcBuffer, _lastFileSize);
		f.close();
		
		return srcBuffer;
	}

	int targetSize = 0;
	uint8 curByte = f.readByte();
	while (curByte != 0) {
		if (curByte >= 0x30 && curByte <= 0x39)
			targetSize = targetSize * 10 + (curByte - 0x30);
		curByte = f.readByte();
	}

	int bufferSize = ((targetSize / 32768) + 1) * 32768;
	byte *destBuffer = new byte[bufferSize];
	memset(destBuffer, 0, targetSize);
	byte *destPtr = destBuffer;

	for(;;) {
		if (f.pos() >= f.size())
			break;
		int16 val = f.readSint16LE();
		int16 blockSize = 0xFF00 - val;

		byte fct0 = f.readByte();
		byte fct1 = f.readByte();
		byte fct2 = f.readByte();
		byte maskSize = f.readByte();
		byte maskl = 0;
		byte maskh = 0;
		for (int i = 0; i < maskSize; ++i) {
			maskl = (maskl << 1) | 1;
			maskh = (maskh >> 1) | 0x80;
		}

		uint16 bp = 1;
		uint8 carry = 0;
		uint8 oldCarry = 0;
		for (;;) {
			carry = bp & 1;
			bp >>= 1;
			if (!bp) {
				bp = f.readUint16LE();
				oldCarry = carry;
				carry = bp & 1;
				bp >>= 1;
				bp |= (oldCarry << 15);
			}

			if (!carry) {
				switch (fct0) {
				case 0:
					goto compFct0;
				case 1:
					goto compFct1;
				case 2:
					goto compFct2;
				default:
					error("bad fct %d", fct0);
				}
			}

			carry = bp & 1;
			bp >>= 1;
			if (!bp) {
				bp = f.readUint16LE();
				oldCarry = carry;
				carry = bp & 1;
				bp >>= 1;
				bp |= (oldCarry << 15);
			}
			if (!carry) {
				switch (fct1) {
				case 0:
					goto compFct0;
				case 1:
					goto compFct1;
				case 2:
					goto compFct2;
				default:
					error("bad fct %d", fct1);
				}
			}

			switch (fct2) {
			case 0:
				goto compFct0;
			case 1:
				goto compFct1;
			case 2:
				goto compFct2;
			default:
				error("bad fct %d", fct2);
			}

	compFct0:
			*destPtr++ = f.readByte();
			continue;
	compFct1 : {
			int16 cx = 0;
			carry = bp & 1;
			bp >>= 1;
			if (!bp) {
				bp = f.readUint16LE();
				oldCarry = carry;
				carry = bp & 1;
				bp >>= 1;
				bp |= (oldCarry << 15);
				cx = (cx << 1) + carry;
				carry = bp & 1;
				bp >>= 1;
			} else {
				cx = (cx << 1) + carry;
				carry = bp & 1;
				bp >>= 1;
				if (!bp) {
					bp = f.readUint16LE();
					oldCarry = carry;
					carry = bp & 1;
					bp >>= 1;
					bp |= (oldCarry << 15);
				}
			}
			cx = (cx << 1) + carry;
			int16 pos = f.readByte();
			pos |= 0xFF00;
			cx += 2;

			for (; cx > 0; --cx) {
				*destPtr = destPtr[pos];
				++destPtr;
			}
			continue;
			}
	compFct2 : {
			int ax = f.readUint16LE();
			int8 ch = ax & 0xFF;
			ax >>= maskSize;
			ax |= (maskh << 8);
			ch &= maskl;
			int cx = ch;
			if (!cx) {
				cx = f.readByte();
				
				if (!cx) {
					_lastFileSize = targetSize;
					break;
				}
			}
			cx += 2;
			int16 pos = ax;
			for (; cx > 0; --cx) {
				*destPtr = destPtr[pos];
				++destPtr;
			}
			continue;
			}
		}
	}
	// Dump the decompressed file
	Common::DumpFile dump;
	dump.open(filename + ".dump");
	dump.write(destBuffer, targetSize);
	dump.flush();
	dump.close();
	return destBuffer;
}

void CastlxEngine::setDisplayStringQueueIdTo0() {
	for (int i = 0; i < 5; ++i)
		_displayStringList[i]._id = 0;
}

Common::Error CastlxEngine::run() {
	// Initialize 320x200 paletted graphics mode
	initGraphics(320, 200);
	_screen = new Graphics::Screen();

	// Set the engine's debugger console
	setDebugger(new Console());

	// If a savegame was selected from the launcher, load it
	int saveSlot = ConfMan.getInt("save_slot");
	if (saveSlot != -1)
		(void)loadGameState(saveSlot);

	/*
	initMouse(629, 399, 0, 0);
	setMousePosition(320, 100);
	sub1AC52();
	sub1AC99();
	sub1E033();
	*/
	
	Common::String filename = "SONG0.OUT";
	_song0 = loadFile(filename);
	for (int i = 1; i < 14; ++i) {
		filename = Common::String::format("I%02d.IMG", i);
		byte *test = loadFile(filename);
		delete[] test;
		filename = Common::String::format("S%02d.SPR", i);
		test = loadFile(filename);
		delete[] test;
	}
	for (int i = 80; i < 84; ++i) {
		filename = Common::String::format("I%02d.IMG", i);
		byte *test = loadFile(filename);
		delete[] test;
	}
	for (int i = 87; i < 91; ++i) {
		if (i == 88)
			continue;
		filename = Common::String::format("I%02d.IMG", i);
		byte *test = loadFile(filename);
		delete[] test;
		filename = Common::String::format("S%02d.SPR", i);
		test = loadFile(filename);
		delete[] test;
	}
	filename = "SONG1.OUT";
	_song1 = loadFile(filename);
	loadGst(0);	

	/*
	handleGst(_word2A302);
	*/
	
	// Draw a series of boxes on screen as a sample
	for (int i = 0; i < 100; ++i)
		_screen->frameRect(Common::Rect(i, i, 320 - i, 200 - i), i);
	_screen->update();

	// Simple event handling loop
	byte pal[256 * 3] = { 0 };
	Common::Event e;
	int offset = 0;

	while (!shouldQuit()) {
		while (g_system->getEventManager()->pollEvent(e)) {
		}

		// Cycle through a simple palette
		++offset;
		for (int i = 0; i < 256; ++i)
			pal[i * 3 + 1] = (i + offset) % 256;
		g_system->getPaletteManager()->setPalette(pal, 0, 256);
		_screen->update();

		// Delay for a bit. All events loops should have a delay
		// to prevent the system being unduly loaded
		g_system->delayMillis(10);
	}

	return Common::kNoError;
}

Common::Error CastlxEngine::syncGame(Common::Serializer &s) {
	// The Serializer has methods isLoading() and isSaving()
	// if you need to specific steps; for example setting
	// an array size after reading it's length, whereas
	// for saving it would write the existing array's length
	int dummy = 0;
	s.syncAsUint32LE(dummy);

	return Common::kNoError;
}

} // End of namespace Castlx
