SlateportCity_BattleTentCorridor_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SlateportCity_BattleTentCorridor_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SlateportCity_BattleTentCorridor_OnWarp
	.byte 0

	@ This is Slateport Tent's version of the Battle Factory Pre-Battle Room

SlateportCity_BattleTentCorridor_OnWarp:
	map_script_2 VAR_TEMP_1, 0, SlateportCity_BattleTentCorridor_EventScript_SetUpObjects
	.2byte 0

SlateportCity_BattleTentCorridor_EventScript_SetUpObjects::
	setvar VAR_TEMP_1, 1
	goto_if_ne VAR_0x8006, 1, SlateportCity_BattleTentCorridor_EventScript_TurnPlayerNorth
	setobjectxy LOCALID_SLATEPORT_TENT_CORRIDOR_ATTENDANT, 2, 2
	turnobject LOCALID_SLATEPORT_TENT_CORRIDOR_ATTENDANT, DIR_SOUTH
SlateportCity_BattleTentCorridor_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

SlateportCity_BattleTentCorridor_OnFrame:
	map_script_2 VAR_TEMP_0, 0, SlateportCity_BattleTentCorridor_EventScript_EnterCorridor
	.2byte 0

SlateportCity_BattleTentCorridor_EventScript_EnterCorridor::
	goto_if_eq VAR_0x8006, 1, SlateportCity_BattleTentCorridor_EventScript_ReturnToRoomFromBattle
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_SLATEPORT_TENT_CORRIDOR_ATTENDANT, SlateportCity_BattleTentCorridor_Movement_AttendantEnter
	applymovement LOCALID_PLAYER, SlateportCity_BattleTentCorridor_Movement_PlayerEnter
	waitmovement 0
	goto_if_eq VAR_0x8006, 2, SlateportCity_BattleTentCorridor_EventScript_ResumeChallenge
	slateporttent_generaterentalmons
	slateporttent_generateopponentmons
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_HoldMonsChooseFromSelection, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	slateporttent_rentmons
	waitstate
SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom::
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_RightThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_TENT_CORRIDOR_ATTENDANT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor 2, 1
	waitdooranim
	applymovement LOCALID_SLATEPORT_TENT_CORRIDOR_ATTENDANT, SlateportCity_BattleTentCorridor_Movement_AttendantExit
	applymovement LOCALID_PLAYER, SlateportCity_BattleTentCorridor_Movement_PlayerExit
	waitmovement 0
	closedoor 2, 1
	waitdooranim
	warp MAP_SLATEPORT_CITY_BATTLE_TENT_BATTLE_ROOM, 4, 4
	waitstate
	end

SlateportCity_BattleTentCorridor_EventScript_ReturnToRoomFromBattle::
	factory_setopponentmons
	factory_resethelditems
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_LetUsRestoreMons, MSGBOX_DEFAULT
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent::
	frontier_get FRONTIER_DATA_BATTLE_NUM
	call_if_eq VAR_RESULT, 1, SlateportCity_BattleTentCorridor_EventScript_ReadyFor2ndOpponent
	call_if_eq VAR_RESULT, 2, SlateportCity_BattleTentCorridor_EventScript_ReadyFor3rdOpponent
	multichoice 20, 6, MULTI_GO_ON_REST_RETIRE, TRUE
	switch VAR_RESULT
	case 0, SlateportCity_BattleTentCorridor_EventScript_AskSwapMon
	case 1, SlateportCity_BattleTentCorridor_EventScript_AskPauseChallenge
	case 2, SlateportCity_BattleTentCorridor_EventScript_AskRetireChallenge

SlateportCity_BattleTentCorridor_EventScript_AskPauseChallenge::
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_SaveAndQuitGame, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent
	case YES, SlateportCity_BattleTentCorridor_EventScript_PauseChallenge
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_EventScript_AskRetireChallenge::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_RetireFromChallenge
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent
	case 0, SlateportCity_BattleTent_EventScript_WarpToLobbyLost
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_EventScript_AskSwapMon::
	slateporttent_generateopponentmons
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_LikeToSwapMon, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom
	case YES, SlateportCity_BattleTentCorridor_EventScript_SwapMons
	case MULTI_B_PRESSED, SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom

SlateportCity_BattleTentCorridor_EventScript_SwapMons::
	fadescreen FADE_TO_BLACK
	slateporttent_swapmons
	waitstate
	goto_if_eq VAR_RESULT, 1, SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom
	msgbox BattleFrontier_BattleFactoryPreBattleRoom_Text_YourSwapIsComplete, MSGBOX_DEFAULT
	goto SlateportCity_BattleTentCorridor_EventScript_EnterBattleRoom

SlateportCity_BattleTentCorridor_EventScript_ReadyFor2ndOpponent::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor2ndOpponent
	waitmessage
	return

SlateportCity_BattleTentCorridor_EventScript_ReadyFor3rdOpponent::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_ReadyFor3rdOpponent
	waitmessage
	return

SlateportCity_BattleTentCorridor_EventScript_PauseChallenge::
	message BattleFrontier_BattleFactoryPreBattleRoom_Text_SavingDataPleaseWait
	waitmessage
	slateporttent_save CHALLENGE_STATUS_PAUSED
	playse SE_SAVE
	waitse
	fadescreen FADE_TO_BLACK
	frontier_reset
	end

SlateportCity_BattleTentCorridor_EventScript_ResumeChallenge::
	special SavePlayerParty
	factory_setparties 0
	goto SlateportCity_BattleTentCorridor_EventScript_AskReadyForOpponent

SlateportCity_BattleTentCorridor_Movement_PlayerEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SlateportCity_BattleTentCorridor_Movement_PlayerExit:
	walk_up
	walk_up
	set_invisible
	step_end

SlateportCity_BattleTentCorridor_Movement_AttendantEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

SlateportCity_BattleTentCorridor_Movement_AttendantExit:
	walk_up
	set_invisible
	step_end

@ Leftover text from when this was a Contest Hall in R/S
@ Unused
SlateportCity_ContestHall_Text_AdviceForContests:
	.string "Mau sedikit nasihat berguna\n"
	.string "untuk CONTEST?\p"
	.string "Menggunakan gerakan tertentu setelah\n"
	.string "jenis gerakan tertentu kadang-kadang\l"
	.string "membuatmu mendapat perhatian ekstra.\p"
	.string "Jika kamu tahu apa yang kamu lakukan,\n"
	.string "kamu bisa mendapatkan nilai tinggi dalam penampilan.\p"
	.string "Tentu saja, lawanmu mungkin akan mencoba\n"
	.string "mengganggu penampilan POKéMON-mu.$"

@ Unused
SlateportCity_ContestHall_Text_MyPapaIsContestJudge:
	.string "Papaku, dia seorang JURI CONTEST.\p"
	.string "Aku bertanya-tanya aku harus jadi apa\n"
	.string "ketika aku besar nanti, JURI atau PEMIMPIN GYM?$"

@ Unused
SlateportCity_ContestHall_Text_ImLikeMajorlyCheesed:
	.string "Hei, bung, aku agak kesal,\n"
	.string "tahu tidak. Seperti, tahu tidak, aku hanya\l"
	.string "ingin tahu mengapa POKéMON-ku\l"
	.string "tidak pernah menang, tahu tidak, seperti, hei?\p"
	.string "Jadi, seperti, aku memberikan JURI\n"
	.string "pendapatku, tahu tidak, itu gratis.\p"
	.string "Dan dia tidak mau mendengarku, seperti, hei!\n"
	.string "Jadi, seperti, sangat menyebalkan, bung!\p"
	.string "Hei, seperti, kamu! Diam, tahu tidak?\n"
	.string "Pokoknya, tahu tidak, ambil ini!$"

@ Unused
SlateportCity_ContestHall_Text_ExplainTorment:
	.string "Itu, seperti, TM41, tahu tidak?\n"
	.string "Hei, itu TORMENT, kamu mendengarku?\p"
	.string "Seperti, itu tidak akan membiarkan\n"
	.string "lawan menggunakan gerakan yang sama dua kali berturut-turut, lihat?\p"
	.string "Hei, sekarang, dengarkan aku, seperti,\n"
	.string "aku tidak akan menyiksamu!$"

