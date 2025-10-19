BattleFrontier_BattleDomeLobby_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattleDomeLobby_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleDomeLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleDomeLobby_OnWarp
	.byte 0

BattleFrontier_BattleDomeLobby_OnResume:
	dome_initresultstree
	end

BattleFrontier_BattleDomeLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleDomeLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleDomeLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleDomeLobby_OnFrame:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattleDomeLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleDomeLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleDomeLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattleDomeLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattleDomeLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattleDomeLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattleDomeLobby_EventScript_QuitWithoutSaving::
	lockall
	msgbox BattleFrontier_BattleDomeLobby_Text_DidntSaveBeforeQuitting, MSGBOX_DEFAULT
	closemessage
	dome_set DOME_DATA_WIN_STREAK, 0
	dome_set DOME_DATA_WIN_STREAK_ACTIVE, FALSE
	dome_set DOME_DATA_ATTEMPTED_CHALLENGE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleDomeLobby_EventScript_WonChallenge::
	call BattleFrontier_EventScript_IncrementWinStreak
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleDomeLobby_EventScript_DefeatedAce
	msgbox BattleFrontier_BattleDomeLobby_Text_CongratsForWinningTourney, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_GiveBattlePoints

BattleFrontier_BattleDomeLobby_EventScript_DefeatedAce::
	msgbox BattleFrontier_BattleDomeLobby_Text_CongratsDefeatedTucker, MSGBOX_DEFAULT
BattleFrontier_BattleDomeLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattleDomeLobby_Text_AwardTheseBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattleDomeLobby_Text_RecordWillBeSaved
	waitmessage
	special LoadPlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	frontier_checkairshow
	dome_set DOME_DATA_ATTEMPTED_CHALLENGE, TRUE
	dome_set DOME_DATA_HAS_WON_CHALLENGE, TRUE
	dome_set DOME_DATA_WIN_STREAK_ACTIVE, TRUE
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	goto BattleFrontier_BattleDomeLobby_EventScript_AskRecordBattle

BattleFrontier_BattleDomeLobby_EventScript_LostChallenge::
	lockall
	msgbox BattleFrontier_BattleDomeLobby_Text_ThankYouForPlaying, MSGBOX_DEFAULT
	message BattleFrontier_BattleDomeLobby_Text_RecordWillBeSaved
	waitmessage
	special LoadPlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	frontier_checkairshow
	dome_set DOME_DATA_WIN_STREAK_ACTIVE, FALSE
	dome_set DOME_DATA_ATTEMPTED_CHALLENGE, TRUE
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
BattleFrontier_BattleDomeLobby_EventScript_AskRecordBattle::
	dome_save 0
	playse SE_SAVE
	waitse
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleDomeLobby_EventScript_EndChallenge
	message BattleFrontier_BattleDomeLobby_Text_RecordLastMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleDomeLobby_EventScript_EndChallenge
	case 0, BattleFrontier_BattleDomeLobby_EventScript_RecordBattle
	case MULTI_B_PRESSED, BattleFrontier_BattleDomeLobby_EventScript_EndChallenge

BattleFrontier_BattleDomeLobby_EventScript_RecordBattle::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattleDomeLobby_EventScript_EndChallenge::
	msgbox BattleFrontier_BattleDomeLobby_Text_HopeToSeeYouAgain, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleDomeLobby_EventScript_ResumeChallenge::
	lockall
	msgbox BattleFrontier_BattleDomeLobby_Text_WeveBeenWaitingForYou, MSGBOX_DEFAULT
	message BattleFrontier_BattleDomeLobby_Text_OkayToSaveBeforeChallenge2
	waitmessage
	dome_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto BattleFrontier_BattleDomeLobby_EventScript_EnterChallenge

BattleFrontier_BattleDomeLobby_EventScript_SinglesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_DOME
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	goto BattleFrontier_BattleDomeLobby_EventScript_AttendantWelcome
	end

BattleFrontier_BattleDomeLobby_EventScript_DoublesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_DOME
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	goto BattleFrontier_BattleDomeLobby_EventScript_AttendantWelcome
	end

BattleFrontier_BattleDomeLobby_EventScript_AttendantWelcome::
	special SavePlayerParty
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleDomeLobby_EventScript_WelcomeSingles
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleDomeLobby_EventScript_WelcomeDoubles
BattleFrontier_BattleDomeLobby_EventScript_AskTakeChallenge::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleDomeLobby_EventScript_TakeSinglesChallenge
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleDomeLobby_EventScript_TakeDoublesChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleDomeLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattleDomeLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge

