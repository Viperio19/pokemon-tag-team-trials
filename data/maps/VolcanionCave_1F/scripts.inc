VolcanionCave_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VolcanionCave_1F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, VolcanionCave_1F_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VolcanionCave_1F_OnFrame
	.byte 0

VolcanionCave_1F_OnTransition:
	callnative UpdateStrengthBoulderPositions
	call_if_set FLAG_VOLCANION_CAVE_1F_DIGLETT_LEFT_SPOT, VolcanionCave_1F_EventScript_UpdateMagmaMGruntAndDiglett
	end

VolcanionCave_1F_EventScript_UpdateMagmaMGruntAndDiglett::
	setobjectxyperm LOCALID_1F_DIGLETT, 34, 17
	turnobject LOCALID_1F_MAGMA_GRUNT_M, DIR_EAST
	return

VolcanionCave_1F_OnWarp:
	map_script_2 VAR_TEMP_1, 0, VolcanionCave_1F_EventScript_InitObjects
	.2byte 0

VolcanionCave_1F_EventScript_InitObjects::
	callnative TrySpawnPlayer2
	setvar VAR_TEMP_1, 1
	call_if_eq VAR_VOLCANION_CAVE_1F_STATE, 0, VolcanionCave_1F_EventScript_HidePlayers
	call_if_ne VAR_OLD_ROD_STATE, 1, VolcanionCave_1F_EventScript_RemoveOldRod
	call_if_eq VAR_OLD_ROD_STATE, 1, VolcanionCave_1F_EventScript_SetOldRodPosition
	end

VolcanionCave_1F_EventScript_RemoveOldRod::
	removeobject LOCALID_1F_OLD_ROD
	return

VolcanionCave_1F_EventScript_SetOldRodPosition::
	setobjectxyperm LOCALID_1F_OLD_ROD, VAR_OLD_ROD_X, VAR_OLD_ROD_Y
	addobject LOCALID_1F_OLD_ROD
	callnative SetOldRodBob
	return

VolcanionCave_1F_EventScript_HidePlayers::
	hideobjectat LOCALID_PLAYER_2, MAP_VOLCANION_CAVE_1F
	hideplayer
	return

VolcanionCave_1F_OnFrame:
	map_script_2 VAR_VOLCANION_CAVE_1F_STATE, 0, VolcanionCave_1F_EventScript_EnterCave
	map_script_2 VAR_OLD_ROD_STATE, 10, VolcanionCave_1F_EventScript_DropOldRod
	.2byte 0

VolcanionCave_1F_EventScript_EnterCave::
	lock
	setvar VAR_VOLCANION_CAVE_1F_STATE, 1
	callnative IsMultiplayer
	goto_if_eq VAR_RESULT, TRUE, VolcanionCave_1F_EventScript_EnterCaveMultiplayer
	applymovement LOCALID_PLAYER_2, VolcanionCave_1F_Movement_Player2EnterCave
	waitmovement 0
	applymovement LOCALID_PLAYER, VolcanionCave_1F_Movement_PlayerEnterCave
	waitmovement 0
	delay 30
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_PLAYER_2, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_PLAYER_2, Common_Movement_WalkInPlaceRight
	message VolcanionCave_1F_Text_IntroOhNo
	waitmovement 0
	waitmessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceLeft
	message VolcanionCave_1F_Text_IntroWeirdo
	waitmovement 0
	waitmessage
	applymovement LOCALID_PLAYER_2, Common_Movement_WalkInPlaceRight
	message VolcanionCave_1F_Text_IntroDontStare
	waitmessage
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceLeft
	message VolcanionCave_1F_Text_IntroLookTheSame
	waitmovement 0
	waitmessage
	applymovement LOCALID_PLAYER_2, Common_Movement_WalkInPlaceRight
	message VolcanionCave_1F_Text_IntroBeatPoochyena
	waitmovement 0
	waitmessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceLeft
	message VolcanionCave_1F_Text_IntroHowDoYouKnow
	waitmovement 0
	waitmessage
	applymovement LOCALID_PLAYER_2, Common_Movement_WalkInPlaceRight
	message VolcanionCave_1F_Text_IntroSmellLikeEggs
	waitmovement 0
	waitmessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceLeft
	message VolcanionCave_1F_Text_IntroJobToDo
	waitmovement 0
	waitmessage
	applymovement LOCALID_PLAYER_2, Common_Movement_WalkInPlaceRight
	message VolcanionCave_1F_Text_IntroTellMeTwice
	waitmovement 0
	waitmessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceLeft
	message VolcanionCave_1F_Text_IntroScrewsLoose
	waitmovement 0
	waitmessage
	callnative UpdatePlayer2Pos
	release
	end

