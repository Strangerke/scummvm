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
	_curGstPtr = nullptr;
	_song0 = _song1 = nullptr;
	_lastFileSize = 0;
	_mouseCursorVisible = 0;
	_word2A302 = nullptr;
	_backgroundImgPtr = nullptr;
	_gstEndPtr = nullptr;

	for (int i = 0; i < 128; ++i)
		_engineFlags[i] = 0;

	for (int i = 0; i < 63; ++i) {
		_opcodes[i]._keyword = "";
		_opcodes[i]._opcodePtr = nullptr;
	}

	_label._keyword = "";
	_label._gstLabelPtr = nullptr;
	_mousePosX = _mousePosY = 0;

	for (int i = 0; i < 16; ++i) {
		_defineArray[i]._name = "";
		_defineArray[i]._value = 0;
	}

	_word1E7E5 = _word1E7E7 = 0;
	_filename = "";

	_postGstSegment = nullptr;
	for (int i = 0; i < 5; ++i)
		_spritePtr[i] = _postGstSegment;

	for (int i = 0; i < 768; ++i)
		_unkPalette[i] = 0;

	for (int i = 0; i < 3; ++i)
		_unkCol1[i] = 0;

	_flagEnableHotspots = 0;
	_mouseButtonStatus = 0;

	for (int i = 0; i < 14; ++i) {
		_hardcodedLogic[i] = nullptr;
	}
	_word113C8 = _word113CA = 0;
	_word113CC = _word113CE = 0;
	_word1E0B0_screenPtr1 = _word1E0B2_screenPtr2 = nullptr;
	_word1E0B6 = nullptr;
	_byte1E7EA = 0;
	_int8Counter3 = 0;
}

CastlxEngine::~CastlxEngine() {
	delete _screen;
	delete[] _gstPtr;
	delete[] _song0;
	delete[] _song1;
	delete[] _backgroundImgPtr;
}

uint32 CastlxEngine::getFeatures() const {
	return _gameDescription->flags;
}

Common::String CastlxEngine::getGameId() const {
	return _gameDescription->gameId;
}

int CastlxEngine::skipNoiseInString(byte **bufferPtr) {
	byte *oldPtr = *bufferPtr;
	byte *curPtr = *bufferPtr;

	byte curByte = *curPtr;
	while (curByte != 0 && curByte != 0xA && curByte != 0xD) {
		if (curByte == '=' || curByte == '.' || curByte == '"' || curByte == '\'' || curByte <= 0x20) {
			curByte = *++curPtr;
			continue;
		}
		*bufferPtr = curPtr;
		return 1;
	}
	*bufferPtr = oldPtr;
	return 0;
}

void CastlxEngine::skipEndOfLine(byte **bufferPtr) {
	byte *curPtr = *bufferPtr;

	byte curByte = *curPtr;
	while (curByte != 0 && curByte != 0xA && curByte != 0xD)
			curByte = *++curPtr;

	*bufferPtr = curPtr;
}

int CastlxEngine::parseString(byte **bufferPtr) {
	byte *curPtr = *bufferPtr;
	byte curByte = *curPtr;

	if (curByte == '\'' || curByte == '"') {
		int retVal = *++curPtr;
		curPtr += 2;
		*bufferPtr = curPtr;
		return retVal;
	}

	if (curByte == 'h' || curByte == 'H') {
		int retVal = 0;
		for (int i = 0; i < 4; ++i) {
			retVal <<= 4;
			curByte = *++curPtr;
			if (curByte >= 'a' && curByte <= 'z')
				curByte &= 0xDF;

			if (curByte >= 0x41)
				curByte -= 0x37;
			else
				curByte -= 0x30;

			retVal += curByte;
		}
		*bufferPtr = curPtr;
		return retVal;
	}

	if (curByte == '_') {
		++curPtr;
		*bufferPtr = curPtr;
		Common::String defName = copyBuffer(bufferPtr);
		for (int i = 0; i < 16; ++i) {
			if (_defineArray[i]._name.equalsIgnoreCase(defName))
				return i;
		}
		error("parseString - parsing error, defName %s not found", defName.c_str());
	}

	if (curByte == 'x' || curByte == 'X') {
		++curPtr;
		*bufferPtr = curPtr;
		return _mousePosX;
	}

	if (curByte == 'y' || curByte == 'Y') {
		++curPtr;
		*bufferPtr = curPtr;
		return _mousePosY;
	}

	int retval = 0;
	for (int i = 0; i < 5; ++i) {
		if (curByte < 0x30 || curByte > 0x39)
			break;

		retval *= 10;
		retval += (curByte - 0x30);
		curByte = *++curPtr;
	}
	*bufferPtr = curPtr;
	return retval;
}

