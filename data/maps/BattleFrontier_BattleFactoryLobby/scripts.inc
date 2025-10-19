BattleFrontier_BattleFactoryLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleFactoryLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleFactoryLobby_OnWarp
	.byte 0

BattleFrontier_BattleFactoryLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleFactoryLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleFactoryLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleFactoryLobby_OnFrame:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattleFactoryLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleFactoryLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleFactoryLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattleFactoryLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattleFactoryLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattleFactoryLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattleFactoryLobby_EventScript_QuitWithoutSaving::
	lockall
	msgbox BattleFrontier_BattleFactoryLobby_Text_DidntSaveBeforeQuitting, MSGBOX_DEFAULT
	closemessage
	factory_setswapped
	factory_set FACTORY_DATA_WIN_STREAK_SWAPS, 0
	factory_set FACTORY_DATA_WIN_STREAK, 0
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleFactoryLobby_EventScript_DefeatedFactoryHead
	msgbox BattleFrontier_BattleFactoryLobby_Text_CongratsSevenWins, MSGBOX_DEFAULT
	waitmessage
	goto BattleFrontier_BattleFactoryLobby_EventScript_GiveBattlePoints

BattleFrontier_BattleFactoryLobby_EventScript_DefeatedFactoryHead::
	msgbox BattleFrontier_BattleFactoryLobby_Text_CongratsForDefeatingHead, MSGBOX_DEFAULT
	waitmessage
BattleFrontier_BattleFactoryLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattleFactoryLobby_Text_AwardBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattleFactoryLobby_Text_ExchangeMonsAndSave
	waitmessage
	frontier_checkairshow
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
	factory_save 0
	playse SE_SAVE
	waitse
	goto BattleFrontier_BattleFactoryLobby_EventScript_AskRecordBattle
	end

BattleFrontier_BattleFactoryLobby_EventScript_LostChallenge::
	lockall
	message BattleFrontier_BattleFactoryLobby_Text_ReturnMonsSaveResults
	waitmessage
	frontier_checkairshow
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, FALSE
	factory_save 0
	playse SE_SAVE
	waitse

BattleFrontier_BattleFactoryLobby_EventScript_AskRecordBattle::
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle
	message BattleFrontier_BattleFactoryLobby_Text_RecordLastMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_RecordBattle
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle

BattleFrontier_BattleFactoryLobby_EventScript_RecordBattle::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle::
	msgbox BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_ResumeChallenge::
	lockall
	message BattleFrontier_BattleFactoryLobby_Text_WaitingForYouToResume
	waitmessage
	factory_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	setvar VAR_0x8006, 2
	goto BattleFrontier_BattleFactoryLobby_EventScript_EnterChallenge

BattleFrontier_BattleFactoryLobby_EventScript_SinglesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_FACTORY
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	goto BattleFrontier_BattleFactoryLobby_EventScript_Attendant
	end

BattleFrontier_BattleFactoryLobby_EventScript_DoublesAttendant::
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_FACTORY
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	goto BattleFrontier_BattleFactoryLobby_EventScript_Attendant
	end

BattleFrontier_BattleFactoryLobby_EventScript_Attendant::
	special SavePlayerParty
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForSingleBattle
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForDoubleBattle
BattleFrontier_BattleFactoryLobby_EventScript_AskTakeChallenge::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_TakeSinglesChallenge
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_TakeDoublesChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge

BattleFrontier_BattleFactoryLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattleFactoryLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleFactoryLobby_Text_OkayToSaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattleFactoryLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattleFactoryLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	factory_init
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallengeSaveFailed
	setvar VAR_0x8006, 0
BattleFrontier_BattleFactoryLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	msgbox BattleFrontier_BattleFactoryLobby_Text_StepThisWay, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_TalkedToSinglesAttendant
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_TalkedToDoublesAttendant
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleFactoryLobby_Movement_AttendantEnterDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattleFactoryLobby_Movement_PlayerEnterDoor
	waitmovement 0
	warp MAP_BATTLE_FRONTIER_BATTLE_FACTORY_PRE_BATTLE_ROOM, 8, 13
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattleFactoryLobby_EventScript_TalkedToSinglesAttendant::
	setvar VAR_LAST_TALKED, LOCALID_FACTORY_ATTENDANT_SINGLES
	return

BattleFrontier_BattleFactoryLobby_EventScript_TalkedToDoublesAttendant::
	setvar VAR_LAST_TALKED, LOCALID_FACTORY_ATTENDANT_DOUBLES
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainChallenge::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_ExplainSinglesChallenge
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_ExplainDoublesChallenge
	goto BattleFrontier_BattleFactoryLobby_EventScript_AskTakeChallenge

