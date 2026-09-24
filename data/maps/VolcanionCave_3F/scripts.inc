VolcanionCave_3F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VolcanionCave_3F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, VolcanionCave_3F_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VolcanionCave_3F_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, VolcanionCave_3F_OnLoad
	.byte 0

VolcanionCave_3F_OnTransition:
	goto_if_set FLAG_DOING_CREDITS, VolcanionCave_3F_EventScript_SetUpCredits
	callnative UpdateStrengthBoulderPositions
	call_if_ne VAR_VOLCANION_CAVE_3F_STATE, 0, VolcanionCave_3F_EventScript_SetWeatherFog
	end

VolcanionCave_3F_EventScript_SetWeatherFog::
	setweather WEATHER_FOG_HORIZONTAL
	return

VolcanionCave_3F_EventScript_SetUpCredits::
	addobject LOCALID_3F_WHISMUR
	setobjectxyperm LOCALID_3F_WHISMUR, 5, 38
	turnobject LOCALID_3F_WHISMUR, DIR_SOUTH
	addobject LOCALID_3F_PIKACHU
	setobjectxyperm LOCALID_3F_PIKACHU, 27, 5
	addobject LOCALID_3F_JESSIE
	setobjectxyperm LOCALID_3F_JESSIE, 26, 4
	addobject LOCALID_3F_JAMES
	setobjectxyperm LOCALID_3F_JAMES, 27, 4
	addobject LOCALID_3F_MEOWTH
	setobjectxyperm LOCALID_3F_MEOWTH, 28, 4
	addobject LOCALID_3F_VOLCANION
	end

VolcanionCave_3F_OnWarp:
	map_script_2 VAR_TEMP_1, 0, VolcanionCave_3F_EventScript_TrySpawnPlayer2
	.2byte 0

VolcanionCave_3F_EventScript_TrySpawnPlayer2::
	setvar VAR_TEMP_1, 1
	goto_if_set FLAG_DOING_CREDITS, VolcanionCave_3F_EventScript_DontSpawnPlayer2
	goto_if_eq VAR_VOLCANION_CAVE_3F_STATE, 0, VolcanionCave_3F_EventScript_SpawnHiddenPlayer2
	callnative TrySpawnPlayer2
	end

VolcanionCave_3F_EventScript_DontSpawnPlayer2::
	end

VolcanionCave_3F_EventScript_SpawnHiddenPlayer2::
	callnative SpawnPlayer2For3FIntro
	hideobjectat LOCALID_PLAYER_2, MAP_VOLCANION_CAVE_3F
	end

VolcanionCave_3F_OnFrame:
	map_script_2 VAR_ACTION_ON_FRAME, 1, Player2_EventScript_Save
	map_script_2 VAR_ACTION_ON_FRAME, 2, Player2_EventScript_ConnectForMultiplayerBattle
	map_script_2 VAR_VOLCANION_CAVE_3F_STATE, 0, VolcanionCave_3F_EventScript_EnterCave
	.2byte 0

#define LOCALID_PLAYER_AQUA  VAR_0x800A
#define LOCALID_PLAYER_MAGMA VAR_0x800B

VolcanionCave_3F_EventScript_EnterCave::
	lock
	special SpawnCameraObject
	callnative IsPlayerOne
	goto_if_eq VAR_RESULT, TRUE, VolcanionCave_3F_EventScript_PlayersEnter
	goto_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_PlayersEnter2
VolcanionCave_3F_EventScript_Intro::
	delay 10
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	message VolcanionCave_3F_Text_IntroCoolRoom
	waitmessage
	closemessage
	playse SE_PIN
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_ExclamationMark
	delay 50
	message VolcanionCave_3F_Text_IHearSomething
	waitmessage
	closemessage
	call VolcanionCave_3F_EventScript_VolcanionCry
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_WalkInPlaceUp
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_WalkInPlaceUp
	message VolcanionCave_3F_Text_IntroIsThat
	waitmovement 0
	waitmessage
	closemessage
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveUpToVolcanion
	applymovement LOCALID_PLAYER_AQUA, VolcanionCave_3F_Movement_PlayerApproachVolcanion
	applymovement LOCALID_PLAYER_MAGMA, VolcanionCave_3F_Movement_PlayerApproachVolcanion
	waitmovement 0
	delay 10
	call VolcanionCave_3F_EventScript_VolcanionCry
	closemessage
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveDown
	waitmovement 0
	message VolcanionCave_3F_Text_IntroTheLegendary
	waitmessage
	closemessage
	delay 30
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	message VolcanionCave_3F_Text_IntroBothEllipsis
	waitmessage
	closemessage
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, VolcanionCave_3F_EventScript_CameraFollowAquaTryToLeave
	call_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_CameraFollowMagmaTryToStopAqua
	playse SE_PIN
	applymovement LOCALID_PLAYER_AQUA, VolcanionCave_3F_Movement_AquaTryToLeave
	applymovement LOCALID_PLAYER_MAGMA, VolcanionCave_3F_Movement_MagmaTryToStopAqua
	waitmovement 0
	message VolcanionCave_3F_Text_IntroCatchIt
	waitmessage
	closemessage
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveBackToVolcanion
	applymovement LOCALID_PLAYER_AQUA, VolcanionCave_3F_Movement_AquaWalkToVolcanion
	applymovement LOCALID_PLAYER_MAGMA, VolcanionCave_3F_Movement_MagmaWalkToVolcanion
	waitmovement 0
	delay 16
	setflag FLAG_SYS_WEATHER_CTRL
	setweather WEATHER_FOG_HORIZONTAL
	doweather
	call VolcanionCave_3F_EventScript_VolcanionCry
	closemessage
	special WaitWeather
	setwildbattle SPECIES_VOLCANION, 40, TRUE
	multi_fixed_players_vs_wild PARTNER_PLAYER_2
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, VolcanionCave_3F_EventScript_DefeatedVolcanion
	message VolcanionCave_3F_Text_IntroAwNuts
	waitmessage
	closemessage
	playbgm MUS_VS_VOLCANION, FALSE
	setvar VAR_CURRENT_HP_BAR_COLOR, 1
	call VolcanionCave_3F_EventScript_SetHPBar
	call VolcanionCave_3F_EventScript_VolcanionCry
	message VolcanionCave_3F_Text_IntroVolcanionUsedEarthPower
	waitmessage
	setvar VAR_0x8004, 0  @ Vertical pan
	setvar VAR_0x8005, 5  @ Horizontal pan
	setvar VAR_0x8006, 15  @ Num shakes
	setvar VAR_0x8007, 3  @ Shake delay
	special ShakeScreen
	playse SE_PIN
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_ExclamationMark
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_ExclamationMark
	delay 50
	setvar VAR_0x8004, 0  @ Vertical pan
	setvar VAR_0x8005, 10  @ Horizontal pan
	setvar VAR_0x8006, 40  @ Num shakes
	setvar VAR_0x8007, 3  @ Shake delay
	special ShakeScreen
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_PlayerGetKnockedBack
	applymovement LOCALID_PLAYER_AQUA, VolcanionCave_3F_Movement_PlayerGetKnockedBack
	applymovement LOCALID_PLAYER_MAGMA, VolcanionCave_3F_Movement_PlayerGetKnockedBack
	closemessage
	waitmovement
	delay 20
	playse SE_M_ROCK_THROW
	call VolcanionCave_3F_EventScript_SetMetatilesRocksBroken
	special DrawWholeMapView
	setvar VAR_VOLCANION_CAVE_3F_STATE, 1
	fadedefaultbgm
	delay 100
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	message VolcanionCave_3F_Text_IntroBattleAgainOrLookAround
	waitmessage
	closemessage
	special RemoveCameraObject
	special SpawnCameraObject
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, VolcanionCave_3F_EventScript_CameraResetToAqua
	call_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_CameraResetToMagma
	waitmovement 0
	special RemoveCameraObject
	forcesave
	release
	end

VolcanionCave_3F_EventScript_PlayersEnter::
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveWithPlayersEntering
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerAquaEnterCave
	applymovement LOCALID_PLAYER_2, VolcanionCave_3F_Movement_Player2MagmaEnterCave
	waitmovement 0
	setvar LOCALID_PLAYER_AQUA, LOCALID_PLAYER
	setvar LOCALID_PLAYER_MAGMA, LOCALID_PLAYER_2
	goto VolcanionCave_3F_EventScript_Intro
	end

VolcanionCave_3F_EventScript_PlayersEnter2::
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveWithPlayersEntering
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerMagmaEnterCave
	applymovement LOCALID_PLAYER_2, VolcanionCave_3F_Movement_Player2AquaEnterCave
	waitmovement 0
	setvar LOCALID_PLAYER_AQUA, LOCALID_PLAYER_2
	setvar LOCALID_PLAYER_MAGMA, LOCALID_PLAYER
	goto VolcanionCave_3F_EventScript_Intro
	end

VolcanionCave_3F_EventScript_VolcanionCry::
	setvar VAR_0x8004, 0  @ Vertical pan
	setvar VAR_0x8005, 3  @ Horizontal pan
	setvar VAR_0x8006, 10  @ Num shakes
	setvar VAR_0x8007, 4  @ Shake delay
	applymovement LOCALID_3F_VOLCANION, Common_Movement_WalkInPlaceDown
	call_if_eq VAR_VOLCANION_CAVE_3F_STATE, 0, VolcanionCave_3F_EventScript_IntroUnknownCry
	call_if_ne VAR_VOLCANION_CAVE_3F_STATE, 0, VolcanionCave_3F_EventScript_IntroVolcanionCry
	playmoncry SPECIES_VOLCANION, CRY_MODE_NORMAL
	special ShakeScreen
	delay 30
	waitmoncry
	return

VolcanionCave_3F_EventScript_IntroUnknownCry::
	message VolcanionCave_3F_Text_IntroUnknownCry
	return

VolcanionCave_3F_EventScript_IntroVolcanionCry::
	message VolcanionCave_3F_Text_IntroVolcanionCry
	return

VolcanionCave_3F_EventScript_CameraFollowAquaTryToLeave::
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraFollowAquaTryToLeave
	return

VolcanionCave_3F_EventScript_CameraFollowMagmaTryToStopAqua::
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraFollowMagmaTryToStopAqua
	return

VolcanionCave_3F_EventScript_CameraResetToAqua::
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraResetToAqua
	return

VolcanionCave_3F_EventScript_CameraResetToMagma::
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraResetToMagma
	return

VolcanionCave_3F_Movement_PlayerAquaEnterCave::
	walk_up
	walk_up
	walk_left
	walk_up
	step_end

VolcanionCave_3F_Movement_PlayerMagmaEnterCave::
	walk_up
	walk_up
	walk_right
	walk_up
	step_end

VolcanionCave_3F_Movement_Player2AquaEnterCave::
	delay_16
	set_visible
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	step_end

VolcanionCave_3F_Movement_Player2MagmaEnterCave::
	delay_16
	set_visible
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	step_end

VolcanionCave_3F_Movement_CameraMoveWithPlayersEntering::
	walk_up
	walk_up
	walk_up
	step_end

VolcanionCave_3F_Movement_PlayerApproachVolcanion::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

VolcanionCave_3F_Movement_CameraMoveUpToVolcanion::
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

VolcanionCave_3F_Movement_AquaTryToLeave::
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

VolcanionCave_3F_Movement_MagmaTryToStopAqua::
	emote_exclamation_mark
	delay_8
	walk_in_place_fast_down
	walk_in_place_fast_down
	delay_8
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_left
	walk_faster_left
	walk_in_place_fast_up
	step_end

VolcanionCave_3F_Movement_CameraFollowAquaTryToLeave::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

VolcanionCave_3F_Movement_CameraFollowMagmaTryToStopAqua::
	delay_8
	walk_in_place_fast_down
	walk_in_place_fast_down
	delay_8
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	step_end

VolcanionCave_3F_Movement_CameraMoveDown::
	walk_down
	walk_down
	step_end

VolcanionCave_3F_Movement_AquaWalkToVolcanion::
	delay_16
	delay_16
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_in_place_up
	step_end

VolcanionCave_3F_Movement_MagmaWalkToVolcanion::
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_in_place_up
	step_end

VolcanionCave_3F_Movement_CameraMoveBackToVolcanion::
	delay_16
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

VolcanionCave_3F_Movement_PlayerGetKnockedBack::
	lock_facing_direction
	jump_2_down
	unlock_facing_direction
	step_end

VolcanionCave_3F_Movement_CameraResetToAqua::
	walk_left
	step_end

VolcanionCave_3F_Movement_CameraResetToMagma::
	walk_right
	step_end

VolcanionCave_3F_Text_IntroCoolRoom::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Phew, it sure is warm in here!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Tch… this humidity is ruining my hair.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}You wear a hoodie though???\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Yes. {PAUSE 40}Fantastic observation.\p"
	.string "You got me real good there.\n"
	.string "Ten points to TEAM AQUA.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}{FONT 5}yes!!! ten points!!!!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}{FONT_NORMAL}That was… {FONT 5}oh forget it.\p$"

VolcanionCave_3F_Text_IHearSomething::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}{FONT_NORMAL}Wait a moment, I think I can\n"
	.string "hear something moving.\p$"

VolcanionCave_3F_Text_IntroIsThat::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}OVER THERE!! IS THAT-\p$"

VolcanionCave_3F_Text_IntroTheLegendary::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}It certainly matches the reports.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}That's the LEGENDARY POKéMON\n"
	.string "I've been looking for!\p$"

VolcanionCave_3F_Text_IntroBothEllipsis::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Interesting.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Thats ALL you have to say about this??\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}It seems your ADMINS aren't quite\n"
	.string "as incompetent as I thought.\l"
	.string "They actually got one of the\l"
	.string "LEGENDARY POKéMON's types right.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}YOU TAKE THAT BACK!!\p"
	.string "NOT THE PART ABOUT THEM BEING RIGHT!!!\n"
	.string "THE INCOMPETENT PART!!!!!\p"
	.string "I'll have you know that SHELLY is on\n"
	.string "her way down here right now because\l"
	.string "she doesn't want us to get hurt\l"
	.string "while trying to catch this POKéMON.\p"
	.string "I bet your ADMINS don't even care\n"
	.string "enough about your well-being to\l"
	.string "help out in person, am I right?\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}INFURIATINGLY, yes.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Well, toodles! My job here is DONE!!\p"
	.string "Good luck catching a LEGENDARY\n"
	.string "with your regular POKé BALLS!!!\p$"

VolcanionCave_3F_Text_IntroCatchIt::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Hold on, you're just leaving\n"
	.string "me to die here?\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}I mean… not exactly??\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}{FONT 5}(Hook.)\p"
	.string "{FONT_NORMAL}Remember, catching this LEGENDARY\n"
	.string "is also TEAM MAGMA'S goal here.\p"
	.string "And look at me, a TEAM MAGMA GRUNT\n"
	.string "ordered to put their life on the line\l"
	.string "just to catch a single POKéMON.\p"
	.string "You know me, I'm not going\n"
	.string "down without a fight.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Yeah, but…\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}{FONT 5}(Line.)\p"
	.string "{FONT_NORMAL}According to my calculations, I have a\n"
	.string "3.557% chance to catch it per ball.\p"
	.string "In the time it takes you to find SHELLY,\n"
	.string "how many POKé BALLS will I have thrown?\p"
	.string "20? {PAUSE 40}50? {PAUSE 40}100?\p"
	.string "I have a surprisingly fast\n"
	.string "throwing arm, you know.\p"
	.string "Do you really want to bet the success\n"
	.string "of your mission on a chance that isn't\l"
	.string "even in your favour?\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Oh… {PAUSE 20}FINE!!!\p"
	.string "I'll catch this LEGENDARY and get\n"
	.string "out of here faster than the speed of\l"
	.string "SHELLY'S SHARPEDO multiplied by 5!!!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}…\p"
	.string "{AUTO_SCROLL 1}{FONT 5}(Sinker.){PAUSE 80}\p"
	.string "{AUTO_SCROLL 0}wait damn it that was a fishing reference\p"
	.string "{FONT_NORMAL}Alright then, it's a challenge.\n"
	.string "Whoever knocks it out gets to catch it.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Fine by me! Let's go!!!\p$"

VolcanionCave_3F_Text_IntroUnknownCry::
	.string "{SPEAKER NAME_QUESTION_MARKS COLOR_NORMAL}FWAHHRSHHHH!!!$"

VolcanionCave_3F_Text_IntroVolcanionCry::
	.string "{SPEAKER NAME_VOLCANION COLOR_NORMAL}FWAHHRSHHHH!!!$"

VolcanionCave_3F_Text_IntroAwNuts::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}YOWZA!! That is one strong POKéMON!\p"
	.string "That's it, I'm getting out of-\p$"

VolcanionCave_3F_Text_IntroVolcanionUsedEarthPower::
	.string "{AUTO_SCROLL 1}{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}What the-{PAUSE 20}\p"
	.string "{AUTO_SCROLL 0}{SPEAKER NAME_NONE COLOR_NORMAL}??? used EARTH POWER!$"

VolcanionCave_3F_Text_IntroBattleAgainOrLookAround::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Oof, that was a close one!\n"
	.string "You still alive, {PLAYER_MAGMA}?\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Regrettably, I am.\p"
	.string "On the bright side, its attack\n"
	.string "destroyed the rocks over there.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Perfect, let's see if there's anything\n"
	.string "in here we can use to teach that meanie\l"
	.string "VOLCANION not to mess with us!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}You named it already?\n"
	.string "And why did you call it VOLCANION??\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Well, we found it in VOLCANO CAVERN\n"
	.string "and ion know what its deal is!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Unbelievable…\p"
	.string "It's too bad that the first person who\n"
	.string "sees a POKéMON has full legal rights to\l"
	.string "decide the name of its species forever.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}IM GONNA BE FAMOUS!!!!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}If you can get out of here in\n"
	.string "one piece, maybe.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}What are we waiting here for then?\n"
	.string "Let's go!!!\p$"