VolcanionCave_1F_EventScript_EnterCaveMultiplayer::
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, VolcanionCave_1F_EventScript_Player1AquaEnter
	call_if_eq VAR_RESULT, FALSE, VolcanionCave_1F_EventScript_Player1MagmaEnter
	waitmovement 0
	@ goto EventScript_Player2_Connect
	release
	end

VolcanionCave_1F_EventScript_Player1AquaEnter::
	applymovement LOCALID_PLAYER, VolcanionCave_1F_Movement_Player2EnterCave
	return

VolcanionCave_1F_EventScript_Player1MagmaEnter::
	applymovement LOCALID_PLAYER, VolcanionCave_1F_Movement_PlayerEnterCave
	return

VolcanionCave_1F_Movement_Player2EnterCave::
	set_visible
	walk_up
	walk_left
	walk_up
	step_end

VolcanionCave_1F_Movement_PlayerEnterCave::
	set_visible
	walk_up
	walk_right
	walk_up
	step_end

VolcanionCave_1F_Text_IntroOhNo::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Oh no…\p"
	.string "Of all of the people to run into\n"
	.string "on this job, it HAD to be you???\p$"

VolcanionCave_1F_Text_IntroWeirdo::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}(What is this TEAM AQUA\n"
	.string "weirdo yelling at me for?)\p$"

VolcanionCave_1F_Text_IntroDontStare::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Don't just stare at me like that!!\n"
	.string "…You do remember who I am, right?\p$"

VolcanionCave_1F_Text_IntroLookTheSame::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}I've seen hundreds of AQUA GRUNTS over\n"
	.string "the years and you all either look like\l"
	.string "pirates or pirates with orange hair.\p"
	.string "You'll have to forgive me for\n"
	.string "having zero clue who you are.\p$"

VolcanionCave_1F_Text_IntroBeatPoochyena::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}hrRrrRRNGH-YOU BEAT MY POOCHYENA ON\n"
	.string "TOP OF MT. CHIMNEY AND YOU KNOW IT!!\p$"

VolcanionCave_1F_Text_IntroHowDoYouKnow::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}How do you know that was me?\p$"

VolcanionCave_1F_Text_IntroSmellLikeEggs::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}YOU SMELL LIKE EGGS!!!!!\p$"

VolcanionCave_1F_Text_IntroJobToDo::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}{FONT 5}oh for the love of- {PAUSE 20}{FONT_NORMAL}Don't bring my\n"
	.string "sister's TOGEPI into this…\p"
	.string "Look, unlike you ARAQUA-NERDS,\n"
	.string "I have an important job to do.\p"
	.string "I'd appreciate it if you\n"
	.string "stayed out of my way.\p$"

VolcanionCave_1F_Text_IntroTellMeTwice::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Don't have to tell me twice!!\p$"

