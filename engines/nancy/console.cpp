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
#include "graphics/surface.h"
#include "audio/audiostream.h"
#include "nancy/console.h"
#include "nancy/nancy.h"
#include "nancy/resource.h"
#include "nancy/video.h"
#include "nancy/audio.h"

namespace Nancy {

NancyConsole::NancyConsole(NancyEngine *vm) : GUI::Debugger(), _vm(vm) {
	DCmd_Register("load_cal", WRAP_METHOD(NancyConsole, Cmd_loadCal));
	DCmd_Register("cif_hexdump", WRAP_METHOD(NancyConsole, Cmd_cifHexDump));
	DCmd_Register("cif_export", WRAP_METHOD(NancyConsole, Cmd_cifExport));
	DCmd_Register("cif_list", WRAP_METHOD(NancyConsole, Cmd_cifList));
	DCmd_Register("cif_info", WRAP_METHOD(NancyConsole, Cmd_cifInfo));
	DCmd_Register("show_image", WRAP_METHOD(NancyConsole, Cmd_showImage));
	DCmd_Register("play_video", WRAP_METHOD(NancyConsole, Cmd_playVideo));
	DCmd_Register("play_audio", WRAP_METHOD(NancyConsole, Cmd_playAudio));
}

NancyConsole::~NancyConsole() {
}

void NancyConsole::postEnter() {
	if (!_videoFile.empty()) {
		Video::VideoDecoder *dec = new AVFDecoder;
	
		if (dec->loadFile(_videoFile)) {
			dec->start();
			while (!dec->endOfVideo()) {
				const Graphics::Surface *frame = dec->decodeNextFrame();
				_vm->_system->fillScreen(0);
				_vm->_system->copyRectToScreen(frame->pixels, frame->pitch, 0, 0, frame->w, frame->h);
				_vm->_system->updateScreen();
				_vm->_system->delayMillis(60);
			}
		} else {
			DebugPrintf("Failed to load '%s'\n", _videoFile.c_str());
		}
		_videoFile.clear();
	}
}

bool NancyConsole::Cmd_cifHexDump(int argc, const char **argv) {
	if (argc < 2 || argc > 3) {
		DebugPrintf("Dumps the specified resource to standard output\n");
		DebugPrintf("Usage: %s name [cal]\n", argv[0]);
		return true;
	}

	uint size;
	byte *buf = _vm->_res->loadCif((argc == 2 ? "ciftree" : argv[2]), argv[1], size);
	if (!buf) {
		DebugPrintf("Failed to load resource '%s'\n", argv[1]);
		return true;
	}

	Common::hexdump(buf, size);
	delete[] buf;
	return true;
}

bool NancyConsole::Cmd_cifExport(int argc, const char **argv) {
	if (argc < 2 || argc > 3) {
		DebugPrintf("Exports the specified resource to .cif file\n");
		DebugPrintf("Usage: %s name [cal]\n", argv[0]);
		return true;
	}

	if (!_vm->_res->exportCif((argc == 2 ? "ciftree" : argv[2]), argv[1]))
		DebugPrintf("Failed to export '%s'\n", argv[1]);

	return true;
}

bool NancyConsole::Cmd_cifList(int argc, const char **argv) {
	if (argc < 2 || argc > 3) {
		DebugPrintf("List resources of a certain type\n");
		DebugPrintf("Types - 0: all, 2: image, 3: script\n");
		DebugPrintf("Usage: %s type [cal]\n", argv[0]);
		return true;
	}

	Common::Array<Common::String> list;
	_vm->_res->list((argc == 2 ? "ciftree" : argv[2]), list, atoi(argv[1]));
	for (uint i = 0; i < list.size(); i++) {
		DebugPrintf("%-38s", list[i].c_str());
		if ((i % 2) == 1 && i + 1 != list.size())
			DebugPrintf("\n");
	}

	DebugPrintf("\n");

	return true;
}

bool NancyConsole::Cmd_cifInfo(int argc, const char **argv) {
	if (argc < 2 || argc > 3) {
		DebugPrintf("Prints information about a resource\n");
		DebugPrintf("Usage: %s name [cal]\n", argv[0]);
		return true;
	}

	DebugPrintf("%s", _vm->_res->getCifDescription((argc == 2 ? "ciftree" : argv[2]), argv[1]).c_str());
	return true;
}

bool NancyConsole::Cmd_showImage(int argc, const char **argv) {
	if (argc < 2 || argc > 3) {
		DebugPrintf("Draws an image on the screen\n");
		DebugPrintf("Usage: %s name [cal]\n", argv[0]);
		return true;
	}

	Graphics::Surface surf;
	if (_vm->_res->loadImage((argc == 2 ? "ciftree" : argv[2]), argv[1], surf)) {
		_vm->_system->fillScreen(0);
		_vm->_system->copyRectToScreen(surf.pixels, surf.pitch, 0, 0, surf.w > 640 ? 640 : surf.w, surf.h > 480 ? 480 : surf.h);
		surf.free();
		return Cmd_Exit(0, 0);
	} else {
		DebugPrintf("Failed to load image\n");
		return true;
	}
}

bool NancyConsole::Cmd_loadCal(int argc, const char **argv) {
	if (argc != 2) {
		DebugPrintf("Loads a .cal file\n");
		DebugPrintf("Usage: %s <name>\n", argv[0]);
		return true;
	}

	if (!_vm->_res->loadCifTree(argv[1], "cal"))
		DebugPrintf("Failed to load '%s.cal'\n", argv[1]);
	return true;
}

bool NancyConsole::Cmd_playVideo(int argc, const char **argv) {
	if (argc != 2) {
		DebugPrintf("Plays a video\n");
		DebugPrintf("Usage: %s <name>\n", argv[0]);
		return true;
	}

	_videoFile = argv[1];
	_videoFile += ".avf";
	return Cmd_Exit(0, 0);
}

bool NancyConsole::Cmd_playAudio(int argc, const char **argv) {
	if (argc != 2) {
		DebugPrintf("Plays an audio file\n");
		DebugPrintf("Usage: %s <name>\n", argv[0]);
		return true;
	}

	Common::File *f = new Common::File;
	if (!f->open(Common::String(argv[1]) + ".his")) {
		DebugPrintf("Failed to open '%s.his'\n", argv[1]);
		return true;
	}

	Audio::AudioStream *stream = makeHISStream(f, DisposeAfterUse::YES);

	if (!stream) {
		DebugPrintf("Failed to load '%s.his'\n", argv[1]);
		delete f;
		return true;
	}
	Audio::SoundHandle handle;
	_vm->_system->getMixer()->playStream(Audio::Mixer::kPlainSoundType, &handle, stream);
	return true;
}

} // End of namespace Nancy