VolcanionCave_3F_OnLoad::
	call_if_eq VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_1, 100, VolcanionCave_3F_EventScript_RemoveRockBarrier1
	call_if_ne VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_2, 100, VolcanionCave_3F_EventScript_SetRockBarrier2
	call_if_eq VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_3, 100, VolcanionCave_3F_EventScript_RemoveRockBarrier3
	call_if_eq VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_4, 100, VolcanionCave_3F_EventScript_RemoveRockBarrier4
	call_if_eq VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_5, 100, VolcanionCave_3F_EventScript_RemoveRockBarrier5
	call_if_eq VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_6, 100, VolcanionCave_3F_EventScript_RemoveRockBarrier6
	call_if_eq VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_7, 100, VolcanionCave_3F_EventScript_RemoveRockBarrier7
	call_if_eq VAR_TEMP_F, 0, VolcanionCave_3F_EventScript_SetMetatilesRedButtonPressed
	call_if_eq VAR_TEMP_F, 1, VolcanionCave_3F_EventScript_SetMetatilesBlueButtonPressed
	call_if_ge VAR_VOLCANION_CAVE_3F_STATE, 1, VolcanionCave_3F_EventScript_SetMetatilesRocksBroken
	call_if_eq VAR_GOLEM_ROCK_SLIDE_STATE, 0, VolcanionCave_3F_EventScript_SetMetatilesNoRockSlideBlockade
	call_if_ne VAR_GOLEM_ROCK_SLIDE_STATE, 0, VolcanionCave_3F_EventScript_SetMetatilesRockSlideBlockade
	call_if_set FLAG_SPAWN_VOLCANION_CAVE_3F_TEAM_ROCKET, VolcanionCave_3F_EventScript_SpawnTeamRocket
	call VolcanionCave_3F_EventScript_SetHPBar
	end

VolcanionCave_3F_EventScript_RemoveRockBarrier1::
	setmetatile 21, 8, METATILE_Cave_Floor, FALSE
	return

VolcanionCave_3F_EventScript_RemoveRockBarrier2::
	setmetatile 22, 9, METATILE_Cave_Floor, FALSE
	return

VolcanionCave_3F_EventScript_SetRockBarrier2::
	setmetatile 22, 9, METATILE_Cave_RockBarrier_Single, TRUE
	return

VolcanionCave_3F_EventScript_RemoveRockBarrier3::
	setmetatile 23, 18, METATILE_Cave_Floor, FALSE
	return

VolcanionCave_3F_EventScript_RemoveRockBarrier4::
	setmetatile 30, 32, METATILE_Cave_Floor, FALSE
	return

VolcanionCave_3F_EventScript_RemoveRockBarrier5::
	setmetatile 26, 37, METATILE_Cave_Floor, FALSE
	return

VolcanionCave_3F_EventScript_RemoveRockBarrier6::
	setmetatile 4, 32, METATILE_Cave_Floor, FALSE
	return

VolcanionCave_3F_EventScript_RemoveRockBarrier7::
	setmetatile 5, 22, METATILE_Cave_FloorSmooth, FALSE
	setmetatile 8, 21, METATILE_Cave_Floor, FALSE
	setmetatile 9, 21, METATILE_Cave_Floor, FALSE
	return

VolcanionCave_3F_EventScript_BlueButton::
	setvar VAR_TEMP_F, 1
	playse SE_PIN
	goto_if_eq VAR_GOLEM_ROCK_SLIDE_STATE, 1, VolcanionCave_3F_EventScript_BlueButtonGolem
	lockall
	call VolcanionCave_3F_EventScript_SetMetatilesBlueButtonPressed
	special DrawWholeMapView
	releaseall
	end

VolcanionCave_3F_EventScript_BlueButtonGolem::
	call VolcanionCave_3F_EventScript_SetMetatilesBlueButtonPressed
	special DrawWholeMapView
	goto_if_eq VAR_GOLEM_ROCK_SLIDE_TIMER, 200, VolcanionCave_3F_EventScript_WaitStartRockSlide
	goto VolcanionCave_3F_EventScript_RockSlide
	return

VolcanionCave_3F_EventScript_RedButton::
	setvar VAR_TEMP_F, 0
	playse SE_PIN
	goto_if_eq VAR_GOLEM_ROCK_SLIDE_STATE, 1, VolcanionCave_3F_EventScript_RedButtonGolem
	lockall
	call VolcanionCave_3F_EventScript_SetMetatilesRedButtonPressed
	special DrawWholeMapView
	releaseall
	end

VolcanionCave_3F_EventScript_RedButtonGolem::
	call VolcanionCave_3F_EventScript_SetMetatilesRedButtonPressed
	special DrawWholeMapView
	goto_if_eq VAR_GOLEM_ROCK_SLIDE_TIMER, 200, VolcanionCave_3F_EventScript_WaitStartRockSlide
	goto VolcanionCave_3F_EventScript_RockSlide
	return

VolcanionCave_3F_EventScript_WaitStartRockSlide::
	waitmovement 0
	goto VolcanionCave_3F_EventScript_RockSlideAfterMovement
	return	

VolcanionCave_3F_EventScript_SetMetatilesBlueButtonPressed::
	@ Golem puzzle
	setmetatile 25, 31, METATILE_Cave_CoolButton_Pressed, FALSE
	setmetatile 30, 31, METATILE_Cave_CoolButton_Pressed, FALSE
	setmetatile 24, 37, METATILE_Cave_CoolButton_Pressed, FALSE
	setmetatile 28, 29, METATILE_Cave_CoolButton_Red, FALSE
	setmetatile 24, 31, METATILE_Cave_CoolButton_Red, FALSE
	setmetatile 27, 28, METATILE_Cave_CoolGem_Blue_Floor_Empty, FALSE
	setmetatile 24, 30, METATILE_Cave_CoolGem_Blue_WaterEdge_Empty, FALSE
	setmetatile 23, 33, METATILE_Cave_CoolGem_Blue_Mud_Empty, FALSE
	setmetatile 25, 33, METATILE_Cave_CoolGem_Blue_Floor_Empty, FALSE
	setmetatile 28, 33, METATILE_Cave_CoolGem_Blue_Floor_Empty, FALSE
	setmetatile 29, 34, METATILE_Cave_CoolGem_Blue_Floor_Empty, FALSE
	setmetatile 26, 36, METATILE_Cave_CoolGem_Blue_Floor_Empty, FALSE
	setmetatile 25, 28, METATILE_Cave_CoolGem_Red_Floor_Full, TRUE
	setmetatile 29, 31, METATILE_Cave_CoolGem_Red_Floor_Full, TRUE
	setmetatile 27, 34, METATILE_Cave_CoolGem_Red_WaterEdge_Full, TRUE
	setmetatile 24, 36, METATILE_Cave_CoolGem_Red_Floor_Full, TRUE
	setmetatile 27, 37, METATILE_Cave_CoolGem_Red_Floor_Full, TRUE
	@ Agent diggs puzzle
	setmetatile 1, 10, METATILE_Cave_CoolButton_Pressed, FALSE
	setmetatile 10, 1, METATILE_Cave_CoolButton_Pressed, FALSE
	setmetatile 10, 18, METATILE_Cave_CoolButton_Pressed, FALSE
	setmetatile 1, 9, METATILE_Cave_CoolButton_Red, FALSE
	setmetatile 4, 18, METATILE_Cave_CoolButton_Red, FALSE
	setmetatile 6, 19, METATILE_Cave_CoolButton_Red, FALSE
	setmetatile 7, 1, METATILE_Cave_CoolGem_Blue_FloorSmooth_Empty, FALSE
	setmetatile 1, 8, METATILE_Cave_CoolGem_Blue_FloorSmooth_Empty, FALSE
	setmetatile 5, 8, METATILE_Cave_CoolGem_Blue_FloorSmooth_Empty, FALSE
	setmetatile 9, 1, METATILE_Cave_CoolGem_Red_FloorSmooth_Full, TRUE
	setmetatile 9, 10, METATILE_Cave_CoolGem_Red_Floor_Full, TRUE
	return

VolcanionCave_3F_EventScript_SetMetatilesRedButtonPressed::
	@ Golem puzzle
	setmetatile 25, 31, METATILE_Cave_CoolButton_Blue, FALSE
	setmetatile 30, 31, METATILE_Cave_CoolButton_Blue, FALSE
	setmetatile 24, 37, METATILE_Cave_CoolButton_Blue, FALSE
	setmetatile 28, 29, METATILE_Cave_CoolButton_Pressed, FALSE
	setmetatile 24, 31, METATILE_Cave_CoolButton_Pressed, FALSE
	setmetatile 27, 28, METATILE_Cave_CoolGem_Blue_Floor_Full, TRUE
	setmetatile 24, 30, METATILE_Cave_CoolGem_Blue_WaterEdge_Full, TRUE
	setmetatile 23, 33, METATILE_Cave_CoolGem_Blue_Mud_Full, TRUE
	setmetatile 25, 33, METATILE_Cave_CoolGem_Blue_Floor_Full, TRUE
	setmetatile 28, 33, METATILE_Cave_CoolGem_Blue_Floor_Full, TRUE
	setmetatile 29, 34, METATILE_Cave_CoolGem_Blue_Floor_Full, TRUE
	setmetatile 26, 36, METATILE_Cave_CoolGem_Blue_Floor_Full, TRUE
	setmetatile 25, 28, METATILE_Cave_CoolGem_Red_Floor_Empty, FALSE
	setmetatile 29, 31, METATILE_Cave_CoolGem_Red_Floor_Empty, FALSE
	setmetatile 27, 34, METATILE_Cave_CoolGem_Red_WaterEdge_Empty, FALSE
	setmetatile 24, 36, METATILE_Cave_CoolGem_Red_Floor_Empty, FALSE
	setmetatile 27, 37, METATILE_Cave_CoolGem_Red_Floor_Empty, FALSE
	@ Agent diggs puzzle
	setmetatile 1, 10, METATILE_Cave_CoolButton_Blue, FALSE
	setmetatile 10, 1, METATILE_Cave_CoolButton_Blue, FALSE
	setmetatile 10, 18, METATILE_Cave_CoolButton_Blue, FALSE
	setmetatile 1, 9, METATILE_Cave_CoolButton_Pressed, FALSE
	setmetatile 4, 18, METATILE_Cave_CoolButton_Pressed, FALSE
	setmetatile 6, 19, METATILE_Cave_CoolButton_Pressed, FALSE
	setmetatile 7, 1, METATILE_Cave_CoolGem_Blue_FloorSmooth_Full, TRUE
	setmetatile 1, 8, METATILE_Cave_CoolGem_Blue_FloorSmooth_Full, TRUE
	setmetatile 5, 8, METATILE_Cave_CoolGem_Blue_FloorSmooth_Full, TRUE
	setmetatile 9, 1, METATILE_Cave_CoolGem_Red_FloorSmooth_Empty, FALSE
	setmetatile 9, 10, METATILE_Cave_CoolGem_Red_Floor_Empty, FALSE
	return

VolcanionCave_3F_EventScript_SetMetatilesRocksBroken::
	setmetatile 10, 24, METATILE_Cave_FloorSmooth_Top, FALSE
	setmetatile 10, 25, METATILE_Cave_FloorSmooth, FALSE
	setmetatile 9, 25, METATILE_Cave_FloorSmooth, FALSE
	setmetatile 9, 26, METATILE_Cave_FloorSmooth, FALSE
	setmetatile 22, 24, METATILE_Cave_FloorSmooth_Top, FALSE
	setmetatile 22, 25, METATILE_Cave_FloorSmooth, FALSE
	setmetatile 23, 25, METATILE_Cave_FloorSmooth, FALSE
	setmetatile 23, 26, METATILE_Cave_FloorSmooth, FALSE
	return

VolcanionCave_3F_EventScript_SetHPBar::
	call_if_ne VAR_LOCALID_CURRENT_HP_BAR, 0, VolcanionCave_3F_EventScript_RemoveHPBar
	setvar VAR_LOCALID_CURRENT_HP_BAR, 0
	switch VAR_CURRENT_HP_BAR_COLOR
	case_call 1, VolcanionCave_3F_EventScript_SetHPBarGreen
	case_call 2, VolcanionCave_3F_EventScript_SetHPBarYellow
	case_call 3, VolcanionCave_3F_EventScript_SetHPBarRed
	goto_if_eq VAR_LOCALID_CURRENT_HP_BAR, 0, VolcanionCave_3F_EventScript_AddNoHPBar
	addobject VAR_LOCALID_CURRENT_HP_BAR
	setobjectxyperm VAR_LOCALID_CURRENT_HP_BAR, 16, 19
	setobjectxy VAR_LOCALID_CURRENT_HP_BAR, 16, 19
	return

VolcanionCave_3F_EventScript_RemoveHPBar::
	setobjectxyperm VAR_LOCALID_CURRENT_HP_BAR, 43, 18
	setobjectxy VAR_LOCALID_CURRENT_HP_BAR, 43, 18
	return

VolcanionCave_3F_EventScript_AddNoHPBar::
	return

VolcanionCave_3F_EventScript_SetHPBarGreen::
	goto_if_eq VAR_VOLCANION_CAVE_3F_PIKACHU_STATE, 100, VolcanionCave_3F_EventScript_SetHPBarGreenPara
	goto_if_eq VAR_ZINNIA_STATE, 1, VolcanionCave_3F_EventScript_SetHPBarGreenStats
	setvar VAR_LOCALID_CURRENT_HP_BAR LOCALID_3F_HP_BAR_GREEN
	return

VolcanionCave_3F_EventScript_SetHPBarGreenPara::
	goto_if_eq VAR_ZINNIA_STATE, 1, VolcanionCave_3F_EventScript_SetHPBarGreenParaStats
	setvar VAR_LOCALID_CURRENT_HP_BAR LOCALID_3F_HP_BAR_GREEN_PARA
	return

VolcanionCave_3F_EventScript_SetHPBarGreenStats::
	setvar VAR_LOCALID_CURRENT_HP_BAR LOCALID_3F_HP_BAR_GREEN_STATS
	return

VolcanionCave_3F_EventScript_SetHPBarGreenParaStats::
	setvar VAR_LOCALID_CURRENT_HP_BAR LOCALID_3F_HP_BAR_GREEN_PARA_STATS
	return

VolcanionCave_3F_EventScript_SetHPBarYellow::
	goto_if_eq VAR_VOLCANION_CAVE_3F_PIKACHU_STATE, 100, VolcanionCave_3F_EventScript_SetHPBarYellowPara
	goto_if_eq VAR_ZINNIA_STATE, 1, VolcanionCave_3F_EventScript_SetHPBarYellowStats
	setvar VAR_LOCALID_CURRENT_HP_BAR LOCALID_3F_HP_BAR_YELLOW
	return

VolcanionCave_3F_EventScript_SetHPBarYellowPara::
	goto_if_eq VAR_ZINNIA_STATE, 1, VolcanionCave_3F_EventScript_SetHPBarYellowParaStats
	setvar VAR_LOCALID_CURRENT_HP_BAR LOCALID_3F_HP_BAR_YELLOW_PARA
	return

VolcanionCave_3F_EventScript_SetHPBarYellowStats::
	setvar VAR_LOCALID_CURRENT_HP_BAR LOCALID_3F_HP_BAR_YELLOW_STATS
	return

VolcanionCave_3F_EventScript_SetHPBarYellowParaStats::
	setvar VAR_LOCALID_CURRENT_HP_BAR LOCALID_3F_HP_BAR_YELLOW_PARA_STATS
	return

VolcanionCave_3F_EventScript_SetHPBarRed::
	goto_if_eq VAR_VOLCANION_CAVE_3F_PIKACHU_STATE, 100, VolcanionCave_3F_EventScript_SetHPBarRedPara
	goto_if_eq VAR_ZINNIA_STATE, 1, VolcanionCave_3F_EventScript_SetHPBarRedStats
	setvar VAR_LOCALID_CURRENT_HP_BAR LOCALID_3F_HP_BAR_RED
	return

VolcanionCave_3F_EventScript_SetHPBarRedPara::
	goto_if_eq VAR_ZINNIA_STATE, 1, VolcanionCave_3F_EventScript_SetHPBarRedParaStats
	setvar VAR_LOCALID_CURRENT_HP_BAR LOCALID_3F_HP_BAR_RED_PARA
	return

VolcanionCave_3F_EventScript_SetHPBarRedStats::
	setvar VAR_LOCALID_CURRENT_HP_BAR LOCALID_3F_HP_BAR_RED_STATS
	return

VolcanionCave_3F_EventScript_SetHPBarRedParaStats::
	setvar VAR_LOCALID_CURRENT_HP_BAR LOCALID_3F_HP_BAR_RED_PARA_STATS
	return

VolcanionCave_3F_EventScript_Volcanion::
	lock
	call VolcanionCave_3F_EventScript_VolcanionCry
	closemessage
	goto_if_unset FLAG_PLAYER_2_READY_TO_BATTLE_TOGETHER, VolcanionCave_3F_EventScript_AskVolcanionMultiBattle
	clearflag FLAG_PLAYER_2_READY_TO_BATTLE_TOGETHER
	getplayerxy VAR_0x8008, VAR_0x8009
	special SpawnCameraObject
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, VolcanionCave_3F_EventScript_PlayerWalkLeftForBattle
	call_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_PlayerWalkRightForBattle
	setwildbattle SPECIES_VOLCANION, 40, TRUE
	multi_fixed_players_vs_wild PARTNER_PLAYER_2
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, VolcanionCave_3F_EventScript_DefeatedVolcanion
	call VolcanionCave_3F_EventScript_VolcanionCry
	closemessage
	special RemoveCameraObject
	special SpawnCameraObject
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, VolcanionCave_3F_EventScript_CameraResetToAqua
	call_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_CameraResetToMagma
	waitmovement 0
	special RemoveCameraObject
	release
	end