BattleFrontier_BattleDomeLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattleDomeLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleDomeLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleDomeLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleDomeLobby_EventScript_LoadPartyCancelChallenge
	msgbox BattleFrontier_BattleDomeLobby_Text_OkayToSaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleDomeLobby_EventScript_LoadPartyCancelChallenge
	case YES, BattleFrontier_BattleDomeLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleDomeLobby_EventScript_LoadPartyCancelChallenge

BattleFrontier_BattleDomeLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	dome_init
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleDomeLobby_EventScript_CancelChallengeSaveFailed
	dome_inittrainers
BattleFrontier_BattleDomeLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	dome_settrainers
	msgbox BattleFrontier_BattleDomeLobby_Text_ShowYouToBattleDome, MSGBOX_DEFAULT
	closemessage
	call BattleFrontier_BattleDomeLobby_EventScript_WalkToDoor
	special HealPlayerParty
	warp MAP_BATTLE_FRONTIER_BATTLE_DOME_CORRIDOR, 23, 6
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattleDomeLobby_EventScript_ExplainChallenge::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleDomeLobby_EventScript_ExplainSinglesChallenge
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleDomeLobby_EventScript_ExplainDoublesChallenge
	goto BattleFrontier_BattleDomeLobby_EventScript_AskTakeChallenge

BattleFrontier_BattleDomeLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattleDomeLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattleDomeLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattleDomeLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattleDomeLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_EndCancelChallenge

BattleFrontier_BattleDomeLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattleDomeLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_EndCancelChallenge

BattleFrontier_BattleDomeLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge

BattleFrontier_BattleDomeLobby_EventScript_LoadPartyCancelChallenge::
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattleDomeLobby_Text_HopeToSeeYouAgain, MSGBOX_DEFAULT
BattleFrontier_BattleDomeLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattleDomeLobby_EventScript_WalkToDoor::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleDomeLobby_EventScript_SinglesAttendantWalkToDoor
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleDomeLobby_EventScript_DoublesAttendantWalkToDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattleDomeLobby_Movement_WalkToDoor
	waitmovement 0
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleDomeLobby_EventScript_OpenSinglesDoor
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleDomeLobby_EventScript_OpenDoublesDoor
	waitdooranim
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleDomeLobby_EventScript_SinglesAttendantEnterDoor
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleDomeLobby_EventScript_DoublesAttendantEnterDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattleDomeLobby_Movement_PlayerEnterDoor
	waitmovement 0
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleDomeLobby_EventScript_CloseSinglesDoor
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleDomeLobby_EventScript_CloseDoublesDoor
	waitdooranim
	return

BattleFrontier_BattleDomeLobby_EventScript_SinglesAttendantWalkToDoor::
	applymovement LOCALID_DOME_ATTENDANT_SINGLES, BattleFrontier_BattleDomeLobby_Movement_WalkToDoor
	return

BattleFrontier_BattleDomeLobby_EventScript_DoublesAttendantWalkToDoor::
	applymovement LOCALID_DOME_ATTENDANT_DOUBLES, BattleFrontier_BattleDomeLobby_Movement_WalkToDoor
	return

BattleFrontier_BattleDomeLobby_EventScript_SinglesAttendantEnterDoor::
	applymovement LOCALID_DOME_ATTENDANT_SINGLES, BattleFrontier_BattleDomeLobby_Movement_AttendantEnterDoor
	return

BattleFrontier_BattleDomeLobby_EventScript_DoublesAttendantEnterDoor::
	applymovement LOCALID_DOME_ATTENDANT_DOUBLES, BattleFrontier_BattleDomeLobby_Movement_AttendantEnterDoor
	return

BattleFrontier_BattleDomeLobby_EventScript_WelcomeSingles::
	msgbox BattleFrontier_BattleDomeLobby_Text_WelcomeSingleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomeLobby_EventScript_WelcomeDoubles::
	msgbox BattleFrontier_BattleDomeLobby_Text_WelcomeDoubleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomeLobby_EventScript_TakeSinglesChallenge::
	message BattleFrontier_BattleDomeLobby_Text_TakeSinglesChallenge
	return

