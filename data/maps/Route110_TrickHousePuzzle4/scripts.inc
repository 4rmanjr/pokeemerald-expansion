Route110_TrickHousePuzzle4_MapScripts::
	.byte 0

Route110_TrickHousePuzzle4_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_4_STATE, 0, Route110_TrickHousePuzzle4_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle4_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_4_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle4_EventScript_Cora::
	trainerbattle_single TRAINER_CORA, Route110_TrickHousePuzzle4_Text_CoraIntro, Route110_TrickHousePuzzle4_Text_CoraDefeat
	msgbox Route110_TrickHousePuzzle4_Text_CoraPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_EventScript_Yuji::
	trainerbattle_single TRAINER_YUJI, Route110_TrickHousePuzzle4_Text_YujiIntro, Route110_TrickHousePuzzle4_Text_YujiDefeat
	msgbox Route110_TrickHousePuzzle4_Text_YujiPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_EventScript_Paula::
	trainerbattle_single TRAINER_PAULA, Route110_TrickHousePuzzle4_Text_PaulaIntro, Route110_TrickHousePuzzle4_Text_PaulaDefeat
	msgbox Route110_TrickHousePuzzle4_Text_PaulaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_Text_WroteSecretCodeLockOpened:
	.string "{PLAYER} menuliskan kode rahasia\n"
	.string "di pintu.\p"
	.string "“TRICK MASTER keren.”\n"
	.string "… … … … … … … …\p"
	.string "Kunci terbuka!$"

Route110_TrickHousePuzzle4_Text_CoraIntro:
	.string "Terlalu merepotkan untuk memikirkannya.\n"
	.string "Aku hanya ingin bertarung!$"

Route110_TrickHousePuzzle4_Text_CoraDefeat:
	.string "Meskipun Aku kalah, Aku tetap paling\n"
	.string "suka bertarung!$"

Route110_TrickHousePuzzle4_Text_CoraPostBattle:
	.string "Tidakkah kamu setuju? Kamu akan pergi\n"
	.string "ke mana saja jika ada TRAINER di sana.$"

Route110_TrickHousePuzzle4_Text_YujiIntro:
	.string "Heh! Batu-batu seperti ini, Aku bisa\n"
	.string "singkirkan dengan satu jari!$"

Route110_TrickHousePuzzle4_Text_YujiDefeat:
	.string "Aku bisa mendorong batu, tapi Aku tidak\n"
	.string "bisa memecahkan teka-teki itu…$"

Route110_TrickHousePuzzle4_Text_YujiPostBattle:
	.string "Tidak cukup hanya berotot…\n"
	.string "Kamu harus menggunakan otakmu. Jadilah cerdas!$"

Route110_TrickHousePuzzle4_Text_PaulaIntro:
	.string "TRICK HOUSE semakin rumit,\n"
	.string "bukan?$"

Route110_TrickHousePuzzle4_Text_PaulaDefeat:
	.string "Aaak!$"

Route110_TrickHousePuzzle4_Text_PaulaPostBattle:
	.string "Apakah ada yang berhasil sampai akhir?$"

