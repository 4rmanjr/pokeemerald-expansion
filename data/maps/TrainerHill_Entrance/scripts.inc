TrainerHill_Entrance_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, TrainerHill_Entrance_OnResume
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, TrainerHill_Entrance_OnReturn
	map_script MAP_SCRIPT_ON_TRANSITION, TrainerHill_Entrance_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, TrainerHill_Entrance_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrainerHill_Entrance_OnFrame
	.byte 0

TrainerHill_Entrance_OnTransition:
	setflag FLAG_LANDMARK_TRAINER_HILL
	getplayerxy VAR_TEMP_D, VAR_RESULT
	end

@ Unused
TrainerHill_Entrance_OnWarp:
	end

TrainerHill_Entrance_OnResume:
	trainerhill_resumetimer
	setvar VAR_TEMP_0, 0
	trainerhill_getusingereader
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_TryFaceAttendant  @ VAR_RESULT always FALSE here
	setobjectxy LOCALID_PLAYER, 9, 6
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	end

TrainerHill_Entrance_EventScript_TryFaceAttendant::
	trainerhill_getwon
	goto_if_eq VAR_RESULT, TRUE, TrainerHill_Entrance_EventScript_PlayerDontFaceAttendant
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	end

TrainerHill_Entrance_EventScript_PlayerDontFaceAttendant::
	end

TrainerHill_Entrance_OnReturn:
	addobject LOCALID_TRAINER_HILL_NURSE
	addobject LOCALID_TRAINER_HILL_ATTENDANT
	addobject LOCALID_TRAINER_HILL_MAN
	addobject LOCALID_TRAINER_HILL_GIRL
	end

TrainerHill_Entrance_OnLoad:
	call_if_eq VAR_TEMP_D, 17, TrainerHill_Entrance_EventScript_OpenCounterDoor
	end

TrainerHill_Entrance_EventScript_OpenCounterDoor::
	setmetatile 17, 10, METATILE_TrainerHill_GreenFloorTile, FALSE
	return

TrainerHill_Entrance_OnFrame:
	map_script_2 VAR_TEMP_0, 0, TrainerHill_Entrance_EventScript_ExitChallenge
	map_script_2 VAR_TEMP_D, 17, TrainerHill_Entrance_EventScript_ExitElevator
	map_script_2 VAR_TEMP_5, 1, TrainerHill_Entrance_EventScript_EntryTrigger
	map_script_2 VAR_TEMP_1, 1, TrainerHill_EventScript_WarpToEntranceCounter
	.2byte 0

TrainerHill_Entrance_EventScript_ExitElevator::
	lockall
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PlayerExitElevator
	waitmovement 0
	setmetatile 17, 10, METATILE_TrainerHill_CounterDoor, TRUE
	special DrawWholeMapView
	playse SE_CLICK
	waitse
	setvar VAR_TEMP_D, 0
	releaseall
	end

TrainerHill_Entrance_EventScript_ExitChallenge::
	setvar VAR_TEMP_0, 1
	trainerhill_getstatus
	switch VAR_RESULT
	case TRAINER_HILL_PLAYER_STATUS_LOST, TrainerHill_Entrance_EventScript_ExitChallengeLost
	case TRAINER_HILL_PLAYER_STATUS_ECARD_SCANNED, TrainerHill_Entrance_EventScript_ExitChallengeECard
	case TRAINER_HILL_PLAYER_STATUS_NORMAL, TrainerHill_Entrance_EventScript_EndExitChallenge

TrainerHill_Entrance_EventScript_ExitChallengeLost::
	lockall
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	msgbox TrainerHill_Entrance_Text_TooBadTremendousEffort, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_PlayerExitChallenge

TrainerHill_Entrance_EventScript_ExitChallengeECard::
	lockall
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	msgbox TrainerHill_Entrance_Text_MovedReceptionHereForSwitch, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_PlayerExitChallenge::
	closemessage
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	setvar VAR_TRAINER_HILL_IS_ACTIVE, 0
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	releaseall
TrainerHill_Entrance_EventScript_EndExitChallenge::
	end

TrainerHill_Entrance_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_TRAINER_HILL_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

TrainerHill_Entrance_EventScript_Attendant::
	lock
	faceplayer
	trainerhill_inchallenge
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_ThanksForPlaying
	msgbox TrainerHill_Entrance_Text_HopeYouGiveItYourBest, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AttendantEnd

