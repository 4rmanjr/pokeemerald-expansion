Route110_TrickHousePuzzle6_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_TrickHousePuzzle6_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route110_TrickHousePuzzle6_OnWarp
	.byte 0

Route110_TrickHousePuzzle6_OnTransition:
	special RotatingGate_InitPuzzle
	end

Route110_TrickHousePuzzle6_OnWarp:
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, Route110_TrickHousePuzzle6_EventScript_InitPuzzle
	.2byte 0

@ NOTE: This rotating gate puzzle makes use of VAR_TEMP_0 - VAR_TEMP_5
Route110_TrickHousePuzzle6_EventScript_InitPuzzle::
	special RotatingGate_InitPuzzleAndGraphics
	end

Route110_TrickHousePuzzle6_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_6_STATE, 0, Route110_TrickHousePuzzle6_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle6_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_6_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle6_EventScript_Sophia::
	trainerbattle_single TRAINER_SOPHIA, Route110_TrickHousePuzzle6_Text_SophiaIntro, Route110_TrickHousePuzzle6_Text_SophiaDefeat
	msgbox Route110_TrickHousePuzzle6_Text_SophiaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_EventScript_Benny::
	trainerbattle_single TRAINER_BENNY, Route110_TrickHousePuzzle6_Text_BennyIntro, Route110_TrickHousePuzzle6_Text_BennyDefeat
	msgbox Route110_TrickHousePuzzle6_Text_BennyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_EventScript_Sebastian::
	trainerbattle_single TRAINER_SEBASTIAN, Route110_TrickHousePuzzle6_Text_SebastianIntro, Route110_TrickHousePuzzle6_Text_SebastianDefeat
	msgbox Route110_TrickHousePuzzle6_Text_SebastianPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_Text_WroteSecretCodeLockOpened:
	.string "{PLAYER} menuliskan kode rahasia\n"
	.string "di pintu.\p"
	.string "“TRICK MASTER adalah hidupku.”\n"
	.string "… … … … … … … …\p"
	.string "Kunci terbuka!$"

Route110_TrickHousePuzzle6_Text_SophiaIntro:
	.string "Ketika Aku mendengar ada rumah aneh,\n"
	.string "Aku harus memeriksanya.$"

Route110_TrickHousePuzzle6_Text_SophiaDefeat:
	.string "Aku telah menemukan TRAINER yang tangguh!$"

Route110_TrickHousePuzzle6_Text_SophiaPostBattle:
	.string "Aku yakin bersenang-senang memeriksa\n"
	.string "tempat ini.\p"
	.string "Ini adalah tantangan yang menurutku\n"
	.string "layak diulang!$"

Route110_TrickHousePuzzle6_Text_BennyIntro:
	.string "Mungkin Aku bisa menyuruh POKéMON BURUNG-ku\n"
	.string "terbang melewati tembok…$"

Route110_TrickHousePuzzle6_Text_BennyDefeat:
	.string "Gwaaah! Aku gagal!$"

Route110_TrickHousePuzzle6_Text_BennyPostBattle:
	.string "Ehehehe… Kurasa Aku kalah karena\n"
	.string "Aku mencoba curang.$"

Route110_TrickHousePuzzle6_Text_SebastianIntro:
	.string "Aku pusing karena pintu-pintu berputar\n"
	.string "ini…$"

Route110_TrickHousePuzzle6_Text_SebastianDefeat:
	.string "Semuanya berputar-putar. Aku tidak\n"
	.string "tahan lagi…$"

Route110_TrickHousePuzzle6_Text_SebastianPostBattle:
	.string "Kamu sepertinya tidak terpengaruh sama sekali.\n"
	.string "Atau apakah kamu sedang memasang muka datar?$"