VolcanionCave_3F_EventScript_AskVolcanionMultiBattle::
	delay 10
	msgbox VolcanionCave_3F_Text_BattleTogether, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, VolcanionCave_3F_EventScript_GetReadyForVolcanionMultiBattle
	closemessage
	release
	end

VolcanionCave_3F_EventScript_GetReadyForVolcanionMultiBattle::
	closemessage
	setflag FLAG_SET_PLAYER_2_FOR_VOLCANION_BATTLE
	setflag FLAG_PLAYER_2_READY_TO_BATTLE_TOGETHER
	callnative SwitchCharacters
	waitstate
	release
	end

VolcanionCave_3F_EventScript_AquaWalkDownForBattle::
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerWalkDownForBattle
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraCenterRightForBattle
	waitmovement 0
	return

VolcanionCave_3F_EventScript_MagmaWalkDownForBattle::
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerWalkDownForBattle
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraCenterLeftForBattle
	waitmovement 0
	return

VolcanionCave_3F_EventScript_PlayerWalkLeftForBattle::
	goto_if_eq VAR_0x8009, 21, VolcanionCave_3F_EventScript_AquaWalkDownForBattle
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerWalkLeftForBattle
	waitmovement 0
	return

VolcanionCave_3F_EventScript_PlayerWalkRightForBattle::
	goto_if_eq VAR_0x8009, 21, VolcanionCave_3F_EventScript_MagmaWalkDownForBattle
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerWalkRightForBattle
	waitmovement 0
	return

VolcanionCave_3F_Movement_PlayerWalkDownForBattle::
	walk_down
	walk_in_place_up
	step_end

VolcanionCave_3F_Movement_PlayerWalkLeftForBattle::
	walk_left
	walk_in_place_up
	step_end

VolcanionCave_3F_Movement_PlayerWalkRightForBattle::
	walk_right
	walk_in_place_up
	step_end

VolcanionCave_3F_Movement_CameraCenterLeftForBattle::
	walk_diag_southwest
	step_end

VolcanionCave_3F_Movement_CameraCenterRightForBattle::
	walk_diag_southeast
	step_end

VolcanionCave_3F_EventScript_DefeatedVolcanion::
	setvar VAR_CURRENT_HP_BAR_COLOR, 0
	call VolcanionCave_3F_EventScript_SetHPBar
	playmoncry SPECIES_VOLCANION, CRY_MODE_NORMAL
	message VolcanionCave_3F_Text_VolcanionCryDefeated
	waitmessage
	waitmoncry
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, VolcanionCave_3F_EventScript_SetLocalIdsPlayer1
	call_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_SetLocalIdsPlayer2
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	message VolcanionCave_3F_Text_WeDidIt
	delay 25
	removeobject LOCALID_3F_DIGLETT
	waitmessage
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_WalkInPlaceUp
	message VolcanionCave_3F_Text_FinishingTouch
	waitmessage
	playse SE_M_DIZZY_PUNCH
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_QuestionMark
	waitmovement 0
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_WalkInPlaceRight
	message VolcanionCave_3F_Text_WhereBalls
	waitmessage
	playse SE_M_DIZZY_PUNCH
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_QuestionMark
	message VolcanionCave_3F_Text_WhereBalls2
	waitmessage
	addobject LOCALID_3F_DIGLETT
	setobjectxy LOCALID_3F_DIGLETT, 16, 26
	turnobject LOCALID_3F_DIGLETT, DIR_NORTH
	lock
	playse SE_M_DIG
	call VolcanionCave_3F_EventScript_DiglettCry
	closemessage
	playse SE_PIN
	applymovement LOCALID_PLAYER_AQUA, VolcanionCave_3F_Movement_NoticeDiglett
	applymovement LOCALID_PLAYER_MAGMA, VolcanionCave_3F_Movement_NoticeDiglett
	waitmovement 0
	special RemoveCameraObject
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveToDiglett
	waitmovement 0
	call_if_set FLAG_AGENT_DIGGS_DIED, VolcanionCave_3F_EventScript_AgentDiggsOk
	call_if_unset FLAG_AGENT_DIGGS_DIED, VolcanionCave_3F_EventScript_AgentDiggs
	waitmessage
	closemessage
	applymovement LOCALID_3F_DIGLETT, VolcanionCave_3F_EventScript_DiglettWalkToVolcanion
	applymovement LOCALID_CAMERA, VolcanionCave_3F_EventScript_CameraMoveUpWithDiglett
	delay 30
	playse SE_M_DIZZY_PUNCH
	applymovement LOCALID_PLAYER_AQUA, VolcanionCave_3F_Movement_AquaWatchDiglett
	applymovement LOCALID_PLAYER_MAGMA, VolcanionCave_3F_Movement_MagmaWatchDiglett
	waitmovement 0
	delay 50
	playse SE_BALL_THROW
	addobject LOCALID_3F_VOLCANION_JAIL_CELL
	applymovement LOCALID_3F_VOLCANION_JAIL_CELL, VolcanionCave_3F_Movement_DiglettThrowJailCell
	delay 3
	setobjectsubpriority LOCALID_3F_VOLCANION_JAIL_CELL, MAP_VOLCANION_CAVE_3F, 200
	waitmovement 0
	delay 20
	playse SE_BALL_OPEN
	delay 20
	removeobject LOCALID_3F_VOLCANION
	setflag FLAG_HIDE_VOLCANION_CAVE_3F_VOLCANION
	delay 20
	playse SE_BALL
	applymovement LOCALID_3F_VOLCANION_JAIL_CELL, VolcanionCave_3F_Movement_JailCellShake
	waitmovement 0
	playse SE_BALL
	applymovement LOCALID_3F_VOLCANION_JAIL_CELL, VolcanionCave_3F_Movement_JailCellShake
	waitmovement 0
	playse SE_BALL
	applymovement LOCALID_3F_VOLCANION_JAIL_CELL, VolcanionCave_3F_Movement_JailCellShake
	waitmovement 0
	playse SE_RG_BALL_CLICK
	applymovement LOCALID_3F_VOLCANION_JAIL_CELL, VolcanionCave_3F_Movement_JailCellJump
	waitmovement 0
	delay 20
	playse SE_PIN
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_ExclamationMark
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_ExclamationMark
	message VolcanionCave_3F_Text_AgentDiggsCatch
	waitmessage
	closemessage
	addobject LOCALID_3F_SHELLY
	playse SE_PIN
	delay 20
	applymovement LOCALID_3F_SHELLY, VolcanionCave_3F_Movement_ShellyEnter
	delay 30
	applymovement LOCALID_CAMERA, Common_Movement_WalkDown
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_WalkInPlaceDown
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_WalkInPlaceDown
	waitmovement LOCALID_3F_SHELLY
	message VolcanionCave_3F_Text_ShellyEnter
	waitmessage
	resetobjectsubpriority LOCALID_3F_VOLCANION_JAIL_CELL, MAP_VOLCANION_CAVE_3F
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	playse SE_WIN_OPEN
	applymovement LOCALID_3F_DIGLETT, VolcanionCave_3F_Movement_DiglettTakePokeball
	waitmovement 0
	removeobject LOCALID_3F_VOLCANION_JAIL_CELL
	setflag FLAG_HIDE_VOLCANION_CAVE_3F_JAIL_CELL
	closemessage
	waitse
	playse SE_PIN
	playse SE_PIN
	playse SE_PIN
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_ExclamationMark
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_ExclamationMark
	applymovement LOCALID_3F_SHELLY, Common_Movement_ExclamationMark
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_WalkInPlaceUp
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_WalkInPlaceUp
	waitmovement 0
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_MoveToDiglettRunningAround
	applymovement LOCALID_3F_DIGLETT, VolcanionCave_3F_Movement_DiglettRunAround
	delay 30
	applymovement LOCALID_PLAYER_AQUA, Common_Movement_WalkInPlaceDown
	applymovement LOCALID_PLAYER_MAGMA, Common_Movement_WalkInPlaceDown
	applymovement LOCALID_3F_SHELLY, VolcanionCave_3F_Movement_ShellyChaseDiglett
	delay 100
	closemessage
	goto VolcanionCave_3F_EventScript_Credits

VolcanionCave_3F_EventScript_SetLocalIdsPlayer1::
	setvar LOCALID_PLAYER_AQUA, LOCALID_PLAYER
	setvar LOCALID_PLAYER_MAGMA, LOCALID_PLAYER_2
	return

VolcanionCave_3F_EventScript_SetLocalIdsPlayer2::
	setvar LOCALID_PLAYER_AQUA, LOCALID_PLAYER_2
	setvar LOCALID_PLAYER_MAGMA, LOCALID_PLAYER
	return

VolcanionCave_3F_EventScript_AgentDiggsOk::
	message VolcanionCave_3F_Text_AgentDiggsOk
	return

VolcanionCave_3F_EventScript_AgentDiggs::
	message VolcanionCave_3F_Text_AgentDiggs
	return

VolcanionCave_3F_Movement_NoticeDiglett::
	emote_exclamation_mark
	walk_in_place_down
	step_end

VolcanionCave_3F_EventScript_DiglettWalkToVolcanion::
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_3F_EventScript_CameraMoveUpWithDiglett::
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_3F_Movement_AquaWatchDiglett::
	emote_question_mark
	walk_in_place_right
	step_end

VolcanionCave_3F_Movement_MagmaWatchDiglett::
	emote_question_mark
	walk_in_place_left
	step_end

VolcanionCave_3F_Movement_CameraMoveToDiglett::
	walk_down
	walk_down
	walk_down
	step_end

VolcanionCave_3F_Movement_DiglettThrowJailCell::
	walk_fast_up
	step_end

VolcanionCave_3F_Movement_JailCellShake::
	levitate
	delay_16
	stop_levitate
	delay_16
	delay_16
	step_end

VolcanionCave_3F_Movement_JailCellJump::
	jump_in_place_down
	delay_16
	step_end

VolcanionCave_3F_Movement_ShellyEnter::
	emote_exclamation_mark
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_3F_Movement_DiglettTakePokeball::
	walk_fast_up
	step_end

VolcanionCave_3F_Movement_MoveToDiglettRunningAround::
	walk_down
	walk_down
	step_end

VolcanionCave_3F_Movement_DiglettRunAround::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

VolcanionCave_3F_Movement_ShellyChaseDiglett::
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

VolcanionCave_3F_Text_BattleTogether::
	.string "Battle together?$"

VolcanionCave_3F_Text_VolcanionCryDefeated::
	.string "{SPEAKER NAME_VOLCANION COLOR_NORMAL}FWAHHRSHHHH…$"

VolcanionCave_3F_Text_WeDidIt::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}AWWWW YEEEAAAAHHHHH!!!!\p$"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Incredible… we actually won.\p$"

VolcanionCave_3F_Text_FinishingTouch::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Now, for the finishing touch…\p$"

VolcanionCave_3F_Text_WhereBalls::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Hey! Where did my GREAT BALLS go???\p$"

VolcanionCave_3F_Text_WhereBalls2::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}My POKé BALLS are missing too.\n"
	.string "Who could have-{PAUSE 20}$"

VolcanionCave_3F_Text_AgentDiggsOk::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}AGENT DIGGS! You're ok!!\p$"

VolcanionCave_3F_Text_AgentDiggs::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}AGENT DIGGS!!\p$"

VolcanionCave_3F_Text_AgentDiggsCatch::	
	.string "AGENT DIGGS caught the VOLCANION!\p$"

VolcanionCave_3F_Text_ShellyEnter::
	.string "{SPEAKER NAME_SHELLY COLOR_AQUA}Somebody, stop that DIGLETT!!{PAUSE 40}\n"
	.string "He's trying to nab our LEGENDARY!!!{PAUSE 40}$"

VolcanionCave_3F_Text_Epilogue::
	.string "{SPEAKER NAME_NONE COLOR_NORMAL}And so, AGENT DIGGS ran off with\n"
	.string "VOLCANION, selling it to the KALOS\l"
	.string "POKéMON LAB for a digillion dollars.\p"
	.string "The professor, MABLE, locked it in a\n"
	.string "dark room for some unknown reason.\p"
	.string "TO BE CONTINUED IN:\n"
	.string "{PAUSE 60}POKéMON LEGENDS Z-A\p$"

VolcanionCave_3F_EventScript_ZinniaEnter::
	setvar VAR_ZINNIA_STATE, 1
	addobject LOCALID_3F_WHISMUR
	applymovement LOCALID_3F_WHISMUR, VolcanionCave_3F_Movement_WhismurEnter
	delay 4
	playse SE_LEDGE
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerGetPushedByWhismur
	waitmovement 0
	callnative HideWarpArrow
	playmoncry SPECIES_WHISMUR, CRY_MODE_NORMAL
	message VolcanionCave_3F_Text_WhismurCry
	waitmessage
	waitmoncry
	closemessage
	clearflag FLAG_HIDE_VOLCANION_CAVE_3F_ZINNIA
	addobject LOCALID_3F_ZINNIA
	setobjectxyperm LOCALID_3F_ZINNIA, 4, 38
	setobjectxy LOCALID_3F_ZINNIA, 4, 39
	applymovement LOCALID_3F_ZINNIA, VolcanionCave_3F_Movement_ZinniaEnter
	delay 30
	playse SE_PIN
	waitmovement 0
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, VolcanionCave_3F_EventScript_ZinniaDialogueAqua
	call_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_ZinniaDialogueMagma
	waitmessage
	applymovement LOCALID_3F_ZINNIA, Common_Movement_WalkInPlaceUp
	waitmovement 0
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveToWhismur
	message VolcanionCave_3F_Text_ZinniaAskAster
	waitmessage
	playmoncry SPECIES_WHISMUR, CRY_MODE_NORMAL
	message VolcanionCave_3F_Text_AsterCry
	waitmessage
	waitmoncry
	closemessage
	playbgm MUS_VS_VOLCANION, FALSE
	applymovement LOCALID_3F_WHISMUR, VolcanionCave_3F_Movement_WhismurStartSlidePuzzle
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_WhismurStartSlidePuzzle
	waitmovement 0
	playse SE_M_DIZZY_PUNCH
	applymovement LOCALID_3F_WHISMUR, VolcanionCave_3F_Movement_WhismurBeConfused
	waitmovement 0
	applymovement LOCALID_3F_WHISMUR, VolcanionCave_3F_Movement_WhismurFinishSlidePuzzle
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_WhismurFinishSlidePuzzle
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_3F_WHISMUR, VolcanionCave_3F_Movement_WhismurCelebrate
	waitmovement 0
	applymovement LOCALID_3F_WHISMUR, VolcanionCave_3F_Movement_WhismurRunToVolcanion
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveWithWhismurToVolcanion
	waitmovement 0
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, VolcanionCave_3F_EventScript_AsterUsedScreeeechAqua
	call_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_AsterUsedScreeeechMagma
	waitmessage
	setvar VAR_0x8004, 0  @ Vertical pan
	setvar VAR_0x8005, 7  @ Horizontal pan
	setvar VAR_0x8006, 15  @ Num shakes
	setvar VAR_0x8007, 3  @ Shake delay
	special ShakeScreen
	playse SE_M_SCREECH
	delay 10
	playse SE_M_SCREECH
	delay 10
	playse SE_M_SCREECH
	delay 20
	playse SE_M_STAT_DECREASE
	applymovement LOCALID_3F_VOLCANION, VolcanionCave_3F_Movement_VolcanionShake
	waitmovement 0
	call VolcanionCave_3F_EventScript_SetHPBar
	lock
	message VolcanionCave_3F_Text_VolcanionsStatsDropped
	waitmessage
	call VolcanionCave_3F_EventScript_VolcanionCry
	message VolcanionCave_3F_Text_VolcanionUsedFlamethrower
	waitmessage
	playse SE_BALL_OPEN
	waitse
	closemessage
	removeobject LOCALID_3F_WHISMUR
	delay 20
	call VolcanionCave_3F_EventScript_VolcanionCry
	closemessage
	fadedefaultbgm
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveBackToZinnia
	waitmovement 0
	special RemoveCameraObject
	message VolcanionCave_3F_Text_GoodJobAster
	waitmessage
	closemessage
	release
	end

VolcanionCave_3F_EventScript_ZinniaDialogueAqua::
	message VolcanionCave_3F_Text_ZinniaDialogueAqua
	return

VolcanionCave_3F_EventScript_ZinniaDialogueMagma::
	message VolcanionCave_3F_Text_ZinniaDialogueMagma
	return

VolcanionCave_3F_EventScript_AsterUsedScreeeechAqua::
	message VolcanionCave_3F_Text_AsterUsedScreeeechAqua
	return

VolcanionCave_3F_EventScript_AsterUsedScreeeechMagma::
	message VolcanionCave_3F_Text_AsterUsedScreeeechMagma
	return

VolcanionCave_3F_Movement_WhismurEnter::
	walk_fast_up
	walk_fast_up
	walk_in_place_down
	step_end

VolcanionCave_3F_Movement_PlayerGetPushedByWhismur::
	face_left
	lock_facing_direction
	jump_right
	unlock_facing_direction
	step_end

VolcanionCave_3F_Movement_ZinniaEnter::
	walk_up
	delay_16
	emote_exclamation_mark
	walk_in_place_right
	step_end

VolcanionCave_3F_Movement_CameraMoveToWhismur::
	walk_diag_northwest
	step_end

VolcanionCave_3F_Movement_WhismurStartSlidePuzzle::
	walk_fast_right
	walk_fast_up
	walk_fast_up
	lock_anim
	walk_fast_up
	unlock_anim
	face_left
	lock_anim
	walk_fast_left
	walk_fast_left
	walk_fast_left
	unlock_anim
	face_down
	lock_anim
	walk_fast_down
	unlock_anim
	face_right
	lock_anim
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	unlock_anim
	face_down
	lock_anim
	walk_fast_down
	unlock_anim
	face_left
	lock_anim
	walk_fast_left
	unlock_anim
	face_up
	lock_anim
	walk_fast_up
	walk_fast_up
	unlock_anim
	face_right
	lock_anim
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	delay_16
	unlock_anim
	step_end

