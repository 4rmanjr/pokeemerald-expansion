Route114_FossilManiacsHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_FossilManiacsHouse_OnTransition
	.byte 0

Route114_FossilManiacsHouse_OnTransition:
	setflag FLAG_LANDMARK_FOSSIL_MANIACS_HOUSE
	end

Route114_FossilManiacsHouse_EventScript_FossilManiacsBrother::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_DIG, Route114_FossilManiacsHouse_EventScript_ReceivedDig
	msgbox Route114_FossilManiacsHouse_Text_HaveThisToDigLikeMyBrother, MSGBOX_DEFAULT
	giveitem ITEM_TM_DIG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_DIG
	release
	end

Route114_FossilManiacsHouse_EventScript_ReceivedDig::
	msgbox Route114_FossilManiacsHouse_Text_DigReturnsYouToEntrance, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsHouse_EventScript_RockDisplay::
	msgbox Route114_FossilManiacsHouse_Text_RocksFillDisplayCase, MSGBOX_SIGN
	end

Route114_FossilManiacsHouse_EventScript_Bookshelf::
	msgbox Route114_FossilManiacsHouse_Text_CrammedWithBooks, MSGBOX_SIGN
	end

Route114_FossilManiacsHouse_Text_HaveThisToDigLikeMyBrother:
	.string "Kakakku adalah FOSSIL MANIAC…\n"
	.string "Dia orang baik yang menyukai FOSSIL…\p"
	.string "Dia juga suka menggali lubang…\n"
	.string "Dia menggali lubang ini sendiri…\p"
	.string "Kamu bisa miliki ini, agar kamu bisa MENGGALI\n"
	.string "lubang seperti kakakku…$"

Route114_FossilManiacsHouse_Text_DigReturnsYouToEntrance:
	.string "Jika kamu menyuruh POKéMON-mu MENGGALI\n"
	.string "di dalam gua, kamu akan kembali ke pintu masuk…$"

Route114_FossilManiacsHouse_Text_RocksFillDisplayCase:
	.string "Batu-batuan berbentuk unik memenuhi\n"
	.string "kotak pajangan…$"

Route114_FossilManiacsHouse_Text_CrammedWithBooks:
	.string "KOMPOSISI LAPISAN TANAH…\n"
	.string "BAGAIMANA HUJAN MEMBENTUK DARATAN…\l"
	.string "BATU, TANAH, DAN BEBATUAN…\p"
	.string "Penuh sesak dengan buku.$"

