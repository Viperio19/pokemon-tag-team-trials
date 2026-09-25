VolcanionCave_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VolcanionCave_2F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, VolcanionCave_2F_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VolcanionCave_2F_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, VolcanionCave_2F_OnLoad
	.byte 0

VolcanionCave_2F_OnLoad::
	call_if_eq VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_1, 100, VolcanionCave_2F_EventScript_RemoveRockBarrier1
	call_if_eq VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_2, 100, VolcanionCave_2F_EventScript_RemoveRockBarrier2
	call_if_eq VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_3, 100, VolcanionCave_2F_EventScript_RemoveRockBarrier3
	call_if_eq VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_4, 100, VolcanionCave_2F_EventScript_RemoveRockBarrier4
	call_if_eq VAR_TEMP_F, 0, VolcanionCave_2F_EventScript_SetMetatilesRedButtonPressed
	call_if_eq VAR_TEMP_F, 1, VolcanionCave_2F_EventScript_SetMetatilesBlueButtonPressed
	end

VolcanionCave_2F_EventScript_RemoveRockBarrier1::
	setmetatile 26, 64, METATILE_Cave_Floor, FALSE
	setmetatile 27, 64, METATILE_Cave_Floor, FALSE
	setmetatile 28, 64, METATILE_Cave_Floor, FALSE
	setmetatile 8, 50, METATILE_Cave_Floor, FALSE
	return

VolcanionCave_2F_EventScript_RemoveRockBarrier2::
	setmetatile 18, 40, METATILE_Cave_Floor, FALSE
	setmetatile 18, 41, METATILE_Cave_Floor, FALSE
	setmetatile 18, 42, METATILE_Cave_Floor, FALSE
	return

VolcanionCave_2F_EventScript_RemoveRockBarrier3::
	setmetatile 20, 8, METATILE_Cave_FloorSmooth_Top, FALSE
	setmetatile 20, 9, METATILE_Cave_FloorSmooth, FALSE
	return

VolcanionCave_2F_EventScript_RemoveRockBarrier4::
	setmetatile 23, 4, METATILE_Cave_Floor, FALSE
	setmetatile 23, 5, METATILE_Cave_Floor, FALSE
	setmetatile 23, 6, METATILE_Cave_Floor, FALSE
	return

VolcanionCave_2F_OnTransition:
	callnative UpdateStrengthBoulderPositions
	call_if_set FLAG_SHOWED_GOLDEEN_TO_GOLDEEN_GRUNT, VolcanionCave_2F_EventScript_MoveGoldeenGrunt
	call_if_ne VAR_VOLCANION_CAVE_2F_CORSOLA_X, 0, VolcanionCave_2F_EventScript_UpdateCorsolaPos
	end

VolcanionCave_2F_EventScript_MoveGoldeenGrunt::
	setobjectxyperm LOCALID_2F_GOLDEEN_GRUNT, 20, 14
	return

VolcanionCave_2F_OnWarp:
	map_script_2 VAR_TEMP_1, 0, VolcanionCave_2F_EventScript_InitObjects
	.2byte 0

VolcanionCave_2F_EventScript_InitObjects::
	callnative TrySpawnPlayer2
	setvar VAR_TEMP_1, 1
	call_if_ne VAR_OLD_ROD_STATE, 2, VolcanionCave_2F_EventScript_RemoveOldRod
	call_if_eq VAR_OLD_ROD_STATE, 2, VolcanionCave_2F_EventScript_SetOldRodPosition
	end

VolcanionCave_2F_EventScript_RemoveOldRod::
	removeobject LOCALID_2F_OLD_ROD
	return

VolcanionCave_2F_EventScript_SetOldRodPosition::
	setobjectxyperm LOCALID_2F_OLD_ROD, VAR_OLD_ROD_X, VAR_OLD_ROD_Y
	addobject LOCALID_2F_OLD_ROD
	callnative SetOldRodBob
	return

VolcanionCave_2F_OnFrame:
	map_script_2 VAR_ACTION_ON_FRAME, 1, Player2_EventScript_Save
	map_script_2 VAR_ACTION_ON_FRAME, 2, Player2_EventScript_FastConnectForMultiplayerBattle
	map_script_2 VAR_VOLCANION_CAVE_2F_STATE, 0, VolcanionCave_2F_EventScript_EnterCave
	map_script_2 VAR_OLD_ROD_STATE, 10, VolcanionCave_2F_EventScript_DropOldRod
	.2byte 0

#define LOCALID_PLAYER_AQUA  VAR_0x800A
#define LOCALID_PLAYER_MAGMA VAR_0x800B

VolcanionCave_2F_EventScript_EnterCave::
	lock
	setvar VAR_VOLCANION_CAVE_2F_STATE, 1
	callnative IsPlayerOne
	goto_if_eq VAR_RESULT, TRUE, VolcanionCave_2F_EventScript_PlayersEnter
	goto_if_eq VAR_RESULT, FALSE, VolcanionCave_2F_EventScript_PlayersEnter2
VolcanionCave_2F_EventScript_Intro::
	delay 30
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_WalkInPlaceRight
	message VolcanionCave_2F_Text_IntroName
	waitmovement 0
	waitmessage
	closemessage
	delay 30
	forcesave
	closemessage
	callnative UpdatePlayer2Pos
	release
	end

VolcanionCave_2F_Text_IntroName::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}So, you got a name?\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Excuse me?\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}A name? You know, like the first thing\n"
	.string "you get when you're 0 years old??\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Yes, I know what those are.\p"
	.string "I just don't see the need for you\n"
	.string "to know my name.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Well, unless you want me to confuse\n"
	.string "every MAGMA grunt in VOLCANO CAVERN\l"
	.string "when I call for you, I think you should\l"
	.string "probably let me know your name.\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}…{PLAYER_MAGMA}.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}That name sucks.\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}piss off.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Anyway, I'm {PLAYER_AQUA}!\p"
	.string "I would say it's nice to meet you\n"
	.string "but I hate you so I won't.\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Good for you, let's get this over with.\p$"

VolcanionCave_2F_EventScript_PlayersEnter::
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_PlayerAquaEnterCave
	waitmovement 0
	callnative SpawnPlayer2For2FIntro
	applymovement LOCALID_PLAYER_2, VolcanionCave_2F_Movement_Player2Enter
	waitmovement 0
	applymovement LOCALID_PLAYER_2, VolcanionCave_2F_Movement_PlayerMagmaEnterCave
	waitmovement 0
	setvar LOCALID_PLAYER_AQUA, LOCALID_PLAYER
	setvar LOCALID_PLAYER_MAGMA, LOCALID_PLAYER_2
	goto VolcanionCave_2F_EventScript_Intro
	end

