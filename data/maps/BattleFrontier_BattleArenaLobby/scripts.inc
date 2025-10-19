BattleFrontier_BattleArenaLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleArenaLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleArenaLobby_OnWarp
	.byte 0

BattleFrontier_BattleArenaLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleArenaLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleArenaLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleArenaLobby_OnFrame:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattleArenaLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleArenaLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleArenaLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattleArenaLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattleArenaLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattleArenaLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattleArenaLobby_EventScript_QuitWithoutSaving::
	lockall
	msgbox BattleFrontier_BattleArenaLobby_Text_DidntSaveBeforeShuttingDown, MSGBOX_DEFAULT
	closemessage
	arena_set ARENA_DATA_WIN_STREAK, 0
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleArenaLobby_EventScript_DefeatedTycoon
	msgbox BattleFrontier_BattleArenaLobby_Text_CongratsOnSevenWins, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_GiveBattlePoints

BattleFrontier_BattleArenaLobby_EventScript_DefeatedTycoon::
	msgbox BattleFrontier_BattleArenaLobby_Text_CongratsOnDefeatingTycoon, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattleArenaLobby_Text_PleaseAcceptBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattleArenaLobby_Text_RecordAchievement
	waitmessage
	call BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_LostChallenge::
	lockall
	message BattleFrontier_BattleArenaLobby_Text_ThankYouWaitWhileSave
	waitmessage
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, FALSE
	call BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge::
	frontier_checkairshow
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	arena_save 0
	playse SE_SAVE
	waitse
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge
	message BattleFrontier_BattleArenaLobby_Text_RecordLastMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge
	case 0, BattleFrontier_BattleArenaLobby_EventScript_RecordMatch
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge

BattleFrontier_BattleArenaLobby_EventScript_RecordMatch::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge::
	return

BattleFrontier_BattleArenaLobby_EventScript_ResumeChallenge::
	lockall
	message BattleFrontier_BattleArenaLobby_Text_LookingForwardToArrivalSaveGame
	waitmessage
	arena_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto BattleFrontier_BattleArenaLobby_EventScript_EnterChallenge

BattleFrontier_BattleArenaLobby_EventScript_Attendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_ARENA
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattleArenaLobby_Text_WelcomeToBattleArena, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_AskTakeChallenge::
	message BattleFrontier_BattleArenaLobby_Text_WishToTakeChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattleArenaLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattleArenaLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleArenaLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_OkayToSave, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattleArenaLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	arena_init
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleArenaLobby_EventScript_CancelChallengeSaveFailed
BattleFrontier_BattleArenaLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattleArenaLobby_Text_GuideYouToArena, MSGBOX_DEFAULT
	closemessage
	frontier_get FRONTIER_DATA_LVL_MODE
	call_if_eq VAR_RESULT, FRONTIER_LVL_50, BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLv50
	call_if_eq VAR_RESULT, FRONTIER_LVL_OPEN, BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLvOpen
	warp MAP_BATTLE_FRONTIER_BATTLE_ARENA_CORRIDOR, 9, 13
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattleArenaLobby_EventScript_ExplainChallenge::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainChallenge, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_AskTakeChallenge

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLv50::
	applymovement LOCALID_ARENA_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToLeftDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToLeftDoor
	waitmovement 0
	opendoor 2, 2
	waitdooranim
	applymovement LOCALID_ARENA_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 2, 2
	waitdooranim
	return

BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToLeftDoor:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToLeftDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLvOpen::
	applymovement LOCALID_ARENA_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToRightDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToRightDoor
	waitmovement 0
	opendoor 11, 2
	waitdooranim
	applymovement LOCALID_ARENA_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 11, 2
	waitdooranim
	return

BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToRightDoor:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToRightDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