VolcanionCave_1F_Text_IntroScrewsLoose::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}{FONT 5}(Woah… I knew TEAM AQUA had a few\n"
	.string "screws loose, but {HESHE_1}'s way worse\l"
	.string "than I expected.)\p"
	.string "(Hmm… {HESHE_1} may not look very\n"
	.string "useful, but you never know…)\p"
	.string "(I'm sure {HESHE_1}'ll make for a\n"
	.string "decent meatshield in a pinch.){FONT_NORMAL}\p$"

VolcanionCave_1F_EventScript_DropOldRod::
	lock
	clearflag FLAG_DISABLE_OLD_ROD_BOB
    clearflag FLAG_HIDE_VOLCANION_CAVE_1F_OLD_ROD
    setflag FLAG_DROPPED_VOLCANION_CAVE_1F_OLD_ROD
	addobject LOCALID_1F_OLD_ROD
	callnative SetOldRodBob
	removeitem ITEM_OLD_ROD
	setvar VAR_OLD_ROD_STATE, 1
	delay 20
	msgbox VolcanionCave_1F_Text_DroppedRod
	closemessage
	release
	end

VolcanionCave_1F_Text_DroppedRod::
	.string "Dropped rod...$"

VolcanionCave_1F_EventScript_OldRod::
	lock
	removeobject VAR_LAST_TALKED
	giveitem ITEM_OLD_ROD
	clearflag FLAG_DROPPED_VOLCANION_CAVE_1F_OLD_ROD
	setflag FLAG_HIDE_VOLCANION_CAVE_1F_OLD_ROD
	setvar VAR_OLD_ROD_STATE, 0
	release
	end

VolcanionCave_1F_EventScript_MagmaGruntF::
	random 3
	goto_if_eq VAR_RESULT, 1, VolcanionCave_1F_EventScript_MagmaGruntFMsg1
	goto_if_eq VAR_RESULT, 2, VolcanionCave_1F_EventScript_MagmaGruntFMsg2
	msgbox VolcanionCave_1F_Text_HowDidIGetHere, MSGBOX_NPC
	end

VolcanionCave_1F_EventScript_MagmaGruntFMsg1::
	msgbox VolcanionCave_1F_Text_Help, MSGBOX_NPC
	end

VolcanionCave_1F_EventScript_MagmaGruntFMsg2::
	msgbox VolcanionCave_1F_Text_HELP, MSGBOX_NPC
	end

VolcanionCave_1F_Text_HowDidIGetHere::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}How did I get here…$"

VolcanionCave_1F_Text_Help::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}… … …\p"
	.string "Please help me.$"

VolcanionCave_1F_Text_HELP::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}HELP$"

VolcanionCave_1F_EventScript_MagmaGruntM::
	lock
	goto_if_set FLAG_VOLCANION_CAVE_1F_GRUNT_DROPPED_BADGE, VolcanionCave_1F_EventScript_MagmaGruntMDroppedBadge
	setflag FLAG_VOLCANION_CAVE_1F_GRUNT_DROPPED_BADGE
	setflag FLAG_VOLCANION_CAVE_1F_DIGLETT_LEFT_SPOT
	faceplayer
	message VolcanionCave_1F_Text_MagmaGruntMLoveDiglett
	waitmessage
	closemessage
	applymovement LOCALID_1F_MAGMA_GRUNT_M, Common_Movement_WalkInPlaceRight
	waitmovement 0
	message VolcanionCave_1F_Text_MagmaGruntMLookAtDiglett
	waitmessage
	closemessage
	playse SE_M_DIG
	applymovement LOCALID_1F_DIGLETT, VolcanionCave_1F_Movement_DiglettDigDown
	waitmovement 0
	playse SE_M_DIZZY_PUNCH
	applymovement LOCALID_1F_MAGMA_GRUNT_M, VolcanionCave_1F_Movement_MagmaGruntMConfused
	waitmovement 0
	delay 20
	playse SE_M_DIG
	applymovement LOCALID_1F_DIGLETT, VolcanionCave_1F_Movement_DiglettDigUp
	waitmovement 0
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	playse SE_PIN
	applymovement LOCALID_1F_MAGMA_GRUNT_M, VolcanionCave_1F_Movement_MagmaGruntMSurprised
	waitmovement 0
	delay 20
	setobjectxyperm LOCALID_1F_DIGLETT, 34, 17
	addobject LOCALID_1F_HEAT_BADGE
	setobjectxy LOCALID_1F_HEAT_BADGE, 33, 17
	clearflag FLAG_HIDE_VOLCANION_CAVE_1F_HEAT_BADGE
	applymovement LOCALID_1F_MAGMA_GRUNT_M, VolcanionCave_1F_Movement_MagmaGruntMWatchBadgeFallDown
	applymovement LOCALID_1F_HEAT_BADGE, VolcanionCave_1F_Movement_BadgeFallDown
	delay 16
	playse SE_PIN
	waitmovement 0
	delay 20
	msgbox VolcanionCave_1F_Text_MagmaGruntMDroppedBadge
	closemessage
	applymovement LOCALID_1F_MAGMA_GRUNT_M, Common_Movement_WalkInPlaceRight
	waitmovement 0
	release
	end

