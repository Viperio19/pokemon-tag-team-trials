EventScript_Player2_Singleplayer::
	lock
	goto_if_set FLAG_PLAYER_2_READY_TO_BATTLE_TOGETHER, EventScript_Player2_ReadyToBattle
	faceplayer
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, Player2Magma_Message_HiPlayer
	call_if_eq VAR_RESULT, FALSE, Player2Aqua_Message_HiPlayer
	waitmessage
	callnative UpdatePlayer2Pos
	goto_if_eq VAR_VOLCANION_CAVE_2F_STATE, 0, EventScript_Player2_MultiChoiceNoTrade
	multichoicedefault 21, 6, MULTI_PLAYER_2_TRADE, 0, FALSE
	switch VAR_RESULT
	case 0, Player2_Singleplayer_Talk
	case 1, Player2_Singleplayer_Trade
	case 2, Player2_Singleplayer_Cancel
	case MULTI_B_PRESSED, Player2_Singleplayer_Cancel
	release
	end

EventScript_Player2_MultiChoiceNoTrade::
	multichoicedefault 21, 8, MULTI_PLAYER_2, 0, FALSE
	switch VAR_RESULT
	case 0, Player2_Singleplayer_Talk
	case 1, Player2_Singleplayer_Cancel
	case MULTI_B_PRESSED, Player2_Singleplayer_Cancel
	release
	end

Player2_Singleplayer_Trade::
	@ choose player mon
	callnative IsPlayerOne
	copyvar VAR_0x8007, VAR_RESULT
	call_if_eq VAR_0x8007, TRUE, Player2Magma_Singleplayer_GiveWhatPokemon
	call_if_eq VAR_0x8007, FALSE, Player2Aqua_Singleplayer_GiveWhatPokemon
	special ChoosePartyMon
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_ge VAR_0x800A, PARTY_SIZE, Player2_Singleplayer_Cancel
	specialvar VAR_0x8008, GetTradeSpecies
	goto_if_eq VAR_0x8008, SPECIES_NUMEL, Player2_Singleplayer_CantTradePokemon
	goto_if_eq VAR_0x8008, SPECIES_CARVANHA, Player2_Singleplayer_CantTradePokemon

	@ choose partner mon
	callnative SwitchParties
	call_if_eq VAR_0x8007, TRUE, Player2Magma_Singleplayer_ReceiveWhatPokemon
	call_if_eq VAR_0x8007, FALSE, Player2Aqua_Singleplayer_ReceiveWhatPokemon
	special ChoosePartyMon
	copyvar VAR_0x800B, VAR_0x8004
	specialvar VAR_0x8009, GetTradeSpecies
	callnative SwitchParties
	goto_if_eq VAR_0x8009, SPECIES_NUMEL, Player2_Singleplayer_CantTradePokemon
	goto_if_eq VAR_0x8009, SPECIES_CARVANHA, Player2_Singleplayer_CantTradePokemon
	goto_if_ge VAR_0x800B, PARTY_SIZE, Player2_Singleplayer_Cancel

	@ confirm trade
	callnative BufferSinglePlayerTradeNicknames
	call_if_eq VAR_0x8007, TRUE, Player2Magma_Singleplayer_GivePokemonForPokemon
	call_if_eq VAR_0x8007, FALSE, Player2Aqua_Singleplayer_GivePokemonForPokemon
	switch VAR_RESULT
	case NO, Player2_Singleplayer_Cancel
	case YES, Player2_Singleplayer_DoTrade
	case MULTI_B_PRESSED, Player2_Singleplayer_Cancel
	release
	end

Player2Magma_Singleplayer_GiveWhatPokemon::
	msgbox Player2Magma_Text_GiveWhatPokemon, MSGBOX_DEFAULT
	return

Player2Aqua_Singleplayer_GiveWhatPokemon::
	msgbox Player2Aqua_Text_GiveWhatPokemon, MSGBOX_DEFAULT
	return

