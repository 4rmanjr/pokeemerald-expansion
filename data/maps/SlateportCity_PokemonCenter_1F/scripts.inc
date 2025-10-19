SlateportCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SlateportCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

SlateportCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_SLATEPORT_CITY
	call Common_EventScript_UpdateBrineyLocation
	end

SlateportCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_SLATEPORT_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

SlateportCity_PokemonCenter_1F_EventScript_Sailor::
	msgbox SlateportCity_PokemonCenter_1F_Text_RaiseDifferentTypesOfPokemon, MSGBOX_NPC
	end

SlateportCity_PokemonCenter_1F_EventScript_Woman::
	msgbox SlateportCity_PokemonCenter_1F_Text_TradedMonWithFriend, MSGBOX_NPC
	end

SlateportCity_PokemonCenter_1F_Text_RaiseDifferentTypesOfPokemon:
	.string "Mau tips untuk bertarung?\p"
	.string "Menurutku, itu adalah melatih berbagai\n"
	.string "jenis POKéMON secara seimbang.\p"
	.string "Tidak baik hanya membuat satu\n"
	.string "POKéMON saja yang kuat.\p"
	.string "Jika ia memiliki kelemahan tipe,\n"
	.string "ia mungkin tidak punya peluang.$"

SlateportCity_PokemonCenter_1F_Text_TradedMonWithFriend:
	.string "Aku menukar POKéMON dengan teman-temanku.\p"
	.string "Jika POKéMON yang ditukar membawa\n"
	.string "item, itu membuatku dua kali lebih senang!$"

