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

#include "hdb/hdb.h"

namespace HDB {

/*
	Comment from Original:
	these arrays list each of the game's actor's possible states and
	which graphics to load for them.
*/

AIStateDef none[] = {
	{ STATE_ENDSTATES, "" }
};

AIStateDef guy[] = {
	{ STATE_BLINK,          GROUP_ENT_GUY_BLINK },
	{ STATE_STANDDOWN,      GROUP_ENT_GUY_STANDDOWN },
	{ STATE_STANDUP,        GROUP_ENT_GUY_STANDUP },
	{ STATE_STANDLEFT,      GROUP_ENT_GUY_STANDLEFT },
	{ STATE_STANDRIGHT,     GROUP_ENT_GUY_STANDRIGHT },
	{ STATE_MOVEDOWN,       GROUP_ENT_GUY_WALKDOWN },
	{ STATE_MOVEUP,         GROUP_ENT_GUY_WALKUP },
	{ STATE_MOVELEFT,       GROUP_ENT_GUY_WALKLEFT },
	{ STATE_MOVERIGHT,      GROUP_ENT_GUY_WALKRIGHT },
	{ STATE_PUSHDOWN,       GROUP_ENT_GUY_PUSHDOWN },
	{ STATE_PUSHUP,         GROUP_ENT_GUY_PUSHUP },
	{ STATE_PUSHLEFT,       GROUP_ENT_GUY_PUSHLEFT },
	{ STATE_PUSHRIGHT,      GROUP_ENT_GUY_PUSHRIGHT },
	{ STATE_GRABDOWN,       GROUP_ENT_GUY_GETDOWN },
	{ STATE_GRABUP,         GROUP_ENT_GUY_GETUP },
	{ STATE_GRABLEFT,       GROUP_ENT_GUY_GETLEFT },
	{ STATE_GRABRIGHT,      GROUP_ENT_GUY_GETRIGHT },
	{ STATE_PLUMMET,        GROUP_ENT_GUY_PLUMMET },
	{ STATE_ATK_STUN_DOWN,  GROUP_ENT_GUY_STUNDOWN },
	{ STATE_ATK_STUN_UP,    GROUP_ENT_GUY_STUNUP },
	{ STATE_ATK_STUN_LEFT,  GROUP_ENT_GUY_STUNLEFT },
	{ STATE_ATK_STUN_RIGHT, GROUP_ENT_GUY_STUNRIGHT },
	{ STATE_ATK_SLUG_DOWN,  GROUP_ENT_GUY_SLINGDOWN },
	{ STATE_ATK_SLUG_UP,    GROUP_ENT_GUY_SLINGUP },
	{ STATE_ATK_SLUG_LEFT,  GROUP_ENT_GUY_SLINGLEFT },
	{ STATE_ATK_SLUG_RIGHT, GROUP_ENT_GUY_SLINGRIGHT },
	{ STATE_DYING,          GROUP_ENT_GUY_DIE },
	{ STATE_HORRIBLE1,      GROUP_ENT_GUY_HORRIBLE1 },
	{ STATE_HORRIBLE2,      GROUP_ENT_GUY_HORRIBLE2 },
	{ STATE_HORRIBLE3,      GROUP_ENT_GUY_HORRIBLE3 },
	{ STATE_HORRIBLE4,      GROUP_ENT_GUY_HORRIBLE4 },
	{ STATE_GOODJOB,        GROUP_ENT_GUY_GOODJOB },
	{ STATE_ENDSTATES, "" }                            // end of list indicator
};

AIStateDef gemAttack[] = {
	{ STATE_MOVEDOWN,       GROUP_ENT_GEM_WHITE_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef slugAttack[] = {
	{ STATE_ENDSTATES, "" }
};

AIStateDef dolly[] = {
	{ STATE_MOVEDOWN,       GROUP_ENT_DOLLY_WALKDOWN },
	{ STATE_MOVEUP,         GROUP_ENT_DOLLY_WALKUP },
	{ STATE_MOVELEFT,       GROUP_ENT_DOLLY_WALKLEFT },
	{ STATE_MOVERIGHT,      GROUP_ENT_DOLLY_WALKRIGHT },
	{ STATE_DOLLYUSERIGHT, GROUP_ENT_DOLLY_USERIGHT },
	{ STATE_KISSRIGHT,      GROUP_ENT_DOLLY_KISSRIGHT },
	{ STATE_KISSLEFT,       GROUP_ENT_DOLLY_KISSLEFT },
	{ STATE_ANGRY,          GROUP_ENT_DOLLY_ANGRY },
	{ STATE_LAUGH,          GROUP_ENT_DOLLY_LAUGH },
	{ STATE_PANIC,          GROUP_ENT_DOLLY_PANIC },
	{ STATE_ENDSTATES, "" }
};

AIStateDef sergeant[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_SERGEANT_STANDDOWN },
	{ STATE_STANDUP,        GROUP_ENT_SERGEANT_STANDUP },
	{ STATE_STANDLEFT,      GROUP_ENT_SERGEANT_STANDLEFT },
	{ STATE_STANDRIGHT,     GROUP_ENT_SERGEANT_STANDRIGHT },
	{ STATE_YELL,           GROUP_ENT_SERGEANT_YELL },
	{ STATE_MOVEDOWN,       GROUP_ENT_SERGEANT_WALKDOWN },
	{ STATE_MOVEUP,         GROUP_ENT_SERGEANT_WALKUP },
	{ STATE_MOVELEFT,       GROUP_ENT_SERGEANT_WALKLEFT },
	{ STATE_MOVERIGHT,      GROUP_ENT_SERGEANT_WALKRIGHT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef spacedude[] = {
	{ STATE_MOVEDOWN,       GROUP_ENT_SPACEDUDE_WALKDOWN },
	{ STATE_MOVEUP,         GROUP_ENT_SPACEDUDE_WALKUP },
	{ STATE_MOVELEFT,       GROUP_ENT_SPACEDUDE_WALKLEFT },
	{ STATE_MOVERIGHT,      GROUP_ENT_SPACEDUDE_WALKRIGHT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef chicken[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_CHICKEN_STANDDOWN },
	{ STATE_STANDUP,        GROUP_ENT_CHICKEN_STANDUP },
	{ STATE_STANDLEFT,      GROUP_ENT_CHICKEN_STANDLEFT },
	{ STATE_STANDRIGHT,     GROUP_ENT_CHICKEN_STANDRIGHT },
	{ STATE_MOVEDOWN,       GROUP_ENT_CHICKEN_WALKDOWN },
	{ STATE_MOVEUP,         GROUP_ENT_CHICKEN_WALKUP },
	{ STATE_MOVELEFT,       GROUP_ENT_CHICKEN_WALKLEFT },
	{ STATE_MOVERIGHT,      GROUP_ENT_CHICKEN_WALKRIGHT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef vortexian[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_VORTEXIAN_STANDDOWN },
	{ STATE_ENDSTATES, "" }
};

AIStateDef maintBot[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_MAINTBOT_STANDDOWN },
	{ STATE_STANDUP,        GROUP_ENT_MAINTBOT_STANDUP },
	{ STATE_STANDLEFT,      GROUP_ENT_MAINTBOT_STANDLEFT },
	{ STATE_STANDRIGHT,     GROUP_ENT_MAINTBOT_STANDRIGHT },
	{ STATE_MOVEDOWN,       GROUP_ENT_MAINTBOT_WALKDOWN },
	{ STATE_MOVEUP,         GROUP_ENT_MAINTBOT_WALKUP },
	{ STATE_MOVELEFT,       GROUP_ENT_MAINTBOT_WALKLEFT },
	{ STATE_MOVERIGHT,      GROUP_ENT_MAINTBOT_WALKRIGHT },
	{ STATE_USEDOWN,        GROUP_ENT_MAINTBOT_USEDOWN },
	{ STATE_USEUP,          GROUP_ENT_MAINTBOT_USEUP },
	{ STATE_USELEFT,        GROUP_ENT_MAINTBOT_USELEFT },
	{ STATE_USERIGHT,       GROUP_ENT_MAINTBOT_USERIGHT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef scientist[] = {
	{ STATE_BLINK,          GROUP_ENT_SCIENTIST_BLINK },
	{ STATE_STANDDOWN,      GROUP_ENT_SCIENTIST_STANDDOWN },
	{ STATE_STANDUP,        GROUP_ENT_SCIENTIST_STANDUP },
	{ STATE_STANDLEFT,      GROUP_ENT_SCIENTIST_STANDLEFT },
	{ STATE_STANDRIGHT,     GROUP_ENT_SCIENTIST_STANDRIGHT },
	{ STATE_MOVEDOWN,       GROUP_ENT_SCIENTIST_WALKDOWN },
	{ STATE_MOVEUP,         GROUP_ENT_SCIENTIST_WALKUP },
	{ STATE_MOVELEFT,       GROUP_ENT_SCIENTIST_WALKLEFT },
	{ STATE_MOVERIGHT,      GROUP_ENT_SCIENTIST_WALKRIGHT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef worker[] = {
	{ STATE_BLINK,          GROUP_ENT_WORKER_BLINK },
	{ STATE_STANDDOWN,      GROUP_ENT_WORKER_STANDDOWN },
	{ STATE_STANDUP,        GROUP_ENT_WORKER_STANDUP },
	{ STATE_STANDLEFT,      GROUP_ENT_WORKER_STANDLEFT },
	{ STATE_STANDRIGHT,     GROUP_ENT_WORKER_STANDRIGHT },
	{ STATE_MOVEDOWN,       GROUP_ENT_WORKER_WALKDOWN },
	{ STATE_MOVEUP,         GROUP_ENT_WORKER_WALKUP },
	{ STATE_MOVELEFT,       GROUP_ENT_WORKER_WALKLEFT },
	{ STATE_MOVERIGHT,      GROUP_ENT_WORKER_WALKRIGHT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef deadWorker[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_DEAD_WORKER_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef accountant[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_ACCOUNTANT_STANDDOWN },
	{ STATE_STANDUP,        GROUP_ENT_ACCOUNTANT_STANDUP },
	{ STATE_STANDLEFT,      GROUP_ENT_ACCOUNTANT_STANDLEFT },
	{ STATE_STANDRIGHT,     GROUP_ENT_ACCOUNTANT_STANDRIGHT },
	{ STATE_ENDSTATES, "" }
};

// Enemies

AIStateDef pushBot[] = {
	{ STATE_MOVEDOWN,       GROUP_ENT_PUSHBOT_WALKDOWN },
	{ STATE_MOVEUP,         GROUP_ENT_PUSHBOT_WALKUP },
	{ STATE_MOVELEFT,       GROUP_ENT_PUSHBOT_WALKLEFT },
	{ STATE_MOVERIGHT,      GROUP_ENT_PUSHBOT_WALKRIGHT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef rightBot[] = {
	{ STATE_MOVEDOWN,       GROUP_ENT_RIGHTBOT_WALKDOWN },
	{ STATE_MOVEUP,         GROUP_ENT_RIGHTBOT_WALKUP },
	{ STATE_MOVELEFT,       GROUP_ENT_RIGHTBOT_WALKLEFT },
	{ STATE_MOVERIGHT,      GROUP_ENT_RIGHTBOT_WALKRIGHT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef omniBot[] = {
	{ STATE_MOVEDOWN,       GROUP_ENT_OMNIBOT_WALKDOWN },
	{ STATE_MOVEUP,         GROUP_ENT_OMNIBOT_WALKUP },
	{ STATE_MOVELEFT,       GROUP_ENT_OMNIBOT_WALKLEFT },
	{ STATE_MOVERIGHT,      GROUP_ENT_OMNIBOT_WALKRIGHT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef laser[] = {
	{ STATE_STANDRIGHT,     GROUP_ENT_LASER_RIGHT },
	{ STATE_STANDLEFT,      GROUP_ENT_LASER_LEFT },
	{ STATE_STANDUP,        GROUP_ENT_LASER_UP },
	{ STATE_STANDDOWN,      GROUP_ENT_LASER_DOWN },
	{ STATE_ENDSTATES, "" }
};

AIStateDef diverter[] = {
	{ STATE_DIVERTER_BL,    GROUP_ENT_DEFLECTORBL_SIT },
	{ STATE_DIVERTER_BR,    GROUP_ENT_DEFLECTORBR_SIT },
	{ STATE_DIVERTER_TL,    GROUP_ENT_DEFLECTORTL_SIT },
	{ STATE_DIVERTER_TR,    GROUP_ENT_DEFLECTORTR_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef turnBot[] = {
	{ STATE_MOVEDOWN,       GROUP_ENT_TURNBOT_WALKDOWN },
	{ STATE_MOVEUP,         GROUP_ENT_TURNBOT_WALKUP },
	{ STATE_MOVELEFT,       GROUP_ENT_TURNBOT_WALKLEFT },
	{ STATE_MOVERIGHT,      GROUP_ENT_TURNBOT_WALKRIGHT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef deadEye[] = {
	{ STATE_MOVEDOWN,       GROUP_ENT_DEADEYE_WALKDOWN },
	{ STATE_MOVEUP,         GROUP_ENT_DEADEYE_WALKUP },
	{ STATE_MOVELEFT,       GROUP_ENT_DEADEYE_WALKLEFT },
	{ STATE_MOVERIGHT,      GROUP_ENT_DEADEYE_WALKRIGHT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef meerkat[] = {
	{ STATE_MEER_MOVE,      GROUP_ENT_MEERKAT_DIRTMOVE },
	{ STATE_MEER_APPEAR,    GROUP_ENT_MEERKAT_APPEAR },
	{ STATE_MEER_BITE,      GROUP_ENT_MEERKAT_BITE },
	{ STATE_MEER_DISAPPEAR, GROUP_ENT_MEERKAT_DISAPPEAR },
	{ STATE_MEER_LOOK,      GROUP_ENT_MEERKAT_LOOK },
	{ STATE_ENDSTATES, "" }
};

AIStateDef goodFairy[] = {
	{ STATE_MOVEDOWN,       GROUP_ENT_GOODFAIRY_WALKDOWN },
	{ STATE_MOVEUP,         GROUP_ENT_GOODFAIRY_WALKUP },
	{ STATE_MOVELEFT,       GROUP_ENT_GOODFAIRY_WALKLEFT },
	{ STATE_MOVERIGHT,      GROUP_ENT_GOODFAIRY_WALKRIGHT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef badFairy[] = {
	{ STATE_MOVEDOWN,       GROUP_ENT_BADFAIRY_WALKDOWN },
	{ STATE_MOVEUP,         GROUP_ENT_BADFAIRY_WALKUP },
	{ STATE_MOVELEFT,       GROUP_ENT_BADFAIRY_WALKLEFT },
	{ STATE_MOVERIGHT,      GROUP_ENT_BADFAIRY_WALKRIGHT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef gatePuddle[] = {
	{ STATE_MOVEDOWN,       GROUP_ENT_GATEPUDDLE_STANDDOWN },
	{ STATE_ENDSTATES, "" }
};

AIStateDef icePuff[] = {
	{ STATE_ICEP_PEEK,      GROUP_ENT_ICEPUFF_PEEK },
	{ STATE_ICEP_APPEAR,    GROUP_ENT_ICEPUFF_APPEAR },
	{ STATE_ICEP_THROWDOWN, GROUP_ENT_ICEPUFF_THROWDOWN },
	{ STATE_ICEP_THROWRIGHT,GROUP_ENT_ICEPUFF_THROWRIGHT },
	{ STATE_ICEP_THROWLEFT, GROUP_ENT_ICEPUFF_THROWLEFT },
	{ STATE_ICEP_DISAPPEAR, GROUP_ENT_ICEPUFF_DISAPPEAR },
	{ STATE_ENDSTATES, "" }
};

AIStateDef buzzfly[] = {
	{ STATE_MOVEDOWN,      GROUP_ENT_BUZZFLY_WALKDOWN },
	{ STATE_MOVEUP,        GROUP_ENT_BUZZFLY_WALKUP },
	{ STATE_MOVELEFT,      GROUP_ENT_BUZZFLY_WALKLEFT },
	{ STATE_MOVERIGHT,     GROUP_ENT_BUZZFLY_WALKRIGHT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef fatFrog[] = {
	{ STATE_STANDDOWN,              GROUP_ENT_FATFROG_STANDDOWN },
	{ STATE_STANDLEFT,              GROUP_ENT_FATFROG_STANDLEFT },
	{ STATE_STANDRIGHT,             GROUP_ENT_FATFROG_STANDRIGHT },
	{ STATE_LICKDOWN,               GROUP_ENT_FATFROG_LICKDOWN },
	{ STATE_LICKLEFT,               GROUP_ENT_FATFROG_LICKLEFT },
	{ STATE_LICKRIGHT,              GROUP_ENT_FATFROG_LICKRIGHT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef dragon[] = {
	{ STATE_ENDSTATES, "" }
};

// These are in the demo

AIStateDef omniBotMissile[] = {
	{ STATE_MOVEDOWN,       GROUP_ENT_OMNIBOT_MISSILE },
	{ STATE_ENDSTATES, "" }
};

AIStateDef fourFirer[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_FOUR_LASER_DOWN },
	{ STATE_STANDUP,        GROUP_ENT_FOUR_LASER_UP },
	{ STATE_STANDLEFT,      GROUP_ENT_FOUR_LASER_LEFT },
	{ STATE_STANDRIGHT,     GROUP_ENT_FOUR_LASER_RIGHT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef railRider[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_RAILRIDER_STANDDOWN },
	{ STATE_STANDUP,        GROUP_ENT_RAILRIDER_STANDUP },
	{ STATE_MOVEDOWN,       GROUP_ENT_RAILRIDER_WALKDOWN },
	{ STATE_MOVEUP,         GROUP_ENT_RAILRIDER_WALKUP },
	{ STATE_MOVELEFT,       GROUP_ENT_RAILRIDER_WALKLEFT },
	{ STATE_MOVERIGHT,      GROUP_ENT_RAILRIDER_WALKRIGHT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef shockBot[] = {
	{ STATE_MOVEDOWN,       GROUP_ENT_SHOCKBOT_WALK },
	{ STATE_SHOCKING,       GROUP_SHOCK_SPARK_SIT },
	{ STATE_ENDSTATES, "" }
};

// Pushables

AIStateDef crate[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_CRATE_SIT },
	{ STATE_FLOATING,       GROUP_ENT_CRATE_FLOAT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef barrelLight[] = {
	{ STATE_FLOATING,       GROUP_ENT_BARREL_LIGHT_FLOAT },
	{ STATE_MELTED,         GROUP_ENT_BARREL_LIGHT_MELT },
	{ STATE_STANDDOWN,      GROUP_ENT_BARREL_LIGHT_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef barrelHeavy[] = {
	{ STATE_FLOATING,       GROUP_ENT_BARREL_HEAVY_FLOAT },
	{ STATE_MELTED,         GROUP_ENT_BARREL_HEAVY_MELT },
	{ STATE_STANDDOWN,      GROUP_ENT_BARREL_HEAVY_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef barrelExplode[] = {
	{ STATE_EXPLODING,      GROUP_EXPLOSION_BOOM_SIT },
	{ STATE_STANDDOWN,      GROUP_ENT_BARREL_EXPLODE_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef frogStatue[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_FROGSTATUE_SIT },
	{ STATE_ENDSTATES, "" }
};

// Weapons

AIStateDef club[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_CLUB_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef roboStunner[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_ROBOSTUNNER_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef slugSlinger[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_SLUGSLINGER_SIT },
	{ STATE_ENDSTATES, "" }
};

// Items

AIStateDef itemChicken[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_CHICKEN_STANDDOWN },
	{ STATE_ENDSTATES, "" }
};

AIStateDef envelopeWhite[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_ENVELOPE_WHITE_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef envelopeBlue[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_ENVELOPE_BLUE_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef envelopeRed[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_ENVELOPE_RED_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef transceiver[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_TRANSCEIVER_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef cell[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_CELL_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef gooCup[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_GOO_CUP_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef gemWhite[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_GEM_WHITE_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef cabKey[] = {
	{ STATE_STANDDOWN, "ent_cabkey_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef envelopeGreen[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_ENVELOPE_GREEN_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef teaCup[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_TEACUP_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef cookie[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_COOKIE_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef burger[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_BURGER_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef pda[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_PDA_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef book[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_BOOK_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef clipboard[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_CLIPBOARD_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef note[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_NOTE_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef keycardWhite[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_KEYCARD_WHITE_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef keycardBlue[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_KEYCARD_BLUE_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef keycardRed[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_KEYCARD_RED_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef keycardGreen[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_KEYCARD_GREEN_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef keycardPurple[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_KEYCARD_PURPLE_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef keycardBlack[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_KEYCARD_BLACK_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef magicEgg[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_MAGIC_EGG_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef iceBlock[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_ICE_BLOCK_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef gemBlue[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_GEM_BLUE_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef gemRed[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_GEM_RED_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef gemGreen[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_GEM_GREEN_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef dollyTool1[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_DOLLY_TOOL1_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef dollyTool2[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_DOLLY_TOOL2_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef dollyTool3[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_DOLLY_TOOL3_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef dollyTool4[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_DOLLY_TOOL4_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef seed[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_SEED_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef soda[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_SODA_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef router[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_ROUTER_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef slicer[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_SLICER_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef package[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_PACKAGE_SIT },
	{ STATE_ENDSTATES, "" }
};

AIStateDef monkeystone[] = {
	{ STATE_STANDDOWN,      GROUP_ENT_MONKEYSTONE_SIT },
	{ STATE_ENDSTATES, "" }
};

AIEntTypeInfo aiEntList[] = {
	// AI.H enum name		lua name				list of gfx for states	name of init function
	//--------------------------------------------------------------------------------------------
	{ AI_NONE,				"AI_NONE",				&none[0],				aiNoneInit,				NULL  },
	{ AI_GUY,				"AI_GUY",				&guy[0],				aiPlayerInit,			aiPlayerInit2  },
	{ AI_DOLLY,				"AI_DOLLY",				&dolly[0],				aiDollyInit,			aiDollyInit2  },
	{ AI_SERGEANT,			"AI_SERGEANT",			&sergeant[0],			aiSergeantInit,			aiSergeantInit2  },
	{ AI_SPACEDUDE,			"AI_SPACEDUDE",			&spacedude[0],			aiSpacedudeInit,		aiSpacedudeInit2  },
	{ AI_CHICKEN,			"AI_CHICKEN",			&chicken[0],			aiChickenInit,			aiChickenInit2  },
	{ AI_VORTEXIAN,			"AI_VORTEXIAN",			&vortexian[0],			aiVortexianInit,		aiVortexianInit2  },
	{ AI_MAINTBOT,			"AI_MAINTBOT",			&maintBot[0],			aiMaintBotInit,			aiMaintBotInit2  },
	{ AI_SCIENTIST,			"AI_SCIENTIST",			&scientist[0],			aiScientistInit,		aiScientistInit2  },
	{ AI_RAILRIDER,			"AI_RAILRIDER",			&railRider[0],			aiRailRiderInit,		aiRailRiderInit2  },
	{ AI_RAILRIDER_ON,		"AI_RAILRIDER",			&railRider[0],			aiRailRiderInit,		aiRailRiderInit2  },
	{ AI_SHOCKBOT,			"AI_SHOCKBOT",			&shockBot[0],			aiShockBotInit,			aiShockBotInit2  },
	{ AI_FOURFIRER,			"AI_FOURFIRER",			&fourFirer[0],			aiFourFirerInit,		aiFourFirerInit2  },
	{ AI_OMNIBOT_MISSILE,	"AI_OMNIBOT_MISSILE",	&omniBotMissile[0],		aiOmniBotMissileInit,	aiOmniBotMissileInit2  },
	{ AI_GEM_ATTACK,		"AI_GEM_ATTACK",		&gemAttack[0],			aiGemAttackInit,		NULL  },
	{ AI_WORKER,			"AI_WORKER",			&worker[0],				aiWorkerInit,			aiWorkerInit2  },
	{ AI_ACCOUNTANT,		"AI_ACCOUNTANT",		&accountant[0],			aiAccountantInit,		aiAccountantInit2  },
	{ AI_SLUG_ATTACK,		"AI_SLUG_ATTACK",		&slugAttack[0],			aiSlugAttackInit,		aiSlugAttackInit2  },
	{ AI_DEADWORKER,		"AI_DEADWORKER",		&deadWorker[0],			aiDeadWorkerInit,		aiDeadWorkerInit2  },

	{ AI_LASER,				"AI_LASER",				&laser[0],				aiLaserInit,			aiLaserInit2  },
	{ AI_DIVERTER,			"AI_DIVERTER",			&diverter[0],			aiDiverterInit,			aiDiverterInit2  },
	{ AI_OMNIBOT,			"AI_OMNIBOT",			&omniBot[0],			aiOmniBotInit,			aiOmniBotInit2  },
	{ AI_TURNBOT,			"AI_TURNBOT",			&turnBot[0],			aiTurnBotInit,			aiTurnBotInit2  },
	{ AI_RIGHTBOT,			"AI_RIGHTBOT",			&rightBot[0],			aiRightBotInit,			aiRightBotInit2  },
	{ AI_PUSHBOT,			"AI_PUSHBOT",			&pushBot[0],			aiPushBotInit,			aiPushBotInit2  },
	{ AI_DEADEYE,			"AI_DEADEYE",			&deadEye[0],			aiDeadEyeInit,			aiDeadEyeInit2  },
	{ AI_MEERKAT,			"AI_MEERKAT",			&meerkat[0],			aiMeerkatInit,			aiMeerkatInit2  },
	{ AI_FATFROG,			"AI_FATFROG",			&fatFrog[0],			aiFatFrogInit,			aiFatFrogInit2  },
	{ AI_GOODFAIRY,			"AI_GOODFAIRY",			&goodFairy[0],			aiGoodFairyInit,		aiGoodFairyInit2  },
	{ AI_BADFAIRY,			"AI_BADFAIRY",			&badFairy[0],			aiBadFairyInit,			aiBadFairyInit2  },
	{ AI_GATEPUDDLE,		"AI_GATEPUDDLE",		&gatePuddle[0],			aiGatePuddleInit,		aiGatePuddleInit2  },
	{ AI_ICEPUFF,			"AI_ICEPUFF",			&icePuff[0],			aiIcePuffInit,			aiIcePuffInit2  },
	{ AI_DRAGON,			"AI_DRAGON",			&dragon[0],				aiDragonInit,			aiDragonInit2  },
	{ AI_BUZZFLY,			"AI_BUZZFLY",			&buzzfly[0],			aiBuzzflyInit,			aiBuzzflyInit2  },
	{ AI_BOOMBARREL,		"AI_BOOMBARREL",		&barrelExplode[0],		aiBarrelExplodeInit,	aiBarrelExplodeInit2  },
	{ AI_FROGSTATUE,		"AI_FROGSTATUE",		&frogStatue[0],			aiFrogStatueInit,		aiFrogStatueInit2  },

	{ AI_MAGIC_EGG,			"AI_MAGIC_EGG",			&magicEgg[0],			aiMagicEggInit,		aiMagicEggInit2  },
	{ AI_ICE_BLOCK,			"AI_ICE_BLOCK",			&iceBlock[0],			aiIceBlockInit,		aiIceBlockInit2  },

	{ AI_CRATE,				"AI_CRATE",				&crate[0],				aiCrateInit,			aiCrateInit2  },
	{ AI_LIGHTBARREL,		"AI_LIGHTBARREL",		&barrelLight[0],		aiBarrelLightInit,		aiBarrelLightInit2  },
	{ AI_HEAVYBARREL,		"AI_HEAVYBARREL",		&barrelHeavy[0],		aiBarrelHeavyInit,		aiBarrelHeavyInit2  },

	{ ITEM_CELL,			"ITEM_CELL",			&cell[0],				aiCellInit,				aiCellInit2  },
	{ ITEM_ENV_WHITE,		"ITEM_ENV_WHITE",		&envelopeWhite[0],		aiEnvelopeWhiteInit,	aiEnvelopeWhiteInit2  },
	{ ITEM_TRANSCEIVER,		"ITEM_TRANSCEIVER",		&transceiver[0],		aiTransceiverInit,		aiTransceiverInit2  },
	{ ITEM_MONKEYSTONE,		"ITEM_MONKEYSTONE",		&monkeystone[0],		aiMonkeystoneInit,		aiMonkeystoneInit2  },
	{ ITEM_GEM_WHITE,		"ITEM_GEM_WHITE",		&gemWhite[0],			aiGemWhiteInit,			aiGemWhiteInit2  },
	{ ITEM_CHICKEN,			"ITEM_CHICKEN",			&itemChicken[0],		aiItemChickenInit,		aiItemChickenInit2  },
	{ ITEM_GOO_CUP,			"ITEM_GOO_CUP",			&gooCup[0],				aiGooCupInit,			aiGooCupInit2  },
	{ ITEM_CABKEY,			"ITEM_CABKEY",			&cabKey[0],				aiCabKeyInit,			aiCabKeyInit2  },
	{ ITEM_ENV_BLUE,		"ITEM_ENV_BLUE",		&envelopeBlue[0],		aiEnvelopeBlueInit,		aiEnvelopeBlueInit2  },
	{ ITEM_ENV_RED,			"ITEM_ENV_RED",			&envelopeRed[0],		aiEnvelopeRedInit,		aiEnvelopeRedInit2  },
	{ ITEM_CLUB,			"ITEM_CLUB",			&club[0],				aiClubInit,				aiClubInit2  },
	{ ITEM_ROBOSTUNNER,		"ITEM_ROBOSTUNNER",		&roboStunner[0],		aiRoboStunnerInit,		aiRoboStunnerInit2  },
	{ ITEM_SLUGSLINGER,		"ITEM_SLUGSLINGER",		&slugSlinger[0],		aiSlugSlingerInit,		aiSlugSlingerInit2  },

	{ ITEM_ENV_GREEN,		"ITEM_ENV_GREEN",		&envelopeGreen[0],		aiEnvelopeGreenInit,	aiEnvelopeGreenInit2  },
	{ ITEM_GEM_BLUE,		"ITEM_GEM_BLUE",		&gemBlue[0],			aiGemBlueInit,			aiGemBlueInit2  },
	{ ITEM_GEM_RED,			"ITEM_GEM_RED",			&gemRed[0],				aiGemRedInit,			aiGemRedInit2  },
	{ ITEM_GEM_GREEN,		"ITEM_GEM_GREEN",		&gemGreen[0],			aiGemGreenInit,			aiGemGreenInit2  },
	{ ITEM_TEACUP,			"ITEM_TEACUP",			&teaCup[0],				aiTeaCupInit,			aiTeaCupInit2  },
	{ ITEM_COOKIE,			"ITEM_COOKIE",			&cookie[0],				aiCookieInit,			aiCookieInit2  },
	{ ITEM_BURGER,			"ITEM_BURGER",			&burger[0],				aiBurgerInit,			aiBurgerInit2  },
	{ ITEM_PDA,				"ITEM_PDA",				&pda[0],				aiPdaInit,				aiPdaInit2  },
	{ ITEM_BOOK,			"ITEM_BOOK",			&book[0],				aiBookInit,				aiBookInit2  },
	{ ITEM_CLIPBOARD,		"ITEM_CLIPBOARD",		&clipboard[0],			aiClipboardInit,		aiClipboardInit2  },
	{ ITEM_NOTE,			"ITEM_NOTE",			&note[0],				aiNoteInit,				aiNoteInit2  },
	{ ITEM_KEYCARD_WHITE,	"ITEM_KEYCARD_WHITE",	&keycardWhite[0],		aiKeycardWhiteInit,		aiKeycardWhiteInit2  },
	{ ITEM_KEYCARD_BLUE,	"ITEM_KEYCARD_BLUE",	&keycardBlue[0],		aiKeycardBlueInit,		aiKeycardBlueInit2  },
	{ ITEM_KEYCARD_RED,		"ITEM_KEYCARD_RED",		&keycardRed[0],			aiKeycardRedInit,		aiKeycardRedInit2  },
	{ ITEM_KEYCARD_GREEN,	"ITEM_KEYCARD_GREEN",	&keycardGreen[0],		aiKeycardGreenInit,	aiKeycardGreenInit2  },
	{ ITEM_KEYCARD_PURPLE,	"ITEM_KEYCARD_PURPLE",	&keycardPurple[0],		aiKeycardPurpleInit,	aiKeycardPurpleInit2  },
	{ ITEM_KEYCARD_BLACK,	"ITEM_KEYCARD_BLACK",	&keycardBlack[0],		aiKeycardBlackInit,	aiKeycardBlackInit2  },
	{ ITEM_DOLLYTOOL1,		"ITEM_DOLLYTOOL1",		&dollyTool1[0],			aiDollyTool1Init,		aiDollyTool1Init2  },
	{ ITEM_DOLLYTOOL2,		"ITEM_DOLLYTOOL2",		&dollyTool2[0],			aiDollyTool2Init,		aiDollyTool2Init2  },
	{ ITEM_DOLLYTOOL3,		"ITEM_DOLLYTOOL3",		&dollyTool3[0],			aiDollyTool3Init,		aiDollyTool3Init2  },
	{ ITEM_DOLLYTOOL4,		"ITEM_DOLLYTOOL4",		&dollyTool4[0],			aiDollyTool4Init,		aiDollyTool4Init2  },
	{ ITEM_SEED,			"ITEM_SEED",			&seed[0],				aiSeedInit,				aiSeedInit2  },
	{ ITEM_SODA,			"ITEM_SODA",			&soda[0],				aiSodaInit,				aiSodaInit2  },
	{ ITEM_ROUTER,			"ITEM_ROUTER",			&router[0],				aiRouterInit,			aiRouterInit2  },
	{ ITEM_SLICER,			"ITEM_SLICER",			&slicer[0],				aiSlicerInit,			aiSlicerInit2  },
	{ ITEM_PACKAGE,			"ITEM_PACKAGE",			&package[0],			aiPackageInit,			aiPackageInit2  },

	{ END_AI_TYPES,			NULL,					NULL,					NULL,					NULL }
};

AI::AI() {
	_ents = new Common::Array<AIEntity *>;
	_floats = new Common::Array<AIEntity *>;
	_arrowPaths = new Common::Array<ArrowPath *>;
	_triggerList = new Common::Array<Trigger *>;
	_hereList = new Common::Array<HereT *>;

	warning("REMOVE: Remove for final. Used here due to lack of a MENU");
	_numGems = _numGooCups = _numMonkeystones = _numInventory = _numDeliveries = 0;

	_stunAnim = 0;
	_stunTimer = g_system->getMillis();
}

AI::~AI() {
	delete _ents;
	delete _floats;
	delete _arrowPaths;
	delete _triggerList;
	delete _hereList;
}

bool AI::init() {
	warning("STUB: AI::init incomplete");

	_debugQMark = new Tile;
	_debugQMark->load(g_hdb->_fileMan->findFirstData("icon_question_mark", TYPE_ICON32));

	// Clear Waypoint list and load Waypoint graphics
	_numWaypoints = 0;
	_waypointGfx[0] = new Tile;
	_waypointGfx[0]->load(g_hdb->_fileMan->findFirstData("icon_waypoint_select1", TYPE_ICON32));
	_waypointGfx[1] = new Tile;
	_waypointGfx[1]->load(g_hdb->_fileMan->findFirstData("icon_waypoint_select2", TYPE_ICON32));
	_waypointGfx[2] = new Tile;
	_waypointGfx[2]->load(g_hdb->_fileMan->findFirstData("icon_waypoint_select3", TYPE_ICON32));
	_waypointGfx[3] = new Tile;
	_waypointGfx[3]->load(g_hdb->_fileMan->findFirstData("icon_waypoint_select4", TYPE_ICON32));

	// Setup Vars to reference SPECIAL Map Tiles
	_useSwitchOff	= g_hdb->_gfx->getTileIndex("anim_t32_switch_off01");
	_useSwitchOn	= g_hdb->_gfx->getTileIndex("t32_switch_on");
	_useSwitch2Off	= g_hdb->_gfx->getTileIndex("anim_t32_1switch_off01");
	_useSwitch2On	= g_hdb->_gfx->getTileIndex("t32_1switch_on");
//	_useHandswitchOn	= g_hdb->_gfx->getTileIndex("t32_ship_handswitch_on");
//	_useHandswitchOff	= g_hdb->_gfx->getTileIndex("anim_t32_ship_handswitch_off1");
	_useHolderEmpty	= g_hdb->_gfx->getTileIndex("anim_t32_holder_empty1");
	_useHolderFull	= g_hdb->_gfx->getTileIndex("t32_holder_full");
	_useMailsorter	= g_hdb->_gfx->getTileIndex("anim_t32_mailsort1");
	_useAskcomp		= g_hdb->_gfx->getTileIndex("anim_t32_askcomp1");

	_targetDoorN	= g_hdb->_gfx->getTileIndex("t32_door_n_1");
	_targetDoorP	= g_hdb->_gfx->getTileIndex("t32_door_p_1");
	_targetDoorS	= g_hdb->_gfx->getTileIndex("t32_door_s_1");
	_targetDoorNv	= g_hdb->_gfx->getTileIndex("t32_door_nv_1");
	_targetDoorPv	= g_hdb->_gfx->getTileIndex("t32_door_pv_1");
	_targetDoorSv	= g_hdb->_gfx->getTileIndex("t32_door_sv_1");

	_targetDoor2N	= g_hdb->_gfx->getTileIndex("t32_door2_n_1");
	_targetDoor2P	= g_hdb->_gfx->getTileIndex("t32_door2_p_1");
	_targetDoor2S	= g_hdb->_gfx->getTileIndex("t32_door2_s_1");
	_targetDoor2Nv	= g_hdb->_gfx->getTileIndex("t32_door2_nv_1");
	_targetDoor2Pv	= g_hdb->_gfx->getTileIndex("t32_door2_pv_1");
	_targetDoor2Sv	= g_hdb->_gfx->getTileIndex("t32_door2_sv_1");

	_target2DoorN	= g_hdb->_gfx->getTileIndex("t32_e2_door_n_1");
	_target2DoorP	= g_hdb->_gfx->getTileIndex("t32_e2_door_p_1");
	_target2DoorS	= g_hdb->_gfx->getTileIndex("t32_e2_door_s_1");
	_target2DoorNv	= g_hdb->_gfx->getTileIndex("t32_e2_door_nv_1");
	_target2DoorPv	= g_hdb->_gfx->getTileIndex("t32_e2_door_pv_1");
	_target2DoorSv	= g_hdb->_gfx->getTileIndex("t32_e2_door_sv_1");

	_target3DoorN	= g_hdb->_gfx->getTileIndex("t32_e3_door_n_1");
	_target3DoorP	= g_hdb->_gfx->getTileIndex("t32_e3_door_p_1");
	_target3DoorS	= g_hdb->_gfx->getTileIndex("t32_e3_door_s_1");
	_target3DoorNv	= g_hdb->_gfx->getTileIndex("t32_e3_door_nv_1");
	_target3DoorPv	= g_hdb->_gfx->getTileIndex("t32_e3_door_pv_1");
	_target3DoorSv	= g_hdb->_gfx->getTileIndex("t32_e3_door_sv_1");

	_targetBridgeU	= g_hdb->_gfx->getTileIndex("t32_bridgeup1");
	_targetBridgeD	= g_hdb->_gfx->getTileIndex("t32_bridgedown1");
	_targetBridgeL	= g_hdb->_gfx->getTileIndex("t32_bridgeleft1");
	_targetBridgeR	= g_hdb->_gfx->getTileIndex("t32_bridgeright1");
	_targetBridgeMidLR	= g_hdb->_gfx->getTileIndex("t32_mgrate_mid");
	_targetBridgeMidUD	= g_hdb->_gfx->getTileIndex("t32_mgrate_tbmid");
	_touchplateOn	= g_hdb->_gfx->getTileIndex("t32_touchplateon");
	_touchplateOff	= g_hdb->_gfx->getTileIndex("t32_touchplateoff");
	_blockpole		= g_hdb->_gfx->getTileIndex("t32_blockpole_1");
	_useTeleporter	= g_hdb->_gfx->getTileIndex("anim_t32_teleporter1");

	_useSwitchOff	= g_hdb->_gfx->getTileIndex("t32_temple_touchplate_on");
	_useSwitchOff	= g_hdb->_gfx->getTileIndex("t32_temple_touchplate_off");

	_kcHolderWhiteOff	= g_hdb->_gfx->getTileIndex("anim_t32_kcholder_white_off1");
	_kcHolderWhiteOn	= g_hdb->_gfx->getTileIndex("t32_kcholder_white_on");
	_kcHolderBlueOff	= g_hdb->_gfx->getTileIndex("anim_t32_kcholder_blue_off1");
	_kcHolderBlueOn		= g_hdb->_gfx->getTileIndex("t32_kcholder_blue_on");
	_kcHolderRedOff		= g_hdb->_gfx->getTileIndex("anim_t32_kcholder_red_off1");
	_kcHolderRedOn		= g_hdb->_gfx->getTileIndex("t32_kcholder_red_on");
	_kcHolderGreenOff	= g_hdb->_gfx->getTileIndex("anim_t32_kcholder_green_off1");
	_kcHolderGreenOn	= g_hdb->_gfx->getTileIndex("t32_kcholder_green_on");
	_kcHolderPurpleOff	= g_hdb->_gfx->getTileIndex("anim_t32_kcholder_purple_off1");
	_kcHolderPurpleOn	= g_hdb->_gfx->getTileIndex("t32_kcholder_purple_on");
	_kcHolderBlackOff	= g_hdb->_gfx->getTileIndex("anim_t32_kcholder_black_off1");
	_kcHolderBlackOn	= g_hdb->_gfx->getTileIndex("t32_kcholder_black_on");

	// icepuff snowball
	_icepSnowballGfxDown = _icepSnowballGfxLeft =
		_icepSnowballGfxRight = NULL;

	// Frogglick
	_tileFroglickMiddleUD = _tileFroglickMiddleLR = NULL;
	_tileFroglickWiggleUD[0] = _tileFroglickWiggleLeft[0] = _tileFroglickWiggleRight[0] = NULL;

	// Dragon
	_gfxDragonAsleep = NULL;

	// laser beam
	_gfxLaserbeamUD[0] = _gfxLaserbeamUD[1] = _gfxLaserbeamLR[0] = _gfxLaserbeamLR[1] = NULL;

	_laserRescan = false;
	_laserOnScreen = false;

	_dummyPlayer.type = AI_GUY;
	_dummyLaser.type = AI_LASERBEAM;
	strcpy(_dummyPlayer.entityName, "Virtual Player");
	_playerRunning = false;

	restartSystem();
	return true;
}

void AI::clearPersistent() {
	_numGems = _numGooCups = _numMonkeystones = 0;
}

void AI::restartSystem() {
	warning("STUB: AI::restartSystem incomplete");

	// Clear Player
	_player = NULL;
	_playerDead = false;
	_playerInvisible = false;
	_playerOnIce = false;
	_playerEmerging = false;

	// Clean up Player Graphics Storage
	memset(_horrible1Gfx, NULL, kMaxDeathFrames * sizeof(Tile *));
	memset(_horrible2Gfx, NULL, kMaxDeathFrames * sizeof(Tile *));
	memset(_horrible3Gfx, NULL, kMaxDeathFrames * sizeof(Tile *));
	memset(_horrible4Gfx, NULL, kMaxDeathFrames * sizeof(Tile *));
	memset(_plummetGfx, NULL, kMaxDeathFrames * sizeof(Tile *));
	memset(_dyingGfx, NULL, kMaxDeathFrames * sizeof(Tile *));

	memset(_pushdownGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_pushupGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_pushleftGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_pushrightGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_stunDownGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_stunUpGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_stunLeftGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_stunRightGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_slugDownGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_slugUpGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_slugLeftGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_slugRightGfx, NULL, kMaxAnimFrames * sizeof(Tile *));

	_horrible1Frames = _horrible2Frames = _horrible3Frames = _horrible4Frames = 0;
	_plummetFrames = _dyingFrames = 0;
	_pushdownFrames = _pushupFrames = _pushleftFrames = _pushrightFrames = 0;
	_stunDownFrames = _stunUpFrames = _stunLeftFrames = _stunRightFrames = 0;
	_slugDownFrames = _slugUpFrames = _slugLeftFrames = _slugRightFrames = 0;

	if (_clubDownFrames) {
		_clubDownFrames = 3;
		_clubUpFrames = 3;
		_clubLeftFrames = 3;
		_clubRightFrames = 3;
	}

	memset(_clubDownGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_clubUpGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_clubLeftGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_clubRightGfx, NULL, kMaxAnimFrames * sizeof(Tile *));

	int i;
	if (_icepSnowballGfxDown) {
		_icepSnowballGfxDown->free();
		_icepSnowballGfxDown = NULL;
	}
	if (_icepSnowballGfxLeft) {
		_icepSnowballGfxLeft->free();
		_icepSnowballGfxLeft = NULL;
	}
	if (_icepSnowballGfxRight) {
		_icepSnowballGfxRight->free();
		_icepSnowballGfxRight = NULL;
	}

	if (_tileFroglickMiddleUD) {
		_tileFroglickMiddleUD->free();
		_tileFroglickMiddleUD = NULL;
	}
	if (_tileFroglickWiggleUD[0]) {
		for (i = 0; i < 3; i++) {
			_tileFroglickWiggleUD[i]->free();
			_tileFroglickWiggleUD[i] = NULL;
		}
	}

	if (_tileFroglickMiddleLR) {
		_tileFroglickMiddleLR->free();
		_tileFroglickMiddleLR = NULL;
	}
	if (_tileFroglickWiggleLeft[0]) {
		for (i = 0; i < 3; i++) {
			_tileFroglickWiggleLeft[i]->free();
			_tileFroglickWiggleLeft[i] = NULL;
		}
	}
	if (_tileFroglickWiggleRight[0]) {
		for (i = 0; i < 3; i++) {
			_tileFroglickWiggleRight[i]->free();
			_tileFroglickWiggleRight[i] = NULL;
		}
	}

	// dragon!  see ya!
	if (_gfxDragonAsleep) {
		_gfxDragonAsleep->free();
		_gfxDragonAsleep = NULL;
		_gfxDragonFlap[0]->free();
		_gfxDragonFlap[1]->free();
		_gfxDragonFlap[0] = _gfxDragonFlap[1] = NULL;
		_gfxDragonBreathe[0]->free();
		_gfxDragonBreathe[1]->free();
		_gfxDragonBreathe[2]->free();
		_gfxDragonBreathe[0] = _gfxDragonBreathe[1] =
			_gfxDragonBreathe[2] = NULL;
	}

	// laser beams
	if (_gfxLaserbeamUD[0]) {
		for (i = 0; i < 4; i++) {
			_gfxLaserbeamUD[i]->free();
			_gfxLaserbeamUDTop[i]->free();
			_gfxLaserbeamUDBottom[i]->free();
			_gfxLaserbeamLR[i]->free();
			_gfxLaserbeamLRLeft[i]->free();
			_gfxLaserbeamLRRight[i]->free();

			_gfxLaserbeamUD[i] = NULL;
			_gfxLaserbeamUDTop[i] = NULL;
			_gfxLaserbeamUDBottom[i] = NULL;
			_gfxLaserbeamLR[i] = NULL;
			_gfxLaserbeamLRLeft[i] = NULL;
			_gfxLaserbeamLRRight[i] = NULL;
		}
	}

	// Clear the Action list
	memset(_actions, 0, sizeof(_actions));

	// Clear Teleporter list
	memset(_teleporters, 0, sizeof(_teleporters));
	_numTeleporters = 0;

	// Clear the Auto-Action list
	memset(_autoActions, 0, sizeof(_autoActions));

	// Clear the Callback List
	memset(_callbacks, 0, sizeof(_callbacks));

	// Clear the Entity List
	_ents->clear();

	// Clear the Floats List
	_floats->clear();

	// Clear the Lua List
	memset(_luaList, 0, sizeof(_luaList));
	_numLuaList = 0;

	// Clear Anim Targets List
	_animTargets.clear();

	// Clear ArrowPath List
	_arrowPaths->clear();

	// Clear Trigger List
	_triggerList->clear();

	// Clear Here List
	_hereList->clear();

	// Clear Cinematic System
	_cineActive = _cameraLock = _playerLock = _cineAborted = false;

	// Clear waypoints
	memset(&_waypoints[0], 0, sizeof(_waypoints));
	_numWaypoints = 0;

	// Clear Bridges
	memset(&_bridges[0], 0, sizeof(_bridges));
	_numBridges = 0;

	// No Gate Puddles
	_gatePuddles = 0;
}

void AI::initAnimInfo() {
	if (g_hdb->_map->checkOneTileExistInRange(_useSwitchOff, 2))
		g_hdb->_gfx->getTile(_useSwitchOn);
	if (g_hdb->_map->checkOneTileExistInRange(_useSwitch2Off, 2))
		g_hdb->_gfx->getTile(_useSwitch2On);
	if (g_hdb->_map->checkOneTileExistInRange(_useHolderEmpty, 2))
		g_hdb->_gfx->getTile(_useHolderFull);
	if (g_hdb->_map->checkOneTileExistInRange(_useHandswitchOff, 2))
		g_hdb->_gfx->getTile(_useHandswitchOn);

	if (g_hdb->_map->checkOneTileExistInRange(_targetDoorN, 4))
		g_hdb->_gfx->cacheTileSequence(_targetDoorN, 4);
	if (g_hdb->_map->checkOneTileExistInRange(_targetDoorP, 4))
		g_hdb->_gfx->cacheTileSequence(_targetDoorP, 4);
	if (g_hdb->_map->checkOneTileExistInRange(_targetDoorS, 4))
		g_hdb->_gfx->cacheTileSequence(_targetDoorS, 4);
	if (g_hdb->_map->checkOneTileExistInRange(_targetDoorNv, 4))
		g_hdb->_gfx->cacheTileSequence(_targetDoorNv, 4);
	if (g_hdb->_map->checkOneTileExistInRange(_targetDoorPv, 4))
		g_hdb->_gfx->cacheTileSequence(_targetDoorPv, 4);
	if (g_hdb->_map->checkOneTileExistInRange(_targetDoorSv, 4))
		g_hdb->_gfx->cacheTileSequence(_targetDoorSv, 4);

	if (g_hdb->_map->checkOneTileExistInRange(_targetDoor2N, 4))
		g_hdb->_gfx->cacheTileSequence(_targetDoor2N, 4);
	if (g_hdb->_map->checkOneTileExistInRange(_targetDoor2P, 4))
		g_hdb->_gfx->cacheTileSequence(_targetDoor2P, 4);
	if (g_hdb->_map->checkOneTileExistInRange(_targetDoor2S, 4))
		g_hdb->_gfx->cacheTileSequence(_targetDoor2S, 4);
	if (g_hdb->_map->checkOneTileExistInRange(_targetDoor2Nv, 4))
		g_hdb->_gfx->cacheTileSequence(_targetDoor2Nv, 4);
	if (g_hdb->_map->checkOneTileExistInRange(_targetDoor2Pv, 4))
		g_hdb->_gfx->cacheTileSequence(_targetDoor2Pv, 4);
	if (g_hdb->_map->checkOneTileExistInRange(_targetDoor2Sv, 4))
		g_hdb->_gfx->cacheTileSequence(_targetDoor2Sv, 4);

	if (g_hdb->_map->checkOneTileExistInRange(_target2DoorN, 4))
		g_hdb->_gfx->cacheTileSequence(_target2DoorN, 4);
	if (g_hdb->_map->checkOneTileExistInRange(_target2DoorP, 4))
		g_hdb->_gfx->cacheTileSequence(_target2DoorP, 4);
	if (g_hdb->_map->checkOneTileExistInRange(_target2DoorS, 4))
		g_hdb->_gfx->cacheTileSequence(_target2DoorS, 4);
	if (g_hdb->_map->checkOneTileExistInRange(_target2DoorNv, 4))
		g_hdb->_gfx->cacheTileSequence(_target2DoorNv, 4);
	if (g_hdb->_map->checkOneTileExistInRange(_target2DoorPv, 4))
		g_hdb->_gfx->cacheTileSequence(_target2DoorPv, 4);
	if (g_hdb->_map->checkOneTileExistInRange(_target2DoorSv, 4))
		g_hdb->_gfx->cacheTileSequence(_target2DoorSv, 4);

	if (g_hdb->_map->checkOneTileExistInRange(_target3DoorN, 4))
		g_hdb->_gfx->cacheTileSequence(_target3DoorN, 4);
	if (g_hdb->_map->checkOneTileExistInRange(_target3DoorP, 4))
		g_hdb->_gfx->cacheTileSequence(_target3DoorP, 4);
	if (g_hdb->_map->checkOneTileExistInRange(_target3DoorS, 4))
		g_hdb->_gfx->cacheTileSequence(_target3DoorS, 4);
	if (g_hdb->_map->checkOneTileExistInRange(_target3DoorNv, 4))
		g_hdb->_gfx->cacheTileSequence(_target3DoorNv, 4);
	if (g_hdb->_map->checkOneTileExistInRange(_target3DoorPv, 4))
		g_hdb->_gfx->cacheTileSequence(_target3DoorPv, 4);
	if (g_hdb->_map->checkOneTileExistInRange(_target3DoorSv, 4))
		g_hdb->_gfx->cacheTileSequence(_target3DoorSv, 4);

	if (g_hdb->_map->checkOneTileExistInRange(_targetBridgeU, 3))
		g_hdb->_gfx->cacheTileSequence(_targetBridgeU, 3);
	if (g_hdb->_map->checkOneTileExistInRange(_targetBridgeD, 3))
		g_hdb->_gfx->cacheTileSequence(_targetBridgeD, 3);
	if (g_hdb->_map->checkOneTileExistInRange(_targetBridgeL, 3))
		g_hdb->_gfx->cacheTileSequence(_targetBridgeL, 3);
	if (g_hdb->_map->checkOneTileExistInRange(_targetBridgeR, 3))
		g_hdb->_gfx->cacheTileSequence(_targetBridgeR, 3);

	g_hdb->_gfx->cacheTileSequence(_targetBridgeMidLR, 1);
	g_hdb->_gfx->cacheTileSequence(_targetBridgeMidUD, 1);

	if (g_hdb->_map->checkOneTileExistInRange(_touchplateOff, 2))
		g_hdb->_gfx->cacheTileSequence(_touchplateOff, 2);
	if (g_hdb->_map->checkOneTileExistInRange(_templeTouchpOff, 2))
		g_hdb->_gfx->cacheTileSequence(_templeTouchpOff, 2);
	if (g_hdb->_map->checkOneTileExistInRange(_blockpole, 4))
		g_hdb->_gfx->cacheTileSequence(_blockpole, 4);

	if (g_hdb->_map->checkOneTileExistInRange(_kcHolderWhiteOff, 2))
		g_hdb->_gfx->getTile(_kcHolderWhiteOn);
	if (g_hdb->_map->checkOneTileExistInRange(_kcHolderBlueOff, 2))
		g_hdb->_gfx->getTile(_kcHolderBlueOn);
	if (g_hdb->_map->checkOneTileExistInRange(_kcHolderRedOff, 2))
		g_hdb->_gfx->getTile(_kcHolderRedOn);
	if (g_hdb->_map->checkOneTileExistInRange(_kcHolderGreenOff, 2))
		g_hdb->_gfx->getTile(_kcHolderGreenOn);
	if (g_hdb->_map->checkOneTileExistInRange(_kcHolderPurpleOff, 2))
		g_hdb->_gfx->getTile(_kcHolderPurpleOn);
	if (g_hdb->_map->checkOneTileExistInRange(_kcHolderBlackOff, 2))
		g_hdb->_gfx->getTile(_kcHolderBlackOn);
}

const char *AITypeStr[] = {
	"AI_NONE",
	"AI_GUY",
	"AI_DOLLY",
	"AI_SPACEDUDE",
	"AI_SERGEANT",
	"AI_SCIENTIST",
	"AI_WORKER",
	"AI_DEADWORKER",
	"AI_ACCOUNTANT",
	"AI_RAILRIDER",
	"AI_RAILRIDER_ON",
	"AI_VORTEXIAN",
	"AI_CHICKEN",
	"AI_GEM_ATTACK",
	"AI_SLUG_ATTACK",

	"AI_LASER",
	"AI_LASERBEAM",
	"AI_DIVERTER",
	"AI_FOURFIRER",
	"AI_OMNIBOT",
	"AI_TURNBOT",
	"AI_SHOCKBOT",
	"AI_RIGHTBOT",
	"AI_PUSHBOT",
	"AI_LISTENBOT",
	"AI_MAINTBOT",
	"AI_OMNIBOT_MISSILE",
	"AI_DEADEYE",
	"AI_MEERKAT",
	"AI_FATFROG",
	"AI_GOODFAIRY",
	"AI_BADFAIRY",
	"AI_ICEPUFF",
	"AI_BUZZFLY",
	"AI_DRAGON",
	"AI_GATEPUDDLE",

	"AI_CRATE",
	"AI_LIGHTBARREL",
	"AI_HEAVYBARREL",
	"AI_BOOMBARREL",
	"AI_FROGSTATUE",

	"AI_MAGIC_EGG",
	"AI_ICE_BLOCK",

	"ITEM_CELL",
	"ITEM_ENV_WHITE",
	"ITEM_ENV_RED",
	"ITEM_ENV_BLUE",
	"ITEM_ENV_GREEN",
	"ITEM_TRANSCEIVER",
	"ITEM_CLUB",
	"ITEM_ROBOSTUNNER",
	"ITEM_SLUGSLINGER",
	"ITEM_MONKEYSTONE",
	"ITEM_GEM_WHITE",
	"ITEM_GEM_BLUE",
	"ITEM_GEM_RED",
	"ITEM_GEM_GREEN",
	"ITEM_GOO_CUP",
	"ITEM_TEACUP",
	"ITEM_COOKIE",
	"ITEM_BURGER",
	"ITEM_PDA",
	"ITEM_BOOK",
	"ITEM_CLIPBOARD",
	"ITEM_NOTE",
	"ITEM_KEYCARD_WHITE",
	"ITEM_KEYCARD_BLUE",
	"ITEM_KEYCARD_RED",
	"ITEM_KEYCARD_GREEN",
	"ITEM_KEYCARD_PURPLE",
	"ITEM_KEYCARD_BLACK",
	"ITEM_CABKEY",
	"ITEM_DOLLYTOOL1",
	"ITEM_DOLLYTOOL2",
	"ITEM_DOLLYTOOL3",
	"ITEM_DOLLYTOOL4",
	"ITEM_SEED",
	"ITEM_SODA",
	"ITEM_ROUTER",
	"ITEM_SLICER",
	"ITEM_CHICKEN",
	"ITEM_PACKAGE",

	"INFO_FAIRY_SRC",
	"INFO_FAIRY_SRC2",
	"INFO_FAIRY_SRC3",
	"INFO_FAIRY_SRC4",
	"INFO_FAIRY_SRC5",
	"INFO_FAIRY_DEST",
	"INFO_FAIRY_DEST2",
	"INFO_FAIRY_DEST3",
	"INFO_FAIRY_DEST4",
	"INFO_FAIRY_DEST5",
	"INFO_TRIGGER",
	"INFO_SET_MUSIC",
	"INFO_PROMOTE",
	"INFO_DEMOTE",
	"INFO_LUA",
	"INFO_HERE",
	"INFO_ARROW_TURN",
	"INFO_ARROW_STOP",
	"INFO_ARROW_4WAY",
	"INFO_TELEPORTER1",
	"INFO_TELEPORTER2",
	"INFO_TELEPORTER3",
	"INFO_TELEPORTER4",
	"INFO_TELEPORTER5",
	"INFO_TELEPORTER6",
	"INFO_TELEPORTER7",
	"INFO_TELEPORTER8",
	"INFO_TELEPORTER9",
	"INFO_TELEPORTER10",
	"INFO_TELEPORTER11",
	"INFO_TELEPORTER12",
	"INFO_TELEPORTER13",
	"INFO_TELEPORTER14",
	"INFO_TELEPORTER15",
	"INFO_TELEPORTER16",
	"INFO_TELEPORTER17",
	"INFO_TELEPORTER18",
	"INFO_TELEPORTER19",
	"INFO_TELEPORTER20",
	"INFO_LEVELEXIT",
	"INFO_ACTION1",
	"INFO_ACTION2",
	"INFO_ACTION3",
	"INFO_ACTION4",
	"INFO_ACTION5",
	"INFO_ACTION6",
	"INFO_ACTION7",
	"INFO_ACTION8",
	"INFO_ACTION9",
	"INFO_ACTION10",
	"INFO_ACTION11",
	"INFO_ACTION12",
	"INFO_ACTION13",
	"INFO_ACTION14",
	"INFO_ACTION15",
	"INFO_ACTION16",
	"INFO_ACTION17",
	"INFO_ACTION18",
	"INFO_ACTION19",
	"INFO_ACTION20",
	"INFO_ACTION_AUTO",

	"INFO_QMARK",
	"INFO_DEBUG",
	"END_AI_TYPES"
};

const char *AIType2Str(AIType v) {
	return AITypeStr[v];
}

const char *AIStateStr[] = {
	"STATE_NONE",
	"STATE_STANDDOWN",
	"STATE_STANDUP",
	"STATE_STANDLEFT",
	"STATE_STANDRIGHT",
	"STATE_BLINK",
	"STATE_MOVEUP",
	"STATE_MOVEDOWN",
	"STATE_MOVELEFT",
	"STATE_MOVERIGHT",
	"STATE_DYING",
	"STATE_DEAD",
	"STATE_HORRIBLE1",
	"STATE_HORRIBLE2",
	"STATE_HORRIBLE3",
	"STATE_HORRIBLE4",
	"STATE_GOODJOB",
	"STATE_PLUMMET",

	"STATE_PUSHUP",
	"STATE_PUSHDOWN",
	"STATE_PUSHLEFT",
	"STATE_PUSHRIGHT",
	"STATE_GRABUP",
	"STATE_GRABDOWN",
	"STATE_GRABLEFT",
	"STATE_GRABRIGHT",
	"STATE_ATK_CLUB_UP",
	"STATE_ATK_CLUB_DOWN",
	"STATE_ATK_CLUB_LEFT",
	"STATE_ATK_CLUB_RIGHT",
	"STATE_ATK_STUN_DOWN",
	"STATE_ATK_STUN_UP",
	"STATE_ATK_STUN_LEFT",
	"STATE_ATK_STUN_RIGHT",
	"STATE_ATK_SLUG_DOWN",
	"STATE_ATK_SLUG_UP",
	"STATE_ATK_SLUG_LEFT",
	"STATE_ATK_SLUG_RIGHT",

	"STATE_FLOATING",
	"STATE_FLOATDOWN",
	"STATE_FLOATUP",
	"STATE_FLOATLEFT",
	"STATE_FLOATRIGHT",
	"STATE_MELTED",
	"STATE_SLIDING",
	"STATE_SHOCKING",
	"STATE_EXPLODING",

	"STATE_USEDOWN",
	"STATE_USEUP",
	"STATE_USELEFT",
	"STATE_USERIGHT",

	"STATE_MEER_MOVE",
	"STATE_MEER_APPEAR",
	"STATE_MEER_BITE",
	"STATE_MEER_DISAPPEAR",
	"STATE_MEER_LOOK",

	"STATE_ICEP_PEEK",
	"STATE_ICEP_APPEAR",
	"STATE_ICEP_THROWDOWN",
	"STATE_ICEP_THROWRIGHT",
	"STATE_ICEP_THROWLEFT",
	"STATE_ICEP_DISAPPEAR",

	"STATE_LICKDOWN",
	"STATE_LICKLEFT",
	"STATE_LICKRIGHT",

	"STATE_DIVERTER_BL",
	"STATE_DIVERTER_BR",
	"STATE_DIVERTER_TL",
	"STATE_DIVERTER_TR",

	"STATE_KISSRIGHT",
	"STATE_KISSLEFT",
	"STATE_ANGRY",
	"STATE_PANIC",
	"STATE_LAUGH",
	"STATE_DOLLYUSERIGHT",

	"STATE_YELL",

	"STATE_ENDSTATES"
};

const char *AIState2Str(AIState v) {
	return AIStateStr[v];
}

} // End of Namespace
