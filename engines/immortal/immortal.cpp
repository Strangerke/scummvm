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
