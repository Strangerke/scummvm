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

#include "titanic/game/phonograph.h"

namespace Titanic {

BEGIN_MESSAGE_MAP(CPhonograph, CMusicPlayer)
	ON_MESSAGE(PhonographPlayMsg)
	ON_MESSAGE(PhonographStopMsg)
	ON_MESSAGE(PhonographRecordMsg)
	ON_MESSAGE(EnterRoomMsg)
	ON_MESSAGE(LeaveRoomMsg)
	ON_MESSAGE(MusicHasStartedMsg)
END_MESSAGE_MAP()

CPhonograph::CPhonograph() : CMusicPlayer(),
		_isPlaying(false), _isRecording(false), _isDisabled(false), _fieldEC(0),
		_fieldF0(0), _fieldF4(0) {
}

void CPhonograph::save(SimpleFile *file, int indent) {
	file->writeNumberLine(1, indent);
	file->writeQuotedLine(_unused, indent);
	file->writeNumberLine(_isPlaying, indent);
	file->writeNumberLine(_isRecording, indent);
	file->writeNumberLine(_isDisabled, indent);
	file->writeNumberLine(_fieldEC, indent);
	file->writeNumberLine(_fieldF0, indent);
	file->writeNumberLine(_fieldF4, indent);

	CMusicPlayer::save(file, indent);
}

void CPhonograph::load(SimpleFile *file) {
	file->readNumber();
	_unused = file->readString();
	_isPlaying = file->readNumber();
	_isRecording = file->readNumber();
	_isDisabled = file->readNumber();
	_fieldEC = file->readNumber();
	_fieldF0 = file->readNumber();
	_fieldF4 = file->readNumber();

	CMusicPlayer::load(file);
}

bool CPhonograph::PhonographPlayMsg(CPhonographPlayMsg *msg) {
	CQueryCylinderHolderMsg holderMsg;
	holderMsg.execute(this);
	if (!holderMsg._isPresent) {
		_isPlaying = false;
		return true;
	}

	CQueryCylinderMsg cylinderMsg;
	cylinderMsg.execute(holderMsg._target);

	if (cylinderMsg._name.empty()) {
		_isPlaying = false;
	} else if (cylinderMsg._name.hasPrefix("STMusic")) {
		CStartMusicMsg startMsg(this);
		startMsg.execute(this);
		_isPlaying = true;
		msg->_value = 1;
	} else {
		stopGlobalSound(false, -1);
		playGlobalSound(cylinderMsg._name, -2, true, true, 0);
		_isPlaying = true;
		msg->_value = 1;
	}

	return true;
}

bool CPhonograph::PhonographStopMsg(CPhonographStopMsg *msg) {
	CQueryCylinderHolderMsg holderMsg;
	holderMsg.execute(this);
	if (!holderMsg._isPresent)
		return true;

	_isPlaying = false;
	CQueryCylinderMsg cylinderMsg;
	cylinderMsg.execute(holderMsg._target);

	if (_isPlaying) {
		if (!cylinderMsg._name.empty()) {
			if (cylinderMsg._name.hasPrefix("STMusic")) {
				CStopMusicMsg stopMsg;
				stopMsg.execute(this);
			} else {
				stopGlobalSound(msg->_leavingRoom, -1);
			}
			msg->_cylinderPresent = true;
		}

		if (!msg->_dontStop)
			_isPlaying = false;
	} else if (_isRecording) {
		_isRecording = false;
		msg->_cylinderPresent = true;
	}

	return true;
}

bool CPhonograph::PhonographRecordMsg(CPhonographRecordMsg *msg) {
	if (!_isPlaying && !_isRecording && !_isDisabled) {
		CQueryCylinderHolderMsg holderMsg;
		holderMsg.execute(this);

		if (holderMsg._isPresent) {
			_isRecording = true;
			msg->_canRecord = true;
			CErasePhonographCylinderMsg eraseMsg;
			eraseMsg.execute(holderMsg._target);
		} else {
			_isRecording = false;
		}
	}

	return true;
}

bool CPhonograph::EnterRoomMsg(CEnterRoomMsg *msg) {
	if (_isPlaying) {
		CPhonographPlayMsg playMsg;
		playMsg.execute(this);
	}

	return true;
}

bool CPhonograph::LeaveRoomMsg(CLeaveRoomMsg *msg) {
	if (_isPlaying) {
		CPhonographStopMsg stopMsg;
		stopMsg._leavingRoom = true;
		stopMsg.execute(this);
	}

	return true;
}

bool CPhonograph::MusicHasStartedMsg(CMusicHasStartedMsg *msg) {
	if (_isRecording) {
		CQueryCylinderHolderMsg holderMsg;
		holderMsg.execute(this);
		if (holderMsg._isPresent) {
			CRecordOntoCylinderMsg recordMsg;
			recordMsg.execute(holderMsg._target);
		} else {
			_isRecording = false;
		}
	}

	return true;
}

} // End of namespace Titanic
