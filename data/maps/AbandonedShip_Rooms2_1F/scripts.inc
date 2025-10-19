AbandonedShip_Rooms2_1F_MapScripts::
	.byte 0

AbandonedShip_Rooms2_1F_EventScript_Dan::
	trainerbattle_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_DanIntro, AbandonedShip_Rooms2_1F_Text_DanDefeat, AbandonedShip_Rooms2_1F_Text_DanNotEnoughMons, AbandonedShip_Rooms2_1F_EventScript_RegisterDan
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms2_1F_EventScript_DanRematch
	msgbox AbandonedShip_Rooms2_1F_Text_DanPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms2_1F_EventScript_RegisterDan::
	msgbox AbandonedShip_Rooms2_1F_Text_KiraRegister, MSGBOX_DEFAULT  @ Kira speaks for both when registering KiraAndDan
	register_matchcall TRAINER_KIRA_AND_DAN_1
	release
	end

AbandonedShip_Rooms2_1F_EventScript_DanRematch::
	trainerbattle_rematch_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_DanRematchIntro, AbandonedShip_Rooms2_1F_Text_DanRematchDefeat, AbandonedShip_Rooms2_1F_Text_DanRematchNotEnoughMons
	msgbox AbandonedShip_Rooms2_1F_Text_DanPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Kira::
	trainerbattle_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_KiraIntro, AbandonedShip_Rooms2_1F_Text_KiraDefeat, AbandonedShip_Rooms2_1F_Text_KiraNotEnoughMons, AbandonedShip_Rooms2_1F_EventScript_RegisterKira
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms2_1F_EventScript_KiraRematch
	msgbox AbandonedShip_Rooms2_1F_Text_KiraPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms2_1F_EventScript_RegisterKira::
	msgbox AbandonedShip_Rooms2_1F_Text_KiraRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_KIRA_AND_DAN_1
	release
	end

AbandonedShip_Rooms2_1F_EventScript_KiraRematch::
	trainerbattle_rematch_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_KiraRematchIntro, AbandonedShip_Rooms2_1F_Text_KiraRematchDefeat, AbandonedShip_Rooms2_1F_Text_KiraRematchNotEnoughMons
	msgbox AbandonedShip_Rooms2_1F_Text_KiraPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Jani::
	trainerbattle_single TRAINER_JANI, AbandonedShip_Rooms2_1F_Text_JaniIntro, AbandonedShip_Rooms2_1F_Text_JaniDefeat
	msgbox AbandonedShip_Rooms2_1F_Text_JaniPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Garrison::
	trainerbattle_single TRAINER_GARRISON, AbandonedShip_Rooms2_1F_Text_GarrisonIntro, AbandonedShip_Rooms2_1F_Text_GarrisonDefeat
	msgbox AbandonedShip_Rooms2_1F_Text_GarrisonPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_Text_DanIntro:
	.string "DAN: Saat mencari harta karun,\n"
	.string "kami malah menemukan TRAINER!$"

AbandonedShip_Rooms2_1F_Text_DanDefeat:
	.string "DAN: Kami tidak bisa menang padahal\n"
	.string "sudah bekerja sama…$"

AbandonedShip_Rooms2_1F_Text_DanPostBattle:
	.string "DAN: Tak ada harta karun…\n"
	.string "Apa sudah ada yang mengambilnya?$"

AbandonedShip_Rooms2_1F_Text_DanNotEnoughMons:
	.string "DAN: Kamu tak punya dua POKéMON.\n"
	.string "Jangan harap bisa mengalahkan kami.$"

AbandonedShip_Rooms2_1F_Text_KiraIntro:
	.string "KIRA: Oh?\n"
	.string "Kami sedang mencari harta karun.\l"
	.string "Tapi malah menemukan TRAINER!$"

AbandonedShip_Rooms2_1F_Text_KiraDefeat:
	.string "KIRA: Ooh, kuatnya!$"

AbandonedShip_Rooms2_1F_Text_KiraPostBattle:
	.string "KIRA: Di mana harta karunnya?\p"
	.string "Aku sudah putuskan mau beli apa\n"
	.string "kalau hartanya ketemu!$"

AbandonedShip_Rooms2_1F_Text_KiraNotEnoughMons:
	.string "KIRA: Oh, kamu tak punya dua POKéMON?\n"
	.string "Kita bertarung lain kali saja, ya!$"

AbandonedShip_Rooms2_1F_Text_KiraRegister:
	.string "KIRA: Ih, menyebalkan!\n"
	.string "Karena itu, nomormu akan kucatat!$"

AbandonedShip_Rooms2_1F_Text_DanRematchIntro:
	.string "DAN: Kami terus mencari harta karun\n"
	.string "selama ini.\p"
	.string "POKéMON kami juga jadi lebih kuat.\n"
	.string "Biar kami tunjukkan, ya?$"

AbandonedShip_Rooms2_1F_Text_DanRematchDefeat:
	.string "DAN: Seperti biasa, kamu kuat!$"

AbandonedShip_Rooms2_1F_Text_DanPostRematch:
	.string "DAN: Harta karun tak ketemu,\n"
	.string "bertarung POKéMON pun kalah…\p"
	.string "Aku mau pulang… Tapi kalau bilang begitu,\n"
	.string "dia nanti marah…$"

AbandonedShip_Rooms2_1F_Text_DanRematchNotEnoughMons:
	.string "DAN: Kamu tak punya dua POKéMON.\n"
	.string "Jangan harap bisa mengalahkan kami.$"

AbandonedShip_Rooms2_1F_Text_KiraRematchIntro:
	.string "KIRA: Oh? Ketemu lagi!\p"
	.string "Sama seperti kami, kamu juga belum\n"
	.string "menyerah mencari harta karun, ya?\p"
	.string "Bagaimana kalau yang kalah harus\n"
	.string "berhenti mencari?$"

AbandonedShip_Rooms2_1F_Text_KiraRematchDefeat:
	.string "KIRA: Oh, kalah lagi…$"

AbandonedShip_Rooms2_1F_Text_KiraPostRematch:
	.string "KIRA: Kami takkan pergi sebelum POKéMON\n"
	.string "kami jadi lebih kuat dan kami menemukan\l"
	.string "harta karun di sini!$"

AbandonedShip_Rooms2_1F_Text_KiraRematchNotEnoughMons:
	.string "KIRA: Oh, kamu tak punya dua POKéMON?\n"
	.string "Kita bertarung lain kali saja, ya!$"

AbandonedShip_Rooms2_1F_Text_JaniIntro:
	.string "Aku tak jago berenang,\n"
	.string "tapi jago bertarung!$"

AbandonedShip_Rooms2_1F_Text_JaniDefeat:
	.string "Ups.\n"
	.string "Tidak berjalan lancar.$"

AbandonedShip_Rooms2_1F_Text_JaniPostBattle:
	.string "Jalan tanpa alas kaki di kapal ini\n"
	.string "agak menjijikkan.$"

AbandonedShip_Rooms2_1F_Text_GarrisonIntro:
	.string "Kekuatan dan kasih sayang…\n"
	.string "Itulah harta karun TRAINER!$"

AbandonedShip_Rooms2_1F_Text_GarrisonDefeat:
	.string "Ah, ada sesuatu darimu\n"
	.string "yang berkilau.$"

AbandonedShip_Rooms2_1F_Text_GarrisonPostBattle:
	.string "Di salah satu kabin di kapal ini,\n"
	.string "aku melihat sesuatu berkilau.$"
