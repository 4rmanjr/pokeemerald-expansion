VictoryRoad_B1F_MapScripts::
	.byte 0

VictoryRoad_B1F_EventScript_Samuel::
	trainerbattle_single TRAINER_SAMUEL, VictoryRoad_B1F_Text_SamuelIntro, VictoryRoad_B1F_Text_SamuelDefeat
	msgbox VictoryRoad_B1F_Text_SamuelPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Shannon::
	trainerbattle_single TRAINER_SHANNON, VictoryRoad_B1F_Text_ShannonIntro, VictoryRoad_B1F_Text_ShannonDefeat
	msgbox VictoryRoad_B1F_Text_ShannonPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Michelle::
	trainerbattle_single TRAINER_MICHELLE, VictoryRoad_B1F_Text_MichelleIntro, VictoryRoad_B1F_Text_MichelleDefeat
	msgbox VictoryRoad_B1F_Text_MichellePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Mitchell::
	trainerbattle_single TRAINER_MITCHELL, VictoryRoad_B1F_Text_MitchellIntro, VictoryRoad_B1F_Text_MitchellDefeat
	msgbox VictoryRoad_B1F_Text_MitchellPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Halle::
	trainerbattle_single TRAINER_HALLE, VictoryRoad_B1F_Text_HalleIntro, VictoryRoad_B1F_Text_HalleDefeat
	msgbox VictoryRoad_B1F_Text_HallePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_Text_SamuelIntro:
	.string "Pikiran bahwa aku semakin dekat dengan\n"
	.string "POKéMON LEAGUE…\p"
	.string "Aku mulai demam panggung…$"

VictoryRoad_B1F_Text_SamuelDefeat:
	.string "Aku tidak bisa berbuat apa-apa…$"

VictoryRoad_B1F_Text_SamuelPostBattle:
	.string "POKéMON LEAGUE kembali menjauh…\n"
	.string "Sungguh mengecewakan…$"

VictoryRoad_B1F_Text_ShannonIntro:
	.string "Untuk memenangkan jalanmu melalui POKéMON\n"
	.string "LEAGUE, kamu membutuhkan kepercayaan\l"
	.string "POKéMON-mu.$"

VictoryRoad_B1F_Text_ShannonDefeat:
	.string "Hubunganmu didasarkan pada\n"
	.string "kepercayaan yang kuat.$"

VictoryRoad_B1F_Text_ShannonPostBattle:
	.string "Dengan selalu bersama, kepercayaan\n"
	.string "tumbuh antara POKéMON dan TRAINER.$"

VictoryRoad_B1F_Text_MichelleIntro:
	.string "Ini bukan tujuan. Ini hanya tempat\n"
	.string "di jalan menuju POKéMON LEAGUE.$"

VictoryRoad_B1F_Text_MichelleDefeat:
	.string "Begitulah!$"

VictoryRoad_B1F_Text_MichellePostBattle:
	.string "Kamu pasti akan baik-baik saja!\n"
	.string "POKéMON-mu semua bersemangat untuk pergi!$"

VictoryRoad_B1F_Text_MitchellIntro:
	.string "POKéMON-ku sangat\n"
	.string "mengagumkan!$"

VictoryRoad_B1F_Text_MitchellDefeat:
	.string "Aku belum pernah bertemu orang sepertimu sebelumnya.$"

VictoryRoad_B1F_Text_MitchellPostBattle:
	.string "Bahkan di luar pertarungan, aku merasakan\n"
	.string "kekuatan luar biasa terpancar darimu\l"
	.string "dan POKéMON-mu.$"

VictoryRoad_B1F_Text_HalleIntro:
	.string "Oke, tidak perlu marah!\n"
	.string "Tenang saja, mari kita santai!$"

VictoryRoad_B1F_Text_HalleDefeat:
	.string "Whoa!\n"
	.string "Luar biasa!$"

VictoryRoad_B1F_Text_HallePostBattle:
	.string "Tentu, ini VICTORY ROAD.\p"
	.string "Tapi tidak jauh berbeda dengan\n"
	.string "jalan yang sudah kamu lalui sejauh ini.\p"
	.string "Cobalah menikmati sisa\n"
	.string "perjalanan!$"