Player2Magma_Singleplayer_ReceiveWhatPokemon::
	msgbox Player2Magma_Text_ReceiveWhatPokemon, MSGBOX_DEFAULT
	return

Player2Aqua_Singleplayer_ReceiveWhatPokemon::
	msgbox Player2Aqua_Text_ReceiveWhatPokemon, MSGBOX_DEFAULT
	return

Player2Magma_Singleplayer_GivePokemonForPokemon::
	msgbox Player2Magma_Text_GivePokemonForPokemon, MSGBOX_YESNO
	return

Player2Aqua_Singleplayer_GivePokemonForPokemon::
	msgbox Player2Aqua_Text_GivePokemonForPokemon, MSGBOX_YESNO
	return

Player2_Singleplayer_CantTradePokemon::
	msgbox Player2_Text_CantTradeStarterPokemon, MSGBOX_DEFAULT
	release
	end

Player2_Singleplayer_DoTrade::
	special DoSinglePlayerTradeScene
	callnative BufferSinglePlayerTradeNicknames
	call_if_eq VAR_0x8007, TRUE, Player2Magma_Singleplayer_TakeGoodCareOfPokemon
	call_if_eq VAR_0x8007, FALSE, Player2Aqua_Singleplayer_TakeGoodCareOfPokemon
	release
	end

Player2Magma_Singleplayer_TakeGoodCareOfPokemon::
	msgbox Player2Magma_Text_TakeGoodCareOfPokemon, MSGBOX_DEFAULT
	return

Player2Aqua_Singleplayer_TakeGoodCareOfPokemon::
	msgbox Player2Aqua_Text_TakeGoodCareOfPokemon, MSGBOX_DEFAULT
	return

Player2_Singleplayer_Talk::
	goto_if_unset FLAG_HIDE_VOLCANION_CAVE_1F_BREAKABLE_ROCK, Player2_Message_Talk
	goto_if_unset FLAG_DEFEATED_VOLCANION_CAVE_1F_GOLEM, Player2_Message_PreGolem
	goto_if_eq VAR_VOLCANION_CAVE_2F_STATE, 0, Player2_Message_PreRoom2
	goto_if_eq VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_1, 0, Player2_Message_MudSliding
	goto_if_unset FLAG_DEFEATED_VOLCANION_CAVE_2F_EXEGGUTOR, Player2_Message_Exeggutor
	goto_if_eq VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_2, 0, Player2_Message_MagmaWall
	goto_if_eq VAR_VOLCANION_CAVE_2F_STRENGTH_BUTTON_4, 0, Player2_Message_Holes
	goto_if_eq VAR_VOLCANION_CAVE_3F_STATE, 0, Player2_Message_PreRoom3
	goto_if_ne VAR_CURRENT_HP_BAR_COLOR, 3, Player2_Message_Room3Main
	goto_if_ne VAR_VOLCANION_CAVE_3F_PIKACHU_STATE, 100, Player2_Message_Room3Main
	goto_if_ne VAR_ZINNIA_STATE, 1, Player2_Message_Room3Main
	msgbox Player2_Text_PreVolcanion, MSGBOX_NPC
	release
	end
	
Player2_Message_Talk::
	msgbox Player2_Text_Talk, MSGBOX_NPC
	release
	end

Player2_Text_Talk::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}This sucks!!!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Yes, I'm aware that TEAM AQUA is the\n"
	.string "objectively worse organization here.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Oh come on, you know that's\n"
	.string "not what I meant!\p"
	.string "There's this stupid rock in my way!!\p"
	.string "If only SHELLY had enough DYNAMO\n"
	.string "BADGES to give to all of us…\p"
	.string "Even then, I don't have a POKéMON\n"
	.string "that knows ROCK SMASH.\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Sounds to me like there's\n"
	.string "nothing you can do about that.\p"
	.string "Good luck, sucker!!$"

Player2_Message_PreGolem::
	msgbox Player2_Text_PreGolem, MSGBOX_NPC
	release
	end

