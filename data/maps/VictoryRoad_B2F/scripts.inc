VictoryRoad_B2F_MapScripts::
	.byte 0

VictoryRoad_B2F_EventScript_Vito::
	trainerbattle_single TRAINER_VITO, VictoryRoad_B2F_Text_VitoIntro, VictoryRoad_B2F_Text_VitoDefeat
	msgbox VictoryRoad_B2F_Text_VitoPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Owen::
	trainerbattle_single TRAINER_OWEN, VictoryRoad_B2F_Text_OwenIntro, VictoryRoad_B2F_Text_OwenDefeat
	msgbox VictoryRoad_B2F_Text_OwenPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Caroline::
	trainerbattle_single TRAINER_CAROLINE, VictoryRoad_B2F_Text_CarolineIntro, VictoryRoad_B2F_Text_CarolineDefeat
	msgbox VictoryRoad_B2F_Text_CarolinePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Julie::
	trainerbattle_single TRAINER_JULIE, VictoryRoad_B2F_Text_JulieIntro, VictoryRoad_B2F_Text_JulieDefeat
	msgbox VictoryRoad_B2F_Text_JuliePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Felix::
	trainerbattle_single TRAINER_FELIX, VictoryRoad_B2F_Text_FelixIntro, VictoryRoad_B2F_Text_FelixDefeat
	msgbox VictoryRoad_B2F_Text_FelixPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Dianne::
	trainerbattle_single TRAINER_DIANNE, VictoryRoad_B2F_Text_DianneIntro, VictoryRoad_B2F_Text_DianneDefeat
	msgbox VictoryRoad_B2F_Text_DiannePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_Text_VitoIntro:
	.string "Aku berlatih bersama seluruh keluargaku,\n"
	.string "setiap orang dari kami!\l"
	.string "Aku tidak akan kalah dari siapa pun!$"

VictoryRoad_B2F_Text_VitoDefeat:
	.string "Lebih baik dari keluargaku?!\n"
	.string "Apakah itu mungkin?!$"

VictoryRoad_B2F_Text_VitoPostBattle:
	.string "Aku lebih baik dari semua orang di\n"
	.string "keluargaku. Aku tidak pernah kalah sebelumnya…\p"
	.string "Aku kehilangan kepercayaan diriku…\n"
	.string "Mungkin aku akan pulang…$"

VictoryRoad_B2F_Text_OwenIntro:
	.string "Aku dengar ada anak kecil yang tangguh\n"
	.string "di sekitar sini. Apakah mereka maksud kamu?$"

VictoryRoad_B2F_Text_OwenDefeat:
	.string "Si udang kecil itu tangguh!$"

VictoryRoad_B2F_Text_OwenPostBattle:
	.string "Rumor yang kudengar, anak kecil\n"
	.string "tangguh itu dari PETALBURG CITY.$"

VictoryRoad_B2F_Text_CarolineIntro:
	.string "Kamu pasti mulai sedikit lelah.$"

VictoryRoad_B2F_Text_CarolineDefeat:
	.string "Tidak ada tanda-tanda kelelahan sama sekali!$"

VictoryRoad_B2F_Text_CarolinePostBattle:
	.string "VICTORY ROAD dan POKéMON LEAGUE\n"
	.string "adalah tantangan yang panjang dan melelahkan.\l"
	.string "Hati-hati terhadap kelelahan!$"

VictoryRoad_B2F_Text_JulieIntro:
	.string "Kamu tidak boleh berpuas diri hanya\n"
	.string "karena kamu punya banyak GYM BADGES.\p"
	.string "Akan selalu ada seseorang\n"
	.string "yang lebih baik darimu!$"

VictoryRoad_B2F_Text_JulieDefeat:
	.string "Kamu lebih baik dariku!$"

VictoryRoad_B2F_Text_JuliePostBattle:
	.string "Lihatlah BADGES yang kamu kumpulkan dan\n"
	.string "ingatlah TRAINER yang sudah kamu hadapi.$"

VictoryRoad_B2F_Text_FelixIntro:
	.string "Aku sudah sejauh ini, tapi ketegangan\n"
	.string "membuat perutku sakit sekali…$"

VictoryRoad_B2F_Text_FelixDefeat:
	.string "Ooh…\n"
	.string "Sakit sekali…$"

VictoryRoad_B2F_Text_FelixPostBattle:
	.string "Aku tidak bisa menahan ketegangan karena\n"
	.string "aku mendekati POKéMON LEAGUE.\p"
	.string "Yang bisa kulakukan hanyalah berpura-pura tenang.$"

VictoryRoad_B2F_Text_DianneIntro:
	.string "Para elit di antara para elit berkumpul di\n"
	.string "gua ini.\p"
	.string "Bagaimana menurutmu?$"

VictoryRoad_B2F_Text_DianneDefeat:
	.string "Tidak gentar sedikit pun!$"

VictoryRoad_B2F_Text_DiannePostBattle:
	.string "Kamu memang punya nyali! Aku suka itu!\n"
	.string "Teruslah berjuang!$"