BattleFrontier_BattleFactoryLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge

BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleFactoryLobby_Movement_AttendantEnterDoor:
	walk_up
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleFactoryLobby_Movement_PlayerEnterDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForSingleBattle::
	msgbox BattleFrontier_BattleFactoryLobby_Text_WelcomeForSingleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForDoubleBattle::
	msgbox BattleFrontier_BattleFactoryLobby_Text_WelcomeForDoubleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_TakeSinglesChallenge::
	message BattleFrontier_BattleFactoryLobby_Text_TakeSinglesChallenge
	return

BattleFrontier_BattleFactoryLobby_EventScript_TakeDoublesChallenge::
	message BattleFrontier_BattleFactoryLobby_Text_TakeDoublesChallenge
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainSinglesChallenge::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSinglesChallenge, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainDoublesChallenge::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainDoublesChallenge, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_ShowSinglesResults::
	lockall
	frontier_results FRONTIER_FACILITY_FACTORY, FRONTIER_MODE_SINGLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_ShowDoublesResults::
	lockall
	frontier_results FRONTIER_FACILITY_FACTORY, FRONTIER_MODE_DOUBLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_Woman::
	msgbox BattleFrontier_BattleFactoryLobby_Text_NeedKnowledgeOfMonsMoves, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_Camper::
	msgbox BattleFrontier_BattleFactoryLobby_Text_SwappedForWeakMon, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_Picnicker::
	lock
	msgbox BattleFrontier_BattleFactoryLobby_Text_NeedToCheckOpponentsMons, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleFactoryLobby_EventScript_FatMan::
	msgbox BattleFrontier_BattleFactoryLobby_Text_CantFigureOutStaffHints, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattleFactoryLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattleFactoryLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 17, 0, MULTI_BATTLE_FACTORY_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_RulesBasics
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapPartner
	case 2, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNumber
	case 3, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNotes
	case 4, BattleFrontier_BattleFactoryLobby_EventScript_RulesOpenLv
	case 5, BattleFrontier_BattleFactoryLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_ExitRules
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesBasics::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainBasicRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapPartner::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapPartnerRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNumber::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNumberRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNotes::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNotesRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesOpenLv::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainOpenLvRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattleFactoryLobby_Text_WelcomeForSingleBattle:
	.string "Tempat di mana kecerdasan TRAINER\n"
	.string "diuji!\p"
	.string "Selamat datang di BATTLE FACTORY!\p"
	.string "Aku pemandumu untuk Turnamen Battle\n"
	.string "Swap Single.$"

BattleFrontier_BattleFactoryLobby_Text_TakeSinglesChallenge:
	.string "Apa kamu ingin mengambil tantangan\n"
	.string "Battle Swap Single?$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSinglesChallenge:
	.string "Turnamen Battle Swap Single adalah\n"
	.string "kompetisi SINGLE BATTLE yang hanya\l"
	.string "menggunakan POKéMON sewaan.\p"
	.string "Pertama, kamu akan dipinjami tiga\n"
	.string "POKéMON khusus untuk acara ini.\p"
	.string "Menggunakan POKéMON sewaan yang ada,\n"
	.string "kamu harus melakukan SINGLE BATTLE.\p"
	.string "Jika menang, kamu diizinkan menukar\n"
	.string "salah satu POKéMON sewaanmu.\p"
	.string "Ulangi siklus bertarung dan menukar\n"
	.string "ini--jika kamu menang tujuh kali\l"
	.string "berturut-turut, kamu akan dapat BP.\p"
	.string "Jika ingin menghentikan tantangan,\n"
	.string "silakan simpan permainan.\p"
	.string "Jika tidak disimpan, kamu akan\n"
	.string "didiskualifikasi dari tantanganmu.$"

BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit:
	.string "Kami menantikan kunjunganmu lagi.$"

BattleFrontier_BattleFactoryLobby_Text_WhichLevelMode:
	.string "Level mana yang ingin kamu tantang?\n"
	.string "Level 50 atau Level Terbuka?$"

BattleFrontier_BattleFactoryLobby_Text_OkayToSaveBeforeChallenge:
	.string "Sebelum kamu memulai tantangan,\n"
	.string "aku harus menyimpan permainan. Boleh?$"

BattleFrontier_BattleFactoryLobby_Text_WillHoldMonsForSafekeeping:
	.string "Oke, akan kusimpan POKéMON-mu\n"
	.string "selama kamu bertanding.$"

