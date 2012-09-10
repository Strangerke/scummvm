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
 * This is a utility for storing all the hardcoded data of Tony Tough in a separate
 * data file, used by the game engine
 */

// Disable symbol overrides so that we can use system headers.
#define FORBIDDEN_SYMBOL_ALLOW_ALL

// HACK to allow building with the SDL backend on MinGW
// see bug #1800764 "TOOLS: MinGW tools building broken"
#ifdef main
#undef main
#endif // main

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/scummsys.h"
#include "common/events.h"

#include "create_tony.h"
#include "staticdata.h"

static void writeByte(FILE *fp, uint8 b) {
	fwrite(&b, 1, 1, fp);
}

static void writeUint16BE(FILE *fp, uint16 value) {
	writeByte(fp, (uint8)(value >> 8));
	writeByte(fp, (uint8)(value & 0xFF));
}

void writeSint16BE(FILE *fp, int16 value) {
	writeUint16BE(fp, (uint16)value);
}

static void writeUint32BE(FILE *fp, uint32 value) {
	writeByte(fp, (uint8)(value >> 24));
	writeByte(fp, (uint8)((value >> 16) & 0xFF));
	writeByte(fp, (uint8)((value >> 8) & 0xFF));
	writeByte(fp, (uint8)(value & 0xFF));
}

void writeSint32BE(FILE *fp, int32 value) {
	writeUint32BE(fp, (uint16)value);
}