Common::String CastlxEngine::copyBuffer(byte **srcBufferPtr) {
	Common::String destStr = "";
	byte* curPtr = *srcBufferPtr;
	byte curByte = *curPtr;
	// Note: In comparison to the original, added a check on '=' in order to reuse this function in various places.
	// This shouldn't be an issue, but this is a reminder in case a problem appears with a missing substring containing '='
	while (curByte != 0xA && curByte != 0xD && curByte != '#' && curByte != ' ' && curByte != '\'' && curByte != '"' && curByte !=0x9 && curByte != '=') {
		destStr += curByte;
		curByte = *++curPtr;
	}

	*srcBufferPtr = curPtr;
	return destStr;
}

void CastlxEngine::sub1AFFE() {
	warning("STUB sub1AFFE (palette)");
}

void CastlxEngine::loadImgFile(Common::String &filename) {
	_backgroundImgPtr = loadFile(filename);
}

void CastlxEngine::sub19B51() {
	warning("STUB - sub19B51 (display background?)");
}

void CastlxEngine::setUnkPalette2(byte *palPtr) {
	warning("STUB - setUnkPalette2");
}

void CastlxEngine::sub1C2B0() {
	warning("STUB - sub1C2B0 (transparency)");
}

void CastlxEngine::sub12C73() {
	warning("STUB - sub12C73");
}

void CastlxEngine::sub12279() {
	warning("STUB - sub12279");
}

void CastlxEngine::handleSoundOff() {
	warning("STUB - handleSoundOff");
}

void CastlxEngine::displayMessageUselessAction() {
	warning("STUB - displayMessageUselessAction");
}

void CastlxEngine::sub1114D(byte *screen, byte *buffer) {
	warning("STUB - sub1114D");
}

void CastlxEngine::sub11475(byte *screen2, byte *screen1) {
	warning("STUB - sub11475");
}

void CastlxEngine::sub10FC9() {
	warning("STUB - sub10FC9");
}

void CastlxEngine::sub1B1A4(int param1, int param2, int param3, byte *str) {
	warning("STUB sub1B1A4 (display sprite)");
}

void CastlxEngine::sub19817() {
	warning("STUB sub19817 (mouse)");
}

/**
 * @brief Opcode:Load Image
 * @param buffer 
*/
void CastlxEngine::opLOADIMG(byte **buffer) {
	if (!_mouseCursorVisible) {
		skipNoiseInString(buffer);
		_filename = copyBuffer(buffer);
	}
	loadImgFile(_filename);

	if (_mouseCursorVisible)
		warning("STUB opLOADIMG call direct");

	warning("opLOADIMG %s", _filename.c_str());
	sub19B51();
}

void CastlxEngine::opEXIT(byte **buffer) { warning("STUB - opEXIT"); }
void CastlxEngine::opTEMPO(byte **buffer) { warning("STUB - opTEMPO"); }
/**
 * @brief opCode : Remove palette from/to
 * @param buffer 
*/
void CastlxEngine::opOTEPALETTE(byte **buffer) {
	if (!_mouseCursorVisible) {
		skipNoiseInString(buffer);
		_word1E7E5 = parseString(buffer);
		skipNoiseInString(buffer);
		_word1E7E7 = parseString(buffer);
		sub1AFFE();
		warning("opOTEPALETTE %d %d", _word1E7E5, _word1E7E7);
	} else {
		warning("opOTEPALETTE - STUB");
	}
}

/**
 * @brief Opcode: Set palette
 * @param buffer
*/
void CastlxEngine::opMETPALETTE(byte **buffer) {
	if (_mouseCursorVisible) {
		warning("opMETPALETTE- missing parameters");
	} else {
		skipNoiseInString(buffer);
		_word1E7E5 = parseString(buffer);
		skipNoiseInString(buffer);
		_word1E7E7 = parseString(buffer);
	}
	warning("opMETPALETTE %d %d", _word1E7E5, _word1E7E7);
	setUnkPalette2(&_unkPalette[_word1E7E5 * 3]);
}

/**
 * @brief Opcode: Define
 * @param bufferPtr 
*/
void CastlxEngine::opDEF(byte **bufferPtr) {
	skipNoiseInString(bufferPtr);
	int index = parseString(bufferPtr);
	skipNoiseInString(bufferPtr);
	_defineArray[index]._name = copyBuffer(bufferPtr);

	warning("opDEF - %d %s", index, _defineArray[index]._name.c_str());
}

