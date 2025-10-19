BattleFrontier_BattlePalaceLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePalaceLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePalaceLobby_OnWarp
	.byte 0

BattleFrontier_BattlePalaceLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePalaceLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattlePalaceLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePalaceLobby_OnFrame:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattlePalaceLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePalaceLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePalaceLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattlePalaceLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattlePalaceLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattlePalaceLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattlePalaceLobby_EventScript_QuitWithoutSaving::
	lockall
	msgbox BattleFrontier_BattlePalaceLobby_Text_FailedToSaveBeforeEndingChallenge, MSGBOX_DEFAULT
	closemessage
	palace_set PALACE_DATA_WIN_STREAK, 0
	palace_set PALACE_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePalaceLobby_EventScript_DefeatedMaven
	msgbox BattleFrontier_BattlePalaceLobby_Text_FirmTrueBondsFor7WinStreak, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_GiveBattlePoints

BattleFrontier_BattlePalaceLobby_EventScript_DefeatedMaven::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ToDefeatMavenAnd7Trainers, MSGBOX_DEFAULT
BattleFrontier_BattlePalaceLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattlePalaceLobby_Text_PresentYouWithBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattlePalaceLobby_Text_FeatWillBeRecorded
	waitmessage
	call BattleFrontier_BattlePalaceLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_LostChallenge::
	lockall
	message BattleFrontier_BattlePalaceLobby_Text_ResultsWillBeRecorded
	waitmessage
	palace_set PALACE_DATA_WIN_STREAK_ACTIVE, FALSE
	call BattleFrontier_BattlePalaceLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_SaveAfterChallenge::
	frontier_checkairshow
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	palace_save 0
	playse SE_SAVE
	waitse
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePalaceLobby_EventScript_EndSaveAfterChallenge
	message BattleFrontier_BattlePalaceLobby_Text_LikeToRecordMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattlePalaceLobby_EventScript_EndSaveAfterChallenge
	case 0, BattleFrontier_BattlePalaceLobby_EventScript_RecordMatch
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_EndSaveAfterChallenge

BattleFrontier_BattlePalaceLobby_EventScript_RecordMatch::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattlePalaceLobby_EventScript_EndSaveAfterChallenge::
	return

BattleFrontier_BattlePalaceLobby_EventScript_ResumeChallenge::
	lockall
	msgbox BattleFrontier_BattlePalaceLobby_Text_WeHaveBeenWaiting, MSGBOX_DEFAULT
	message BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge
	waitmessage
	palace_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto BattleFrontier_BattlePalaceLobby_EventScript_EnterChallenge

BattleFrontier_BattlePalaceLobby_EventScript_SinglesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PALACE
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	goto BattleFrontier_BattlePalaceLobby_EventScript_Attendant
	end

BattleFrontier_BattlePalaceLobby_EventScript_DoublesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PALACE
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	goto BattleFrontier_BattlePalaceLobby_EventScript_Attendant
	end

BattleFrontier_BattlePalaceLobby_EventScript_Attendant::
	palace_get PALACE_DATA_PRIZE
	goto_if_ne VAR_RESULT, ITEM_NONE, BattleFrontier_BattlePalaceLobby_EventScript_WonChallenge
	special SavePlayerParty
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattlePalaceLobby_EventScript_WelcomeForSingleBattle
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_WelcomeForDoubleBattle
BattleFrontier_BattlePalaceLobby_EventScript_AskTakeChallenge::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattlePalaceLobby_EventScript_AskTakeSingleBattleChallenge
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_AskTakeDoubleBattleChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePalaceLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattlePalaceLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge

BattleFrontier_BattlePalaceLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattlePalaceLobby_Text_WhichChallenge
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattlePalaceLobby_Text_NowSelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePalaceLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge2, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePalaceLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattlePalaceLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattlePalaceLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	palace_init
	palace_set PALACE_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallengeSaveFailed
BattleFrontier_BattlePalaceLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattlePalaceLobby_Text_FollowMe, MSGBOX_DEFAULT
	closemessage
	call BattleFrontier_BattlePalaceLobby_EventScript_WalkToDoor
	warp MAP_BATTLE_FRONTIER_BATTLE_PALACE_CORRIDOR, 8, 13
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattlePalaceLobby_EventScript_ExplainChallenge::
	goto_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_ExplainDoublesChallenge
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainSingleBattleChallenge, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_AskTakeChallenge

BattleFrontier_BattlePalaceLobby_EventScript_ExplainDoublesChallenge::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainDoubleBattleChallenge, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_AskTakeChallenge

BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePalaceLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge

BattleFrontier_BattlePalaceLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
	callnative LoadPlayerParty
BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified, MSGBOX_DEFAULT
BattleFrontier_BattlePalaceLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattlePalaceLobby_EventScript_WelcomeForSingleBattle::
	msgbox BattleFrontier_BattlePalaceLobby_Text_WelcomeForSingleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePalaceLobby_EventScript_WelcomeForDoubleBattle::
	msgbox BattleFrontier_BattlePalaceLobby_Text_WelcomeForDoubleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePalaceLobby_EventScript_AskTakeSingleBattleChallenge::
	message BattleFrontier_BattlePalaceLobby_Text_TakeSingleBattleChallenge
	return

BattleFrontier_BattlePalaceLobby_EventScript_AskTakeDoubleBattleChallenge::
	message BattleFrontier_BattlePalaceLobby_Text_TakeDoubleBattleChallenge
	return

BattleFrontier_BattlePalaceLobby_EventScript_WalkToDoor::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattlePalaceLobby_EventScript_TalkedToSinglesAttendant
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_TalkedToDoublesAttendant
	applymovement VAR_LAST_TALKED, BattleFrontier_BattlePalaceLobby_Movement_WalkToDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePalaceLobby_Movement_WalkToDoor
	waitmovement 0
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattlePalaceLobby_EventScript_OpenSinglesHallDoor
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_OpenDoublesHallDoor
	waitdooranim
	applymovement VAR_LAST_TALKED, BattleFrontier_BattlePalaceLobby_Movement_AttendantEnterDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePalaceLobby_Movement_PlayerEnterDoor
	waitmovement 0
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattlePalaceLobby_EventScript_CloseSinglesHallDoor
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_CloseDoublesHallDoor
	waitdooranim
	return

BattleFrontier_BattlePalaceLobby_EventScript_TalkedToSinglesAttendant::
	setvar VAR_LAST_TALKED, LOCALID_PALACE_ATTENDANT_SINGLES
	return

BattleFrontier_BattlePalaceLobby_EventScript_TalkedToDoublesAttendant::
	setvar VAR_LAST_TALKED, LOCALID_PALACE_ATTENDANT_DOUBLES
	return

BattleFrontier_BattlePalaceLobby_EventScript_OpenSinglesHallDoor::
	opendoor 5, 4
	return

BattleFrontier_BattlePalaceLobby_EventScript_OpenDoublesHallDoor::
	opendoor 19, 4
	return

BattleFrontier_BattlePalaceLobby_EventScript_CloseSinglesHallDoor::
	closedoor 5, 4
	return

BattleFrontier_BattlePalaceLobby_EventScript_CloseDoublesHallDoor::
	closedoor 19, 4
	return

BattleFrontier_BattlePalaceLobby_Movement_WalkToDoor:
	walk_up
	step_end

BattleFrontier_BattlePalaceLobby_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePalaceLobby_Movement_PlayerEnterDoor:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePalaceLobby_EventScript_ShowSinglesResults::
	lockall
	frontier_results FRONTIER_FACILITY_PALACE, FRONTIER_MODE_SINGLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_ShowDoublesResults::
	lockall
	frontier_results FRONTIER_FACILITY_PALACE, FRONTIER_MODE_DOUBLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_BlackBelt::
	msgbox BattleFrontier_BattlePalaceLobby_Text_LadyCanTellWhatMonsThink, MSGBOX_NPC
	end

