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
}

CastlxEngine::~CastlxEngine() {
	delete _screen;
}

uint32 CastlxEngine::getFeatures() const {
	return _gameDescription->flags;
}

Common::String CastlxEngine::getGameId() const {
	return _gameDescription->gameId;
}

void CastlxEngine::loadGst(int fileNumber) {
	Common::String filename = Common::String::format("%02d.GST", fileNumber);
	Common::File f;
	f.open(filename);
	// if failed, your return
	byte *srcBuffer = new byte[f.size()];
	f.read(srcBuffer, f.size());
	f.close();
	
	uint32 sign = READ_BE_UINT32(srcBuffer);
	srcBuffer += 4;
	uint32 tag = MKTAG('C', 'P', 'X', ' ');

	if (sign != tag)
		error("Unexpected signature"); // shouldn't error out, should read file

	int targetSize = 0;
	uint8 curByte = *srcBuffer++;
	while (curByte != 0) {
		if (curByte >= 0x30 && curByte <= 0x39)
			targetSize = targetSize * 10 + (curByte - 0x30);
		curByte = *srcBuffer++;
	}

	int bufferSize = ((targetSize / 32768) + 1) * 32768;
	byte *destBuffer = new byte[bufferSize];
	byte *destPtr = destBuffer;
	
	// skip 2 unknown bytes
	for (int i = 0; i < 2; ++i)
		curByte = *srcBuffer++;

	byte fct0 = *srcBuffer++;
	byte fct1 = *srcBuffer++;
	byte fct2 = *srcBuffer++;
	byte maskSize = *srcBuffer++;
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
			bp = READ_LE_UINT16(srcBuffer);
			srcBuffer += 2;
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
			bp = READ_LE_UINT16(srcBuffer);
			srcBuffer += 2;
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
		*destPtr++ = *srcBuffer++;
		continue;
compFct1 : {
		int16 cx = 0;
		carry = bp & 1;
		bp >>= 1;
		if (!bp) {
			bp = READ_LE_UINT16(srcBuffer);
			srcBuffer += 2;
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
				bp = READ_LE_UINT16(srcBuffer);
				srcBuffer += 2;
				oldCarry = carry;
				carry = bp & 1;
				bp >>= 1;
				bp |= (oldCarry << 15);
			}
		}
		cx = (cx << 1) + carry;
		int16 pos = *srcBuffer++;
		pos |= 0xFF00;
		cx += 2;

		for (; cx > 0; --cx) {
			*destPtr = destPtr[pos];
			++destPtr;
		}
		continue;
		}
compFct2 : {
		int ax = READ_LE_UINT16(srcBuffer);
		srcBuffer += 2;
		int8 ch = ax & 0xFF;
		ax >>= maskSize;
		ax |= (maskh << 8);
		ch &= maskl;
		int cx = ch;
		if (!cx) {
			cx = *srcBuffer++;
			
			if (!cx) {
				// Dump the decompressed file
				Common::DumpFile dump;
				dump.open(filename + ".dump");
				dump.write(destBuffer, targetSize);
				dump.flush();
				dump.close();
				return;
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

	loadGst(0);	
	
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