VolcanionCave_2F_EventScript_PlayersEnter2::
	applymovement LOCALID_PLAYER, VolcanionCave_2F_Movement_PlayerMagmaEnterCave
	waitmovement 0
	callnative SpawnPlayer2For2FIntro
	applymovement LOCALID_PLAYER_2, VolcanionCave_2F_Movement_Player2Enter
	waitmovement 0
	applymovement LOCALID_PLAYER_2, VolcanionCave_2F_Movement_PlayerAquaEnterCave
	waitmovement 0
	setvar LOCALID_PLAYER_AQUA, LOCALID_PLAYER_2
	setvar LOCALID_PLAYER_MAGMA, LOCALID_PLAYER
	goto VolcanionCave_2F_EventScript_Intro
	end

VolcanionCave_2F_Movement_Player2Enter::
	set_visible
	walk_up
	step_end

VolcanionCave_2F_Movement_PlayerMagmaEnterCave::
	walk_right
	walk_up
	step_end

VolcanionCave_2F_Movement_PlayerAquaEnterCave::
	walk_left
	walk_up
	step_end

VolcanionCave_2F_EventScript_DropOldRod::
	lock
	clearflag FLAG_DISABLE_OLD_ROD_BOB
    clearflag FLAG_HIDE_VOLCANION_CAVE_2F_OLD_ROD
    setflag FLAG_DROPPED_VOLCANION_CAVE_2F_OLD_ROD
	addobject LOCALID_2F_OLD_ROD
	callnative SetOldRodBob
	removeitem ITEM_OLD_ROD
	setvar VAR_OLD_ROD_STATE, 2
	getplayerxy VAR_0x8000, VAR_0x8001
	goto_if_ne VAR_0x8000, 29, VolcanionCave_2F_EventScript_MessageDroppedRod
	goto_if_eq VAR_0x8001, 24, VolcanionCave_2F_EventScript_OldRodCurrentsY24
	goto_if_eq VAR_0x8001, 25, VolcanionCave_2F_EventScript_OldRodCurrentsY25
	goto_if_eq VAR_0x8001, 26, VolcanionCave_2F_EventScript_OldRodCurrentsY26
	goto_if_eq VAR_0x8001, 27, VolcanionCave_2F_EventScript_OldRodCurrentsY27
VolcanionCave_2F_EventScript_MessageDroppedRod::
	msgbox VolcanionCave_2F_Text_DroppedRod
	closemessage
	release
	end

VolcanionCave_2F_EventScript_OldRodCurrentsY24::
	special SpawnCameraObject
	applymovement LOCALID_2F_OLD_ROD, VolcanionCave_2F_Movement_OldRodFloatY24
	applymovement LOCALID_CAMERA, VolcanionCave_2F_Movement_OldRodFloatY24
	waitmovement 0
	callnative StopOldRodBob
	playse SE_LEDGE
	applymovement LOCALID_2F_OLD_ROD, VolcanionCave_2F_Movement_OldRodJumpY24
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceDown
	waitmovement 0
	setvar VAR_OLD_ROD_X, 29
	setvar VAR_OLD_ROD_Y, 25
	setobjectxyperm LOCALID_2F_OLD_ROD, VAR_OLD_ROD_X, VAR_OLD_ROD_Y
	delay 20
	applymovement LOCALID_CAMERA, Common_Movement_WalkUp
	waitmovement 0
	special RemoveCameraObject
	msgbox VolcanionCave_2F_Text_DroppedRodFloated
	closemessage
	release
	end

VolcanionCave_2F_Movement_OldRodFloatY24::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

VolcanionCave_2F_Movement_OldRodJumpY24::
	jump_right
	step_end

VolcanionCave_2F_Movement_CameraMoveBackY24::
	walk_up
	step_end

VolcanionCave_2F_EventScript_OldRodCurrentsY25::
	msgbox VolcanionCave_2F_Text_DroppedRodFloated
	closemessage
	release
	end

VolcanionCave_2F_EventScript_OldRodCurrentsY26::
	special SpawnCameraObject
	applymovement LOCALID_2F_OLD_ROD, VolcanionCave_2F_Movement_OldRodFloatY26
	applymovement LOCALID_CAMERA, VolcanionCave_2F_Movement_OldRodFloatY26
	waitmovement 0
	callnative StopOldRodBob
	playse SE_LEDGE
	applymovement LOCALID_2F_OLD_ROD, VolcanionCave_2F_Movement_OldRodJumpY26
	waitmovement 0
	setvar VAR_OLD_ROD_X, 17
	setvar VAR_OLD_ROD_Y, 31
	setobjectxyperm LOCALID_2F_OLD_ROD, VAR_OLD_ROD_X, VAR_OLD_ROD_Y
	delay 20
	applymovement LOCALID_CAMERA, VolcanionCave_2F_Movement_CameraMoveBackY26
	waitmovement 0
	special RemoveCameraObject
	msgbox VolcanionCave_2F_Text_DroppedRodFloatedSuccessfully
	closemessage
	release
	end

VolcanionCave_2F_Movement_OldRodFloatY26::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

VolcanionCave_2F_Movement_OldRodJumpY26::
	jump_left
	step_end

VolcanionCave_2F_Movement_CameraMoveBackY26::
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

VolcanionCave_2F_EventScript_OldRodCurrentsY27::
	special SpawnCameraObject
	applymovement LOCALID_2F_OLD_ROD, VolcanionCave_2F_Movement_OldRodFloatY27
	applymovement LOCALID_CAMERA, VolcanionCave_2F_Movement_OldRodFloatY27
	waitmovement 0
	setvar VAR_OLD_ROD_X, 27
	setvar VAR_OLD_ROD_Y, 30
	setobjectxyperm LOCALID_2F_OLD_ROD, VAR_OLD_ROD_X, VAR_OLD_ROD_Y
	delay 20
	applymovement LOCALID_CAMERA, VolcanionCave_2F_Movement_CameraMoveBackY27
	waitmovement 0
	special RemoveCameraObject
	msgbox VolcanionCave_2F_Text_DroppedRodFloated
	closemessage
	release
	end

VolcanionCave_2F_Movement_OldRodFloatY27::
	walk_left
	walk_down
	walk_fast_down
	walk_fast_down
	step_end

VolcanionCave_2F_Movement_CameraMoveBackY27::
	walk_up
	walk_up
	walk_up
	walk_right
	step_end

VolcanionCave_2F_Text_DroppedRod::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Aw yeah, FISHING SUCCESSFUL!!!\p"
	.string "…wait no actually it didn't do anything.\p"
	.string "It must be the water's fault!\n"
	.string "No self-respecting fish POKéMON\l"
	.string "would live in water this weak!!!\p"
	.string "Surely the problem is NOT my own\n"
	.string "lack of fishing experience!$"

