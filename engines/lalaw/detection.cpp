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

#include "base/plugins.h"
#include "common/savefile.h"
#include "common/str-array.h"
#include "common/memstream.h"
#include "engines/advancedDetector.h"
#include "common/system.h"
#include "graphics/colormasks.h"
#include "graphics/surface.h"

#define MAX_SAVES 99

namespace Lalaw {

struct LalawGameDescription {
	ADGameDescription desc;
};

uint32 LalawEngine::getFeatures() const {
	return _gameDescription->desc.flags;
}

Common::Language LalawEngine::getLanguage() const {
	return _gameDescription->desc.language;
}

Common::Platform LalawEngine::getPlatform() const {
	return _gameDescription->desc.platform;
}

bool LalawEngine::getIsDemo() const {
	return _gameDescription->desc.flags & ADGF_DEMO;
}

} // End of namespace Lalaw

static const PlainGameDescriptor lalawGames[] = {
	{"lalaw", "L.A. Law"},
	{0, 0}
};

#include "lalaw/detection_tables.h"

class LalawMetaEngine : public AdvancedMetaEngine {
public:
	LalawMetaEngine() : AdvancedMetaEngine(Lalaw::gameDescriptions, sizeof(Lalaw::LalawGameDescription), lalawGames) {
		_maxScanDepth = 3;
	}

	virtual const char *getName() const {
		return "Lalaw Engine";
	}

	virtual const char *getOriginalCopyright() const {
		return "Lalaw (c) Capstone 1992";
	}

	virtual bool hasFeature(MetaEngineFeature f) const;
	virtual bool createInstance(OSystem *syst, Engine **engine, const ADGameDescription *desc) const;
	virtual SaveStateList listSaves(const char *target) const;
	virtual int getMaximumSaveSlot() const;
	virtual void removeSaveState(const char *target, int slot) const;
	SaveStateDescriptor querySaveMetaInfos(const char *target, int slot) const;
};

bool LalawMetaEngine::hasFeature(MetaEngineFeature f) const {
	return
		(f == kSupportsListSaves) ||
		(f == kSupportsLoadingDuringStartup) ||
		(f == kSupportsDeleteSave) ||
		(f == kSavesSupportMetaInfo) ||
		(f == kSavesSupportThumbnail);
}

bool Lalaw::LalawEngine::hasFeature(EngineFeature f) const {
	return
		(f == kSupportsRTL) ||
		(f == kSupportsLoadingDuringRuntime) ||
		(f == kSupportsSavingDuringRuntime);
}

bool LalawMetaEngine::createInstance(OSystem *syst, Engine **engine, const ADGameDescription *desc) const {
	const Lalaw::LalawGameDescription *gd = (const Lalaw::LalawGameDescription *)desc;
	if (gd) {
		*engine = new Lalaw::LalawEngine(syst, gd);
	}
	return gd != 0;
}

SaveStateList LalawMetaEngine::listSaves(const char *target) const {
	Common::SaveFileManager *saveFileMan = g_system->getSavefileManager();
	Common::StringArray filenames;
	Common::String saveDesc;
	Common::String pattern = Common::String::format("%s.0??", target);

	filenames = saveFileMan->listSavefiles(pattern);
	sort(filenames.begin(), filenames.end());   // Sort to get the files in numerical order

	SaveStateList saveList;
	Lalaw::LalawSavegameHeader header;

	for (Common::StringArray::const_iterator file = filenames.begin(); file != filenames.end(); ++file) {
		const char *ext = strrchr(file->c_str(), '.');
		int slot = ext ? atoi(ext + 1) : -1;

		if (slot >= 0 && slot <= MAX_SAVES) {
			Common::InSaveFile *in = g_system->getSavefileManager()->openForLoading(*file);

			if (in) {
				if (header.read(in)) {
					saveList.push_back(SaveStateDescriptor(slot, header._saveName));
					header._thumbnail->free();
				}
				delete in;
			}
		}
	}

	return saveList;
}

int LalawMetaEngine::getMaximumSaveSlot() const {
	return MAX_SAVES;
}

void LalawMetaEngine::removeSaveState(const char *target, int slot) const {
	Common::String filename = Common::String::format("%s.%03d", target, slot);
	g_system->getSavefileManager()->removeSavefile(filename);
}

SaveStateDescriptor LalawMetaEngine::querySaveMetaInfos(const char *target, int slot) const {
	Common::String filename = Common::String::format("%s.%03d", target, slot);
	Common::InSaveFile *f = g_system->getSavefileManager()->openForLoading(filename);

	if (f) {
		Lalaw::LalawSavegameHeader header;
		header.read(f);
		delete f;

		// Create the return descriptor
		SaveStateDescriptor desc(slot, header._saveName);
		desc.setThumbnail(header._thumbnail);

		return desc;
	}

	return SaveStateDescriptor();
}


#if PLUGIN_ENABLED_DYNAMIC(LALAW)
	REGISTER_PLUGIN_DYNAMIC(LALAW, PLUGIN_TYPE_ENGINE, LalawMetaEngine);
#else
	REGISTER_PLUGIN_STATIC(LALAW, PLUGIN_TYPE_ENGINE, LalawMetaEngine);
#endif
