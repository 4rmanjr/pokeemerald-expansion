BattleFrontier_BattlePikeLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePikeLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePikeLobby_OnWarp
	.byte 0

BattleFrontier_BattlePikeLobby_OnFrame:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattlePikeLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePikeLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattlePikeLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattlePikeLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattlePikeLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePikeLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattlePikeLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePikeLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattlePikeLobby_EventScript_QuitWithoutSaving::
	special HealPlayerParty
	pike_resethelditems
	lockall
	msgbox BattleFrontier_BattlePikeLobby_Text_FailedToSaveBeforeQuitting, MSGBOX_DEFAULT
	closemessage
	pike_set PIKE_DATA_WIN_STREAK, 0
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePikeLobby_EventScript_DefeatedQueen
	msgbox BattleFrontier_BattlePikeLobby_Text_PossessLuckInAbundance, MSGBOX_DEFAULT
	waitmessage
	goto BattleFrontier_BattlePikeLobby_EventScript_GiveBattlePoints

BattleFrontier_BattlePikeLobby_EventScript_DefeatedQueen::
	msgbox BattleFrontier_BattlePikeLobby_Text_SnatchedVictoryFromQueen, MSGBOX_DEFAULT
	waitmessage
BattleFrontier_BattlePikeLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	frontier_checkairshow
	pike_get PIKE_DATA_TOTAL_STREAKS
	addvar VAR_RESULT, 1
	pike_set PIKE_DATA_TOTAL_STREAKS, VAR_RESULT
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	pike_resethelditems
	message BattleFrontier_BattlePikeLobby_Text_ShallRecordResults
	waitmessage
	pike_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_LostChallenge::
	lockall
	message BattleFrontier_BattlePikeLobby_Text_ChallengeEndedRecordResults
	waitmessage
	frontier_checkairshow
	frontier_set FRONTIER_DATA_BATTLE_NUM, 0
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, FALSE
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	pike_resethelditems
	pike_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_Attendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PIKE
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattlePikeLobby_Text_WelcomeToBattlePike, MSGBOX_DEFAULT
BattleFrontier_BattlePikeLobby_EventScript_AskTakeChallenge::
	message BattleFrontier_BattlePikeLobby_Text_TakeChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePikeLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattlePikeLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattlePikeLobby_Text_WhichChallengeMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattlePikeLobby_Text_PleaseChooseThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattlePikeLobby_Text_SaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattlePikeLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_1, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	pike_init
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, TRUE
	pike_savehelditems
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	pike_savehelditems
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePikeLobby_EventScript_CancelChallengeSaveFailed
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattlePikeLobby_Text_StepThisWay, MSGBOX_DEFAULT
	closemessage
	frontier_settrainers
	call BattleFrontier_BattlePikeLobby_EventScript_WalkToCorridor
	special HealPlayerParty
	call BattleFrontier_BattlePike_EventScript_CloseCurtain
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PIKE_CORRIDOR, 6, 7
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattlePikeLobby_EventScript_ExplainChallenge::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainBattlePike, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_AskTakeChallenge

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge

BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou, MSGBOX_DEFAULT
BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattlePikeLobby_EventScript_ShowResults::
	lockall
	frontier_results FRONTIER_FACILITY_PIKE
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_WalkToCorridor::
	applymovement LOCALID_PIKE_LOBBY_ATTENDANT, BattleFrontier_BattlePikeLobby_Movement_AttendantWalkToCorridor
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePikeLobby_Movement_PlayerWalkToCorridor
	waitmovement 0
	return

BattleFrontier_BattlePikeLobby_Movement_PlayerWalkToCorridor:
	walk_up
