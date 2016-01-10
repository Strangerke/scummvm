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

#include "lalaw/lalaw.h"
#include "common/scummsys.h"
#include "common/config-manager.h"
#include "common/debug-channels.h"
#include "graphics/palette.h"
#include "graphics/scaler.h"
#include "graphics/thumbnail.h"

namespace Lalaw {

LalawEngine::LalawEngine(OSystem *syst, const LalawGameDescription *gameDesc) : Engine(syst),
		_gameDescription(gameDesc), _randomSource("Lalaw") {
	_debugger = nullptr;

	_loadGameSlot = -1;

	DebugMan.addDebugChannel(kDebugScripts, "scripts", "Game scripts");
	_debugger = new Debugger(this);
}

LalawEngine::~LalawEngine() {
	delete _debugger;
}

Common::Error LalawEngine::run() {
	return Common::kNoError;
}


int LalawEngine::getRandomNumber(int maxNumber) {
	return _randomSource.getRandomNumber(maxNumber);
}

/*------------------------------------------------------------------------*/

Common::String LalawEngine::generateSaveName(int slot) {
	return Common::String::format("%s.%03d", _targetName.c_str(), slot);
}

/**
 * Returns true if it is currently okay to restore a game
 */
bool LalawEngine::canLoadGameStateCurrently() {
	warning("STUB: canLoadGameStateCurrently()");
	return false;
}

/**
 * Returns true if it is currently okay to save the game
 */
bool LalawEngine::canSaveGameStateCurrently() {
	warning("STUB: canSaveGameStateCurrently()");
	return false;
}

/**
 * Load the savegame at the specified slot index
 */
Common::Error LalawEngine::loadGameState(int slot) {
	_loadGameSlot = slot;
	return Common::kNoError;
}

void LalawEngine::loadGame(int slot) {
	// Open up the save file
	Common::InSaveFile *saveFile = g_system->getSavefileManager()->openForLoading(generateSaveName(slot));
	if (!saveFile)
		return;

	Common::Serializer serializer(saveFile, NULL);

	// Read in the savegame header
	LalawSavegameHeader header;
	if (!header.read(saveFile))
		return;
	if (header._thumbnail)
		header._thumbnail->free();
	delete header._thumbnail;

	synchronize(serializer);

	delete saveFile;
}

/**
 * Save the game to the given slot index, and with the given name
 */
Common::Error LalawEngine::saveGameState(int slot, const Common::String &desc) {
	// Open the save file for writing
	Common::OutSaveFile *saveFile = g_system->getSavefileManager()->openForSaving(generateSaveName(slot));
	if (!saveFile)
		return Common::kCreatingFileFailed;

	// Write out the header
	LalawSavegameHeader header;
	header.write(saveFile, this, desc);

	// Set up a serializer
	Common::Serializer serializer(NULL, saveFile);

	// Synchronise the data
	synchronize(serializer);

	saveFile->finalize();
	delete saveFile;

	return Common::kNoError;
}

void LalawEngine::synchronize(Common::Serializer &s) {
	warning("STUB: synchronize");
}

/*------------------------------------------------------------------------*/

bool LalawSavegameHeader::read(Common::InSaveFile *f) {
	_thumbnail = NULL;

	uint32 signature = f->readUint32BE();
	if (signature != MKTAG('L', 'L', 'A', 'W')) {
		warning("Invalid savegame");
		return false;
	}

	_version = f->readByte();
	if (_version > LALAW_SAVEGAME_VERSION)
		return false;

	char c;
	_saveName = "";
	while ((c = f->readByte()) != 0)
		_saveName += c;

	// Get the thumbnail
	_thumbnail = Graphics::loadThumbnail(*f);
	if (!_thumbnail)
		return false;

	return true;
}

void LalawSavegameHeader::write(Common::OutSaveFile *f, LalawEngine *vm, const Common::String &saveName) {
	// Write ident string
	f->writeUint32BE(MKTAG('L', 'L', 'A', 'W'));

	// Write out savegame version
	f->writeByte(LALAW_SAVEGAME_VERSION);

	// Write out savegame name
	f->write(saveName.c_str(), saveName.size());
	f->writeByte(0);

	// Create a thumbnail and save it
	Graphics::Surface *thumb = new Graphics::Surface();
	warning("TODO: createThumbnail");
	//::createThumbnail(thumb, (byte *)vm->_graphicsManager->_screenSurface.getPixels(),
	//	SCREEN_WIDTH, SCREEN_HEIGHT, vm->_graphicsManager->_VGAColors);
	Graphics::saveThumbnail(*f, *thumb);
	thumb->free();
	delete thumb;
}

} // End of namespace Lalaw