VolcanionCave_2F_Text_DroppedRodFloated::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Ohhhh, you tricky fishy!!!\n"
	.string "Next time I'll catch you for SURE!!$"

VolcanionCave_2F_Text_DroppedRodFloatedSuccessfully::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}HEY!! THAT WAS MY FISHING ROD!!!\p"
	.string "Guess I'm not getting that back\n"
	.string "anytime soon…$"

VolcanionCave_2F_EventScript_AquaGruntF::
	lock
	applymovement LOCALID_2F_AQUA_GRUNT_F, Common_Movement_FacePlayer
	waitmovement 0
	callnative IsPlayerOne
	goto_if_eq VAR_RESULT, FALSE, VolcanionCave_2F_EventScript_AquaGruntFMagmaPlayer
	goto_if_set FLAG_RECEIVED_SIGNED_REPEL, VolcanionCave_2F_EventScript_AquaGruntFSprayingRepels
	msgbox VolcanionCave_2F_Text_AquaGruntFAquaPlayer, MSGBOX_DEFAULT
	closemessage
	delay 10
	giveitem ITEM_SIGNED_REPEL
	setflag FLAG_RECEIVED_SIGNED_REPEL
VolcanionCave_2F_EventScript_AquaGruntFSprayingRepels::
	msgbox VolcanionCave_2F_Text_AquaGruntFSprayingRepels, MSGBOX_NPC
	end

VolcanionCave_2F_EventScript_AquaGruntFMagmaPlayer::
	msgbox VolcanionCave_2F_Text_NoRepels, MSGBOX_NPC
	setvar VAR_STINKY_STEP_COUNT, 100
	end

VolcanionCave_2F_Text_AquaGruntFAquaPlayer::
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}Hey partner!\p"
	.string "You'll never guess how I got here!\p"
	.string "AGENT DIGGS helped me down from\n"
	.string "the ledge in the last room!\p"
	.string "I'm so happy!! I can't believe I got\n"
	.string "to meet the legend himself!!\p"
	.string "He even signed one of my repels!!\l"
	.string "This is the best day EVER!!!!\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}You do realize that you got stuck on\n"
	.string "another ledge mid-fangirling, right?\p"
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}Oh, that was completely intentional.\p"
	.string "I'm hoping AGENT DIGGS sees me up\n"
	.string "here and helps me down again!\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}What you're doing is wasting the time\n"
	.string "of TEAM AQUA'S best agent, TWICE.\p"
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}Oopsie…?\p"
	.string "Oh well, I'm sure SHELLY won't ignore\n"
	.string "a GRUNT in need when she comes by!\p"
	.string "In that case, can you hold onto the\n"
	.string "repel that AGENT DIGGS signed for me?\p"
	.string "I wouldn't want SHELLY to take it\n"
	.string "from me when she finds out I've been \l"
	.string "intentionally getting myself stuck\l"
	.string "so I can talk to AGENT DIGGS.\n"

VolcanionCave_2F_Text_AquaGruntFSprayingRepels::
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}Thanks, partner!\n"
	.string "Guard that repel with your life!$"

VolcanionCave_2F_Text_NoRepels::
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}EWWWWW!!!{PAUSE 20} MAGMA!!!!!\p"
	.string "{SPEAKER NAME_NONE COLOR_NORMAL}(The GRUNT sprays you with a repel.)\p"
	.string "(You now smell like eggs and repel.)$"

VolcanionCave_2F_EventScript_Diglett::
	lock
	applymovement LOCALID_2F_DIGLETT, Common_Movement_FacePlayer
	waitmovement
	callnative IsPlayerOne
	goto_if_eq VAR_RESULT, FALSE, VolcanionCave_2F_EventScript_DiglettMagma
	goto VolcanionCave_2F_EventScript_DiglettAqua
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	release
	end

VolcanionCave_2F_EventScript_DiglettMagma::
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	msgbox VolcanionCave_2F_Text_DiglettCry
	waitmoncry
	closemessage
	delay 20
	msgbox VolcanionCave_2F_Text_DiglettSecretAgent
	closemessage
	release
	end

VolcanionCave_2F_EventScript_DiglettAqua::
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	message VolcanionCave_2F_Text_AgentDiggs1 
	waitmoncry
	waitmessage
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL 
	message VolcanionCave_2F_Text_AgentDiggs2
	waitmoncry
	waitmessage
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	message VolcanionCave_2F_Text_AgentDiggs3
	waitmoncry
	waitmessage
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	message VolcanionCave_2F_Text_AgentDiggs4 
	waitmoncry
	waitmessage
	closemessage
	release
	end

VolcanionCave_2F_Text_DiglettCry::
	.string "{SPEAKER NAME_DIGLETT COLOR_AQUA}Pipipi wowow!$"

VolcanionCave_2F_Text_AgentDiggs1::
	.string "{SPEAKER NAME_AGENT_DIGGS COLOR_AQUA}Pipipi wowow!\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}AGENT DIGGS!!! How's it going, my guy??\p$"

VolcanionCave_2F_Text_DiglettSecretAgent::
	.string "{SPEAKER NAME_WORD COLOR_JESSIE}This dialogue is not intended to\n"
	.string "be accessible in normal gameplay.\p"
	.string "Hi cheater!!!!$"
	
VolcanionCave_2F_Text_AgentDiggs2::
	.string "{SPEAKER NAME_AGENT_DIGGS COLOR_AQUA}pi wow.\p"
	.string "{SPEAKER NAME_PLAYER COLOR_AQUA}Good to hear!!\p"
	.string "Hey, thanks for the assist back there!\p"
	.string "I never would have been able to nab\n"
	.string "that HEAT BADGE off of TEAM MAGMA\l"
	.string "if it wasn't for your quick thinking!\p"
	.string "Now I'm one step closer to completing\n"
	.string "my GYM CHALLENGE!\p$"

VolcanionCave_2F_Text_AgentDiggs3::
	.string "{SPEAKER NAME_AGENT_DIGGS COLOR_AQUA}Pi pi wow. Wow wow.\p"
	.string "{SPEAKER NAME_PLAYER COLOR_AQUA}What do you mean they aren't valid\n"
	.string "if they're stolen from the LEAGUE?\p"
	.string "They're BADGES, not gift cards to the\n"
	.string "POKéMON LEAGUE CHAMPION store!!\p"
	.string "I'll be able to get in just fine!\p"
	.string "…once I get my hands the other five\n"
	.string "badges that I need, of course.\p$"