TrainerHill_Entrance_EventScript_ThanksForPlaying::
	msgbox TrainerHill_Entrance_Text_ThankYouForPlaying, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_AttendantEnd::
	release
	end

TrainerHill_Entrance_EventScript_EntryTrigger::
	lockall
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_Closed
	msgbox TrainerHill_Entrance_Text_WelcomeToTrainerHill, MSGBOX_DEFAULT
	trainerhill_getsaved
	call_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_SaveGame
	trainerhill_allfloorsused
	goto_if_eq VAR_RESULT, TRUE, TrainerHill_Entrance_EventScript_AllFloorsUsed
	msgbox TrainerHill_Entrance_Text_TrainersUpToFloorX, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AskChallengeTrainers

TrainerHill_Entrance_EventScript_AllFloorsUsed::
	msgbox TrainerHill_Entrance_Text_TrainersInEveryRoom, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_AskChallengeTrainers::
	message TrainerHill_Entrance_Text_LikeToChallengeTrainers
	waitmessage
	multichoice 15, 6, MULTI_YESNOINFO, FALSE
	switch VAR_RESULT
	case 0, TrainerHill_Entrance_EventScript_ChooseChallenge
	case 1, TrainerHill_Entrance_EventScript_CancelEntry
	case 2, TrainerHill_Entrance_EventScript_Info
	case MULTI_B_PRESSED, TrainerHill_Entrance_EventScript_CancelEntry
	end

TrainerHill_Entrance_EventScript_Info::
	msgbox TrainerHill_Entrance_Text_ExplainTrainerHill, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AskChallengeTrainers
	end

TrainerHill_Entrance_EventScript_ChooseChallenge::
	multichoice 13, 2, MULTI_TAG_MATCH_TYPE, FALSE
	switch VAR_RESULT
	case 4, TrainerHill_Entrance_EventScript_CancelEntry
	case MULTI_B_PRESSED, TrainerHill_Entrance_EventScript_CancelEntry
	trainerhill_setmode VAR_RESULT
	setvar VAR_TRAINER_HILL_IS_ACTIVE, 1
	setvar VAR_TEMP_5, 0
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	msgbox TrainerHill_Entrance_Text_TimeProgessGetSetGo, MSGBOX_DEFAULT
	trainerhill_start
	releaseall
	end

TrainerHill_Entrance_EventScript_CancelEntry::
	setvar VAR_TEMP_5, 0
	msgbox TrainerHill_Entrance_Text_PleaseVisitUsAgain, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

TrainerHill_Entrance_EventScript_SaveGame::
	msgbox TrainerHill_Entrance_Text_SaveGameBeforeEnter, MSGBOX_DEFAULT
	trainerhill_setsaved
	setvar VAR_TEMP_5, 1
	call Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_SaveFailed
	trainerhill_setsaved
	return

TrainerHill_Entrance_EventScript_SaveFailed::
	trainerhill_clearsaved
	goto TrainerHill_Entrance_EventScript_CancelEntry
	end

TrainerHill_Entrance_EventScript_Closed::
	msgbox TrainerHill_Entrance_Text_StillGettingReady, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

TrainerHill_Entrance_Movement_PlayerFaceAttendant:
	face_right
	step_end

TrainerHill_Entrance_Movement_PushPlayerBackFromCounter:
	walk_down
	step_end

@ Unused
TrainerHill_Entrance_Movement_FaceUp:
	face_up
	step_end

TrainerHill_Entrance_Movement_PlayerExitElevator:
	walk_down
	walk_down
	step_end

TrainerHill_Entrance_EventScript_Records::
	lockall
	fadescreen FADE_TO_BLACK
	special ShowTrainerHillRecords
	waitstate
	releaseall
	end

TrainerHill_Entrance_EventScript_Man::
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_ManTrainerHillClosed
	msgbox TrainerHill_Entrance_Text_WhatSortOfTrainersAreAhead, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_ManTrainerHillClosed::
	msgbox TrainerHill_Entrance_Text_CantWaitToTestTheWaters, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_Girl::
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_GirlTrainerHillClosed
	msgbox TrainerHill_Entrance_Text_FriendsTryingToReachTimeBoardTop, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_GirlTrainerHillClosed::
	msgbox TrainerHill_Entrance_Text_DoYouKnowWhenTheyOpen, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_set FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_ExpandedPokemart
	pokemart TrainerHill_Entrance_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
