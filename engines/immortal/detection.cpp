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

#include "base/plugins.h"
#include "engines/advancedDetector.h"
#include "common/textconsole.h"

#include "immortal/detection.h"

namespace Immortal {

static const PlainGameDescriptor immortalGames[] = {
	// Games
	{"immortal", "The Immortal"},
	{0, 0}
};

static const ImmortalGameDescription gameDescriptions[] = {

	// The Immortal English
	{
		{
			"immortal", 0, AD_ENTRY2s("IMM1.LIB", "45933f560d9c55384e10b9a7fb797026", 181166, "IMM2.lib", "ba0aa7459cff483df34506303c8b9889", 362044),
			Common::EN_ANY,
			Common::kPlatformDOS,
			ADGF_UNSTABLE,
			GUIO0()
		},
		kGameTypeImmortal
	},
	{AD_TABLE_END_MARKER, kGameTypeNone}
};

class ImmortalMetaEngineDetection : public AdvancedMetaEngineDetection {
public:
	ImmortalMetaEngineDetection() : AdvancedMetaEngineDetection(gameDescriptions, sizeof(ImmortalGameDescription), immortalGames) {
	}

	const char *getEngineId() const override {
		return "immortal";
	}

	const char *getName() const override {
		return "Immortal";
	}

	const char *getOriginalCopyright() const override {
		return "The Immortal (C) SandCastle, Electronic Arts, 1990-1991";
	}
};

} // End of namespace immortal

REGISTER_PLUGIN_STATIC(IMMORTAL_DETECTION, PLUGIN_TYPE_ENGINE_DETECTION, Immortal::ImmortalMetaEngineDetection);