VolcanionCave_1F_EventScript_MagmaGruntMDroppedBadge::
	goto_if_set FLAG_HIDE_VOLCANION_CAVE_1F_HEAT_BADGE, VolcanionCave_1F_EventScript_MagmaGruntMBadgeStolen
	faceplayer
	msgbox VolcanionCave_1F_Text_MagmaGruntMCoolDiglett
	closemessage
	applymovement LOCALID_1F_MAGMA_GRUNT_M, Common_Movement_WalkInPlaceRight
	waitmovement 0
	release
	end

VolcanionCave_1F_EventScript_MagmaGruntMBadgeStolen::
	msgbox VolcanionCave_1F_Text_MagmaGruntMHideoutPassword
	faceplayer
	msgbox VolcanionCave_1F_Text_MagmaGruntMGetALoadOfDiglett
	closemessage
	waitse
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	applymovement LOCALID_1F_DIGLETT, VolcanionCave_1F_Movement_DiglettSurprised
	waitmoncry
	applymovement LOCALID_1F_MAGMA_GRUNT_M, Common_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox VolcanionCave_1F_Text_MagmaGruntMWoahThereDiglett
	closemessage
	applymovement LOCALID_1F_MAGMA_GRUNT_M, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VolcanionCave_1F_Movement_DiglettDigDown::
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_fast_left
	set_invisible
	walk_faster_left
	walk_faster_left
	face_left
	step_end

VolcanionCave_1F_Movement_DiglettDigUp::
	face_left
	set_visible
	walk_in_place_fast_left
	step_end

VolcanionCave_1F_Movement_MagmaGruntMConfused::
	emote_question_mark
	walk_in_place_left
	delay_16
	walk_in_place_down
	delay_16
	walk_in_place_right
	delay_16
	step_end

VolcanionCave_1F_Movement_MagmaGruntMSurprised::
	emote_exclamation_mark
	jump_in_place_right
	step_end

VolcanionCave_1F_Movement_MagmaGruntMWatchBadgeFallDown::
	delay_16
	emote_exclamation_mark
	walk_in_place_down
	step_end

VolcanionCave_1F_Movement_BadgeFallDown::
	set_visible
	slide_down
	jump_down
	jump_left
	jump_down
	step_end

VolcanionCave_1F_Movement_DiglettSurprised::
	emote_exclamation_mark
	step_end

VolcanionCave_1F_Text_MagmaGruntMLoveDiglett::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}I love DIGLETT.\p"
	.string "Their funny little bald heads\n"
	.string "always crack me up.\p$"

VolcanionCave_1F_Text_MagmaGruntMLookAtDiglett::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}I've been trying to get a closer look\n"
	.string "at this little guy for an hour now,\l"
	.string "but it doesn't seem like it's inter-{PAUSE 40}$"

VolcanionCave_1F_Text_MagmaGruntMDroppedBadge::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}Aw DIGLETTS!{PAUSE 20} That was my HEAT BADGE…\p"
	.string "And after COURTNEY went through the\n"
	.string "trouble of stealing BADGES from the\l"
	.string "POKéMON League so we could use HMs…\p"
	.string "I am in BIG trouble.$"

VolcanionCave_1F_Text_MagmaGruntMCoolDiglett::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}I guess on the bright side, being this\n"
	.string "close to a DIGLETT has been pretty rad.$"

VolcanionCave_1F_Text_MagmaGruntMHideoutPassword::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}…The PASSWORD to MAGMA HIDEOUT?\p"
	.string "Why would a DIGLETT want to know that?$"

VolcanionCave_1F_Text_MagmaGruntMGetALoadOfDiglett::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}Oh hey, get a load of this DIGLETT!!\p"
	.string "Little fella has been trying to\n"
	.string "get all sorts of confidential\l"
	.string "information out of me for a while.\p"
	.string "I'm pretty sure my little boy\n"
	.string "sent him to check up on me.\p"
	.string "I haven't been home much recently.\n"
	.string "He must be so worried about me…\p"
	.string "Don't worry TOMMY, I'll be home soon!$"

