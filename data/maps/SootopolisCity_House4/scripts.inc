SootopolisCity_House4_MapScripts::
	.byte 0

SootopolisCity_House4_EventScript_Man::
	msgbox SootopolisCity_House4_Text_AncientTreasuresWaitingInSea, MSGBOX_NPC
	end

SootopolisCity_House4_EventScript_Woman::
	msgbox SootopolisCity_House4_Text_StrollUnderwaterWithPokemon, MSGBOX_NPC
	end

SootopolisCity_House4_EventScript_Azumarill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZUMARILL, CRY_MODE_NORMAL
	msgbox SootopolisCity_House4_Text_Azumarill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SootopolisCity_House4_Text_AncientTreasuresWaitingInSea:
	.string "Dengarkan baik-baik, aku akan memberitahumu\n"
	.string "sesuatu yang bagus.\p"
	.string "Konon ada reruntuhan kuno di laut\n"
	.string "sekitar sini.\p"
	.string "Mungkin ada harta karun yang menunggu\n"
	.string "untuk ditemukan di sana.$"

SootopolisCity_House4_Text_StrollUnderwaterWithPokemon:
	.string "Harta karun kuno…\p"
	.string "Akan menyenangkan jika itu ada, tapi\n"
	.string "meskipun tidak, akan sangat indah\l"
	.string "untuk berjalan-jalan di bawah air\l"
	.string "bersama POKéMON-ku.$"

SootopolisCity_House4_Text_Azumarill:
	.string "AZUMARILL: Marurii.$"