BattleFrontier_BattleArenaLobby_EventScript_ShowResults::
	lockall
	frontier_results FRONTIER_FACILITY_ARENA
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_Youngster::
	msgbox BattleFrontier_BattleArenaLobby_Text_BadIdeaToNotAttack, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Man::
	msgbox BattleFrontier_BattleArenaLobby_Text_LandingHitsWorked, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Camper::
	msgbox BattleFrontier_BattleArenaLobby_Text_MatchWasDeclaredDraw, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Woman::
	msgbox BattleFrontier_BattleArenaLobby_Text_OrderOfMonsImportant, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattleArenaLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattleArenaLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 17, 2, MULTI_BATTLE_ARENA_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaLobby_EventScript_BattleRules
	case 1, BattleFrontier_BattleArenaLobby_EventScript_MindRules
	case 2, BattleFrontier_BattleArenaLobby_EventScript_SkillRules
	case 3, BattleFrontier_BattleArenaLobby_EventScript_BodyRules
	case 4, BattleFrontier_BattleArenaLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_ExitRules
	end

BattleFrontier_BattleArenaLobby_EventScript_BattleRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainBattleRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_MindRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainMindRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_SkillRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainSkillRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_BodyRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainBodyRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattleArenaLobby_Text_WelcomeToBattleArena:
	.string "Tempat di mana semangat bertarung\n"
	.string "para TRAINER diuji!\p"
	.string "Selamat datang di BATTLE ARENA!\p"
	.string "Aku pemandumu untuk Turnamen Set KO!$"

BattleFrontier_BattleArenaLobby_Text_WishToTakeChallenge:
	.string "Sekarang, apa kamu ingin mengambil\n"
	.string "tantangan BATTLE ARENA?$"

BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge:
	.string "Kami menantikan tantanganmu di\n"
	.string "kesempatan lain!$"

BattleFrontier_BattleArenaLobby_Text_ExplainChallenge:
	.string "Di BATTLE ARENA, kami mengadakan\n"
	.string "Turnamen Set KO.\p"
	.string "Semua peserta masuk dengan tim\n"
	.string "berisi tiga POKéMON.\p"
	.string "Ketiga POKéMON harus diatur dalam\n"
	.string "urutan kemunculannya.\p"
	.string "Selama pertarungan, POKéMON akan\n"
	.string "muncul satu per satu sesuai urutan.\p"
	.string "Sekali POKéMON masuk ke pertarungan,\n"
	.string "ia harus tetap di sana sampai selesai.\p"
	.string "Jika pertarungan belum selesai dalam\n"
	.string "tiga giliran, akan ada penilaian.\p"
	.string "Jika kamu ingin menghentikan tantangan,\n"
	.string "silakan simpan permainan.\p"
	.string "Jika tidak disimpan, kamu tidak akan\n"
	.string "bisa melanjutkan tantanganmu.\p"
	.string "Jika kamu berhasil mengalahkan tujuh\n"
	.string "TRAINER berturut-turut,\l"
	.string "kami akan memberimu Battle Points.$"

BattleFrontier_BattleArenaLobby_Text_OkayToSave:
	.string "Sebelum menuju ke BATTLE ARENA,\n"
	.string "kamu harus menyimpan. Boleh?$"

BattleFrontier_BattleArenaLobby_Text_WhichLevelMode:
	.string "BATTLE ARENA menawarkan dua level\n"
	.string "tantangan, Level 50 dan Level Terbuka.\l"
	.string "Mana pilihanmu?$"

BattleFrontier_BattleArenaLobby_Text_SelectThreeMons:
	.string "Baiklah, sekarang pilih tiga\n"
	.string "POKéMON-mu.$"

BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLvOpen:
	.string "Penantang yang terhormat!\p"
	.string "Kamu tidak memiliki tiga POKéMON\n"
	.string "yang dibutuhkan untuk masuk.\p"
	.string "Untuk lolos, kamu harus membawa tiga\n"
	.string "jenis POKéMON yang berbeda.\p"
	.string "Mereka juga tidak boleh memegang\n"
	.string "jenis item yang sama.\p"
	.string "TELUR{STR_VAR_1} tidak memenuhi syarat.\p"
	.string "Jika persiapanmu sudah selesai,\n"
	.string "silakan kembali.$"

BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLv50:
	.string "Penantang yang terhormat!\p"
	.string "Kamu tidak memiliki tiga POKéMON\n"
	.string "yang dibutuhkan untuk masuk.\p"
	.string "Untuk lolos, kamu harus membawa tiga\n"
	.string "jenis POKéMON yang berbeda.\p"
	.string "Ketiga POKéMON yang berbeda itu\n"
	.string "harus Level 50 atau lebih rendah.\p"
	.string "Mereka juga tidak boleh memegang\n"
	.string "jenis item yang sama.\p"
	.string "TELUR{STR_VAR_1} tidak memenuhi syarat.\p"
	.string "Jika persiapanmu sudah selesai,\n"
	.string "silakan kembali.$"

BattleFrontier_BattleArenaLobby_Text_GuideYouToArena:
	.string "Sekarang akan kupandu kamu ke\n"
	.string "BATTLE ARENA.$"

BattleFrontier_BattleArenaLobby_Text_DidntSaveBeforeShuttingDown:
	.string "Penantang yang terhormat!\p"
	.string "Kamu tidak menyimpan permainan sebelum\n"
	.string "mematikan, bukan?\p"
	.string "Sangat disayangkan, tapi itu\n"
	.string "mengakibatkan diskualifikasi\l"
	.string "dari tantanganmu.\p"
	.string "Tentu saja, kamu boleh memulai\n"
	.string "tantangan yang baru.$"

BattleFrontier_BattleArenaLobby_Text_CongratsOnSevenWins:
	.string "Selamat atas kemenangan beruntunmu\n"
	.string "melawan tujuh TRAINER!$"

BattleFrontier_BattleArenaLobby_Text_RecordAchievement:
	.string "Pencapaianmu akan dicatat.\n"
	.string "Harap tunggu selagi aku menyimpan.$"

@ Unused
BattleFrontier_BattleArenaLobby_Text_PresentYouWithPrize:
	.string "Untuk merayakan 7 kemenanganmu,\n"
	.string "kami berikan hadiah ini.$"

@ Unused
BattleFrontier_BattleArenaLobby_Text_ReceivedPrize:
	.string "{PLAYER} mendapatkan hadiah\n"
	.string "{STR_VAR_1}.$"

@ Unused
BattleFrontier_BattleArenaLobby_Text_BagFullReturnForPrize:
	.string "Oh?\n"
	.string "TAS-mu sepertinya penuh.\p"
	.string "Kosongkan dulu dan kembalilah\n"
	.string "untuk mengambil hadiahmu.$"

BattleFrontier_BattleArenaLobby_Text_ThankYouWaitWhileSave:
	.string "Terima kasih banyak atas partisipasinya!\p"
	.string "Harap tunggu selagi aku menyimpan.$"

BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2:
	.string "Kami menantikan tantanganmu di\n"
	.string "kesempatan lain!$"

BattleFrontier_BattleArenaLobby_Text_LookingForwardToArrivalSaveGame:
	.string "Kami telah menantikan\n"
	.string "kedatanganmu.\p"
	.string "Sebelum kupandu ke BATTLE ARENA,\n"
	.string "aku harus menyimpan permainan.\l"
	.string "Harap tunggu.$"

BattleFrontier_BattleArenaLobby_Text_RecordLastMatch:
	.string "Perlukah kucatat pertarungan BATTLE\n"
	.string "ARENA terakhirmu di FRONTIER PASS?$"

BattleFrontier_BattleArenaLobby_Text_BadIdeaToNotAttack:
	.string "Aku kalah karena keputusan WASIT…\p"
	.string "Sepertinya bukan ide bagus hanya\n"
	.string "bertahan dan tidak menyerang…$"

BattleFrontier_BattleArenaLobby_Text_LandingHitsWorked:
	.string "Aku menang dalam penilaian!\p"
	.string "Terus-menerus menyerang POKéMON\n"
	.string "lawan ternyata berhasil!$"

BattleFrontier_BattleArenaLobby_Text_MatchWasDeclaredDraw:
	.string "Pertarungan kami dinyatakan seri.\p"
	.string "Saat waktu habis, HP POKéMON-ku dan\n"
	.string "lawan kira-kira sama banyaknya.$"

