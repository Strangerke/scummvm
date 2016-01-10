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
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef LALAW_LALAW_H
#define LALAW_LALAW_H

#include "lalaw/debugger.h"
#include "common/scummsys.h"
#include "common/system.h"
#include "common/error.h"
#include "common/random.h"
#include "common/savefile.h"
#include "common/serializer.h"
#include "common/util.h"
#include "engines/engine.h"
#include "graphics/surface.h"

/**
 * This is the namespace of the Lalaw engine.
 *
 * Status of this engine: WIP
 *
 * Games using this engine:
 * - L.A. Law (Dos)
 */
namespace Lalaw {

#define DEBUG_BASIC 1
#define DEBUG_INTERMEDIATE 2
#define DEBUG_DETAILED 3

enum LalawDebugChannels {
	kDebugScripts	= 1 << 0
};

struct LalawGameDescription;

class LalawEngine : public Engine {
private:
	const LalawGameDescription *_gameDescription;
	Common::RandomSource _randomSource;

	/**
	 * Synchronizes the game data
	 */
	void synchronize(Common::Serializer &s);

protected:
	// Engine APIs
	virtual Common::Error run();
	virtual bool hasFeature(EngineFeature f) const;
public:
	Debugger *_debugger;

	int _loadGameSlot;
public:
	LalawEngine(OSystem *syst, const LalawGameDescription *gameDesc);
	virtual ~LalawEngine();

	uint32 getFeatures() const;
	Common::Language getLanguage() const;
	Common::Platform getPlatform() const;
	uint16 getVersion() const;
	bool getIsDemo() const;

	int getRandomNumber(int maxNumber);
	Common::String generateSaveName(int slotNumber);
	virtual bool canLoadGameStateCurrently();
	virtual bool canSaveGameStateCurrently();
	virtual Common::Error loadGameState(int slot);
	virtual Common::Error saveGameState(int slot, const Common::String &desc);
	void loadGame(int slot);
};

#define LALAW_SAVEGAME_VERSION 1

/**
 * Header for Lalaw savegame files
 */
struct LalawSavegameHeader {
	uint8 _version;
	Common::String _saveName;
	Graphics::Surface *_thumbnail;

	/**
	 * Read in the header from the specified file
	 */
	bool read(Common::InSaveFile *f);

	/**
	 * Write out header information to the specified file
	 */
	void write(Common::OutSaveFile *f, LalawEngine *vm, const Common::String &saveName);
};

} // End of namespace Lalaw

#endif /* LALAW_LALAW_H */