BattleFrontier_BattleDomeLobby_EventScript_TakeDoublesChallenge::
	message BattleFrontier_BattleDomeLobby_Text_TakeDoublesChallenge
	return

BattleFrontier_BattleDomeLobby_EventScript_ExplainSinglesChallenge::
	msgbox BattleFrontier_BattleDomeLobby_Text_ExplainSinglesChallenge, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomeLobby_EventScript_ExplainDoublesChallenge::
	msgbox BattleFrontier_BattleDomeLobby_Text_ExplainDoublesChallenge, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomeLobby_EventScript_OpenSinglesDoor::
	opendoor 5, 4
	return

BattleFrontier_BattleDomeLobby_EventScript_OpenDoublesDoor::
	opendoor 17, 4
	return

BattleFrontier_BattleDomeLobby_EventScript_CloseSinglesDoor::
	closedoor 5, 4
	return

BattleFrontier_BattleDomeLobby_EventScript_CloseDoublesDoor::
	closedoor 17, 4
	return

BattleFrontier_BattleDomeLobby_Movement_WalkToDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattleDomeLobby_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleDomeLobby_Movement_PlayerEnterDoor:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleDomeLobby_EventScript_ShowSinglesResults::
	lockall
	frontier_results FRONTIER_FACILITY_DOME, FRONTIER_MODE_SINGLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleDomeLobby_EventScript_ShowDoublesResults::
	lockall
	frontier_results FRONTIER_FACILITY_DOME, FRONTIER_MODE_DOUBLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleDomeLobby_EventScript_ShowPrevTourneyTree::
	dome_get DOME_DATA_PREV_TOURNEY_TYPE
	call_if_eq VAR_RESULT, 0, BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsSinglesLv50
	call_if_eq VAR_RESULT, 1, BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsDoublesLv50
	call_if_eq VAR_RESULT, 2, BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsSinglesLvOpen
	call_if_eq VAR_RESULT, 3, BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsDoublesLvOpen
	fadescreen FADE_TO_BLACK
	dome_showprevtourneytree
	waitstate
	end

BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsSinglesLv50::
	msgbox BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsSinglesLv50, MSGBOX_SIGN
	return

BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsDoublesLv50::
	msgbox BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsDoublesLv50, MSGBOX_SIGN
	return

BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsSinglesLvOpen::
	msgbox BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsSinglesLvOpen, MSGBOX_SIGN
	return

BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsDoublesLvOpen::
	msgbox BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsDoublesLvOpen, MSGBOX_SIGN
	return

BattleFrontier_BattleDomeLobby_EventScript_Maniac::
	dome_getwinnersname
	msgbox BattleFrontier_BattleDomeLobby_Text_LastWinnerWasTough, MSGBOX_NPC
	end

BattleFrontier_BattleDomeLobby_EventScript_Lass::
	msgbox BattleFrontier_BattleDomeLobby_Text_WinnersGainReputation, MSGBOX_NPC
	end

BattleFrontier_BattleDomeLobby_EventScript_FatMan::
	msgbox BattleFrontier_BattleDomeLobby_Text_TrashedInFirstRound, MSGBOX_NPC
	end

BattleFrontier_BattleDomeLobby_EventScript_Man::
	msgbox BattleFrontier_BattleDomeLobby_Text_NeedToCheckOpponentCarefully, MSGBOX_NPC
	end

@ A few OutsideWest event scripts are inserted here instead, two of which are unused
BattleFrontier_OutsideWest_EventScript_Man3::
	msgbox BattleFrontier_OutsideWest_Text_LongDreamedAboutBattleFrontier, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_BattleDomeSign2::
	msgbox BattleFrontier_OutsideWest_Text_BattleDomeSign2, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnderConstructionSign::
	msgbox BattleFrontier_OutsideWest_Text_QuestionMarkUnderConstruction, MSGBOX_NPC
	end

BattleFrontier_BattleDomeLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattleDomeLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleDomeLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattleDomeLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 17, 4, MULTI_BATTLE_DOME_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleDomeLobby_EventScript_RulesMatchup
	case 1, BattleFrontier_BattleDomeLobby_EventScript_RulesTourneyTree
	case 2, BattleFrontier_BattleDomeLobby_EventScript_RulesDoubleKO
	case 3, BattleFrontier_BattleDomeLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattleDomeLobby_EventScript_ExitRules
	end