int main(int argc, char *argv[]) {

	int _cTable[256];
	int _lTable[256];
	int _lDefault;
	int _hDefault;

	enum {
		IT_ITA = 1 << 0,
		PL_POL = 1 << 1,
		RU_RUS = 1 << 2,
		CZ_CZE = 1 << 3,
		FR_FRA = 1 << 4,
		DE_DEU = 1 << 5
	};

	int _lang = DE_DEU;
	printf("DE_DEU\n");

	_lDefault = 26;
	_hDefault = 30;

	for (int i = 0; i < 256; i++) {
		_cTable[i] = -1;
		_lTable[i] = _lDefault;
	}

	for (int i = 0; i < 26; i++) {
		_cTable['A' + i] = i + 0;
		_cTable['a' + i] = i + 0;
	}

	for (int i = 0; i < 10; i++)
		_cTable['0' + i] = i + 26;

	_cTable[','] = 36;
	_cTable[';'] = 37;
	_cTable['.'] = 38;
	_cTable[':'] = 39;
	_cTable['-'] = 40;
	_cTable['+'] = 41;
	_cTable['!'] = 42;
	// _cTable['!'] = 43; Exclamation countdown
	_cTable['?'] = 44;
	// _cTable['?'] = 45;  Interrogativo alla rovescia
	_cTable['/'] = 46;
	_cTable['('] = 47;
	_cTable[')'] = 48;
	_cTable['='] = 49;
	_cTable['\''] = 50;
	_cTable['\"'] = 51;
	_cTable[(byte)'�'] = 52;
	_cTable[(byte)'$'] = 53;
	_cTable[(byte)'%'] = 54;
	_cTable[(byte)'&'] = 55;
	_cTable[(byte)'^'] = 56;
	_cTable[(byte)'*'] = 57;
	_cTable[(byte)'<'] = 58;
	_cTable[(byte)'>'] = 59;
	_cTable[(byte)'�'] = 60;
	_cTable[(byte)'�'] = 61;
	_cTable[(byte)'�'] = 62;
	_cTable[(byte)'�'] = 63;
	//_cTable[(byte)'�'] = 64;   integral
	_cTable[(byte)'�'] = 65;
	_cTable[(byte)'�'] = 66;
	_cTable[(byte)'�'] = 67;
	_cTable[(byte)'�'] = 68;
	_cTable[(byte)'�'] = 69;
	_cTable[(byte)'�'] = _cTable[(byte)'�'] = 70;
	_cTable[(byte)'�'] = 71;
	_cTable[(byte)'�'] = 72;
	_cTable[(byte)'�'] = 73;
	//_cTable[(byte)' '] = 74;   e circlet
	_cTable[(byte)'�'] = 75;
	_cTable[(byte)'�'] = 76;
	//_cTable[(byte)' '] = 77;     i circlet
	_cTable[(byte)'�'] = 78;
	_cTable[(byte)'�'] = _cTable[(byte)'�'] = 79;
	//_cTable[(byte)' '] = 80;       o circlet
	_cTable[(byte)'�'] = 81;
	_cTable[(byte)'�'] = _cTable[(byte)'�'] = 82;
	//_cTable[' '] = 83;     u circlet
	//_cTable[' '] = 84;   y dieresi

	/* Little lengths */
	_lTable[' '] = 11;
	_lTable['.'] = 8;
	_lTable['-'] = 12;
	_lTable['\''] = 8;
	_lTable['0'] = 20;
	_lTable['1'] = 20;
	_lTable['2'] = 15;
	_lTable['3'] = 20;
	_lTable['4'] = 20;
	_lTable['5'] = 20;
	_lTable['6'] = 20;
	_lTable['7'] = 20;
	_lTable['8'] = 20;
	_lTable['9'] = 20;


	_lTable['a'] = _lTable['A'] = _lTable['�'] = _lTable['�'] = 17;
	_lTable['b'] = _lTable['B'] = 17;
	_lTable['c'] = _lTable['C'] = 19;
	_lTable['d'] = _lTable['D'] = 17;
	_lTable['e'] = _lTable['E'] = 15;
	_lTable['f'] = _lTable['F'] = 17;
	_lTable['g'] = _lTable['G'] = 19;
	_lTable['i'] = _lTable['I'] = 16;
	_lTable['h'] = _lTable['H'] = 17;
	_lTable['k'] = _lTable['K'] = 17;
	_lTable['l'] = _lTable['L'] = 14;
	_lTable['m'] = _lTable['M'] = 19;
	_lTable['n'] = _lTable['N'] = 17;
	_lTable['o'] = _lTable['O'] = _lTable['�'] = _lTable['�'] = 19;
	_lTable['p'] = _lTable['P'] = 17;
	_lTable['q'] = _lTable['Q'] = 19;
	_lTable['r'] = _lTable['R'] = 14;
	_lTable['s'] = _lTable['S'] = 13;
	_lTable['t'] = _lTable['T'] = 15;
	_lTable['u'] = _lTable['U'] = _lTable['�'] = _lTable['�'] = 15;
	_lTable['v'] = _lTable['V'] = 13;
	_lTable['x'] = _lTable['X'] = 15;
	_lTable['y'] = _lTable['Y'] = 13;
	_lTable['w'] = _lTable['W'] = 19;
	_lTable['z'] = _lTable['Z'] = 20;
	_lTable[(byte)'�'] = 17;

	if (_lang == PL_POL) {
		// Polish characters
		//�����ꣳ���󌜯���
		//AaCcEeLlNnOoSsZzZz
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 85;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 20;

		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 86;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 22;

		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 87;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 17;

		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 88;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 19;

		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 89;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 17;

		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 90;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 22;

		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 91;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 15;

		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 92;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 21;

		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 93;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 21;

	} else if (_lang == RU_RUS) {
		// Russian Characters
		// WARNING: The Russian font uses many of the ISO-Latin-1 font,
		// allowing for further translations. To support Tonyin other langauges,
		// these mappings could be used as a basis

		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 85;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 20;

		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 94;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 95;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 96;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 97;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 98;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 99;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 100;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 101;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 102;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 103;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 104;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 105;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 106;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 107;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 108;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 109;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 110;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 111;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 112;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 113;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 114;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 115;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 116;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 117;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 118;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 119;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 120;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 121;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 122;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 123;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 124;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 125;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 126;


		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 18;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 18;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 18;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 17;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 16;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 18;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 18;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 20;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 18;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 18;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 18;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 18;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 16;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 18;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 15;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 22;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 15;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 18;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 22;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 19;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 16;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 21;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 20;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 16;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 16;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 19;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 22;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 18;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 19;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 19;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 15;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 18;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 18;

	} else if (_lang == CZ_CZE) {
		// Czech

		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 127;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 128;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 129;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 130;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 131;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 132;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 133;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 134;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 135;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 136;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 137;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 138;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 139;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 140;
		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 141;

		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 17;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 15;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 22;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 18;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 21;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 16;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 18;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 19;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 17;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 23;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 24;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 17;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 22;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 16;
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 16;

	} else if (_lang == FR_FRA) {
		// French

		// Translate accented characters as normal letters

		_cTable[(byte)'�'] = _cTable[(byte)'�'] = _cTable[(byte)'�'] = 0; // a
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = _lTable[(byte)'�'] = 17;

		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 4; // e
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 15;

		_cTable[(byte)'�'] = _cTable[(byte)'�'] = _cTable[(byte)'�'] = 8; // i
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = _lTable[(byte)'�'] = 16;

		_cTable[(byte)'�'] = _cTable[(byte)'�'] = _cTable[(byte)'�'] = _cTable[(byte)'�'] = 14; // o
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = _lTable[(byte)'�'] = _lTable[(byte)'�'] = 19;

		_cTable[(byte)'�'] = _cTable[(byte)'�'] = 20; // u
		_lTable[(byte)'�'] = _lTable[(byte)'�'] = 15;

	} else if (_lang == DE_DEU) {
		// German

		_cTable['�'] = 142;
		// SS = 143

		_lTable['�'] = 24;
	}

	printf("_cTableObj = {");
	for (int i = 0; i < 256; i++)
		printf("%d, ", _cTable[i]);
	printf("};\n_lTableObj = {");
	for (int i = 0; i < 256; i++)
		printf("%d, ", _lTable[i]);
	printf("};");




/*
	FILE *outFile;
	int nbrElem;

	outFile = fopen("tony.dat", "wb");

	// Write header
	fwrite("TONY", 4, 1, outFile);

	writeByte(outFile, TONY_DAT_VER_MAJ);
	writeByte(outFile, TONY_DAT_VER_MIN);

	// game versions/variants
	writeUint16BE(outFile, NUM_VARIANTS);

	// Write locationDirNotVisited
	nbrElem = sizeof(locationDirNotVisited_EN) / sizeof(char *);
	writeTextArray(outFile, locationDirNotVisited_EN, nbrElem);

	nbrElem = sizeof(locationDirNotVisited_FR) / sizeof(char *);
	writeTextArray(outFile, locationDirNotVisited_FR, nbrElem);

	nbrElem = sizeof(locationDirNotVisited_DE) / sizeof(char *);
	writeTextArray(outFile, locationDirNotVisited_DE, nbrElem);

	nbrElem = sizeof(locationDirNotVisited_RU) / sizeof(char *);
	writeTextArray(outFile, locationDirNotVisited_RU, nbrElem);

	nbrElem = sizeof(locationDirNotVisited_SP) / sizeof(char *);
	writeTextArray(outFile, locationDirNotVisited_SP, nbrElem);

	// Write locationDirVisited
	nbrElem = sizeof(locationDirVisited_EN) / sizeof(char *);
	writeTextArray(outFile, locationDirVisited_EN, nbrElem);

	nbrElem = sizeof(locationDirVisited_FR) / sizeof(char *);
	writeTextArray(outFile, locationDirVisited_FR, nbrElem);

	nbrElem = sizeof(locationDirVisited_DE) / sizeof(char *);
	writeTextArray(outFile, locationDirVisited_DE, nbrElem);

	nbrElem = sizeof(locationDirVisited_RU) / sizeof(char *);
	writeTextArray(outFile, locationDirVisited_RU, nbrElem);

	nbrElem = sizeof(locationDirVisited_SP) / sizeof(char *);
	writeTextArray(outFile, locationDirVisited_SP, nbrElem);

	// Write specialInfoLine
	nbrElem = sizeof(specialInfoLine_EN) / sizeof(char *);
	writeTextArray(outFile, specialInfoLine_EN, nbrElem);

	nbrElem = sizeof(specialInfoLine_FR) / sizeof(char *);
	writeTextArray(outFile, specialInfoLine_FR, nbrElem);

	nbrElem = sizeof(specialInfoLine_DE) / sizeof(char *);
	writeTextArray(outFile, specialInfoLine_DE, nbrElem);

	nbrElem = sizeof(specialInfoLine_RU) / sizeof(char *);
	writeTextArray(outFile, specialInfoLine_RU, nbrElem);

	nbrElem = sizeof(specialInfoLine_SP) / sizeof(char *);
	writeTextArray(outFile, specialInfoLine_SP, nbrElem);

	// Not yet handled: miscTexts, endingLine and exitLine. Are they useful?

	fclose(outFile);
	return 0;
}

void writeTextArray(FILE *outFile, const char *textArray[], int nbrText) {
	int len, len1, pad;
	uint8 padBuf[DATAALIGNMENT];

	for (int i = 0; i < DATAALIGNMENT; i++)
		padBuf[i] = 0;

	writeUint16BE(outFile, nbrText);
	len = DATAALIGNMENT - 2;
	for (int i = 0; i < nbrText; i++) {
		len1 = strlen(textArray[i]) + 1;
		pad = DATAALIGNMENT - (len1 + 2) % DATAALIGNMENT;
		len += 2 + len1 + pad;
	}
	writeUint16BE(outFile, len);

	fwrite(padBuf, DATAALIGNMENT - 2, 1, outFile); // padding
	for (int i = 0; i < nbrText; i++) {
		len = strlen(textArray[i]) + 1;
		pad = DATAALIGNMENT - (len + 2) % DATAALIGNMENT;

		writeUint16BE(outFile, len + pad + 2);
		fwrite(textArray[i], len, 1, outFile);
		fwrite(padBuf, pad, 1, outFile);
	}
*/
}