/**
 * @brief  Opcode: set name
 * @param buffer 
*/
void CastlxEngine::opNAME(byte **buffer) {
	skipNoiseInString(buffer);
	int index = parseString(buffer);
	skipNoiseInString(buffer);
	int value = parseString(buffer);

	_defineArray[index]._value = value;

	warning("opNAME - keyword found at id %d,set value to %d", index, value);
}

void CastlxEngine::opIF(byte **buffer) { warning("opIF"); }
void CastlxEngine::opLabel(byte **buffer) { warning("opLabel"); }

/**
 * @brief Opcode: Jump to Label
 * @param buffer 
*/
void CastlxEngine::opJUMP(byte **buffer) {
	skipNoiseInString(buffer);
	Common::String targetLabel = copyBuffer(buffer);
	warning("opJUMP %s", targetLabel.c_str());
	if (targetLabel.equalsIgnoreCase(_label._keyword))
		*buffer = _label._gstLabelPtr;
	else
		warning("Label not found %s (found %s)", targetLabel.c_str(), _label._keyword.c_str());
}

void CastlxEngine::opCALL(byte **buffer) { warning("opCALL"); }
void CastlxEngine::opRETURN(byte **buffer) { warning("opRETURN"); }
void CastlxEngine::opUNCALL(byte **buffer) { warning("opUNCALL"); }
void CastlxEngine::opKEY(byte **buffer) { warning("opKEY"); }
void CastlxEngine::opRESO(byte **buffer) { warning("opRESO"); }
/**
 * @brief Opcode: set timer
 * @param buffer 
*/
void CastlxEngine::opTIMER(byte **buffer) {
	skipNoiseInString(buffer);
	int delay = parseString(buffer);
	_int8Counter3 = delay;
	warning("opTIMER %d", delay);
}

/**
 * @brief 
 * @param buffer 
*/
void CastlxEngine::opWAIT(byte **buffer) {
	skipNoiseInString(buffer);
	int target = parseString(buffer);

	if (_int8Counter3 <= target) {
		warning("opWAIT - Condition not met %d > %d", _int8Counter3, target);
		_int8Counter3 += 10;
		return;
	}

	skipEndOfLine(buffer);
}

void CastlxEngine::opTIMEPLAY(byte **buffer) { warning("opTIMEPLAY"); }
void CastlxEngine::opPLAYFLI(byte **buffer) { warning("opPLAYFLI"); }
void CastlxEngine::opPLAYFLX(byte **buffer) { warning("opPLAYFLX"); }
void CastlxEngine::opCLIPPLAY(byte **buffer) { warning("opCLIPPLAY"); }
void CastlxEngine::opAFFMOUSEV(byte **buffer) { warning("opAFFMOUSEV"); }
void CastlxEngine::opAFFMOUSEF(byte **buffer) { warning("opAFFMOUSEF"); }
/**
 * @brief Opcode: wait for retrace
 * @param buffer 
*/
void CastlxEngine::opVBL(byte **buffer) {
	warning("STUB - opVBL");
}

void CastlxEngine::opDummy(byte **buffer) { warning("opDummy"); }
void CastlxEngine::opOPENFLI(byte **buffer) { warning("opOPENFLI"); }
void CastlxEngine::opOPENFLX(byte **buffer) { warning("opOPENFLX"); }
void CastlxEngine::opENDPLAY(byte **buffer) { warning("opENDPLAY"); }
void CastlxEngine::opSETMOUSE(byte **buffer) { warning("opSETMOUSE"); }
void CastlxEngine::opCLIPMOUSE(byte **buffer) { warning("opCLIPMOUSE"); }

/**
 * @brief Opcode: Load GST file
 * @param buffer 
*/
void CastlxEngine::opLOAD(byte **buffer) {
	warning("opLOAD");
	skipNoiseInString(buffer);
	int index = parseString(buffer);
	loadGst(index);
	sub19817();
	_int8Counter3 = 0;
}

/**
 * @brief Opcode: Load sprite
 * @param buffer 
*/
void CastlxEngine::opLOADSPR(byte **buffer) {
	warning("opLOADSPR");
	int index = 1;
	if(!_mouseCursorVisible) {
		skipNoiseInString(buffer);
		_filename = copyBuffer(buffer);
		skipNoiseInString(buffer);
		index = parseString(buffer);
	} else {
		warning("opLOADSPR params not set");
	}

	--index;
	_spritePtr[index] = loadFile(_filename);
	for (int i = 2; i < 10; i += 2) {
		int16 unkVal = READ_LE_INT16(&_spritePtr[index][i]);
		warning("sprite %d - val %d", i, unkVal);
	}
	warning("opLOADSPR - Weird set of _backGroundImgPtr");
}