BattleFrontier_BattleFactoryLobby_Text_StepThisWay:
	.string "Silakan lewat sini.$"

BattleFrontier_BattleFactoryLobby_Text_ReturnMonsSaveResults:
	.string "Terima kasih atas partisipasinya!\p"
	.string "Akan kukembalikan POKéMON-mu sebagai\n"
	.string "ganti POKéMON sewaan kami.\p"
	.string "Juga, aku harus menyimpan hasil acara.\n"
	.string "Harap tunggu.$"

BattleFrontier_BattleFactoryLobby_Text_ReturnMons:
	.string "Akan kukembalikan POKéMON-mu sebagai\n"
	.string "ganti POKéMON sewaan kami.$"

BattleFrontier_BattleFactoryLobby_Text_CongratsSevenWins:
	.string "Selamat! Kamu telah memenangkan tujuh\n"
	.string "laga Battle Swap berturut-turut!$"

BattleFrontier_BattleFactoryLobby_Text_AwardBattlePointsForStreak:
	.string "Sebagai pengakuan atas 7 kemenanganmu,\n"
	.string "kami berikan Battle Point ini.$"

BattleFrontier_BattleFactoryLobby_Text_MaxBattlePoints:
	.string "Oh, oh, oh!\p"
	.string "Battle Points-mu sudah maksimal.\p"
	.string "Silakan kembali setelah menggunakan\n"
	.string "beberapa Battle Points.$"

BattleFrontier_BattleFactoryLobby_Text_WaitingForYouToResume:
	.string "Kami sudah menunggumu!\p"
	.string "Sebelum kita melanjutkan tantanganmu,\n"
	.string "aku harus menyimpan permainan.$"

BattleFrontier_BattleFactoryLobby_Text_DidntSaveBeforeQuitting:
	.string "Maaf harus mengatakan ini, tapi kamu\n"
	.string "tidak menyimpan sebelum berhenti main.\p"
	.string "Akibatnya, kamu telah didiskualifikasi\n"
	.string "dari tantanganmu.$"

BattleFrontier_BattleFactoryLobby_Text_WellReturnMons:
	.string "Kami akan kembalikan POKéMON pribadimu.$"

BattleFrontier_BattleFactoryLobby_Text_ReceivedPrizeItem:
	.string "{PLAYER} mendapatkan hadiah\n"
	.string "{STR_VAR_1}.$"

BattleFrontier_BattleFactoryLobby_Text_WelcomeForDoubleBattle:
	.string "Tempat di mana kecerdasan TRAINER\n"
	.string "diuji!\p"
	.string "Selamat datang di BATTLE FACTORY!\p"
	.string "Aku pemandumu untuk Turnamen Battle\n"
	.string "Swap Double.$"

BattleFrontier_BattleFactoryLobby_Text_TakeDoublesChallenge:
	.string "Apa kamu ingin mengambil tantangan\n"
	.string "Battle Swap Double?$"

BattleFrontier_BattleFactoryLobby_Text_ExplainDoublesChallenge:
	.string "Turnamen Battle Swap Double adalah\n"
	.string "kompetisi DOUBLE BATTLE yang hanya\l"
	.string "menggunakan POKéMON sewaan.\p"
	.string "Pertama, kamu akan dipinjami tiga\n"
	.string "POKéMON khusus untuk acara ini.\p"
	.string "Menggunakan POKéMON sewaan yang ada,\n"
	.string "kamu harus melakukan DOUBLE BATTLE.\p"
	.string "Jika menang, kamu diizinkan menukar\n"
	.string "salah satu POKéMON sewaanmu.\p"
	.string "Ulangi siklus bertarung dan menukar\n"
	.string "ini--jika kamu menang tujuh kali\l"
	.string "berturut-turut, kamu akan dapat BP.\p"
	.string "Jika ingin menghentikan tantangan,\n"
	.string "silakan simpan permainan.\p"
	.string "Jika tidak disimpan sebelum berhenti,\n"
	.string "kamu akan didiskualifikasi.$"

BattleFrontier_BattleFactoryLobby_Text_CongratsForDefeatingHead:
	.string "Selamat telah mengalahkan\n"
	.string "KEPALA PABRIK dan memenangkan\l"
	.string "tujuh laga berturut-turut!$"

BattleFrontier_BattleFactoryLobby_Text_AwardBattlePoints:
	.string "Sebagai pengakuan atas luasnya\n"
	.string "pengetahuan dan kecerdasanmu,\l"
	.string "kami berikan Battle Point ini.$"

