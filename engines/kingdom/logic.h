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

#ifndef KINGDOM_LOGIC_H
#define KINGDOM_LOGIC_H

#include "gui/debugger.h"

namespace Kingdom {

class KingdomGame;

class Logic {

typedef void (Kingdom::Logic::*Opcode)(void);

private:
	KingdomGame *_vm;

	Common::HashMap<int, Opcode> _opCodes;
	void initOpcodes();

	void GPL1_10();
	void GPL1_11();
	void GPL1_20();
	void GPL1_30();
	void GPL1_31();
	void GPL1_32();
	void GPL1_40();
	void GPL1_41();
	void GPL1_42();
	void GPL1_50();
	void GPL1_51();
	void GPL1_52();
	void GPL1_53();
	void GPL1_60();
	void GPL1_70();
	void GPL1_71();
	void GPL1_72();
	void GPL1_80();
	void GPL1_81();
	void GPL1_82();
	void GPL1_90();
	void GPL1_91();
	void GPL1_92();
	void GPL1_100();
	void GPL1_101();
	void GPL1_102();
	void GPL1_110();
	void GPL1_111();
	void GPL1_112();
	void GPL1_120();
	void GPL1_121();
	void GPL1_130();
	void GPL1_140();
	void GPL1_141();
	void GPL1_142();
	void GPL1_150();
	void GPL1_151();
	void GPL1_160();
	void GPL1_161();
	void GPL1_162();
	void GPL1_170();
	void GPL1_171();
	void GPL1_172();
	void GPL1_180();
	void GPL1_181();
	void GPL1_182();
	void GPL1_190();
	void GPL1_200();
	void GPL1_201();
	void GPL1_202();
	void GPL1_210();
	void GPL1_211();
	void GPL1_212();
	void GPL1_220();
	void GPL1_221();
	void GPL1_222();
	void GPL1_230();
	void GPL1_240();
	void GPL1_241();
	void GPL1_242();

	void GPL2_250();
	void GPL2_251();
	void GPL2_252();
	void GPL2_260();
	void GPL2_261();
	void GPL2_270();
	void GPL2_271();
	void GPL2_272();
	void GPL2_280();
	void GPL2_290();
	void GPL2_291();
	void GPL2_292();
	void GPL2_300();
	void GPL2_301();
	void GPL2_302();
	void GPL2_310();
	void GPL2_311();
	void GPL2_312();
	void GPL2_320();
	void GPL2_321();
	void GPL2_322();
	void GPL2_330();
	void GPL2_331();
	void GPL2_332();
	void GPL2_340();
	void GPL2_341();
	void GPL2_342();
	void GPL2_350();
	void GPL2_351();
	void GPL2_360();
	void GPL2_361();
	void GPL2_362();
	void GPL2_370();
	void GPL2_371();
	void GPL2_372();
	void GPL2_380();
	void GPL2_381();
	void GPL2_382();
	void GPL2_390();
	void GPL2_400();
	void GPL2_401();
	void GPL2_402();
	void GPL2_410();
	void GPL2_411();
	void GPL2_420();
	void GPL2_421();
	void GPL2_422();
	void GPL2_430();
	void GPL2_431();
	void GPL2_440();
	void GPL2_441();
	void GPL2_442();
	void GPL2_450();
	void GPL2_451();
	void GPL2_460();
	void GPL2_461();
	void GPL2_462();
	void GPL2_480();
	void GPL2_481();
	void GPL2_482();
	void GPL2_490();
	void GPL2_491();

public:
	int _statPlay;
	int _oldStatPlay;
	int _nodeNum;
	int _oldNode; // CHECKME: Useless? If so, to be removed
	int _nextNode;
	int _robberyNode;
	int16 _nodes[99];
	int _currMap;
	bool _oldEye;
	bool _eye;
	bool _oldHelp;
	bool _help;
	int _lastObstacle;
	bool _lastObs;
	int _inventory[19];
	bool _replay;
	bool _pouch;
	bool _oldPouch;
	bool _resurrect;
	bool _tideCntl;
	int _rtnNode;
	int _health;
	int _healthOld;
	bool _fstFwd;
	bool _spell1;
	bool _spell2;
	bool _spell3;

	int _mapStat; // CHECKME: Useless? If so, to be removed

	void enAll(); // TODO: Rename later as enableAll
	void dsAll(); // TODO: Rename later as disableAll
	bool wound();
	void GPLogic1_SubSP10();
	void GPLogic1_SubSP121();
	void GPLogic2_SubSP361();
	void GPLogic4_SP901();
	bool chkDesertObstacles();
	void increaseHealth();
	void endCredits();
	void gameHelp_Sub43C();

public:
	explicit Logic(Kingdom::KingdomGame *vm);
	virtual ~Logic(void) {}

	void GPLogic3();
	void GPLogic4();
	void gameHelp();
	void inventoryDel(int item);
	void inventoryAdd(int item);
	void initVariables();
	void executeOpcode();
	void initPlay();
	void switchAS();
	void synchronize(Common::Serializer &s);
};
}

#endif
