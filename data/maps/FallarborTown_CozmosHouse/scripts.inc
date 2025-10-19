FallarborTown_CozmosHouse_MapScripts::
	.byte 0

FallarborTown_CozmosHouse_EventScript_ProfCozmo::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_RETURN, FallarborTown_CozmosHouse_EventScript_GaveMeteorite
	checkitem ITEM_METEORITE
	goto_if_eq VAR_RESULT, TRUE, FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite::
	call_if_unset FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_NoticeMeteorite
	call_if_set FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_AskForMeteorite
	goto_if_eq VAR_RESULT, NO, FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite
	msgbox FallarborTown_CozmosHouse_Text_PleaseUseThisTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_RETURN
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_0x8004, ITEM_METEORITE
	call Common_EventScript_PlayerHandedOverTheItem
	setflag FLAG_RECEIVED_TM_RETURN
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_NoticeMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	msgbox FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_AskForMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_MayIHaveMeteorite, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite::
	setflag FLAG_TEMP_2
	msgbox FallarborTown_CozmosHouse_Text_CrushedWithDisappointment, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_GaveMeteorite::
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmosWife::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_RETURN, FallarborTown_CozmosHouse_EventScript_CozmoIsHappy
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_CozmosHouse_EventScript_CozmoIsSad
	msgbox FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsSad::
	msgbox FallarborTown_CozmosHouse_Text_FeelSorryForCozmo, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsHappy::
	msgbox FallarborTown_CozmosHouse_Text_CozmoIsSoHappy, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow:
	.string "PROF. COZMO: Oh…\n"
	.string "Seharusnya aku tidak membiarkan diriku\l"
	.string "ditipu untuk memberitahu TEAM MAGMA di\l"
	.string "mana bisa menemukan METEORITE…\p"
	.string "METEORITE dari METEOR FALLS itu…\n"
	.string "Sekarang tidak akan pernah menjadi milikku…$"

FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt:
	.string "Oh!\n"
	.string "Hah?\p"
	.string "Item itu…\p"
	.string "Mungkinkah?\p"
	.string "Apakah itu METEORITE yang diambil\n"
	.string "TEAM MAGMA dari METEOR FALLS?\p"
	.string "Tolong, bolehkah aku memintanya?\p"
	.string "Aku tidak memintanya secara gratis.\n"
	.string "Bagaimana kalau ditukar dengan TM ini?$"

FallarborTown_CozmosHouse_Text_PleaseUseThisTM:
	.string "PROF. COZMO: TM ini, ini melambangkan\n"
	.string "rasa terima kasihku.\l"
	.string "Silakan gunakan!$"

FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch:
	.string "PROF. COZMO: Oh, aku tidak percaya.\n"
	.string "Ini benar-benar, benar-benar hebat!\p"
	.string "Ini akan sangat membantu penelitianku!$"

FallarborTown_CozmosHouse_Text_CrushedWithDisappointment:
	.string "PROF. COZMO: Oh, tapi…\n"
	.string "Aku hancur karena kecewa…$"

FallarborTown_CozmosHouse_Text_MayIHaveMeteorite:
	.string "PROF. COZMO: Tolong, bolehkah aku\n"
	.string "meminta METEORITE itu?\p"
	.string "Aku tidak memintanya secara gratis.\n"
	.string "Bagaimana kalau ditukar dengan TM ini?$"

FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls:
	.string "PROF. COZMO pergi ke METEOR FALLS\n"
	.string "di ROUTE 114 bersama beberapa orang\l"
	.string "dari TEAM MAGMA.$"

FallarborTown_CozmosHouse_Text_FeelSorryForCozmo:
	.string "Kasihan PROF. COZMO…\n"
	.string "Dia sangat tertekan… Aku kasihan padanya.$"

FallarborTown_CozmosHouse_Text_CozmoIsSoHappy:
	.string "Lihat PROF. COZMO…\n"
	.string "Dia sangat senang! Menurutku itu lucu.$"