@ Unused
SlateportCity_ContestHall_Text_MCStepUpTakePartInContest:
	.string "MC: Oh, ya ampun!\n"
	.string "Bukankah itu POKéMON yang hebat?\p"
	.string "Silakan! Maju dan ambil\n"
	.string "bagian dalam CONTEST kami yang luar biasa!\p"
	.string "Kamu akan berhasil! Aku yakin!\n"
	.string "Mataku tidak pernah salah!$"

@ Unused
SlateportCity_ContestHall_Text_JudgeWouldntDoToMissContest:
	.string "JURI: Nah, halo!\n"
	.string "Aku lihat kamu adalah seorang TRAINER!\p"
	.string "Kalau begitu, tidak baik bagimu\n"
	.string "untuk melewatkan POKéMON CONTEST!\p"
	.string "Dapatkan CONTEST PASS di VERDANTURF\n"
	.string "CITY dan masuk kapan saja!$"

@ Unused
SlateportCity_ContestHall_Text_ItsAppealTime:
	.string "Waktunya penampilan!\n"
	.string "Apa yang harus aku tampilkan lebih dulu?$"

@ Unused
SlateportCity_ContestHall_Text_DidntPayAttentionToAppeal:
	.string "Mereka tidak terlalu memperhatikan\n"
	.string "penampilan POKéMON-ku…\p"
	.string "Huh, JURI itu, dia tidak tahu\n"
	.string "hal yang bagus saat melihatnya.$"

@ Unused
SlateportCity_ContestHall_Text_RewardWithSageAdvice:
	.string "Oh, hai! Kamu pasti penggemar berat\n"
	.string "sampai bisa sedekat ini dengan aksi.\p"
	.string "Aku akan menghargai antusiasmemu dengan\n"
	.string "nasihat bijak ini.\p"
	.string "Jika sebuah gerakan berjalan sangat baik,\n"
	.string "penonton akan sangat antusias.\p"
	.string "POKéMON yang tampil tepat\n"
	.string "saat semua orang bersemangat…\p"
	.string "Yah, kamu pasti berpikir sesuatu yang baik\n"
	.string "akan terjadi!$"

@ Unused
SlateportCity_ContestHall_Text_MoreFreakedOutThanMon:
	.string "Aku tidak bisa! Aku lebih ketakutan\n"
	.string "daripada POKéMON-ku.\p"
	.string "Aku menggigil dan jantungku berdebar kencang!$"

@ Unused
SlateportCity_ContestHall_Text_BattleAndContestAlike:
	.string "Pertarungan dan CONTEST tidaklah\n"
	.string "sama, tapi keduanya juga mirip.\p"
	.string "Kamu harus bekerja keras dan percaya\n"
	.string "pada POKéMON yang telah kamu latih.$"

@ Unused
SlateportCity_ContestHall_Text_MonLooksOnTopOfGame:
	.string "POKéMON itu terlihat sangat prima,\n"
	.string "ya?\p"
	.string "POKéMON yang tampil baik dalam\n"
	.string "penilaian sekunder tampaknya lebih\l"
	.string "santai saat melakukan penampilan.$"

@ Unused
SlateportCity_ContestHall_Text_MyMonBetterThanThatLot:
	.string "Lihatlah pemandangan menyedihkan itu?\p"
	.string "Heh, POKéMON-ku jelas lebih baik\n"
	.string "daripada yang itu!$"

@ Unused
SlateportCity_ContestHall_Text_GetUrgeToMoveWithMon:
	.string "Tidakkah kamu merasa ingin bergerak\n"
	.string "bersama POKéMON jika mereka menampilkan\l"
	.string "penampilan yang energik?$"

@ Unused
SlateportCity_ContestHall_Text_HyperRankStage:
	.string "POKéMON CONTESTS\n"
	.string "TAHAP HYPER RANK!$"