BattleFrontier_BattleFactoryLobby_Text_ExchangeMonsAndSave:
	.string "Biar kutukar POKéMON-mu dengan\n"
	.string "POKéMON sewaan kami.\p"
	.string "Aku perlu menyimpan data pertarungan,\n"
	.string "jadi harap tunggu.$"

BattleFrontier_BattleFactoryLobby_Text_RecordLastMatch:
	.string "Maukah kamu merekam pertarungan\n"
	.string "BATTLE FACTORY terakhirmu di\l"
	.string "FRONTIER PASS-mu?$"

BattleFrontier_BattleFactoryLobby_Text_NeedKnowledgeOfMonsMoves:
	.string "Hai!\n"
	.string "Kamu!\p"
	.string "Apa kamu pikir acara di sini mudah\n"
	.string "karena tak perlu punya tim POKéMON?\p"
	.string "Aku takkan seyakin itu bisa menang\n"
	.string "dengan mudah.\p"
	.string "Jika kamu tak punya pengetahuan mendalam\n"
	.string "tentang POKéMON dan jurus mereka,\l"
	.string "akan sulit untuk terus menang.$"

BattleFrontier_BattleFactoryLobby_Text_SwappedForWeakMon:
	.string "Aku menukar dengan POKéMON lemah…\n"
	.string "Kukira jenis yang bagus…\p"
	.string "Kami dibantai habis-habisan…$"

BattleFrontier_BattleFactoryLobby_Text_NeedToCheckOpponentsMons:
	.string "Semuanya tidak berjalan sesuai mauku.\p"
	.string "Kamu harus periksa POKéMON lawanmu\n"
	.string "selama pertarungan untuk melihat\l"
	.string "apakah mereka bagus.$"

BattleFrontier_BattleFactoryLobby_Text_CantFigureOutStaffHints:
	.string "Kamu tahu staf di sini memberimu\n"
	.string "sedikit petunjuk tentang lawanmu?\p"
	.string "Yah, aku sudah dewasa, tapi aku\n"
	.string "sulit memahami petunjuk mereka.$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_RentalMonsAreVaried:
	.string "Aku ini tangguh, tapi aku gampang\n"
	.string "bosan, jadi aku terus menukar dan\l"
	.string "bertarung berulang kali.\p"
	.string "Ngomong-ngomong, saat aku terus ikut\n"
	.string "acara Battle Swap, aku sadar mereka\l"
	.string "mengganti-ganti POKéMON sewaan.$"

BattleFrontier_BattleFactoryLobby_Text_RulesAreListed:
	.string "Aturan Battle Swap terdaftar.$"

BattleFrontier_BattleFactoryLobby_Text_ReadWhichHeading:
	.string "Judul mana yang ingin kamu baca?$"

BattleFrontier_BattleFactoryLobby_Text_ExplainBasicRules:
	.string "Di acara Battle Swap, kamu hanya boleh\n"
	.string "menggunakan tiga POKéMON.\p"
	.string "Baik saat menyewa atau menukar, timmu\n"
	.string "tidak boleh punya dua atau lebih\l"
	.string "POKéMON yang sama.$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapPartnerRules:
	.string "Kamu hanya bisa menukar POKéMON dengan\n"
	.string "TRAINER yang baru saja kamu kalahkan.\p"
	.string "Kamu hanya bisa menukar dengan POKéMON\n"
	.string "yang digunakan oleh TRAINER itu.$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNumberRules:
	.string "Setelah setiap kemenangan, kamu boleh\n"
	.string "menukar dengan salah satu POKéMON\l"
	.string "lawan yang kalah.\p"
	.string "Kamu tidak akan bisa menukar POKéMON\n"
	.string "dengan TRAINER ketujuh di acara ini.$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNotesRules:
	.string "Ada dua poin penting yang harus\n"
	.string "diketahui saat menukar POKéMON.\p"
	.string "Pertama, saat menukar, kamu tak bisa\n"
	.string "memeriksa status POKéMON yang akan\l"
	.string "kamu terima.\p"
	.string "Kedua, POKéMON di timmu diatur\n"
	.string "dalam urutan, tergantung pada urutan\l"
	.string "kamu menyewanya.\p"
	.string "Urutan ini tidak akan berubah\n"
	.string "meskipun ada penukaran.$"

BattleFrontier_BattleFactoryLobby_Text_ExplainOpenLvRules:
	.string "Di Level Terbuka, POKéMON sewaan\n"
	.string "dan POKéMON TRAINER lawan semuanya\l"
	.string "Level 100.$"
