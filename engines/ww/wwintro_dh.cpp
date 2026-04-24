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

#include "ww/graphics.h"
#include "ww/gxlarchive.h"
#include "ww/ww.h"
#include "ww/wwintro.h"

#include "audio/audiostream.h"
#include "graphics/paletteman.h"

namespace WW {

DHIntro::DHIntro(WWEngine *vm) : Intro(vm) {
}

void DHIntro::runIntro() {
	bool continueFl = init();

	if (continueFl)
		continueFl = introPt1();
	if (continueFl)
		continueFl = introPt2();
	if (continueFl)
		continueFl = introPt3();
}

bool DHIntro::init() {
	GxlArchive *koa00Gxl = new GxlArchive("koa00");

	_vm->loadPalette(koa00Gxl, "credit1.pcx");

	delete koa00Gxl;
	_vm->_midi->stopSong();

	return true;
}

bool DHIntro::introPt1() {
	GxlArchive *koa00Gxl = new GxlArchive("koa00");
	_vm->paletteFadeOut(0, 256, 3);
	_vm->changeMusic("meanwhil.xmi");

	_vm->drawImageToScreen(koa00Gxl, "pyramid.pcx", 58, 21);
	_vm->paletteFadeIn(0, 256, 3);
	
	// The original has all the frames hardcoded one after the other, I used a loop instead.
	Frame animation[] = {
		{"prestxt1.pcx", 40, 125, 60},
		{"prestxt2.pcx", 40, 125, 60},
		{"prestxt3.pcx", 40, 125, 60},
		{"prestxt4.pcx", 40, 125, 60},
		{"prestxt5.pcx", 40, 125, 60},
		{"prestxt6.pcx", 40, 125, 60},
		{"present1.pcx", 115, 156, 60},
		{"present2.pcx", 115, 156, 60},
		{"present3.pcx", 115, 156, 60},
		{"present4.pcx", 115, 156, 60},
		{"present5.pcx", 115, 156, 60},
		{"present6.pcx", 115, 156, 60},
		{"star1.pcx", 146, 17, 150},
		{"star2.pcx", 146, 17, 150},
		{"star3.pcx", 146, 17, 150},
		{"star4.pcx", 146, 17, 150},
		{"pyramid.pcx", 58, 21, 250} // TODO : 7250 in the original
	};

	for (const Frame &frame : animation) {
		_vm->drawImageToScreen(koa00Gxl, frame.filename, frame.x, frame.y);
		_vm->waitMillis(frame.delay);
	}

	_vm->_midi->stopSong();
	_vm->paletteFadeOut(0, 256, 2);

	delete koa00Gxl;
	return true;
}

bool DHIntro::introPt2() {
	int deyeProba = 3;
	int deyeId = 1;
	int neyeProba = 3;
	int neyeId = 1;

	GxlArchive *koa05Gxl = new GxlArchive("koa05");
	_vm->_screen->clear(0);
	_vm->drawImageToScreen(koa05Gxl, "surg.pcx", 0, 15);
	_vm->paletteFadeIn(0, 256, 2);
	_vm->changeMusic("o_r_.xmi");


	for (int loopCtr = 1; loopCtr < 30; ++loopCtr) {
		if (_vm->getRandom(20) <= neyeProba) {
			Common::String filename = Common::String::format("neye%d.pcx", neyeId);
			_vm->drawImageToScreen(koa05Gxl, filename.c_str(), 74, 75);
			neyeProba = neyeId ? 8 : 3;
			neyeId ^= 1;
		}

		if (_vm->getRandom(20) <= deyeProba) {
			Common::String filename = Common::String::format("deye%d.pcx", deyeId);
			_vm->drawImageToScreen(koa05Gxl, filename.c_str(), 205, 65);
			deyeProba = deyeId ? 8 : 3;
			deyeId ^= 1;
		}

		if (loopCtr == 15) {
			for (int i = 1; i < 5; ++i) {
				Common::String filename = Common::String::format("arm%d.pcx", i);
				_vm->drawImageToScreen(koa05Gxl, filename.c_str(), 78, 83);
			}
		}

		_vm->waitMillis(50);
	}

	_vm->playSound("saw.snd", false);


	delete koa05Gxl;
	_vm->waitSeconds(1);

	return true;
}

bool DHIntro::introPt3() {
	GxlArchive *koa03Gxl = new GxlArchive("koa03");
	_vm->paletteFadeOut(0, 256, 32);
	_vm->_screen->clear(0);
	_vm->drawImageToScreen(koa03Gxl, "face.pcx", 61, 15);
	_vm->paletteFadeIn(0, 256, 64);
	_vm->waitMillis(500);

	_vm->playSound("surgt1.snd", false, 10000);
	_vm->drawImageToScreen(koa03Gxl, "ceye.pcx", 126, 79);
	_vm->waitSeconds(1);
	_vm->drawImageToScreen(koa03Gxl, "oeye.pcx", 123, 70);
	_vm->waitMillis(500);
	_vm->drawImageToScreen(koa03Gxl, "text.pcx", 11, 149);
	for (int i = 0; i < 5; ++i) {
		_vm->drawImageToScreen(koa03Gxl, "mouth.pcx", 114, 96);
		_vm->waitMillis(_vm->getRandom(300));
		_vm->drawImageToScreen(koa03Gxl, "face.pcx", 61, 15);
		_vm->waitMillis(_vm->getRandom(300));
	}

	delete koa03Gxl;

	return true;
}
} // End of namespace WW
