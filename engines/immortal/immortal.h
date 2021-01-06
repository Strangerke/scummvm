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

#ifndef IMMORTAL_IMMORTAL_H
#define IMMORTAL_IMMORTAL_H

#include "immortal/detection.h"

#include "common/file.h"
#include "common/rect.h"
#include "common/events.h"

#include "engines/engine.h"
#include "graphics/palette.h"
#include "graphics/surface.h"

namespace Common {
class RandomSource;
}

/**
 * This is the namespace of the Immortal engine.
 *
 * Status of this engine:
 * - Adventures of Robin Hood is mostly working without sound
 *
 * Games using this engine:
 * - Adventures of Robin Hood
 * - Rome: Pathway to Rome
 */
namespace Immortal {

static const int kSavegameVersion = 1;

struct ImmortalGameDescription;

class ImmortalEngine : public Engine {
public:
	ImmortalEngine(OSystem *syst, const ImmortalGameDescription *gd);
	~ImmortalEngine() override;

	OSystem *_system;
	Graphics::Surface *_mainSurface;
	Common::RandomSource *_rnd;

	const ImmortalGameDescription *_gameDescription;
	uint32 getFeatures() const;
	const char *getGameId() const;

	void initGame(const ImmortalGameDescription *gd);
	GameType getGameType() const;
	Common::Platform getPlatform() const;

	bool hasFeature(EngineFeature f) const override;
	const char *getCopyrightString() const;

	Common::String getSavegameFilename(int slot);
	void syncSoundSettings() override;

	bool _shouldQuit;

protected:
	Common::EventManager *_eventMan;
	int _lastTime;

	// Engine APIs
	Common::Error run() override;
	void handleMenu();

private:
	static ImmortalEngine *s_Engine;

	GameType _gameType;
	Common::Platform _platform;

	int _Gmode;
	int _SoundType;
	int soundon;
	int gotjoystick;
	int PlayerInv;
	int dim;
	int lastdim;
	int jiffies;
	bool gameOverFlag;
	bool levelOver;
	Common::File CurLibHand;
	
	void initialize();

	void convertPaletteToRGB(int palColor, byte *red, byte *green, byte *blue);

	void D_loadtitle();
	void kernal_loadSprites();
	void loadwindow();
	void kernal_loadmaze(int mazeNumber);
	void kernal_usenormal();
	void initmusic();
	void inituserio();
	void kernal_loadSingles();
	void MusicDriver_TuneOn();
	void kernal_clearSprites();
	void logic_init();
	void logic();
	bool logic_freeze();
	void D_drawuniv();
	void IBMPoll();
	void setcolors();
	byte *LoadIff(Common::String filename, uint32 *bufSize);
	void SetTitlePal();
	void ConvertPic(byte *buffer);
	void ShowPic(byte *buffer, uint32 size);
	byte *Load(Common::String filename, uint32 * size);
	byte *decodeFile(byte * inBuffer, int encodedFilesize, int *decodedFilesize);
};

} // End of namespace Immortal

#endif