BattleFrontier_BattleDomeLobby_EventScript_RulesMatchup::
	msgbox BattleFrontier_BattleDomeLobby_Text_ExplainMatchupRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleDomeLobby_EventScript_RulesTourneyTree::
	msgbox BattleFrontier_BattleDomeLobby_Text_ExplainTourneyTree, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleDomeLobby_EventScript_RulesDoubleKO::
	msgbox BattleFrontier_BattleDomeLobby_Text_ExplainDoubleKORules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleDomeLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattleDomeLobby_Text_WelcomeSingleBattle:
	.string "Tempat di mana strategi para TRAINER\n"
	.string "diuji!\p"
	.string "Selamat datang di BATTLE DOME!\p"
	.string "Aku pemandumu untuk Turnamen\n"
	.string "SINGLE BATTLE.$"

BattleFrontier_BattleDomeLobby_Text_TakeSinglesChallenge:
	.string "Apa kamu ingin menantang di\n"
	.string "Turnamen SINGLE BATTLE?$"

BattleFrontier_BattleDomeLobby_Text_HopeToSeeYouAgain:
	.string "Kami harap kamu datang lagi.$"

BattleFrontier_BattleDomeLobby_Text_ExplainSinglesChallenge:
	.string "Turnamen SINGLE BATTLE, seperti\n"
	.string "namanya, adalah turnamen\l"
	.string "PERTARUNGAN TUNGGAL.\p"
	.string "Semua TRAINER yang berpartisipasi\n"
	.string "harus memasukkan tiga POKéMON.\p"
	.string "Di setiap pertarungan, satu dari tiga\n"
	.string "POKéMON harus dicadangkan.\p"
	.string "Dua POKéMON lainnya bisa bertarung\n"
	.string "satu per satu.\p"
	.string "Pilih dua POKéMON petarung setelah\n"
	.string "melihat trio POKéMON lawan.\p"
	.string "Kamu menangkan turnamen dengan\n"
	.string "mengalahkan empat TRAINER.\p"
	.string "Battle Points diberikan kepada\n"
	.string "pemenang turnamen.\p"
	.string "Jika kamu ingin menghentikan\n"
	.string "turnamen, silakan simpan permainan.\p"
	.string "Jika tidak disimpan sebelum berhenti,\n"
	.string "kamu akan didiskualifikasi.$"

BattleFrontier_BattleDomeLobby_Text_OkayToSaveBeforeChallenge:
	.string "Sebelum kupandu ke BATTLE DOME,\n"
	.string "aku harus menyimpan data. Boleh?$"

BattleFrontier_BattleDomeLobby_Text_WhichLevelMode:
	.string "Turnamen ini menawarkan dua level\n"
	.string "tantangan, Level 50 dan Level Terbuka.\l"
	.string "Mana pilihanmu?$"

BattleFrontier_BattleDomeLobby_Text_SelectThreeMons:
	.string "Sekarang pilih tiga POKéMON yang\n"
	.string "ingin kamu daftarkan.$"

BattleFrontier_BattleDomeLobby_Text_NotEnoughValidMonsLvOpen:
	.string "Permisi!\p"
	.string "Kamu tidak punya tiga POKéMON yang valid.\p"
	.string "Selain itu, POKéMON harus memegang\n"
	.string "item yang berbeda.\p"
	.string "TELUR{STR_VAR_1} tidak memenuhi syarat.\p"
	.string "Silakan temui aku jika sudah siap.$"

BattleFrontier_BattleDomeLobby_Text_NotEnoughValidMonsLv50:
	.string "Permisi!\p"
	.string "Kamu tidak punya tiga POKéMON yang valid.\p"
	.string "Kamu harus punya tiga POKéMON berbeda\n"
	.string "Level 50 atau kurang untuk masuk.\p"
	.string "Mereka juga harus memegang\n"
	.string "item yang berbeda.\p"
	.string "TELUR{STR_VAR_1} tidak memenuhi syarat.\p"
	.string "Silakan temui aku jika sudah siap.$"

BattleFrontier_BattleDomeLobby_Text_ShowYouToBattleDome:
	.string "Sekarang akan kutunjukkan jalan ke\n"
	.string "BATTLE DOME.$"

