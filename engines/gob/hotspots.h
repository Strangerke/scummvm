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
 * $URL$
 * $Id$
 *
 */

#ifndef GOB_HOTSPOTS_H
#define GOB_HOTSPOTS_H

#include "common/stack.h"

#include "gob/util.h"

namespace Gob {

class Script;

class Hotspots {
public:
	static const int kHotspotCount = 250;

	enum Type {
		kTypeNone              =  0,
		kTypeMove              =  1,
		kTypeClick             =  2,
		kTypeInput1NoLeave     =  3,
		kTypeInput1Leave       =  4,
		kTypeInput2NoLeave     =  5,
		kTypeInput2Leave       =  6,
		kTypeInput3NoLeave     =  7,
		kTypeInput3Leave       =  8,
		kTypeInputFloatNoLeave =  9,
		kTypeInputFloatLeave   = 10
	};

	Hotspots(GobEngine *vm);
	~Hotspots();

	void clear();

	/** Add a hotspot, returning the new index. */
	uint16 add(uint16 id,
			uint16 left,  uint16 top, uint16 right, uint16 bottom,
			uint16 flags, uint16 key,
			uint16 funcEnter, uint16 funcLeave, uint16 funcPos);

	void remove(uint16 id);
	void removeState(uint8 state);

	/** Push the current hotspots onto the stack.
	 *
	 *  @param all   0: Don't push global ones; 1: Push all; 2: Push only the ones with the correct state
	 *  @param force Force a push although _shouldPush is false
	 */
	void push(uint8 all, bool force = false);
	/** Pop hotspots from the stack. */
	void pop();

	uint16 check(uint8 handleMouse, int16 delay, uint16 &id, uint16 &index);
	uint16 check(uint8 handleMouse, int16 delay);

	void evaluate();

	int16 findCursor(uint16 x, uint16 y) const;

private:
	struct Hotspot {
		uint16  id;
		uint16  left;
		uint16  top;
		uint16  right;
		uint16  bottom;
		uint16  flags;
		uint16  key;
		uint16  funcEnter;
		uint16  funcLeave;
		uint16  funcPos;
		Script *script;

		Hotspot();
		Hotspot(uint16 i,
				uint16 l, uint16 t, uint16 r, uint16 b, uint16 f, uint16 k,
				uint16 enter, uint16 leave, uint16 pos);

		void clear();

		Type getType() const;
		MouseButtons getButton() const;
		uint8 getWindow() const;
		uint8 getCursor() const;
		uint8 getState() const;

		/** Is this hotspot the block end marker? */
		bool isEnd() const;

		bool isInput() const;
		bool isActiveInput() const;

		/** Are the specified coordinates in the hotspot? */
		bool isIn(uint16 x, uint16 y) const;
		/** Does the specified button trigger the hotspot? */
		bool buttonMatch(MouseButtons button) const;

		static uint8 getState(uint16 id);
	};

	struct StackEntry {
		bool     shouldPush;
		Hotspot *hotspots;
		uint32   size;
		uint32   key;
		uint32   id;
		uint32   index;
	};

	struct InputDesc {
		uint16 fontIndex;
		uint16 backColor;
		uint16 frontColor;
		const char *str;
	};

	GobEngine *_vm;

	Hotspot *_hotspots;
	Common::Stack<StackEntry> _stack;

	bool _shouldPush;

	uint16 _currentKey;
	uint16 _currentIndex;
	uint16 _currentId;

	/** Add a hotspot, returning the new index. */
	uint16 add(const Hotspot &hotspot);

	/** Recalculate all hotspot parameters
	 *
	 *  @param force Force recalculation of all hotspots, including global ones.
	 */
	void recalculate(bool force);

	bool isValid(uint16 key, uint16 id, uint16 index) const;

	/** Call a hotspot subroutine. */
	void call(uint16 offset);
	/** Handling hotspot enter events. */
	void enter(uint16 index);
	/** Handling hotspot leave events. */
	void leave(uint16 index);

	/** Which hotspot is the mouse cursor currently at? */
	uint16 checkMouse(Type type, uint16 &id, uint16 &index) const;

	void checkHotspotChanged();

	uint16 readString(uint16 xPos, uint16 yPos, uint16 width, uint16 height,
			uint16 backColor, uint16 frontColor, char *str, uint16 fontIndex,
			Type type, int16 &duration, uint16 &id, uint16 index);

	uint16 handleInput(int16 time, uint16 inputCount, uint16 &curInput,
			InputDesc *inputs, uint16 &id, uint16 &index);

	void evaluateNew(uint16 i, uint16 *ids, InputDesc *inputs,
			uint16 &validId, bool &hasInput, uint16 &inputCount);

	// Finding certain inputs
	uint16 findInput(uint16 input) const;
	uint16 findClickedInput(uint16 index) const;
	uint16 findNthInput(uint16 n) const;

	/** Calculate the graphical cursor position. */
	void getTextCursorPos(const Video::FontDesc &font, const char *str,
			uint32 pos, uint16 x, uint16 y, uint16 width, uint16 height,
			uint16 &cursorX, uint16 &cursorY, uint16 &cursorWidth, uint16 &cursorHeight) const;

	// Drawing functions
	void fillRect(uint16 x, uint16 y, uint16 width, uint16 height, uint16 color) const;
	void printText(uint16 x, uint16 y, const char *str, uint16 fontIndex, uint16 color) const;

	void updateAllTexts(const InputDesc *inputs) const;
};

} // End of namespace Gob

#endif // GOB_HOTSPOTS_H
