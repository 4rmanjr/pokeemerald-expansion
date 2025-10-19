DewfordTown_House1_MapScripts::
	.byte 0

DewfordTown_House1_EventScript_Man::
	msgbox DewfordTown_House1_Text_LotToBeSaidForLivingOnIsland, MSGBOX_NPC
	end

DewfordTown_House1_EventScript_Woman::
	msgbox DewfordTown_House1_Text_LifeGoesSlowlyOnIsland, MSGBOX_NPC
	end

DewfordTown_House1_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox DewfordTown_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

DewfordTown_House1_Text_LotToBeSaidForLivingOnIsland:
	.string "Banyak yang bisa dikatakan tentang hidup\n"
	.string "di pulau kecil seperti ini selaras dengan\l"
	.string "POKéMON dan keluarga.$"

DewfordTown_House1_Text_LifeGoesSlowlyOnIsland:
	.string "Aku meninggalkan pelabuhan utama KOTA\n"
	.string "SLATEPORT saat aku menikah dengan\l"
	.string "suamiku di sini.\p"
	.string "Kehidupan berjalan lambat di pulau kecil\n"
	.string "ini. Tapi dikelilingi oleh laut yang\l"
	.string "indah--itu juga kebahagiaan.$"

DewfordTown_House1_Text_Zigzagoon:
	.string "ZIGZAGOON: Guguuh!$"