VolcanionCave_1F_Text_MagmaGruntMWoahThereDiglett::
	.string "{SPEAKER NAME_MAGMA COLOR_MAGMA}No, I don't know MAXIE's\n"
	.string "POKENAV number!$"

VolcanionCave_1F_EventScript_HeatBadge::
	removeobject VAR_LAST_TALKED
	msgbox VolcanionCave_1F_Text_ObtainedHeatBadge
	closemessage
	setflag FLAG_BADGE04_GET
	end

VolcanionCave_1F_Text_ObtainedHeatBadge::
	.string "{PLAYER} obtained the HEAT BADGE!$"

VolcanionCave_1F_EventScript_Diglett::
	lock
	faceplayer
	callnative IsPlayerOne
	goto_if_eq VAR_RESULT, FALSE, VolcanionCave_1F_EventScript_DiglettMagma
	goto VolcanionCave_1F_EventScript_DiglettAqua
	end

VolcanionCave_1F_EventScript_DiglettMagma::
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	msgbox VolcanionCave_1F_Text_DiglettCry, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	delay 20
	msgbox VolcanionCave_1F_Text_DiglettSecretAgent
	closemessage
	release
	end

VolcanionCave_1F_EventScript_DiglettAqua::
	playmoncry SPECIES_DIGLETT, CRY_MODE_NORMAL
	msgbox VolcanionCave_1F_Text_AgentDiggsCry, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	delay 20
	msgbox VolcanionCave_1F_Text_GoodWorkDiggs
	closemessage
	delay 20
	release
	end

VolcanionCave_1F_Text_DiglettCry::
	.string "{SPEAKER NAME_DIGLETT COLOR_AQUA}Pipipi wowow!$"

VolcanionCave_1F_Text_AgentDiggsCry::
	.string "{SPEAKER NAME_AGENT_DIGGS COLOR_AQUA}Pipipi wowow!$"

VolcanionCave_1F_Text_DiglettSecretAgent::
	.string "(The DIGLETT seems to be an\n"
	.string "agent working for TEAM AQUA.)\p"
	.string "(You decide not to ruin the MAGMA\n"
	.string "GRUNT'S day with this information.)$"

VolcanionCave_1F_Text_GoodWorkDiggs::
	.string "{SPEAKER NAME_PLAYER COLOR_AQUA}Keep up the good work, AGENT DIGGS!$"

VolcanionCave_1F_Movement_DiglettDigDown2::
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_in_place_fast_up
	set_invisible
	walk_faster_right
	walk_faster_right
	face_left
	step_end

VolcanionCave_1F_Movement_DiglettDigUp2::
	face_left
	set_visible
	walk_in_place_fast_left
	step_end

VolcanionCave_1F_EventScript_AquaGruntF::
	lock
	applymovement LOCALID_1F_AQUA_GRUNT_F, Common_Movement_FacePlayer
	waitmovement 0
	callnative IsPlayerOne
	goto_if_eq VAR_RESULT, FALSE, VolcanionCave_1F_EventScript_AquaGruntFMagmaPlayer
	goto_if_set FLAG_RECEIVED_REPEL, VolcanionCave_1F_EventScript_AquaGruntFSprayingRepels
VolcanionCave_1F_EventScript_AquaGruntFGiveRepel::
	msgbox VolcanionCave_1F_Text_AquaGruntFAquaPlayer, MSGBOX_DEFAULT
	closemessage
	delay 10
	giveitem ITEM_REPEL
	setflag FLAG_RECEIVED_REPEL
VolcanionCave_1F_EventScript_AquaGruntFSprayingRepels::
	msgbox VolcanionCave_1F_Text_AquaGruntFSprayingRepels, MSGBOX_NPC
	end

VolcanionCave_1F_EventScript_AquaGruntFMagmaPlayer::
	msgbox VolcanionCave_1F_Text_NoRepels, MSGBOX_NPC
	setvar VAR_STINKY_STEP_COUNT, 100
	end

