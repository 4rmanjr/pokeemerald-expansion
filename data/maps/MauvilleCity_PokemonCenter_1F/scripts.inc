MauvilleCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MauvilleCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

MauvilleCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_MAUVILLE_CITY
	call Common_EventScript_UpdateBrineyLocation
	goto MauvilleCity_PokemonCenter_1F_EventScript_SetMauvilleOldManGfx
	end

MauvilleCity_PokemonCenter_1F_EventScript_SetMauvilleOldManGfx::
	special SetMauvilleOldManObjEventGfx
	end

MauvilleCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_MAUVILLE_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_Woman1::
	msgbox MauvilleCity_PokemonCenter_1F_Text_ManOverThereSaysWeirdThings, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_Woman2::
	msgbox MauvilleCity_PokemonCenter_1F_Text_MyDataUpdatedFromRecordCorner, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_Youngster::
	msgbox MauvilleCity_PokemonCenter_1F_Text_RecordCornerSoundsFun, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_Text_ManOverThereSaysWeirdThings:
	.string "Pria di sebelah sana, dia mengatakan\n"
	.string "hal-hal aneh!\p"
	.string "Dia lucu dengan cara yang aneh.\n"
	.string "Kurasa aku tidak akan melupakannya!$"

MauvilleCity_PokemonCenter_1F_Text_MyDataUpdatedFromRecordCorner:
	.string "Saat aku mengakses RECORD CORNER,\n"
	.string "data tentang apa yang sedang tren di\l"
	.string "DEWFORD diperbarui.\p"
	.string "Sekarang data itu sama dengan milik\n"
	.string "temanku!$"

MauvilleCity_PokemonCenter_1F_Text_RecordCornerSoundsFun:
	.string "RECORD CORNER telah dibuka di lantai atas\n"
	.string "POKéMON CENTER.\p"
	.string "Aku tidak tahu tentang apa itu, tapi\n"
	.string "kedengarannya menyenangkan. Aku akan\l"
	.string "memeriksanya!$"