VolcanionCave_2F_Text_AgentDiggs4::
	.string "{SPEAKER NAME_AGENT_DIGGS COLOR_AQUA}Pipi, wow.\p$"

VolcanionCave_2F_EventScript_AquaGruntOldRod::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_VOLCANION_CAVE_2F_TOXAPEX, VolcanionCave_2F_EventScript_AquaGruntReceivedOldRod
	goto_if_set FLAG_TALKED_TO_OLD_ROD_GRUNT, VolcanionCave_2F_EventScript_AquaGruntAskBattleShort
	setflag FLAG_TALKED_TO_OLD_ROD_GRUNT
	msgbox VolcanionCave_2F_Text_AquaGruntWantToBattle, MSGBOX_YESNO
VolcanionCave_2F_EventScript_AquaGruntTryBattle::
	goto_if_ne VAR_RESULT, YES, VolcanionCave_2F_EventScript_AquaGruntRejected
	trainerbattle_single TRAINER_GRUNT_VC_2F_TOXAPEX, VolcanionCave_2F_Text_AquaGruntIntro, VolcanionCave_2F_Text_AquaGruntDefeat, VolcanionCave_2F_EventScript_AquaGruntGiveOldRod
	msgbox VolcanionCave_2F_Text_AquaGruntPostBattle, MSGBOX_NPC
	end

VolcanionCave_2F_EventScript_AquaGruntAskBattleShort::
	msgbox VolcanionCave_2F_Text_AquaGruntWantToBattleShort, MSGBOX_YESNO
	goto VolcanionCave_2F_EventScript_AquaGruntTryBattle

VolcanionCave_2F_EventScript_AquaGruntRejected::
	msgbox VolcanionCave_2F_Text_AquaGruntRejected, MSGBOX_NPC
	end

VolcanionCave_2F_EventScript_AquaGruntGiveOldRod::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, VolcanionCave_2F_EventScript_AquaGruntVictory
	setflag FLAG_DEFEATED_VOLCANION_CAVE_2F_TOXAPEX
	message VolcanionCave_2F_Text_AquaGruntPostBattle1
	waitmessage
	closemessage
	delay 10
	giveitem ITEM_OLD_ROD
	closemessage
	delay 10
	message VolcanionCave_2F_Text_AquaGruntPostBattle2
	waitmessage
	closemessage
	release
	end

VolcanionCave_2F_EventScript_AquaGruntReceivedOldRod::
	msgbox VolcanionCave_2F_Text_AquaGruntPostBattle, MSGBOX_NPC
	end

VolcanionCave_2F_EventScript_AquaGruntVictory::
	msgbox VolcanionCave_2F_Text_AquaGruntVictory, MSGBOX_NPC
	end

VolcanionCave_2F_Text_AquaGruntWantToBattle:
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}Hey, chum!\p"
	.string "Fancy some fishing but find yourself\n"
	.string "completely and utterly rod-less?\p"
	.string "Well you're in luck!\p"
	.string "My fishing buddy TOXAPEX has been\n"
	.string "itching for a battle and a snack!\p"
	.string "If you can provide both of those\n"
	.string "things for her, I'll let you have my\l"
	.string "limited-edition-one-of-a-kind-\l"
	.string "MEOWSTIX-branded OLD ROD!!\p"
	.string "Things it is: the best and coolest\n"
	.string "fishing rod in town.\p"
	.string "Things it is not: a normal twig with a\n"
	.string "MEOWSTIC sticker falling off of it.\p"
	.string "So, do we have a deal?$"

VolcanionCave_2F_Text_AquaGruntWantToBattleShort:
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}So, do we have a deal?$"

VolcanionCave_2F_Text_AquaGruntRejected:
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}Your loss, chum!$"

VolcanionCave_2F_Text_AquaGruntIntro:
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}Now that's what I'm talking about!$"

VolcanionCave_2F_Text_AquaGruntDefeat:
	.string "Woo-wee! You know a good deal when\n"
	.string "you see it, chum!$"

VolcanionCave_2F_Text_AquaGruntPostBattle1:
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}Here you go, one super-awesome-\n"
	.string "coolest-thing-ever-mega-\l"
	.string "extraordinary-limited-edition-\l"
	.string "MEOWSTIX-branded OLD ROD!!\p"
	.string "There is no warranty or return policy.\p"
	.string "Enjoy!!!\p$"

VolcanionCave_2F_Text_AquaGruntPostBattle2:
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Yeah, that's cool and all but how do\n"
	.string "I use the thing??\p"
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}You don't know how??\p"
	.string "How can you call yourself a TEAM AQUA\n"
	.string "GRUNT and not know how to fish?\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}My parents were… {PAUSE 40}landlubbers.\p"
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}I'm sorry to hear that, chum.\p"
	.string "Anyway, just throw it in the water,\n"
	.string "you'll get the hang of it no problem!\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Thanks, big chum!!\p"
	.string "I now understand everything there\n"
	.string "is to know about fishing!$"

VolcanionCave_2F_Text_AquaGruntPostBattle:
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}Just throw it in the water,\n"
	.string "you'll get the hang of it no problem!$"

VolcanionCave_2F_Text_AquaGruntVictory:
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}Nice try chum, but you aren't\n"
	.string "getting my OLD ROD that easily!$"

VolcanionCave_2F_EventScript_FloorSwitch1::
	lock
	goto_if_eq VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_1, 100, VolcanionCave_2F_EventScript_FloorSwitchAlreadyPressed
	setmetatile 26, 64, METATILE_Cave_Floor, FALSE
	setmetatile 27, 64, METATILE_Cave_Floor, FALSE
	setmetatile 28, 64, METATILE_Cave_Floor, FALSE
	setmetatile 8, 50, METATILE_Cave_Floor, FALSE
	playse SE_ICE_BREAK
	special DrawWholeMapView
	waitse
	setvar VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_1, 100
	releaseall
	end

VolcanionCave_2F_EventScript_FloorSwitch2::
	lock
	goto_if_eq VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_2, 100, VolcanionCave_2F_EventScript_FloorSwitchAlreadyPressed
	setmetatile 18, 40, METATILE_Cave_Floor, FALSE
	setmetatile 18, 41, METATILE_Cave_Floor, FALSE
	setmetatile 18, 42, METATILE_Cave_Floor, FALSE
	playse SE_ICE_BREAK
	special DrawWholeMapView
	waitse
	setvar VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_2, 100
	releaseall
	end

VolcanionCave_2F_EventScript_FloorSwitch3::
	lock
	goto_if_eq VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_3, 100, VolcanionCave_2F_EventScript_FloorSwitchAlreadyPressed
	setmetatile 20, 8, METATILE_Cave_FloorSmooth_Top, FALSE
	setmetatile 20, 9, METATILE_Cave_FloorSmooth, FALSE
	playse SE_ICE_BREAK
	special DrawWholeMapView
	waitse
	setvar VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_3, 100
	releaseall
	end