VolcanionCave_1F_Text_AquaGruntFAquaPlayer::
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}Hey partner!\p"
	.string "I've been spraying repels so SHELLY\n"
	.string "doesn't have to deal with a ton of wild\l"
	.string "battles when she comes through here.\p"
	.string "There's a few POKéMON here that are\n"
	.string "stronger than our assigned CARVANHA,\l"
	.string "but not enough for it to be a problem.\p"
	.string "What IS a problem is how I'm\n"
	.string "supposed to get down from here.\p"
	.string "Oh well, I'm sure I'll find a way down.\p"
	.string "In the meantime, take this repel!\p"
	.string "You never know when you'll need one!$"

VolcanionCave_1F_Text_AquaGruntFSprayingRepels::
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}Although, I guess we do already have\n"
	.string "GRUNTS spraying the rest of the cave…\p"
	.string "Oh, who cares!\p"
	.string "Maybe you'll find a use, maybe not!$"

VolcanionCave_1F_Text_NoRepels::
	.string "{SPEAKER NAME_AQUA COLOR_AQUA}EWWWWW!!!{PAUSE 20} MAGMA!!!!!\p"
	.string "{SPEAKER NAME_NONE COLOR_NORMAL}(The GRUNT sprays you with a repel.)\p"
	.string "(You now smell like eggs and repel.)$"

VolcanionCave_1F_EventScript_RemoveLastTalked::
	removeobject VAR_LAST_TALKED
	return

VolcanionCave_1F_EventScript_Tirtouga::
	lock
	faceplayer
	playmoncry SPECIES_TIRTOUGA, CRY_MODE_ENCOUNTER
	msgbox VolcanionCave_1F_Text_TirtougaCry, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setwildbattle SPECIES_TIRTOUGA, 20
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	call_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, VolcanionCave_1F_EventScript_RemoveLastTalked
	release
	end

VolcanionCave_1F_Text_TirtougaCry::
	.string "{SPEAKER NAME_TIRTOUGA COLOR_NORMAL}Buh buh bwoay!$"

VolcanionCave_1F_EventScript_Cubone::
	lock
	faceplayer
	playmoncry SPECIES_CUBONE, CRY_MODE_ENCOUNTER
	msgbox VolcanionCave_1F_Text_CuboneCry, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setwildbattle SPECIES_CUBONE, 20
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	call_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, VolcanionCave_1F_EventScript_RemoveLastTalked
	release
	end

VolcanionCave_1F_Text_CuboneCry::
	.string "{SPEAKER NAME_CUBONE COLOR_NORMAL}Bawaay uh!$"

VolcanionCave_1F_EventScript_RockSmash::
	lockall
	checkfieldmove FIELD_MOVE_ROCK_SMASH, TRUE
	goto_if_eq VAR_RESULT, PARTY_SIZE, VolcanionCave_1F_EventScript_CantSmashRock
	setfieldeffectargument 0, VAR_RESULT
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	buffermovename STR_VAR_2, MOVE_ROCK_SMASH
	msgbox Text_WantToSmash, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VolcanionCave_1F_EventScript_CancelSmash
	msgbox Text_MonUsedFieldMove, MSGBOX_DEFAULT
	closemessage
VolcanionCave_1F_EventScript_RockSmashCommon:
	dofieldeffect FLDEFF_USE_ROCK_SMASH
	waitstate
VolcanionCave_1F_EventScript_SmashRock:: @ fallthrough
	applymovement VAR_LAST_TALKED, Movement_SmashRock
	waitmovement 0
	removeobject VAR_LAST_TALKED
	callnative RemovePlayer2RockSmashRock
	delay 10
	call_if_eq VAR_FACING, DIR_NORTH, VolcanionCave_1F_EventScript_PlayerWalkInPlaceNorth
	call_if_eq VAR_FACING, DIR_SOUTH, VolcanionCave_1F_EventScript_PlayerWalkInPlaceSouth
	call_if_eq VAR_FACING, DIR_EAST, VolcanionCave_1F_EventScript_PlayerWalkInPlaceEast
	call_if_eq VAR_FACING, DIR_WEST, VolcanionCave_1F_EventScript_PlayerWalkInPlaceWest
	msgbox VolcanionCave_1F_Text_RockIsGone, MSGBOX_DEFAULT
	releaseall
	end