/**
 * @brief Opcode: Skippable delay (skipped by user input
 * @param buffer 
*/
void CastlxEngine::opPAUSE(byte **buffer) {
	int delay = 0;
	if (!_mouseCursorVisible) {
		skipNoiseInString(buffer);
		delay = parseString(buffer);
	} else {
		warning("opPAUSE: missing variable init");
	}

	warning("opPAUSE : TODO implement skippable delay - %d", delay);
}

/**
 * @brief Opcode: Reset sprite
 * @param buffer 
*/
void CastlxEngine::opRAZSPR(byte **buffer) {
	int index = 1;
	if (!_mouseCursorVisible) {
		skipNoiseInString(buffer);
		index = parseString(buffer);
	} else
		warning("opRAZSPR missing param");

	--index;
	byte *ptr;
	if (!index)
		ptr = _backgroundImgPtr;
	else
		ptr = _postGstSegment;

	_spritePtr[index] = ptr;
	_backgroundImgPtr = ptr;

	warning("opRAZSPR %d", index);
}

void CastlxEngine::opPALNOIR(byte **buffer) { warning("opPALNOIR"); }
/**
 * @brief Opcode: Load partial palette
 * @param buffer 
*/
void CastlxEngine::opLOADPALETTE(byte **buffer) {
	int param = 0;
	if (!_mouseCursorVisible) {
		skipNoiseInString(buffer);
		param = parseString(buffer);
		skipNoiseInString(buffer);
		_filename = copyBuffer(buffer);
	} else
		warning("opLOADPALETTE - params not set");

	byte *palette = loadFile(_filename);
	for (int i = param * 3, j = 0; i < 768;) {
		if (j > _lastFileSize)
			break;
		_unkPalette[i++] = palette[j++];
	}
	_word1E7E5 = 0;
	warning("opLOADPALETTE %d %s", param, _filename.c_str());
	delete[] palette;
}

void CastlxEngine::opSETPLAY(byte **buffer) { warning("opSETPLAY"); }
void CastlxEngine::opCLOSEPLAY(byte **buffer) { warning("opCLOSEPLAY"); }
void CastlxEngine::opPALETTE(byte **buffer) { warning("opPALETTE"); }

void CastlxEngine::opSETCOLORPLAY(byte **buffer) { warning("opSETCOLORPLAY"); }
/**
 * @brief Opcode: switch between back and front screen buffer
 * @param buffer (not used)
*/
void CastlxEngine::opSWITCH(byte **buffer) {
	warning("STUB opSWITCH");
}

void CastlxEngine::opMODEPLAY(byte **buffer) { warning("opMODEPLAY"); }
void CastlxEngine::opINCRUSTIMGV(byte **buffer) { warning("opINCRUSTIMGV"); }
void CastlxEngine::opINCRUSTIMGF(byte **buffer) { warning("opINCRUSTIMGF"); }
/**
 * @brief Opcode: TODO - no idea
 * @param buffer 
*/
void CastlxEngine::opCOPYVF(byte **buffer) {
	if (_mouseCursorVisible) {
		warning("opCOPYVF missing parameters");
	} else {
		skipNoiseInString(buffer);
		_word113C8 = parseString(buffer);
		skipNoiseInString(buffer);
		_word113CA = parseString(buffer);
		skipNoiseInString(buffer);
		_word113CC = parseString(buffer);
		skipNoiseInString(buffer);
		_word113CE = parseString(buffer);
	}
	warning("opCOPYVF %d %d %d %d", _word113C8, _word113CA, _word113CC, _word113CE);
	sub11475(_word1E0B2_screenPtr2, _word1E0B0_screenPtr1);
	sub10FC9();
}
void CastlxEngine::opCOPYFV(byte **buffer) { warning("opCOPYFV"); }

