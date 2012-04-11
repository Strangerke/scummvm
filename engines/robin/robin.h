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

#ifndef ROBIN_H
#define ROBIN_H

#include "robin/console.h"
#include "robin/script.h"

#include "common/file.h"
#include "engines/engine.h"
#include "graphics/palette.h"
#include "graphics/surface.h"

namespace Common {
class RandomSource;
}

/**
 * This is the namespace of the Robin engine.
 *
 * Status of this engine: ???
 *
 * Games using this engine:
 * - Adventures of Robin Hood
 * - Rome: Pathway to Rome
 */
namespace Robin {

static const int kSavegameVersion = 1;

enum GameType {
	kGameTypeNone  = 0,
	kGameTypeRobin,
	kGameTypeRome
};

enum RobinDebugChannels {
	kDebugEngine    = 1 <<  0,
	kDebugScript    = 1 <<  1
};

struct RobinGameDescription;

struct struct18560 {
	byte _field0;
	int16 _field1;
	int16 _field3;
	int16 _field5[8];
};

class RobinEngine : public Engine {
public:
	RobinEngine(OSystem *syst, const RobinGameDescription *gd);
	~RobinEngine();

	OSystem *_system;

	GUI::Debugger *getDebugger();

	Common::RandomSource *_rnd;
	RobinScript *_scriptHandler;
	Graphics::Surface *_mainSurface;

	struct18560 _arr18560[4];
	byte _byte1714E;
	byte _byte184F4;
	byte _sound_byte16F06;
	byte _byte16F09;
	byte _keyboard_nextIndex;
	byte _keyboard_oldIndex;

	byte _buffer1[45056];
	byte _buffer2[45056];
	byte _buffer3[45056];
	byte *_bufferIsoMap;
	byte _bufferCubegfx[61440];
	byte *_bufferMen;
	byte *_bufferMen2;
	byte *_bufferIsoChars;
	byte *_bufferIdeogram;
	byte _buffer10[4032];
	byte _curPalette[768];

	bool _saveFlag;
	
	int _word10800_ERULES;
	int _word10807_ERULES;
	int _word16EFA;
	int _word17081_nextIndex;
	int _word16EFE;
	int _word1817B;

	int _array11D49[40];

	byte *_rulesChunk1;
	int _rulesBuffer2PrevIndx;
	int _rulesBuffer2_1[40];
	int _rulesBuffer2_2[40];
	byte _rulesBuffer2_3[40];
	int _rulesBuffer2_4[40];
	byte _rulesBuffer2_5[40];
	byte _rulesBuffer2_6[40];
	byte _rulesBuffer2_7[40];
	byte _rulesBuffer2_8[40];
	byte _rulesBuffer2_9[40];
	byte _rulesBuffer2_10[40];
	byte _rulesBuffer2_11[40];
	byte _rulesBuffer2_12[40];
	byte _rulesBuffer2_13[40];
	byte _rulesBuffer2_14[40];
	byte _rulesBuffer2_15[40 * 32];
	byte *_ptr_rulesBuffer2_15;
	byte _rulesBuffer2_16[40 * 32];
	int *_rulesChunk3;
	int _rulesChunk3_size;
	byte *_rulesChunk4;
	byte *_initScript;
	int _initScript_size;
	byte *_menuScript;
	int _menuScript_size;
	int *_arrayGameScriptIndex;
	int _gameScriptIndexSize;
	byte *_arrayGameScripts;
	byte _rulesChunk9[60];
	int _rulesChunk10_size;
	int *_rulesChunk10;
	byte *_rulesChunk11;
	int _rulesChunk12_size;
	int _rulesBuffer12_1[40];
	int _rulesBuffer12_2[40];
	int _rulesBuffer12_3[40];
	int _rulesBuffer12_4[40];
	int _word12F68_ERULES;
	byte _rulesBuffer13_1[20];
	int _rulesBuffer13_2[20];
	int _rulesBuffer13_3[20];
	byte _rulesBuffer13_4[20];
	byte _byte10999[40];
	byte _byte109C1[40];

	const RobinGameDescription *_gameDescription;
	uint32 getFeatures() const;
	const char *getGameId() const;

	void initGame(const RobinGameDescription *gd);
	byte *loadVGA(Common::String filename, bool loadPal);
	byte *loadRaw(Common::String filename);
	void loadRules();

	void displayVGAFile(Common::String fileName);
	void initPalette();
	void fixPaletteEntries(uint8 *palette, int num);

	GameType getGameType() const;
	Common::Platform getPlatform() const;

	bool hasFeature(EngineFeature f) const;
	const char *getCopyrightString() const;

	Common::String getSavegameFilename(int slot);
	void syncSoundSettings();

	int _mouseX;
	int _mouseY;
	int _mouseButton;
	int _savedMousePosDivided;

	byte _byte16F07_menuId;
	byte _byte12FCE;
	byte _byte129A0;
	int _word10804;

	void pollEvent();
	void sub170EE(int index);
	void sub130DD();
	void handleGameScripts();

	// Temporary stubs
	byte _keyboard_getch();

protected:
	Common::EventManager *_eventMan;
	bool _shouldQuit;

	// Engine APIs
	Common::Error run();
	void handleMenu();

private:
	static RobinEngine *s_Engine;

	RobinConsole *_console;
	GameType _gameType;
	Common::Platform _platform;

	void initialize();
};

} // End of namespace Robin

#endif // Robin_H