VolcanionCave_3F_Movement_WhismurBeConfused::
	emote_question_mark
	delay_16
	face_up
	delay_16
	face_down
	delay_16
	face_right
	delay_16
	delay_16
	step_end

VolcanionCave_3F_Movement_WhismurFinishSlidePuzzle::
	face_left
	lock_anim
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	unlock_anim
	face_down
	lock_anim
	walk_fast_down
	walk_fast_down
	unlock_anim
	face_right
	lock_anim
	walk_fast_right
	unlock_anim
	face_up
	lock_anim
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	unlock_anim
	walk_fast_up
	walk_fast_up
	lock_anim
	walk_fast_up
	unlock_anim
	face_left
	lock_anim
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	unlock_anim
	face_up
	lock_anim
	walk_fast_up
	unlock_anim
	delay_16
	step_end

VolcanionCave_3F_Movement_WhismurCelebrate::
	emote_exclamation_mark
	jump_in_place_down
	jump_in_place_down
	delay_16
	delay_16
	step_end

VolcanionCave_3F_Movement_WhismurRunToVolcanion::
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	step_end

VolcanionCave_3F_Movement_CameraMoveWithWhismurToVolcanion::
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
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
	step_end

VolcanionCave_3F_Movement_CameraMoveBackToZinnia::
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

VolcanionCave_3F_Text_WhismurCry::
	.string "{SPEAKER NAME_WHISMUR COLOR_ZINNIA}Walawala!\p$"

VolcanionCave_3F_Text_ZinniaDialogueAqua::
	.string "{SPEAKER NAME_AQUA_QUESTION COLOR_ZINNIA}Come on, ASTER!\p"
	.string "We're so close to finding what we're\n"
	.string "looking for, I can feel it!\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}And what do we have here?\p"
	.string "{SPEAKER NAME_AQUA_QUESTION COLOR_ZINNIA}Excuse me?\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Just when I thought I found a new\n"
	.string "AQUA GRUNT to befriend, this walking\l"
	.string "dress code violation shows up instead!\p"
	.string "{SPEAKER NAME_AQUA_QUESTION COLOR_ZINNIA}{AUTO_SCROLL 1}Well, that's-{PAUSE 20}\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}{AUTO_SCROLL 0}NO EXCUSES!\p"
	.string "The stripes on your shirt are 2 cm wider\n"
	.string "than they should be, your pants don't\l"
	.string "have a single hole in them, and your hair\l"
	.string "isn't even dyed orange!\p"
	.string "This is TEAM AQUA, not the CIRCUS!!\p"
	.string "{SPEAKER NAME_AQUA_QUESTION COLOR_ZINNIA}Wow, and here I thought this was\n"
	.string "a pretty convicing disguise.\p"
	.string "You found me out, I'm not actually\n"
	.string "a TEAM AQUA GRUNT.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}YOU'RE A SPY FROM TEAM MAGMA????\p"
	.string "{SPEAKER NAME_AQUA_QUESTION COLOR_ZINNIA}Hold on, let me finish.\p"
	.string "{SPEAKER NAME_ZINNIA COLOR_ZINNIA}My name is ZINNIA, and I'm looking\n"
	.string "for MEGA STONES.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Aren't those the weird shiny rocks\n"
	.string "that fell from the sky when RAYQUAZA\l"
	.string "stopped KYOGRE from totally owning\l"
	.string "that stupid GROUDON?\p"
	.string "{SPEAKER NAME_ZINNIA COLOR_ZINNIA}Yes, I guess you could say that.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Well I'm no science-ologist, but\n"
	.string "VOLCANO CAVERN is just about as\l"
	.string "far away from the sky as you can get.\p"
	.string "{SPEAKER NAME_ZINNIA COLOR_ZINNIA}Aw man, {HESHE_1}'s got a point.\p"
	.string "Hey, want to do me a favour and stay\n"
	.string "quiet about all this while I sneak out?\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Not really.\p"
	.string "{SPEAKER NAME_ZINNIA COLOR_ZINNIA}How about if I help you out with that\n"
	.string "LEGENDARY POKéMON that's been giving\l"
	.string "you some trouble?\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Oh fine, just make it quick.\p"
	.string "{SPEAKER NAME_ZINNIA COLOR_ZINNIA}You betcha!\p$"

VolcanionCave_3F_Text_ZinniaDialogueMagma::
	.string "{SPEAKER NAME_AQUA_QUESTION COLOR_ZINNIA}Come on, ASTER!\p"
	.string "We're so close to finding what we're\n"
	.string "looking for, I can feel it!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Weird.\p"
	.string "{SPEAKER NAME_AQUA_QUESTION COLOR_ZINNIA}Excuse me?\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Your hair, it's not orange like the\n"
	.string "rest of the AQUA GRUNTS.\p"
	.string "{SPEAKER NAME_AQUA_QUESTION COLOR_ZINNIA}{AUTO_SCROLL 1}Well, that's-{PAUSE 20}\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}{AUTO_SCROLL 0}And your accent.\p"
	.string "If mine was red and {PLAYER_AQUA}'s was blue,\n"
	.string "yours would be… green?\p"
	.string "{SPEAKER NAME_AQUA_QUESTION COLOR_ZINNIA}Alright, alright.\p"
	.string "That's enough scrutinizing, you got me.\p"
	.string "{SPEAKER NAME_ZINNIA COLOR_ZINNIA}My name is ZINNIA, and I'm not with\n"
	.string "either team here.\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}So you're a spy? For who?\p"
	.string "{SPEAKER NAME_ZINNIA COLOR_ZINNIA}Not quite.\p"
	.string "I'm looking for MEGA STONES, and it\n"
	.string "would have been impossible to walk\l"
	.string "around here freely without a disguise.\p"
	.string "That's all, I promise.\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}MEGA STONES? In a cave?\p"
	.string "News flash bud, those fell from the\n"
	.string "sky when RAYQUAZA broke up GROUDON\l"
	.string "and KYOGRE'S fight.\p"
	.string "You're looking for those things on\n"
	.string "the wrong side of the crust.\p"
	.string "{SPEAKER NAME_ZINNIA COLOR_ZINNIA}Aw man, {HESHE_2}'s got a point.\p"
	.string "Well then, guess I'll skedaddle.\p"
	.string "Wouldn't want the AQUA ADMINS to\n"
	.string "know I'm running around here in a\l"
	.string "poorly-made cosplay.\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Before you go, can I make a proposal?\p"
	.string "{SPEAKER NAME_ZINNIA COLOR_ZINNIA}Ooo! I do! I do!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}NOT WHAT I MEANT.\p"
	.string "I've been {FONT 5}reluctantly {FONT_NORMAL}working with\n"
	.string "a GRUNT from TEAM AQUA.\p"
	.string "If you were willing to help out with\n"
	.string "the pissed-off LEGENDARY POKéMON\l"
	.string "over there, I might consider keeping\l"
	.string "this whole conversation to myself.\p"
	.string "{SPEAKER NAME_ZINNIA COLOR_ZINNIA}Easiest deal of my life!\p$"

VolcanionCave_3F_Text_ZinniaAskAster::
	.string "{SPEAKER NAME_ZINNIA COLOR_ZINNIA}Go get em, ASTER!\p$"

VolcanionCave_3F_Text_AsterCry::
	.string "{SPEAKER NAME_ASTER COLOR_ZINNIA}Walawala!\p$"

VolcanionCave_3F_Text_AsterUsedScreeeechAqua::
	.string "{SPEAKER NAME_ZINNIA COLOR_ZINNIA}Cover your ears.\p"
	.string "{AUTO_SCROLL 1}{SPEAKER NAME_PLAYER COLOR_AQUA}Uh, okay-{PAUSE 20}\p"
	.string "{AUTO_SCROLL 0}{SPEAKER NAME_NONE COLOR_NORMAL}ASTER used SCREEEECH!$"

VolcanionCave_3F_Text_AsterUsedScreeeechMagma::
	.string "{SPEAKER NAME_ZINNIA COLOR_ZINNIA}Cover your ears.\p"
	.string "{AUTO_SCROLL 1}{SPEAKER NAME_PLAYER COLOR_MAGMA}Why-{PAUSE 20}\p"
	.string "{AUTO_SCROLL 0}{SPEAKER NAME_NONE COLOR_NORMAL}ASTER used SCREEEECH!$"

VolcanionCave_3F_Text_VolcanionsStatsDropped::
	.string "VOLCANION's stats dropped!\p$"

VolcanionCave_3F_Text_VolcanionUsedFlamethrower::
	.string "{AUTO_SCROLL 1}{SPEAKER NAME_NONE COLOR_NORMAL}VOLCANION used FLAMETHROWE-{PAUSE 10}\p"
	.string "{AUTO_SCROLL 0}{SPEAKER NAME_ZINNIA COLOR_ZINNIA}ASTER, return!$"

VolcanionCave_3F_Text_GoodJobAster::
	.string "{SPEAKER NAME_ZINNIA COLOR_ZINNIA}Nice going, ASTER!\p"
	.string "I'll let you rest a bit before we leave,\n"
	.string "you deserve it after that performance!\p$"

VolcanionCave_3F_EventScript_Zinnia::
	lock
	msgbox VolcanionCave_3F_Text_Zinnia, MSGBOX_NPC
	release
	end

VolcanionCave_3F_Text_Zinnia::
	.string "{SPEAKER NAME_ZINNIA COLOR_ZINNIA}Mind giving ASTER some space?\n"
	.string "She's all tuckered out now.$"

VolcanionCave_3F_EventScript_Whismur::
	release
	end

VolcanionCave_3F_EventScript_Golem::
	applymovement LOCALID_3F_GOLEM, Common_Movement_FacePlayer
	goto_if_set FLAG_ROCK_SLIDE_HIT_VOLCANION, VolcanionCave_3F_EventScript_GolemSatisfied
	call VolcanionCave_3F_EventScript_SetMetatilesRockSlideBlockade
	special DrawWholeMapView
	playmoncry SPECIES_GOLEM_ALOLA, CRY_MODE_ENCOUNTER
	message VolcanionCave_3F_Text_GolemCry
	waitmoncry
	waitmessage
	closemessage
	delay 10
	goto_if_set FLAG_TALKED_VOLCANION_CAVE_3F_GOLEM, VolcanionCave_3F_EventScript_GolemUsedRockSlide
	setflag FLAG_TALKED_VOLCANION_CAVE_3F_GOLEM
	message VolcanionCave_3F_Text_GolemSeemsAngry
	waitmessage
	closemessage
	delay 20
	playbgm MUS_VS_VOLCANION, FALSE
	call VolcanionCave_3F_EventScript_RockSlideSpawnRocks
	resetobjectsubpriority LOCALID_3F_ROCK_SLIDE_1, MAP_VOLCANION_CAVE_3F
	resetobjectsubpriority LOCALID_3F_ROCK_SLIDE_2, MAP_VOLCANION_CAVE_3F
	resetobjectsubpriority LOCALID_3F_ROCK_SLIDE_3, MAP_VOLCANION_CAVE_3F
	message VolcanionCave_3F_Text_GolemUsedRockSlide
	delay 5
	playse SE_PIN
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerNoticeRockSlide
	waitmovement 0
	waitmessage
	closemessage
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerDodgeRockSlideLeftDown
	call VolcanionCave_3F_EventScript_RockSlideDropRocks
	call VolcanionCave_3F_EventScript_RockSlideRemoveRocks
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, VolcanionCave_3F_EventScript_MaybeICanUseThisAqua
	call_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_MaybeICanUseThisMagma
	waitmessage
	call VolcanionCave_3F_EventScript_RockSlideSpawnRocks
	delay 5
	playse SE_PIN
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerNoticeRockSlide
	waitmovement 0
	delay 20
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, VolcanionCave_3F_EventScript_GottaRunAqua
	call_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_GottaRunMagma
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerDodgeRockSlideUp
	call VolcanionCave_3F_EventScript_RockSlideDropRocks
	call VolcanionCave_3F_EventScript_RockSlideRemoveRocks
	closemessage
	setvar VAR_GOLEM_ROCK_SLIDE_STATE, 1
	setvar VAR_GOLEM_ROCK_SLIDE_TIMER, 0
	goto VolcanionCave_3F_EventScript_RockSlide
	end

VolcanionCave_3F_EventScript_GolemUsedRockSlide::
	playbgm MUS_VS_VOLCANION, FALSE
	call VolcanionCave_3F_EventScript_RockSlideSpawnRocks
	resetobjectsubpriority LOCALID_3F_ROCK_SLIDE_1, MAP_VOLCANION_CAVE_3F
	resetobjectsubpriority LOCALID_3F_ROCK_SLIDE_2, MAP_VOLCANION_CAVE_3F
	resetobjectsubpriority LOCALID_3F_ROCK_SLIDE_3, MAP_VOLCANION_CAVE_3F
	message VolcanionCave_3F_Text_GolemUsedRockSlide
	delay 5
	playse SE_PIN
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerNoticeRockSlide
	waitmovement 0
	waitmessage
	delay 20
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, VolcanionCave_3F_EventScript_GottaRunAqua
	call_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_GottaRunMagma
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerDodgeRockSlideLeftDown
	call VolcanionCave_3F_EventScript_RockSlideDropRocks
	call VolcanionCave_3F_EventScript_RockSlideRemoveRocks
	closemessage
	setvar VAR_GOLEM_ROCK_SLIDE_STATE, 1
	setvar VAR_GOLEM_ROCK_SLIDE_TIMER, 0
	goto VolcanionCave_3F_EventScript_RockSlide
	end

VolcanionCave_3F_EventScript_RockSlide::
	delay 1
	addvar VAR_GOLEM_ROCK_SLIDE_TIMER, 1
	goto_if_le VAR_GOLEM_ROCK_SLIDE_TIMER, 20, VolcanionCave_3F_EventScript_RockSlide

	setvar VAR_GOLEM_ROCK_SLIDE_TIMER, 200

	call VolcanionCave_3F_EventScript_RockSlideSpawnRocks
	call VolcanionCave_3F_EventScript_RockSlideDropRocks
	@ fall through
VolcanionCave_3F_EventScript_RockSlideAfterMovement::
	call VolcanionCave_3F_EventScript_RockSlideRemoveRocks

	goto_if_eq VAR_GOLEM_ROCK_SLIDE_STATE, 3, VolcanionCave_3F_EventScript_RockSlideHitVolcanion
	goto_if_eq VAR_GOLEM_ROCK_SLIDE_STATE, 2, VolcanionCave_3F_EventScript_RockSlideHitPlayer

	setvar VAR_GOLEM_ROCK_SLIDE_TIMER, 0

	goto VolcanionCave_3F_EventScript_RockSlide

VolcanionCave_3F_EventScript_RockSlideSpawnRocks::
	@ Shake screen
	setvar VAR_0x8004, 0  @ Vertical pan
	setvar VAR_0x8005, 3  @ Horizontal pan
	setvar VAR_0x8006, 10  @ Num shakes
	setvar VAR_0x8007, 4  @ Shake delay
	special ShakeScreen

	@ Spawn rocks
	getplayerxy VAR_0x8008, VAR_0x8009

	subvar VAR_0x8009, 5
	subvar VAR_0x8008, 1
	addobject LOCALID_3F_ROCK_SLIDE_1
	setobjectsubpriority LOCALID_3F_ROCK_SLIDE_1, MAP_VOLCANION_CAVE_3F, 200
	setobjectxyperm LOCALID_3F_ROCK_SLIDE_1, VAR_0x8008, VAR_0x8009
	setobjectxy LOCALID_3F_ROCK_SLIDE_1, VAR_0x8008, VAR_0x8009

	addvar VAR_0x8008, 1
	addobject LOCALID_3F_ROCK_SLIDE_2
	setobjectsubpriority LOCALID_3F_ROCK_SLIDE_2, MAP_VOLCANION_CAVE_3F, 200
	setobjectxyperm LOCALID_3F_ROCK_SLIDE_2, VAR_0x8008, VAR_0x8009
	setobjectxy LOCALID_3F_ROCK_SLIDE_2, VAR_0x8008, VAR_0x8009

	addvar VAR_0x8008, 1
	addobject LOCALID_3F_ROCK_SLIDE_3
	setobjectsubpriority LOCALID_3F_ROCK_SLIDE_3, MAP_VOLCANION_CAVE_3F, 200
	setobjectxyperm LOCALID_3F_ROCK_SLIDE_3, VAR_0x8008, VAR_0x8009
	setobjectxy LOCALID_3F_ROCK_SLIDE_3, VAR_0x8008, VAR_0x8009
	return

VolcanionCave_3F_EventScript_RockSlideDropRocks::
	applymovement LOCALID_3F_ROCK_SLIDE_1, VolcanionCave_3F_Movement_Rock1FallDown
	applymovement LOCALID_3F_ROCK_SLIDE_3, VolcanionCave_3F_Movement_Rock3FallDown
	applymovement LOCALID_3F_ROCK_SLIDE_2, VolcanionCave_3F_Movement_Rock2FallDown
	delay 30
	playse SE_FALL
	delay 20
	playse SE_M_ROCK_THROW
	delay 8
	playse SE_M_ROCK_THROW
	delay 8
	playse SE_M_ROCK_THROW
	waitmovement 0
	return

