VerdanturfTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

VerdanturfTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_VERDANTURF_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

VerdanturfTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_VERDANTURF_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

VerdanturfTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox VerdanturfTown_PokemonCenter_1F_Text_FaithInYourPokemon, MSGBOX_NPC
	end

VerdanturfTown_PokemonCenter_1F_EventScript_ExpertM::
	msgbox VerdanturfTown_PokemonCenter_1F_Text_VisitForBattleTent, MSGBOX_NPC
	end

VerdanturfTown_PokemonCenter_1F_Text_FaithInYourPokemon:
	.string "Kamu tidak bisa menganggap dirimu\n"
	.string "TRAINER sejati jika kamu tidak\l"
	.string "percaya pada POKéMON-mu.\p"
	.string "Hanya orang-orang yang bisa percaya\n"
	.string "pada POKéMON yang bertarung mereka\l"
	.string "yang bisa menang sampai akhir.$"

VerdanturfTown_PokemonCenter_1F_Text_VisitForBattleTent:
	.string "Alasan mengapa seseorang mengunjungi\n"
	.string "VERDANTURF…\p"
	.string "Itu adalah BATTLE TENT. Sudah jelas.\p"
	.string "Atau adakah seseorang di sini yang\n"
	.string "kamu datangi?$"