TrainerHill_Entrance_Pokemart_Basic:
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_X_ACCURACY
	pokemartlistend

TrainerHill_Entrance_EventScript_ExpandedPokemart::
	pokemart TrainerHill_Entrance_Pokemart_Expanded
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
TrainerHill_Entrance_Pokemart_Expanded:
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_X_ACCURACY
	pokemartlistend

TrainerHill_Entrance_Text_StillGettingReady:
	.string "Ini adalah TRAINER HILL tempat\n"
	.string "kamu bisa menikmati pertarungan tag\l"
	.string "dengan banyak TRAINER.\p"
	.string "Sayangnya, kami masih dalam persiapan.\n"
	.string "Silakan datang lagi nanti!$"

TrainerHill_Entrance_Text_WelcomeToTrainerHill:
	.string "Selamat datang!\p"
	.string "Ini adalah TRAINER HILL tempat\n"
	.string "kamu bisa menikmati pertarungan tag\l"
	.string "dengan banyak TRAINER!$"

TrainerHill_Entrance_Text_SaveGameBeforeEnter:
	.string "Apakah ini kunjungan pertamamu ke sini?\p"
	.string "Sebelum masuk, tolong simpan\n"
	.string "permainanmu.$"

TrainerHill_Entrance_Text_TrainersUpToFloorX:
	.string "Coba kulihat…\n"
	.string "TRAINER yang ada di sini sekarang adalah…\p"
	.string "Sampai lantai no. {STR_VAR_1}.$"

TrainerHill_Entrance_Text_TrainersInEveryRoom:
	.string "Coba kulihat…\n"
	.string "TRAINER yang ada di sini sekarang adalah…\p"
	.string "Sepertinya ada TRAINER berkumpul\n"
	.string "di setiap ruangan.$"

TrainerHill_Entrance_Text_LikeToChallengeTrainers:
	.string "Maukah kamu menantang TRAINER\n"
	.string "yang menunggu?$"

TrainerHill_Entrance_Text_TimeProgessGetSetGo:
	.string "Aku akan menghitung waktumu.\n"
	.string "Semoga berhasil!\p"
	.string "Siap di posisi…\p"
	.string "Siap…\p"
	.string "Mulai!$"

TrainerHill_Entrance_Text_PleaseVisitUsAgain:
	.string "Silakan kunjungi kami lagi!$"

TrainerHill_Entrance_Text_TooBadTremendousEffort:
	.string "Sayang sekali.\p"
	.string "Aku rasa kamu telah mengerahkan\n"
	.string "usaha yang luar biasa dalam pertarunganmu.\p"
	.string "Silakan kembali dan coba lagi!$"

TrainerHill_Entrance_Text_HopeYouGiveItYourBest:
	.string "Aku harap kamu memberikan yang terbaik.$"

TrainerHill_Entrance_Text_MovedReceptionHereForSwitch:
	.string "Ketika TRAINER bertukar tempat,\n"
	.string "pergerakannya bisa jadi kacau.\p"
	.string "Untuk menghindari kerumunan, kami memindahkan\n"
	.string "meja resepsionis ke sini.\p"
	.string "Maaf atas ketidaknyamanannya.$"

TrainerHill_Entrance_Text_ThankYouForPlaying:
	.string "Terima kasih sudah bermain!$"

TrainerHill_Entrance_Text_ExplainTrainerHill:
	.string "Di TRAINER HILL ini, kami mengadakan\n"
	.string "acara bernama Time Attack.\p"
	.string "Ini adalah balapan yang mengukur berapa\n"
	.string "lama kamu mencapai pemilik kami di\l"
	.string "atap dari meja ini.\p"
	.string "Waktu tercepat diposting di\n"
	.string "Time Board--cobalah bersaing dengan\l"
	.string "teman-temanmu.\p"
	.string "Dalam pertarungan TRAINER di sepanjang\n"
	.string "jalan, baik Exp. Points maupun uang tidak\l"
	.string "akan diberikan.$"

@ Unused
TrainerHill_Entrance_Text_NeedAtLeastTwoPokemon:
	.string "Oh, maaf, tapi kamu sepertinya hanya\n"
	.string "memiliki satu POKéMON bersamamu.\p"
	.string "Kamu akan membutuhkan setidaknya dua POKéMON\n"
	.string "untuk mengikuti acara ini.$"