VolcanionCave_1F_EventScript_CantSmashRock::
	msgbox Text_CantSmash, MSGBOX_DEFAULT
	releaseall
	end

VolcanionCave_1F_EventScript_CancelSmash::
	closemessage
	releaseall
	end

VolcanionCave_1F_EventScript_PlayerWalkInPlaceNorth::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceUp
	waitmovement 0
	return

VolcanionCave_1F_EventScript_PlayerWalkInPlaceSouth::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceDown
	waitmovement 0
	return

VolcanionCave_1F_EventScript_PlayerWalkInPlaceEast::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceRight
	waitmovement 0
	return

VolcanionCave_1F_EventScript_PlayerWalkInPlaceWest::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceLeft
	waitmovement 0
	return

VolcanionCave_1F_Text_RockIsGone::
	.string "{SPEAKER NAME_PLAYER COLOR_MAGMA}Hold on… {PAUSE 20}Was that really a good idea?\p"
	.string "Now anyone can get up here,\n"
	.string "even… {PAUSE 20}{FONT 5}blech… {PAUSE 20}{FONT_NORMAL}TEAM AQUA.\p"
	.string "Thing is, I need all the help I can get\n"
	.string "to move this GOLEM out of the way.\p"
	.string "Well, what's done is done.\p"
	.string "No matter how much I try,\n"
	.string "I can't just un-smash the rock.$"

VolcanionCave_1F_EventScript_Golem::
	lock
	faceplayer
	playmoncry SPECIES_GOLEM_ALOLA, CRY_MODE_ENCOUNTER
	message VolcanionCave_1F_Text_GolemCry
	waitmoncry
	waitmessage
	goto_if_set FLAG_PLAYER_2_READY_TO_BATTLE_TOGETHER, VolcanionCave_1F_EventScript_DoGolemMultiBattle
	goto_if_unset FLAG_HIDE_VOLCANION_CAVE_1F_BREAKABLE_ROCK, VolcanionCave_1F_EventScript_DoGolemSingleBattle
VolcanionCave_1F_EventScript_AskGolemMultiBattle::
	callnative IsPlayerOne
	goto_if_eq VAR_RESULT, FALSE, VolcanionCave_1F_EventScript_BattleTogetherMagma
	goto VolcanionCave_1F_EventScript_BattleTogetherAqua
	end

VolcanionCave_1F_EventScript_DoGolemSingleBattle::
	closemessage
	setwildbattle SPECIES_GOLEM_ALOLA, 35, TRUE
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, VolcanionCave_1F_EventScript_DefeatedGolem
	release
	end

VolcanionCave_1F_EventScript_DoGolemMultiBattle::
	closemessage
	clearflag FLAG_PLAYER_2_READY_TO_BATTLE_TOGETHER
	setwildbattle SPECIES_GOLEM_ALOLA, 35, TRUE
	multi_fixed_players_vs_wild PARTNER_PLAYER_2
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, VolcanionCave_1F_EventScript_DefeatedGolem
	release
	end

VolcanionCave_1F_EventScript_GetReadyForGolemMultiBattleMagma::
	msgbox VolcanionCave_1F_Text_BattleTogetherMagmaWell, MSGBOX_DEFAULT
	setflag FLAG_PLAYER_2_READY_TO_BATTLE_TOGETHER
	callnative SwitchCharacters
	waitstate
	release
	end

VolcanionCave_1F_EventScript_GetReadyForGolemMultiBattleAqua::
	msgbox VolcanionCave_1F_Text_BattleTogetherAquaFine, MSGBOX_DEFAULT
	setflag FLAG_PLAYER_2_READY_TO_BATTLE_TOGETHER
	callnative SwitchCharacters
	waitstate
	release
	end