VolcanionCave_3F_EventScript_RockSlideRemoveRocks::
	setobjectxyperm LOCALID_3F_ROCK_SLIDE_1, 39, 34
	removeobject LOCALID_3F_ROCK_SLIDE_1
	setobjectxyperm LOCALID_3F_ROCK_SLIDE_3, 39, 36
	removeobject LOCALID_3F_ROCK_SLIDE_3
	setobjectxyperm LOCALID_3F_ROCK_SLIDE_2, 39, 33
	removeobject LOCALID_3F_ROCK_SLIDE_2
	return

VolcanionCave_3F_EventScript_MaybeICanUseThisAqua::
	message VolcanionCave_3F_Text_MaybeICanUseThisAqua
	return

VolcanionCave_3F_EventScript_MaybeICanUseThisMagma::
	message VolcanionCave_3F_Text_MaybeICanUseThisMagma
	return

VolcanionCave_3F_EventScript_GottaRunAqua::
	message VolcanionCave_3F_Text_GottaRunAqua
	return

VolcanionCave_3F_EventScript_GottaRunMagma::
	message VolcanionCave_3F_Text_GottaRunMagma
	return

VolcanionCave_3F_EventScript_SetMetatilesRockSlideBlockade::
	setmetatile 5, 25, METATILE_Cave_Rock_1, TRUE
	setmetatile 6, 26, METATILE_Cave_Rock_2, TRUE
	setmetatile 26, 24, METATILE_Cave_Rock_2, TRUE
	setmetatile 27, 25, METATILE_Cave_Rock_1, TRUE
	setmetatile 28, 26, METATILE_Cave_Rock_2, TRUE
	setmetatile 16, 33, METATILE_Cave_Rock_2, TRUE
	return

VolcanionCave_3F_EventScript_SetMetatilesNoRockSlideBlockade::
	setmetatile 5, 25, METATILE_Cave_FloorSmooth, FALSE
	setmetatile 6, 26, METATILE_Cave_FloorSmooth, FALSE
	setmetatile 26, 24, METATILE_Cave_FloorSmooth, FALSE
	setmetatile 27, 25, METATILE_Cave_FloorSmooth, FALSE
	setmetatile 28, 26, METATILE_Cave_FloorSmooth, FALSE
	setmetatile 16, 33, METATILE_Cave_FloorSmooth, FALSE
	return

VolcanionCave_3F_Movement_Rock1FallDown::
	delay_16
	delay_16
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	rock_smash_break
	step_end

VolcanionCave_3F_Movement_Rock3FallDown::
	delay_16
	delay_16
	delay_8
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	rock_smash_break
	step_end

VolcanionCave_3F_Movement_Rock2FallDown::
	delay_16
	delay_16
	delay_8
	delay_8
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	rock_smash_break
	step_end

VolcanionCave_3F_Movement_PlayerNoticeRockSlide::
	face_up
	emote_exclamation_mark
	step_end

VolcanionCave_3F_Movement_PlayerDodgeRockSlideLeftDown::
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	delay_8
	walk_fast_left
	jump_down
	delay_8
	face_up
	step_end

VolcanionCave_3F_Movement_PlayerDodgeRockSlideUp::
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	delay_16
	delay_8
	jump_up
	step_end

VolcanionCave_3F_Text_GolemCry::
	.string "{SPEAKER NAME_GOLEM COLOR_NORMAL}Buh nuh nt!\p$"

VolcanionCave_3F_Text_GolemSeemsAngry::
	.string "GOLEM seems angry!\p$"

VolcanionCave_3F_Text_GolemSeemsSatisfied::
	.string "GOLEM seems satisfied!\p$"

VolcanionCave_3F_Text_GolemUsedRockSlide::
	.string "GOLEM used ROCK SLIDE!{PAUSE 40}$"

VolcanionCave_3F_Text_MaybeICanUseThisAqua::
	.string "{SPEAKER NAME_PLAYER COLOR_AQUA}Hey, watch where you're dropping those!{PAUSE 50}$"

VolcanionCave_3F_Text_MaybeICanUseThisMagma::
	.string "{SPEAKER NAME_PLAYER COLOR_MAGMA}Goodness, somebody seems upset.{PAUSE 25}.{PAUSE 25}.$"

VolcanionCave_3F_Text_GottaRunAqua::
	.string "{SPEAKER NAME_PLAYER COLOR_AQUA}Uh oh!{PAUSE 40} Gotta run!$"

VolcanionCave_3F_Text_GottaRunMagma::
	.string "{SPEAKER NAME_PLAYER COLOR_MAGMA}Careful, you might end up hitting\n"
	.string "someone else with those!$"

VolcanionCave_3F_EventScript_RockSlideHitPlayer::
	setvar VAR_GOLEM_ROCK_SLIDE_STATE, 4
	applymovement LOCALID_PLAYER, VolcanionCave_3F_Movement_PlayerFlicker
	waitmovement 0
	fadedefaultbgm
	message VolcanionCave_3F_Text_YouGotHit
	waitmessage
	closemessage
	release
	end

VolcanionCave_3F_Movement_PlayerFlicker::
	set_invisible
	delay_8
	set_visible
	delay_8
	set_invisible
	delay_8
	set_visible
	delay_8
	set_invisible
	delay_8
	set_visible
	step_end

VolcanionCave_3F_Text_YouGotHit::
	.string "You got hit by a rock, ow!\p"
	.string "GOLEM seems to be satisfied\n"
	.string "and stopped using ROCK SLIDE.\p"
	.string "For now…\p$"

VolcanionCave_3F_EventScript_RockSlideHitVolcanion::
	call VolcanionCave_3F_EventScript_SetMetatilesNoRockSlideBlockade
	special DrawWholeMapView
	setflag FLAG_ROCK_SLIDE_HIT_VOLCANION
	setvar VAR_GOLEM_ROCK_SLIDE_STATE, 0
	applymovement LOCALID_3F_VOLCANION, VolcanionCave_3F_Movement_VolcanionFlicker
	applymovement VAR_LOCALID_CURRENT_HP_BAR, VolcanionCave_3F_Movement_VolcanionFlicker
	waitmovement 0
	addvar VAR_CURRENT_HP_BAR_COLOR, 1
	applymovement LOCALID_3F_VOLCANION, VolcanionCave_3F_Movement_VolcanionSetVisible
	call VolcanionCave_3F_EventScript_SetHPBar
	lock
	message VolcanionCave_3F_Text_VolcanionGotHit
	waitmessage
	fadedefaultbgm
	call VolcanionCave_3F_EventScript_VolcanionCry
	closemessage
	delay 10
	message VolcanionCave_3F_Text_GolemSeemsFullySatisfied
	waitmessage
	closemessage
	release
	end

VolcanionCave_3F_Movement_VolcanionFlicker::
	set_invisible
	delay_8
	set_visible
	delay_8
	set_invisible
	delay_8
	set_visible
	delay_8
	set_invisible
	delay_8
	step_end

VolcanionCave_3F_Movement_VolcanionSetVisible::
	set_visible
	step_end

VolcanionCave_3F_Text_VolcanionGotHit::
	.string "VOLCANION was hit by the ROCK SLIDE!\n"
	.string "It's SUPER EFFECTIVE!\p$"

VolcanionCave_3F_Text_GolemSeemsFullySatisfied::
	.string "GOLEM seems to be satisfied\n"
	.string "and stopped using ROCK SLIDE.\p$"

VolcanionCave_3F_EventScript_GolemSatisfied::
	lock
	playmoncry SPECIES_GOLEM_ALOLA, CRY_MODE_ENCOUNTER
	message VolcanionCave_3F_Text_GolemCry
	waitmessage
	closemessage
	delay 10
	message VolcanionCave_3F_Text_GolemSeemsSatisfied
	waitmessage
	closemessage
	release
	end

VolcanionCave_3F_EventScript_Hole1A::
	jumphole VolcanionCave_3F_Movement_Hole1AToB, VolcanionCave_3F_Movement_ExitHoleNorth

VolcanionCave_3F_EventScript_Hole1B::
	jumphole VolcanionCave_3F_Movement_Hole1BToA, VolcanionCave_3F_Movement_ExitHoleSouth

VolcanionCave_3F_Movement_Hole1AToB::
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

VolcanionCave_3F_Movement_Hole1BToA::
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

VolcanionCave_3F_EventScript_Hole2A::
	jumphole VolcanionCave_3F_Movement_Hole2AToB, VolcanionCave_3F_Movement_ExitHoleSouth

VolcanionCave_3F_EventScript_Hole2B::
	jumphole VolcanionCave_3F_Movement_Hole2BToA, VolcanionCave_3F_Movement_ExitHoleNorth

VolcanionCave_3F_Movement_Hole2AToB::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

VolcanionCave_3F_Movement_Hole2BToA::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_3F_EventScript_Hole3A::
	jumphole VolcanionCave_3F_Movement_Hole3AToB, VolcanionCave_3F_Movement_ExitHoleWest

VolcanionCave_3F_EventScript_Hole3B::
	jumphole VolcanionCave_3F_Movement_Hole3BToA, VolcanionCave_3F_Movement_ExitHoleNorth

VolcanionCave_3F_Movement_Hole3AToB::
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_down
	step_end

VolcanionCave_3F_Movement_Hole3BToA::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	step_end

VolcanionCave_3F_EventScript_Hole4A::
	jumphole VolcanionCave_3F_Movement_Hole4AToB, VolcanionCave_3F_Movement_ExitHoleNorth

VolcanionCave_3F_EventScript_Hole4B::
	jumphole VolcanionCave_3F_Movement_Hole4BToA, VolcanionCave_3F_Movement_ExitHoleWest

VolcanionCave_3F_Movement_Hole4AToB::
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

VolcanionCave_3F_Movement_Hole4BToA::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

VolcanionCave_3F_EventScript_Hole5A::
	jumphole VolcanionCave_3F_Movement_Hole5AToB, VolcanionCave_3F_Movement_ExitHoleNorth

VolcanionCave_3F_EventScript_Hole5B::
	jumphole VolcanionCave_3F_Movement_Hole5BToA, VolcanionCave_3F_Movement_ExitHoleSouth

VolcanionCave_3F_Movement_Hole5AToB::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
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
	walk_fast_left
	step_end

VolcanionCave_3F_Movement_Hole5BToA::
	walk_fast_right
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
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_3F_EventScript_Hole6A::
	jumphole VolcanionCave_3F_Movement_Hole6AToB, VolcanionCave_3F_Movement_ExitHoleWest

VolcanionCave_3F_EventScript_Hole6B::
	jumphole VolcanionCave_3F_Movement_Hole6BToA, VolcanionCave_3F_Movement_ExitHoleNorth

VolcanionCave_3F_Movement_Hole6AToB::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	step_end

VolcanionCave_3F_Movement_Hole6BToA::
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_3F_EventScript_Hole7A::
	jumphole VolcanionCave_3F_Movement_Hole7AToB, VolcanionCave_3F_Movement_ExitHoleWest

VolcanionCave_3F_EventScript_Hole7B::
	jumphole VolcanionCave_3F_Movement_Hole7BToA, VolcanionCave_3F_Movement_ExitHoleSouth

VolcanionCave_3F_Movement_Hole7AToB::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
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
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_3F_Movement_Hole7BToA::
	walk_fast_down
	walk_fast_down
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
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

VolcanionCave_3F_EventScript_Hole8A::
	jumphole VolcanionCave_3F_Movement_Hole8AToB, VolcanionCave_3F_Movement_ExitHoleEast

VolcanionCave_3F_EventScript_Hole8B::
	jumphole VolcanionCave_3F_Movement_Hole8BToA, VolcanionCave_3F_Movement_ExitHoleSouth

VolcanionCave_3F_Movement_Hole8AToB::
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_3F_Movement_Hole8BToA::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	step_end

VolcanionCave_3F_EventScript_Hole9A::
	jumphole VolcanionCave_3F_Movement_Hole9AToB, VolcanionCave_3F_Movement_ExitHoleSouth

VolcanionCave_3F_EventScript_Hole9B::
	jumphole VolcanionCave_3F_Movement_Hole9BToA, VolcanionCave_3F_Movement_ExitHoleWest

VolcanionCave_3F_Movement_Hole9AToB::
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
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

VolcanionCave_3F_Movement_Hole9BToA::
	walk_fast_right
	walk_fast_right
	walk_fast_right
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
	step_end

VolcanionCave_3F_EventScript_Hole10A::
	jumphole VolcanionCave_3F_Movement_Hole10AToB, VolcanionCave_3F_Movement_ExitHoleSouth

VolcanionCave_3F_EventScript_Hole10B::
	jumphole VolcanionCave_3F_Movement_Hole10BToA, VolcanionCave_3F_Movement_ExitHoleNorth

VolcanionCave_3F_Movement_Hole10AToB::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	step_end

VolcanionCave_3F_Movement_Hole10BToA::
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

VolcanionCave_3F_EventScript_Hole11A::
	jumphole VolcanionCave_3F_Movement_Hole11AToB, VolcanionCave_3F_Movement_ExitHoleSouth

VolcanionCave_3F_EventScript_Hole11B::
	jumphole VolcanionCave_3F_Movement_Hole11BToA, VolcanionCave_3F_Movement_ExitHoleNorth

VolcanionCave_3F_Movement_Hole11AToB::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_left
	step_end

VolcanionCave_3F_Movement_Hole11BToA::
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_3F_EventScript_Hole12A::
	jumphole VolcanionCave_3F_Movement_Hole12AToB, VolcanionCave_3F_Movement_ExitHoleNorth

VolcanionCave_3F_EventScript_Hole12B::
	jumphole VolcanionCave_3F_Movement_Hole12BToA, VolcanionCave_3F_Movement_ExitHoleEast

VolcanionCave_3F_Movement_Hole12AToB::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	step_end

VolcanionCave_3F_Movement_Hole12BToA::
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_3F_EventScript_Hole13A::
	jumphole VolcanionCave_3F_Movement_Hole13AToB, VolcanionCave_3F_Movement_ExitHoleWest

VolcanionCave_3F_EventScript_Hole13B::
	jumphole VolcanionCave_3F_Movement_Hole13BToA, VolcanionCave_3F_Movement_ExitHoleSouth

VolcanionCave_3F_Movement_Hole13AToB::
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	step_end

VolcanionCave_3F_Movement_Hole13BToA::
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

VolcanionCave_3F_EventScript_Hole14A::
	jumphole VolcanionCave_3F_Movement_Hole14AToB, VolcanionCave_3F_Movement_ExitHoleEast

VolcanionCave_3F_EventScript_Hole14B::
	jumphole VolcanionCave_3F_Movement_Hole14BToA, VolcanionCave_3F_Movement_ExitHoleNorth

VolcanionCave_3F_Movement_Hole14AToB::
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

VolcanionCave_3F_Movement_Hole14BToA::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

VolcanionCave_3F_Movement_ExitHoleSouth::
	face_down
	set_visible
	jump_down
	step_end

VolcanionCave_3F_Movement_ExitHoleNorth::
	face_up
	set_visible
	jump_up
	step_end

VolcanionCave_3F_Movement_ExitHoleEast::
	face_right
	set_visible
	jump_right
	step_end

VolcanionCave_3F_Movement_ExitHoleWest::
	face_left
	set_visible
	jump_left
	step_end

VolcanionCave_3F_EventScript_Diglett::
	lock
	applymovement LOCALID_3F_DIGLETT, Common_Movement_FacePlayer
	waitmovement 0
	callnative IsPlayerOne
	goto_if_eq VAR_RESULT, FALSE, VolcanionCave_3F_EventScript_DiglettMagma
	goto VolcanionCave_3F_EventScript_DiglettAqua
	end

VolcanionCave_3F_EventScript_DiglettMagma::
	call VolcanionCave_3F_EventScript_DiglettCry
	message VolcanionCave_3F_Text_AskDiggsHelpMagma
	waitmessage
	call VolcanionCave_3F_EventScript_DiglettCry
	closemessage
	delay 10
	playbgm MUS_VS_VOLCANION, FALSE
	message VolcanionCave_3F_Text_DiglettUsedDig
	waitmessage
	call VolcanionCave_3F_EventScript_DiglettUseDig
	call VolcanionCave_3F_EventScript_DiglettCry
	message VolcanionCave_3F_Text_ThanksDiggsMagma
	waitmessage
	call VolcanionCave_3F_EventScript_VolcanionUseSteamEruption
	call VolcanionCave_3F_EventScript_CameraMoveToPlayerAfterSteamEruption
	message VolcanionCave_3F_Text_RipDiggsMagma
	waitmessage
	closemessage
	release
	end

VolcanionCave_3F_EventScript_DiglettAqua::
	call VolcanionCave_3F_EventScript_AgentDiggsCry
	message VolcanionCave_3F_Text_AskDiggsHelpAqua
	waitmessage
	call VolcanionCave_3F_EventScript_AgentDiggsCry
	closemessage
	delay 10
	playbgm MUS_VS_VOLCANION, FALSE
	message VolcanionCave_3F_Text_AgentDiggsUsedDig
	waitmessage
	call VolcanionCave_3F_EventScript_DiglettUseDig
	call VolcanionCave_3F_EventScript_AgentDiggsCry
	message VolcanionCave_3F_Text_ThanksDiggsAqua
	waitmessage
	call VolcanionCave_3F_EventScript_VolcanionUseSteamEruption
	call VolcanionCave_3F_EventScript_CameraMoveToPlayerAfterSteamEruption
	message VolcanionCave_3F_Text_RipDiggsAqua
	waitmessage
	closemessage
	release
	end

VolcanionCave_3F_EventScript_DiglettCry::
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	message VolcanionCave_3F_Text_DiglettCry
	waitmessage
	waitmoncry
	return

VolcanionCave_3F_EventScript_AgentDiggsCry::
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	message VolcanionCave_3F_Text_AgentDiggsCry
	waitmessage
	waitmoncry
	return

