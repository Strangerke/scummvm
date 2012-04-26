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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "robin/robin.h"
#include "robin/script.h"
#include "common/debug.h"

#include "common/system.h"

namespace Robin {

RobinScript::RobinScript(RobinEngine *vm) : _vm(vm), _currScript(NULL) {
	_byte129A0 = 0xFF;
	displayMap = 0;
	_byte1855D = 0;
	_byte12A04 = 0;
	_byte10806 = 0;
	_byte12FE4 = 0xFF;
	_byte16F02 = 0;

	_word1855E = 0;
	_word16F00 = -1;
	_viewportCharacterTarget = -1;
	_word10804 = 0;
	_heroismBarX = 0;
	_heroismBarBottomY = 0;
	_viewportX = 0;
	_viewportY = 0;
	_word18776 = 0;



	_savedBuffer215Ptr = NULL;

	for (int i = 0; i < 20; i++) {
		_array122E9[i] = 0;
		_array122FD[i] = 0;
	}

	for (int i = 0; i < 32; i++)
		_array1813B[i] = 0;

	for (int i = 0; i < 40; i++) {
		_array10B29[i] = 1;
		_array128EF[i] = 15;
		_array10AB1[i] = 0;
		_array12811[i] = 16;
		_array12839[i] = 0xFF;
		_array16123[i] = 0;
		_array1614B[i] = 0;
		_array16173[i] = 0xFF;
		_array122C1[i] = 0;
		_array1813B[i] = 0;
	}

	for (int i = 0; i < 640; i++) {
		_array12311[i] = -1;
	}
}

RobinScript::~RobinScript() {
}

byte RobinScript::handleOpcodeType1(int curWord) {
	debugC(2, kDebugScript, "handleOpcodeType1(0x%x)", curWord);
	switch (curWord) {
	case 0x0:
		return OC_sub173DF();
		break;
	case 0x1:
		return OC_sub173F0();
		break;
	case 0x2:
		return OC_sub1740A();
		break;
	case 0x3:
		return OC_sub17434();
		break;
	case 0x4:
		return OC_sub17468();
		break;
	case 0x5:
		return OC_getRandom();
		break;
	case 0x6:
		return OC_sub1748C();
		break;
	case 0x7:
		return OC_compWord18776();
		break;
	case 0x8:
		return OC_checkSaveFlag();
		break;
	case 0x9:
		return OC_sub174C8();
		break;
	case 0xA:
		return OC_sub174D8();
		break;
	case 0xB:
		return OC_sub1750E();
		break;
	case 0xC:
		return OC_compareCoords_1();
		break;
	case 0xD:
		return OC_compareCoords_2();
		break;
	case 0xE:
		return OC_sub1757C();
		break;
	case 0xF:
		return OC_sub1759E();
		break;
	case 0x10:
		return OC_compWord16EF8();
		break;
	case 0x11:
		return OC_sub175C8();
		break;
	case 0x12:
		return OC_sub17640();
		break;
	case 0x13:
		return OC_sub176C4();
		break;
	case 0x14:
		return OC_compWord10804();
		break;
	case 0x15:
		return OC_sub17766();
		break;
	case 0x16:
		return OC_sub17782();
		break;
	case 0x17:
		return OC_sub1779E();
		break;
	case 0x18:
		return OC_sub177C6();
		break;
	case 0x19:
		return OC_compWord16EFE();
		break;
	case 0x1A:
		return OC_sub177F5();
		break;
	case 0x1B:
		return OC_sub17812();
		break;
	case 0x1C:
		return OC_sub17825();
		break;
	case 0x1D:
		return OC_sub17844();
		break;
	case 0x1E:
		return OC_sub1785C();
		break;
	case 0x1F:
		return OC_sub17886();
		break;
	case 0x20:
		return OC_sub178A8();
		break;
	case 0x21:
		return OC_sub178BA();
		break;
	case 0x22:
		return OC_sub178C2();
		break;
	case 0x23:
		return OC_sub178D2();
		break;
	case 0x24:
		return OC_sub178E8();
		break;
	case 0x25:
		return OC_sub178FC();
		break;
	case 0x26:
		return OC_sub1790F();
		break;
	case 0x27:
		return OC_sub1792A();
		break;
	case 0x28:
		return OC_sub1793E();
		break;
	case 0x29:
		return OC_sub1795E();
		break;
	case 0x2A:
		return OC_sub1796E();
		break;
	case 0x2B:
		return OC_sub17984();
		break;
	case 0x2C:
		return OC_checkSavedMousePos();
		break;
	case 0x2D:
		return OC_sub179AE();
		break;
	case 0x2E:
		return OC_sub179C2();
		break;
	case 0x2F:
		return OC_sub179E5();
		break;
	case 0x30:
		return OC_sub17A07();
		break;
	case 0x31:
		return OC_sub17757();
		break;
	default:
		error("Unexpected opcode %d", curWord);
		break;
	}
}

void RobinScript::handleOpcodeType2(int curWord) {
	debugC(2, kDebugScript, "handleOpcodeType2(0x%x)", curWord);
	switch (curWord) {
	case 0x0:
		OC_setWord18821();
		break;
	case 0x1:
		OC_sub17A3E();
		break;
	case 0x2:
		OC_sub17D57();
		break;
	case 0x3:
		OC_sub17D7F();
		break;
	case 0x4:
		OC_sub17DB9();
		break;
	case 0x5:
		OC_sub17DF9();
		break;
	case 0x6:
		OC_sub17E07();
		break;
	case 0x7:
		OC_sub17E15();
		break;
	case 0x8:
		OC_sub17B03();
		break;
	case 0x9:
		OC_getRandom_type2();
		break;
	case 0xA:
		OC_sub17A66();
		break;
	case 0xB:
		OC_sub17A8D();
		break;
	case 0xC:
		OC_saveAndQuit();
		break;
	case 0xD:
		OC_sub17B93();
		break;
	case 0xE:
		OC_sub17E37();
		break;
	case 0xF:
		OC_resetByte1714E();
		break;
	case 0x10:
		OC_deleteSavegameAndQuit();
		break;
	case 0x11:
		OC_incByte16F04();
		break;
	case 0x12:
		OC_sub17BA5();
		break;
	case 0x13:
		OC_setByte18823();
		break;
	case 0x14:
		OC_sub17BB7();
		break;
	case 0x15:
		OC_sub17BF2();
		break;
	case 0x16:
		OC_sub17ACC();
		break;
	case 0x17:
		OC_resetByte16F04();
		break;
	case 0x18:
		OC_sub17AE1();
		break;
	case 0x19:
		OC_sub17AEE();
		break;
	case 0x1A:
		OC_setWord10804();
		break;
	case 0x1B:
		OC_sub17C0E();
		break;
	case 0x1C:
		OC_sub17C55();
		break;
	case 0x1D:
		OC_sub17C76();
		break;
	case 0x1E:
		OC_sub17AFC();
		break;
	case 0x1F:
		OC_sub17C8B();
		break;
	case 0x20:
		OC_sub17CA2();
		break;
	case 0x21:
		OC_sub17CB9();
		break;
	case 0x22:
		OC_sub17CD1();
		break;
	case 0x23:
		OC_resetWord16EFE();
		break;
	case 0x24:
		OC_sub17CEF();
		break;
	case 0x25:
		OC_sub17D1B();
		break;
	case 0x26:
		OC_sub17D23();
		break;
	case 0x27:
		OC_sub17E6D();
		break;
	case 0x28:
		OC_sub17E7E();
		break;
	case 0x29:
		OC_sub17E99();
		break;
	case 0x2A:
		OC_sub17EC5();
		break;
	case 0x2B:
		OC_sub17EF4();
		break;
	case 0x2C:
		OC_sub17F08();
		break;
	case 0x2D:
		OC_sub17F4F();
		break;
	case 0x2E:
		OC_sub17F68();
		break;
	case 0x2F:
		OC_getNextVal();
		break;
	case 0x30:
		OC_sub17FD2();
		break;
	case 0x31:
		OC_sub17FDD();
		break;
	case 0x32:
		OC_setByte10B29();
		break;
	case 0x33:
		OC_sub18007();
		break;
	case 0x34:
		OC_sub18014();
		break;
	case 0x35:
		OC_sub1801D();
		break;
	case 0x36:
		OC_sub1805D();
		break;
	case 0x37:
		OC_sub18074();
		break;
	case 0x38:
		OC_sub1808B();
		break;
	case 0x39:
		OC_sub18099();
		break;
	case 0x3A:
		OC_sub180C3();
		break;
	case 0x3B:
		OC_sub1810A();
		break;
	case 0x3C:
		OC_sub1812D();
		break;
	case 0x3D:
		OC_sub1817F();
		break;
	case 0x3E:
		OC_sub181BB();
		break;
	case 0x3F:
		OC_sub18213();
		break;
	case 0x40:
		OC_sub18252();
		break;
	case 0x41:
		OC_sub18260();
		break;
	case 0x42:
		OC_sub182EC();
		break;
	case 0x43:
		OC_PaletteFadeOut();
		break;
	case 0x44:
		OC_PaletteFadeIn();
		break;
	case 0x45:
		OC_loadAndDisplayCUBESx_GFX();
		break;
	case 0x46:
		OC_sub1834C();
		break;
	case 0x47:
		OC_sub18359();
		break;
	case 0x48:
		OC_sub18367();
		break;
	case 0x49:
		OC_sub17D04();
		break;
	case 0x4A:
		OC_sub18387();
		break;
	case 0x4B:
		OC_setByte14835();
		break;
	case 0x4C:
		OC_setByte14837();
		break;
	case 0x4D:
		OC_sub183A2();
		break;
	case 0x4E:
		OC_sub183C6();
		break;
	case 0x4F:
		OC_loadFile_AERIAL_GFX();
		break;
	case 0x50:
		OC_sub17E22();
		break;
	case 0x51:
		OC_sub1844A();
		break;
	case 0x52:
		OC_sub1847F();
		break;
	case 0x53:
		OC_displayVGAFile();
		break;
	case 0x54:
		OC_sub184D7();
		break;
	case 0x55:
		OC_displayTitleScreen();
		break;
	case 0x56:
		OC_sub1853B();
		break;
	case 0x57:
		OC_sub1864D();
		break;
	case 0x58:
		OC_initArr18560();
		break;
	case 0x59:
		OC_sub18678();
		break;
	case 0x5A:
		OC_sub18690();
		break;
	case 0x5B:
		OC_setWord10802();
		break;
	case 0x5C:
		OC_sub186A1();
		break;
	case 0x5D:
		OC_sub186E5_snd();
		break;
	case 0x5E:
		OC_sub1870A_snd();
		break;
	case 0x5F:
		OC_sub18725_snd();
		break;
	case 0x60:
		OC_sub18733_snd();
		break;
	case 0x61:
		OC_sub1873F_snd();
		break;
	case 0x62:
		OC_sub18746_snd();
		break;
	case 0x63:
		OC_sub1875D_snd();
		break;
	case 0x64:
		OC_sub18764();
		break;
	case 0x65:
		OC_sub1853B();
		break;
	default:
		error("Unknown opcode %d", curWord);
		break;
	}
}

int RobinScript::handleOpcode(Common::MemoryReadStream *script) {
	debugC(2, kDebugScript, "handleOpcode");
	_currScript = script;
	uint16 curWord = _currScript->readUint16LE();
	if (curWord == 0xFFF6)
		return 0xFF;

	for (; curWord != 0xFFF8; curWord = _currScript->readUint16LE()) {
		byte mask = 0; 
		if (curWord > 1000) {
			curWord -= 1000;
			mask = 1;
		}
		byte result = handleOpcodeType1(curWord);
		if ((result ^ mask) == 0) {
			do {
				curWord = _currScript->readUint16LE();
			} while (curWord != 0xFFF7);
			return 0;
		}
	}

	_vm->_byte1714E = 1;

	for (;;) {
		curWord = _currScript->readUint16LE();
		if (curWord == 0xFFF7)
			return _vm->_byte1714E;

		handleOpcodeType2(curWord);
	}
}

void RobinScript::runScript(Common::MemoryReadStream script) {
	debugC(1, kDebugScript, "runScript");
	_byte16F05_ScriptHandler = 1;
	
	while (handleOpcode(&script) != 0xFF)
		_vm->update();
}

void RobinScript::runMenuScript(Common::MemoryReadStream script) {
	debugC(1, kDebugScript, "runMenuScript");
	warning("========================== Menu Script ==============================");
	_byte16F05_ScriptHandler = 0;
	
	while (handleOpcode(&script) == 0)
		_vm->update();
}

void RobinScript::sub1863B() {
	_vm->_arr18560[0]._field0 = 0;
	_vm->_arr18560[1]._field0 = 0;
	_vm->_arr18560[2]._field0 = 0;
	_vm->_arr18560[3]._field0 = 0;
	_word1855E = 0;
}


void RobinScript::sub185ED(byte index, byte subIndex) {
	debugC(2, kDebugScript, "sub185ED");
	if (_vm->_arr18560[index]._field0 != 1)
		return;

	_vm->displayFunction1(_vm->_bufferIdeogram, _vm->_arr18560[index]._field5[subIndex], _vm->_arr18560[index]._field1, _vm->_arr18560[index]._field3);
}

byte RobinScript::compareValues(byte var1, int oper, int var2) {
	debugC(2, kDebugScript, "compareValues(%d, %c, %d)", var1, oper & 0xFF, var2);
	switch (oper & 0xFF) {
	case '<':
		return (var1 < var2);
	case '>':
		return (var1 > var2);
	default:
		return (var1 == var2);
		break;
	}
}

void RobinScript::computeOperation(byte *bufPtr, int oper, int var2) {
	debugC(1, kDebugScript, "computeOperation(bufPtr, %c, %d)", oper & 0xFF, var2 & 0xFF);

	switch (oper & 0xFF) {
	case '=':
		bufPtr[0] = var2 & 0xFF;
		break;
	case '+': {
		int tmpVal = bufPtr[0] + var2;
		if (tmpVal > 0xFF)
			bufPtr[0] = 0xFF;
		else
			bufPtr[0] = (byte)tmpVal;
		}
		break;
	case '-': {
		int tmpVal = bufPtr[0] - var2;
		if (tmpVal < 0)
			bufPtr[0] = 0;
		else
			bufPtr[0] = (byte)tmpVal;
		}
		break;
	case '*': {
		int tmpVal = bufPtr[0] * var2;
		bufPtr[0] = tmpVal & 0xFF;
		}
		break;
	case '/': {
		if (var2 != 0)
			bufPtr[0] /= var2;
		}
		break;
	default: {
		warning("computeOperation : oper %d", oper);
		if (var2 != 0) {
			int tmpVal = bufPtr[0] / var2;
			if (tmpVal < 0)
				bufPtr[0] = 0xFF;
			else 
				bufPtr[0] = 0;
		}
		break;
		}
	}
}



void RobinScript::sub185B4_display() {
	if (_vm->_byte12A04 == _byte1855D)
		return;

	_byte1855D = _vm->_byte12A04;
	
	assert(_word1855E < 8);
	int subIndex = _word1855E;
	sub185ED(0, subIndex);
	sub185ED(1, subIndex);
	sub185ED(2, subIndex);
	sub185ED(3, subIndex);

	// In the original, increment by 2 as it's an array of words
	++subIndex;
	if (subIndex == 8)
		subIndex = 0;

	_word1855E = subIndex;
}

void RobinScript::sub1823E(byte var1, byte var2, byte *curBufPtr) {
	debugC(1, kDebugScript, "sub1823E(%d, %d, curBufPtr)", var1, var2);

	assert ((var1 >= 0) && (var1 < 40));
	_array10B29[var1] = 1;
	curBufPtr[0] = var2;
	curBufPtr[1] = 0;
	curBufPtr[2] = 0;
	curBufPtr[3] = 0;
}

void RobinScript::sub17B6C(int var1) {
	debugC(1, kDebugScript, "sub17B6C(%d)", var1);

	if (var1 == 0) {
		int curWord = 0;
		while (curWord != 0xFFF6)
			curWord = _currScript->readUint16LE();
		
		_currScript->seek(_currScript->pos() - 4);
		return;
	}

	++var1;
	int curVal = 0;
	int tmpVal;
	while (curVal < var1) {
		tmpVal = _currScript->readUint16LE();
		if (tmpVal == 0xFFF7)
			++curVal;
	}

	_currScript->seek(_currScript->pos() - 2);
}

void RobinScript::sub16C86(int index, byte *buf) {
	debugC(1, kDebugScript, "sub16C86()");

	_array12811[index] = 0;

	for (int i = 0; i < 16; i++) {
		_array12311[(index * 16) + i] = (buf[(2 * i) + 1] << 8) + buf[2 * i];
	}
}

void RobinScript::sub16C5C(int index, byte var3) {
	debugC(1, kDebugScript, "sub16C5C(%d, %d)", index, var3);

	assert(index < 40);
	_array12839[index] = var3;

	byte *buf = _vm->_rulesChunk1;
	if (var3 != 0) {
		int count = 0;
		while (count < var3) {
			if ((buf[0] == 0xFF) && (buf[1] == 0xFF))
				++count;
			buf = &buf[2];
		}
	}

	sub16C86(index, buf);
}

int RobinScript::sub17D40(int var) {
	debugC(1, kDebugScript, "sub17D40(%d)", var);

	if ((displayMap != 1) && (_array16173[_vm->_rulesBuffer2PrevIndx] != 0xFF))
		return var;

	warning("sub17D40() - FIXME: Unexpected POP");
	return var;
}

void RobinScript::sub18A56(byte *buf) {
	warning("TODO: sub18A56(buf)");
}

void RobinScript::sub18B3C(int var) {
	debugC(2, kDebugScript, "sub18B3C(%d)", var);

	if (var == 0xFFFF)
		return;

	_word18776 = var;

	int index = _vm->_rulesChunk3[var];
	int count = 0;
	while (_vm->_rulesChunk4[index + count] != 0x5B)
		++count;

	int i = 0;
	if (count != 0) {
		int tmpVal = _vm->_rnd->getRandomNumber(count + 1);
		if (tmpVal != 0) {
			int i = 0;
			for (int j = 0; j < tmpVal; j++) {
				do
					++i;
				while (_vm->_rulesChunk4[index + count + i] != 0x5B);
			}
		}
	}

	sub18A56(&_vm->_rulesChunk4[index + count + i]);
}

int RobinScript::getValue1() {
	debugC(2, kDebugScript, "getValue1()");

	int curWord = _currScript->readUint16LE();
	if (curWord < 1000)
		return curWord;

	switch (curWord) {
	case 1000:
		return (int)_byte129A0;
	case 1001:
		return _vm->_rulesBuffer2PrevIndx;
	case 1002:
		return _word16F00;
	case 1003:
		return (int)_vm->_rulesBuffer2_15[6];
	case 1004:
		return _word10804;
	default:
		warning("getValue1: Unexpected large value %d", curWord);
		return curWord;
	}
}

int RobinScript::getValue2() {
	debugC(2, kDebugScript, "getValue2()");

	int curWord = _currScript->readUint16LE();
	int tmpVal = curWord >> 8;
	switch(tmpVal) {
	case 0xFF:
		assert((_vm->_rulesBuffer2PrevIndx >= 0) && (_vm->_rulesBuffer2PrevIndx < 40));
		return ((_vm->_rulesBuffer2_13[_vm->_rulesBuffer2PrevIndx] << 8) + _vm->_rulesBuffer2_14[_vm->_rulesBuffer2PrevIndx]);
	case 0xFE: {
		int index = curWord & 0xFF;
		assert((index >= 0) && (index < 40));
		return ((_vm->_rulesBuffer2_13[index] << 8) + _vm->_rulesBuffer2_14[index]);
		}
	case 0xFD:
		return _vm->_word16EFA;
	case 0xFC: {
		int index = curWord & 0xFF;
		assert(index < 40);
		byte var1 = _vm->_characterPositionX[index] >> 3;
		byte var2 = _vm->_characterPositionY[index] >> 3;

		return (var1 << 8) + var2;
		}
	case 0xFB: {
		int index = _word16F00;
		assert(index < 40);
		byte var1 = _vm->_characterPositionX[index] >> 3;
		byte var2 = _vm->_characterPositionY[index] >> 3;

		return (var1 << 8) + var2;
		}
	case 0xFA:
		return ((_vm->_array10999[_vm->_rulesBuffer2PrevIndx] << 8) + _vm->_array109C1[_vm->_rulesBuffer2PrevIndx]);
	case 0xF9:
		return ((_vm->_rulesBuffer2_15[4] << 8) + _vm->_rulesBuffer2_15[5]);
	case 0xF8: {
		int index = curWord & 0xFF;
		assert((index >= 0) && (index < 40));
		return _vm->_rulesBuffer12_3[index];
		}
	case 0xF7: {
		int index = _vm->_rulesBuffer2_15[6];
		assert(index < 40);
		byte var1 = _vm->_characterPositionX[index] >> 3;
		byte var2 = _vm->_characterPositionY[index] >> 3;

		return (var1 << 8) + var2;
		}
	case 0xF6:
		return _vm->_savedMousePosDivided;
	default:
		warning("getValue2 - 0x%x - High value %d", tmpVal, curWord);
		return curWord;
	}
}


void RobinScript::sub130B6() {
	debugC(1, kDebugScript, "sub130B6()");
	assert(_vm->_word12F68_ERULES <= 20);
	for (int i = 0; i < _vm->_word12F68_ERULES; i++) {
		if (_array122E9[i] == 3)
			_array122E9[i] = 2;
	}
}

byte *RobinScript::getBuffer215Ptr() {
	debugC(2, kDebugScript, "getBuffer215Ptr()");
	int tmpVal = getValue1();
	tmpVal *= 32;
	tmpVal += _currScript->readUint16LE();

	assert(tmpVal < 40 * 32);
	return &_vm->_rulesBuffer2_15[tmpVal];
}

byte RobinScript::OC_sub173DF() {
	warning("OC_sub173DF");
	return 0;
}
byte RobinScript::OC_sub173F0() {
	warning("OC_sub173F0");
	return 0;
}
byte RobinScript::OC_sub1740A() {
	warning("OC_sub1740A");
	return 0;
}

byte RobinScript::OC_sub17434() {
	debugC(1, kDebugScript, "OC_sub17434()");

	byte *tmpArr = getBuffer215Ptr();
	byte var1 = tmpArr[0];
	uint16 oper = _currScript->readUint16LE();
	int16 var2 = _currScript->readUint16LE();

	return compareValues(var1, oper, var2);
}

byte RobinScript::OC_sub17468() {
	warning("OC_sub17468");
	return 0;
}

byte RobinScript::OC_getRandom() {
	debugC(1, kDebugScript, "OC_getRandom()");

	int maxVal = _currScript->readUint16LE();
	int rand = _vm->_rnd->getRandomNumber(maxVal);
	_byte16F02 = (rand & 0xFF);
	
	if (rand == 0)
		return 1;

	return 0;
}

byte RobinScript::OC_sub1748C() {
	warning("OC_sub1748C");
	return 0;
}
byte RobinScript::OC_compWord18776() {
	warning("OC_compWord18776");
	return 0;
}
byte RobinScript::OC_checkSaveFlag() {
	debugC(1, kDebugScript, "OC_checkSaveFlag()");

	if (_vm->_saveFlag)
		return 1;

	return 0;
}

byte RobinScript::OC_sub174C8() {
	warning("OC_sub174C8");
	return 0;
}

byte RobinScript::OC_sub174D8() {
	debugC(1, kDebugScript, "OC_sub174D8()");

	byte tmpVal = getValue1() & 0xFF;
	int curWord = _currScript->readUint16LE();
	
	if (curWord == 3000) {
		int index;
		for (index = 0; index < _vm->_word10807_ERULES; index++) {
			if (_vm->_rulesBuffer2_5[index] == tmpVal) {
				_word16F00 = index;
				return 1;
			}
		}
	} else {
		_currScript->seek(_currScript->pos() - 2);
		int index = getValue1();
		assert(index < 40);
		if (_vm->_rulesBuffer2_5[index] == tmpVal) {
			_word16F00 = index;
			return 1;
		}
	}

	return 0;
}

byte RobinScript::OC_sub1750E() {
	warning("OC_sub1750E");
	return 0;
}

byte RobinScript::OC_compareCoords_1() {
	debugC(1, kDebugScript, "OC_compareCoords_1()");

	int index = _currScript->readUint16LE();
	assert(index < 40);

	int var3 = _vm->_rulesBuffer12_1[index];
	int var4 = _vm->_rulesBuffer12_2[index];
	int var1 = _vm->_word16EFA;

	if (((var1 >> 8) < (var3 >> 8)) || ((var1 >> 8) > (var3 & 0xFF)) || ((var1 & 0xFF) < (var4 >> 8)) || ((var1 & 0xFF) > (var4 & 0xFF)))
		return 0;

	return 1;
}

byte RobinScript::OC_compareCoords_2() {
	warning("compareCoords_2");
	return 0;
}
byte RobinScript::OC_sub1757C() {
	warning("OC_sub1757C");
	return 0;
}
byte RobinScript::OC_sub1759E() {
	warning("OC_sub1759E");
	return 0;
}

byte RobinScript::OC_compWord16EF8() {
	debugC(1, kDebugScript, "OC_compWord16EF8()");
	
	int tmpVal = getValue1();
	if (tmpVal == _vm->_rulesBuffer2PrevIndx)
		return 1;
	return 0;
}

byte RobinScript::OC_sub175C8() {
	debugC(1, kDebugScript, "OC_sub175C8()");
	
	byte var4 = _currScript->readUint16LE() & 0xFF;

	int tmpVal = _currScript->readUint16LE();
	
	if (tmpVal < 2000) {
		_currScript->seek(_currScript->pos() - 2);
		int index = getValue1();
		int var1 = _array10B51[(_vm->_rulesBuffer2PrevIndx * 40) + index];
		if ((var1 & 0xFF) < var4)
			return 0;
		
		_word16F00 = index;
		return 1;
	}

	if (tmpVal == 3000) {
		for (int i = 0; i < _vm->_word10807_ERULES; i++) {
			int var1 = _array10B51[(_vm->_rulesBuffer2PrevIndx * 40) + i];
			if ((var1 & 0xFF) >= var4) {
				_word16F00 = i;
				return 1;
			}
		}
		return 0;
	}
	
	tmpVal -= 2000;
	byte var4b = tmpVal & 0xFF;
	for (int i = 0; i < _vm->_word10807_ERULES; i++) {
		int var1 = _array10B51[(_vm->_rulesBuffer2PrevIndx * 40) + i];
		if ((var1 & 0xFF) >= var4) {
			if (_vm->_rulesBuffer2_12[i] == var4b) {
				_word16F00 = i;
				return 1;
			}
		}
	}	
	
	return 0;
}
byte RobinScript::OC_sub17640() {
	debugC(1, kDebugScript, "OC_sub176C4()");

	int var4 = _currScript->readUint16LE();
	int index = _vm->_rulesBuffer2PrevIndx * 40;
	int subIndex = 0xFFFF;

	int tmpVal = _currScript->readUint16LE();

	if (tmpVal >= 2000) {
		int var1 = tmpVal;

		if (var1 == 3000) {
			subIndex = 0;
			for (int i = 0; i < _vm->_word10807_ERULES; i++) {
				tmpVal = _array10B51[index + i];
				byte v1 = tmpVal & 0xFF;
				byte v2 = tmpVal >> 8;
				if ((v1 >= (var4 & 0xFF)) && (v2 < (var4 & 0xFF))) {
					_word16F00 = subIndex;
					return 1;
				}
			}
			return 0;
		} else {
			var1 -= 2000;
			var4 &= ((var1 & 0xFF) << 8);
			for (int i = 0; i < _vm->_word10807_ERULES; i++) {
				tmpVal = _array10B51[index + i];
				byte v1 = tmpVal & 0xFF;
				byte v2 = tmpVal >> 8;
				if ((v1 >= (var4 & 0xFF)) && (v2 < (var4 & 0xFF)) && (_vm->_rulesBuffer2_12[subIndex] != (var4 >> 8))) {
					_word16F00 = subIndex;
					return 1;
				}
			}
			return 0;
		}
	} else {
		_currScript->seek(_currScript->pos() - 2);
		subIndex = getValue1();
		tmpVal = _array10B51[index + subIndex];
		byte v1 = tmpVal & 0xFF;
		byte v2 = tmpVal >> 8;
		if ((v1 < (var4 & 0xFF)) || (v2 >= (var4 & 0xFF)))
			return 0;
		_word16F00 = subIndex;
		return 1;
	}
}

byte RobinScript::OC_sub176C4() {
	debugC(1, kDebugScript, "OC_sub176C4()");
	
	byte var4 = _currScript->readUint16LE() & 0xFF;

	int tmpVal = _currScript->readUint16LE();
	
	if (tmpVal < 2000) {
		_currScript->seek(_currScript->pos() - 2);
		int index = getValue1();
		int var1 = _array10B51[(_vm->_rulesBuffer2PrevIndx * 40) + index];
		if (((var1 & 0xFF) >= var4) || ((var1 >> 8) < var4))
			return 0;
		
		_word16F00 = index;
		return 1;
	}

	if (tmpVal == 3000) {
		for (int i = 0; i < _vm->_word10807_ERULES; i++) {
			int var1 = _array10B51[(_vm->_rulesBuffer2PrevIndx * 40) + i];
			if (((var1 & 0xFF) < var4) && ((var1 >> 8) >= var4)) {
				_word16F00 = i;
				return 1;
			}
		}
		return 0;
	}
	
	tmpVal -= 2000;
	byte var4b = tmpVal & 0xFF;
	for (int i = 0; i < _vm->_word10807_ERULES; i++) {
		int var1 = _array10B51[(_vm->_rulesBuffer2PrevIndx * 40) + i];
		if (((var1 & 0xFF) < var4) && ((var1 >> 8) >= var4)) {
			if (_vm->_rulesBuffer2_12[i] == var4b) {
				_word16F00 = i;
				return 1;
			}
		}
	}	
	
	return 0;
}

byte RobinScript::OC_compWord10804() {
	debugC(1, kDebugScript, "OC_compWord10804()");
	
	byte tmpVal = getValue1();
	
	if (tmpVal == _word10804)
		return 1;

	return 0;
}
byte RobinScript::OC_sub17766() {
	warning("OC_sub17766");
	return 0;
}
byte RobinScript::OC_sub17782() {
	warning("OC_sub17782");
	return 0;
}
byte RobinScript::OC_sub1779E() {
	warning("OC_sub1779E");
	return 0;
}
byte RobinScript::OC_sub177C6() {
	debugC(1, kDebugScript, "OC_sub177C6()");

	int index = _currScript->readUint16LE();
	if (_vm->_characterPositionX[index] == 0xFFFF)
		return 0;

	return 1;
}
byte RobinScript::OC_compWord16EFE() {
	debugC(1, kDebugScript, "OC_compWord16EFE()");

	byte curByte = _currScript->readUint16LE() & 0xFF;
	byte tmpVal = _vm->_word16EFE >> 8;

	if (curByte != tmpVal)
		return 0;

	_word16F00 = (_vm->_word16EFE & 0xFF);
	return 1;
}

byte RobinScript::OC_sub177F5() {
	debugC(1, kDebugScript, "OC_sub177F5()");

	byte var1 = _currScript->readUint16LE() & 0xFF;
	byte var2 = _currScript->readUint16LE() & 0xFF;

	assert(_vm->_ptr_rulesBuffer2_15 != NULL);

	if ((var1 == _vm->_ptr_rulesBuffer2_15[0]) && (var2 == _vm->_ptr_rulesBuffer2_15[1]))
		return 1;

	return 0;
}

byte RobinScript::OC_sub17812() {
	debugC(1, kDebugScript, "OC_sub17812()");

	byte curByte = (_currScript->readUint16LE() & 0xFF);
	assert(_vm->_ptr_rulesBuffer2_15 != NULL);
	if (_vm->_ptr_rulesBuffer2_15[0] == curByte)
		return 1;
	return 0;
}

byte RobinScript::OC_sub17825() {
	debugC(1, kDebugScript, "OC_sub17825()");

	byte tmpVal = (_currScript->readUint16LE() & 0xFF);
	
	if ((_vm->_byte16F07_menuId != 1) && (_vm->_byte16F07_menuId != 3))
		return 0;

	if (tmpVal == _byte12FE4)
		return 1;

	return 0;
}

byte RobinScript::OC_sub17844() {
	debugC(1, kDebugScript, "OC_sub17844()");

	int tmpVal = _currScript->readUint16LE();

	if ((_vm->_byte16F07_menuId == 2) || ((tmpVal & 0xFF) != _byte12FE4))
		return 0;

	return 1;
}

byte RobinScript::OC_sub1785C() {
	debugC(1, kDebugScript, "OC_sub1785C()");

	byte curByte = (_currScript->readUint16LE() & 0xFF);
	int count = 0;

	for (int i = 0; i < _vm->_word10807_ERULES; i++) {
		if (curByte == _vm->_rulesBuffer2_15[(32 * i)])
			++count;
	}

	int oper = _currScript->readUint16LE();
	int var2 = _currScript->readUint16LE();

	return compareValues(count, oper, var2);
}

byte RobinScript::OC_sub17886() {
	warning("OC_sub17886");
	return 0;
}
byte RobinScript::OC_sub178A8() {
	warning("OC_sub178A8");
	return 0;
}
byte RobinScript::OC_sub178BA() {
	warning("OC_sub178BA");
	return 0;
}
byte RobinScript::OC_sub178C2() {
	debugC(1, kDebugScript, "OC_sub178C2()");

	assert(_vm->_ptr_rulesBuffer2_15 != NULL);
	if (_vm->_ptr_rulesBuffer2_15[2] == 1)
		return 1;
	return 0;
}
byte RobinScript::OC_sub178D2() {
	warning("OC_sub178D2");
	return 0;
}
byte RobinScript::OC_sub178E8() {
	warning("OC_sub178E8");
	return 0;
}

byte RobinScript::OC_sub178FC() {
	debugC(1, kDebugScript, "OC_sub178FC()");

	assert(_vm->_ptr_rulesBuffer2_15 != NULL);
	byte curByte = (_currScript->readUint16LE() & 0xFF);

	if (curByte <= _vm->_ptr_rulesBuffer2_15[0])
		return 1;
	return 0;
}

byte RobinScript::OC_sub1790F() {
	debugC(1, kDebugScript, "OC_sub1790F()");

	int index = getValue1();
	assert(index < 40);
	if (_vm->_rulesBuffer2_5[index] == 0xFF)
		return 0;

	_word16F00 = _vm->_rulesBuffer2_5[index];

	return 1;
}

byte RobinScript::OC_sub1792A() {
	debugC(1, kDebugScript, "OC_sub1792A()");

	assert(_vm->_ptr_rulesBuffer2_15 != NULL);
	byte curByte = (_currScript->readUint16LE() & 0xFF);

	if (_vm->_ptr_rulesBuffer2_15[1] == curByte)
		return 1;

	return 0;
}

byte RobinScript::OC_sub1793E() {
	debugC(1, kDebugScript, "OC_sub1793E()");

	if (_vm->_word16EFA == 0xFFFF)
		return 0;

	if (_vm->_array16E94[_vm->_rulesBuffer2PrevIndx] == 0)
		return 0;

	return 1;
}

byte RobinScript::OC_sub1795E() {
	debugC(1, kDebugScript, "OC_sub1795E()");

	assert(_vm->_ptr_rulesBuffer2_15 != NULL);
	if (_vm->_ptr_rulesBuffer2_15[3] == 1)
		return 1;

	return 0;
}

byte RobinScript::OC_sub1796E() {
	warning("OC_sub1796E");
	return 0;
}
byte RobinScript::OC_sub17984() {
	debugC(1, kDebugScript, "OC_sub17984()");

	int index = _currScript->readUint16LE();
	int var2 = _currScript->readUint16LE();

	assert(index < 20);

	if (_array122E9[index] == (var2 & 0xFF))
		return 1;

	return 0;
}

byte RobinScript::OC_checkSavedMousePos() {
	debugC(1, kDebugScript, "OC_checkSavedMousePos()");

	if ((_byte129A0 != 0xFF) || (_vm->_savedMousePosDivided == 0xFFFF))
		return 0;

	return 1;
}

byte RobinScript::OC_sub179AE() {
	debugC(1, kDebugScript, "OC_sub179AE()");

	if ((_vm->_byte12FCE == 1) || (_byte129A0 == 0xFF))
		return 0;

	return 1;
}

byte RobinScript::OC_sub179C2() {
	warning("OC_sub179C2");
	return 0;
}
byte RobinScript::OC_sub179E5() {
	warning("OC_sub179E5");
	return 0;
}

byte RobinScript::OC_sub17A07() {
	debugC(1, kDebugScript, "OC_sub17A07()");

	static const byte _array179FD[10] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	if (_vm->_byte16F07_menuId == 6) {
		int index = _currScript->readUint16LE();
		if (_array179FD[index] == _vm->_array147D1[0]) {
			index = _currScript->readUint16LE();
			if (_array179FD[index] == _vm->_array147D1[1]) {
				index = _currScript->readUint16LE();
				if (_array179FD[index] == _vm->_array147D1[2]) {
					return 1;
				}
			}
		}
	}
	
	_currScript->seek(_currScript->pos() + 6);
	return 0;
}

byte RobinScript::OC_sub17757() {
	warning("OC_sub17757");
	return 0;
}

void RobinScript::OC_setWord18821() {
	warning("OC_setWord18821");
}
void RobinScript::OC_sub17A3E() {
	warning("OC_sub17A3E");
}

void RobinScript::OC_sub17D57() {
	debugC(1, kDebugScript, "OC_sub17D57()");

	int curWord = _currScript->readUint16LE();

	if((displayMap == 1) || (_array16173[_vm->_rulesBuffer2PrevIndx] == 0xFF))
		return;

	_word1881B = _vm->_rulesBuffer2PrevIndx;
	sub18B3C(curWord);

}

void RobinScript::OC_sub17D7F() {
	warning("OC_sub17D7F");
}
void RobinScript::OC_sub17DB9() {
	warning("OC_sub17DB9");
}

void RobinScript::OC_sub17DF9() {
	debugC(1, kDebugScript, "OC_sub17DF9()");

	if ((_word1881B & 0xFF) == 0xFF) {
		OC_sub17D57();
		return;
	}

	_currScript->readUint16LE();
}

void RobinScript::OC_sub17E07() {
	warning("OC_sub17E07");
}
void RobinScript::OC_sub17E15() {
	warning("OC_sub17E15");
}

void RobinScript::OC_sub17B03() {
	debugC(1, kDebugScript, "OC_sub17B03()");

	byte *bufPtr = getBuffer215Ptr();
	int oper = _currScript->readUint16LE();
	int var2 = _currScript->readUint16LE();

	computeOperation(bufPtr, oper, var2);
}

void RobinScript::OC_getRandom_type2() {
	warning("OC_getRandom_type2");
}

void RobinScript::OC_sub17A66() {
	debugC(1, kDebugScript, "OC_sub17A66()");
	
	int index = getValue1();
	int tmpVal = getValue2();

	int var2 = ((tmpVal >> 8) << 3) + 4;
	int var4 = ((tmpVal & 0xFF) << 3) + 4;

	assert(index < 40);
	_vm->_characterPositionX[index] = var2;
	_vm->_characterPositionY[index] = var4;
}

void RobinScript::OC_sub17A8D() {
	debugC(1, kDebugScript, "OC_sub17A8D()");

	int tmpVal = getValue1();
	assert(tmpVal < 40);

	if (tmpVal == _word10804)
		_viewportCharacterTarget = 0xFFFF;

	_vm->_characterPositionX[tmpVal] = 0xFFFF;
	_vm->_characterPositionY[tmpVal] = 0xFFFF;
}
void RobinScript::OC_saveAndQuit() {
	warning("OC_saveAndQuit");
}
void RobinScript::OC_sub17B93() {
	debugC(1, kDebugScript, "OC_sub17B93()");
	int var1 = _currScript->readUint16LE();

	sub17B6C(var1);
}

void RobinScript::OC_sub17E37() {
	warning("OC_sub17E37");
}
void RobinScript::OC_resetByte1714E() {
	warning("OC_resetByte1714E");
}
void RobinScript::OC_deleteSavegameAndQuit() {
	warning("OC_deleteSavegameAndQuit");
}
void RobinScript::OC_incByte16F04() {
	warning("OC_incByte16F04");
}

void RobinScript::OC_sub17BA5() {
	debugC(1, kDebugScript, "OC_sub17BA5()");
	
	byte *tmpArr = getBuffer215Ptr();
	byte oper = (_currScript->readUint16LE() & 0xFF);
	byte var2 = getBuffer215Ptr()[0];
	computeOperation(tmpArr, oper, var2);
}

void RobinScript::OC_setByte18823() {
	warning("OC_setByte18823");
}
void RobinScript::OC_sub17BB7() {
	debugC(1, kDebugScript, "OC_sub17BB7()");

	int index = _currScript->readUint16LE();
	int var1 = getValue1();

	_vm->sub170EE(var1);
	int tmpIndex = _vm->_rulesBuffer2PrevIndx;

	assert(index < _vm->_gameScriptIndexSize);
	int scriptIndex = _vm->_arrayGameScriptIndex[index];

	_scriptStack.push(_currScript);

	if (_byte16F05_ScriptHandler == 0) {
		_vm->_byte1714E = 0;
		runMenuScript(Common::MemoryReadStream(&_vm->_arrayGameScripts[scriptIndex], _vm->_arrayGameScriptIndex[index + 1] - _vm->_arrayGameScriptIndex[index]));
	} else {
		runScript(Common::MemoryReadStream(&_vm->_arrayGameScripts[scriptIndex], _vm->_arrayGameScriptIndex[index + 1] - _vm->_arrayGameScriptIndex[index]));
	}

	_currScript = _scriptStack.pop();

	_vm->sub170EE(tmpIndex);
}

void RobinScript::OC_sub17BF2() {
	debugC(1, kDebugScript, "OC_sub17BF2()");

	OC_sub17BB7();
	sub17B6C(0);
}

void RobinScript::OC_sub17ACC() {
	warning("OC_sub17ACC");
}
void RobinScript::OC_resetByte16F04() {
	warning("OC_resetByte16F04");
}

void RobinScript::OC_sub17AE1() {
	debugC(1, kDebugScript, "OC_sub17AE1()");

	byte var3 = (_currScript->readUint16LE() & 0xFF);
	sub16C5C(_vm->_rulesBuffer2PrevIndx, var3);
}

void RobinScript::OC_sub17AEE() {
	debugC(1, kDebugScript, "OC_sub17AEE()");

	byte var3 = (_currScript->readUint16LE() & 0xFF);
	sub16C5C(_vm->_rulesBuffer2PrevIndx + 1, var3);
}

void RobinScript::OC_setWord10804() {
	debugC(1, kDebugScript, "OC_setWord10804()");

	_word10804 = getValue1();
}
void RobinScript::OC_sub17C0E() {
	warning("OC_sub17C0E");
}
void RobinScript::OC_sub17C55() {
	warning("OC_sub17C55");
}
void RobinScript::OC_sub17C76() {
	warning("OC_sub17C76");
}
void RobinScript::OC_sub17AFC() {
	warning("OC_sub17AFC");
}
void RobinScript::OC_sub17C8B() {
	warning("OC_sub17C8B");
}
void RobinScript::OC_sub17CA2() {
	warning("OC_sub17CA2");
}
void RobinScript::OC_sub17CB9() {
	warning("OC_sub17CB9");
}
void RobinScript::OC_sub17CD1() {
	warning("OC_sub17CD1");
}
void RobinScript::OC_resetWord16EFE() {
	warning("OC_resetWord16EFE");
}
void RobinScript::OC_sub17CEF() {
	debugC(1, kDebugScript, "OC_sub17CEF()");

	int var1 = _currScript->readUint16LE();
	sub1823E(_vm->_rulesBuffer2PrevIndx , var1, _vm->_ptr_rulesBuffer2_15);
	sub17B6C(0);
}

void RobinScript::OC_sub17D1B() {
	debugC(1, kDebugScript, "OC_sub17D1B()");

	assert(_vm->_ptr_rulesBuffer2_15 != NULL);
	++_vm->_ptr_rulesBuffer2_15[1];
}

void RobinScript::OC_sub17D23() {
	warning("OC_sub17D23");
}
void RobinScript::OC_sub17E6D() {
	warning("OC_sub17E6D");
}
void RobinScript::OC_sub17E7E() {
	warning("OC_sub17E7E");
}
void RobinScript::OC_sub17E99() {
	warning("OC_sub17E99");
}
void RobinScript::OC_sub17EC5() {
	warning("OC_sub17EC5");
}
void RobinScript::OC_sub17EF4() {
	warning("OC_sub17EF4");
}
void RobinScript::OC_sub17F08() {
	warning("OC_sub17F08");
}
void RobinScript::OC_sub17F4F() {
	warning("OC_sub17F4F");
}
void RobinScript::OC_sub17F68() {
	warning("OC_sub17F68");
}
void RobinScript::OC_getNextVal() {
	warning("OC_getNextVal");
}
void RobinScript::OC_sub17FD2() {
	warning("OC_sub17FD2");
}

void RobinScript::OC_sub17FDD() {
	debugC(1, kDebugScript, "OC_sub17FDD()");

	int index = _currScript->readUint16LE();
	
	int tmpVal = (_vm->_rulesBuffer2PrevIndx * 32) + index;
	assert (tmpVal < 40 * 32);
	_array10AB1[_vm->_rulesBuffer2PrevIndx] = _vm->_rulesBuffer2_16[tmpVal];
	_array12811[_vm->_rulesBuffer2PrevIndx] = 16;
}

void RobinScript::OC_setByte10B29() {
	warning("OC_setByte10B29");
}

void RobinScript::OC_sub18007() {
	debugC(1, kDebugScript, "OC_sub18007()");

	int curWord = _currScript->readUint16LE();
	assert(_vm->_ptr_rulesBuffer2_15 != NULL);
	_vm->_ptr_rulesBuffer2_15[2] = curWord & 0xFF;
}

void RobinScript::OC_sub18014() {
	debugC(1, kDebugScript, "OC_sub18014()");

	assert(_vm->_ptr_rulesBuffer2_15 != NULL);
	_vm->_ptr_rulesBuffer2_15[2] = 0;
}

void RobinScript::OC_sub1801D() {
	warning("OC_sub1801D");
}
void RobinScript::OC_sub1805D() {
	warning("OC_sub1805D");
}
void RobinScript::OC_sub18074() {
	warning("OC_sub18074");
}
void RobinScript::OC_sub1808B() {
	warning("OC_sub1808B");
}
void RobinScript::OC_sub18099() {
	debugC(1, kDebugScript, "OC_sub18099()");

	int index = _currScript->readUint16LE();
	assert((index >= 0) && (index < 20));
	int curWord = _currScript->readUint16LE();

	_array122E9[index] = (curWord & 0xFF);
	_array122FD[index] = (curWord >> 8);

	_vm->displayFunction8();
}
void RobinScript::OC_sub180C3() {
	warning("OC_sub180C3");
}
void RobinScript::OC_sub1810A() {
	warning("OC_sub1810A");
}

void RobinScript::OC_sub1812D() {
	debugC(1, kDebugScript, "OC_sub1812D()");

	_vm->_rulesBuffer2_3[_vm->_rulesBuffer2PrevIndx] = (_currScript->readUint16LE() & 0xFF);
}

void RobinScript::OC_sub1817F() {
	debugC(1, kDebugScript, "OC_sub1817F()");

	int var1 = _currScript->readUint16LE();
	int var2 = _currScript->readUint16LE();
	
	int b1 = var1 & 0xFF;
	int b2 = var2 & 0xFF;
	OC_sub1817F_loop(b1,b2);
}

void RobinScript::OC_sub1817F_loop( int b1, int b2 ) {
	for (int i = 0; i <  _vm->_word1817B; i++) {
		if ((_array1813B[i] >> 8) == b2 ) {
			b2 += _array1813B[i] & 0xFF;
			if (b2 < 0) {
				b2 = 0xFF;
			}
			_array1813B[i] = (_array1813B[i] & 0xFF00) + b2;
			return;
		}
	}

	_array1813B[_vm->_word1817B++] = (b1 << 8) + b2;
}

void RobinScript::OC_sub181BB() {
	debugC(1, kDebugScript, "OC_sub1817F()");
	
	int b = _currScript->readUint16LE();
	int d = _currScript->readUint16LE() & 0xFF;
	int s = _currScript->readUint16LE();
	int c = _vm->_ptr_rulesBuffer2_15[s];
	int c2 = 0;

	if ( d == 0x2D ) {
		c = - 1 - c;
	} else if ( d == 0x3E ) {
		c = c - 0x80;
		if ( c < 0 ) 
			c = 0;
		c = c * 2;
	} else if ( d == 0x3C ) {
		c = -1 - c;
		c = c - 0x80;
		if ( c < 0 )
			c = 0;
		c = c * 2;
	}

	int a = _currScript->readUint16LE() * c + (c & 0xFF);
	b = b & 0xFF00 + a;
	OC_sub1817F_loop(b & 0xFF, b >> 8);

}
void RobinScript::OC_sub18213() {
	debugC(1, kDebugScript, "OC_sub18213()");

	int var1 = _currScript->readUint16LE();

	int maxValue = 0;
	int maxItem = var1 & 0xFF;

	for (int i = 0; i < _vm->_word1817B; i++) {
		if ( _array1813B[i] & 0xFF > maxValue ) {
			maxValue = _array1813B[i] & 0xFF;
			maxItem = _array1813B[i] >> 8;
		}
	}
	sub1823E(_vm->_rulesBuffer2PrevIndx, maxItem, &_vm->_rulesBuffer2_15[var1]);
}
void RobinScript::OC_sub18252() {
	warning("OC_sub18252");
}
void RobinScript::OC_sub18260() {
	warning("OC_sub18260");
}
void RobinScript::OC_sub182EC() {
	warning("OC_sub182EC");
}

void RobinScript::OC_PaletteFadeOut() {
	sub1863B();
	byte palette[768];
	for (int fade = 256; fade >= 0;	fade -= 8) {
		for (int i = 0; i < 768; i++) {
			palette[i] = (_vm->_curPalette[i] * fade) >> 8;
		}
		_vm->_system->getPaletteManager()->setPalette(palette, 0, 256);
		_vm->_system->updateScreen();
		_vm->_system->delayMillis(20);
	}
}

void RobinScript::OC_PaletteFadeIn() {

	byte palette[768];
	for (int fade = 8; fade <= 256;	fade += 8) {
		for (int i = 0; i < 768; i++) {
			palette[i] = (_vm->_curPalette[i] * fade) >> 8;
		}
		_vm->_system->getPaletteManager()->setPalette(palette, 0, 256);
		_vm->_system->updateScreen();
		_vm->_system->delayMillis(20);
	}
}

void RobinScript::OC_loadAndDisplayCUBESx_GFX() {
	debugC(1, kDebugScript, "OC_loadAndDisplayCUBESx_GFX()");

	int curWord = _currScript->readUint16LE();
	assert((curWord >= 0) && (curWord <= 9));
	Common::String fileName = Common::String::format("CUBES%d.GFX", curWord);
	_byte10806 = curWord + 0x30;

	_vm->_bufferCubegfx = _vm->loadVGA(fileName, false);
	_vm->displayFunction9();
	_vm->displayFunction15();

}

void RobinScript::OC_sub1834C() {
	debugC(1, kDebugScript, "OC_sub1834C()");

	byte curWord = _currScript->readUint16LE() & 0xFF;
	assert(_vm->_ptr_rulesBuffer2_15 != NULL);

	_vm->_ptr_rulesBuffer2_15[3] = curWord;
}

void RobinScript::OC_sub18359() {
	debugC(1, kDebugScript, "OC_sub18359()");

	int var1 = _currScript->readUint16LE();
	_array122C1[_vm->_rulesBuffer2PrevIndx] = var1;
}
void RobinScript::OC_sub18367() {
	warning("OC_sub18367");
}

void RobinScript::OC_sub17D04() {
	debugC(1, kDebugScript, "OC_sub17D04()");

	byte var1 = getValue1();
	byte var2 = _currScript->readUint16LE() & 0xFF;
	
	sub1823E(var1, var2, &_vm->_rulesBuffer2_15[var1]);
}

void RobinScript::OC_sub18387() {
	warning("OC_sub18387");
}
void RobinScript::OC_setByte14835() {
	warning("OC_setByte14835");
}
void RobinScript::OC_setByte14837() {
	warning("OC_setByte14837");
}
void RobinScript::OC_sub183A2() {
	warning("OC_sub183A2");
}
void RobinScript::OC_sub183C6() {
	warning("OC_sub183C6");
}
void RobinScript::OC_loadFile_AERIAL_GFX() {
	debugC(1, kDebugScript, "OC_loadFile_AERIAL_GFX()");
	
	int var1 = _currScript->readUint16LE() & 0xff;
	_vm->_byte15EAD = var1;

	_byte12A09 = 1;
	_word1881B = 0xFFFF;
	OC_PaletteFadeOut();
	_vm->_word15AC2 = 1;
	_vm->displayVGAFile("AERIAL.GFX");
	OC_PaletteFadeIn();

	_vm->displayCharactersOnMap();
	_vm->_byte16F08 = 1;
	_vm->_keyboard_oldIndex = 0;
	_vm->_keyboard_nextIndex = 0;

	_vm->_byte12A09 = 0;
}

void RobinScript::OC_sub17E22() {
	warning("OC_sub17E22");
}
void RobinScript::OC_sub1844A() {
	warning("OC_sub1844A");
}

void RobinScript::OC_sub1847F() {
	debugC(1, kDebugScript, "OC_sub1847F()");

	byte *buf215Ptr = getBuffer215Ptr();
	byte tmpVal = buf215Ptr[0];
	int curWord = _currScript->readUint16LE();
	assert(curWord != 0);
	int var1 = tmpVal / (curWord & 0xFF);
	int var2 = _currScript->readUint16LE();
	int var4 = _currScript->readUint16LE();

	if (displayMap != 1) {
		_vm->displayFunction5();
		sub18BE6(var1 & 0xFF, var2, var4);
		_vm->displayFunction4();
	}
}

void RobinScript::sub18BE6(byte var1, int var2, int var4) {
	debugC(1, kDebugScript, "sub18BE6(%d, %d, %d)", var1, var2, var4);

	_vm->_displayStringIndex = 0;
	_vm->_displayStringBuf[0] = 32;
	_vm->_displayStringBuf[1] = 32;
	_vm->_displayStringBuf[2] = 32;
	_vm->_displayStringBuf[3] = 0;

	_vm->prepareGoldAmount(var1);
	_vm->displayString(_vm->_displayStringBuf, var2, var4);
}

void RobinScript::OC_displayVGAFile() {
	debugC(1, kDebugScript, "OC_displayVGAFile()");

	_byte12A09 = 1;
	OC_PaletteFadeOut();
	int curWord = _currScript->readUint16LE();
	int index = _vm->_rulesChunk3[curWord];
	Common::String fileName = Common::String((const char *)&_vm->_rulesChunk4[index]);
	_word1881B = -1;
	_vm->displayVGAFile(fileName);
	OC_PaletteFadeIn();
}

void RobinScript::OC_sub184D7() {
	warning("OC_sub184D7");
}

void RobinScript::OC_displayTitleScreen() {
	debugC(1, kDebugScript, "OC_displayTitleScreen()");

	_vm->_byte184F4 = (_currScript->readUint16LE() & 0xFF);
	_vm->_sound_byte16F06 = _vm->_byte184F4;

	// TODO: Rewrite keyboard handling (this code was in a separated function)
	_vm->_keyboard_nextIndex = 0;
	_vm->_keyboard_oldIndex = 0;
	//
	_vm->_mouseButton = 0;
	_vm->_byte16F09 = 0;

	for (;;) {
		sub185B4_display();
		_vm->update();
		if (_vm->_keyboard_nextIndex != _vm->_keyboard_oldIndex) {
			_vm->_byte16F09 = _vm->_keyboard_getch();
			_vm->_keyboard_getch();
			break;
		}
		
		if (_vm->_mouseButton & 1)
			break;
		
		if ((_vm->_byte184F4 != 0) && (_vm->_sound_byte16F06 == 0))
			break;
	}
	
	_vm->_mouseButton = 0;
}

void RobinScript::OC_sub1853B() {
	debugC(1, kDebugScript, "OC_sub1853B()");

	OC_PaletteFadeOut();
	displayMap = 0;
	_heroismLevel = 0;
	sub130B6();

	_vm->displayFunction12();

	OC_PaletteFadeIn();
	_byte12A09 = 0;
	
	_vm->_soundHandler->contentFct5();
}

void RobinScript::OC_sub1864D() {
	warning("OC_sub1864D");
}

void RobinScript::OC_initArr18560() {
	debugC(1, kDebugScript, "OC_initArr18560()");

	int curWord = _currScript->readUint16LE();
	assert (curWord < 4);
	_vm->_arr18560[curWord]._field0 = 1;
	_vm->_arr18560[curWord]._field1 = _currScript->readUint16LE();
	_vm->_arr18560[curWord]._field3 = _currScript->readUint16LE();

	for (int i = 0; i < 8; i++)
		_vm->_arr18560[curWord]._field5[i] = _currScript->readUint16LE();
}

void RobinScript::OC_sub18678() {
	debugC(1, kDebugScript, "OC_initArr18578()");
	_savedBuffer215Ptr = getBuffer215Ptr();
	_heroismBarX = _currScript->readUint16LE();
	_heroismBarBottomY = _currScript->readUint16LE();
}

void RobinScript::OC_sub18690() {
	warning("OC_sub18690");
}

void RobinScript::OC_setWord10802() {
	debugC(1, kDebugScript, "OC_setWord10802()");

	_viewportCharacterTarget = getValue1();
}

void RobinScript::OC_sub186A1() {
	warning("OC_sub186A1");
}

void RobinScript::OC_sub186E5_snd() {
	debugC(1, kDebugScript, "OC_sub186E5_snd()");
	int index = getValue1();
	assert(index < 40);

	byte var4h = 0xFF;
	byte var4l = (index & 0xFF);
	byte var3h = _array16123[index];
	byte var3l = _array1614B[index];
	byte var2h = (_viewportX & 0xFF);
	byte var2l = (_viewportY & 0xFF);
	int var1 = _currScript->readUint16LE();

	_vm->_soundHandler->contentFct2();
}

void RobinScript::OC_sub1870A_snd() {
	debugC(1, kDebugScript, "OC_sub1870A_snd()");

	int var3 = getValue2();
	int var4 = var3;
	int var2 = (_viewportX << 8) + _viewportY;
	int var1 = (_currScript->readUint16LE() & 0xFF);

	_vm->_soundHandler->contentFct2();
}

void RobinScript::OC_sub18725_snd() {
	debugC(1, kDebugScript, "OC_sub18725_snd()");

	int var4 = getValue1() | 0xFF00;

	_vm->_soundHandler->contentFct3();
}

void RobinScript::OC_sub18733_snd() {
	debugC(1, kDebugScript, "OC_sub18733_snd()");

	int var4 = getValue2();

	_vm->_soundHandler->contentFct3();
}

void RobinScript::OC_sub1873F_snd() {
	debugC(1, kDebugScript, "OC_sub1873F_snd()");

	_vm->_soundHandler->contentFct4();
}

void RobinScript::OC_sub18746_snd() {
	debugC(1, kDebugScript, "OC_sub18746_snd()");

	int var4 = -1;
	int var2 = (_viewportX << 8) + _viewportY;
	int var1 = _currScript->readUint16LE() & 0xFF;

	_vm->_soundHandler->contentFct2();
}

void RobinScript::OC_sub1875D_snd() {
	debugC(1, kDebugScript, "OC_sub1875D_snd()");

	_vm->_soundHandler->contentFct6();
}

void RobinScript::OC_sub18764() {
	debugC(1, kDebugScript, "OC_sub18764()");

	int index = getValue1();
	int var1 = _currScript->readUint16LE();

	assert(index < 40);
	_array128EF[index] = var1 & 0xFF;
}

} // End of namespace