Player2_Text_PreGolem::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}{FONT 5}hmmmm… mmgrmh… mrgrgr…\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}{FONT_NORMAL}Hey, quit mumbling!\p"
	.string "If you have another insult for me\n"
	.string "then just spit it out already!!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Shockingly, that isn't what I was\n"
	.string "planning this time.\p"
	.string "I'm simply thinking about my strategy\n"
	.string "to beat the GOLEM blocking the exit.\p"
	.string "{FONT 5}I have no problems when it uses\n"
	.string "THUNDERPUNCH, but I can't easily\l"
	.string "take an EARTHQUAKE.\p"
	.string "I wonder if there's a way to\n"
	.string "avoid both of its moves…\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}{FONT_NORMAL}Sweet! Thanks for the tips, loose lips!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Wait… I said that all out LOUD???$"

Player2_Message_PreRoom2::
	msgbox Player2_Text_PreRoom2, MSGBOX_NPC
	release
	end

Player2_Text_PreRoom2::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}You know, I could get used to\n"
	.string "this teamwork thing!\p"
	.string "But only if you were a TEAM AQUA GRUNT,\n"
	.string "of course.\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Go bother a TEAM AQUA GRUNT and\n"
	.string "leave me alone, then.$"

Player2_Message_MudSliding::
	msgbox Player2_Text_MudSliding, MSGBOX_NPC
	release
	end

Player2_Text_MudSliding::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Mud. My least favourite kind of dirt.\n"
	.string "It's so slippery and wet and gross!\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}We're in a cave. You're going to have\n"
	.string "to get used to the ground being wet.\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}This is ridiculous though!\p"
	.string "There's nothing to stop us from\n"
	.string "sliding until we're past the mud!\p"
	.string "{PLAYER_AQUA}. Do something about this.$"

Player2_Message_Exeggutor::
	msgbox Player2_Text_Exeggutor, MSGBOX_NPC
	release
	end

Player2_Text_Exeggutor::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Gee, it sure would be nice if there\n"
	.string "WASN'T AN EXEGGUTOR IN MY PATH!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}I believe this is called a skill issue.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}This is called a problem that\n"
	.string "YOU'RE going to deal with!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Good luck with that, I can't get past\n"
	.string "this other DISGUSTING MUD PIT with\l"
	.string "these stupid blue crystals in the way!\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Blue crystals, eh?\n"
	.string "{FONT 5}(Wasn't there a switch…?){FONT_NORMAL}$"

Player2_Message_MagmaWall::
	msgbox Player2_Text_MagmaWall, MSGBOX_NPC
	release
	end

Player2_Text_MagmaWall::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}The EXEGGUTOR is out of the way,\n"
	.string "but now I'm the one at a dead end.\p"
	.string "You can use STRENGTH, right {PLAYER_AQUA}?\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}It's one of my many… {FONT 5}hehe… {FONT_NORMAL}STRENGTHS!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Quit punning around, I asked because\n"
	.string "the wall in my way looks suspiciously\l"
	.string "like the one you removed the last time\l"
	.string "you pushed a boulder onto a switch.\p"
	.string "Go kick rocks, kid. Maybe you'll luck\n"
	.string "your way into clearing a path for me.$"

Player2_Message_Holes::
	msgbox Player2_Text_Holes, MSGBOX_NPC
	release
	end

Player2_Text_Holes::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}This… SERGEANT DUGS, you called him?\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}EXCUUUSE ME! His name is AGENT DIGGS\n"
	.string "and you will RESPECT his name!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Well whatever his name is, he made\n"
	.string "quite the mess of this place.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}I know right, isn't he just the best?\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}I fail to understand how me spraining\n"
	.string "my ankle every time I try to walk here\l"
	.string "is good… Ah yes, the whole “I hate you”\l"
	.string "thing, I understand completely now.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}You don't get the point at all!\p"
	.string "AGENT DIGGS dug those holes so we\n"
	.string "can reach the ledges that we can't\l"
	.string "get to on foot!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Hmm… maybe the little guy deserves\n"
	.string "some credit after all.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}He's the pride and joy of TEAM AQUA!!$"