BattleFrontier_BattleArenaLobby_Text_OrderOfMonsImportant:
	.string "Di BATTLE ARENA, urutan POKéMON\n"
	.string "sangatlah penting.\p"
	.string "Misalnya, jika POKéMON pertamamu\n"
	.string "lemah terhadap tipe tertentu,\l"
	.string "coba pasang POKéMON kedua yang punya\l"
	.string "jurus super efektif melawannya.\p"
	.string "Kurasa itu cara yang bagus untuk\n"
	.string "membuat tim yang efektif.$"

BattleFrontier_BattleArenaLobby_Text_RulesAreListed:
	.string "Aturan Turnamen Set KO terdaftar.$"

BattleFrontier_BattleArenaLobby_Text_ReadWhichHeading:
	.string "Judul mana yang ingin kamu baca?$"

BattleFrontier_BattleArenaLobby_Text_ExplainBattleRules:
	.string "Turnamen Set KO punya aturan khusus,\n"
	.string "tidak seperti pertarungan standar.\p"
	.string "Pertama, satu pertarungan hanya\n"
	.string "berlangsung tiga giliran.\p"
	.string "Jika hasilnya belum ditentukan setelah\n"
	.string "tiga giliran, akan ada penilaian.\p"
	.string "WASIT akan memilih pemenang\n"
	.string "berdasarkan cara POKéMON bertarung.\p"
	.string "Selain itu, POKéMON tidak bisa diganti\n"
	.string "sampai hasil pertarungannya ditentukan.$"

BattleFrontier_BattleArenaLobby_Text_ExplainMindRules:
	.string "Faktor penilaian pertama adalah “Pikiran.”\n"
	.string "Faktor ini mengevaluasi seberapa\l"
	.string "agresif para petarung.\p"
	.string "Penilaian didasarkan pada seberapa\n"
	.string "sering TRAINER memerintahkan\l"
	.string "penggunaan jurus ofensif.$"

BattleFrontier_BattleArenaLobby_Text_ExplainSkillRules:
	.string "Faktor penilaian kedua adalah “Keahlian.”\n"
	.string "Faktor ini mengevaluasi seberapa\l"
	.string "efektif jurus POKéMON digunakan.\p"
	.string "Jika jurus berhasil, peringkat\n"
	.string "Keahlian akan naik.\p"
	.string "Jika jurus gagal, peringkat Keahlian\n"
	.string "akan diturunkan.\p"
	.string "Jika itu jurus ofensif, peringkat\n"
	.string "Keahlian naik jika jurus itu “super\l"
	.string "efektif” dan turun jika “tidak\l"
	.string "terlalu efektif.”\p"
	.string "Peringkat Keahlian tidak akan naik\n"
	.string "untuk jurus seperti PROTECT dan DETECT.\p"
	.string "Jika lawan menggunakan PROTECT atau\n"
	.string "DETECT, dan POKéMON-mu gagal\l"
	.string "mengenai sasaran, peringkat Keahliannya\l"
	.string "tidak akan turun.$"

BattleFrontier_BattleArenaLobby_Text_ExplainBodyRules:
	.string "Faktor penilaian ketiga adalah “Fisik.”\n"
	.string "Faktor ini didasarkan pada berapa\l"
	.string "banyak HP yang tersisa di akhir laga.\p"
	.string "Peringkat ini memperhitungkan berapa\n"
	.string "banyak HP POKéMON di awal\l"
	.string "pertarungan, dan sisanya di akhir.$"

BattleFrontier_BattleArenaLobby_Text_CongratsOnDefeatingTycoon:
	.string "Kemenangan dari ARENA TYCOON,\n"
	.string "dan sapu bersih tujuh TRAINER!\p"
	.string "Kami ucapkan selamat atas\n"
	.string "tantanganmu yang luar biasa!$"

BattleFrontier_BattleArenaLobby_Text_PleaseAcceptBattlePoints:
	.string "Penantang yang terhormat, sebagai\n"
	.string "pengakuan atas semangat gigihmu,\l"
	.string "silakan terima Battle Point ini.$"
