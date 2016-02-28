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

#include "titanic/carry/arm.h"
#include "titanic/carry/brain.h"
#include "titanic/carry/bridge_piece.h"
#include "titanic/carry/carry.h"
#include "titanic/carry/carry_parrot.h"
#include "titanic/carry/chicken.h"
#include "titanic/carry/crushed_tv.h"
#include "titanic/carry/ear.h"
#include "titanic/carry/eye.h"
#include "titanic/carry/feathers.h"
#include "titanic/carry/fruit.h"
#include "titanic/carry/glass.h"
#include "titanic/carry/hammer.h"
#include "titanic/carry/head_piece.h"
#include "titanic/carry/hose.h"
#include "titanic/carry/key.h"
#include "titanic/carry/liftbot_head.h"
#include "titanic/carry/long_stick.h"
#include "titanic/carry/magazine.h"
#include "titanic/carry/mouth.h"
#include "titanic/carry/napkin.h"
#include "titanic/carry/nose.h"
#include "titanic/carry/note.h"
#include "titanic/carry/parcel.h"
#include "titanic/carry/phonograph_cylinder.h"
#include "titanic/carry/photograph.h"
#include "titanic/carry/plug_in.h"
#include "titanic/carry/sweets.h"

#include "titanic/core/saveable_object.h"
#include "titanic/core/background.h"
#include "titanic/core/click_responder.h"
#include "titanic/core/drop_target.h"
#include "titanic/core/file_item.h"
#include "titanic/core/link_item.h"
#include "titanic/core/list.h"
#include "titanic/core/message_target.h"
#include "titanic/core/movie_clip.h"
#include "titanic/core/multi_drop_target.h"
#include "titanic/core/node_item.h"
#include "titanic/core/project_item.h"
#include "titanic/core/saveable_object.h"
#include "titanic/core/turn_on_object.h"
#include "titanic/core/turn_on_play_sound.h"
#include "titanic/core/tree_item.h"
#include "titanic/core/view_item.h"

#include "titanic/game/announce.h"
#include "titanic/game/cdrom.h"
#include "titanic/game/cdrom_computer.h"
#include "titanic/game/cdrom_tray.h"
#include "titanic/game/computer_screen.h"
#include "titanic/game/credits.h"
#include "titanic/game/credits_button.h"
#include "titanic/game/dead_area.h"
#include "titanic/game/desk_click_responder.h"
#include "titanic/game/doorbot_home_handler.h"
#include "titanic/game/drawer.h"
#include "titanic/game/hammer_dispensor_button.h"
#include "titanic/game/null_port_hole.h"
#include "titanic/game/pet_position.h"
#include "titanic/game/port_hole.h"
#include "titanic/game/room_item.h"
#include "titanic/game/service_elevator_door.h"
#include "titanic/game/sgt_state_room.h"
#include "titanic/game/sgt_upper_doors_sound.h"
#include "titanic/game/start_action.h"
#include "titanic/game/sub_glass.h"
#include "titanic/game/sweet_bowl.h"
#include "titanic/game/television.h"
#include "titanic/game/parrot/parrot_lobby_controller.h"
#include "titanic/game/parrot/parrot_lobby_link_updater.h"
#include "titanic/game/parrot/parrot_lobby_object.h"
#include "titanic/game/parrot/parrot_lobby_view_object.h"
#include "titanic/game/parrot/parrot_loser.h"
#include "titanic/game/parrot/parrot_nut_bowl_actor.h"
#include "titanic/game/parrot/parrot_nut_eater.h"
#include "titanic/game/parrot/parrot_perch_holder.h"
#include "titanic/game/parrot/parrot_succubus.h"
#include "titanic/game/parrot/parrot_trigger.h"

