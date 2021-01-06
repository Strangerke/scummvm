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

#include "common/system.h"
#include "common/random.h"
#include "common/error.h"
#include "common/config-manager.h"
#include "common/events.h"
#include "engines/util.h"
#include "graphics/cursorman.h"

#include "immortal/immortal.h"
#include "engines/util.h"

namespace Immortal {

ImmortalEngine *ImmortalEngine::s_Engine = 0;

ImmortalEngine::ImmortalEngine(OSystem *syst, const ImmortalGameDescription *gd) : Engine(syst), _gameDescription(gd) {
	_system = syst;
	_rnd = nullptr;

	_shouldQuit = false;
	_eventMan = nullptr;
	_lastTime = 0;
	_gameType = kGameTypeNone;
	_platform = Common::kPlatformUnknown;
	_mainSurface = nullptr;

	_Gmode = 0;
	_SoundType = 0;

	gameOverFlag = false;
	levelOver = false;
}

ImmortalEngine::~ImmortalEngine() {
	delete _rnd;
}

bool ImmortalEngine::hasFeature(EngineFeature f) const {
	return (f == kSupportsReturnToLauncher) || (f == kSupportsLoadingDuringRuntime) || (f == kSupportsSavingDuringRuntime);
}

const char *ImmortalEngine::getCopyrightString() const {
	return "The Immortal (C) SandCastle, Electronic Arts, 1990-1991";
}

GameType ImmortalEngine::getGameType() const {
	return _gameType;
}

Common::Platform ImmortalEngine::getPlatform() const {
	return _platform;
}

/**
 * Flag-based LZSS Decoder with integrated dictionary for files in *.LIB.
 *
 * @param inBuffer encoded file buffer
 * @param encodedFilesize size of the encoded file
 * @param decodedFilesize size of the decoded file
 * @return decoded file buffer
 */
byte *ImmortalEngine::decodeFile(byte *inBuffer, int encodedFilesize, int *decodedFilesize) {
	byte lzwBuffer[4096] = {};
	byte *outBuffer = nullptr;
	int lzwBufferIndex = sizeof(lzwBuffer) - 18;
	int inBufferIndex = 0;
	int outBufferIndex = 0;
	int flags = 0;

	memset(lzwBuffer, '\0', lzwBufferIndex);
	int fileSize = READ_LE_INT32(inBuffer);
	if (decodedFilesize)
		*decodedFilesize = fileSize;
	inBuffer += 4;
	outBuffer = new byte[fileSize];

	while (inBufferIndex < encodedFilesize && outBufferIndex < fileSize) {
		flags >>= 1;
		if ((flags & 0x100) == 0)
			flags = 0xFF00 | inBuffer[inBufferIndex++];

		if (flags & 1) {
			byte tmp = inBuffer[inBufferIndex++];
			outBuffer[outBufferIndex++] = tmp;
			lzwBuffer[lzwBufferIndex++] = tmp;
			lzwBufferIndex &= sizeof(lzwBuffer) - 1;
			continue;
		}

		int seqPosition = inBuffer[inBufferIndex++];
		int seqLength = inBuffer[inBufferIndex++];
		seqPosition |= ((seqLength & 0xF0) << 4);
		seqLength = (seqLength & 0xF) + 3; // sequence pos and length + terminator?

		for (; seqLength != 0; --seqLength) {
			seqPosition &= sizeof(lzwBuffer) - 1;
			byte c = lzwBuffer[seqPosition++];
			lzwBuffer[lzwBufferIndex++] = c;
			lzwBufferIndex &= sizeof(lzwBuffer) - 1;
			outBuffer[outBufferIndex++] = c;
		}
	}

	return outBuffer;
}

byte *ImmortalEngine::Load(Common::String filename, uint32 *destSize) {
	/****************************************************************
	in zparm0, 1 load address;
	zparm2, 3 nameptr;
	out c error;
	X dos error code;
	Y file type;
	zparm0, 1 pointer unchanged;
	zparm2 after file;
	zparm6 length of file
*/
	CurLibHand.seek(0, SEEK_SET);
	uint32 sign = CurLibHand.readUint32BE();
	if (sign != MKTAG('E', 'A', 'L', 'I'))
		error("LIB File - Bad signature");
	CurLibHand.skip(1); // the original skips the end of signature ('B')

	uint16 numb = CurLibHand.readUint16LE();
	byte *dest = nullptr;
	*destSize = 0;
	
	for (int i = 0; i < numb + 1; ++i) { // Last record doesn't contain file name but contains the end address
		Common::String curName;
		for (int j = 0; j < 13; ++j)
			curName += CurLibHand.readByte();

		uint8 unk1 = CurLibHand.readByte(); // 1 = file, 0 = dummy record ?
		uint32 pos = CurLibHand.readUint32LE();

		if (filename.compareToIgnoreCase(curName) == 0) {
			CurLibHand.skip(13);
			unk1 = CurLibHand.readByte();
			uint32 endPos = CurLibHand.readUint32LE();
			uint32 size = endPos - pos;
			byte *buffer = new byte[size];
			CurLibHand.seek(pos);
			CurLibHand.read(buffer, size);
			int realSize;
			
			dest = decodeFile(buffer, size, &realSize);
			*destSize = realSize;
			
			Common::DumpFile test;
			test.open(curName);
			test.write(dest, realSize);
			test.flush();
			test.close();
			break;
		}
	}

	if (!dest)
		error("File %s not found in LIB file", filename.c_str());

	return dest;
}

byte *ImmortalEngine::LoadIff(Common::String filename, uint32 *bufSize) {
	// zparam0/1 = load address, zparam2/3 = filename
	// return : zparam2/3 : after file, zparam4/5: ptr after form header, zparam6: size

	return Load(filename, bufSize);
}

void ImmortalEngine::convertPaletteToRGB(int palColor, byte *red, byte *green, byte *blue) {
	*blue = ((palColor & 0xF)) * 16;
	*green = ((palColor & 0xF0) >> 4) * 16;
	*red = ((palColor & 0xF00) >> 8) * 16;
}

void ImmortalEngine::SetTitlePal() {
	uint16 titlePal[16] = {0x0000, 0x0007, 0x0363, 0x00aa, 0x0a00, 0x0999, 0x090a, 0x0cbb, 0x0555, 0x085f, 0x0995, 0x05ff, 0x0f33, 0x0b6f, 0x0cc4, 0x0fff};

	byte convertedPalette[48] = {};
	for (int i = 0; i < 16; ++i) {
		byte *dest = &convertedPalette[i * 3];
		convertPaletteToRGB(titlePal[i], dest, dest + 1, dest + 2);
	}
	g_system->getPaletteManager()->setPalette(convertedPalette, 0, 16);
}

void ImmortalEngine::ConvertPic(byte *buffer) {
	// No implementation required : MCGA
}

void ImmortalEngine::ShowPic(byte *buffer, uint32 size) {
	warning("ShowPic");

	byte *convertedBuffer = new byte[size * 2];
	byte *itSource = buffer;
	byte *itDest = convertedBuffer;
	for (int y = 0; y < 200; ++y) {
		for (int x = 0; x < 320 / 2; ++x, ++itSource) {
			byte pixel = *itSource & 0xF0;
			*itDest++ = (pixel >> 4);
			pixel = *itSource & 0x0F;
			*itDest++ = pixel;
		}
	}

	_mainSurface->copyRectToSurface(convertedBuffer, 320, 0, 0, 320, 200);
}

void ImmortalEngine::D_loadtitle() {
	Common::String filename = "IMM1.LIB";
	if (!CurLibHand.open(filename.c_str()))
		error("Unable to open IMM1.LIB.");

	// zparam0/1 = load address, zparam2/3 = filename
	// return : zparam2/3 : after file, zparam4/5: ptr after form header, zparam6: size
	uint32 titleSize;
	byte *titleBuf = LoadIff("TITLEVGA.BM", &titleSize);
	SetTitlePal();
	ConvertPic(titleBuf);
	ShowPic(titleBuf, titleSize);
	delete titleBuf;
}

void ImmortalEngine::kernal_loadSprites() {
	warning("STUB - kernal_loadSprites");
}

void ImmortalEngine::loadwindow() {
	warning("STUB - loadwindow");
}

void ImmortalEngine::kernal_loadmaze(int mazeNumber) {
	warning("STUB - kernal_loadmaze");
}

void ImmortalEngine::kernal_usenormal() {
	warning("STUB - kernal_usenormal");
}

void ImmortalEngine::initmusic() {
	warning("STUB - initmusic");
}

void ImmortalEngine::inituserio() {
	warning("STUB - inituserio");
}

void ImmortalEngine::kernal_loadSingles() {
	warning("STUB - kernal_loadSingles");
}

void ImmortalEngine::MusicDriver_TuneOn() {
	warning("STUB - MusicDriver_TuneOn");
}

void ImmortalEngine::kernal_clearSprites() {
	warning("STUB - kernal_clearSprites");
}

void ImmortalEngine::logic_init() {
	warning("STUB - logic_init");
}

void ImmortalEngine::logic() {
	warning("STUB - logic");
}

bool ImmortalEngine::logic_freeze() {
	return !(gameOverFlag | levelOver);
}

void ImmortalEngine::D_drawuniv() {
	warning("STUB - D_drawuniv");
}

void ImmortalEngine::IBMPoll() {
	warning("STUB - IBMPoll");
}

void ImmortalEngine::setcolors() {
	warning("STUB - setcolors");
}

Common::Error ImmortalEngine::run() {
	s_Engine = this;
	initialize();

	initGraphics(320, 200);

	_mainSurface = new Graphics::Surface();
	_mainSurface->create(320, 200, Graphics::PixelFormat::createFormatCLUT8());
/*
	// Setup mixer
	syncSoundSettings();
	_soundHandler->init();

	CursorMan.replaceCursor(_normalCursor, 16, 16, 0, 0, 0);
	CursorMan.showMouse(true);
*/

	_Gmode = 3;     // MCGA
	_SoundType = 1; // AdLib

	D_loadtitle(); // load in title screen
	kernal_loadSprites();
	loadwindow();
	kernal_loadmaze(0);
	kernal_usenormal(); // bgd

	soundon = 1; //initially sound is on
	gotjoystick = 0;
	PlayerInv = 0;
	initmusic();
	inituserio();
	kernal_loadSingles();

	// Useless : Check for lib2 and request disk
	//CHECKME: set pheap +2 to Titleptr
	MusicDriver_TuneOn();
	//CHECKME: MusictPtr is set to pheap+2

	kernal_clearSprites();
	dim = 0;
	lastdim = 0;

	logic_init();

	do {
		jiffies = 0;
		logic();
		if (logic_freeze()) {
			D_drawuniv();

			gotjoystick = 0;
			IBMPoll();
			setcolors();
		}

		_system->copyRectToScreen((byte *)_mainSurface->getPixels(), 320, 0, 0, 320, 200);
		_system->updateScreen();
		_system->delayMillis(20);

		while (jiffies <= 4) {
		} // CHECKME : Endless loop? check if modified by keyboard or timer

	} while (true);
	
	return Common::kNoError;
}

void ImmortalEngine::initialize() {
	_rnd = new Common::RandomSource("immortal");
	_rnd->setSeed(42);                              // Kick random number generator
	_shouldQuit = false;
}


void ImmortalEngine::syncSoundSettings() {
	Engine::syncSoundSettings();

//	_sound->syncVolume();
}

Common::String ImmortalEngine::getSavegameFilename(int slot) {
	return _targetName + Common::String::format("-%02d.SAV", slot);
}

} // End of namespace Immortal