BattleFrontier_BattlePikeLobby_Movement_AttendantWalkToCorridor:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePikeLobby_EventScript_Hiker::
	msgbox BattleFrontier_BattlePikeLobby_Text_OneRoomAwayFromGoal, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_Twin::
	msgbox BattleFrontier_BattlePikeLobby_Text_NeverHadToBattleTrainer, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_Beauty::
	msgbox BattleFrontier_BattlePikeLobby_Text_ThinkAbilitiesUsefulHere, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattlePikeLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattlePikeLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 16, 4, MULTI_BATTLE_PIKE_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePikeLobby_EventScript_RulesPokenavBag
	case 1, BattleFrontier_BattlePikeLobby_EventScript_RulesHeldItems
	case 2, BattleFrontier_BattlePikeLobby_EventScript_RulesMonOrder
	case 3, BattleFrontier_BattlePikeLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_ExitRules
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesPokenavBag::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainPokenavBagRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesHeldItems::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainHeldItemRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesMonOrder::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainMonOrderRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePikeLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattlePike_EventScript_CloseCurtain::
	playse SE_PIKE_CURTAIN_CLOSE
	special CloseBattlePikeCurtain
	waitstate
	waitse
	return

BattleFrontier_BattlePikeLobby_Text_WelcomeToBattlePike:
	.string "Tempat di mana keberuntungan TRAINER\n"
	.string "diuji…\p"
	.string "Selamat datang di BATTLE PIKE…\p"
	.string "Aku pemandumu di BATTLE PIKE…$"

BattleFrontier_BattlePikeLobby_Text_TakeChallenge:
	.string "Apa kamu ingin mengambil tantangan\n"
	.string "Battle Choice?$"

BattleFrontier_BattlePikeLobby_Text_ExplainBattlePike:
	.string "Di sini kami mengadakan acara yang\n"
	.string "kami sebut Battle Choice.\p"
	.string "Aturan Battle Choice sangat\n"
	.string "sederhana…\p"
	.string "Pilih satu dari tiga jalur dan capai\n"
	.string "ruang tujuan di ujung BATTLE PIKE.\l"
	.string "Sesederhana itu.\p"
	.string "Namun, apa yang terjadi di jalur\n"
	.string "pilihan bergantung sepenuhnya pada\l"
	.string "keberuntungan penantang…\p"
	.string "Jika kamu mencapai tujuan, kamu akan\n"
	.string "diberi hadiah Battle Points.\p"
	.string "Jika ingin menghentikan tantangan,\n"
	.string "bicaralah dengan staf kami di\l"
	.string "ruangan besar di sepanjang jalan.\p"
	.string "Jika tidak disimpan sebelum berhenti,\n"
	.string "kamu akan didiskualifikasi.$"

BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou:
	.string "Kami menantikan kedatanganmu\n"
	.string "di lain waktu…$"

BattleFrontier_BattlePikeLobby_Text_WhichChallengeMode:
	.string "Ada dua pilihan jalur, Level 50 dan\n"
	.string "Level Terbuka.\l"
	.string "Mana yang akan kamu tantang?$"

BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLv50:
	.string "Mohon maaf, tapi…\p"
	.string "Kamu tidak punya tiga POKéMON yang\n"
	.string "memenuhi syarat untuk acara ini.\p"
	.string "Kamu harus punya tiga POKéMON berbeda\n"
	.string "Level 50 atau kurang untuk masuk.\p"
	.string "Mereka juga tidak boleh memegang\n"
	.string "jenis item yang sama.\p"
	.string "TELUR{STR_VAR_1} tidak memenuhi syarat.\p"
	.string "Silakan temui aku jika\n"
	.string "kamu sudah siap…$"

BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLvOpen:
	.string "Mohon maaf, tapi…\p"
	.string "Kamu tidak punya tiga POKéMON yang\n"
	.string "memenuhi syarat untuk acara ini.\p"
	.string "Kamu harus punya tiga POKéMON\n"
	.string "berbeda untuk masuk.\p"
	.string "Mereka juga tidak boleh memegang\n"
	.string "jenis item yang sama.\p"
	.string "TELUR{STR_VAR_1} tidak memenuhi syarat.\p"
	.string "Silakan temui aku jika\n"
	.string "kamu sudah siap…$"

BattleFrontier_BattlePikeLobby_Text_PleaseChooseThreeMons:
	.string "Silakan pilih tiga POKéMON yang\n"
	.string "ingin kamu ikutkan dalam tantangan…$"

BattleFrontier_BattlePikeLobby_Text_SaveBeforeChallenge:
	.string "Sebelum memulai tantangan Battle\n"
	.string "Choice, aku harus menyimpan permainan.\l"
	.string "Apa itu tidak apa-apa?$"

BattleFrontier_BattlePikeLobby_Text_StepThisWay:
	.string "Silakan lewat sini…$"