VolcanionCave_1F_EventScript_DefeatedGolem::
	playmoncry SPECIES_GOLEM_ALOLA, CRY_MODE_NORMAL
	msgbox VolcanionCave_1F_Text_GolemCryDefeated, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	playse SE_M_ROCK_THROW
	removeobject LOCALID_1F_GOLEM
	addobject LOCALID_1F_GOLEM_BOULDER
	clearflag FLAG_HIDE_VOLCANION_CAVE_1F_GOLEM_BOULDER
	delay 20
	msgbox VolcanionCave_1F_Text_DidWeKillIt, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_VOLCANION_CAVE_1F_GOLEM
	release
	end

VolcanionCave_1F_EventScript_BattleTogetherMagma::
	msgbox VolcanionCave_1F_Text_BattleTogetherMagma, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, VolcanionCave_1F_EventScript_GetReadyForGolemMultiBattleMagma
	goto VolcanionCave_1F_EventScript_DoGolemSingleBattle
	end

VolcanionCave_1F_EventScript_BattleTogetherAqua::
	msgbox VolcanionCave_1F_Text_BattleTogetherAqua, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, VolcanionCave_1F_EventScript_GetReadyForGolemMultiBattleAqua
	goto VolcanionCave_1F_EventScript_DoGolemSingleBattle
	return

VolcanionCave_1F_Text_GolemCry::
	.string "{SPEAKER NAME_GOLEM COLOR_NORMAL}Buh nuh nt!\p$"

VolcanionCave_1F_Text_GolemCryDefeated::
	.string "{SPEAKER NAME_GOLEM COLOR_NORMAL}Buh…$"

VolcanionCave_1F_Text_BattleTogetherMagma::
	.string "{SPEAKER NAME_PLAYER COLOR_MAGMA}It's definitely too strong\n"
	.string "for me to handle on my own.\p"
	.string "The best tactic would be… {FONT 5}oh MANAPHY…\p"
	.string "{SPEAKER NAME_NONE COLOR_NORMAL}{FONT_NORMAL}Battle together with {RIVAL}?$"

VolcanionCave_1F_Text_BattleTogetherMagmaWell::
	.string "{SPEAKER NAME_PLAYER COLOR_MAGMA}Well, I guess we have to do this…$"
	.string "{SPEAKER NAME_NONE COLOR_NORMAL}{PLAYER} is ready to battle!$"

VolcanionCave_1F_Text_BattleTogetherAqua::
	.string "{SPEAKER NAME_PLAYER COLOR_AQUA}WOAH!! This guy is SUPER strong!\p"
	.string "I could probably take some of\n"
	.string "its attacks by myself, but…\p"
	.string "{SPEAKER NAME_NONE COLOR_NORMAL}Battle together with {RIVAL}?$"

VolcanionCave_1F_Text_BattleTogetherAquaFine::
	.string "{SPEAKER NAME_PLAYER COLOR_AQUA}Ugh… FINE, I'll battle it with you.$"
	.string "{SPEAKER NAME_NONE COLOR_NORMAL}{PLAYER} is ready to battle!$"
	
VolcanionCave_1F_Text_DidWeKillIt::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Is that it??{PAUSE 20} DID WE DO IT???\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Indoor voice please.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Ugh, you're no fun.\p"
	.string "We just beat the strongest\n"
	.string "POKéMON we've ever battled\l"
	.string "and THAT'S your reaction??\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}If THAT'S the strongest POKéMON\n"
	.string "you've ever battled, you should\l"
	.string "seriously reconsider being here.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Are all TEAM MAGMA GRUNTS as\n"
	.string "annoying as you????\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Yeah.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Look, as much as I really really REALLY\n"
	.string "don't want to say it, we needed to work\l"
	.string "together to take out that GOLEM.\p"
	.string "There's probably more POKéMON in here\n"
	.string "that are too strong for just one of us.\p"
	.string "What do you say to a truce for now?\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}As long as it's ONLY temporary.\p"
	.string "Any more than that, and the shame\n"
	.string "of working with you will kill me.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}{FONT 5}{AUTO_SCROLL 1}not if i kill you first{PAUSE 10}\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}{FONT_NORMAL}{AUTO_SCROLL 0}What???\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}What?\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}{FONT 5}Sigh… {FONT_NORMAL}We're getting nowhere with this.\n"
	.string "Let's go.$"
