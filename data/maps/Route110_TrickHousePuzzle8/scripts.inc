Route110_TrickHousePuzzle8_MapScripts::
	.byte 0

Route110_TrickHousePuzzle8_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_8_STATE, 0, Route110_TrickHousePuzzle8_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle8_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_8_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle8_EventScript_Vincent::
	trainerbattle_single TRAINER_VINCENT, Route110_TrickHousePuzzle8_Text_VincentIntro, Route110_TrickHousePuzzle8_Text_VincentDefeat
	msgbox Route110_TrickHousePuzzle8_Text_VincentPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_EventScript_Keira::
	trainerbattle_single TRAINER_KEIRA, Route110_TrickHousePuzzle8_Text_KeiraIntro, Route110_TrickHousePuzzle8_Text_KeiraDefeat
	msgbox Route110_TrickHousePuzzle8_Text_KeiraPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_EventScript_Leroy::
	trainerbattle_single TRAINER_LEROY, Route110_TrickHousePuzzle8_Text_LeroyIntro, Route110_TrickHousePuzzle8_Text_LeroyDefeat
	msgbox Route110_TrickHousePuzzle8_Text_LeroyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_Text_WroteSecretCodeLockOpened::
	.string "{PLAYER} menuliskan kode rahasia\n"
	.string "di pintu.\p"
	.string "“TRICK MASTER Aku cinta.”\n"
	.string "… … … … … … … …\p"
	.string "Kunci terbuka!$"

Route110_TrickHousePuzzle8_Text_VincentIntro:
	.string "Tidak banyak TRAINER yang berhasil\n"
	.string "sejauh ini.$"

Route110_TrickHousePuzzle8_Text_VincentDefeat:
	.string "Itu berarti kamu juga tangguh…$"

Route110_TrickHousePuzzle8_Text_VincentPostBattle:
	.string "Kamu sudah mengalahkan JUARA LIGA\n"
	.string "POKéMON? Itu terlalu banyak!$"

Route110_TrickHousePuzzle8_Text_KeiraIntro:
	.string "Anggap dirimu beruntung bisa\n"
	.string "melawanku!$"

Route110_TrickHousePuzzle8_Text_KeiraDefeat:
	.string "Ini tidak benar!\n"
	.string "Aku tidak bisa kalah!$"

Route110_TrickHousePuzzle8_Text_KeiraPostBattle:
	.string "Sungguh keajaiban kamu bisa mengalahkanku.\n"
	.string "Kamu bisa membanggakannya.$"

Route110_TrickHousePuzzle8_Text_LeroyIntro:
	.string "Kamu juga sudah berjuang melewati\n"
	.string "tantangan TRICK HOUSE.$"

Route110_TrickHousePuzzle8_Text_LeroyDefeat:
	.string "Aku mengerti…\n"
	.string "Kamu memiliki gaya yang luar biasa.$"

Route110_TrickHousePuzzle8_Text_LeroyPostBattle:
	.string "Melihat seseorang sepertimu seharusnya\n"
	.string "menyenangkan TRICK MASTER.$"

