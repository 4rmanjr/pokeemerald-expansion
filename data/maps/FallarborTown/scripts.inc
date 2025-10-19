FallarborTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_OnTransition
	.byte 0

FallarborTown_OnTransition:
	setflag FLAG_VISITED_FALLARBOR_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	clearflag FLAG_CONTEST_SKETCH_CREATED
	end

FallarborTown_EventScript_ExpertM::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_EventScript_ExpertMNormal
	msgbox FallarborTown_Text_ShadyCharactersCozmosHome, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_ExpertMNormal::
	msgbox FallarborTown_Text_RegionKnownForMeteors, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_Girl::
	msgbox FallarborTown_Text_MyPreciousAzurill, MSGBOX_NPC
	end

FallarborTown_EventScript_Gentleman::
	msgbox FallarborTown_Text_HaveYouChallengedFlannery, MSGBOX_NPC
	end

FallarborTown_EventScript_Azurill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, CRY_MODE_NORMAL
	msgbox FallarborTown_Text_Azurill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FallarborTown_EventScript_BattleTentSign::
	msgbox FallarborTown_Text_BattleTentSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_TownSign::
	msgbox FallarborTown_Text_TownSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_MoveTutorSign::
	msgbox FallarborTown_Text_MoveTutorSign, MSGBOX_SIGN
	end

FallarborTown_Text_ShadyCharactersCozmosHome:
	.string "Sesuatu sedang terjadi,\n"
	.string "dan aku tidak menyukainya!\p"
	.string "Aku melihat orang-orang mencurigakan\n"
	.string "berkeliaran masuk dan keluar dari rumah\l"
	.string "PROF. COZMO…$"

FallarborTown_Text_RegionKnownForMeteors:
	.string "Wilayah ini dikenal karena meteornya\n"
	.string "sejak zaman dulu.\p"
	.string "Katanya METEOR FALLS terbentuk oleh\n"
	.string "hantaman meteorit yang jatuh sejak lama.$"

FallarborTown_Text_MyPreciousAzurill:
	.string "Lihat! Coba lihat!\n"
	.string "Ini AZURILL-ku yang berharga!\p"
	.string "Dia licin, halus, dan juga empuk!$"

FallarborTown_Text_Azurill:
	.string "AZURILL: Rooreelooo.$"

FallarborTown_Text_HaveYouChallengedFlannery:
	.string "Apakah kamu sudah menantang FLANNERY,\n"
	.string "LEADER GYM LAVARIDGE?\p"
	.string "Kakek gadis itu terkenal.\n"
	.string "Dia pernah menjadi salah satu ELITE FOUR\l"
	.string "di LIGA POKéMON.\p"
	.string "Aku tidak akan terkejut melihat FLANNERY\n"
	.string "menjadi TRAINER hebat dengan caranya\l"
	.string "sendiri.$"

FallarborTown_Text_BattleTentSign:
	.string "LOKASI TENDA PERTARUNGAN FALLARBOR\n"
	.string "“Semoga Tim Terhebat Berkumpul!”$"

FallarborTown_Text_TownSign:
	.string "KOTA FALLARBOR\n"
	.string "“Komunitas pertanian dengan taman-taman kecil.”$"

FallarborTown_Text_MoveTutorSign:
	.string "RUMAH GURU JURUS\n"
	.string "“Jurus baru diajarkan kepada POKéMON.”$"