VolcanionCave_2F_EventScript_FloorSwitch4::
	lock
	goto_if_eq VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_4, 100, VolcanionCave_2F_EventScript_FloorSwitchAlreadyPressed
	setmetatile 23, 4, METATILE_Cave_Floor, FALSE
	setmetatile 23, 5, METATILE_Cave_Floor, FALSE
	setmetatile 23, 6, METATILE_Cave_Floor, FALSE
	playse SE_ICE_BREAK
	special DrawWholeMapView
	waitse
	setvar VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_4, 100
	releaseall
	end

VolcanionCave_2F_EventScript_FloorSwitchAlreadyPressed::
	release
	end

VolcanionCave_2F_EventScript_Exeggutor::
	playmoncry SPECIES_EXEGGUTOR_ALOLA, CRY_MODE_NORMAL
	msgbox VolcanionCave_2F_Text_Exeggutor, MSGBOX_DEFAULT
	waitmoncry
	setwildbattle SPECIES_EXEGGUTOR_ALOLA, 25, TRUE, ITEM_SITRUS_BERRY
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, VolcanionCave_2F_EventScript_DefeatedExeggutor
	release
	end

VolcanionCave_2F_EventScript_DefeatedExeggutor::
	playmoncry SPECIES_EXEGGUTOR_ALOLA, CRY_MODE_NORMAL
	msgbox VolcanionCave_2F_Text_Exeggutor, MSGBOX_DEFAULT
	waitmoncry
	setflag FLAG_DEFEATED_VOLCANION_CAVE_2F_EXEGGUTOR
	removeobject LOCALID_2F_EXEGGUTOR_1
	removeobject LOCALID_2F_EXEGGUTOR_2
	release
	end

VolcanionCave_2F_Text_Exeggutor::
	.string "{SPEAKER NAME_EXEGGUTOR COLOR_NORMAL}Beuhbwah behdebuh bwah!$"

VolcanionCave_2F_EventScript_Toxapex::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TOXAPEX, CRY_MODE_NORMAL
	call_if_unset FLAG_DEFEATED_VOLCANION_CAVE_2F_TOXAPEX, VolcanionCave_2F_EventScript_ToxapexHappy
	call_if_set FLAG_DEFEATED_VOLCANION_CAVE_2F_TOXAPEX, VolcanionCave_2F_EventScript_ToxapexSad
	waitmoncry
	release
	end

VolcanionCave_2F_EventScript_ToxapexHappy:
	msgbox VolcanionCave_2F_Text_ToxapexHappy, MSGBOX_DEFAULT
	return

VolcanionCave_2F_EventScript_ToxapexSad:
	msgbox VolcanionCave_2F_Text_ToxapexSad, MSGBOX_DEFAULT
	return

VolcanionCave_2F_Text_ToxapexHappy::
	.string "{SPEAKER NAME_TOXAPEX COLOR_AQUA}(phonetically impossible cry)$"

VolcanionCave_2F_Text_ToxapexSad::
	.string "{SPEAKER NAME_TOXAPEX COLOR_AQUA}(phonetically impossible cry but sad)$"

VolcanionCave_2F_EventScript_OldRod::
	lock
	removeobject VAR_LAST_TALKED
	giveitem ITEM_OLD_ROD
	clearflag FLAG_DROPPED_VOLCANION_CAVE_2F_OLD_ROD
	setflag FLAG_HIDE_VOLCANION_CAVE_2F_OLD_ROD
	setvar VAR_OLD_ROD_STATE, 0
	release
	end

VolcanionCave_2F_EventScript_MagmaMemberFGoldeen::
	lock
	goto_if_set FLAG_SHOWED_GOLDEEN_TO_GOLDEEN_GRUNT, VolcanionCave_2F_EventScript_GoldeenGruntSleeping
	faceplayer
	goto_if_set FLAG_TALKED_TO_GOLDEEN_GRUNT, VolcanionCave_2F_EventScript_PleaseShowGoldeen
	setflag FLAG_TALKED_TO_GOLDEEN_GRUNT
	msgbox VolcanionCave_2F_Text_IDroppedGoldeen, MSGBOX_DEFAULT
	goto VolcanionCave_2F_EventScript_ChoosePartyMonGoldeen
	end

VolcanionCave_2F_EventScript_PleaseShowGoldeen::
	msgbox VolcanionCave_2F_Text_PleaseShowGoldeen, MSGBOX_DEFAULT
VolcanionCave_2F_EventScript_ChoosePartyMonGoldeen::
	setvar VAR_0x8009, SPECIES_CHI_YU
	special ChooseGoldeen
	specialvar VAR_RESULT, GetTradeSpecies
	goto_if_eq VAR_RESULT, SPECIES_NONE, VolcanionCave_2F_EventScript_PleaseKeepLooking
	goto_if_ne VAR_RESULT, VAR_0x8009, VolcanionCave_2F_EventScript_ThatsNotGoldeen
	message VolcanionCave_2F_Text_ThatsIt
	waitmessage
	applymovement LOCALID_2F_GOLDEEN_GRUNT, Common_Movement_FaceRight
	message VolcanionCave_2F_Text_NicePillow
	waitmessage
	waitmovement 0
	applymovement LOCALID_2F_GOLDEEN_GRUNT, VolcanionCave_2F_Movement_GoldeenGruntWalkInPlace
	msgbox VolcanionCave_2F_Text_BedtimeTrain, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_SHOWED_GOLDEEN_TO_GOLDEEN_GRUNT
	setobjectxyperm LOCALID_2F_GOLDEEN_GRUNT, 20, 14
	release
	end

VolcanionCave_2F_EventScript_ThatsNotGoldeen::
	msgbox VolcanionCave_2F_Text_ThatsNotGoldeen, MSGBOX_NPC
	end

VolcanionCave_2F_EventScript_PleaseKeepLooking::
	closemessage
	delay 5
	msgbox VolcanionCave_2F_Text_PleaseKeepLooking, MSGBOX_NPC
	end

VolcanionCave_2F_EventScript_GoldeenGruntSleeping::
	msgbox VolcanionCave_2F_Text_GoldeenGruntSleeping, MSGBOX_DEFAULT
	closemessage
	release
	end

