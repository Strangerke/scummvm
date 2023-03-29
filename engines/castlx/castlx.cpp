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
	_word2A302 = nullptr;
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

void CastlxEngine::opLOADIMG(byte **buffer) { warning("STUB - opLOADIMG"); }
void CastlxEngine::opEXIT(byte **buffer) { warning("STUB - opEXIT"); }
void CastlxEngine::opTEMPO(byte **buffer) { warning("STUB - opTEMPO"); }
void CastlxEngine::opOTEPALETTE(byte **buffer) { warning("opOTEPALETTE"); }
void CastlxEngine::opMETPALETTE(byte **buffer) { warning("opMETPALETTE"); }

int CastlxEngine::skipNoiseInString(byte **bufferPtr) {
	byte *oldPtr = *bufferPtr;
	byte *curPtr = *bufferPtr;

	byte curByte = *curPtr;
	while (curByte != 0 && curByte != 0xA && curByte != 0xD) {
		if (curByte == '=' || curByte == '.' || curByte == '"' || curByte == '\'' || curByte < 0x20) {
			curByte = *++curPtr;
			continue;
		}
		*bufferPtr = curPtr;
		return 1;
	}
	*bufferPtr = oldPtr;
	return 0;
}

int CastlxEngine::parseString(byte **bufferPtr) {
	byte *curPtr = *bufferPtr;
	byte curByte = *curPtr;

	if (curByte == '\'' || curByte == '"') {
		int retVal = *++curPtr;
		curPtr += 2;
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
		return retVal;
	}

	if (curByte == '_') {
		warning("STUB parseString case _");
		*bufferPtr = curPtr;
		return 0;
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

void CastlxEngine::opDEF(byte **bufferPtr) {
	warning("opDEF");
	skipNoiseInString(bufferPtr);
	int index = parseString(bufferPtr);
	skipNoiseInString(bufferPtr);
	warning("copyValue(bufferPtr, _defineArray[index]);");
}

void CastlxEngine::opNAME(byte **buffer) { warning("opNAME"); }
void CastlxEngine::opIF(byte **buffer) { warning("opIF"); }
void CastlxEngine::opLabel(byte **buffer) { warning("opLabel"); }
void CastlxEngine::opJUMP(byte **buffer) { warning("opJUMP"); }
void CastlxEngine::opCALL(byte **buffer) { warning("opCALL"); }
void CastlxEngine::opRETURN(byte **buffer) { warning("opRETURN"); }
void CastlxEngine::opUNCALL(byte **buffer) { warning("opUNCALL"); }
void CastlxEngine::opKEY(byte **buffer) { warning("opKEY"); }
void CastlxEngine::opRESO(byte **buffer) { warning("opRESO"); }
void CastlxEngine::opTIMER(byte **buffer) { warning("opTIMER"); }
void CastlxEngine::opWAIT(byte **buffer) { warning("opWAIT"); }
void CastlxEngine::opTIMEPLAY(byte **buffer) { warning("opTIMEPLAY"); }
void CastlxEngine::opPLAYFLI(byte **buffer) { warning("opPLAYFLI"); }
void CastlxEngine::opPLAYFLX(byte **buffer) { warning("opPLAYFLX"); }
void CastlxEngine::opCLIPPLAY(byte **buffer) { warning("opCLIPPLAY"); }
void CastlxEngine::opAFFMOUSEV(byte **buffer) { warning("opAFFMOUSEV"); }
void CastlxEngine::opAFFMOUSEF(byte **buffer) { warning("opAFFMOUSEF"); }
void CastlxEngine::opVBL(byte **buffer) { warning("opVBL"); }
void CastlxEngine::opDummy(byte **buffer) { warning("opDummy"); }
void CastlxEngine::opOPENFLI(byte **buffer) { warning("opOPENFLI"); }
void CastlxEngine::opOPENFLX(byte **buffer) { warning("opOPENFLX"); }
void CastlxEngine::opENDPLAY(byte **buffer) { warning("opENDPLAY"); }
void CastlxEngine::opSETMOUSE(byte **buffer) { warning("opSETMOUSE"); }
void CastlxEngine::opCLIPMOUSE(byte **buffer) { warning("opCLIPMOUSE"); }
void CastlxEngine::opLOAD(byte **buffer) { warning("opLOAD"); }
void CastlxEngine::opLOADSPR(byte **buffer) { warning("opLOADSPR"); }
void CastlxEngine::opPAUSE(byte **buffer) { warning("opPAUSE"); }
void CastlxEngine::opRAZSPR(byte **buffer) { warning("opRAZSPR"); }
void CastlxEngine::opPALNOIR(byte **buffer) { warning("opPALNOIR"); }
void CastlxEngine::opLOADPALETTE(byte **buffer) { warning("opLOADPALETTE"); }
void CastlxEngine::opSETPLAY(byte **buffer) { warning("opSETPLAY"); }
void CastlxEngine::opCLOSEPLAY(byte **buffer) { warning("opCLOSEPLAY"); }
void CastlxEngine::opPALETTE(byte **buffer) { warning("opPALETTE"); }
void CastlxEngine::opSETCOLORPLAY(byte **buffer) { warning("opSETCOLORPLAY"); }
void CastlxEngine::opSWITCH(byte **buffer) { warning("opSWITCH"); }
void CastlxEngine::opMODEPLAY(byte **buffer) { warning("opMODEPLAY"); }
void CastlxEngine::opINCRUSTIMGV(byte **buffer) { warning("opINCRUSTIMGV"); }
void CastlxEngine::opINCRUSTIMGF(byte **buffer) { warning("opINCRUSTIMGF"); }
void CastlxEngine::opCOPYVF(byte **buffer) { warning("opCOPYVF"); }
void CastlxEngine::opCOPYFV(byte **buffer) { warning("opCOPYFV"); }
void CastlxEngine::opCOPYVB(byte **buffer) { warning("opCOPYVB"); }
void CastlxEngine::opCOPYFB(byte **buffer) { warning("opCOPYFB"); }
void CastlxEngine::opCOPYBV(byte **buffer) { warning("opCOPYBV"); }
void CastlxEngine::opCOPYBF(byte **buffer) { warning("opCOPYBF"); }
void CastlxEngine::opAFFSPRITEV(byte **buffer) { warning("opAFFSPRITEV"); }
void CastlxEngine::opAFFSPRITEF(byte **buffer) { warning("opAFFSPRITEF"); }
void CastlxEngine::opMODESPRITE(byte **buffer) { warning("opMODESPRITE"); }
void CastlxEngine::opCLEARV(byte **buffer) { warning("opCLEARV"); }
void CastlxEngine::opCLEARF(byte **buffer) { warning("opCLEARF"); }
void CastlxEngine::opOTEPAL(byte **buffer) { warning("opOTEPAL"); }
void CastlxEngine::opMETPAL(byte **buffer) { warning("opMETPAL"); }
void CastlxEngine::opREADMOUSE(byte **buffer) { warning("opREADMOUSE"); }
void CastlxEngine::opGAME(byte **buffer) { warning("opGAME"); }
void CastlxEngine::opTRANSV(byte **buffer) { warning("opTRANSV"); }
void CastlxEngine::opTRANSF(byte **buffer) { warning("opTRANSF"); }
void CastlxEngine::opTRANSPARENCE(byte **buffer) { warning("opTRANSPARENCE"); }

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

void CastlxEngine::loadGst(int fileNumber) {
	Common::String filename = Common::String::format("%02d.GST", fileNumber);
	_gstPtr = loadFile(filename);
/*
	_guess_postGstSegment = _gstPtr + _decompFileSize;
*/
	_gstEndPtr = _gstPtr + _lastFileSize;
	
/*
	word1E7D9 = word1E0C0 = word1E0C2 = word1E0C4 = word1E0C6 = word1E0C8 = _guess_postGstSegment;
*/
	setDisplayStringQueueIdTo0();
	_mouseCursorVisible = false;
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
	byte *curGstPtr = _gstPtr;
	while (curGstPtr < _gstEndPtr) {
		byte curByte = *curGstPtr;
		if (!curByte)
			break;

		if (curByte == '#') {
			Common::String comment;
			while (curByte != 0xA && curByte != 0xD && curByte) {
				comment += curByte;
				curByte = *++curGstPtr;
			}
			warning("Handle GST - Comment : %s", comment.c_str());
		}

		if (curByte <= ' ') {
			++curGstPtr;
			continue;
		}

		sub19A16();
		sub1024E();

		Common::String nextWord;
		while (curByte > ' ') {
			nextWord += curByte;
			curByte = *++curGstPtr;
		}

		warning("Next word: %s", nextWord.c_str());

		if (nextWord[0] == ':') {
			_label._keyword = nextWord;
			_label._keyword.deleteChar(0);
			_label._gstLabelPtr = curGstPtr;
		} else {
			for (int i = 0; i < 63; ++i) {
				if (nextWord.equalsIgnoreCase(_opcodes[i]._keyword)) {
					(this->*_opcodes[i]._opcodePtr)(&curGstPtr);
				}
			}
		}
	}
	
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

	initOpcodes();
	
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
