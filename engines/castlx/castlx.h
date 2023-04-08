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

#ifndef CASTLX_H
#define CASTLX_H

#include "common/scummsys.h"
#include "common/system.h"
#include "common/error.h"
#include "common/fs.h"
#include "common/hash-str.h"
#include "common/random.h"
#include "common/serializer.h"
#include "common/util.h"
#include "engines/engine.h"
#include "engines/savestate.h"
#include "graphics/screen.h"

#include "castlx/detection.h"

namespace Castlx {

struct CastlxGameDescription;

struct DisplayStringQueue {
	int16 _id;
	int16 _posX;
	int16 _posY;
	void *_unkPtr;
	void *_headerPtr;

	DisplayStringQueue() {
		_id = _posX = _posY = 0;
		_unkPtr = _headerPtr = nullptr;
	}
};

class CastlxEngine;
typedef void (CastlxEngine::*OpcodePtr)(byte **buffer);
typedef void (CastlxEngine::*HardcodedLogic)();

struct OpcodeDic {
	Common::String _keyword;
	OpcodePtr _opcodePtr;
};

struct Label {
	Common::String _keyword;
	byte *_gstLabelPtr;
};

struct DefinedVar {
	Common::String _name;
	int _value;
};

class CastlxEngine : public Engine {
private:
	const ADGameDescription *_gameDescription;
	Common::RandomSource _rnd;

	byte *_gstPtr;
	byte *_curGstPtr;
	byte *_song0;
	byte *_song1;
	int _lastFileSize;
	DisplayStringQueue _displayStringList[5];
	int _mouseCursorVisible;
	byte *_word2A302;
	byte *_backgroundImgPtr;
	byte *_gstEndPtr;
	byte _engineFlags[128];
	OpcodeDic _opcodes[63];
	HardcodedLogic _hardcodedLogic[14];
	Label _label;
	int16 _mousePosX, _mousePosY;
	int16 _mouseMinX, _mouseMaxX;
	int16 _mouseMinY, _mouseMaxY;
	DefinedVar _defineArray[16];
	int _word1E7E5;
	int _word1E7E7;
	Common::String _filename;
	byte *_spritePtr[5];
	byte *_postGstSegment;
	byte _unkPalette[768];
	byte _unkCol1[3];
	int _flagEnableHotspots;
	int _mouseButtonStatus;
	int _word113C8, _word113CA;
	int _word113CC, _word113CE;
	byte *_word1E0B0_screenPtr1;
	byte *_word1E0B2_screenPtr2;
	byte *_word1E0B6;
	byte _byte1E7EA;
	int _int8Counter3;
	byte _byte2C0BC;
	byte _activeSoundFl;
	int16 _word2C0A8;
	int16 _word2C0AA[8];
	byte _byte2C0BE;
	byte _byte2C0F3;
	int16 _unkSpriteNumber;
	

	int skipNoiseInString(byte **bufferPtr);
	void skipEndOfLine(byte **buffer);
	int parseString(byte **buffer);
	Common::String copyBuffer(byte **srcBuffer);
	void sub1AFFE();
	void loadImgFile(Common::String &filename);
	void sub19B51();
	void setUnkPalette2(byte *palPtr);
	void sub1C2B0();
	void sub19306(void *ptr, int16 posX, int16 poxY);
	void sub12C73();
	void sub1228A();
	void sub12279();
	void handleSoundOff();
	void displayMessageUselessAction();
	void sub1114D(byte *screen, byte *buffer);
	void sub11475(byte *screen2, byte *screen1);
	void sub10FC9();
	void sub1B1A4(int param1, int param2, int param3, byte *str);
	int getRandom(int max);
	void waitForMouseClick();
	void initMouse(int16 minX, int16 minY, int16 width, int16 height);
	void setMousePosition(int16 cx, int16 dx);

