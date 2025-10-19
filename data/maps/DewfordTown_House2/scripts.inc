DewfordTown_House2_MapScripts::
	.byte 0

DewfordTown_House2_EventScript_Man::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SILK_SCARF, DewfordTown_House2_EventScript_ExplainSilkScarf
	msgbox DewfordTown_House2_Text_WantYouToHaveSilkScarf, MSGBOX_DEFAULT
	giveitem ITEM_SILK_SCARF
	goto_if_eq VAR_RESULT, FALSE, DewfordTown_House2_EventScript_NoRoomForScarf
	setflag FLAG_RECEIVED_SILK_SCARF
	release
	end

DewfordTown_House2_EventScript_NoRoomForScarf::
	msgbox DewfordTown_House2_Text_NoRoom, MSGBOX_DEFAULT
	release
	end

DewfordTown_House2_EventScript_ExplainSilkScarf::
	msgbox DewfordTown_House2_Text_ExplainSilkScarf, MSGBOX_DEFAULT
	release
	end

DewfordTown_House2_EventScript_Boy::
	msgbox DewfordTown_House2_Text_BrawlySoCool, MSGBOX_NPC
	end

DewfordTown_House2_Text_WantYouToHaveSilkScarf:
	.string "Manjakan matamu dengan ini!\p"
	.string "Ini adalah SILK SCARF. Ini adalah mode\n"
	.string "terkini, ya!\p"
	.string "Oh, aku bisa melihat matamu berbinar!\n"
	.string "Kamu menghargai gayaku yang mempesona!\p"
	.string "Oh, kamu menyenangkan sekali!\n"
	.string "Ini dia. Aku ingin kamu memilikinya!$"

DewfordTown_House2_Text_NoRoom:
	.string "Oh, kamu tidak punya ruang?\p"
	.string "Sekarang, dengarkan baik-baik, SYAL ini\n"
	.string "wajib dimiliki! Kenapa, aku akan menjual\l"
	.string "semua itemku untuk mendapatkannya!$"

DewfordTown_House2_Text_ExplainSilkScarf:
	.string "SILK SCARF meningkatkan kekuatan jurus\n"
	.string "tipe NORMAL.\p"
	.string "Ini adalah SYAL luar biasa yang cocok\n"
	.string "dengan hampir semua POKéMON!$"

DewfordTown_House2_Text_BrawlySoCool:
	.string "Wow, kamu repot-repot menyeberangi lautan\n"
	.string "untuk mengunjungi DEWFORD?\p"
	.string "Apakah kamu mungkin datang ke sini karena\n"
	.string "mendengar tentang BRAWLY?\p"
	.string "Dia sangat keren…\n"
	.string "Semua orang mengidolakannya.$"