Player2_Message_PreRoom3::
	msgbox Player2_Text_PreRoom3, MSGBOX_NPC
	release
	end

Player2_Text_PreRoom3::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Well this has been a day and a half…\p"
	.string "First I get put on this stupid mission,\n"
	.string "then this jerk shows up, and finally I\l"
	.string "lose my brand-old fishing rod!!\p"
	.string "Its not fair!!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Would you like your day to be worse?\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Not really…\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Hey, {PLAYER_AQUA}.\p"
	.string "Take a look at how far we've come\n"
	.string "in such a short amount of time.\p"
	.string "We're ahead of everyone else now,\n"
	.string "that's a huge accomplishment.\p"
	.string "From here on though, we're walking\n"
	.string "into uncharted territory.\p"
	.string "You feel that rumbling?\p"
	.string "Whatever is waiting in there won't be\n"
	.string "very happy to see us waltzing in.\p"
	.string "So chin up, we need you to focus on\n"
	.string "what we can accomplish right now.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Well look at you worrying about me,\n"
	.string "maybe there is actually something\l"
	.string "soft in that rocky heart of yours.\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}It's not nearly that deep.\p"
	.string "If you aren't there, then who will be\n"
	.string "my meatshield if things go wrong?\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Yep. {PAUSE 40}Figured.$"

Player2_Message_Room3Main::
	msgbox Player2_Text_Room3Main, MSGBOX_NPC
	release
	end

Player2_Text_Room3Main::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Wow, VOLCANION is SUPER STRONG!!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}It certainly lives up to the title of\n"
	.string "LEGENDARY POKéMON.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}But how do we catch it?\n"
	.string "We can barely even make a dent in it!!\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}If attacking it head on won't work,\n"
	.string "we go around and look for weak points.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}There are a lot of wild POKéMON around\n"
	.string "here, I wonder if any of them can help?\p"
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Well, why don't we find out?$"

Player2_Text_PreVolcanion::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}It seems like we've found everything\n"
	.string "we can find in this room.\p"
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}All that's left is beating VOLCANION up!\n"
	.string "LET'S DO THIS!!!$"

Player2_Singleplayer_Cancel::
	callnative IsPlayerOne
	call_if_eq VAR_RESULT, TRUE, Player2Magma_Singleplayer_Cancel
	call_if_eq VAR_RESULT, FALSE, Player2Aqua_Singleplayer_Cancel
	release
	end

Player2Aqua_Singleplayer_Cancel::
	msgbox Player2Aqua_Text_Cancel, MSGBOX_DEFAULT
	return

Player2Magma_Singleplayer_Cancel::
	msgbox Player2Magma_Text_Cancel, MSGBOX_DEFAULT
	return

Player2Magma_Message_HiPlayer::
	message Player2Magma_Text_HiPlayer
	return

Player2Aqua_Message_HiPlayer::
	message Player2Aqua_Text_HiPlayer
	return

Player2Magma_Text_HiPlayer::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}You again?\n"
	.string "What did I do to deserve this?$"

Player2Aqua_Text_HiPlayer::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}What, you need something?$"

Player2Aqua_Text_GiveWhatPokemon::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}What are you giving me?$"

Player2Magma_Text_GiveWhatPokemon::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}What POKéMON are you offering?$"

Player2Aqua_Text_ReceiveWhatPokemon::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Cool! I'll give you…$"

Player2Magma_Text_ReceiveWhatPokemon::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Alright, I'll trade for…$"

Player2Aqua_Text_GivePokemonForPokemon::
	.string "Trade {STR_VAR_1}\nfor {STR_VAR_2}?$"

Player2Magma_Text_GivePokemonForPokemon::
	.string "Trade {STR_VAR_1}\nfor {STR_VAR_2}?$"

