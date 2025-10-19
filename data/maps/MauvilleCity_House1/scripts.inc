MauvilleCity_House1_MapScripts::
	.byte 0

MauvilleCity_House1_EventScript_RockSmashDude::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_ROCK_SMASH, MauvilleCity_House1_EventScript_ReceivedRockSmash
	msgbox MauvilleCity_House1_Text_ImRockSmashDudeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_HM_ROCK_SMASH
	setflag FLAG_RECEIVED_HM_ROCK_SMASH
	setflag FLAG_HIDE_ROUTE_111_ROCK_SMASH_TIP_GUY
	msgbox MauvilleCity_House1_Text_ExplainRockSmash, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_EventScript_ReceivedRockSmash::
	msgbox MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_Text_ImRockSmashDudeTakeThis:
	.string "Woohoo!\p"
	.string "Kudengar orang-orang memanggilku\n"
	.string "ROCK SMASH GUY, tapi menurutku itu\l"
	.string "agak merendahkan.\p"
	.string "Kurasa aku pantas lebih dihormati,\n"
	.string "mungkin seperti ROCK SMASH DUDE.\p"
	.string "Woohoo!\p"
	.string "Ngomong-ngomong, POKéMON-mu terlihat\n"
	.string "cukup kuat.\p"
	.string "Aku suka itu!\n"
	.string "Ini, ambil HIDDEN MACHINE ini!$"

MauvilleCity_House1_Text_ExplainRockSmash:
	.string "HM itu berisi ROCK SMASH.\p"
	.string "Jika kamu menemukan batu besar yang\n"
	.string "menghalangi jalanmu…\p"
	.string "Nah, gunakan jurus HM itu dan hancurkan\n"
	.string "batu-batu itu dari jalanmu!\p"
	.string "Ya, tuan! Hancurkan batu-batu itu,\n"
	.string "kataku! Woohoo!$"

MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock:
	.string "Oh, ya, jika kamu menghancurkan batu,\n"
	.string "seekor POKéMON bisa saja keluar dari\l"
	.string "persembunyian.\p"
	.string "Woohoo!$"