VolcanionCave_3F_EventScript_DiglettUseDig::
	special SpawnCameraObject
	applymovement LOCALID_3F_DIGLETT, VolcanionCave_3F_Movement_DiglettDigDown
	delay 10
	playse SE_M_DIG
	waitmovement 0
	waitse
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveWithDiglettToVolcanion
	applymovement LOCALID_3F_DIGLETT, VolcanionCave_3F_Movement_DiglettDigToVolcanion
	waitmovement 0
	setvar VAR_0x8004, 0  @ Vertical pan
	setvar VAR_0x8005, 3  @ Horizontal pan
	setvar VAR_0x8006, 3  @ Num shakes
	setvar VAR_0x8007, 4  @ Shake delay
	special ShakeScreen
	playse SE_M_DIZZY_PUNCH
	applymovement LOCALID_3F_VOLCANION, VolcanionCave_3F_Movement_VolcanionLookAround
	delay 40
	setvar VAR_0x8004, 0  @ Vertical pan
	setvar VAR_0x8005, 5  @ Horizontal pan
	setvar VAR_0x8006, 6  @ Num shakes
	setvar VAR_0x8007, 2  @ Shake delay
	special ShakeScreen
	delay 20
	waitmovement 0
	delay 20
	playse SE_M_DIG
	applymovement LOCALID_3F_DIGLETT, VolcanionCave_3F_Movement_DiglettAttackVolcanion
	applymovement LOCALID_3F_VOLCANION, VolcanionCave_3F_Movement_VolcanionGetAttackedByDiglett
	delay 16
	closemessage
	playse SE_SUPER_EFFECTIVE
	delay 16
	playse SE_M_DIG
	waitmovement 0
	applymovement LOCALID_3F_VOLCANION, VolcanionCave_3F_Movement_VolcanionFlicker
	applymovement VAR_LOCALID_CURRENT_HP_BAR, VolcanionCave_3F_Movement_VolcanionFlicker
	waitmovement 0
	addvar VAR_CURRENT_HP_BAR_COLOR, 1
	applymovement LOCALID_3F_VOLCANION, VolcanionCave_3F_Movement_VolcanionSetVisible
	call VolcanionCave_3F_EventScript_SetHPBar
	lock
	fadedefaultbgm
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveDownToDiglett
	applymovement LOCALID_3F_DIGLETT, VolcanionCave_3F_Movement_DiglettDigBackUp
	waitmovement 0
	applymovement LOCALID_3F_DIGLETT, Common_Movement_WalkInPlaceUp
	return

VolcanionCave_3F_EventScript_VolcanionUseSteamEruption::
	playbgm MUS_VS_VOLCANION, FALSE
	call VolcanionCave_3F_EventScript_VolcanionCry
	closemessage
	delay 10
	message VolcanionCave_3F_Text_VolcanionUsedSteamEruption
	waitmessage
	setvar VAR_0x8004, 0  @ Vertical pan
	setvar VAR_0x8005, 3  @ Horizontal pan
	setvar VAR_0x8006, 40  @ Num shakes
	setvar VAR_0x8007, 4  @ Shake delay
	special ShakeScreen
	delay 20
	playse SE_M_HYDRO_PUMP
	setmetatile 16, 22, METATILE_General_SteamEruption_EndFloor, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 22, METATILE_General_SteamEruption_EndFull, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 22, METATILE_General_SteamEruption_Connection, FALSE
	setmetatile 16, 23, METATILE_General_SteamEruption_EndStairs, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 22, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 23, METATILE_General_SteamEruption_EndFull, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 22, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 23, METATILE_General_SteamEruption_Connection, FALSE
	setmetatile 16, 24, METATILE_General_SteamEruption_EndFloor, FALSE
	special DrawWholeMapView
	applymovement LOCALID_3F_DIGLETT, VolcanionCave_3F_Movement_DiglettGetPushedBack
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_DiglettGetPushedBack
	delay 2
	setmetatile 16, 22, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 23, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 24, METATILE_General_SteamEruption_EndFull, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 22, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 23, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 24, METATILE_General_SteamEruption_Connection, FALSE
	setmetatile 16, 25, METATILE_General_SteamEruption_EndFloor, FALSE
	special DrawWholeMapView
	delay 100
	setmetatile 16, 22, METATILE_General_SteamEruption_BottomHalf, FALSE
	setmetatile 16, 23, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 24, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 25, METATILE_General_SteamEruption_EndTopHalf, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 22, METATILE_Cave_FloorSmooth, FALSE
	setmetatile 16, 23, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 24, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 25, METATILE_General_SteamEruption_TopHalf, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 23, METATILE_General_SteamEruption_BottomHalfStairs, FALSE
	setmetatile 16, 24, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 25, METATILE_General_SteamEruption_TopHalf, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 23, METATILE_Cave_Stairs, FALSE
	setmetatile 16, 24, METATILE_General_SteamEruption_Main, FALSE
	setmetatile 16, 25, METATILE_General_SteamEruption_TopHalf, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 24, METATILE_General_SteamEruption_BottomHalf, FALSE
	setmetatile 16, 25, METATILE_General_SteamEruption_TopHalf, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 24, METATILE_Cave_FloorSmooth, FALSE
	setmetatile 16, 25, METATILE_General_SteamEruption_TopHalf, FALSE
	special DrawWholeMapView
	delay 2
	setmetatile 16, 25, METATILE_Cave_FloorSmooth, FALSE
	special DrawWholeMapView
	closemessage
	playse SE_SUPER_EFFECTIVE
	applymovement LOCALID_3F_DIGLETT, VolcanionCave_3F_Movement_PlayerFlicker
	waitmovement 0
	delay 20
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	waitmoncry
	playse SE_FAINT
	removeobject LOCALID_3F_DIGLETT
	removeobject LOCALID_3F_DIGLETT_INVISIBLE
	setflag FLAG_HIDE_VOLCANION_CAVE_3F_DIGLETT
	setflag FLAG_AGENT_DIGGS_DIED
	fadedefaultbgm
	delay 20
	waitse
	return

VolcanionCave_3F_EventScript_CameraMoveToPlayerAfterSteamEruption::
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	delay 20
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveToPlayerAfterSteamEruption
	waitmovement 0
	special RemoveCameraObject
	return

VolcanionCave_3F_Movement_DiglettDigDown::
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_fast_left
	set_invisible
	step_end

VolcanionCave_3F_Movement_DiglettDigToVolcanion::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_down
	face_up
	step_end

VolcanionCave_3F_Movement_CameraMoveWithDiglettToVolcanion::
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

VolcanionCave_3F_Movement_VolcanionLookAround::
	emote_question_mark
	walk_in_place_left
	delay_16
	walk_in_place_right
	delay_16
	walk_in_place_down
	step_end

VolcanionCave_3F_Movement_DiglettAttackVolcanion::
	set_visible
	walk_fast_up
	delay_16
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	set_invisible

VolcanionCave_3F_Movement_VolcanionGetAttackedByDiglett::
	delay_8
	lock_facing_direction
	walk_up
	delay_16
	walk_fast_down
	unlock_facing_direction
	step_end

VolcanionCave_3F_Movement_CameraMoveDownToDiglett::
	walk_down
	walk_down
	step_end

VolcanionCave_3F_Movement_DiglettDigBackUp::
	walk_down
	walk_down
	walk_down
	face_up
	set_visible
	step_end

VolcanionCave_3F_Movement_DiglettGetPushedBack::
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

VolcanionCave_3F_Movement_CameraMoveToPlayerAfterSteamEruption::
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_3F_Text_DiglettCry::
	.string "{SPEAKER NAME_DIGLETT COLOR_AQUA}Pipipi wowow!\p$"

VolcanionCave_3F_Text_AgentDiggsCry::
	.string "{SPEAKER NAME_AGENT_DIGGS COLOR_AQUA}Pipipi wowow!\p$"

VolcanionCave_3F_Text_AskDiggsHelpMagma::
	.string "{SPEAKER NAME_PLAYER COLOR_MAGMA}You're AGENT DIGGS, I presume?\p"
	.string "I heard about you from {PLAYER_AQUA},\n"
	.string "it seems you have quite the resume\l"
	.string "for a DIGLETT.\p"
	.string "I hate to ask a member of TEAM AQUA\n"
	.string "for a favour, but as you can see we're\l"
	.string "in a bit of a pickle here.\p"
	.string "Would you mind helping us out?\p$"

VolcanionCave_3F_Text_AskDiggsHelpAqua::
	.string "{SPEAKER NAME_PLAYER COLOR_AQUA}AGENT DIGGS, great to see that you've\n"
	.string "joined us for the grand finale!\p"
	.string "Want to join in on the fun?\p"
	.string "Go teach VOLCANION a lesson in\n"
	.string "GROUND-TYPE attacks!!\p$"

VolcanionCave_3F_Text_DiglettUsedDig::
	.string "DIGLETT used DIG!$"

VolcanionCave_3F_Text_AgentDiggsUsedDig::
	.string "AGENT DIGGS used DIG!$"

VolcanionCave_3F_Text_ThanksDiggsMagma::
	.string "{SPEAKER NAME_PLAYER COLOR_MAGMA}Thank you, DIGGS.\p"
	.string "You've been very helpful-{PAUSE 10}$"

VolcanionCave_3F_Text_ThanksDiggsAqua::
	.string "{SPEAKER NAME_PLAYER COLOR_AQUA}Nice work, AGENT DIGGS!\p"
	.string "Looks like someone's getting promoted-{PAUSE 10}$"

VolcanionCave_3F_Text_VolcanionUsedSteamEruption::
	.string "VOLCANION used STEAM ERUPTION!$"

VolcanionCave_3F_Text_RipDiggsMagma::
	.string "{SPEAKER NAME_PLAYER COLOR_MAGMA}Of course this happens to the only\n"
	.string "member of TEAM AQUA I will ever respect.\p"
	.string "Alright VOLCANION, you asked for it!\n"
	.string "WE'RE TAKING YOU DOWN!!!\p$"

VolcanionCave_3F_Text_RipDiggsAqua::
	.string "{SPEAKER NAME_PLAYER COLOR_AQUA}AGENT DIGGS, NOOOOO!!!!\p"
	.string "VOLCANION, you… {PAUSE 10}you… {PAUSE 10}{FONT 5}sniff…\p"
	.string "{FONT_NORMAL}YOU'LL PAY FOR THIS!!!!!!\p$"

VolcanionCave_3F_EventScript_FloorSwitch1::
	lock
	goto_if_eq VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_1, 100, VolcanionCave_3F_EventScript_FloorSwitchAlreadyPressed
	setmetatile 21, 8, METATILE_Cave_Floor, FALSE
	playse SE_ICE_BREAK
	special DrawWholeMapView
	waitse
	setvar VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_1, 100
	releaseall
	end

VolcanionCave_3F_EventScript_FloorSwitch2::
	lock
	goto_if_eq VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_2, 100, VolcanionCave_3F_EventScript_FloorSwitchAlreadyPressed
	setmetatile 22, 9, METATILE_Cave_Floor, FALSE
	playse SE_ICE_BREAK
	special DrawWholeMapView
	waitse
	setvar VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_2, 100
	releaseall
	end

VolcanionCave_3F_EventScript_FloorSwitch3::
	lock
	goto_if_eq VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_3, 100, VolcanionCave_3F_EventScript_FloorSwitchAlreadyPressed
	setmetatile 23, 18, METATILE_Cave_Floor, FALSE
	playse SE_ICE_BREAK
	special DrawWholeMapView
	waitse
	setvar VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_3, 100
	releaseall
	end

VolcanionCave_3F_EventScript_FloorSwitch4::
	lock
	goto_if_eq VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_4, 100, VolcanionCave_3F_EventScript_FloorSwitchAlreadyPressed
	setmetatile 30, 32, METATILE_Cave_Floor, FALSE
	playse SE_ICE_BREAK
	special DrawWholeMapView
	waitse
	setvar VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_4, 100
	releaseall
	end

VolcanionCave_3F_EventScript_FloorSwitch5::
	lock
	goto_if_eq VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_5, 100, VolcanionCave_3F_EventScript_FloorSwitchAlreadyPressed
	setmetatile 26, 37, METATILE_Cave_Floor, FALSE
	playse SE_ICE_BREAK
	special DrawWholeMapView
	waitse
	setvar VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_5, 100
	releaseall
	end

VolcanionCave_3F_EventScript_FloorSwitch6::
	lock
	goto_if_eq VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_6, 100, VolcanionCave_3F_EventScript_FloorSwitchAlreadyPressed
	setmetatile 4, 32, METATILE_Cave_Floor, FALSE
	playse SE_ICE_BREAK
	special DrawWholeMapView
	waitse
	setvar VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_6, 100
	releaseall
	end

VolcanionCave_3F_EventScript_FloorSwitch7::
	lock
	goto_if_eq VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_7, 100, VolcanionCave_3F_EventScript_FloorSwitchAlreadyPressed
	setmetatile 5, 22, METATILE_Cave_FloorSmooth, FALSE
	setmetatile 8, 21, METATILE_Cave_Floor, FALSE
	setmetatile 9, 21, METATILE_Cave_Floor, FALSE
	playse SE_ICE_BREAK
	special DrawWholeMapView
	waitse
	setvar VAR_VOLCANION_CAVE_3F_STRENGTH_BUTTON_7, 100
	releaseall
	end

VolcanionCave_3F_EventScript_FloorSwitchAlreadyPressed::
	release
	end

VolcanionCave_3F_EventScript_Cramorant::
	lock
	call VolcanionCave_3F_EventScript_CramorantCry
	delay 20
	goto_if_eq VAR_VOLCANION_CAVE_3F_PIKACHU_STATE, 100, VolcanionCave_3F_EventScript_CramorantStillLookingForFood
	message VolcanionCave_3F_Text_CramorantLookingForFood
	waitmessage
	closemessage
	release
	end

VolcanionCave_3F_EventScript_CramorantStillLookingForFood::
	message VolcanionCave_3F_Text_CramorantStillLookingForFood
	waitmessage
	closemessage
	release
	end

VolcanionCave_3F_EventScript_CramorantEatPikachu::
	lock
	setvar VAR_VOLCANION_CAVE_3F_PIKACHU_STATE, 100
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveToCramorant
	applymovement LOCALID_3F_CRAMORANT, Common_Movement_WalkInPlaceUp
	call VolcanionCave_3F_EventScript_CramorantCry

	@ Cramorant eat Pikachu
	applymovement LOCALID_3F_CRAMORANT, VolcanionCave_3F_Movement_CramorantEatPikachu
	waitmovement 0
	removeobject LOCALID_3F_PIKACHU
	removeobject LOCALID_3F_CRAMORANT
	setflag FLAG_HIDE_VOLCANION_CAVE_3F_PIKACHU
	setflag FLAG_HIDE_VOLCANION_CAVE_3F_CRAMORANT
	addobject LOCALID_3F_CRAMORANT_GORGING
	clearflag FLAG_HIDE_VOLCANION_CAVE_3F_CRAM_GORGING
	setobjectxyperm LOCALID_3F_CRAMORANT_GORGING, 23, 21
	setobjectxy LOCALID_3F_CRAMORANT_GORGING, 23, 20
	applymovement LOCALID_3F_CRAMORANT_GORGING, Common_Movement_WalkDown
	waitmovement 0
	call VolcanionCave_3F_EventScript_CramorantCry
	closemessage
	delay 20

	@ Pikachu attack Cramorant
	playbgm MUS_VS_VOLCANION, FALSE
	message VolcanionCave_3F_Text_PikachuUsedQuickAttack
	waitmessage
	delay 30
	applymovement LOCALID_3F_CRAMORANT_GORGING, VolcanionCave_3F_Movement_CramorantShake
	waitmovement 0
	playse SE_NOT_EFFECTIVE
	message VolcanionCave_3F_Text_ButItFailed
	waitmessage
	delay 60
	closemessage
	applymovement LOCALID_3F_CRAMORANT_GORGING, VolcanionCave_3F_Movement_CramorantLaunchPikachu
	waitmovement 0

	@ Launch Pikachu
	addobject LOCALID_3F_PIKACHU
	clearflag FLAG_HIDE_VOLCANION_CAVE_3F_PIKACHU
	setobjectxy LOCALID_3F_PIKACHU, 23, 21
	removeobject LOCALID_3F_CRAMORANT_GORGING
	setflag FLAG_HIDE_VOLCANION_CAVE_3F_CRAM_GORGING
	addobject LOCALID_3F_CRAMORANT_ICON
	clearflag FLAG_HIDE_VOLCANION_CAVE_3F_CRAM_ICON
	lock
	playse SE_FALL
	setobjectsubpriority LOCALID_3F_PIKACHU, MAP_VOLCANION_CAVE_3F, 200
	applymovement LOCALID_3F_PIKACHU, VolcanionCave_3F_Movement_PikachuFly
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraFollowPikachuFly
	delay 100

	@ Pikachu hit Volcanion
	removeobject LOCALID_3F_PIKACHU
	setflag FLAG_HIDE_VOLCANION_CAVE_3F_PIKACHU
	playse SE_M_THUNDERBOLT2
	applymovement LOCALID_3F_VOLCANION, VolcanionCave_3F_Movement_VolcanionShake
	waitmovement 0
	applymovement LOCALID_3F_VOLCANION, VolcanionCave_3F_Movement_VolcanionSetVisible
	call VolcanionCave_3F_EventScript_SetHPBar
	lock
	waitmovement 0
	delay 20

	@ Volcanion is confused (well, paralyzed)
	playse SE_M_DIZZY_PUNCH
	applymovement LOCALID_3F_VOLCANION, VolcanionCave_3F_Movement_VolcanionLookAround
	waitmovement 0
	delay 40
	call VolcanionCave_3F_EventScript_VolcanionCry
	closemessage

	@ Camera move back
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveBackToCramorant
	waitmovement 0
	delay 20

	@ Reset Cramorant
	fadedefaultbgm
	removeobject LOCALID_3F_CRAMORANT_ICON
	setflag FLAG_HIDE_VOLCANION_CAVE_3F_CRAM_ICON
	addobject LOCALID_3F_CRAMORANT
	clearflag FLAG_HIDE_VOLCANION_CAVE_3F_CRAMORANT
	applymovement LOCALID_3F_CRAMORANT, Common_Movement_FaceLeft
	call VolcanionCave_3F_EventScript_CramorantCry

	@ Reset Camera
	applymovement LOCALID_3F_CRAMORANT, Common_Movement_FaceDown
	applymovement LOCALID_CAMERA, VolcanionCave_3F_Movement_CameraMoveBackUpFromCramorant
	waitmovement 0
	special RemoveCameraObject
	release
	end