/**
 * @brief Opcode: TODO - no idea
 * @param buffer 
*/
void CastlxEngine::opCOPYVB(byte **buffer) {
	if (_mouseCursorVisible) {
		warning("opCOPYVB missing parameters");
	} else {
		skipNoiseInString(buffer);
		_word113C8 = parseString(buffer);
		skipNoiseInString(buffer);
		_word113CA = parseString(buffer);
		skipNoiseInString(buffer);
		_word113CC = parseString(buffer);
		skipNoiseInString(buffer);
		_word113CE = parseString(buffer);
	}

	warning("opCOPYVB %d %d %d %d", _word113C8, _word113CA, _word113CC, _word113CE);
	sub1114D(_word1E0B2_screenPtr2, _word1E0B6);
	sub10FC9();
}
void CastlxEngine::opCOPYFB(byte **buffer) { warning("opCOPYFB"); }
void CastlxEngine::opCOPYBV(byte **buffer) { warning("opCOPYBV"); }
void CastlxEngine::opCOPYBF(byte **buffer) { warning("opCOPYBF"); }

/**
 * @brief Opcode: TODO: clarify which type of sprite display it is
 * @param buffer 
*/
void CastlxEngine::opAFFSPRITEV(byte **buffer) {
	skipNoiseInString(buffer);
	int param1 = parseString(buffer);
	skipNoiseInString(buffer);
	int param2 = parseString(buffer);
	skipNoiseInString(buffer);
	int param3 = parseString(buffer);
	skipNoiseInString(buffer);
	int param4 = parseString(buffer);
	if (skipNoiseInString(buffer))
		_byte1E7EA = parseString(buffer);
	else
		_byte1E7EA = 0;

	warning("opAFFSPRITEV %d %d %d index: %d [%d]", param1, param2, param3, param4, _byte1E7EA);
	
	sub1B1A4(param1, param2, param3, _spritePtr[param4]);
}
void CastlxEngine::opAFFSPRITEF(byte **buffer) { warning("opAFFSPRITEF"); }
void CastlxEngine::opMODESPRITE(byte **buffer) { warning("opMODESPRITE"); }
void CastlxEngine::opCLEARV(byte **buffer) { warning("opCLEARV"); }
void CastlxEngine::opCLEARF(byte **buffer) { warning("opCLEARF"); }
void CastlxEngine::opOTEPAL(byte **buffer) { warning("opOTEPAL"); }
void CastlxEngine::opMETPAL(byte **buffer) { warning("opMETPAL"); }
void CastlxEngine::opREADMOUSE(byte **buffer) { warning("opREADMOUSE"); }

/**
 * @brief Opcode: Call the hardcoded logic of the game
 * @param buffer 
*/
void CastlxEngine::opGAME(byte **buffer) {
	skipNoiseInString(buffer);
	int index = parseString(buffer);
	warning("opGAME %d", index);

	_flagEnableHotspots = _mouseButtonStatus;
	++_mouseCursorVisible;

	if (index == 0) {
		sub12C73();
		sub12279();
	}

	(this->*_hardcodedLogic[index])();

	if (index == 0) {
		handleSoundOff();
		displayMessageUselessAction();
		--_mouseCursorVisible;
	}
}
void CastlxEngine::opTRANSV(byte **buffer) { warning("opTRANSV"); }
void CastlxEngine::opTRANSF(byte **buffer) { warning("opTRANSF"); }

/**
 * @brief Opcode: Handle transparency
 * @param buffer 
*/
void CastlxEngine::opTRANSPARENCE(byte **buffer) {
	warning("opTRANSPARENCE");
	if (_mouseCursorVisible)
		warning("opTRANSPARENCE - col1 not set");
	else {
		_unkCol1[0] = 110;
		_unkCol1[1] = 110;
		_unkCol1[2] = 110;
	}

	sub1C2B0();
}

