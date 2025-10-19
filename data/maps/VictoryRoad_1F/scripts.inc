VictoryRoad_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VictoryRoad_1F_OnTransition
	.byte 0

VictoryRoad_1F_OnTransition:
	call_if_eq VAR_VICTORY_ROAD_1F_STATE, 1, VictoryRoad_1F_EventScript_SetEntranceWallyPos1
	call_if_eq VAR_VICTORY_ROAD_1F_STATE, 2, VictoryRoad_1F_EventScript_SetEntranceWallyPos2
	end

VictoryRoad_1F_EventScript_SetEntranceWallyPos1::
	setobjectxyperm LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, 2, 24
	setobjectmovementtype LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, MOVEMENT_TYPE_FACE_DOWN
	return

VictoryRoad_1F_EventScript_SetEntranceWallyPos2::
	setobjectxyperm LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, 3, 24
	setobjectmovementtype LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, MOVEMENT_TYPE_FACE_DOWN
	return

VictoryRoad_1F_EventScript_WallyBattleTrigger1::
	lockall
	setvar VAR_0x8008, 1
	addobject LOCALID_VICTORY_ROAD_ENTRANCE_WALLY
	applymovement LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, VictoryRoad_1F_Movement_WallyApproachPlayer1
	waitmovement 0
	goto VictoryRoad_1F_EventScript_WallyEntranceBattle
	end

VictoryRoad_1F_EventScript_WallyBattleTrigger2::
	lockall
	setvar VAR_0x8008, 2
	addobject LOCALID_VICTORY_ROAD_ENTRANCE_WALLY
	applymovement LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, VictoryRoad_1F_Movement_WallyApproachPlayer2
	waitmovement 0
	goto VictoryRoad_1F_EventScript_WallyEntranceBattle
	end

VictoryRoad_1F_EventScript_WallyEntranceBattle::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox VictoryRoad_1F_Text_WallyNotGoingToLoseAnymore, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_VR_1, VictoryRoad_1F_Text_WallyEntranceDefeat
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_VICTORY_ROAD_ENTRANCE_WALLY
	copyobjectxytoperm LOCALID_VICTORY_ROAD_ENTRANCE_WALLY
	setflag FLAG_DEFEATED_WALLY_VICTORY_ROAD
	copyvar VAR_VICTORY_ROAD_1F_STATE, VAR_0x8008
	releaseall
	end

VictoryRoad_1F_Movement_WallyApproachPlayer1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

VictoryRoad_1F_Movement_WallyApproachPlayer2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

@ This Wally appears near the entrance once his battle is triggered and remains there until the Hall of Fame is entered
VictoryRoad_1F_EventScript_EntranceWally::
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_NPC
	end

@ This Wally appears and remains at the exit after the Hall of Fame is entered
VictoryRoad_1F_EventScript_ExitWally::
	trainerbattle_single TRAINER_WALLY_VR_2, VictoryRoad_1F_Text_WallyIntro, VictoryRoad_1F_Text_WallyDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, VictoryRoad_1F_EventScript_RematchWally
	msgbox VictoryRoad_1F_Text_WallyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_RematchWally::
	trainerbattle_rematch TRAINER_WALLY_VR_2, VictoryRoad_1F_Text_WallyIntro, VictoryRoad_1F_Text_WallyDefeat
	msgbox VictoryRoad_1F_Text_WallyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Edgar::
	trainerbattle_single TRAINER_EDGAR, VictoryRoad_1F_Text_EdgarIntro, VictoryRoad_1F_Text_EdgarDefeat
	msgbox VictoryRoad_1F_Text_EdgarPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Albert::
	trainerbattle_single TRAINER_ALBERT, VictoryRoad_1F_Text_AlbertIntro, VictoryRoad_1F_Text_AlbertDefeat
	msgbox VictoryRoad_1F_Text_AlbertPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Hope::
	trainerbattle_single TRAINER_HOPE, VictoryRoad_1F_Text_HopeIntro, VictoryRoad_1F_Text_HopeDefeat
	msgbox VictoryRoad_1F_Text_HopePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Quincy::
	trainerbattle_single TRAINER_QUINCY, VictoryRoad_1F_Text_QuincyIntro, VictoryRoad_1F_Text_QuincyDefeat
	msgbox VictoryRoad_1F_Text_QuincyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Katelynn::
	trainerbattle_single TRAINER_KATELYNN, VictoryRoad_1F_Text_KatelynnIntro, VictoryRoad_1F_Text_KatelynnDefeat
	msgbox VictoryRoad_1F_Text_KatelynnPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_Text_WallyNotGoingToLoseAnymore:
	.string "WALLY: Hai! {PLAYER}!\p"
	.string "Aku yakin kamu terkejut melihatku di sini!\p"
	.string "Aku berhasil sampai di sini, dan itu\n"
	.string "semua berkat kamu!\p"
	.string "{PLAYER}, kekalahan darimu waktu itu\n"
	.string "membuatku lebih kuat!\p"
	.string "Tapi aku tidak akan kalah lagi!\p"
	.string "Aku akan menang! Demi POKéMON yang\n"
	.string "memberiku keberanian dan kekuatan!\p"
	.string "Oke… Aku datang!$"