VolcanionCave_2F_Text_IDroppedGoldeen::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}YOU THERE!!! YOU WITH THE RED HOODIE!!!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Speaking.\p"
	.string "Assuming you were talking to me and\n"
	.string "not the other billion MAGMA GRUNTS\l"
	.string "in here, of course.\p"
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}You'll NEVER believe what I just s-saw!!\p"
	.string "A g-g-g-g-g-g-g-g-g-g-g-g-g-g-g-g-\n"
	.string "g-g-g-g-g-g-G-G-G-G-GOLDEEN!!!!!!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Yes, they ARE sometimes found in caves.\p"
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}I know that!!\p"
	.string "Watch, I'll list them all off to prove\n"
	.string "that I'm not a weenie cave-goer:\p"
	.string "{AUTO_SCROLL 1}Seafoam Islands, Cerulean Cave,{PAUSE 20}\n"
	.string "Dark Cave, Union Cave, Slowpoke Well,{PAUSE 20}\l"
	.string "Mt. Mortar, Tohjo Falls, Mt. Silver Cave,{PAUSE 20}\l"
	.string "Petalburg City, Meteor Falls,{PAUSE 20}\l"
	.string "Scorched Slab, Victory Road,{PAUSE 20}\l"
	.string "{AUTO_SCROLL 0}Waterfall Pond, and Murky Cave.\p"
	.string "You know w-what WASN'T in that list?\n"
	.string "VOLCANO CAVERN.\p"
	.string "That's not all t-though…\p"
	.string "If this was a case of invasive species\n"
	.string "I would be upset at the environmental\l"
	.string "impact b-but not scared for m-my life!\p"
	.string "The GOLDEEN here is… different.\p"
	.string "It was all c-creepy and red, just like\n"
	.string "those ALPHA POKéMON that I read about\l"
	.string "in my History and French textbooks.\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}An ALPHA GOLDEEN…\p"
	.string "Sounds dangerous, but not TOO bad.\p"
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}EVEN MORE!!!\p"
	.string "I saw it in the lava over there!\n"
	.string "Lava is S-SCARY!!\p"
	.string "Quick, I need you to f-find a way to get\n"
	.string "that GOLDEEN out of the lava and into\l"
	.string "your POKé BALL s-so I can have some\l"
	.string "peace of mind for once in t-this place.$"

VolcanionCave_2F_Text_PleaseShowGoldeen::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}Have you found the G-GOLDEEN yet?$"

VolcanionCave_2F_Text_ThatsNotGoldeen::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}N-no, this can't be it…\p"
	.string "This isn't s-scary enough to be\n"
	.string "the GOLDEEN that I saw…$"

VolcanionCave_2F_Text_PleaseKeepLooking::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}Can you f-find the GOLDEEN soon?\n"
	.string "I'm s-seriously freaking out here.$"

VolcanionCave_2F_Text_ThatsIt::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}EEP! THAT'S IT! THE S-S-SCARY GOLDEEN!\p"
	.string "NASTY!!!\n"
	.string "Put that fish away NOW!!!!!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Alright, alright.\n"
	.string "Whatever you say, Captain CLODSIRE.\p"
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}Phew… thanks for getting that freak of\n"
	.string "nature out of my line of sight!\p"
	.string "I deserve a nice break after\n"
	.string "that horrifying situation.\p$"

VolcanionCave_2F_Text_NicePillow::
	.string "And would you look at that, a nice\n"
	.string "soft rock pillow with my name on it!\p$"

VolcanionCave_2F_Text_BedtimeTrain::
	.string "WAHOOO!!! {PAUSE 40}ALL ABOARD THE BEDTIME TRAIN\n"
	.string "DESTINATION ZZZZZZZZzzzzzzzzzzzzz…$"

VolcanionCave_2F_Text_GoldeenGruntSleeping::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}ZZZZZZZZzzzzzzzzzzzzz…\n"
	.string "Choo-choo!$"

VolcanionCave_2F_Movement_GoldeenGruntWalkInPlace::
	walk_in_place_faster_right
	walk_in_place_faster_right
	walk_in_place_faster_right
	delay_16
	delay_16
	jump_right
	delay_16
	face_down
	step_end

VolcanionCave_2F_EventScript_BlueButton::
	lockall
	setvar VAR_TEMP_F, 1
	playse SE_PIN
	call VolcanionCave_2F_EventScript_SetMetatilesBlueButtonPressed
	special DrawWholeMapView
	releaseall
	end

VolcanionCave_2F_EventScript_RedButton::
	lockall
	setvar VAR_TEMP_F, 0
	playse SE_PIN
	call VolcanionCave_2F_EventScript_SetMetatilesRedButtonPressed
	special DrawWholeMapView
	releaseall
	end

VolcanionCave_2F_EventScript_SetMetatilesBlueButtonPressed::
	setmetatile 7, 47, METATILE_Cave_CoolButton_Pressed, FALSE
	setmetatile 17, 11, METATILE_Cave_CoolButton_Pressed, FALSE
	setmetatile 11, 46, METATILE_Cave_CoolButton_Red, FALSE
	setmetatile 9, 46, METATILE_Cave_CoolGem_Blue_FloorSmooth_Empty, FALSE
	setmetatile 33, 58, METATILE_Cave_CoolGem_Blue_Mud_Empty, FALSE
	setmetatile 35, 50, METATILE_Cave_CoolGem_Blue_Mud_Empty, FALSE
	setmetatile 21, 11, METATILE_Cave_CoolGem_Blue_FloorSmooth_Empty, FALSE
	setmetatile 8, 48, METATILE_Cave_CoolGem_Red_FloorSmooth_Full, TRUE
	setmetatile 11, 47, METATILE_Cave_CoolGem_Red_FloorSmooth_Full, TRUE
	setmetatile 17, 9, METATILE_Cave_CoolGem_Red_FloorSmooth_Full, TRUE
	return

VolcanionCave_2F_EventScript_SetMetatilesRedButtonPressed::
	setmetatile 7, 47, METATILE_Cave_CoolButton_Blue, FALSE
	setmetatile 17, 11, METATILE_Cave_CoolButton_Blue, FALSE
	setmetatile 11, 46, METATILE_Cave_CoolButton_Pressed, FALSE
	setmetatile 9, 46, METATILE_Cave_CoolGem_Blue_FloorSmooth_Full, TRUE
	setmetatile 33, 58, METATILE_Cave_CoolGem_Blue_Mud_Full, TRUE
	setmetatile 35, 50, METATILE_Cave_CoolGem_Blue_Mud_Full, TRUE
	setmetatile 21, 11, METATILE_Cave_CoolGem_Blue_FloorSmooth_Full, TRUE
	setmetatile 8, 48, METATILE_Cave_CoolGem_Red_FloorSmooth_Empty, FALSE
	setmetatile 11, 47, METATILE_Cave_CoolGem_Red_FloorSmooth_Empty, FALSE
	setmetatile 17, 9, METATILE_Cave_CoolGem_Red_FloorSmooth_Empty, FALSE
	return

