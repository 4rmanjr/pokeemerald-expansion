SSTidalLowerDeck_MapScripts::
	.byte 0

SSTidalLowerDeck_EventScript_Phillip::
	trainerbattle_single TRAINER_PHILLIP, SSTidalLowerDeck_Text_PhillipIntro, SSTidalLowerDeck_Text_PhillipDefeat
	msgbox SSTidalLowerDeck_Text_PhillipPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalLowerDeck_EventScript_Leonard::
	trainerbattle_single TRAINER_LEONARD, SSTidalLowerDeck_Text_LeonardIntro, SSTidalLowerDeck_Text_LeonardDefeat
	msgbox SSTidalLowerDeck_Text_LeonardPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalLowerDeck_Text_PhillipIntro:
	.string "Arrgh! Aku muak dan lelah sekali\n"
	.string "membersihkan tempat besar ini!\p"
	.string "Ayo kita bertarung cepat!$"

SSTidalLowerDeck_Text_PhillipDefeat:
	.string "Adik, aku kalah!$"

SSTidalLowerDeck_Text_PhillipPostBattle:
	.string "Kami CLEANUP BROTHERS!\p"
	.string "Yang tua menuangkan deterjen,\n"
	.string "dan yang muda menggosok!$"

SSTidalLowerDeck_Text_LeonardIntro:
	.string "Ini adalah bagian bawah lambung kapal.\n"
	.string "Ada banyak ruang.\l"
	.string "Akan baik-baik saja untuk pertarungan POKéMON.$"

SSTidalLowerDeck_Text_LeonardDefeat:
	.string "Kakak, aku kalah!$"

SSTidalLowerDeck_Text_LeonardPostBattle:
	.string "Kami CLEANUP BROTHERS!\p"
	.string "Yang tua menuangkan deterjen,\n"
	.string "dan yang muda menggosok!$"