	void opLOADIMG(byte **buffer);
	void opEXIT(byte **buffer);
	void opTEMPO(byte **buffer);
	void opOTEPALETTE(byte **buffer);
	void opMETPALETTE(byte **buffer);
	void opDEF(byte **buffer);
	void opNAME(byte **buffer);
	void opIF(byte **buffer);
	void opLabel(byte **buffer);
	void opJUMP(byte **buffer);
	void opCALL(byte **buffer);
	void opRETURN(byte **buffer);
	void opUNCALL(byte **buffer);
	void opKEY(byte **buffer);
	void opRESO(byte **buffer);
	void opTIMER(byte **buffer);
	void opWAIT(byte **buffer);
	void opTIMEPLAY(byte **buffer);
	void opPLAYFLI(byte **buffer);
	void opPLAYFLX(byte **buffer);
	void opCLIPPLAY(byte **buffer);
	void opAFFMOUSEV(byte **buffer);
	void opAFFMOUSEF(byte **buffer);
	void opVBL(byte **buffer);
	void opDummy(byte **buffer);
	void opOPENFLI(byte **buffer);
	void opOPENFLX(byte **buffer);
	void opENDPLAY(byte **buffer);
	void opSETMOUSE(byte **buffer);
	void opCLIPMOUSE(byte **buffer);
	void opLOAD(byte **buffer);
	void opLOADSPR(byte **buffer);
	void opPAUSE(byte **buffer);
	void opRAZSPR(byte **buffer);
	void opPALNOIR(byte **buffer);
	void opLOADPALETTE(byte **buffer);
	void opSETPLAY(byte **buffer);
	void opCLOSEPLAY(byte **buffer);
	void opPALETTE(byte **buffer);
	void opSETCOLORPLAY(byte **buffer);
	void opSWITCH(byte **buffer);
	void opMODEPLAY(byte **buffer);
	void opINCRUSTIMGV(byte **buffer);
	void opINCRUSTIMGF(byte **buffer);
	void opCOPYVF(byte **buffer);
	void opCOPYFV(byte **buffer);
	void opCOPYVB(byte **buffer);
	void opCOPYFB(byte **buffer);
	void opCOPYBV(byte **buffer);
	void opCOPYBF(byte **buffer);
	void opAFFSPRITEV(byte **buffer);
	void opAFFSPRITEF(byte **buffer);
	void opMODESPRITE(byte **buffer);
	void opCLEARV(byte **buffer);
	void opCLEARF(byte **buffer);
	void opOTEPAL(byte **buffer);
	void opMETPAL(byte **buffer);
	void opREADMOUSE(byte **buffer);
	void opGAME(byte **buffer);
	void opTRANSV(byte **buffer);
	void opTRANSF(byte **buffer);
	void opTRANSPARENCE(byte **buffer);

	void handleExitRoom();
	void sub1E033(int i, int i1, int i2, int i3);
	void sub126AE();

	void initRoom00();
	void initRoom01();
	void initRoom02();
	void initRoom03();
	void initRoom04();
	void initRoom05();
	void initRoom06();
	void initRoom07();
	void initRoom08();
	void initRoom09();
	void initRoom10();
	void initRoom11();
	void initRoom12();
	void initRoom13();

	void hlInit();
	void hlGate();
	void hlHall();
	void hlKitchen();
	void hlCellar();
	void hlDiningRoom();
	void hlLivingRoom();
	void hlDungeon();
	void hlLibrary();
	void hlMaevaRoom();
	void hlBathroom();
	void hlBedroom1();
	void hlBedroom2();
	void hlAttic();
	
	byte *loadFile(Common::String &filename);
	void setDisplayStringQueueIdTo0();
	void initOpcodes();
	void initHardcodedLogic();
	void loadGst(int fileNumber);
	void sub19A16();
	void sub1024E();
	void handleGst(byte **buffer);

protected:
	// Engine APIs
	Common::Error run() override;

public:
	Graphics::Screen *_screen = nullptr;

	CastlxEngine(OSystem *syst, const ADGameDescription *gameDesc);
	~CastlxEngine() override;

	uint32 getFeatures() const;

	/**
	 * Returns the game Id
	 */
	Common::String getGameId() const;

	/**
	 * Gets a random number
	 */
	uint32 getRandomNumber(uint maxNum) {
		return _rnd.getRandomNumber(maxNum);
	}

	bool hasFeature(EngineFeature f) const override {
		return
		    (f == kSupportsLoadingDuringRuntime) ||
		    (f == kSupportsSavingDuringRuntime) ||
		    (f == kSupportsReturnToLauncher);
	};

	bool canLoadGameStateCurrently() override {
		return true;
	}
	bool canSaveGameStateCurrently() override {
		return true;
	}

	/**
	 * Uses a serializer to allow implementing savegame
	 * loading and saving using a single method
	 */
	Common::Error syncGame(Common::Serializer &s);

	Common::Error saveGameStream(Common::WriteStream *stream, bool isAutosave = false) override {
		Common::Serializer s(nullptr, stream);
		return syncGame(s);
	}
	Common::Error loadGameStream(Common::SeekableReadStream *stream) override {
		Common::Serializer s(stream, nullptr);
		return syncGame(s);
	}
};

extern CastlxEngine *g_engine;
#define SHOULD_QUIT ::Castlx::g_engine->shouldQuit()

} // End of namespace Castlx

#endif // CASTLX_H