#include "titanic/gfx/act_button.h"
#include "titanic/gfx/changes_season_button.h"
#include "titanic/gfx/chev_left_off.h"
#include "titanic/gfx/chev_left_on.h"
#include "titanic/gfx/chev_right_off.h"
#include "titanic/gfx/chev_right_on.h"
#include "titanic/gfx/chev_send_rec_switch.h"
#include "titanic/gfx/chev_switch.h"
#include "titanic/gfx/elevator_button.h"
#include "titanic/gfx/get_from_succ.h"
#include "titanic/gfx/helmet_on_off.h"
#include "titanic/gfx/home_photo.h"
#include "titanic/gfx/icon_nav_action.h"
#include "titanic/gfx/icon_nav_down.h"
#include "titanic/gfx/icon_nav_left.h"
#include "titanic/gfx/icon_nav_right.h"
#include "titanic/gfx/icon_nav_up.h"
#include "titanic/gfx/keybrd_butt.h"
#include "titanic/gfx/move_object_button.h"
#include "titanic/gfx/pet_mode_off.h"
#include "titanic/gfx/pet_mode_on.h"
#include "titanic/gfx/pet_mode_panel.h"
#include "titanic/gfx/send_to_succ.h"
#include "titanic/gfx/slider_button.h"
#include "titanic/gfx/small_chev_left_off.h"
#include "titanic/gfx/small_chev_left_on.h"
#include "titanic/gfx/small_chev_right_off.h"
#include "titanic/gfx/small_chev_right_on.h"
#include "titanic/gfx/status_change_button.h"
#include "titanic/gfx/st_button.h"
#include "titanic/gfx/toggle_switch.h"

#include "titanic/messages/messages.h"
#include "titanic/messages/mouse_messages.h"
#include "titanic/messages/pet_messages.h"

#include "titanic/moves/enter_bomb_room.h"
#include "titanic/moves/exit_arboretum.h"
#include "titanic/moves/exit_bridge.h"
#include "titanic/moves/exit_state_room.h"
#include "titanic/moves/move_player_in_parrot_room.h"
#include "titanic/moves/move_player_to.h"
#include "titanic/moves/move_player_to_from.h"
#include "titanic/moves/multi_move.h"
#include "titanic/moves/pan_from_pel.h"
#include "titanic/moves/restaurant_pan_handler.h"
#include "titanic/moves/restricted_move.h"
#include "titanic/moves/trip_down_canal.h"

#include "titanic/npcs/barbot.h"
#include "titanic/npcs/bellbot.h"
#include "titanic/npcs/callbot.h"
#include "titanic/npcs/deskbot.h"
#include "titanic/npcs/doorbot.h"
#include "titanic/npcs/liftbot.h"
#include "titanic/npcs/maitre_d.h"
#include "titanic/npcs/mobile.h"
#include "titanic/npcs/parrot.h"
#include "titanic/npcs/starlings.h"
#include "titanic/npcs/succubus.h"
#include "titanic/npcs/summon_bots.h"
#include "titanic/npcs/titania.h"

#include "titanic/sound/auto_music_player.h"