VictoryRoad_1F_Text_WallyEntranceDefeat:
	.string "Wow!\n"
	.string "{PLAYER}, kamu memang kuat!$"

VictoryRoad_1F_Text_WallyPostEntranceBattle:
	.string "WALLY: Aku tidak bisa mengalahkanmu hari\n"
	.string "ini, {PLAYER}, tapi suatu saat nanti, aku\l"
	.string "akan menyusulmu!$"

VictoryRoad_1F_Text_WallyIntro:
	.string "WALLY: Hai! {PLAYER}!\p"
	.string "Aku sudah menjadi lebih kuat sejak\n"
	.string "terakhir kali! Aku ingin menunjukkannya padamu, {PLAYER}!\p"
	.string "Oke… Aku datang!$"

VictoryRoad_1F_Text_WallyDefeat:
	.string "Wow!\n"
	.string "{PLAYER}, kamu memang kuat!$"

VictoryRoad_1F_Text_WallyPostBattle:
	.string "WALLY: Aku tidak bisa mengalahkanmu kali\n"
	.string "ini juga… Tapi suatu saat nanti, {PLAYER},\l"
	.string "aku akan menyusulmu…\p"
	.string "Dan menantang POKéMON LEAGUE!$"

VictoryRoad_1F_Text_EdgarIntro:
	.string "Aku sudah sampai sejauh ini beberapa kali,\n"
	.string "tapi bagian terakhir ini sangat panjang…$"

VictoryRoad_1F_Text_EdgarDefeat:
	.string "Impianku berakhir di sini lagi…$"

VictoryRoad_1F_Text_EdgarPostBattle:
	.string "Kamu sudah sampai sejauh ini. Terus\n"
	.string "pertahankan momentum dan jadilah\l"
	.string "CHAMPION! Jika ada yang bisa, itu kamu!$"

VictoryRoad_1F_Text_AlbertIntro:
	.string "Aku tidak datang sejauh ini untuk kalah sekarang.\n"
	.string "Kemungkinan itu tidak ada!$"

VictoryRoad_1F_Text_AlbertDefeat:
	.string "Tidak mungkin…\n"
	.string "Aku kalah?$"

VictoryRoad_1F_Text_AlbertPostBattle:
	.string "Aku kalah di sini…\p"
	.string "Itu berarti aku tidak memiliki kualifikasi\n"
	.string "untuk menjadi CHAMPION…$"

VictoryRoad_1F_Text_HopeIntro:
	.string "Jalan yang tampaknya tak terbatas dan\n"
	.string "keras ini sesuai dengan namanya, VICTORY.$"

VictoryRoad_1F_Text_HopeDefeat:
	.string "Gaya bertarungmu luar biasa…$"

VictoryRoad_1F_Text_HopePostBattle:
	.string "Kamu sepertinya punya potensi untuk\n"
	.string "menjadi CHAMPION.$"

VictoryRoad_1F_Text_QuincyIntro:
	.string "Apa itu VICTORY ROAD?\n"
	.string "Aku akan memberitahumu jika kamu menang!$"

VictoryRoad_1F_Text_QuincyDefeat:
	.string "Oke!\n"
	.string "Bagus sekali!$"

VictoryRoad_1F_Text_QuincyPostBattle:
	.string "Melewati sini dengan aman--itulah\n"
	.string "ujian terakhir bagi setiap TRAINER yang\l"
	.string "ingin menjadi POKéMON CHAMPION.\p"
	.string "Itulah mengapa disebut VICTORY\n"
	.string "ROAD.$"

VictoryRoad_1F_Text_KatelynnIntro:
	.string "Aku tidak punya apa-apa untuk dikatakan\n"
	.string "kepada siapa pun yang sudah sejauh ini. Ayo!$"

VictoryRoad_1F_Text_KatelynnDefeat:
	.string "Ini memalukan…$"

VictoryRoad_1F_Text_KatelynnPostBattle:
	.string "Hmph, silakan saja.\n"
	.string "Lihat saja apakah aku peduli.$"