VolcanionCave_3F_EventScript_CramorantCry::
	playmoncry SPECIES_CRAMORANT, CRY_MODE_NORMAL
	message VolcanionCave_3F_Text_CramorantCry
	waitmessage
	waitmoncry
	closemessage
	return

VolcanionCave_3F_Movement_CameraMoveToCramorant::
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

VolcanionCave_3F_Movement_CramorantEatPikachu::
	walk_fast_up
	step_end

VolcanionCave_3F_Movement_CramorantShake::
	levitate
	walk_in_place_left
	stop_levitate
	step_end

VolcanionCave_3F_Movement_CramorantLaunchPikachu::
	lock_facing_direction
	walk_slow_right
	delay_16
	walk_fast_left
	unlock_facing_direction
	step_end

VolcanionCave_3F_Movement_PikachuFly::
	lock_facing_direction
	walk_diag_northwest
	walk_diag_northwest
	walk_diag_northwest
	walk_left
	walk_diag_southwest
	walk_diag_southwest
	walk_diag_southwest
	unlock_facing_direction
	step_end

VolcanionCave_3F_Movement_CameraFollowPikachuFly::
	delay_16
	delay_8
	walk_diag_northwest
	walk_diag_northwest
	walk_left
	walk_diag_southwest
	walk_diag_southwest
	unlock_facing_direction
	step_end

VolcanionCave_3F_Movement_VolcanionShake::
	levitate
	delay_16
	delay_16
	stop_levitate
	step_end

VolcanionCave_3F_Movement_CameraMoveBackToCramorant::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

VolcanionCave_3F_Movement_CameraMoveBackUpFromCramorant::
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VolcanionCave_3F_Text_CramorantCry::
	.string "{SPEAKER NAME_CRAMORANT COLOR_NORMAL}Wah wuh!\p$"

VolcanionCave_3F_Text_CramorantLookingForFood::
	.string "CRAMORANT seems to be looking\n"
	.string "for food in the water.\p"
	.string "It doesn't seem to realize that\n"
	.string "the puddle is completely empty.\p$"

VolcanionCave_3F_Text_CramorantStillLookingForFood::
	.string "CRAMORANT still seems to be looking\n"
	.string "for food in the water.\p"
	.string "It still doesn't seem to realize that\n"
	.string "the puddle is completely empty.\p$"

VolcanionCave_3F_Text_PikachuUsedQuickAttack::
	.string "PIKACHU used QUICK ATTACK!$"

VolcanionCave_3F_Text_ButItFailed::
	.string "But it failed!$"

VolcanionCave_3F_EventScript_Pikachu::
	lock
	goto_if_set FLAG_TEAM_ROCKET_KNOCKED_OUT_PIKACHU, VolcanionCave_3F_EventScript_PikachuStrengthBoulder
	faceplayer
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	message VolcanionCave_3F_Text_PikachuCry
	waitmessage
	waitmoncry
	release
	end

VolcanionCave_3F_Text_PikachuCry::
	.string "{SPEAKER NAME_PIKACHU COLOR_NORMAL}Piiawoh!\p$"

VolcanionCave_3F_EventScript_PikachuStrengthBoulder::
	lockall
	goto_if_set FLAG_SYS_USE_STRENGTH, VolcanionCave_3F_EventScript_AskResetPikachu
	checkfieldmove FIELD_MOVE_STRENGTH, TRUE
	goto_if_eq VAR_RESULT, PARTY_SIZE, VolcanionCave_3F_EventScript_CantStrength
	setfieldeffectargument 0, VAR_RESULT
	msgbox VolcanionCave_3F_Text_WantToStrength, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VolcanionCave_3F_EventScript_CancelStrength
	closemessage
	dofieldeffect FLDEFF_USE_STRENGTH
	waitstate
	goto VolcanionCave_3F_EventScript_ActivateStrength
	end

VolcanionCave_3F_EventScript_AskResetPikachu::
	message VolcanionCave_3F_Text_AskResetPikachu
	waitmessage
	yesnobox 20, 8, 1
	goto_if_eq VAR_RESULT, YES, VolcanionCave_3F_EventScript_ResetPikachu
	releaseall
	end

VolcanionCave_3F_EventScript_ResetPikachu::
	fadescreen FADE_TO_BLACK
	setobjectxyperm LOCALID_3F_PIKACHU, 27, 5
	setobjectxy LOCALID_3F_PIKACHU, 27, 5
	turnobject LOCALID_3F_PIKACHU, DIR_SOUTH
	callnative ResetPikachuStrenghBoulderPosition
	closemessage
	delay 20
	fadescreen FADE_FROM_BLACK
	msgbox VolcanionCave_3F_Text_PikachuMovedBack, MSGBOX_DEFAULT
	release
	end

VolcanionCave_3F_EventScript_CantStrength::
	msgbox VolcanionCave_3F_Text_CantStrength, MSGBOX_DEFAULT
	releaseall
	end

VolcanionCave_3F_EventScript_CancelStrength::
	closemessage
	releaseall
	end

VolcanionCave_3F_EventScript_ActivateStrength::
	setflag FLAG_SYS_USE_STRENGTH
	msgbox VolcanionCave_3F_Text_MonUsedStrength, MSGBOX_DEFAULT
	releaseall
	end

VolcanionCave_3F_Text_WantToStrength:
	.string "PIKACHU is out cold, but a POKéMON\n"
	.string "may be able to push it aside.\p"
	.string "Would you like to use STRENGTH?$"

VolcanionCave_3F_Text_MonUsedStrength:
	.string "{STR_VAR_1} used STRENGTH!\p"
	.string "{STR_VAR_1}'s STRENGTH made it\n"
	.string "possible to move PIKACHU around!$"

VolcanionCave_3F_Text_CantStrength:
	.string "PIKACHU is out cold, but a POKéMON\n"
	.string "may be able to push it aside.$"

VolcanionCave_3F_Text_AskResetPikachu:
	.string "STRENGTH made it possible to move\n"
	.string "PIKACHU around.\p"
	.string "Do you want to move PIKACHU back\n"
	.string "to it's original place?$"

VolcanionCave_3F_Text_PikachuMovedBack:
	.string "You moved PIKACHU back\n"
	.string "to it's original place!$"

VolcanionCave_3F_EventScript_Jessie::
	applymovement LOCALID_3F_JESSIE, Common_Movement_FacePlayer
	applymovement LOCALID_3F_JAMES, Common_Movement_FacePlayer
	applymovement LOCALID_3F_MEOWTH, Common_Movement_FacePlayer
	msgbox VolcanionCave_3F_Text_JessieBattleIntro, MSGBOX_DEFAULT
	goto VolcanionCave_3F_EventScript_BattleTeamRocket

VolcanionCave_3F_EventScript_James::
	applymovement LOCALID_3F_JESSIE, Common_Movement_FacePlayer
	applymovement LOCALID_3F_JAMES, Common_Movement_FacePlayer
	applymovement LOCALID_3F_MEOWTH, Common_Movement_FacePlayer
	msgbox VolcanionCave_3F_Text_JamesBattleIntro, MSGBOX_DEFAULT
	goto VolcanionCave_3F_EventScript_BattleTeamRocket

VolcanionCave_3F_EventScript_Meowth::
	applymovement LOCALID_3F_JESSIE, Common_Movement_FacePlayer
	applymovement LOCALID_3F_JAMES, Common_Movement_FacePlayer
	applymovement LOCALID_3F_MEOWTH, Common_Movement_FacePlayer
	msgbox VolcanionCave_3F_Text_MeowthBattleIntro, MSGBOX_DEFAULT
	goto VolcanionCave_3F_EventScript_BattleTeamRocket

VolcanionCave_3F_EventScript_TeamRocketMotto::
	lock
	setvar VAR_VOLCANION_CAVE_3F_TEAM_ROCKET_STATE, 1
	setflag FLAG_SPAWN_VOLCANION_CAVE_3F_TEAM_ROCKET
	playbgm MUS_ENCOUNTER_SUSPICIOUS, FALSE
	message VolcanionCave_3F_Text_RocketMottoStart
	delay 30
	playse SE_M_DIZZY_PUNCH
	applymovement LOCALID_PLAYER, Common_Movement_QuestionMark
	waitmessage
	playse SE_FALL
	addobject LOCALID_3F_JESSIE
	setobjectxyperm LOCALID_3F_JESSIE, 26, 4
	setobjectxy LOCALID_3F_JESSIE, 26, 0
	applymovement LOCALID_3F_JESSIE, VolcanionCave_3F_Movement_TeamRocketFallDown
	delay 30
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	playse SE_M_STRENGTH
	message VolcanionCave_3F_Text_RocketMottoJessieEnter
	waitmessage
	playse SE_FALL
	addobject LOCALID_3F_JAMES
	setobjectxyperm LOCALID_3F_JAMES, 27, 4
	setobjectxy LOCALID_3F_JAMES, 27, 0
	applymovement LOCALID_3F_JAMES, VolcanionCave_3F_Movement_TeamRocketFallDown
	waitmovement 0
	playse SE_M_STRENGTH
	message VolcanionCave_3F_Text_RocketMottoJamesEnter
	waitmessage
	playse SE_FALL
	clearflag FLAG_HIDE_VOLCANION_CAVE_3F_TEAM_ROCKET
	addobject LOCALID_3F_MEOWTH
	setobjectxyperm LOCALID_3F_MEOWTH, 28, 4
	setobjectxy LOCALID_3F_MEOWTH, 28, 0
	applymovement LOCALID_3F_MEOWTH, VolcanionCave_3F_Movement_TeamRocketFallDown
	waitmovement 0
	playse SE_M_STRENGTH
	message VolcanionCave_3F_Text_RocketMottoMeowthEnter
	waitmessage
	message VolcanionCave_3F_Text_RocketMottoRest
	waitmessage
	closemessage
VolcanionCave_3F_EventScript_BattleTeamRocket::
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_DUO_VC_3F, VolcanionCave_3F_Text_RocketDefeat
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, VolcanionCave_3F_EventScript_DefeatedTeamRocket
	message VolcanionCave_3F_Text_ThatsRight
	waitmessage
	closemessage
	release
	end

VolcanionCave_3F_EventScript_DefeatedTeamRocket::
	delay 20
	playse SE_M_EXPLOSION
	setvar VAR_0x8004, 0  @ Vertical pan
	setvar VAR_0x8005, 5  @ Horizontal pan
	setvar VAR_0x8006, 40  @ Num shakes
	setvar VAR_0x8007, 3  @ Shake delay
	special ShakeScreen
	message VolcanionCave_3F_Text_BlastingOffAgain
	getobjectfacingdirection LOCALID_3F_JESSIE, VAR_0x8008
	switch VAR_0x8008
	case_call DIR_NORTH, VolcanionCave_3F_EventScript_TeamRocketBlastOffFaceNorth
	case_call DIR_EAST, VolcanionCave_3F_EventScript_TeamRocketBlastOffFaceEast
	case_call DIR_SOUTH, VolcanionCave_3F_EventScript_TeamRocketBlastOffFaceSouth
	case_call DIR_WEST, VolcanionCave_3F_EventScript_TeamRocketBlastOffFaceWest
	delay 60
	closemessage
	playse SE_SUPER_EFFECTIVE
	applymovement LOCALID_3F_PIKACHU, VolcanionCave_3F_Movement_PikachuFlicker
	waitmovement 0
	waitmovement LOCALID_3F_JESSIE
	waitmovement LOCALID_3F_JAMES
	waitmovement LOCALID_3F_MEOWTH
	removeobject LOCALID_3F_JESSIE
	removeobject LOCALID_3F_JAMES
	removeobject LOCALID_3F_MEOWTH
	delay 10
	playse SE_FAINT
	msgbox VolcanionCave_3F_Text_PikachuFainted
	clearflag FLAG_SPAWN_VOLCANION_CAVE_3F_TEAM_ROCKET
	setflag FLAG_TEAM_ROCKET_KNOCKED_OUT_PIKACHU
	release
	end

VolcanionCave_3F_EventScript_TeamRocketBlastOffFaceNorth::
	applymovement LOCALID_3F_JESSIE, VolcanionCave_3F_Movement_TeamRocketBlastOffFaceNorth
	applymovement LOCALID_3F_JAMES, VolcanionCave_3F_Movement_TeamRocketBlastOffFaceNorth
	applymovement LOCALID_3F_MEOWTH, VolcanionCave_3F_Movement_TeamRocketBlastOffFaceNorth
	return

VolcanionCave_3F_EventScript_TeamRocketBlastOffFaceEast::
	applymovement LOCALID_3F_JESSIE, VolcanionCave_3F_Movement_TeamRocketBlastOffFaceEast
	applymovement LOCALID_3F_JAMES, VolcanionCave_3F_Movement_TeamRocketBlastOffFaceEast
	applymovement LOCALID_3F_MEOWTH, VolcanionCave_3F_Movement_TeamRocketBlastOffFaceEast
	return

VolcanionCave_3F_EventScript_TeamRocketBlastOffFaceSouth::
	applymovement LOCALID_3F_JESSIE, VolcanionCave_3F_Movement_TeamRocketBlastOffFaceSouth
	applymovement LOCALID_3F_JAMES, VolcanionCave_3F_Movement_TeamRocketBlastOffFaceSouth
	applymovement LOCALID_3F_MEOWTH, VolcanionCave_3F_Movement_TeamRocketBlastOffFaceSouth
	return

VolcanionCave_3F_EventScript_TeamRocketBlastOffFaceWest::
	applymovement LOCALID_3F_JESSIE, VolcanionCave_3F_Movement_TeamRocketBlastOffFaceWest
	applymovement LOCALID_3F_JAMES, VolcanionCave_3F_Movement_TeamRocketBlastOffFaceWest
	applymovement LOCALID_3F_MEOWTH, VolcanionCave_3F_Movement_TeamRocketBlastOffFaceWest
	return

VolcanionCave_3F_EventScript_SpawnTeamRocket::
	addobject LOCALID_3F_JESSIE
	setobjectxyperm LOCALID_3F_JESSIE, 26, 4
	addobject LOCALID_3F_JAMES
	setobjectxyperm LOCALID_3F_JAMES, 27, 4
	addobject LOCALID_3F_MEOWTH
	setobjectxyperm LOCALID_3F_MEOWTH, 28, 4
	return

VolcanionCave_3F_Movement_TeamRocketFallDown::
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	step_end

VolcanionCave_3F_Movement_TeamRocketBlastOffFaceNorth::
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	face_right
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	face_down
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	face_left
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	face_up
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	face_right
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	step_end

VolcanionCave_3F_Movement_TeamRocketBlastOffFaceEast::
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	face_down
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	face_left
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	face_up
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	face_right
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	face_down
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	step_end

VolcanionCave_3F_Movement_TeamRocketBlastOffFaceSouth::
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	face_left
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	face_up
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	face_right
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	face_down
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	face_left
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	step_end

VolcanionCave_3F_Movement_TeamRocketBlastOffFaceWest::
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	face_up
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	face_right
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	face_down
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	face_left
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	face_up
	lock_facing_direction
	walk_diag_northeast
	unlock_facing_direction
	step_end

VolcanionCave_3F_Movement_PikachuFlicker::
	set_invisible
	delay_8
	set_visible
	delay_8
	set_invisible
	delay_8
	set_visible
	delay_8
	set_invisible
	delay_8
	set_visible
	step_end

VolcanionCave_3F_Text_JessieBattleIntro::
	.string "{SPEAKER NAME_JESSIE COLOR_JESSIE}Prepare for trouble!$"

VolcanionCave_3F_Text_JamesBattleIntro::
	.string "{SPEAKER NAME_JAMES COLOR_JAMES}Prepare for trouble!$"

VolcanionCave_3F_Text_MeowthBattleIntro::
	.string "{SPEAKER NAME_MEOWTH COLOR_NORMAL}Prepare for trouble!$"

VolcanionCave_3F_Text_RocketMottoStart::
	.string "{SPEAKER NAME_QUESTION_MARKS COLOR_JESSIE}{FONT_TYPE 1}Prepare for trouble!\p"
	.string "{SPEAKER NAME_QUESTION_MARKS COLOR_JAMES}…we're in HOENN.\p"
	.string "{SPEAKER NAME_QUESTION_MARKS COLOR_JESSIE}…oh. {FONT_TYPE 0}Ahem…\p"
	.string "Prepare for trouble from the skies!\p"
	.string "{SPEAKER NAME_QUESTION_MARKS COLOR_JAMES}From beyond the stars,\n"
	.string "a nasty surprise!\p$"

VolcanionCave_3F_Text_RocketMottoJessieEnter::
	.string "{SPEAKER NAME_ROCKET COLOR_JESSIE}An evil as old as the galaxy…\p$"

VolcanionCave_3F_Text_RocketMottoJamesEnter::
	.string "{SPEAKER NAME_ROCKET COLOR_JAMES}…sent here to fulfill our destiny!\p$"

VolcanionCave_3F_Text_RocketMottoMeowthEnter::
	.string "{SPEAKER NAME_ROCKET_3 COLOR_NORMAL}Plus, there's me!\p$"