BattleFrontier_BattlePalaceLobby_EventScript_Man::
	msgbox BattleFrontier_BattlePalaceLobby_Text_NatureAndMovesKeyHere, MSGBOX_NPC
	end

BattleFrontier_BattlePalaceLobby_EventScript_Beauty::
	msgbox BattleFrontier_BattlePalaceLobby_Text_MonDocileButTransforms, MSGBOX_NPC
	end

BattleFrontier_BattlePalaceLobby_EventScript_Maniac::
	msgbox BattleFrontier_BattlePalaceLobby_Text_WhatNatureFavorsChippingAway, MSGBOX_NPC
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattlePalaceLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattlePalaceLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 16, 0, MULTI_BATTLE_PALACE_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePalaceLobby_EventScript_RulesBasics
	case 1, BattleFrontier_BattlePalaceLobby_EventScript_RulesNature
	case 2, BattleFrontier_BattlePalaceLobby_EventScript_RulesMoves
	case 3, BattleFrontier_BattlePalaceLobby_EventScript_RulesUnderpowered
	case 4, BattleFrontier_BattlePalaceLobby_EventScript_RulesWhenInDanger
	case 5, BattleFrontier_BattlePalaceLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_ExitRules
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesBasics::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesBasics, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesNature::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesNature, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesMoves::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesMoves, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesUnderpowered::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesUnderpowered, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesWhenInDanger::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesWhenInDanger, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePalaceLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattlePalaceLobby_Text_WelcomeForSingleBattle:
	.string "Tempat di mana hati para TRAINER\n"
	.string "diuji.\p"
	.string "Selamat datang di BATTLE PALACE.\p"
	.string "Aku menerima tantangan untuk\n"
	.string "SINGLE BATTLE HALLS.$"

BattleFrontier_BattlePalaceLobby_Text_TakeSingleBattleChallenge:
	.string "Apa kamu ingin mengambil tantangan\n"
	.string "SINGLE BATTLE HALL?$"

BattleFrontier_BattlePalaceLobby_Text_ExplainSingleBattleChallenge:
	.string "Di BATTLE PALACE, ada beberapa\n"
	.string "auditorium untuk SINGLE BATTLE yang\l"
	.string "disebut SINGLE BATTLE HALLS.\p"
	.string "SINGLE BATTLE dilakukan seperti biasa,\n"
	.string "kecuali satu aturan penting yang\l"
	.string "harus dipatuhi.\p"
	.string "TRAINER hanya diizinkan untuk\n"
	.string "menukar POKéMON mereka.\p"
	.string "Selain itu, TRAINER dilarang\n"
	.string "memerintah POKéMON mereka.\p"
	.string "POKéMON akan bertingkah sesuai\n"
	.string "sifatnya dan bertarung sendiri.\p"
	.string "Kamu harus menaruh kepercayaan pada\n"
	.string "POKéMON-mu dan mengawasinya.\p"
	.string "Jika kamu meraih kehormatan mengalahkan\n"
	.string "tujuh TRAINER berturut-turut,\l"
	.string "kami akan memberimu Battle Points.\p"
	.string "Jika kamu ingin menghentikan\n"
	.string "tantangan, kamu harus menyimpan.\p"
	.string "Jika tidak disimpan sebelum berhenti,\n"
	.string "kamu akan didiskualifikasi.$"

BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified:
	.string "Saat kamu sudah memperkuat hati dan\n"
	.string "POKéMON-mu, kamu harus kembali.$"

BattleFrontier_BattlePalaceLobby_Text_WhichChallenge:
	.string "Ada dua BATTLE HALL, Level 50 dan\n"
	.string "Level Terbuka.\l"
	.string "Mana tantangan pilihanmu?$"

BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLv50:
	.string "Hah…\p"
	.string "Kamu tidak punya tiga POKéMON\n"
	.string "yang dibutuhkan untuk tantangan ini.\p"
	.string "Untuk masuk, kamu harus menyediakan tiga\n"
	.string "jenis POKéMON yang berbeda.\p"
	.string "POKéMON ini harus semuanya\n"
	.string "Level 50 atau lebih rendah.\p"
	.string "Mereka juga tidak boleh memegang\n"
	.string "jenis item yang sama.\p"
	.string "TELUR{STR_VAR_1} tidak memenuhi syarat.\p"
	.string "Kembalilah saat persiapanmu\n"
	.string "sudah selesai.$"

BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLvOpen:
	.string "Hah…\p"
	.string "Kamu tidak punya tiga POKéMON\n"
	.string "yang dibutuhkan untuk tantangan ini.\p"
	.string "Untuk masuk, kamu harus menyediakan tiga\n"
	.string "jenis POKéMON yang berbeda.\p"
	.string "Mereka juga tidak boleh memegang\n"
	.string "jenis item yang sama.\p"
	.string "TELUR{STR_VAR_1} tidak memenuhi syarat.\p"
	.string "Kembalilah saat persiapanmu\n"
	.string "sudah selesai.$"

BattleFrontier_BattlePalaceLobby_Text_NowSelectThreeMons:
	.string "Bagus. Sekarang, kamu harus memilih\n"
	.string "tiga POKéMON-mu.$"

BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge2:
	.string "Aku harus menyimpan sebelum kupandu\n"
	.string "ke BATTLE HALL. Boleh?$"

BattleFrontier_BattlePalaceLobby_Text_FollowMe:
	.string "Bagus.\n"
	.string "Sekarang, ikuti aku.$"

BattleFrontier_BattlePalaceLobby_Text_ResultsWillBeRecorded:
	.string "Aku merasa terhormat telah melihat\n"
	.string "kemampuan POKéMON-mu.\p"
	.string "Hasilnya akan dicatat.\n"
	.string "Harap tunggu sebentar.$"

BattleFrontier_BattlePalaceLobby_Text_FirmTrueBondsFor7WinStreak:
	.string "Untuk meraih 7 kemenangan beruntun…\p"
	.string "Ikatan yang mengikat hatimu dengan\n"
	.string "POKéMON-mu terlihat kokoh dan tulus.$"

BattleFrontier_BattlePalaceLobby_Text_FeatWillBeRecorded:
	.string "Prestasimu akan dicatat.\n"
	.string "Harap tunggu sebentar.$"

BattleFrontier_BattlePalaceLobby_Text_BattlePointsFor7WinStreak:
	.string "Untuk prestasi 7 kemenangan beruntunmu,\n"
	.string "kami berikan Battle Point ini.$"

BattleFrontier_BattlePalaceLobby_Text_NoSpaceForPrize:
	.string "Sepertinya kamu tak punya ruang untuk\n"
	.string "hadiah kami.\p"
	.string "Kamu harus kembali setelah merapikan\n"
	.string "TAS-mu.$"

BattleFrontier_BattlePalaceLobby_Text_WeHaveBeenWaiting:
	.string "Kami telah menunggumu…$"

BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge:
	.string "Aku harus menyimpan sebelum kupandu\n"
	.string "ke BATTLE HALL. Boleh?$"

BattleFrontier_BattlePalaceLobby_Text_FailedToSaveBeforeEndingChallenge:
	.string "Hah…\p"
	.string "Kamu gagal menyimpan sebelum mengakhiri\n"
	.string "tantanganmu yang terakhir.\p"
	.string "Akibatnya, tantanganmu telah\n"
	.string "didiskualifikasi. Sungguh disayangkan.$"

BattleFrontier_BattlePalaceLobby_Text_ReceivedPrize:
	.string "{PLAYER} mendapatkan hadiah\n"
	.string "{STR_VAR_1}.$"