void CastlxEngine::initOpcodes() {
	_opcodes[0]._keyword = "LOADIMG";
	_opcodes[0]._opcodePtr = &CastlxEngine::opLOADIMG;
	_opcodes[1]._keyword = "EXIT";
	_opcodes[1]._opcodePtr = &CastlxEngine::opEXIT;
	_opcodes[2]._keyword = "TEMPO";
	_opcodes[2]._opcodePtr = &CastlxEngine::opTEMPO;
	_opcodes[3]._keyword = "OTEPALETTE";
	_opcodes[3]._opcodePtr = &CastlxEngine::opOTEPALETTE;
	_opcodes[4]._keyword = "METPALETTE";
	_opcodes[4]._opcodePtr = &CastlxEngine::opMETPALETTE;
	_opcodes[5]._keyword = "DEF";
	_opcodes[5]._opcodePtr = &CastlxEngine::opDEF;
	_opcodes[6]._keyword = "NAME";
	_opcodes[6]._opcodePtr = &CastlxEngine::opNAME;
	_opcodes[7]._keyword = "IF";
	_opcodes[7]._opcodePtr = &CastlxEngine::opIF;
	_opcodes[8]._keyword = ":";
	_opcodes[8]._opcodePtr = &CastlxEngine::opLabel;
	_opcodes[9]._keyword = "JUMP";
	_opcodes[9]._opcodePtr = &CastlxEngine::opJUMP;
	_opcodes[10]._keyword = "CALL";
	_opcodes[10]._opcodePtr = &CastlxEngine::opCALL;
	_opcodes[11]._keyword = "RETURN";
	_opcodes[11]._opcodePtr = &CastlxEngine::opRETURN;
	_opcodes[12]._keyword = "UNCALL";
	_opcodes[12]._opcodePtr = &CastlxEngine::opUNCALL;
	_opcodes[13]._keyword = "KEY";
	_opcodes[13]._opcodePtr = &CastlxEngine::opKEY;
	_opcodes[14]._keyword = "RESO";
	_opcodes[14]._opcodePtr = &CastlxEngine::opRESO;
	_opcodes[15]._keyword = "TIMER";
	_opcodes[15]._opcodePtr = &CastlxEngine::opTIMER;
	_opcodes[16]._keyword = "WAIT";
	_opcodes[16]._opcodePtr = &CastlxEngine::opWAIT;
	_opcodes[17]._keyword = "TIMEPLAY";
	_opcodes[17]._opcodePtr = &CastlxEngine::opTIMEPLAY;
	_opcodes[18]._keyword = "PLAYFLI";
	_opcodes[18]._opcodePtr = &CastlxEngine::opPLAYFLI;
	_opcodes[19]._keyword = "PLAYFLX";
	_opcodes[19]._opcodePtr = &CastlxEngine::opPLAYFLX;
	_opcodes[20]._keyword = "CLIPPLAY";
	_opcodes[20]._opcodePtr = &CastlxEngine::opCLIPPLAY;
	_opcodes[21]._keyword = "AFFMOUSEV";
	_opcodes[21]._opcodePtr = &CastlxEngine::opAFFMOUSEV;
	_opcodes[22]._keyword = "AFFMOUSEF";
	_opcodes[22]._opcodePtr = &CastlxEngine::opAFFMOUSEF;
	_opcodes[23]._keyword = "VBL";
	_opcodes[23]._opcodePtr = &CastlxEngine::opVBL;
	_opcodes[24]._keyword = "Libre";
	_opcodes[24]._opcodePtr = &CastlxEngine::opDummy;
	_opcodes[25]._keyword = "OPENFLI";
	_opcodes[25]._opcodePtr = &CastlxEngine::opOPENFLI;
	_opcodes[26]._keyword = "OPENFLX";
	_opcodes[26]._opcodePtr = &CastlxEngine::opOPENFLX;
	_opcodes[27]._keyword = "ENDPLAY";
	_opcodes[27]._opcodePtr = &CastlxEngine::opENDPLAY;
	_opcodes[28]._keyword = "SETMOUSE";
	_opcodes[28]._opcodePtr = &CastlxEngine::opSETMOUSE;
	_opcodes[29]._keyword = "CLIPMOUSE";
	_opcodes[29]._opcodePtr = &CastlxEngine::opCLIPMOUSE;
	_opcodes[30]._keyword = "LOAD";
	_opcodes[30]._opcodePtr = &CastlxEngine::opLOAD;
	_opcodes[31]._keyword = "LOADSPR";
	_opcodes[31]._opcodePtr = &CastlxEngine::opLOADSPR;
	_opcodes[32]._keyword = "PAUSE";
	_opcodes[32]._opcodePtr = &CastlxEngine::opPAUSE;
	_opcodes[33]._keyword = "RAZSPR";
	_opcodes[33]._opcodePtr = &CastlxEngine::opRAZSPR;
	_opcodes[34]._keyword = "Libre";
	_opcodes[34]._opcodePtr = &CastlxEngine::opDummy;
	_opcodes[35]._keyword = "PALNOIR";
	_opcodes[35]._opcodePtr = &CastlxEngine::opPALNOIR;
	_opcodes[36]._keyword = "LOADPALETTE";
	_opcodes[36]._opcodePtr = &CastlxEngine::opLOADPALETTE;
	_opcodes[37]._keyword = "SETPLAY";
	_opcodes[37]._opcodePtr = &CastlxEngine::opSETPLAY;
	_opcodes[38]._keyword = "CLOSEPLAY";
	_opcodes[38]._opcodePtr = &CastlxEngine::opCLOSEPLAY;
	_opcodes[39]._keyword = "PALETTE";
	_opcodes[39]._opcodePtr = &CastlxEngine::opPALETTE;
	_opcodes[40]._keyword = "SETCOLORPLAY";
	_opcodes[40]._opcodePtr = &CastlxEngine::opSETCOLORPLAY;
	_opcodes[41]._keyword = "SWITCH";
	_opcodes[41]._opcodePtr = &CastlxEngine::opSWITCH;
	_opcodes[42]._keyword = "MODEPLAY";
	_opcodes[42]._opcodePtr = &CastlxEngine::opMODEPLAY;
	_opcodes[43]._keyword = "INCRUSTIMGV";
	_opcodes[43]._opcodePtr = &CastlxEngine::opINCRUSTIMGV;
	_opcodes[44]._keyword = "INCRUSTIMGF";
	_opcodes[44]._opcodePtr = &CastlxEngine::opINCRUSTIMGF;
	_opcodes[45]._keyword = "COPYVF";
	_opcodes[45]._opcodePtr = &CastlxEngine::opCOPYVF;
	_opcodes[46]._keyword = "COPYFV";
	_opcodes[46]._opcodePtr = &CastlxEngine::opCOPYFV;
	_opcodes[47]._keyword = "COPYVB";
	_opcodes[47]._opcodePtr = &CastlxEngine::opCOPYVB;
	_opcodes[48]._keyword = "COPYFB";
	_opcodes[48]._opcodePtr = &CastlxEngine::opCOPYFB;
	_opcodes[49]._keyword = "COPYBV";
	_opcodes[49]._opcodePtr = &CastlxEngine::opCOPYBV;
	_opcodes[50]._keyword = "COPYBF";
	_opcodes[50]._opcodePtr = &CastlxEngine::opCOPYBF;
	_opcodes[51]._keyword = "AFFSPRITEV";
	_opcodes[51]._opcodePtr = &CastlxEngine::opAFFSPRITEV;
	_opcodes[52]._keyword = "AFFSPRITEF";
	_opcodes[52]._opcodePtr = &CastlxEngine::opAFFSPRITEF;
	_opcodes[53]._keyword = "MODESPRITE";
	_opcodes[53]._opcodePtr = &CastlxEngine::opMODESPRITE;
	_opcodes[54]._keyword = "CLEARV";
	_opcodes[54]._opcodePtr = &CastlxEngine::opCLEARV;
	_opcodes[55]._keyword = "CLEARF";
	_opcodes[55]._opcodePtr = &CastlxEngine::opCLEARF;
	_opcodes[56]._keyword = "OTEPAL";
	_opcodes[56]._opcodePtr = &CastlxEngine::opOTEPAL;
	_opcodes[57]._keyword = "METPAL";
	_opcodes[57]._opcodePtr = &CastlxEngine::opMETPAL;
	_opcodes[58]._keyword = "READMOUSE";
	_opcodes[58]._opcodePtr = &CastlxEngine::opREADMOUSE;
	_opcodes[59]._keyword = "GAME";
	_opcodes[59]._opcodePtr = &CastlxEngine::opGAME;
	_opcodes[60]._keyword = "TRANSV";
	_opcodes[60]._opcodePtr = &CastlxEngine::opTRANSV;
	_opcodes[61]._keyword = "TRANSF";
	_opcodes[61]._opcodePtr = &CastlxEngine::opTRANSF;
	_opcodes[62]._keyword = "TRANSPARENCE";
	_opcodes[62]._opcodePtr = &CastlxEngine::opTRANSPARENCE;
}