VolcanionCave_2F_EventScript_Hole1A::
	jumphole VolcanionCave_2F_Movement_Hole1AToB, VolcanionCave_2F_Movement_ExitHoleSouth

VolcanionCave_2F_EventScript_Hole1B::
	jumphole VolcanionCave_2F_Movement_Hole1BToA, VolcanionCave_2F_Movement_ExitHoleWest

VolcanionCave_2F_Movement_Hole1AToB::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_2F_Movement_Hole1BToA::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

VolcanionCave_2F_EventScript_Hole2A::
	jumphole VolcanionCave_2F_Movement_Hole2AToB, VolcanionCave_2F_Movement_ExitHoleNorth

VolcanionCave_2F_EventScript_Hole2B::
	jumphole VolcanionCave_2F_Movement_Hole2BToA, VolcanionCave_2F_Movement_ExitHoleWest

VolcanionCave_2F_Movement_Hole2AToB::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_2F_Movement_Hole2BToA::
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

VolcanionCave_2F_EventScript_Hole3A::
	jumphole VolcanionCave_2F_Movement_Hole3AToB, VolcanionCave_2F_Movement_ExitHoleNorth

VolcanionCave_2F_EventScript_Hole3B::
	jumphole VolcanionCave_2F_Movement_Hole3BToA, VolcanionCave_2F_Movement_ExitHoleSouth

VolcanionCave_2F_Movement_Hole3AToB::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_2F_Movement_Hole3BToA::
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

VolcanionCave_2F_EventScript_Hole4A::
	jumphole VolcanionCave_2F_Movement_Hole4AToB, VolcanionCave_2F_Movement_ExitHoleSouth

VolcanionCave_2F_EventScript_Hole4B::
	jumphole VolcanionCave_2F_Movement_Hole4BToA, VolcanionCave_2F_Movement_ExitHoleNorth

VolcanionCave_2F_Movement_Hole4AToB::
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_2F_Movement_Hole4BToA::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

VolcanionCave_2F_EventScript_Hole5A::
	jumphole VolcanionCave_2F_Movement_Hole5AToB, VolcanionCave_2F_Movement_ExitHoleSouth

VolcanionCave_2F_EventScript_Hole5B::
	jumphole VolcanionCave_2F_Movement_Hole5BToA, VolcanionCave_2F_Movement_ExitHoleSouth

VolcanionCave_2F_Movement_Hole5AToB::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_2F_Movement_Hole5BToA::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

VolcanionCave_2F_Movement_ExitHoleSouth::
	face_down
	set_visible
	jump_down
	step_end

VolcanionCave_2F_Movement_ExitHoleNorth::
	face_up
	set_visible
	jump_up
	step_end

VolcanionCave_2F_Movement_ExitHoleEast::
	face_right
	set_visible
	jump_right
	step_end

VolcanionCave_2F_Movement_ExitHoleWest::
	face_left
	set_visible
	jump_left
	step_end

VolcanionCave_2F_EventScript_RockSmash::
	lockall
	checkfieldmove FIELD_MOVE_ROCK_SMASH, TRUE
	goto_if_eq VAR_RESULT, PARTY_SIZE, VolcanionCave_2F_EventScript_CantSmashRock
	setfieldeffectargument 0, VAR_RESULT
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	buffermovename STR_VAR_2, MOVE_ROCK_SMASH
	msgbox Text_WantToSmash, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VolcanionCave_2F_EventScript_CancelSmash
	msgbox Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
VolcanionCave_2F_EventScript_RockSmashCommon:
	dofieldeffect FLDEFF_USE_ROCK_SMASH
	waitstate
VolcanionCave_2F_EventScript_SmashRock:: @ fallthrough
	applymovement VAR_LAST_TALKED, Movement_SmashRock
	waitmovement 0
	removeobject VAR_LAST_TALKED
	delay 10
	setflag FLAG_ANIMATE_MUD_UNDER_BOULDER
	playse SE_FALL
	applymovement LOCALID_2F_BOULDER_ON_MUD, VolcanionCave_2F_Movement_BoulderSlideDown
	waitmovement 0
	setobjectxyperm LOCALID_2F_BOULDER_ON_MUD, 26, 13
	playse SE_M_STRENGTH
	clearflag FLAG_ANIMATE_MUD_UNDER_BOULDER
	callnative UpdateBoulderOnMudPosition
	delay 10
	msgbox VolcanionCave_2F_Text_BoulderSlidDown, MSGBOX_DEFAULT
	releaseall
	end

VolcanionCave_2F_EventScript_CantSmashRock::
	msgbox Text_CantSmash, MSGBOX_DEFAULT
	releaseall
	end

VolcanionCave_2F_EventScript_CancelSmash::
	closemessage
	releaseall
	end

VolcanionCave_2F_Text_BoulderSlidDown::
	.string "The boulder slid down!$"

VolcanionCave_2F_Movement_BoulderSlideDown::
	walk_down
	walk_down
	walk_fast_down
	jump_down
	step_end

VolcanionCave_2F_EventScript_UpdateCorsolaPos::
	setobjectxyperm LOCALID_2F_CORSOLA, VAR_VOLCANION_CAVE_2F_CORSOLA_X, VAR_VOLCANION_CAVE_2F_CORSOLA_Y
	return

VolcanionCave_2F_EventScript_CorsolaFacePlayer::
	lock
	playse SE_ICE_CRACK
	applymovement LOCALID_2F_CORSOLA, VolcanionCave_2F_Movement_CorsolaNoticePlayer
	waitmovement 0
	release
	end

VolcanionCave_2F_EventScript_Corsola::
	lock
	getobjectfacingdirection LOCALID_PLAYER, VAR_0x800A
	getobjectfacingdirection LOCALID_2F_CORSOLA, VAR_0x800B
	goto_if_ne VAR_0x800A, VAR_0x800B, VolcanionCave_2F_EventScript_CorsolaFlee
	applymovement LOCALID_2F_CORSOLA, Common_Movement_ExclamationMark
	faceplayer
	waitmovement 0
	playmoncry SPECIES_CORSOLA, CRY_MODE_ENCOUNTER
	msgbox VolcanionCave_2F_Text_Corsola, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	specialvar VAR_RESULT, IsTagTeamTrialsLinkActive
	goto_if_eq VAR_RESULT, TRUE, VolcanionCave_2F_EventScript_BattleCorsola
	delay 10
	forcesave
	closemessage
VolcanionCave_2F_EventScript_BattleCorsola::
	setwildbattle SPECIES_CORSOLA, 20
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, VolcanionCave_2F_EventScript_CaughtCorsola
	release
	end