namespace Titanic {

Common::HashMap<Common::String, CSaveableObject::CreateFunction> * 
	CSaveableObject::_classList = nullptr;

#define DEFFN(T) CSaveableObject *Function##T() { return new T(); }
#define ADDFN(T) (*_classList)[#T] = Function##T

DEFFN(CArm);
DEFFN(CBrain);
DEFFN(CBridgePiece);
DEFFN(CCarryParrot);
DEFFN(CChicken);
DEFFN(CCrushedTV);
DEFFN(CFeathers);
DEFFN(CFruit);
DEFFN(CGlass);
DEFFN(CHammer);
DEFFN(CHeadPiece);
DEFFN(CHose);
DEFFN(CKey);
DEFFN(CLiftbotHead);
DEFFN(CLongStick);
DEFFN(CMagazine);
DEFFN(CNapkin);
DEFFN(CNote);
DEFFN(CParcel);
DEFFN(CPhonographCylinder);
DEFFN(CPhotograph);
DEFFN(CPlugIn);
DEFFN(CSweets);

DEFFN(CBackground);
DEFFN(CClickResponder);
DEFFN(CDropTarget);
DEFFN(CFileItem);
DEFFN(CFileListItem);
DEFFN(CLinkItem);
DEFFN(CMessageTarget);
DEFFN(CMovieClip);
DEFFN(CMovieClipList);
DEFFN(CMultiDropTarget);
DEFFN(CNodeItem);
DEFFN(CProjectItem);
DEFFN(CTurnOnObject);
DEFFN(CTurnOnPlaySound);
DEFFN(CTreeItem);
DEFFN(CViewItem);

DEFFN(CAnnounce);
DEFFN(CCDROM);
DEFFN(CCDROMComputer);
DEFFN(CCDROMTray);
DEFFN(CComputerScreen);
DEFFN(CCredits);
DEFFN(CCreditsButton);
DEFFN(CDeadArea);
DEFFN(CDeskClickResponder);
DEFFN(CDoorbotHomeHandler);
DEFFN(CHammerDispensorButton);
DEFFN(CNullPortHole);
DEFFN(CPETPosition);
DEFFN(CPortHole);
DEFFN(CRoomItem);
DEFFN(CServiceElevatorDoor);
DEFFN(CSGTStateRoom);
DEFFN(CSGTUpperDoorsSound);
DEFFN(CStartAction);
DEFFN(CSUBGlass);
DEFFN(CSweetBowl);
DEFFN(CTelevision);
DEFFN(CParrotLobbyController);
DEFFN(CParrotLobbyLinkUpdater);
DEFFN(CParrotLobbyObject);
DEFFN(CParrotLobbyViewObject);
DEFFN(CParrotLoser);
DEFFN(CParrotNutBowlActor);
DEFFN(CParrotNutEater);
DEFFN(CParrotPerchHolder);
DEFFN(CParrotSuccUBus);
DEFFN(CParrotTrigger);

DEFFN(CActButton);
DEFFN(CChangesSeasonButton);
DEFFN(CChevLeftOff);
DEFFN(CChevLeftOn);
DEFFN(CChevRightOff);
DEFFN(CChevRightOn);
DEFFN(CChevSendRecSwitch);
DEFFN(CChevSwitch);
DEFFN(CElevatorButton);
DEFFN(CGetFromSucc);
DEFFN(CHelmetOnOff);
DEFFN(CHomePhoto);
DEFFN(CIconNavAction);
DEFFN(CIconNavDown);
DEFFN(CIconNavLeft);
DEFFN(CIconNavRight);
DEFFN(CIconNavUp);
DEFFN(CKeybrdButt);
DEFFN(CMoveObjectButton);
DEFFN(CPetModeOff);
DEFFN(CPetModeOn);
DEFFN(CPetModePanel);
DEFFN(CSendToSucc);
DEFFN(CSliderButton);
DEFFN(CSmallChevLeftOff);
DEFFN(CSmallChevLeftOn);
DEFFN(CSmallChevRightOff);
DEFFN(CSmallChevRightOn);
DEFFN(CStatusChangeButton);
DEFFN(CSTButton);

DEFFN(CActMsg);
DEFFN(CActivationmsg);
DEFFN(CAddHeadPieceMsg);
DEFFN(CAnimateMaitreDMsg);
DEFFN(CArboretumGateMsg);
DEFFN(CArmPickedUpFromTableMsg);
DEFFN(CAutoSoundEvent);
DEFFN(CBodyInBilgeRoomMsg);
DEFFN(CBowlStateChange);
DEFFN(CCarryObjectArrivedMsg);
DEFFN(CChangeSeasonMsg);
DEFFN(CCheckAllPossibleCodes);
DEFFN(CCheckChevCode);
DEFFN(CChildDragEndMsg);
DEFFN(CChildDragMoveMsg);
DEFFN(CChildDragStartMsg);
DEFFN(CClearChevPanelBits);
DEFFN(CCorrectMusicPlayedMsg);
DEFFN(CCreateMusicPlayerMsg);
DEFFN(CCylinderHolderReadyMsg);
DEFFN(CDeactivationMsg);
DEFFN(CDeliverCCarryMsg);
DEFFN(CDisableMaitreDProdReceptor);
DEFFN(CDismissBotMsg);
DEFFN(CDoffNavHelmet);
DEFFN(CDonNavHelmet);
DEFFN(CDoorAutoSoundEvent);
DEFFN(CDoorbotNeededInElevatorMsg);
DEFFN(CDoorbotNeededInHomeMsg);
DEFFN(CDropobjectMsg);
DEFFN(CDropZoneGotObjectMsg);
DEFFN(CDropZoneLostObjectMsg);
DEFFN(CEditControlMsg);
DEFFN(CEjectCylinderMsg);
DEFFN(CErasePhonographCylinderMsg);
DEFFN(CFreshenCookieMsg);
DEFFN(CGetChevClassBits);
DEFFN(CGetChevClassNum);
DEFFN(CGetChevCodeFromRoomNameMsg);
DEFFN(CGetChevFloorBits);
DEFFN(CGetChevFloorNum);
DEFFN(CGetChevLiftBits);
DEFFN(CGetChevLiftNum);
DEFFN(CGetChevRoomBits);
DEFFN(CGetChevRoomNum);
DEFFN(CHoseConnectedMsg);
DEFFN(CInitializeAnimMsg);
DEFFN(CIsEarBowlPuzzleDone);
DEFFN(CIsHookedOnMsg);
DEFFN(CIsParrotPresentMsg);
DEFFN(CKeyCharMsg);
DEFFN(CLemonFallsFromTreeMsg);
DEFFN(CLightsMsg);
DEFFN(CLockPhonographMsg);
DEFFN(CMaitreDDefeatedMsg);
DEFFN(CMaitreDHappyMsg);
DEFFN(CMissiveOMatActionMsg);
DEFFN(CMouseMsg);
DEFFN(CMouseMoveMsg);
DEFFN(CMouseButtonMsg);
DEFFN(CMouseButtonDownMsg);
DEFFN(CMouseButtonUpMsg);
DEFFN(CMouseButtonDoubleClickMsg);
DEFFN(CMouseDragMsg);
DEFFN(CMouseDragStartMsg);
DEFFN(CMouseDragMoveMsg);
DEFFN(CMouseDragEndMsg);
DEFFN(CMoveToStartPosMsg);
DEFFN(CMovieEndMsg);
DEFFN(CMovieFrameMsg);
DEFFN(CMusicHasStartedMsg);
DEFFN(CMusicHasStoppedMsg);
DEFFN(CMusicSettingChangedMsg);
DEFFN(CNPCPlayAnimationMsg);
DEFFN(CNPCPlayIdleAnimationMsg);
DEFFN(CNPCPlayTalkingAnimationMsg);
DEFFN(CNPCQueueIdleAnimMsg);
DEFFN(CNutPuzzleMsg);
DEFFN(COnSummonBotMsg);
DEFFN(COpeningCreditsMsg);
DEFFN(CPETDeliverMsg);
DEFFN(CPETGainedObjectMsg);
DEFFN(CPETHelmetOnOffMsg);
DEFFN(CPETKeyboardOnOffMsg);
DEFFN(CPETLostObjectMsg);
DEFFN(CPETObjectSelectedMsg);
DEFFN(CPETObjectStateMsg);
DEFFN(CPETPhotoOnOffMsg);
DEFFN(CPETPlaySoundMsg);
DEFFN(CPETReceiveMsg);
DEFFN(CPETSetStarDestinationMsg);
DEFFN(CPETStarFieldLockMsg);
DEFFN(CPETStereoFieldOnOffMsg);
DEFFN(CPETTargetMsg);
DEFFN(CPanningAwayFromParrotMsg);
DEFFN(CParrotSpeakMsg);
DEFFN(CParrotTriesChickenMsg);
DEFFN(CPassOnDragStartMsg);
DEFFN(CPhonographPlayMsg);
DEFFN(CPhonographReadyToPlayMsg);
DEFFN(CPhonographRecordMsg);
DEFFN(CPhonographStopMsg);
DEFFN(CPlayRangeMsg);
DEFFN(CPlayerTriesRestaurantTableMsg);
DEFFN(CPreSaveMsg);
DEFFN(CProdMaitreDMsg);
DEFFN(CPumpingMsg);
DEFFN(CPutBotBackInHisBoxMsg);
DEFFN(CPutParrotBackMsg);
DEFFN(CPuzzleSolvedMsg);
DEFFN(CQueryCylinderHolderMsg);
DEFFN(CQueryCylinderMsg);
DEFFN(CQueryCylinderNameMsg);
DEFFN(CQueryCylinderTypeMsg);
DEFFN(CQueryMusicControlSettingMsg);
DEFFN(CQueryPhonographState);
DEFFN(CRecordOntoCylinderMsg);
DEFFN(CRemoveFromGameMsg);
DEFFN(CReplaceBowlAndNutsMsg);
DEFFN(CRestaurantMusicChanged);
DEFFN(CSendCCarryMsg);
DEFFN(CSenseWorkingMsg);
DEFFN(CServiceElevatorFloorChangeMsg);
DEFFN(CServiceElevatorFloorRequestMsg);
DEFFN(CServiceElevatorMsg);
DEFFN(CSetChevButtonImageMsg);
DEFFN(CSetChevClassBits);
DEFFN(CSetChevFloorBits);
DEFFN(CSetChevLiftBits);
DEFFN(CSetChevPanelBitMsg);
DEFFN(CSetChevPanelButtonsMsg);
DEFFN(CSetChevRoomBits);
DEFFN(CSetMusicControlsMsg);
DEFFN(CSetVarMsg);
DEFFN(CSetVolumeMsg);
DEFFN(CShipSettingMsg);
DEFFN(CShowTextMsg);
DEFFN(CSignalObject);
DEFFN(CSpeechFallsFromTreeMsg);
DEFFN(CStartMusicMsg);
DEFFN(CStatusChangeMsg);
DEFFN(CStopMusicMsg);
DEFFN(CSubAcceptCCarryMsg);
DEFFN(CSubDeliverCCarryMsg);
DEFFN(CSubSendCCarryMsg);
DEFFN(CSUBTransition);
DEFFN(CSubTurnOffMsg);
DEFFN(CSubTurnOnMsg);
DEFFN(CSummonBotMsg);
DEFFN(CSummonBotQuerryMsg);
DEFFN(CTakeHeadPieceMsg);
DEFFN(CTextInputMsg);
DEFFN(CTimeDilationMsg);
DEFFN(CTimeMsg);
DEFFN(CTitleSequenceEndedMsg);
DEFFN(CTransitMsg);
DEFFN(CTransportMsg);
DEFFN(CTriggerAutoMusicPlayerMsg);
DEFFN(CTriggerNPCEvent);
DEFFN(CTrueTalkGetAnimSetMsg);
DEFFN(CTrueTalkGetAssetDetailsMsg);
DEFFN(CTrueTalkGetStateValueMsg);
DEFFN(CTrueTalkNotifySpeechEndedMsg);
DEFFN(CTrueTalkNotifySpeechStartedMsg);
DEFFN(CTrueTalkQueueUpAnimSetMsg);
DEFFN(CTrueTalkSelfQueueAnimSetMsg);
DEFFN(CTrueTalkTriggerActionMsg);
DEFFN(CTurnOff);
DEFFN(CTurnOn);
DEFFN(CUse);
DEFFN(CUseWithCharMsg);
DEFFN(CUseWithOtherMsg);
DEFFN(CVirtualKeyCharMsg);
DEFFN(CVisibleMsg);

DEFFN(CEnterBombRoom);
DEFFN(CExitArboretum);
DEFFN(CExitBridge);
DEFFN(CExitStateRoom);
DEFFN(CMovePlayerInParrotRoom);
DEFFN(CMovePlayerTo);
DEFFN(CMovePlayerToFrom);
DEFFN(CMultiMove);
DEFFN(CPanFromPel);
DEFFN(CRestaurantPanHandler);
DEFFN(CRestrictedMove);
DEFFN(CTripDownCanal);

DEFFN(CBarbot);
DEFFN(CBellBot);
DEFFN(CCallBot);
DEFFN(CDeskbot);
DEFFN(CDoorbot);
DEFFN(CLiftBot);
DEFFN(CMaitreD);
DEFFN(CMobile);
DEFFN(CParrot);
DEFFN(CStarlings);
DEFFN(CSummonBots);
DEFFN(CSuccUBus);
DEFFN(CTitania);

DEFFN(CAutoMusicPlayer);

void CSaveableObject::initClassList() {
	_classList = new Common::HashMap<Common::String, CreateFunction>();
	ADDFN(CArm);
	ADDFN(CBrain);
	ADDFN(CBridgePiece);
	ADDFN(CCarryParrot);
	ADDFN(CChicken);
	ADDFN(CCrushedTV);
	ADDFN(CFeathers);
	ADDFN(CFruit);
	ADDFN(CGlass);
	ADDFN(CHammer);
	ADDFN(CHeadPiece);
	ADDFN(CHose);
	ADDFN(CKey);
	ADDFN(CLiftbotHead);
	ADDFN(CLongStick);
	ADDFN(CMagazine);
	ADDFN(CNapkin);
	ADDFN(CNote);
	ADDFN(CParcel);
	ADDFN(CPhonographCylinder);
	ADDFN(CPhotograph);
	ADDFN(CPlugIn);
	ADDFN(CSweets);

	ADDFN(CBackground);
	ADDFN(CClickResponder);
	ADDFN(CDropTarget);
	ADDFN(CFileItem);
	ADDFN(CFileListItem);
	ADDFN(CLinkItem);
	ADDFN(CMessageTarget);
	ADDFN(CMovieClip);
	ADDFN(CMovieClipList);
	ADDFN(CMultiDropTarget);
	ADDFN(CNodeItem);
	ADDFN(CProjectItem);
	ADDFN(CTreeItem);
	ADDFN(CTurnOnObject);
	ADDFN(CTurnOnPlaySound);
	ADDFN(CViewItem);

	ADDFN(CAnnounce);
	ADDFN(CCDROM);
	ADDFN(CCDROMComputer);
	ADDFN(CCDROMTray);
	ADDFN(CComputerScreen);
	ADDFN(CCredits);
	ADDFN(CCreditsButton);
	ADDFN(CDeadArea);
	ADDFN(CDeskClickResponder);
	ADDFN(CDoorbotHomeHandler);
	ADDFN(CDropTarget);
	ADDFN(CHammerDispensorButton);
	ADDFN(CNullPortHole);
	ADDFN(CPETPosition);
	ADDFN(CPortHole);
	ADDFN(CRoomItem);
	ADDFN(CServiceElevatorDoor);
	ADDFN(CSGTStateRoom);
	ADDFN(CSGTUpperDoorsSound);
	ADDFN(CStartAction);
	ADDFN(CSUBGlass);
	ADDFN(CSweetBowl);
	ADDFN(CTelevision);
	ADDFN(CParrotLobbyController);
	ADDFN(CParrotLobbyLinkUpdater);
	ADDFN(CParrotLobbyObject);
	ADDFN(CParrotLobbyViewObject);
	ADDFN(CParrotLoser);
	ADDFN(CParrotNutBowlActor);
	ADDFN(CParrotNutEater);
	ADDFN(CParrotPerchHolder);
	ADDFN(CParrotSuccUBus);
	ADDFN(CParrotTrigger);

	ADDFN(CActButton);
	ADDFN(CChangesSeasonButton);
	ADDFN(CChevLeftOff);
	ADDFN(CChevLeftOn);
	ADDFN(CChevRightOff);
	ADDFN(CChevRightOn);
	ADDFN(CChevSendRecSwitch);
	ADDFN(CChevSwitch);
	ADDFN(CElevatorButton);
	ADDFN(CGetFromSucc);
	ADDFN(CHelmetOnOff);
	ADDFN(CHomePhoto);
	ADDFN(CIconNavAction);
	ADDFN(CIconNavDown);
	ADDFN(CIconNavLeft);
	ADDFN(CIconNavRight);
	ADDFN(CIconNavUp);
	ADDFN(CKeybrdButt);
	ADDFN(CMoveObjectButton);
	ADDFN(CPetModeOff);
	ADDFN(CPetModeOn);
	ADDFN(CPetModePanel);
	ADDFN(CSendToSucc);
	ADDFN(CSliderButton);
	ADDFN(CSmallChevLeftOff);
	ADDFN(CSmallChevLeftOn);
	ADDFN(CSmallChevRightOff);
	ADDFN(CSmallChevRightOn);
	ADDFN(CStatusChangeButton);
	ADDFN(CSTButton);

	ADDFN(CActMsg);
	ADDFN(CActivationmsg);
	ADDFN(CAddHeadPieceMsg);
	ADDFN(CAnimateMaitreDMsg);
	ADDFN(CArboretumGateMsg);
	ADDFN(CArmPickedUpFromTableMsg);
	ADDFN(CAutoSoundEvent);
	ADDFN(CBodyInBilgeRoomMsg);
	ADDFN(CBowlStateChange);
	ADDFN(CCarryObjectArrivedMsg);
	ADDFN(CChangeSeasonMsg);
	ADDFN(CCheckAllPossibleCodes);
	ADDFN(CCheckChevCode);
	ADDFN(CChildDragEndMsg);
	ADDFN(CChildDragMoveMsg);
	ADDFN(CChildDragStartMsg);
	ADDFN(CClearChevPanelBits);
	ADDFN(CCorrectMusicPlayedMsg);
	ADDFN(CCreateMusicPlayerMsg);
	ADDFN(CCylinderHolderReadyMsg);
	ADDFN(CDeactivationMsg);
	ADDFN(CDeliverCCarryMsg);
	ADDFN(CDisableMaitreDProdReceptor);
	ADDFN(CDismissBotMsg);
	ADDFN(CDoffNavHelmet);
	ADDFN(CDonNavHelmet);
	ADDFN(CDoorAutoSoundEvent);
	ADDFN(CDoorbotNeededInElevatorMsg);
	ADDFN(CDoorbotNeededInHomeMsg);
	ADDFN(CDropobjectMsg);
	ADDFN(CDropZoneGotObjectMsg);
	ADDFN(CDropZoneLostObjectMsg);
	ADDFN(CEditControlMsg);
	ADDFN(CEjectCylinderMsg);
	ADDFN(CErasePhonographCylinderMsg);
	ADDFN(CFreshenCookieMsg);
	ADDFN(CGetChevClassBits);
	ADDFN(CGetChevClassNum);
	ADDFN(CGetChevCodeFromRoomNameMsg);
	ADDFN(CGetChevFloorBits);
	ADDFN(CGetChevFloorNum);
	ADDFN(CGetChevLiftBits);
	ADDFN(CGetChevLiftNum);
	ADDFN(CGetChevRoomBits);
	ADDFN(CGetChevRoomNum);
	ADDFN(CHoseConnectedMsg);
	ADDFN(CInitializeAnimMsg);
	ADDFN(CIsEarBowlPuzzleDone);
	ADDFN(CIsHookedOnMsg);
	ADDFN(CIsParrotPresentMsg);
	ADDFN(CKeyCharMsg);
	ADDFN(CLemonFallsFromTreeMsg);
	ADDFN(CLightsMsg);
	ADDFN(CLockPhonographMsg);
	ADDFN(CMaitreDDefeatedMsg);
	ADDFN(CMaitreDHappyMsg);
	ADDFN(CMissiveOMatActionMsg);
	ADDFN(CMouseMsg);
	ADDFN(CMouseMoveMsg);
	ADDFN(CMouseButtonMsg);
	ADDFN(CMouseButtonDownMsg);
	ADDFN(CMouseButtonUpMsg);
	ADDFN(CMouseButtonDoubleClickMsg);
	ADDFN(CMouseDragMsg);
	ADDFN(CMouseDragStartMsg);
	ADDFN(CMouseDragMoveMsg);
	ADDFN(CMouseDragEndMsg);
	ADDFN(CMoveToStartPosMsg);
	ADDFN(CMovieEndMsg);
	ADDFN(CMovieFrameMsg);
	ADDFN(CMusicHasStartedMsg);
	ADDFN(CMusicHasStoppedMsg);
	ADDFN(CMusicSettingChangedMsg);
	ADDFN(CNPCPlayAnimationMsg);
	ADDFN(CNPCPlayIdleAnimationMsg);
	ADDFN(CNPCPlayTalkingAnimationMsg);
	ADDFN(CNPCQueueIdleAnimMsg);
	ADDFN(CNutPuzzleMsg);
	ADDFN(COnSummonBotMsg);
	ADDFN(COpeningCreditsMsg);
	ADDFN(CPETDeliverMsg);
	ADDFN(CPETGainedObjectMsg);
	ADDFN(CPETHelmetOnOffMsg);
	ADDFN(CPETKeyboardOnOffMsg);
	ADDFN(CPETLostObjectMsg);
	ADDFN(CPETObjectSelectedMsg);
	ADDFN(CPETObjectStateMsg);
	ADDFN(CPETPhotoOnOffMsg);
	ADDFN(CPETPlaySoundMsg);
	ADDFN(CPETReceiveMsg);
	ADDFN(CPETSetStarDestinationMsg);
	ADDFN(CPETStarFieldLockMsg);
	ADDFN(CPETStereoFieldOnOffMsg);
	ADDFN(CPETTargetMsg);
	ADDFN(CPanningAwayFromParrotMsg);
	ADDFN(CParrotSpeakMsg);
	ADDFN(CParrotTriesChickenMsg);
	ADDFN(CPassOnDragStartMsg);
	ADDFN(CPhonographPlayMsg);
	ADDFN(CPhonographReadyToPlayMsg);
	ADDFN(CPhonographRecordMsg);
	ADDFN(CPhonographStopMsg);
	ADDFN(CPlayRangeMsg);
	ADDFN(CPlayerTriesRestaurantTableMsg);
	ADDFN(CPreSaveMsg);
	ADDFN(CProdMaitreDMsg);
	ADDFN(CPumpingMsg);
	ADDFN(CPutBotBackInHisBoxMsg);
	ADDFN(CPutParrotBackMsg);
	ADDFN(CPuzzleSolvedMsg);
	ADDFN(CQueryCylinderHolderMsg);
	ADDFN(CQueryCylinderMsg);
	ADDFN(CQueryCylinderNameMsg);
	ADDFN(CQueryCylinderTypeMsg);
	ADDFN(CQueryMusicControlSettingMsg);
	ADDFN(CQueryPhonographState);
	ADDFN(CRecordOntoCylinderMsg);
	ADDFN(CRemoveFromGameMsg);
	ADDFN(CReplaceBowlAndNutsMsg);
	ADDFN(CRestaurantMusicChanged);
	ADDFN(CSendCCarryMsg);
	ADDFN(CSenseWorkingMsg);
	ADDFN(CServiceElevatorFloorChangeMsg);
	ADDFN(CServiceElevatorFloorRequestMsg);
	ADDFN(CServiceElevatorMsg);
	ADDFN(CSetChevButtonImageMsg);
	ADDFN(CSetChevClassBits);
	ADDFN(CSetChevFloorBits);
	ADDFN(CSetChevLiftBits);
	ADDFN(CSetChevPanelBitMsg);
	ADDFN(CSetChevPanelButtonsMsg);
	ADDFN(CSetChevRoomBits);
	ADDFN(CSetMusicControlsMsg);
	ADDFN(CSetVarMsg);
	ADDFN(CSetVolumeMsg);
	ADDFN(CShipSettingMsg);
	ADDFN(CShowTextMsg);
	ADDFN(CSignalObject);
	ADDFN(CSpeechFallsFromTreeMsg);
	ADDFN(CStartMusicMsg);
	ADDFN(CStatusChangeMsg);
	ADDFN(CStopMusicMsg);
	ADDFN(CSubAcceptCCarryMsg);
	ADDFN(CSubDeliverCCarryMsg);
	ADDFN(CSubSendCCarryMsg);
	ADDFN(CSUBTransition);
	ADDFN(CSubTurnOffMsg);
	ADDFN(CSubTurnOnMsg);
	ADDFN(CSummonBotMsg);
	ADDFN(CSummonBotQuerryMsg);
	ADDFN(CTakeHeadPieceMsg);
	ADDFN(CTextInputMsg);
	ADDFN(CTimeDilationMsg);
	ADDFN(CTimeMsg);
	ADDFN(CTitleSequenceEndedMsg);
	ADDFN(CTransitMsg);
	ADDFN(CTransportMsg);
	ADDFN(CTriggerAutoMusicPlayerMsg);
	ADDFN(CTriggerNPCEvent);
	ADDFN(CTrueTalkGetAnimSetMsg);
	ADDFN(CTrueTalkGetAssetDetailsMsg);
	ADDFN(CTrueTalkGetStateValueMsg);
	ADDFN(CTrueTalkNotifySpeechEndedMsg);
	ADDFN(CTrueTalkNotifySpeechStartedMsg);
	ADDFN(CTrueTalkQueueUpAnimSetMsg);
	ADDFN(CTrueTalkSelfQueueAnimSetMsg);
	ADDFN(CTrueTalkTriggerActionMsg);
	ADDFN(CTurnOff);
	ADDFN(CTurnOn);
	ADDFN(CUse);
	ADDFN(CUseWithCharMsg);
	ADDFN(CUseWithOtherMsg);
	ADDFN(CVirtualKeyCharMsg);
	ADDFN(CVisibleMsg);

	ADDFN(CEnterBombRoom);
	ADDFN(CExitArboretum);
	ADDFN(CExitBridge);
	ADDFN(CExitStateRoom);
	ADDFN(CMovePlayerInParrotRoom);
	ADDFN(CMovePlayerTo);
	ADDFN(CMovePlayerToFrom);
	ADDFN(CMultiMove);
	ADDFN(CPanFromPel);
	ADDFN(CRestaurantPanHandler);
	ADDFN(CRestrictedMove);
	ADDFN(CTripDownCanal);

	ADDFN(CBarbot);
	ADDFN(CBellBot);
	ADDFN(CCallBot);
	ADDFN(CDeskbot);
	ADDFN(CDoorbot);
	ADDFN(CMaitreD);
	ADDFN(CLiftBot);
	ADDFN(CMobile);
	ADDFN(CParrot);
	ADDFN(CStarlings);
	ADDFN(CSuccUBus);
	ADDFN(CSummonBots);
	ADDFN(CTitania);

	ADDFN(CAutoMusicPlayer);
}

void CSaveableObject::freeClassList() {
	delete _classList;
}

CSaveableObject *CSaveableObject::createInstance(const Common::String &name) {
	return (*_classList)[name]();
}

void CSaveableObject::save(SimpleFile *file, int indent) const {
	file->writeNumberLine(0, indent);
}

void CSaveableObject::load(SimpleFile *file) {
	file->readNumber();
}

void CSaveableObject::saveHeader(SimpleFile *file, int indent) const {
	file->writeClassStart(getClassName(), indent);
}

void CSaveableObject::saveFooter(SimpleFile *file, int indent) const {
	file->writeClassEnd(indent);
}

} // End of namespace Titanic