BattleFrontier_BattlePalaceLobby_Text_LadyCanTellWhatMonsThink:
	.string "Bagi orang sepertiku, POKéMON yang\n"
	.string "kuat adalah yang terbaik.\p"
	.string "Menyerang adalah pertahanan terbaik!\n"
	.string "Serangan tanpa henti itu pamungkas!\p"
	.string "Tapi bukan itu yang ingin kubicarakan.\p"
	.string "Kadang-kadang ada wanita manis yang\n"
	.string "datang ke sini.\p"
	.string "Dia bilang dia bisa tahu apa yang\n"
	.string "dipikirkan POKéMON.\p"
	.string "Aku tak tahu soal itu, tapi dia\n"
	.string "benar-benar manis.\p"
	.string "Hah?\n"
	.string "Kenapa kamu melihatku seperti itu?$"

BattleFrontier_BattlePalaceLobby_Text_NatureAndMovesKeyHere:
	.string "Hmm…\p"
	.string "Sepertinya sifat POKéMON dan jurus\n"
	.string "yang telah mereka pelajari adalah\l"
	.string "kunci pertarungan di sini.\p"
	.string "Lebih tepatnya, seberapa cocok jurus\n"
	.string "itu dengan sifat POKéMON.\p"
	.string "Jika POKéMON-mu dalam masalah dan\n"
	.string "tak bisa mengeluarkan potensinya,\l"
	.string "kamu mungkin perlu memeriksa kecocokan\l"
	.string "jurus dengan sifatnya.$"

BattleFrontier_BattlePalaceLobby_Text_MonDocileButTransforms:
	.string "POKéMON-ku biasanya sangat jinak.\p"
	.string "Tapi saat di BATTLE HALL, kadang ia\n"
	.string "seperti berubah menjadi sesuatu\l"
	.string "yang jahat!\p"
	.string "Ia jadi sangat mengintimidasi.\n"
	.string "Bahkan mengejutkan.$"

BattleFrontier_BattlePalaceLobby_Text_WhatNatureFavorsChippingAway:
	.string "Kira-kira sifat apa yang dimiliki\n"
	.string "POKéMON jika ia suka melemahkan\l"
	.string "lawan dan menyerang perlahan.\p"
	.string "Aku akan kaget jika itu sifat LAX.\p"
	.string "Tapi, ah, tidak mungkin.$"

BattleFrontier_BattlePalaceLobby_Text_WelcomeForDoubleBattle:
	.string "Tempat di mana hati para TRAINER\n"
	.string "diuji.\p"
	.string "Selamat datang di BATTLE PALACE.\p"
	.string "Aku menerima tantangan untuk\n"
	.string "DOUBLE BATTLE HALLS.$"

BattleFrontier_BattlePalaceLobby_Text_TakeDoubleBattleChallenge:
	.string "Apa kamu ingin mengambil tantangan\n"
	.string "DOUBLE BATTLE HALL?$"

BattleFrontier_BattlePalaceLobby_Text_ExplainDoubleBattleChallenge:
	.string "Di BATTLE PALACE, ada beberapa\n"
	.string "auditorium untuk DOUBLE BATTLE yang\l"
	.string "disebut DOUBLE BATTLE HALLS.\p"
	.string "DOUBLE BATTLE dilakukan seperti biasa,\n"
	.string "kecuali satu aturan penting yang\l"
	.string "harus dipatuhi.\p"
	.string "TRAINER hanya diizinkan untuk\n"
	.string "menukar POKéMON mereka.\p"
	.string "Selain itu, TRAINER dilarang\n"
	.string "memerintah POKéMON mereka.\p"
	.string "POKéMON akan bertingkah sesuai\n"
	.string "sifatnya dan bertarung sendiri.\p"
	.string "Kamu harus menaruh kepercayaan pada\n"
	.string "POKéMON-mu dan mengawasinya.\p"
	.string "Jika kamu meraih kehormatan mengalahkan\n"
	.string "tujuh TRAINER berturut-turut,\l"
	.string "kami akan memberimu Battle Points.\p"
	.string "Jika kamu ingin menghentikan\n"
	.string "tantangan, kamu harus menyimpan.\p"
	.string "Jika tidak disimpan sebelum berhenti,\n"
	.string "kamu akan didiskualifikasi.$"

