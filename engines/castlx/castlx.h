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

struct OpcodeDic {
	Common::String _keyword;
	OpcodePtr _opcodePtr;
};

struct Label {
	Common::String _keyword;
	byte *_gstLabelPtr;
};

class CastlxEngine : public Engine {
private:
	const ADGameDescription *_gameDescription;
	Common::RandomSource _randomSource;

	byte *_gstPtr;
	byte *_song0;
	byte *_song1;
	int _lastFileSize;
	DisplayStringQueue _displayStringList[5];
	bool _mouseCursorVisible;
	byte *_word2A302;
	byte *_gstEndPtr;
	byte _engineFlags[128];
	OpcodeDic _opcodes[63];
	Label _label;
	int _mousePosX, _mousePosY;
	Common::String  _defineArray[16];
	int _word1E7E5;
	int _word1E7E7;

	int skipNoiseInString(byte **bufferPtr);
	int parseString(byte **buffer);
	Common::String copyBuffer(byte **srcBuffer);
	void sub1AFFE();

	
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


	byte *loadFile(Common::String &filename);
	void setDisplayStringQueueIdTo0();
	void initOpcodes();
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
		return _randomSource.getRandomNumber(maxNum);
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
