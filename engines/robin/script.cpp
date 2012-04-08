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

namespace Robin {

RobinScript::RobinScript(RobinEngine *vm) : _vm(vm), _currScript(NULL) {
	_byte129A0 = 0xFF;
	_byte16F08 = 0;

	_word16F00 = -1;
	_word10802 = -1;
	_word10804 = 0;
	_word15FFB = 0;
	_word15FFD = 0;

	_savedBuffer215Ptr = NULL;

	for (int i = 0; i < 20; i++) {
		_array122E9[i] = 0;
		_array122FD[i] = 0;
	}

	for (int i = 0; i < 40; i++) {
		_array10B29[i] = 1;
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
		OC_unkPaletteFunction_1();
		break;
	case 0x44:
		OC_unkPaletteFunction_2();
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
		OC_sub184F5();
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
		return -1;

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
		;
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
			byte tmpVal = bufPtr[0] / var2;
			if (tmpVal < 0)
				bufPtr[0] = 0xFF;
			else 
				bufPtr[0] = 0;
		}
		break;
		}
	}
}

void RobinScript::sub1823E(byte var1, byte var2, byte *curBufPtr) {
	debugC(1, kDebugScript, "sub1823E(%d, %d, curBufPtr)", var1, var2);

	assert ((var1 >= 0) && (var1 < 40));
	_array10B29[var1] = 0;
	curBufPtr[0] = var2;
	curBufPtr[1] = 0;
	curBufPtr[2] = 0;
	curBufPtr[3] = 0;
}