TrainerHill_Roof_Text_YouFinallyCameBravo:
	.string "Hm! Hm!\p"
	.string "Kamu akhirnya datang!\n"
	.string "Ya, kamu sudah tiba!\p"
	.string "Tunggu! Jangan katakan itu!\n"
	.string "Aku tahu mengapa kamu datang jauh-jauh\l"
	.string "ke sini sendirian!\p"
	.string "Kamu ingin bertemu denganku, pemilik\n"
	.string "TRAINER HILL, karena…\p"
	.string "Kamu ingin membentuk tim tag denganku!\n"
	.string "Wa-hoo!\p"
	.string "…Eh?\n"
	.string "Bukan itu?\p"
	.string "Ngomong-ngomong, aku memperhatikanmu\n"
	.string "saat kamu naik. Pertarungan yang luar biasa!\n"
	.string "Bravo, sungguh!$"

TrainerHill_Roof_Text_HaveTheMostMarvelousGift:
	.string "Untuk seseorang yang luar biasa sepertimu,\n"
	.string "aku punya hadiah yang paling luar biasa!$"

TrainerHill_Roof_Text_FullUpBeBackLaterForThis:
	.string "Oh, tidak, sudah penuh barang!\n"
	.string "Kamu akan kembali nanti untuk ini!$"

TrainerHill_Roof_Text_GotHereMarvelouslyQuickly:
	.string "Oh, tunggu sebentar! Apakah kamu tiba\n"
	.string "di sini dengan sangat cepat?\p"
	.string "Betapa luar biasa! Kamu tidak perlu\n"
	.string "terburu-buru untuk menemuiku!\p"
	.string "Itu sangat menyenangkan. Aku akan meminta\n"
	.string "Time Board di resepsionis diperbarui!$"

TrainerHill_Roof_Text_YouWerentVeryQuick:
	.string "Tapi, oh…\n"
	.string "Kamu tidak terlalu cepat sampai di sini.$"

TrainerHill_Roof_Text_ArriveZippierNextTime:
	.string "Mungkin akan lebih menyenangkan bagiku\n"
	.string "jika kamu tiba lebih cepat lain kali.\p"
	.string "Kalau begitu, aku akan senang membentuk\n"
	.string "tim tag denganmu!\p"
	.string "Sampai jumpa lagi, amigo!$"

@ Unused
TrainerHill_Roof_Text_BuiltTrainerHillToFindPartner:
	.string "Aku membangun TRAINER HILL hanya\n"
	.string "untuk satu alasan dan satu-satunya!\p"
	.string "Untuk menemukan partner paling cocok\n"
	.string "untuk membentuk tim tag denganku!$"

TrainerHill_Entrance_Text_ChallengeTime:
	.string "{STR_VAR_1} menit. {STR_VAR_2}.{STR_VAR_3} detik.$"

TrainerHill_Entrance_Text_WhatSortOfTrainersAreAhead:
	.string "Siapa tahu TRAINER macam apa\n"
	.string "dan kombinasi POKéMON apa yang menanti?\p"
	.string "Yang aku tahu hanyalah aku akan menyingkirkan\n"
	.string "siapa pun yang menghalangi jalanku!$"

TrainerHill_Entrance_Text_CantWaitToTestTheWaters:
	.string "Aku dengar TRAINER tangguh datang ke\n"
	.string "TRAINER HILL ini dari seluruh penjuru.\p"
	.string "Aku tidak sabar untuk mencoba!$"

TrainerHill_Entrance_Text_FriendsTryingToReachTimeBoardTop:
	.string "Apakah kamu melihat Time Board di sana?\p"
	.string "Teman-temanku dan aku mencoba melihat\n"
	.string "siapa yang bisa mencapai puncak dalam waktu tersingkat.$"

TrainerHill_Entrance_Text_DoYouKnowWhenTheyOpen:
	.string "Apakah kamu tahu kapan mereka akan\n"
	.string "membuka tempat ini?\p"
	.string "Aku menunggu di sini untuk menjadi\n"
	.string "penantang pertama!$"

TrainerHill_Elevator_Text_ReturnToReception:
	.string "Maukah kamu kembali ke\n"
	.string "meja resepsionis?$"
