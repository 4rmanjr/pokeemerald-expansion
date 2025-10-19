FallarborTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FallarborTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_FALLARBOR_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

FallarborTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_FALLARBOR_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

FallarborTown_PokemonCenter_1F_EventScript_Girl::
	msgbox FallarborTown_PokemonCenter_1F_Text_FossilManiacEdgeOfTown, MSGBOX_NPC
	end

FallarborTown_PokemonCenter_1F_EventScript_ExpertM::
	msgbox FallarborTown_PokemonCenter_1F_Text_PlantHardyTrees, MSGBOX_NPC
	end

FallarborTown_PokemonCenter_1F_EventScript_Lanette::
	lock
	faceplayer
	msgbox FallarborTown_PokemonCenter_1F_Text_LanetteGreeting, MSGBOX_DEFAULT
	closemessage
	switch VAR_FACING
	case DIR_NORTH, FallarborTown_PokemonCenter_1F_EventScript_LanetteExitNorth
	case DIR_WEST, FallarborTown_PokemonCenter_1F_EventScript_LanetteExitWest
	end

FallarborTown_PokemonCenter_1F_EventScript_LanetteExitNorth::
	applymovement LOCALID_FALLARBOR_LANETTE, FallarborTown_PokemonCenter_1F_Movement_LanetteExitNorth
	waitmovement 0
	goto FallarborTown_PokemonCenter_1F_EventScript_LanetteExited
	end

FallarborTown_PokemonCenter_1F_EventScript_LanetteExitWest::
	applymovement LOCALID_FALLARBOR_LANETTE, FallarborTown_PokemonCenter_1F_Movement_LanetteExitWest
	waitmovement 0
	goto FallarborTown_PokemonCenter_1F_EventScript_LanetteExited
	end

FallarborTown_PokemonCenter_1F_EventScript_LanetteExited::
	playse SE_SLIDING_DOOR
	removeobject LOCALID_FALLARBOR_LANETTE
	clearflag FLAG_HIDE_LANETTES_HOUSE_LANETTE
	release
	end

FallarborTown_PokemonCenter_1F_Movement_LanetteExitNorth:
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

FallarborTown_PokemonCenter_1F_Movement_LanetteExitWest:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

FallarborTown_PokemonCenter_1F_Text_LanetteGreeting:
	.string "Oh, halo.\n"
	.string "Kamu siapa?\p"
	.string "Oke, namamu {PLAYER}{KUN}.\n"
	.string "Kulihat kamu seorang TRAINER.\p"
	.string "Berarti kamu memakai Sistem Storage\n"
	.string "POKéMON buatanku.\p"
	.string "Aku menyimpulkannya lewat proses\n"
	.string "deduksi sederhana.\p"
	.string "Kamu bicara padaku karena ingin\n"
	.string "mengakses PC ini.\p"
	.string "Oh, maaf. Aku LANETTE.\p"
	.string "Jujur, aku senang bertemu denganmu.\n"
	.string "Hebat kamu memakai Sistem Storage-ku.\p"
	.string "Kalau bisa, kunjungi aku di rumah ya.\n"
	.string "Rumahku ada di ROUTE 114.$"

FallarborTown_PokemonCenter_1F_Text_FossilManiacEdgeOfTown:
	.string "Aku penasaran seperti apa wujud\n"
	.string "POKéMON zaman dulu kala?\p"
	.string "Mungkin FOSSIL MANIAC di ujung\n"
	.string "kota tahu jawabannya.$"

FallarborTown_PokemonCenter_1F_Text_PlantHardyTrees:
	.string "Di ladang FALLARBOR, kami menanam\n"
	.string "bibit pohon kuat yang tumbuh subur\l"
	.string "di abu vulkanik.$"

