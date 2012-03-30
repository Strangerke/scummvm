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
#include "common/events.h"
#include "common/debug-channels.h"
#include "common/config-manager.h"
#include "common/textconsole.h"

#include "robin/robin.h"

#include "engines/util.h"

namespace Robin {

RobinEngine *RobinEngine::s_Engine = 0;

RobinEngine::RobinEngine(OSystem *syst, const RobinGameDescription *gd) : Engine(syst), _gameDescription(gd)
{
	_system = syst;
	DebugMan.addDebugChannel(kDebugSchedule, "Schedule", "Script Schedule debug level");
	DebugMan.addDebugChannel(kDebugEngine, "Engine", "Engine debug level");
	DebugMan.addDebugChannel(kDebugDisplay, "Display", "Display debug level");
	DebugMan.addDebugChannel(kDebugMouse, "Mouse", "Mouse debug level");
	DebugMan.addDebugChannel(kDebugParser, "Parser", "Parser debug level");
	DebugMan.addDebugChannel(kDebugFile, "File", "File IO debug level");
	DebugMan.addDebugChannel(kDebugRoute, "Route", "Route debug level");
	DebugMan.addDebugChannel(kDebugInventory, "Inventory", "Inventory debug level");
	DebugMan.addDebugChannel(kDebugObject, "Object", "Object debug level");
	DebugMan.addDebugChannel(kDebugMusic, "Music", "Music debug level");

	_console = new RobinConsole(this);
	_rnd = 0;
}

RobinEngine::~RobinEngine() {

	DebugMan.clearAllDebugChannels();
	delete _console;
	delete _rnd;
}

GUI::Debugger *RobinEngine::getDebugger() {
	return _console;
}

bool RobinEngine::hasFeature(EngineFeature f) const {
	return (f == kSupportsRTL) || (f == kSupportsLoadingDuringRuntime) || (f == kSupportsSavingDuringRuntime);
}

const char *RobinEngine::getCopyrightString() const {
	return "Copyright 1989-1997 David P Gray, All Rights Reserved.";
}

GameType RobinEngine::getGameType() const {
	return _gameType;
}

Common::Platform RobinEngine::getPlatform() const {
	return _platform;
}

Common::Error RobinEngine::run() {
	s_Engine = this;
	initGraphics(320, 200, false);
	_console = new Console(this);

//	_mouse = new MouseHandler(this);

	// Setup mixer
	syncSoundSettings();

	return Common::kNoError;
}

void RobinEngine::initialize() {
	debugC(1, kDebugEngine, "initialize");

	_rnd = new Common::RandomSource("robin");
	_rnd->setSeed(42);                              // Kick random number generator
}

void RobinEngine::syncSoundSettings() {
	Engine::syncSoundSettings();

//	_sound->syncVolume();
}

Common::String RobinEngine::getSavegameFilename(int slot) {
	return _targetName + Common::String::format("-%02d.SAV", slot);
}



} // End of namespace Robin