void CastlxEngine::hlCheckAge() { warning("STUB hlCheckAge"); }
void CastlxEngine::hlGate() { warning("STUB hlGate"); }
void CastlxEngine::hlHall() { warning("STUB hlHall"); }
void CastlxEngine::hlKitchen() { warning("STUB hlKitchen"); }
void CastlxEngine::hlCellar() { warning("STUB hlCellar"); }
void CastlxEngine::hlDiningRoom() { warning("STUB hlDiningRoom"); }
void CastlxEngine::hlLivingRoom() { warning("STUB hlLivingRoom"); }
void CastlxEngine::hlDungeon() { warning("STUB hlDungeon"); }
void CastlxEngine::hlLibrary() { warning("STUB hlLibrary"); }
void CastlxEngine::hlMaevaRoom() { warning("STUB hlMaevaRoom"); }
void CastlxEngine::hlBathroom() { warning("STUB hlBathroom"); }
void CastlxEngine::hlBedroom1() { warning("STUB hlBedroom1"); }
void CastlxEngine::hlBedroom2() { warning("STUB hlBedroom2"); }
void CastlxEngine::hlAttic() { warning("STUB hlAttic"); }

void CastlxEngine::initHardcodedLogic() {
	_hardcodedLogic[0] = &CastlxEngine::hlCheckAge;
	_hardcodedLogic[1] = &CastlxEngine::hlGate;
	_hardcodedLogic[2] = &CastlxEngine::hlHall;
	_hardcodedLogic[3] = &CastlxEngine::hlKitchen;
	_hardcodedLogic[4] = &CastlxEngine::hlCellar;
	_hardcodedLogic[5] = &CastlxEngine::hlDiningRoom;
	_hardcodedLogic[6] = &CastlxEngine::hlLivingRoom;
	_hardcodedLogic[7] = &CastlxEngine::hlDungeon;
	_hardcodedLogic[8] = &CastlxEngine::hlLibrary;
	_hardcodedLogic[9] = &CastlxEngine::hlMaevaRoom;
	_hardcodedLogic[10] = &CastlxEngine::hlBathroom;
	_hardcodedLogic[11] = &CastlxEngine::hlBedroom1;
	_hardcodedLogic[12] = &CastlxEngine::hlBedroom2;
	_hardcodedLogic[13] = &CastlxEngine::hlAttic;
}