BattleFrontier_BattleDomeLobby_Text_DidntSaveBeforeQuitting:
	.string "Permisi!\p"
	.string "Kamu tidak menyimpan sebelum keluar dari\n"
	.string "tantanganmu yang terakhir.\p"
	.string "Karena itu, tantanganmu sejauh ini\n"
	.string "telah didiskualifikasi. Maaf!$"

BattleFrontier_BattleDomeLobby_Text_CongratsForWinningTourney:
	.string "Selamat telah memenangkan\n"
	.string "Turnamen Pertarunganmu!$"

@ Unused
BattleFrontier_BattleDomeLobby_Text_HereIsYourPrize:
	.string "Ini hadiah untuk kemenangan\n"
	.string "Turnamen Pertarunganmu.$"

@ Used by Verdanturf Tent
BattleFrontier_BattleDomeLobby_Text_ReceivedPrize:
	.string "{PLAYER} mendapatkan hadiah\n"
	.string "{STR_VAR_1}.$"

@ Unused
BattleFrontier_BattleDomeLobby_Text_BagFullMakeRoom:
	.string "Oh, TAS-mu sepertinya penuh.\p"
	.string "Tolong kosongkan TAS-mu, lalu temui\n"
	.string "aku lagi.$"

BattleFrontier_BattleDomeLobby_Text_ThankYouForPlaying:
	.string "Terima kasih sudah bermain!$"

BattleFrontier_BattleDomeLobby_Text_RecordWillBeSaved:
	.string "Rekormu akan disimpan.\n"
	.string "Harap tunggu.$"

BattleFrontier_BattleDomeLobby_Text_WeveBeenWaitingForYou:
	.string "Kami sudah menunggumu!$"

BattleFrontier_BattleDomeLobby_Text_OkayToSaveBeforeChallenge2:
	.string "Sebelum kupandu ke BATTLE DOME,\n"
	.string "aku harus menyimpan data. Boleh?$"

BattleFrontier_BattleDomeLobby_Text_WelcomeDoubleBattle:
	.string "Tempat di mana strategi para TRAINER\n"
	.string "diuji!\p"
	.string "Selamat datang di BATTLE DOME!\p"
	.string "Aku pemandumu untuk Turnamen\n"
	.string "DOUBLE BATTLE.$"

BattleFrontier_BattleDomeLobby_Text_TakeDoublesChallenge:
	.string "Apa kamu ingin menantang di\n"
	.string "Turnamen DOUBLE BATTLE?$"

BattleFrontier_BattleDomeLobby_Text_ExplainDoublesChallenge:
	.string "Turnamen DOUBLE BATTLE, seperti\n"
	.string "namanya, adalah turnamen\l"
	.string "PERTARUNGAN GANDA.\p"
	.string "Semua TRAINER yang berpartisipasi\n"
	.string "harus memasukkan tiga POKéMON.\p"
	.string "Di setiap pertarungan, satu dari tiga\n"
	.string "POKéMON harus dicadangkan.\p"
	.string "Dua POKéMON yang tersisa harus ikut\n"
	.string "dalam PERTARUNGAN GANDA.\p"
	.string "Pilih dua POKéMON petarung setelah\n"
	.string "melihat trio POKéMON lawan.\p"
	.string "Kamu menangkan turnamen dengan\n"
	.string "mengalahkan empat TRAINER.\p"
	.string "Battle Points diberikan kepada\n"
	.string "pemenang turnamen.\p"
	.string "Jika kamu ingin menghentikan\n"
	.string "turnamen, silakan simpan permainan.\p"
	.string "Jika tidak disimpan sebelum berhenti,\n"
	.string "kamu akan didiskualifikasi.$"

BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsSinglesLv50:
	.string "Ini hasil Turnamen SINGLE BATTLE\n"
	.string "Level 50 yang terakhir.$"

BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsDoublesLv50:
	.string "Ini hasil Turnamen DOUBLE BATTLE\n"
	.string "Level 50 yang terakhir.$"

BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsSinglesLvOpen:
	.string "Ini hasil Turnamen SINGLE BATTLE\n"
	.string "Level Terbuka yang terakhir.$"

BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsDoublesLvOpen:
	.string "Ini hasil Turnamen DOUBLE BATTLE\n"
	.string "Level Terbuka yang terakhir.$"

