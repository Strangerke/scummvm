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
#include "common/file.h"
#include "common/system.h"
#include "engines/util.h"
#include "graphics/font.h"
#include "graphics/fontman.h"
#include "graphics/palette.h"

namespace Castlx {

CastlxEngine *g_engine;

CastlxEngine::CastlxEngine(OSystem *syst, const ADGameDescription *gameDesc) : Engine(syst),
	_gameDescription(gameDesc), _rnd("Castlx") {
	g_engine = this;

	// Add the game folder to the search manager path variable
	const Common::FSNode gameDataDir(ConfMan.get("path"));
	SearchMan.addSubDirectoryMatching(gameDataDir, "SONG1");
	SearchMan.addSubDirectoryMatching(gameDataDir, "GESTION1");
	SearchMan.addSubDirectoryMatching(gameDataDir, "SPRIT1/PC");
	
	_surfaceF = _surfaceV = nullptr;
	_surfaceB = nullptr;
	_gstPtr = nullptr;
	_curGstPtr = nullptr;
	_song0 = _song1 = nullptr;
	_lastFileSize = 0;
	_mouseCursorVisible = 0;
	_word2A302 = nullptr;
	_backgroundImgPtr = nullptr;
	_gstEndPtr = nullptr;

	for (int i = 0; i < 128; ++i)
		_keyPressed[i] = 0;

	for (int i = 0; i < 63; ++i) {
		_opcodes[i]._keyword = "";
		_opcodes[i]._opcodePtr = nullptr;
	}

	_label._keyword = "";
	_label._gstLabelPtr = nullptr;
	_mousePosX = _mousePosY = 0;
	_oldMousePosX = _oldMousePosY = 0;
	_mouseMinX = _mouseMaxX = 0;
	_mouseMinY = _mouseMaxY = 0;

	for (int i = 0; i < 16; ++i) {
		_defineArray[i]._name = "";
		_defineArray[i]._value = 0;
	}

	_paletteFctStart = _paletteFctCounter = 0;
	_filename = "";

	_postGstSegment = nullptr;
	for (int i = 0; i < 5; ++i)
		_spritePtr[i] = _postGstSegment;

	for (int i = 0; i < 768; ++i) {
		_unkPalette[i] = 0;
		_unkPalette2[i] = 0;
		_unkPalette3[i] = 0;
	}

	for (int i = 0; i < 3; ++i) {
		_blendingCol1[i] = 60;
		_unkCol2[i] = 60;
	}

	_flagEnableHotspots = 0;
	_mouseButtonStatus = 0;

	for (int i = 0; i < 14; ++i)
		_hardcodedLogic[i] = nullptr;

	_opCopyMinY = _opCopyMinX = 0;
	_opCopyMaxY = _opCopyMaxX = 0;
	_surfaceB = nullptr;
	_byte1E7EA = 0;
	_int8Counter3 = 0;
	_byte2C0BC = 0;
	_activeSoundFl = 0;
	_word2C0A8 = 0;
	for (int i = 0; i < 8; ++i)
		_word2C0AA[i] = 0;
	_byte2C0BE = 0;
	_byte2C0F3 = 0;
	_unkSpriteNumber = 0;
	_displayMessageRect = 0;
	
	for (int i = 0; i < 256; ++i)
		_blending1Map[i] = 0;
	_byte2C0BF = 0;

	_hotspotX = _hotspotY = 0;
	_hotspotWidth = _hotspotHeight = 0;
	_unkHotspotVal1 = _unkHotspotVal2 = 0;
	_hotspotHit = 0;
	
	_byte1EFF0 = 0;
	_byte1F49D = 0;
	_word19144 = 0;
	_word19140 = 0;
	_blitBoundaryMinX = _blitBoundaryMinY = _blitBoundaryMinX = _blitBoundaryMinX = 0;

	_word1913C = false;
	_boundaryType = 0;

	_word14502 = 0;

	// Room 00 flags
	_ageChecked = false;
	// Room 01 flags
	_flagUseTits = _flagTakeSeed = 0;
	
	_hotspot2871.init(35, Common::String("L'utilisation de cet objet ne déclenche rien de spécial.ÿRIEN"));
	_infoC068.init(28, Common::String("$  Avant de commencer vous $devez nous préciser si vous$   avez plus de 18 ans ?$$    (O) Oui     (N) Non$ÿ "));
	_infoC0DA.init(40, Common::String("$ Désolé vous n'avez pas l'âge requis $        pour jouer à CASTL'X$ÿ "));
}

CastlxEngine::~CastlxEngine() {
	delete _screen;
	delete[] _gstPtr;
	delete[] _song0;
	delete[] _song1;
	delete[] _backgroundImgPtr;
	if (_surfaceF)
		_surfaceF->free();
	if (_surfaceV)
		_surfaceV->free();
	if (_surfaceB)
		_surfaceB->free();
	
	delete _surfaceF;
	delete _surfaceV;
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

void CastlxEngine::waitRetrace() {
	// No longer needed for display quality, replaced by a short delay
	_system->delayMillis(5);
}

void CastlxEngine::setPartialPalette(byte *palette) {
	waitRetrace();
	_system->getPaletteManager()->setPalette(palette, _paletteFctStart, _paletteFctCounter);
}

/**
 * @brief Fade from black to _unkPalette2 using _unkPalette3
*/
void CastlxEngine::fadeInPalette2() {
	debugC(5, kDebugGraphics, "fadeInPalette2");

	int start = _paletteFctStart * 3;
	int counter = _paletteFctCounter * 3;
	for (int16 factor = 256; factor >= 0; factor -= 16) {
		for (int i = 0; i < counter; ++i) {
			_unkPalette3[start + i] = (_unkPalette2[start + i] * factor) >> 8;
		}
		waitRetrace();
		setPartialPalette(_unkPalette3);

		_system->copyRectToScreen((const byte *)_surfaceF->getBasePtr(0, 0), _surfaceF->pitch, 0, 0, 640, 400);
		_system->updateScreen();
	}
}

/**
 * @brief Fade palette to back using _unkPalette2
 * @param palPtr 
*/
void CastlxEngine::fadeOutPalette2(byte *palPtr) {
	debugC(5, kDebugGraphics, "fadeOutPalette2");
	int start = _paletteFctStart * 3;
	int counter = _paletteFctCounter * 3;
	for (int16 factor = 0; factor <= 256; factor += 8) {
		for (int i = 0; i < counter; ++i) {
			_unkPalette2[start + i] = (palPtr[start + i] * factor) >> 8;
		}
		waitRetrace();
		setPartialPalette(_unkPalette2);

		_system->copyRectToScreen((const byte *)_surfaceF->getBasePtr(0, 0), _surfaceF->pitch, 0, 0, 640, 400);
		_system->updateScreen();
	}
}

void CastlxEngine::loadImgFile(Common::String &filename) {
	_backgroundImgPtr = loadFile(filename);
}

void CastlxEngine::loadImgToSurface(byte *imgBuffer, Graphics::Surface *surface) {
	byte *curPtr = imgBuffer;
	curPtr += 32;

	for (int i = 0; i < 768; ++i)
		_unkPalette[i] = *curPtr++;

	for (int i = 0; i < 3; ++i)
		_unkPalette[i] = 0;
	
	byte *dest = (byte *)surface->getBasePtr(0,0);
	for (int y = 0; y < 400; ++y) {
		for (int x = 0; x < 320; ++x) {
			int index = (y * 640) + (2 * x);
			// Images are stored in 320x400, each pixel is doubled at display
			dest[index] = dest[index + 1] = curPtr[y * 320 + x];
		}
	}

	_system->copyRectToScreen((uint8 *)surface->getPixels(), surface->pitch, 0, 0, 640, 400);
}

void CastlxEngine::createTransparencyMapping() {
	warning("createTransparencyMapping");
	for (int i = 0; i < 3; ++i)
		_unkCol2[i] = _blendingCol1[i];

	for (int i = 0; i < 256; ++i) {
		int _newCol1 = (_unkPalette2[3 * i] * _blendingCol1[0]) >> 8;
		int _newCol2 = (_unkPalette2[3 * i+ 1] * _blendingCol1[1]) >> 8;
		int _newCol3 = (_unkPalette2[3 * i + 2] * _blendingCol1[2]) >> 8;
		int bl = i;
		int dl = 255;
		int dh = 0;
		
		for (int j = 0; j < 256; ++j) {
			int ah = abs(_unkPalette2[3 * j] - _newCol1);
			int bh = abs(_unkPalette2[3 * j + 1] - _newCol2);
			int ch = abs(_unkPalette2[3 * j + 2] - _newCol3);

			int al = ah;
			if (al < bh)
				al = bh;
			if (al < ch)
				al = ch;

			if (al < dl) {
				bl = j;
				dl = al;
			}
		}		

		_blending1Map[i] = bl;
	}
}

void CastlxEngine::sub19306(Common::String ptr, int16 posX, int16 poxY) {
	warning("STUB sub19306");
}

void CastlxEngine::resetDisplayStringList() {
	warning("resetDisplayStringList");
	for (int i = 0; i < 5; ++i) {
		if (!_displayStringList[i]._id)
			continue;

		if (_int8Counter3 > READ_LE_INT16(_displayStringList[i]._headerPtr)) {
			_displayStringList[i]._id = 0;
			
			sub19306(_displayStringList[i]._message, _displayStringList[i]._posX, _displayStringList[i]._posY);
		}
	}
}

void CastlxEngine::sub1228A() {
	warning("STUB - sub1228A");
	if (_word14502) {
		sub12CAF();
	} else {
		warning("STUB - inventory?");
	}
}

void CastlxEngine::checkOpenInventory() {
	warning("checkOpenInventory");

	getEvents();
	if (_lastEvent.type == Common::EVENT_RBUTTONDOWN || (_lastEvent.type == Common::EVENT_KEYUP && _lastEvent.kbd.keycode == Common::KEYCODE_SPACE))
		sub1228A();
}

void CastlxEngine::handleSoundOff() {
	warning("STUB - handleSoundOff");
}

bool CastlxEngine::checkHotspot(int ax, int bx, int cx, int dx) {
	warning("checkHotspot");
	_hotspotX = dx;
	_hotspotY = cx;
	_hotspotWidth = ax;
	_hotspotHeight = bx;
	_hotspotHit = 0;

	if (_mousePosY >= dx && _mousePosY <= dx + ax && _mousePosX >= cx && _mousePosX <= cx + bx)
		_hotspotHit = 1;

	return _hotspotHit;
}

bool CastlxEngine::setDisplayStringQueue(int16 di, int16 cx, int16 dx, Common::String message, DisplMessage *bp) {
	warning("setDisplayStringQueue");
	for (int i = 0; i < 5; ++i) {
		if (!_displayStringList[i]._id) {
			_displayStringList[i]._id = di;
			_displayStringList[i]._posX = dx;
			_displayStringList[i]._posY = cx;
			_displayStringList[i]._message = message;
			_displayStringList[i]._headerPtr = bp;
			return true;
		}
	}

	return false;
}

int16 CastlxEngine::sub12D4C(int16 si) {
	warning("sub12D4C");
	int16 bp = _hotspotY;
	int16 dx = bp + _hotspotWidth;
	int16 ax = 400 - dx;

	if (ax <= bp) {
		dx = 64;
		ax = bp;
	} else {
		dx = bp + _hotspotWidth + 64;
	}

	dx += getRandom(128) - 64;
	CLIP<int16>(dx, 0, 340);

	ax = 5 * si;
	int16 cx = 8 + getRandom(320 - ax - 16);

	return (cx & 0xFFFC);
}

void CastlxEngine::sub1918D(Common::String detail, int16 cx, int16 dx) {
	warning("STUB - sub1918D %s %d %d", detail.c_str(), cx, dx);

	const Graphics::Font *font = FontMan.getFontByUsage(Graphics::FontManager::kBigGUIFont);

	const char *head = detail.c_str();
	const char *ptr = head;
	int lineCtr = 1;
	int maxLength = 0;
	Common::String curLine = "";
	while (*ptr) {
		if (*ptr == '$') {
			++lineCtr;
			int len = font->getStringWidth(curLine);
			curLine.trim();
			if (len > maxLength)
				maxLength = len;
			curLine = "";
		} else if (*ptr == -1) {
			warning("split found (header?) -1/0xFF");
			break;
		} else {
			curLine += *ptr;
		}
		++ptr;
	}

	int posX = cx * 2;
	int posY = dx;
	int delta = 0;
	int color = 0xFF;
	if (_displayMessageRect) {
		delta = 10;
		// +2 and -2 are used to cut corner
		_surfaceF->drawLine(posX + 2, posY, posX + maxLength + delta - 1, posY, color);
		_surfaceF->drawLine(posX + 2, posY + lineCtr * font->getFontHeight(), posX + maxLength + delta - 1, posY + lineCtr * font->getFontHeight(), color);
		// vertical line are doubled
		_surfaceF->drawLine(posX, posY + 1, posX, posY + -1 + lineCtr * font->getFontHeight(), color);
		_surfaceF->drawLine(posX + 1, posY + 1, posX + 1, posY - 1 + lineCtr * font->getFontHeight(), color);
		_surfaceF->drawLine(posX + delta + maxLength, posY + 1, posX + delta + maxLength, posY + -1 + lineCtr * font->getFontHeight(), color);
		_surfaceF->drawLine(posX + delta + maxLength + 1, posY + 1, posX + delta + maxLength + 1, posY - 1 + lineCtr * font->getFontHeight(), color);
	}

	// Add Blending effect
	for (int y = posY + 1; y < posY + lineCtr * font->getFontHeight(); ++y) {
		byte *destLine = (byte *)_surfaceF->getBasePtr(0, y);
		for (int x = posX + 2; x < posX + delta + maxLength; ++x) {
			destLine[x] = _blending1Map[destLine[x]];
		}
	}

	lineCtr = 0;
	ptr = head;
	posX += delta / 2;
	while (*ptr) {
		if (*ptr == '$') {
			font->drawString(_surfaceF, curLine, posX, posY + lineCtr * font->getFontHeight(), font->getStringWidth(curLine), color);
			curLine = "";
			++lineCtr;
		} else if (*ptr == -1) {
			break;
		} else {
			curLine += *ptr;
		}
		++ptr;
	}

	_system->copyRectToScreen((const byte *)_surfaceF->getBasePtr(0, 0), _surfaceF->pitch, 0, 0, 640, 400);
	_system->updateScreen();
}

void CastlxEngine::sub1915D(Common::String si, int16 cx, int16 dx) {
	warning("sub1915D");
	_word1913C = false;
	Graphics::Surface *back = _surfaceF;

	switchSurfaceBuffers();
	waitRetrace();
	sub1918D(si, cx, dx);
	switchSurfaceBuffers();
	waitRetrace();
	
	_surfaceF = back;
}

void CastlxEngine::addHotSpotUseObjectOn(int16 ax, int16 bx, int16 cx, int16 dx, DisplMessage *message, DisplMessage *bp) {
	warning("addHotspotUseObjectOn");
	if (!_flagEnableHotspots || (_byte1EFF0 & 0x80))
		return;

	if (bp != nullptr) {
		if (bp->_field1 == 0)
			return;

		warning("TODO - addHotSpotUseObjectOn - check if inventory");
	}

	if (!checkHotspot(ax, bx, cx, dx))
		return;

	cleanEvents();
	sub10902();
	++message->_field2;
	if (!_unkHotspotVal1 && !_unkHotspotVal2)
		cx = sub12D4C(message->_field2);

	if (setDisplayStringQueue(message->_field2, cx, dx, message->_detail, bp)) {
		sub1915D(message->_detail, cx, dx);
		message->_field1 = _word19144 + _int8Counter3;
		_flagEnableHotspots = false;
		_byte1EFF0 = 0;
	}
}

void CastlxEngine::setBackgroundHotspot() {
	debug("setBackgroundHotspot");
	_unkHotspotVal1 = _unkHotspotVal2 = 0;
	addHotSpotUseObjectOn(400, 320, 0, 0, &_hotspot2871, nullptr);
}

void CastlxEngine::opCopySurface(Graphics::Surface *src, Graphics::Surface *dest) {
	debugC(5, kDebugGraphics, "opCopySurface");
	byte *srcPtr = (byte *)src->getBasePtr(_opCopyMinX, _opCopyMinY);
	byte *destPtr = (byte *)dest->getBasePtr(_opCopyMinX, _opCopyMinY);

	for (int y = _opCopyMinY; y < _opCopyMaxY; ++y) {
		for (int x = _opCopyMinX; x < _opCopyMaxX; ++x) {
			int index = y * 640 + x;
			destPtr[index] = srcPtr[index];
		}		
	}	
}

void CastlxEngine::setSpriteBlitBoundaries(int16 type) {
	debugC(5, kDebugGraphics, "setSpriteBlitBoundaries");

	switch (type) {
	case 1:
		_blitBoundaryMinX = _blitBoundaryMinY = 0;
		_blitBoundaryMaxX = 640;
		_blitBoundaryMaxY = 400;
		_boundaryType = 0;
		break;		
	case 2:
		_blitBoundaryMinX = _blitBoundaryMinY = 0;
		_blitBoundaryMaxX = 640;
		_blitBoundaryMaxY = 152;
		_boundaryType = 1;
		break;
	case 3:
		_blitBoundaryMinX = _blitBoundaryMinY = 0;
		_blitBoundaryMaxX = 640;
		_blitBoundaryMaxY = 82;
		_boundaryType = 2;
		break;
	case 4:
		_blitBoundaryMinX = 0;
		_blitBoundaryMinY = 100;
		_blitBoundaryMaxX = 640;
		_blitBoundaryMaxY = 182;
		_boundaryType = 3;
		break;
	default:
		break;
	}
}

void CastlxEngine::blitSpriteCtrlOnSurfaceF(SpriteCtrl *spriteCtrl) {
	debugC(5, kDebugGraphics, "blitSpriteCtrlOnSurfaceF");
	setSpriteBlitBoundaries(spriteCtrl->_boundaryType);
	
	byte *curBankPtr = _spritePtr[spriteCtrl->_spriteBank - 1];
	uint16 startPos = READ_LE_UINT16(&curBankPtr[8 * spriteCtrl->_spriteId]);
	uint16 size = READ_LE_UINT16(&curBankPtr[8 * spriteCtrl->_spriteId] + 4) * READ_LE_UINT16(&curBankPtr[8 * spriteCtrl->_spriteId] + 6);

	byte *curSprite = &curBankPtr[startPos];
	uint32 sign = READ_LE_UINT32(curSprite);
	if (sign != MKTAG('N', 'E', 'X', 'T'))
		error("Invalid signature");

	uint16 posY = READ_LE_UINT32(curSprite + 4);
	uint16 posX = READ_LE_UINT32(curSprite + 6);
	uint16 height = READ_LE_UINT32(curSprite + 8);
	uint16 width = READ_LE_UINT32(curSprite + 10);

	// Will be used later for boundaries
	spriteCtrl->_param1 = posY;
	spriteCtrl->_param2 = posX;
	
	byte *curPtr = curSprite + 12;

	byte *dest = (byte *)_surfaceF->getBasePtr(0, 0);
	
	for (int plane = 0; plane != 4; ++plane) {
		for (int y = 0; y != height; ++y) {
			for (int x = 0; x != width / 4; ++x) {
				int dst = 640 * (posY + y) + 4 * (posX / 2 + 2 * x) + plane * 2;
				uint8 c = *curPtr++;
				if (c)
					dest[dst + 0] = dest[dst + 1] = c;
			}
		}
	}
	
	_surfaceF->setPixels(dest);

	_system->copyRectToScreen((uint8 *)_surfaceF->getPixels(), _surfaceF->pitch, 0, 0, 640, 400);
	_system->updateScreen();
}

// ax = sprite Idx, bx = sprite bank
void CastlxEngine::setSpriteCtrlAndBlitOnSurfaceF(int16 ax, int16 bx, int16 cx, uint16 dx) {
	debugC(5, kDebugGraphics, "setSpriteCtrlAndBlitOnSurfaceF ax %d bx %d cx %d dx %d", ax, bx, cx, dx);
	_spriteCtrl._boundaryType = _boundaryType;
	_spriteCtrl._param1 = dx;
	_spriteCtrl._param2 = cx;
	_spriteCtrl._spriteId = ax;
	_spriteCtrl._spriteBank = bx;

	blitSpriteCtrlOnSurfaceF(&_spriteCtrl);
}

// ax = sprite Idx, bx = sprite bank
void CastlxEngine::setSpriteCtrlAndBlitOnSurfaceV(int16 ax, int16 bx, int16 cx, int16 dx) {
	Graphics::Surface *tmpSurface = _surfaceF;
	_surfaceF = _surfaceV;
	setSpriteCtrlAndBlitOnSurfaceF(ax, bx, cx, dx);
	_surfaceF = tmpSurface;	
}

int CastlxEngine::getRandom(int max) {
	return _rnd.getRandomNumber(max);
}

/**
 * @brief Wait until there no useful event
*/
void CastlxEngine::cleanEvents() {
	warning("cleanEvents");

	getRandom(1); // wtf ??

	for (;;) {
		_eventMan->pollEvent(_lastEvent);
		Common::Point mousePos = _eventMan->getMousePos();
		_mousePosX = CLIP(mousePos.x, _mouseMinX, _mouseMaxX);
		_mousePosY = mousePos.y;

		if (_lastEvent.type != Common::EVENT_LBUTTONUP && _lastEvent.type != Common::EVENT_KEYUP)
			break;

		_system->updateScreen();
		_system->delayMillis(10);
	}
	
	_flagEnableHotspots = 0;
	
}

/**
 * @brief Set _lastEvent
*/
void CastlxEngine::getEvents() {
	_eventMan->pollEvent(_lastEvent);
	Common::Point mousePos = _eventMan->getMousePos();
	_mousePosX = CLIP(mousePos.x, _mouseMinX, _mouseMaxX);
	_mousePosY = mousePos.y;

	_system->updateScreen();
	_system->delayMillis(10);
}

/**
 * @brief Initialize display
 * The original is using a parameter as this function is also used in opRESO.
 * As this opcode isn't used in the game, I only considered the value used in
 * start(), which is 1. The is used to access multiple arrays in order to
 * set a 640x400 ModeX display.
*/
void CastlxEngine::initDisplayMode() {
	_surfaceF = new Graphics::Surface();
	_surfaceF->create(640, 400, Graphics::PixelFormat::createFormatCLUT8());
	_surfaceV = new Graphics::Surface();
	_surfaceV->create(640, 400, Graphics::PixelFormat::createFormatCLUT8());
	_surfaceB = new Graphics::Surface();
	_surfaceB->create(640, 400, Graphics::PixelFormat::createFormatCLUT8());
}

void CastlxEngine::switchSurfaceBuffers() {
	debugC(5, kDebugGraphics, "SwitchSurfaceBuffers");
	SWAP(_surfaceF, _surfaceV);
	_system->copyRectToScreen((const byte *)_surfaceV->getBasePtr(0, 0), _surfaceV->pitch, 0, 0, 640, 400);
	_system->updateScreen();
}

/**
 * @brief initMouse - Init mouse variables
 * @param minX 
 * @param minY 
 * @param width 
 * @param height 
*/
void CastlxEngine::initMouse(int16 minX, int16 minY, int16 width, int16 height) {
	_mouseMinX = minX;
	_mouseMinY = minY;
	_mouseMaxX = minX + height;
	_mouseMaxY = minY + width;
}

/**
 * @brief setMousePosition - Set Mouse Position
 * @param posX 
 * @param posY 
*/
void CastlxEngine::setMousePosition(int16 posX, int16 posY) {
	_mousePosX = posX;
	_mousePosY = posY;
	g_system->warpMouse(_mousePosX, _mousePosY);
}

void CastlxEngine::getMouseStateClipped() {
	getEvents();
}

void CastlxEngine::sub11104(Graphics::Surface *byteArr, Graphics::Surface *surface) {
	warning("STUB sub11104 (guess restore surface under mouse cursor)");
}

void CastlxEngine::sub10902() {
	if (_byte1EFF0) {
		_opCopyMinY = _oldMousePosX;
		_opCopyMinX = _oldMousePosY;
		_opCopyMaxY = 11;
		_opCopyMaxX = 6;
	} else {
		_opCopyMinY = _oldMousePosX - 1;
		_opCopyMinX = _oldMousePosY - 1;
		_opCopyMaxY = 17;
		_opCopyMaxX = 10;
	}
	sub11104(_surfaceB, _surfaceV);
}

void CastlxEngine::displayInfoMessage(DisplMessage *info, uint16 cx, uint16 dx) {
	warning("STUB displayInfoMessage %s", info->_detail.c_str());

	if (info->_field2)
		return;

	++(info->_field2);
	if (setDisplayStringQueue(info->_field2, cx, dx, info->_detail, info)) 
		sub1915D(info->_detail, cx, dx);	
}

void CastlxEngine::sub12CAF() {
	warning("STUB - sub12CAF");
}

void CastlxEngine::loc12BFA() {
	// CHECKME: numbers are normally in variables, this is a shortcut
	opCOPYFB(0, 0, 640, 400);
	opCOPYVF(0, 0, 640, 400);

	switchSurfaceBuffers();
	waitRetrace();
	opCOPYBF(0, 0, 640, 400);
}

/**
 * @brief Opcode: Load Image
 * @param buffer 
*/
void CastlxEngine::opLOADIMG(byte **buffer) {
	skipNoiseInString(buffer);
	_filename = copyBuffer(buffer);
	debugC(5, kDebugScript, "opLOADIMG %s", _filename.c_str());

	loadImgFile(_filename);
	loadImgToSurface(_backgroundImgPtr, _surfaceF);
}

void CastlxEngine::opLOADIMG() {
	debugC(5, kDebugScript, "opLOADIMG %s", _filename.c_str());

	loadImgFile(_filename);
	loadImgToSurface(_backgroundImgPtr, _surfaceF);
}

void CastlxEngine::opEXIT(byte **buffer) { warning("STUB - opEXIT"); }
void CastlxEngine::opTEMPO(byte **buffer) { warning("STUB - opTEMPO"); }
/**
 * @brief opCode : Remove palette from/to
 * @param buffer 
*/
void CastlxEngine::opOTEPALETTE(byte **buffer) {
	skipNoiseInString(buffer);
	_paletteFctStart = parseString(buffer);
	skipNoiseInString(buffer);
	_paletteFctCounter = parseString(buffer);
	fadeInPalette2();
	debugC(5, kDebugScript, "opOTEPALETTE %d %d", _paletteFctStart, _paletteFctCounter);
}

void CastlxEngine::opOTEPALETTE(int start, int end) {
	_paletteFctStart = start;
	_paletteFctCounter = end;
	fadeInPalette2();
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
		_paletteFctStart = parseString(buffer);
		skipNoiseInString(buffer);
		_paletteFctCounter = parseString(buffer);
	}
	debugC(5, kDebugScript, "opMETPALETTE %d %d", _paletteFctStart, _paletteFctCounter);
	fadeOutPalette2(&_unkPalette[_paletteFctStart * 3]);
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

	debugC(5, kDebugScript, "opDEF - %d %s", index, _defineArray[index]._name.c_str());
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

	debugC(5, kDebugScript, "opNAME - index %d set to %d", index, value);
}

void CastlxEngine::opIF(byte **buffer) { warning("opIF"); }
void CastlxEngine::opLabel(byte **buffer) { warning("opLabel"); }

/**
 * @brief Opcode: Jump to Label
 * @note This implementation differs from the one in the original, it was easier to keep track of the label and jump to it, rather than re-parsing the whole script, looking for a (random) label.
 *       Keeping the label offset and it's name is far more readable and works for all the scripts. 
 * @param buffer 
*/
void CastlxEngine::opJUMP(byte **buffer) {
	skipNoiseInString(buffer);
	Common::String targetLabel = copyBuffer(buffer);
	debugC(5, kDebugScript,"opJUMP %s", targetLabel.c_str());
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
	debugC(5, kDebugScript, "opTIMER %d", delay);
}

/**
 * @brief Followed by a loop, it corresponds to a while. Only used once in script 00
 * @param buffer 
*/
void CastlxEngine::opWAIT(byte **buffer) {
	skipNoiseInString(buffer);
	int target = parseString(buffer);

	if (_int8Counter3 <= target) {
		debugC(5, kDebugScript, "opWAIT - Condition not met %d > %d", _int8Counter3, target);
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
	waitRetrace();
}

void CastlxEngine::opDummy(byte **buffer) { warning("Unexpected call to opDummy"); }
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
	cleanEvents();
	_int8Counter3 = 0;
}

/**
 * @brief Opcode: Load sprite
 * @param buffer 
*/
void CastlxEngine::opLOADSPR(byte **buffer) {
	skipNoiseInString(buffer);
	_filename = copyBuffer(buffer);
	skipNoiseInString(buffer);
	int index = parseString(buffer);

	debugC(5, kDebugScript, "opLOADSPR %s %d", _filename.c_str(), index);

	--index;
	_spritePtr[index] = loadFile(_filename);

	warning("opLOADSPR - Weird set of _backGroundImgPtr");
}

void CastlxEngine::opLOADSPR(int index) {
	debugC(5, kDebugScript, "opLOADSPR %s %d", _filename.c_str(), index);

	--index;
	_spritePtr[index] = loadFile(_filename);

	warning("opLOADSPR - Weird set of _backGroundImgPtr");
}

/**
 * @brief Opcode: Skippable delay (skipped by user input
 * @param buffer 
*/
void CastlxEngine::opPAUSE(byte **buffer) {
	skipNoiseInString(buffer);
	int delay = parseString(buffer);

	warning("opPAUSE : TODO implement skippable delay - %d", delay);
}

/**
 * @brief Opcode: Reset sprite
 * @param buffer 
*/
void CastlxEngine::opRAZSPR(byte **buffer) {
	skipNoiseInString(buffer);
	int index = parseString(buffer);

	--index;
	byte *ptr;
	if (!index)
		ptr = _backgroundImgPtr;
	else
		ptr = _postGstSegment;

	_spritePtr[index] = ptr;
	_backgroundImgPtr = ptr;

	debugC(5, kDebugScript, "opRAZSPR %d", index);
}

void CastlxEngine::opRAZSPR(int index) {
	--index;
	byte *ptr;
	if (!index)
		ptr = _backgroundImgPtr;
	else
		ptr = _postGstSegment;

	_spritePtr[index] = ptr;
	_backgroundImgPtr = ptr;

	debugC(5, kDebugScript, "opRAZSPR %d", index);
}

void CastlxEngine::opPALNOIR(byte **buffer) { warning("opPALNOIR"); }

/**
 * @brief Opcode: Load partial palette
 * @param buffer 
*/
void CastlxEngine::opLOADPALETTE(byte **buffer) {
	skipNoiseInString(buffer);
	int param = parseString(buffer);
	skipNoiseInString(buffer);
	_filename = copyBuffer(buffer);

	_paletteFctStart = param;
	
	byte *palette = loadFile(_filename);
	for (int i = _paletteFctStart * 3, j = 0; i < 768;) {
		if (j > _lastFileSize)
			break;
		// Color values are coded on 6bits (for old 6bits DAC)
		int32 col = palette[j++];
		assert(col < 64);

		col = (col << 2) | (col >> 4);
		if (col > 255)
			col = 255;

		_unkPalette[i++] = col;
	}
	_paletteFctStart = 0;
	debugC(5,kDebugScript, "opLOADPALETTE %d %s", param, _filename.c_str());
	delete[] palette;
}

void CastlxEngine::opLOADPALETTE(int index) {
	_paletteFctStart = index;

	byte *palette = loadFile(_filename);
	for (int i = _paletteFctStart * 3, j = 0; i < 768;) {
		if (j > _lastFileSize)
			break;
		// Color values are coded on 6bits (for old 6bits DAC)
		int32 col = palette[j++];
		assert(col < 64);

		col = (col << 2) | (col >> 4);
		if (col > 255)
			col = 255;

		_unkPalette[i++] = col;
	}
	_paletteFctStart = 0;
	debugC(5, kDebugScript, "opLOADPALETTE %d %s", index, _filename.c_str());
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
	switchSurfaceBuffers();
}

void CastlxEngine::opMODEPLAY(byte **buffer) { warning("opMODEPLAY"); }
void CastlxEngine::opINCRUSTIMGV(byte **buffer) { warning("opINCRUSTIMGV"); }
void CastlxEngine::opINCRUSTIMGF(byte **buffer) { warning("opINCRUSTIMGF"); }
/**
 * @brief Opcode: Copy partial surface from surfaceV to surfaceF
 * @param buffer 
*/
void CastlxEngine::opCOPYVF(byte **buffer) {
	skipNoiseInString(buffer);
	_opCopyMinY = parseString(buffer);
	skipNoiseInString(buffer);
	_opCopyMinX = parseString(buffer);
	skipNoiseInString(buffer);
	_opCopyMaxY = parseString(buffer);
	skipNoiseInString(buffer);
	_opCopyMaxX = parseString(buffer);

	// Double X
	_opCopyMinX *= 2;
	_opCopyMaxX *= 2;

	debugC(5, kDebugScript, "opCOPYVF %d %d %d %d", _opCopyMinY, _opCopyMinX, _opCopyMaxY, _opCopyMaxX);
	opCopySurface(_surfaceV, _surfaceF);
}

void CastlxEngine::opCOPYVF(uint16 posX, uint16 posY, uint16 width, uint16 height) {
	_opCopyMinX = posX;
	_opCopyMinY = posY;
	_opCopyMaxX = width;
	_opCopyMaxY = height;

	if (!_opCopyMaxX)
		return;

	opCopySurface(_surfaceV, _surfaceF);
}

/**
 * @brief Opcode: Copy partial surface from surfaceF to surfaceV
 * @param buffer 
*/
void CastlxEngine::opCOPYFV(byte **buffer) {
	skipNoiseInString(buffer);
	_opCopyMinY = parseString(buffer);
	skipNoiseInString(buffer);
	_opCopyMinX = parseString(buffer);
	skipNoiseInString(buffer);
	_opCopyMaxY = parseString(buffer);
	skipNoiseInString(buffer);
	_opCopyMaxX = parseString(buffer);

	// Double X
	_opCopyMinX *= 2;
	_opCopyMaxX *= 2;

	debugC(5, kDebugScript, "opCOPYFV %d %d %d %d", _opCopyMinY, _opCopyMinX, _opCopyMaxY, _opCopyMaxX);
	opCopySurface(_surfaceF, _surfaceV);
}

void CastlxEngine::opCOPYFV(uint16 posX, uint16 posY, uint16 width, uint16 height) {
	_opCopyMinX = posX;
	_opCopyMinY = posY;
	_opCopyMaxX = width;
	_opCopyMaxY = height;

	if (!_opCopyMaxX)
		return;

	opCopySurface(_surfaceF, _surfaceV);
}

/**
 * @brief Opcode: Copy partial surface from surfaceV to surfaceB
 * @param buffer 
*/
void CastlxEngine::opCOPYVB(byte **buffer) {
	skipNoiseInString(buffer);
	_opCopyMinY = parseString(buffer);
	skipNoiseInString(buffer);
	_opCopyMinX = parseString(buffer);
	skipNoiseInString(buffer);
	_opCopyMaxY = parseString(buffer);
	skipNoiseInString(buffer);
	_opCopyMaxX = parseString(buffer);

	// Double X
	_opCopyMinX *= 2;
	_opCopyMaxX *= 2;

	debugC(5, kDebugScript, "opCOPYVB %d %d %d %d", _opCopyMinY, _opCopyMinX, _opCopyMaxY, _opCopyMaxX);
	opCopySurface(_surfaceV, _surfaceB);
}

void CastlxEngine::opCOPYVB(int minX, int minY, int maxX, int maxY) {
	_opCopyMinX = minX;
	_opCopyMinY = minY;
	_opCopyMaxX = maxX;
	_opCopyMaxY = maxY;

	debugC(5, kDebugScript, "opCOPYVB %d %d %d %d", _opCopyMinY, _opCopyMinX, _opCopyMaxY, _opCopyMaxX);
	opCopySurface(_surfaceV, _surfaceB);
}

/**
 * @brief Opcode: Copy partial surface from surfaceF to surfaceB
 * @param buffer 
*/
void CastlxEngine::opCOPYFB(byte **buffer) {
	skipNoiseInString(buffer);
	_opCopyMinY = parseString(buffer);
	skipNoiseInString(buffer);
	_opCopyMinX = parseString(buffer);
	skipNoiseInString(buffer);
	_opCopyMaxY = parseString(buffer);
	skipNoiseInString(buffer);
	_opCopyMaxX = parseString(buffer);

	// Double X
	_opCopyMinX *= 2;
	_opCopyMaxX *= 2;

	debugC(5, kDebugScript, "opCOPYFB %d %d %d %d", _opCopyMinY, _opCopyMinX, _opCopyMaxY, _opCopyMaxX);
	opCopySurface(_surfaceF, _surfaceB);
}

void CastlxEngine::opCOPYFB(uint16 posX, uint16 posY, uint16 width, uint16 height) {
	_opCopyMinX = posX;
	_opCopyMinY = posY;
	_opCopyMaxX = width;
	_opCopyMaxY = height;

	if (!_opCopyMaxX)
		return;

	opCopySurface(_surfaceF, _surfaceB);
}

void CastlxEngine::opCOPYBV(byte **buffer) { warning("opCOPYBV"); }

/**
 * @brief Opcode: Copy partial surface from surfaceB to surfaceF
 * @param buffer 
*/
void CastlxEngine::opCOPYBF(byte **buffer) {
	skipNoiseInString(buffer);
	_opCopyMinY = parseString(buffer);
	skipNoiseInString(buffer);
	_opCopyMinX = parseString(buffer);
	skipNoiseInString(buffer);
	_opCopyMaxY = parseString(buffer);
	skipNoiseInString(buffer);
	_opCopyMaxX = parseString(buffer);

	// Double X
	_opCopyMinX *= 2;
	_opCopyMaxX *= 2;

	debugC(5, kDebugScript, "opCOPYBF %d %d %d %d", _opCopyMinY, _opCopyMinX, _opCopyMaxY, _opCopyMaxX);
	opCopySurface(_surfaceB, _surfaceF);
}

void CastlxEngine::opCOPYBF(uint16 posX, uint16 posY, uint16 width, uint16 height) {
	_opCopyMinX = posX;
	_opCopyMinY = posY;
	_opCopyMaxX = width;
	_opCopyMaxY = height;

	if (!_opCopyMaxX)
		return;

	opCopySurface(_surfaceB, _surfaceF);
}

/**
 * @brief Opcode: Blit sprite on _surfaceV
 * @param buffer 
*/
void CastlxEngine::opAFFSPRITEV(byte **buffer) {
	skipNoiseInString(buffer);
	int param1 = parseString(buffer);
	skipNoiseInString(buffer);
	int param2 = parseString(buffer);
	skipNoiseInString(buffer);
	int spriteId = parseString(buffer);
	skipNoiseInString(buffer);
	int spriteBank = parseString(buffer);
	if (skipNoiseInString(buffer))
		_byte1E7EA = parseString(buffer);
	else
		_byte1E7EA = 0;

	debugC(5, kDebugScript,"opAFFSPRITEV %d %d %d index: %d [%d]", param1, param2, spriteId, spriteBank, _byte1E7EA);
	
	setSpriteCtrlAndBlitOnSurfaceV(spriteId, spriteBank, param2, param1);
}

/**
 * @brief Opcode: Blit sprite on _surfaceF
 * @param buffer 
*/
void CastlxEngine::opAFFSPRITEF(byte **buffer) {
	skipNoiseInString(buffer);
	int param1 = parseString(buffer);
	skipNoiseInString(buffer);
	int param2 = parseString(buffer);
	skipNoiseInString(buffer);
	int spriteId = parseString(buffer);
	skipNoiseInString(buffer);
	int spriteBank = parseString(buffer);
	if (skipNoiseInString(buffer))
		_byte1E7EA = parseString(buffer);
	else
		_byte1E7EA = 0;

	debug("opAFFSPRITEF %d %d %d index: %d [%d]", param1, param2, spriteId, spriteBank, _byte1E7EA);

	setSpriteCtrlAndBlitOnSurfaceF(spriteId, spriteBank, param2, param1);
}

void CastlxEngine::opAFFSPRITEF(int ax, int bx, int cx, int dx) {
	setSpriteCtrlAndBlitOnSurfaceF(ax, bx, cx, dx);
}


void CastlxEngine::opMODESPRITE(byte **buffer) { warning("opMODESPRITE"); }
void CastlxEngine::opCLEARV(byte **buffer) { warning("opCLEARV"); }
void CastlxEngine::opCLEARF(byte **buffer) { warning("opCLEARF"); }
void CastlxEngine::opOTEPAL(byte **buffer) { warning("opOTEPAL"); }
void CastlxEngine::opMETPAL(byte **buffer) { warning("opMETPAL"); }
void CastlxEngine::opREADMOUSE(byte **buffer) {
	debugC(5,kDebugScript, "opREADMOUSE");
	_oldMousePosX = _mousePosX;
	_oldMousePosY = _mousePosY;
	getMouseStateClipped();
}

/**
 * @brief Opcode: Call the hardcoded logic of the game
 * @param buffer 
*/
void CastlxEngine::opGAME(byte **buffer) {
	skipNoiseInString(buffer);
	int index = parseString(buffer);
	warning("opGAME %d", index);

	_flagEnableHotspots = _mouseButtonStatus;
//	++_mouseCursorVisible;

	if (index == 0) {
		resetDisplayStringList();
		checkOpenInventory();
	}

	(this->*_hardcodedLogic[index])();

	if (index != 0) {
		handleSoundOff();
		setBackgroundHotspot();
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
	debugC(5, kDebugScript, "opTRANSPARENCE");
	if (buffer) {
		_blendingCol1[0] = 110;
		_blendingCol1[1] = 110;
		_blendingCol1[2] = 110;
	}

	createTransparencyMapping();
}

void CastlxEngine::handleExitRoom() {
	warning("STUB handleExitRoom");
}

byte CastlxEngine::sub1DF1D(int param1) {
	warning("STUB - sub1DF1D %d (sound?)", param1);
	return 0;
}

byte CastlxEngine::sub1DFD0(int param1, int param2) {
	warning("STUB - sub1DFD0 %d %d (sound?)", param1, param2);
	return 0;
}

byte CastlxEngine::sub1DF8F() {
	warning("STUB - sub1DF8F (sound?)");
	return 0;
}

byte CastlxEngine::sub1DFC0(int param1, int param2, int param3) {
	warning("STUB - sub1DFC0 %d %d %d (sound?)", param1, param2, param3);
	return 0;
}

byte CastlxEngine::sub1DFDD(int param1, int param2, int param3) {
	warning("STUB - sub1DFDD %d %d %d (sound?)", param1, param2, param3);
	return 0;
}

byte CastlxEngine::sub1E01E() {
	warning("STUB - sub1E01E (sound?)");
	return 0;
}

byte CastlxEngine::sub1E033(int type, int param1, int param2, int param3) {
	switch (type) {
	case 0:
		return sub1DF1D(param1);
	case 1:
		return sub1DFD0(param1, param2);		
	case 2:
		return sub1DF8F();
	case 3:
		return sub1DFC0(param1, param2, param3);
	case 4:
		return sub1DFDD(param1, param2, param3);
	case 5:
		return sub1E01E();
	default:
		error("sub1E033 - unexpected type");
	}
}

void CastlxEngine::loadBackgroundAndSprites() {
	warning("STUB loadBackgroundAndSprites");
	opOTEPALETTE(0, 256);
	_filename = Common::String::format("I%02d.IMG", _unkSpriteNumber);
	opLOADIMG();
	opCOPYFV(0, 0, 640, 400);
	opRAZSPR(1);
	_filename = Common::String::format("S%02d.SPR", _unkSpriteNumber);
	opLOADSPR(1);
	opRAZSPR(2);
	_filename = "S91.SPR"; // inventory sprites?
	opLOADSPR(2);
	_filename = "P90.PAL";
	opLOADPALETTE(219);
	for (int i = 0; i < 3; ++i)
		_unkPalette[i] = 0;

	_system->getPaletteManager()->setPalette(_unkPalette, 0, 256);

	opCOPYFV(0, 0, 640, 400);
	_system->copyRectToScreen((const byte *)_surfaceF->getBasePtr(0, 0), _surfaceF->pitch, 0, 0, 640, 400);
	_system->updateScreen();
}

void CastlxEngine::sub12BD6(int param) {
	// CHECKME : This uses index instead of pointer for bx.
	opAFFSPRITEF(param, 1, 0, 0);

	byte *curBankPtr = _spritePtr[_spriteCtrl._spriteBank - 1];
	uint16 startPos = READ_LE_UINT16(&curBankPtr[8 * _spriteCtrl._spriteId]);
	uint16 size = READ_LE_UINT16(&curBankPtr[8 * _spriteCtrl._spriteId] + 4) * READ_LE_UINT16(&curBankPtr[8 * _spriteCtrl._spriteId] + 6);

	byte *curSprite = &curBankPtr[startPos];
	uint32 sign = READ_LE_UINT32(curSprite);
	if (sign != MKTAG('N', 'E', 'X', 'T'))
		error("Invalid signature");

	uint16 posY = READ_LE_UINT32(curSprite + 4);
	uint16 posX = READ_LE_UINT32(curSprite + 6);
	uint16 height = READ_LE_UINT32(curSprite + 8);
	uint16 width = READ_LE_UINT32(curSprite + 10);

	opCOPYFB(posX, posY, width, height);
}

void CastlxEngine::initRoom00() {
	debug("initRoom00");
	if (_ageChecked) {
		cleanEvents();
		sub12CAF();
		return;
	}

	_ageChecked = true;
	cleanEvents();
	++_displayMessageRect;

	displayInfoMessage(&_infoC068, 92, 250);
	_displayMessageRect = 0;

	do {
		getEvents();
		
		if (_lastEvent.type == Common::EVENT_KEYUP && (_lastEvent.kbd.keycode == Common::KEYCODE_o || _lastEvent.kbd.keycode == Common::KEYCODE_y)) {
			cleanEvents();
			sub12CAF();
			return;
		}
	} while (!(_lastEvent.type == Common::EVENT_KEYUP && _lastEvent.kbd.keycode == Common::KEYCODE_n));

	displayInfoMessage(&_infoC0DA, 68, 200);
	cleanEvents();

	// TODO = check int8Counter3 + key pressed

	sub12CAF();
	handleExitRoom();
	fadeInPalette2();

	error("TODO exit game");
}

void CastlxEngine::initRoom01() {
	debugC(5, kDebugScript, "STUB initRoom01");
	if (!_flagUseTits)
		sub12BD6(1);

	if (!_flagTakeSeed)
		sub12BD6(2);

	loc12BFA();

	_paletteFctStart = 0;
	_paletteFctCounter = 256;
	fadeInPalette2();

	_blendingCol1[0] = _blendingCol1[1] = _blendingCol1[2] = 110;
	opTRANSPARENCE(nullptr);
	opCOPYVB(0, 0, 640, 400);
	opCOPYVF(0, 0, 640, 400);
	_int8Counter3 = 0;	
}

void CastlxEngine::initRoom02() { warning("STUB initRoom02"); }
void CastlxEngine::initRoom03() { warning("STUB initRoom03"); }
void CastlxEngine::initRoom04() { warning("STUB initRoom04"); }
void CastlxEngine::initRoom05() { warning("STUB initRoom05"); }
void CastlxEngine::initRoom06() { warning("STUB initRoom06"); }
void CastlxEngine::initRoom07() { warning("STUB initRoom07"); }
void CastlxEngine::initRoom08() { warning("STUB initRoom08"); }
void CastlxEngine::initRoom09() { warning("STUB initRoom09"); }
void CastlxEngine::initRoom10() { warning("STUB initRoom10"); }
void CastlxEngine::initRoom11() { warning("STUB initRoom11"); }
void CastlxEngine::initRoom12() { warning("STUB initRoom12"); }
void CastlxEngine::initRoom13() { warning("STUB initRoom13"); }

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

void CastlxEngine::hlInit() {
	int room = _defineArray[0]._value;
	warning("hlInit %d", room);
	switch (room) {
	case 0:
		initRoom00();
		return;
	case 100:
		if (!_byte2C0BC || !_activeSoundFl) {
			_word2C0A8 = 0;
			// the rest is part of a function
			handleExitRoom();
			sub1E033(1, 0, 0, _word2C0AA[_word2C0A8]);
			sub1E033(3, 0, 0x80, 0x2800);
			_byte2C0BE = 1;
			_byte2C0BC = 1;
		}
		_byte2C0F3 = 0;
		return;
	case 101:
		handleExitRoom();
		return;
	default:
		break;
	}

	_unkSpriteNumber = room;
	loadBackgroundAndSprites();

	_system->delayMillis(5000);
	
	switch (room) {
	case 1:
		initRoom01();
		break;
	case 2:
		initRoom02();
		break;
	case 3:
		initRoom03();
		break;
	case 4:
		initRoom04();
		break;
	case 5:
		initRoom05();
		break;
	case 6:
		initRoom06();
		break;
	case 7:
		initRoom07();
		break;
	case 8:
		initRoom08();
		break;
	case 9:
		initRoom09();
		break;
	case 10:
		initRoom10();
		break;
	case 11:
		initRoom11();
		break;
	case 12:
		initRoom12();
		break;
	case 13:
		initRoom13();
		break;
	default:
		error("Unexpected room %d", room);
	}
}
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
	_hardcodedLogic[0] = &CastlxEngine::hlInit;
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

void CastlxEngine::checkExit() {
	debugC(9, kDebugScan, "checkExit");
	getEvents();

	if (!(_lastEvent.type == Common::EVENT_KEYUP && _lastEvent.kbd.hasFlags(Common::KBD_CTRL)))
		return;
	
	if (_lastEvent.kbd.keycode == Common::KEYCODE_c || _lastEvent.kbd.keycode == Common::KEYCODE_x)
		error("TODO: checkExit - Exit game");

	// The original game also check for ctrl-alt-del
}

void CastlxEngine::sub1024E() {
	if (!_keyPressed[25])
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
			debugC(1, kDebugScript, "Handle GST - Comment : %s", comment.c_str());
		}

		if (curByte <= ' ') {
			++_curGstPtr;
			continue;
		}

		checkExit();
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
	// Initialize 640x400 paletted graphics mode
	initGraphics(640, 400);
	_screen = new Graphics::Screen();
	_rnd.setSeed(g_system->getMillis()); // Kick random number generator

	// Set the engine's debugger console
	setDebugger(new Console());

	// If a savegame was selected from the launcher, load it
	int saveSlot = ConfMan.getInt("save_slot");
	if (saveSlot != -1)
		(void)loadGameState(saveSlot);

	initOpcodes();
	initHardcodedLogic();
	
	initMouse(0, 0, 629, 399);
	setMousePosition(640, 100);
	initDisplayMode();
	
	/*
	sub1AC99();
	*/

	_byte2C0BF = sub1E033(0, 0, -1,-1);
	
	Common::String filename = "SONG0.OUT";
	_song0 = loadFile(filename);
	filename = "SONG1.OUT";
	_song1 = loadFile(filename);

	loadGst(0);
	cleanEvents();
	_int8Counter3 = 0;

	handleGst(&_word2A302);
	
	// Draw a series of boxes on screen as a sample
	for (int i = 0; i < 120; ++i)
		_screen->frameRect(Common::Rect(i, i, 640 - i, 400 - i), i);
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