VolcanionCave_3F_Text_RocketMottoRest::
	.string "{SPEAKER NAME_ROCKET COLOR_JESSIE}To denounce the evils\n"
	.string "of truth and love!\p"
	.string "{SPEAKER NAME_ROCKET COLOR_JAMES}To extend our reach\n"
	.string "to the stars above!\p"
	.string "{SPEAKER NAME_JESSIE COLOR_JESSIE}Jessie!\p"
	.string "{SPEAKER NAME_JAMES COLOR_JAMES}And James!\p"
	.string "{SPEAKER NAME_MEOWTH COLOR_NORMAL}And Meowth are the names!\p"
	.string "{SPEAKER NAME_JESSIE COLOR_JESSIE}Anywhere there's peace\n"
	.string "in the universe…\p"
	.string "{SPEAKER NAME_JAMES COLOR_JAMES}…Team Rocket…\p"
	.string "{SPEAKER NAME_MEOWTH COLOR_NORMAL}…will be there…\p"
	.string "{SPEAKER NAME_ALL COLOR_NORMAL}…to make everything worse!\p$"

VolcanionCave_3F_Text_RocketDefeat::
	.string "That's not right…$"

VolcanionCave_3F_Text_ThatsRight::
	.string "{SPEAKER NAME_MEOWTH COLOR_NORMAL}That's right!\p$"

VolcanionCave_3F_Text_BlastingOffAgain::
	.string "{SPEAKER NAME_ALL COLOR_NORMAL}We're blasting off again!$"

VolcanionCave_3F_Text_PikachuFainted::
	.string "PIKACHU fainted!\p"
	.string "A POKéMON may be able\n"
	.string "to push it aside.$"

VolcanionCave_3F_EventScript_Credits::
	fadescreenspeed FADE_TO_BLACK, 8
	message VolcanionCave_3F_Text_Epilogue
	waitmessage
	closemessage
	setflag FLAG_DO_CREDITS_TITLE
	creditsmessage Credits_TagTeamTrials, Credits_Credits
	clearflag FLAG_DO_CREDITS_TITLE
	setflag FLAG_DOING_CREDITS
	setflag FLAG_HIDE_SURF_BLOBS
	clearflag FLAG_DEFEATED_VOLCANION_CAVE_2F_EXEGGUTOR
	clearflag FLAG_HIDE_VOLCANION_CAVE_2F_CORSOLA
	setflag FLAG_HIDE_VOLCANION_CAVE_3F_CRAMORANT
	clearflag FLAG_HIDE_VOLCANION_CAVE_3F_CRAM_GORGING
	clearflag FLAG_HIDE_VOLCANION_CAVE_3F_TEAM_ROCKET
	clearflag FLAG_SPAWN_VOLCANION_CAVE_3F_TEAM_ROCKET
	setvar VAR_CURRENT_HP_BAR_COLOR, 0
	setflag FLAG_HIDE_VOLCANION_CAVE_3F_SHELLY
	clearflag FLAG_HIDE_VOLCANION_CAVE_3F_DIGLETT
	clearflag FLAG_HIDE_VOLCANION_CAVE_3F_ZINNIA
	clearflag FLAG_HIDE_VOLCANION_CAVE_3F_WHISMUR
	clearflag FLAG_HIDE_VOLCANION_CAVE_3F_VOLCANION
	clearflag FLAG_HIDE_VOLCANION_CAVE_3F_PIKACHU
	warpcontinuescript MAP_VOLCANION_CAVE_1F, 19, 19, VolcanionCave_3F_EventScript_Credits2
	end

VolcanionCave_3F_EventScript_Credits2::
	hideplayer
	fadescreen FADE_FROM_BLACK
	creditsmessage Credits_TheCompetition, Credits_TARC
	creditsmessage Credits_TheTeam, Credits_Viperio, Credits_Word, Credits_Keeper
	fadescreen FADE_TO_BLACK
	warpcontinuescript MAP_VOLCANION_CAVE_1F, 8, 8, VolcanionCave_3F_EventScript_Credits3

VolcanionCave_3F_EventScript_Credits3::
	hideplayer
	fadescreen FADE_FROM_BLACK
	creditsmessage Credits_Programmer, Credits_Viperio
	creditsmessage Credits_GraphicDesigner, Credits_Viperio
	fadescreen FADE_TO_BLACK
	warpcontinuescript MAP_VOLCANION_CAVE_1F, 32, 15, VolcanionCave_3F_EventScript_Credits4

VolcanionCave_3F_EventScript_Credits4::
	hideplayer
	fadescreen FADE_FROM_BLACK
	creditsmessage Credits_MapDesigners, Credits_Viperio, Credits_Keeper
	creditsmessage Credits_PuzzleDesigners, Credits_Viperio, Credits_Keeper
	fadescreen FADE_TO_BLACK
	warpcontinuescript MAP_VOLCANION_CAVE_2F, 20, 66, VolcanionCave_3F_EventScript_Credits5

VolcanionCave_3F_EventScript_Credits5::
	hideplayer
	fadescreen FADE_FROM_BLACK
	creditsmessage Credits_ScriptDesigners, Credits_Viperio, Credits_Word
	creditsmessage Credits_MusicComposition, Credits_Word
	fadescreen FADE_TO_BLACK
	warpcontinuescript MAP_VOLCANION_CAVE_2F, 23, 45, VolcanionCave_3F_EventScript_Credits6

VolcanionCave_3F_EventScript_Credits6::
	hideplayer
	fadescreen FADE_FROM_BLACK
	creditsmessage Credits_DialogueWriter, Credits_Word
	creditsmessage Credits_PokedexText, Credits_Keeper
	fadescreen FADE_TO_BLACK
	warpcontinuescript MAP_VOLCANION_CAVE_2F, 15, 11, VolcanionCave_3F_EventScript_Credits7

VolcanionCave_3F_EventScript_Credits7::
	hideplayer
	fadescreen FADE_FROM_BLACK
	creditsmessage Credits_Playtesters, Credits_RyanGreenBlue, Credits_FlippyPlays, Credits_CoolOwen
	creditsmessage Credits_Trailer, Credits_RyanGreenBlue
	fadescreen FADE_TO_BLACK
	warpcontinuescript MAP_VOLCANION_CAVE_3F, 7, 34, VolcanionCave_3F_EventScript_Credits8

VolcanionCave_3F_EventScript_Credits8::
	hideplayer
	fadescreen FADE_FROM_BLACK
	creditsmessage Credits_MagmaGruntsBackPics, Credits_Necrolichmon
	creditsmessage Credits_MagmaGruntsOverworldSprites, Credits_Jicem
	fadescreen FADE_TO_BLACK
	warpcontinuescript MAP_VOLCANION_CAVE_3F, 26, 6, VolcanionCave_3F_EventScript_Credits9

VolcanionCave_3F_EventScript_Credits9::
	hideplayer
	fadescreen FADE_FROM_BLACK
	creditsmessage Credits_TeamRocketOverworldSprites, Credits_Kalari
	creditsmessage Credits_TitleScreenBackground, Credits_Journeys
	fadescreen FADE_TO_BLACK
	warpcontinuescript MAP_VOLCANION_CAVE_3F, 16, 21, VolcanionCave_3F_EventScript_Credits10

VolcanionCave_3F_EventScript_Credits10::
	hideplayer
	fadescreen FADE_FROM_BLACK
	creditsmessage Credits_IdeaGuy, Credits_Keeper
	creditsmessage Credits_DiggsVoice, Credits_CassandraLeeMorris
	fadescreen FADE_TO_BLACK
	warpcontinuescript MAP_VOLCANION_CAVE_OUTSIDE, 9, 10, VolcanionCave_3F_EventScript_Credits11

VolcanionCave_3F_EventScript_Credits11::
	hideplayer
	fadescreen FADE_FROM_BLACK
	creditsmessage Credits_Awesome, Credits_Shelly
	creditsmessage Credits_Loser, Credits_Viperio
	fadescreen FADE_TO_BLACK
	warpcontinuescript MAP_PETALBURG_CITY, 20, 8, VolcanionCave_3F_EventScript_Credits12

VolcanionCave_3F_EventScript_Credits12::
	hideplayer
	fadescreen FADE_FROM_BLACK
	creditsmessage Credits_SpecialThanks, Credits_Pret, Credits_Expansion, Credits_AquaHideout
	fadescreen FADE_TO_BLACK
	creditsmessage Credits_LegendOfDragoon, Credits_Sony
	warpcontinuescript MAP_VOLCANION_CAVE_3F, 57, 27, VolcanionCave_3F_EventScript_Credits13

VolcanionCave_3F_EventScript_Credits13::
	hideplayer
	fadescreen FADE_FROM_BLACK
	delay 50
	callnative BufferStardustCount
	goto_if_ge VAR_0x800A, 50, VolcanionCave_3F_EventScript_ThanksForPlayingStardust50
	goto_if_ge VAR_0x800A, 40, VolcanionCave_3F_EventScript_ThanksForPlayingStardust40
	goto_if_ge VAR_0x800A, 25, VolcanionCave_3F_EventScript_ThanksForPlayingStardust25
	goto_if_ge VAR_0x800A, 10, VolcanionCave_3F_EventScript_ThanksForPlayingStardust10
	goto VolcanionCave_3F_EventScript_ThanksForPlayingStardust0

VolcanionCave_3F_EventScript_ThanksForPlayingStardust0::
	msgbox Credits_ThanksForPlayingStardust0
	release
	end

VolcanionCave_3F_EventScript_ThanksForPlayingStardust10::
	msgbox Credits_ThanksForPlayingStardust10
	release
	end

VolcanionCave_3F_EventScript_ThanksForPlayingStardust25::
	msgbox Credits_ThanksForPlayingStardust25
	release
	end

VolcanionCave_3F_EventScript_ThanksForPlayingStardust40::
	msgbox Credits_ThanksForPlayingStardust40
	release
	end

VolcanionCave_3F_EventScript_ThanksForPlayingStardust50::
	msgbox Credits_ThanksForPlayingStardust50
	release
	end

Credits_TagTeamTrials::
	.string "POKéMON TAG TEAM TRIALS$"

Credits_Credits::
	.string "Credits$"

Credits_TheCompetition::
	.string "The Competition$"

Credits_TARC::
	.string "Team Aqua Romhacking Competition 3$"

Credits_TheTeam::
	.string "The Team$"

Credits_Viperio::
	.string "Viperio$"

Credits_Word::
	.string "WordOfTheDayIsYay$"

Credits_Keeper::
	.string "Keeper$"

Credits_Programmer::
	.string "Programmer$"

Credits_GraphicDesigner::
	.string "Graphic Designer$"

Credits_MapDesigners::
	.string "Map Designers$"

Credits_PuzzleDesigners::
	.string "Puzzle Designers$"

Credits_ScriptDesigners::
	.string "Script Designers$"

Credits_MusicComposition::
	.string "Music Composition$"

Credits_DialogueWriter::
	.string "Dialogue Writer$"

Credits_PokedexText::
	.string "Pokédex Text$"

Credits_Playtesters::
	.string "Playtesters$"

Credits_RyanGreenBlue::
	.string "RyanGreenBlue$"

Credits_FlippyPlays::
	.string "FlippyPlays$"

Credits_CoolOwen::
	.string "Cool Owen$"

Credits_Trailer::
	.string "Trailer$"

Credits_MagmaGruntsBackPics::
	.string "Magma Grunts Back Pics$"

Credits_Necrolichmon::
	.string "Necrolichmon (Deviantart)$"

Credits_MagmaGruntsOverworldSprites::
	.string "Magma Grunts Overworld Sprites$"

Credits_Jicem::
	.string "Jicem (Pokémon Mu Magma)$"

Credits_TeamRocketOverworldSprites::
	.string "Magma Grunts Overworld Sprites$"

Credits_Kalari::
	.string "Kalari (Pokecommunity)$"

Credits_TitleScreenBackground::
	.string "Title Screen Background$"

Credits_Journeys::
	.string "Pokémon Journeys: The Series$"

Credits_IdeaGuy::
	.string "“Idea Guy”$"

Credits_DiggsVoice::
	.string "Voice of Agent Diggs$"

Credits_CassandraLeeMorris::
	.string "Cassandra Lee Morris$"

Credits_Awesome::
	.string "Awesome$"

Credits_Shelly::
	.string "Shelly$"

Credits_Loser::
	.string "Told me to add Courtney$"

Credits_SpecialThanks::
	.string "Special Thanks$"

Credits_Pret::
	.string "pret$"

Credits_Expansion::
	.string "pokeemerald-expansion$"

Credits_AquaHideout::
	.string "Team Aqua's Hideout$"

Credits_LegendOfDragoon::
	.string "The Legend of Dragoon$"

Credits_Sony::
	.string "Sony Computer Entertainment$"

Credits_ThanksForPlayingStardust0::
	.string "{SPEAKER NAME_WORD COLOR_JESSIE}Thanks for playing!\p"
	.string "Fun fact!\p"
	.string "There are 50 pieces of STARDUST\n"
	.string "hidden throughout the game.\p"
	.string "You've found… {STR_VAR_1} of them!\p"
	.string "That's no good!\p"
	.string "Better replay the entire game and find\n"
	.string "them all so you can brag to us about\l"
	.string "how cool and amazing you are!\p"
	.string "That's all for POKéMON TAG TEAM TRIALS!\p"
	.string "Make sure to check out the other\n"
	.string "super cool TARC 3 entries!\p"
	.string "(unless they suck im writing this\n"
	.string "the day before the due date)\p"
	.string "Enjoy the VOLCANION room!\p"
	.string "And of course, stay alive.\n"
	.string "{PAUSE 80} - Viperio (2004-2027)$"

Credits_ThanksForPlayingStardust10::
	.string "{SPEAKER NAME_WORD COLOR_JESSIE}Thanks for playing!\p"
	.string "Fun fact!\p"
	.string "There are 50 pieces of STARDUST\n"
	.string "hidden throughout the game.\p"
	.string "You've found… {STR_VAR_1} of them!\p"
	.string "That's less than half of them!\p"
	.string "Try pressing the A button once per\n"
	.string "frame to have a higher chance of\l"
	.string "finding all of the STARDUST!\p"
	.string "That's all for POKéMON TAG TEAM TRIALS!\p"
	.string "Make sure to check out the other\n"
	.string "super cool TARC 3 entries!\p"
	.string "(unless they suck im writing this\n"
	.string "the day before the due date)\p"
	.string "Enjoy the VOLCANION room!\p"
	.string "And of course, stay alive.\n"
	.string "{PAUSE 80} - Viperio (2004-2027)$"

Credits_ThanksForPlayingStardust25::
	.string "{SPEAKER NAME_WORD COLOR_JESSIE}Thanks for playing!\p"
	.string "Fun fact!\p"
	.string "There are 50 pieces of STARDUST\n"
	.string "hidden throughout the game.\p"
	.string "You've found… {STR_VAR_1} of them!\p"
	.string "Hey, not too shabby!\n"
	.string "That's more than half of them!\p"
	.string "Viperio told me you find more STARDUST\n"
	.string "when you're subscribed to his YouTube\l"
	.string "channel, have you tried that?\p"
	.string "That's all for POKéMON TAG TEAM TRIALS!\p"
	.string "Make sure to check out the other\n"
	.string "super cool TARC 3 entries!\p"
	.string "(unless they suck im writing this\n"
	.string "the day before the due date)\p"
	.string "Enjoy the VOLCANION room!\p"
	.string "And of course, stay alive.\n"
	.string "{PAUSE 80} - Viperio (2004-2027)$"

Credits_ThanksForPlayingStardust40::
	.string "{SPEAKER NAME_WORD COLOR_JESSIE}Thanks for playing!\p"
	.string "Fun fact!\p"
	.string "There are 50 pieces of STARDUST\n"
	.string "hidden throughout the game.\p"
	.string "You've found… {STR_VAR_1} of them!\p"
	.string "Almost there!\p"
	.string "Have you tried spamming Word's DMs to\n"
	.string "ask where the ones you're missing are?\p"
	.string "That's all for POKéMON TAG TEAM TRIALS!\p"
	.string "Make sure to check out the other\n"
	.string "super cool TARC 3 entries!\p"
	.string "(unless they suck im writing this\n"
	.string "the day before the due date)\p"
	.string "Enjoy the VOLCANION room!\p"
	.string "And of course, stay alive.\n"
	.string "{PAUSE 80} - Viperio (2004-2027)$"

Credits_ThanksForPlayingStardust50::
	.string "{SPEAKER NAME_WORD COLOR_JESSIE}Thanks for playing!\p"
	.string "Fun fact!\p"
	.string "There are 50 pieces of STARDUST\n"
	.string "hidden throughout the game.\p"
	.string "You've found… {STR_VAR_1} of them!\p"
	.string "Wow! Congrats, NERD!!!\p"
	.string "That's all for POKéMON TAG TEAM TRIALS!\p"
	.string "Make sure to check out the other\n"
	.string "super cool TARC 3 entries!\p"
	.string "(unless they suck im writing this\n"
	.string "the day before the due date)\p"
	.string "Enjoy the VOLCANION room!\p"
	.string "And of course, stay alive.\n"
	.string "{PAUSE 80} - Viperio (2004-2027)$"

EventScript_VolcanionCave_3F_Dig::
	message VolcanionCave_3F_Text_AskDig
	waitmessage
	yesnobox 20, 8, 1
	goto_if_eq VAR_RESULT, YES, VolcanionCave_3F_EventScript_UseDig
	release
	end

VolcanionCave_3F_EventScript_UseDig::
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	message VolcanionCave_3F_Text_AgentDiggsUsedDig
	waitmoncry
	waitmessage
	playse SE_M_DIG
	warp MAP_VOLCANION_CAVE_3F, 16, 35
	waitstate
	end

VolcanionCave_3F_Text_AskDig::
	.string "AGENT DIGGS can use DIG to reset\n"
	.string "the players and STRENGTH boulders.\p"
	.string "Do you want AGENT DIGGS to use DIG?$"