BattleFrontier_BattleDomeLobby_Text_LastWinnerWasTough:
	.string "Kamu lihat?\n"
	.string "Turnamen Pertarungan terakhir?\p"
	.string "Pemenangnya, {STR_VAR_1}, benar-benar\n"
	.string "tangguh.\p"
	.string "Kamu harus lihat hasilnya di monitor\n"
	.string "sebelah PC.$"

BattleFrontier_OutsideWest_Text_LongDreamedAboutBattleFrontier:
	.string "The BATTLE FRONTIER…\n"
	.string "I've long dreamed about a place like it.$"

@ Functionally unused
BattleFrontier_OutsideWest_Text_BattleDomeSign2:
	.string "The BATTLE DOME\n"
	.string "Become the Unbeatable Superstar!$"

@ Functionally unused
BattleFrontier_OutsideWest_Text_QuestionMarkUnderConstruction:
	.string "The ??????\n"
	.string "Under Construction!$"

BattleFrontier_BattleDomeLobby_Text_WinnersGainReputation:
	.string "Saat seorang TRAINER memenangkan\n"
	.string "turnamen beruntun di BATTLE DOME,\l"
	.string "ia mendapat reputasi sebagai bintang.\p"
	.string "TRAINER tangguh tertarik oleh reputasi\n"
	.string "itu ke BATTLE DOME.\p"
	.string "Superstar sejati adalah TRAINER yang\n"
	.string "bisa terus memenangkan turnamen.$"

BattleFrontier_BattleDomeLobby_Text_TrashedInFirstRound:
	.string "Aku bertemu salah satu favorit\n"
	.string "turnamen di ronde pertama.\p"
	.string "Tentu saja aku dibantai…$"

BattleFrontier_BattleDomeLobby_Text_NeedToCheckOpponentCarefully:
	.string "Aku pasti menang jika POKéMON ini\n"
	.string "kucadangkan.\p"
	.string "Kamu harus periksa POKéMON lawanmu\n"
	.string "dengan teliti sebelum memilih\l"
	.string "POKéMON petarungmu.$"

BattleFrontier_BattleDomeLobby_Text_CongratsDefeatedTucker:
	.string "Selamat!\p"
	.string "Kamu mengalahkan DOME ACE dan memenangkan\n"
	.string "Turnamen Pertarungan!$"

BattleFrontier_BattleDomeLobby_Text_AwardTheseBattlePoints:
	.string "Sebagai pengakuan atas strategimu--\n"
	.string "yang juga sangat indah--\l"
	.string "kami berikan Battle Point ini!$"

BattleFrontier_BattleDomeLobby_Text_RecordLastMatch:
	.string "Maukah kamu merekam pertarungan\n"
	.string "BATTLE DOME terakhirmu di\l"
	.string "FRONTIER PASS-mu?$"

BattleFrontier_BattleDomeLobby_Text_RulesAreListed:
	.string "Aturan Turnamen Pertarungan\n"
	.string "terdaftar.$"

BattleFrontier_BattleDomeLobby_Text_ReadWhichHeading:
	.string "Judul mana yang ingin kamu baca?$"

BattleFrontier_BattleDomeLobby_Text_ExplainMatchupRules:
	.string "Bagan turnamen dibuat berdasarkan\n"
	.string "ketangguhan POKéMON yang dimiliki\l"
	.string "oleh para TRAINER.\p"
	.string "Bagan ini menghindari TRAINER tangguh\n"
	.string "saling berhadapan di awal.$"

BattleFrontier_BattleDomeLobby_Text_ExplainTourneyTree:
	.string "Bagan turnamen, atau yang kami sebut\n"
	.string "“Pohon,” bisa dilihat di Ruang Tunggu\l"
	.string "dari pemandu mana pun.\p"
	.string "Pohon Turnamen akan menyediakan\n"
	.string "beberapa jenis data.\p"
	.string "Data yang terlihat termasuk hasil\n"
	.string "turnamen sebelumnya, POKéMON yang\l"
	.string "dipegang TRAINER, dan gaya bertarung\l"
	.string "para TRAINER.$"

BattleFrontier_BattleDomeLobby_Text_ExplainDoubleKORules:
	.string "Jika POKéMON petarung pingsan di saat\n"
	.string "yang sama--double KO--dalam laga\l"
	.string "turnamen, para WASIT akan meninjau\l"
	.string "ulang laga dan mengumumkan pemenangnya.$"