void CastlxEngine::loadGst(int fileNumber) {
	Common::String filename = Common::String::format("%02d.GST", fileNumber);
	delete[] _gstPtr;
	_gstPtr = loadFile(filename);
/*
	_guess_postGstSegment = _gstPtr + _decompFileSize;
*/
	_gstEndPtr = _gstPtr + _lastFileSize;

	for (int i = 0; i < 5; ++i)
		_spritePtr[i] = _postGstSegment;
/*
	word1E7D9 = _guess_postGstSegment;
*/
	setDisplayStringQueueIdTo0();
	_mouseCursorVisible = false;

	_label._keyword = "";
	_label._gstLabelPtr = nullptr;

	_curGstPtr = _gstPtr;
}

void CastlxEngine::sub19A16() {
	if (!_engineFlags[29])
		return;

	if (_engineFlags[46]) {
		warning("TODO: sub19A16 - Exit");
	}

	if (_engineFlags[56] && _engineFlags[83]) {
		warning("TODO: sub19A16 - Replace 'and bl, 0DFh' by 'xor al, 0x12' at loc_10472");
	}
}

void CastlxEngine::sub1024E() {
	if (!_engineFlags[25])
		return;

	warning("STUB: sub1024E");
}

void CastlxEngine::handleGst(byte **buffer) {
	while (_curGstPtr < _gstEndPtr) {
		byte curByte = *_curGstPtr;
		if (!curByte)
			break;

		if (curByte == '#') {
			Common::String comment;
			while (curByte != 0xA && curByte != 0xD && curByte) {
				comment += curByte;
				curByte = *++_curGstPtr;
			}
			warning("Handle GST - Comment : %s", comment.c_str());
		}

		if (curByte <= ' ') {
			++_curGstPtr;
			continue;
		}

		sub19A16();
		sub1024E();

		Common::String nextWord;
		while (curByte > ' ') {
			nextWord += curByte;
			curByte = *++_curGstPtr;
		}

		if (nextWord[0] == ':') {
			_label._keyword = nextWord;
			_label._keyword.deleteChar(0);
			_label._gstLabelPtr = _curGstPtr;
		} else {
			int i;
			for (i = 0; i < 63; ++i) {
				if (nextWord.equalsIgnoreCase(_opcodes[i]._keyword)) {
					(this->*_opcodes[i]._opcodePtr)(&_curGstPtr);
					break;
				}
			}
			if (i == 63)
				warning("Missed word: %s", nextWord.c_str());
		}
	}
	
}

byte *CastlxEngine::loadFile(Common::String &filename) {
	Common::String shortName = filename;
	while (shortName.contains('\\'))
		shortName.deleteChar(0);
	
	Common::File f;
	f.open(shortName);

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
	dump.open(shortName + ".dump");
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

	initOpcodes();
	initHardcodedLogic();
	
	/*
	initMouse(629, 399, 0, 0);
	setMousePosition(320, 100);
	sub1AC52();
	sub1AC99();
	sub1E033();
	*/
	
	Common::String filename = "SONG0.OUT";
	_song0 = loadFile(filename);
	filename = "SONG1.OUT";
	_song1 = loadFile(filename);

	loadGst(0);
	sub19817();
	_int8Counter3 = 0;

	handleGst(&_word2A302);
	
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
