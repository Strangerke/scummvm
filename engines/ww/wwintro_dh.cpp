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
		{"pyramid.pcx", 58, 21, 7250}
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
} // End of namespace WW