Player2_Text_CantTradeStarterPokemon::
	.string "You can't trade a starter POKéMON.$"

Player2Aqua_Text_TakeGoodCareOfPokemon::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Thanks! I'll take care of {STR_VAR_2}!$"

Player2Magma_Text_TakeGoodCareOfPokemon::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}I'll take good care of {STR_VAR_2}.$"

Player2Aqua_Text_Cancel::
	.string "{SPEAKER NAME_PLAYER_AQUA COLOR_AQUA}Okie dokie!$"

Player2Magma_Text_Cancel::
	.string "{SPEAKER NAME_PLAYER_MAGMA COLOR_MAGMA}Alright, let's go.$"

EventScript_Player2_Connect::
	message gText_PleaseWaitForLink
	waitmessage
	special TryTradeLinkup
	goto_if_eq VAR_RESULT, LINKUP_SUCCESS, Player2_LinkSuccess
	goto_if_eq VAR_RESULT, LINKUP_SOMEONE_NOT_READY, Player2_AbortLinkTryAgain
	goto_if_eq VAR_RESULT, LINKUP_DIFF_SELECTIONS, Player2_AbortLinkTryAgain
	goto_if_eq VAR_RESULT, LINKUP_WRONG_NUM_PLAYERS, Player2_AbortLinkTryAgain
	goto_if_eq VAR_RESULT, LINKUP_FAILED, Player2_AbortLinkTryAgain
	goto_if_eq VAR_RESULT, LINKUP_CONNECTION_ERROR, Player2_AbortLinkTryAgain
	goto_if_eq VAR_RESULT, LINKUP_PLAYER_NOT_READY, Player2_AbortLinkTryAgain
	goto_if_eq VAR_RESULT, LINKUP_PARTNER_NOT_READY, Player2_AbortLinkTryAgain
	end

Player2_AbortLinkTryAgain::
	special CloseLink
	msgbox CableClub_Text_PleaseVisitAgain, MSGBOX_DEFAULT
	release
	end

Player2_LinkSuccess::
	callnative StoreLinkPlayerName
	setvar VAR_0x8004, USING_TRADE_CENTER
	copyvar VAR_CABLE_CLUB_STATE, VAR_0x8004
	callnative SetWarpCurrentPosition
	special DoCableClubWarp
	end

EventScript_Player2_Multiplayer::
	lock
	faceplayer
	callnative IsPlayerOne
	goto_if_eq VAR_RESULT, FALSE, Player2Magma_Text_HiPlayer
	message Player2Aqua_Text_HiPlayer
	waitmessage
	multichoicedefault 21, 6, MULTI_PLAYER_2, 0, FALSE
	switch VAR_RESULT
	case 0, Player2_Multiplayer_Trade
	case 1, Player2_Multiplayer_Talk
	case 2, Player2_Multiplayer_Cancel
	case MULTI_B_PRESSED, Player2_Multiplayer_Cancel
	release
	end

Player2_Multiplayer_Trade::
	setvar VAR_0x8005, 0
	special PlayerEnteredTradeSeat
	end

Player2_Multiplayer_Talk::
	msgbox Player2_Text_Talk, MSGBOX_NPC
	release
	end

Player2_Multiplayer_Cancel::
	msgbox Player2Aqua_Text_Cancel, MSGBOX_NPC
	release
	end

EventScript_Player2_ReadyToBattle::
	lock
	message Player2_Text_ReadyToBattle
	waitmessage
	yesnobox 20, 8, 1
	goto_if_eq VAR_RESULT, YES, EventScript_Player2_CancelBattleAndSwitch
	release
	end

EventScript_Player2_CancelBattleAndSwitch::
	clearflag FLAG_PLAYER_2_READY_TO_BATTLE_TOGETHER
	callnative SwitchCharacters
	waitstate
	release
	end

Player2_Text_ReadyToBattle::
	.string "{RIVAL} is ready to battle!\p"
	.string "Do you want to cancel the battle\n"
	.string "and switch anyways?$"