int RobinScript::getValue1() {
	debugC(1, kDebugScript, "getValue1()");
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
	debugC(1, kDebugScript, "getValue2()");
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
	case 0xFC:
		warning("TODO: getValue2 - 0xFC");
		return 0;
	case 0xFB:
		warning("TODO: getValue2 - 0xFB");
		return 0;
	case 0xFA:
		return ((_vm->_byte10999[_vm->_rulesBuffer2PrevIndx] << 8) + _vm->_byte109C1[_vm->_rulesBuffer2PrevIndx]);
	case 0xF9:
		return ((_vm->_rulesBuffer2_15[4] << 8) + _vm->_rulesBuffer2_15[5]);
	case 0xF8: {
		int index = curWord & 0xFF;
		assert((index >= 0) && (index < 40));
		return _vm->_rulesBuffer12_3[index];
		}
	case 0xF7:
		warning("TODO: getValue2 - 0xF7");
		return 0;
	case 0xF6:
		return _vm->_mouse_savedMousePosDivided;
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
	warning("OC_getRandom");
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
	warning("OC_sub174D8");
	return 0;
}
byte RobinScript::OC_sub1750E() {
	warning("OC_sub1750E");
	return 0;
}
byte RobinScript::OC_compareCoords_1() {
	warning("compareCoords_1");
	return 0;
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
	warning("OC_compWord16EF8");
	return 0;
}
byte RobinScript::OC_sub175C8() {
	warning("OC_sub175C8");
	return 0;
}
byte RobinScript::OC_sub17640() {
	warning("OC_sub17640");
	return 0;
}
byte RobinScript::OC_sub176C4() {
	warning("OC_sub176C4");
	return 0;
}
byte RobinScript::OC_compWord10804() {
	warning("OC_compWord10804");
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
	warning("OC_sub177C6");
	return 0;
}
byte RobinScript::OC_compWord16EFE() {
	warning("OC_compWord16EFE");
	return 0;
}
byte RobinScript::OC_sub177F5() {
	warning("OC_sub177F5");
	return 0;
}
byte RobinScript::OC_sub17812() {
	warning("OC_sub17812");
	return 0;
}
byte RobinScript::OC_sub17825() {
	warning("OC_sub17825");
	return 0;
}
byte RobinScript::OC_sub17844() {
	warning("OC_sub17844");
	return 0;
}
byte RobinScript::OC_sub1785C() {
	warning("OC_sub1785C");
	return 0;
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
	warning("OC_sub178C2");
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
	warning("OC_sub178FC");
	return 0;
}
byte RobinScript::OC_sub1790F() {
	warning("OC_sub1790F");
	return 0;
}
byte RobinScript::OC_sub1792A() {
	warning("OC_sub1792A");
	return 0;
}
byte RobinScript::OC_sub1793E() {
	warning("OC_sub1793E");
	return 0;
}
byte RobinScript::OC_sub1795E() {
	warning("OC_sub1795E");
	return 0;
}
byte RobinScript::OC_sub1796E() {
	warning("OC_sub1796E");
	return 0;
}
byte RobinScript::OC_sub17984() {
	warning("OC_sub17984");
	return 0;
}
byte RobinScript::OC_checkSavedMousePos() {
	warning("OC_checkSavedMousePos");
	return 0;
}
byte RobinScript::OC_sub179AE() {
	warning("OC_sub179AE");
	return 0;
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
	warning("OC_sub17A07");
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
	warning("OC_sub17D57");
}
void RobinScript::OC_sub17D7F() {
	warning("OC_sub17D7F");
}
void RobinScript::OC_sub17DB9() {
	warning("OC_sub17DB9");
}
void RobinScript::OC_sub17DF9() {
	warning("OC_sub17DF9");
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
	warning("OC_sub17A66");
}
void RobinScript::OC_sub17A8D() {
	warning("OC_sub17A8D");
}
void RobinScript::OC_saveAndQuit() {
	warning("OC_saveAndQuit");
}
void RobinScript::OC_sub17B93() {
	warning("OC_sub17B93");
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
	warning("OC_sub17BA5");
}
void RobinScript::OC_setByte18823() {
	warning("OC_setByte18823");
}
void RobinScript::OC_sub17BB7() {
	warning("OC_sub17BB7");
}
void RobinScript::OC_sub17BF2() {
	warning("OC_sub17BF2");
}
void RobinScript::OC_sub17ACC() {
	warning("OC_sub17ACC");
}
void RobinScript::OC_resetByte16F04() {
	warning("OC_resetByte16F04");
}
void RobinScript::OC_sub17AE1() {
	warning("OC_sub17AE1");
}
void RobinScript::OC_sub17AEE() {
	warning("OC_sub17AEE");
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
	warning("OC_sub17CEF");
}
void RobinScript::OC_sub17D1B() {
	warning("OC_sub17D1B");
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
	warning("OC_sub17FDD");
}
void RobinScript::OC_setByte10B29() {
	warning("OC_setByte10B29");
}
void RobinScript::OC_sub18007() {
	warning("OC_sub18007");
}
void RobinScript::OC_sub18014() {
	warning("OC_sub18014");
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

	warning("TODO: display function #8");
	
}
void RobinScript::OC_sub180C3() {
	warning("OC_sub180C3");
}
void RobinScript::OC_sub1810A() {
	warning("OC_sub1810A");
}
void RobinScript::OC_sub1812D() {
	warning("OC_sub1812D");
}
void RobinScript::OC_sub1817F() {
	warning("OC_sub1817F");
}
void RobinScript::OC_sub181BB() {
	warning("OC_sub181BB");
}
void RobinScript::OC_sub18213() {
	warning("OC_sub18213");
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
void RobinScript::OC_unkPaletteFunction_1() {
	warning("OC_unkPaletteFunction_1");
}
void RobinScript::OC_unkPaletteFunction_2() {
	warning("OC_unkPaletteFunction_2");
}

void RobinScript::OC_loadAndDisplayCUBESx_GFX() {
	debugC(1, kDebugScript, "OC_loadAndDisplayCUBESx_GFX()");

	int curWord = _currScript->readUint16LE();
	assert((curWord >= 0) && (curWord <= 9));
	Common::String fileName = Common::String::format("CUBES%d.GFX", curWord);
	warning("TODO: load %s then display things", fileName.c_str());
}

void RobinScript::OC_sub1834C() {
	warning("OC_sub1834C");
}
void RobinScript::OC_sub18359() {
	warning("OC_sub18359");
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
	warning("OC_loadFile_AERIAL_GFX");
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
	int var1 = tmpVal / curWord;
	int var2 = _currScript->readUint16LE();
	int var3 = _currScript->readUint16LE();

	if (_byte16F08 != 1) {
		warning("TODO: OC_sub1847F - Display Function 5");
		warning("TODO: OC_sub1847F - sub_18BE6");
		warning("TODO: OC_sub1847F - Display Function 4");
	}

}
void RobinScript::OC_displayVGAFile() {
	debugC(1, kDebugScript, "OC_displayVGAFile()");

	_byte12A09 = 1;
	warning("TODO: unkPaletteFunction_1");
	int curWord = _currScript->readUint16LE();
	int index = _vm->_rulesChunk3[curWord];
	Common::String fileName = Common::String((const char *)&_vm->_rulesChunk4[index]);
	_word1881B = -1;
	warning("TODO: guess_displayFunction_VGAFile(%s)", fileName.c_str());
	warning("TODO: unkPaletteFunction_2");
}
void RobinScript::OC_sub184D7() {
	warning("OC_sub184D7");
}
void RobinScript::OC_sub184F5() {
	debugC(1, kDebugScript, "OC_sub184F5()");

	_vm->_byte184F4 = (_currScript->readUint16LE() & 0xFF);
	_vm->_sound_byte16F06 = _vm->_byte184F4;
	// TODO: use a separated function when properly identified
	_vm->_word12D3D = 0;
	_vm->_word12D3F = 0;
	//
	_vm->_mouse_byte1299A = 0;
	_vm->_byte16F09 = 0;

	// TODO: Remove when the sound is hooked
	_vm->_sound_byte16F06 = 0;
	//

	for (;;) {
		warning("TODO: display function sub_185B4();");

		if (_vm->_keyboard_nextIndex != _vm->_keyboard_oldIndex) {
			_vm->_byte16F09 = _vm->_keyboard_getch();
			_vm->_keyboard_getch();
			break;
		}
		
		if (_vm->_mouse_byte1299A == 1)
			break;
		
		if ((_vm->_byte184F4 != 0) && (_vm->_sound_byte16F06 == 0))
			break;
	}
	
	_vm->_mouse_byte1299A = 0;
}

void RobinScript::OC_sub1853B() {
	debugC(1, kDebugScript, "OC_initArr1853B()");

	warning("TODO: unkPaletteFunction_1");
	_byte16F08 = 0;
	_byte15FFA = 0;
	sub130B6();
	warning("TODO: Display function sub15CBC();");
	warning("TODO: unkPaletteFunction_2");
	_byte12A09 = 0;
	warning("TODO: call sound function #5");
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
	_word15FFB = _currScript->readUint16LE();
	_word15FFD = _currScript->readUint16LE();
}
void RobinScript::OC_sub18690() {
	warning("OC_sub18690");
}
void RobinScript::OC_setWord10802() {
	debugC(1, kDebugScript, "OC_setWord10802()");

	_word10802 = getValue1();
}
void RobinScript::OC_sub186A1() {
	warning("OC_sub186A1");
}
void RobinScript::OC_sub186E5_snd() {
	warning("OC_sub186E5_snd");
}

void RobinScript::OC_sub1870A_snd() {
	debugC(1, kDebugScript, "OC_sub1870A_snd()");

	int var3 = getValue2();
	// TODO: int var2 = ...
	int var1 = (_currScript->readUint16LE() & 0xFF);
	warning("TODO: call sound function #2");
}

void RobinScript::OC_sub18725_snd() {
	warning("OC_sub18725_snd");
}
void RobinScript::OC_sub18733_snd() {
	warning("OC_sub18733_snd");
}
void RobinScript::OC_sub1873F_snd() {
	warning("OC_sub1873F_snd");
}
void RobinScript::OC_sub18746_snd() {
	debugC(1, kDebugScript, "OC_sub18746_snd()");

	int curWord = _currScript->readUint16LE();
	curWord = (2 << 8) + (curWord & 0xFF);
	warning("TODO: ovlContentOVL Function 2, init DX and BX");
}
void RobinScript::OC_sub1875D_snd() {
	debugC(1, kDebugScript, "OC_sub1875D_snd()");
	warning("TODO: ovlContentOVL Function 6");
}
void RobinScript::OC_sub18764() {
	warning("OC_sub18764");
}
} // End of namespace
