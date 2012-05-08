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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "robin/robin.h"
#include "robin/sound.h"

#include "common/debug.h"

namespace Robin {

RobinSound::RobinSound(RobinEngine *vm) : _vm(vm) {
}

RobinSound::~RobinSound() {
}

// Used during initialisation
void RobinSound::contentFct0() {
	debugC(1, kDebugSound, "contentFct0()");
}

void RobinSound::contentFct1() {
	debugC(1, kDebugSound, "contentFct1()");
}

void RobinSound::contentFct2() {
	debugC(1, kDebugSound, "contentFct2()");
}

void RobinSound::contentFct3() {
	debugC(1, kDebugSound, "contentFct3()");
}

void RobinSound::contentFct4() {
	debugC(1, kDebugSound, "contentFct4()");
}

void RobinSound::contentFct5() {
	debugC(1, kDebugSound, "contentFct5()");
}

void RobinSound::contentFct6() {
	debugC(1, kDebugSound, "contentFct6()");
}

} // End of namespace