VolcanionCave_2F_EventScript_CaughtCorsola::
	removeobject LOCALID_2F_CORSOLA
	setflag FLAG_HIDE_VOLCANION_CAVE_2F_CORSOLA
	setvar VAR_VOLCANION_CAVE_2F_CORSOLA_STATE, 1
	release
	end

VolcanionCave_2F_EventScript_CorsolaFlee::
	applymovement LOCALID_2F_CORSOLA, VolcanionCave_2F_Movement_CorsolaNoticePlayer
	playmoncry SPECIES_CORSOLA, CRY_MODE_ENCOUNTER
	waitmovement 0
	getobjectcurrentxy LOCALID_2F_CORSOLA, CURRENT_POSITION, VAR_0x8008, VAR_0x8009
	goto_if_eq VAR_0x8009, 17, VolcanionCave_2F_EventScript_CorsolaFleeNorthCases
	switch VAR_0x8008
	case 24, VolcanionCave_2F_EventScript_CorsolaSWFlee
	case 28, VolcanionCave_2F_EventScript_CorsolaSMFlee
	case 31, VolcanionCave_2F_EventScript_CorsolaSEFlee
	end

VolcanionCave_2F_EventScript_CorsolaFleeNorthCases::
	switch VAR_0x8008
	case 24, VolcanionCave_2F_EventScript_CorsolaNWFlee
	case 28, VolcanionCave_2F_EventScript_CorsolaNMFlee
	case 31, VolcanionCave_2F_EventScript_CorsolaNEFlee
	end

VolcanionCave_2F_EventScript_CorsolaSWFlee::
	goto_if_eq VAR_0x800A, DIR_WEST, VolcanionCave_2F_EventScript_CorsolaFleeUp
	goto VolcanionCave_2F_EventScript_CorsolaFleeRight4 @ DIR_SOUTH & DIR_EAST
	end

VolcanionCave_2F_EventScript_CorsolaSMFlee::
	goto_if_eq VAR_0x800A, DIR_EAST, VolcanionCave_2F_EventScript_CorsolaFleeRight3
	goto VolcanionCave_2F_EventScript_CorsolaFleeLeft4 @ DIR_SOUTH & DIR_WEST
	end

VolcanionCave_2F_EventScript_CorsolaSEFlee::
	goto_if_eq VAR_0x800A, DIR_EAST, VolcanionCave_2F_EventScript_CorsolaFleeUp
	goto VolcanionCave_2F_EventScript_CorsolaFleeLeft3 @ DIR_SOUTH & DIR_WEST
	end

VolcanionCave_2F_EventScript_CorsolaNWFlee::
	goto_if_eq VAR_0x800A, DIR_WEST, VolcanionCave_2F_EventScript_CorsolaFleeDown
	goto VolcanionCave_2F_EventScript_CorsolaFleeRight4 @ DIR_NORTH
	end

VolcanionCave_2F_EventScript_CorsolaNMFlee::
	goto_if_eq VAR_0x800A, DIR_EAST, VolcanionCave_2F_EventScript_CorsolaFleeRight3
	goto VolcanionCave_2F_EventScript_CorsolaFleeLeft4 @ DIR_NORTH & DIR_WEST
	end

VolcanionCave_2F_EventScript_CorsolaNEFlee::
	goto_if_eq VAR_0x800A, DIR_EAST, VolcanionCave_2F_EventScript_CorsolaFleeDown
	goto VolcanionCave_2F_EventScript_CorsolaFleeLeft3 @ DIR_NORTH
	end

VolcanionCave_2F_EventScript_CorsolaFleeUp::
	applymovement LOCALID_2F_CORSOLA, VolcanionCave_2F_Movement_CorsolaFleeUp
	goto VolcanionCave_2F_EventScript_CorsolaFleeEnd
	end

VolcanionCave_2F_EventScript_CorsolaFleeDown::
	applymovement LOCALID_2F_CORSOLA, VolcanionCave_2F_Movement_CorsolaFleeDown
	goto VolcanionCave_2F_EventScript_CorsolaFleeEnd
	end

VolcanionCave_2F_EventScript_CorsolaFleeLeft3::
	applymovement LOCALID_2F_CORSOLA, VolcanionCave_2F_Movement_CorsolaFleeLeft3
	goto VolcanionCave_2F_EventScript_CorsolaFleeEnd
	end

VolcanionCave_2F_EventScript_CorsolaFleeLeft4::
	applymovement LOCALID_2F_CORSOLA, VolcanionCave_2F_Movement_CorsolaFleeLeft4
	goto VolcanionCave_2F_EventScript_CorsolaFleeEnd
	end

VolcanionCave_2F_EventScript_CorsolaFleeRight3::
	applymovement LOCALID_2F_CORSOLA, VolcanionCave_2F_Movement_CorsolaFleeRight3
	goto VolcanionCave_2F_EventScript_CorsolaFleeEnd
	end

VolcanionCave_2F_EventScript_CorsolaFleeRight4::
	applymovement LOCALID_2F_CORSOLA, VolcanionCave_2F_Movement_CorsolaFleeRight4
	goto VolcanionCave_2F_EventScript_CorsolaFleeEnd
	end

VolcanionCave_2F_EventScript_CorsolaFleeEnd::
	waitmovement 0
	getobjectcurrentxy LOCALID_2F_CORSOLA, CURRENT_POSITION, VAR_0x8008, VAR_0x8009
	setobjectxyperm LOCALID_2F_CORSOLA, VAR_0x8008, VAR_0x8009
	copyvar VAR_VOLCANION_CAVE_2F_CORSOLA_X, VAR_0x8008
	copyvar VAR_VOLCANION_CAVE_2F_CORSOLA_Y, VAR_0x8009
	release
	end

VolcanionCave_2F_Movement_CorsolaNoticePlayer::
	emote_exclamation_mark
	face_player
	step_end

VolcanionCave_2F_Movement_CorsolaFleeUp::
	walk_fast_up
	walk_fast_up
	walk_fast_up
	face_down
	step_end

VolcanionCave_2F_Movement_CorsolaFleeDown::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	face_up
	step_end

VolcanionCave_2F_Movement_CorsolaFleeLeft3::
	walk_fast_left
	walk_fast_left
	walk_fast_left
	face_right
	step_end

VolcanionCave_2F_Movement_CorsolaFleeLeft4::
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	face_right
	step_end

VolcanionCave_2F_Movement_CorsolaFleeRight3::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	face_left
	step_end

VolcanionCave_2F_Movement_CorsolaFleeRight4::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	face_left
	step_end

VolcanionCave_2F_Text_Corsola::
	.string "{SPEAKER NAME_CORSOLA COLOR_NORMAL}Pi uwaa!$"