BattleFrontier_BattlePalaceLobby_Text_ToDefeatMavenAnd7Trainers:
	.string "Mengalahkan PALACE MAVEN\n"
	.string "dan tujuh TRAINER berturut-turut…$"

BattleFrontier_BattlePalaceLobby_Text_PresentYouWithBattlePoints:
	.string "Untuk menghormati ikatanmu dengan\n"
	.string "POKéMON, kami berikan\l"
	.string "Battle Point ini.$"

BattleFrontier_BattlePalaceLobby_Text_LikeToRecordMatch:
	.string "Maukah kamu merekam pertarungan\n"
	.string "BATTLE PALACE terbarumu di\l"
	.string "FRONTIER PASS-mu?$"

BattleFrontier_BattlePalaceLobby_Text_RulesAreListed:
	.string "Aturan BATTLE HALL terdaftar.$"

BattleFrontier_BattlePalaceLobby_Text_ReadWhichHeading:
	.string "Judul mana yang ingin kamu baca?$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesBasics:
	.string "Di sini, POKéMON diharuskan berpikir\n"
	.string "dan bertarung sendiri.\p"
	.string "Tidak seperti di alam liar, POKéMON\n"
	.string "yang hidup dengan manusia bertingkah\l"
	.string "berbeda tergantung sifatnya.$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesNature:
	.string "Tergantung sifatnya, POKéMON mungkin\n"
	.string "lebih suka menyerang apa pun yang terjadi.\p"
	.string "POKéMON lain mungkin lebih suka\n"
	.string "melindungi diri dari bahaya.\p"
	.string "Yang lain mungkin suka mengganggu atau\n"
	.string "membuat bingung musuhnya.\p"
	.string "Karena sifatnya, POKéMON akan punya\n"
	.string "jurus favorit yang pandai ia gunakan.\p"
	.string "Ia juga mungkin tidak suka jurus\n"
	.string "tertentu yang sulit ia gunakan.$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesMoves:
	.string "Ada jurus ofensif yang memberikan\n"
	.string "kerusakan langsung pada musuh.\p"
	.string "Ada jurus defensif yang digunakan\n"
	.string "untuk bersiap dari serangan musuh atau\l"
	.string "memulihkan HP dan sebagainya.\p"
	.string "Ada juga jurus aneh lainnya yang\n"
	.string "dapat melemahkan musuh dengan masalah\l"
	.string "status seperti racun dan lumpuh.\p"
	.string "POKéMON akan mempertimbangkan\n"
	.string "menggunakan jurus dari tiga kategori ini.$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesUnderpowered:
	.string "Saat tidak diperintah oleh TRAINER-nya,\n"
	.string "POKéMON mungkin tak bisa menggunakan\l"
	.string "jurus tertentu secara efektif.\p"
	.string "POKéMON tidak pandai menggunakan\n"
	.string "jurus apa pun yang tidak disukainya.\p"
	.string "Jika POKéMON hanya tahu jurus yang\n"
	.string "tidak cocok dengan sifatnya, ia sering\l"
	.string "kali tak bisa mencapai potensinya.$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesWhenInDanger:
	.string "Tergantung sifatnya, POKéMON mungkin\n"
	.string "mulai menggunakan jurus yang tak cocok\l"
	.string "dengan sifatnya saat dalam bahaya.\p"
	.string "Jika POKéMON mulai bertingkah aneh\n"
	.string "saat terdesak, perhatikan baik-baik.$"