BattleFrontier_BattlePikeLobby_Text_ChallengeEndedRecordResults:
	.string "Tantanganmu telah berakhir…\p"
	.string "Akan kucatat hasilnya.\n"
	.string "Harap tunggu…$"

BattleFrontier_BattlePikeLobby_Text_PossessLuckInAbundance:
	.string "Kamu telah menyelesaikan tantangan…\p"
	.string "Harus kuakui… Kamu tampaknya punya\n"
	.string "keberuntungan yang melimpah…$"

BattleFrontier_BattlePikeLobby_Text_ShallRecordResults:
	.string "Akan kucatat hasilnya.\n"
	.string "Harap tunggu…$"

BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints2:
	.string "Untuk merayakan penyelesaian\n"
	.string "tantangan Battle Choice, kami berikan\l"
	.string "Battle Point ini…$"

BattleFrontier_BattlePikeLobby_Text_ReachedBattlePointLimit:
	.string "Kamu tampaknya telah mencapai batas\n"
	.string "Battle Points…\p"
	.string "Silakan tukar beberapa Battle Points\n"
	.string "dengan hadiah, lalu kembali…$"

BattleFrontier_BattlePikeLobby_Text_FailedToSaveBeforeQuitting:
	.string "Mohon maaf, tapi…\p"
	.string "Kamu gagal menyimpan sebelum keluar\n"
	.string "dari tantanganmu yang terakhir.\p"
	.string "Karena itu, tantanganmu sejauh ini\n"
	.string "telah didiskualifikasi. Maafkan aku…$"

BattleFrontier_BattlePikeLobby_Text_SnatchedVictoryFromQueen:
	.string "Selamat…\p"
	.string "Kamu telah merebut kemenangan dari\n"
	.string "PIKE QUEEN dan menyelesaikan acara ini…$"

BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints:
	.string "Sebagai pengakuan atas keberuntunganmu,\n"
	.string "kami berikan Battle Point ini…$"

BattleFrontier_BattlePikeLobby_Text_OneRoomAwayFromGoal:
	.string "Arrgh! Kesempatanku hilang!\n"
	.string "Tinggal satu ruangan lagi dari tujuan!\p"
	.string "Di tempat ini, sebaiknya kamu waspada\n"
	.string "terhadap racun, beku, dan lainnya.$"

BattleFrontier_BattlePikeLobby_Text_NeverHadToBattleTrainer:
	.string "Aku sudah menyelesaikan tantangan ini\n"
	.string "10 kali, tapi tak pernah sekalipun\l"
	.string "bertarung dengan TRAINER.$"

BattleFrontier_BattlePikeLobby_Text_ThinkAbilitiesUsefulHere:
	.string "Dengar! Dengar!\p"
	.string "Tidakkah kamu pikir kemampuan spesial\n"
	.string "POKéMON akan berguna di sini?$"

BattleFrontier_BattlePikeLobby_Text_TrainersWhicheverPathIChoose:
	.string "Tempat aneh apa ini?\n"
	.string "Aku tak mengerti sama sekali!\p"
	.string "Aku sudah mengambil tantangan ini\n"
	.string "berkali-kali, tapi yang kutemui\l"
	.string "hanyalah TRAINER di jalur mana pun.$"

BattleFrontier_BattlePikeLobby_Text_RulesAreListed:
	.string "Aturan Battle Choice terdaftar.$"

BattleFrontier_BattlePikeLobby_Text_ReadWhichHeading:
	.string "Judul mana yang ingin kamu baca?$"

BattleFrontier_BattlePikeLobby_Text_ExplainPokenavBagRules:
	.string "TAS dan POKéNAV tidak dapat digunakan\n"
	.string "selama tantangan Battle Choice.$"

BattleFrontier_BattlePikeLobby_Text_ExplainHeldItemRules:
	.string "Selama tantangan Battle Choice,\n"
	.string "BERRY atau HERB yang dipegang POKéMON\l"
	.string "hanya akan efektif satu kali.$"

BattleFrontier_BattlePikeLobby_Text_ExplainMonOrderRules:
	.string "Selama tantangan Battle Choice,\n"
	.string "urutan POKéMON tidak dapat diubah.\p"
	.string "Urutan harus diatur sebelum\n"
	.string "memulai tantanganmu.$"

