Route111_WinstrateFamilysHouse_MapScripts::
	.byte 0

Route111_WinstrateFamilysHouse_EventScript_Victor::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VICTOR
	msgbox Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Victoria::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VICTORIA
	goto_if_set FLAG_RECEIVED_MACHO_BRACE, Route111_WinstrateFamilysHouse_EventScript_ReceivedMachoBrace
	msgbox Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace, MSGBOX_DEFAULT
	giveitem ITEM_MACHO_BRACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MACHO_BRACE
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_ReceivedMachoBrace::
	msgbox Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vivi::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VIVI
	msgbox Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vicky::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_WINSTRATE_HOUSE_VICKY
	goto_if_set FLAG_TEMP_4, Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrong, MSGBOX_DEFAULT
	setflag FLAG_TEMP_4
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo::
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection::
	closemessage
	applymovement VAR_0x8008, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou:
	.string "Kamu adalah TRAINER pertama yang Aku\n"
	.string "lihat yang mengerahkan POKéMON\n"
	.string "dengan begitu mahir.\p"
	.string "Tapi, harus kukatakan padamu--anakku\n"
	.string "lebih kuat darimu.\p"
	.string "Dia bahkan mengikuti tantangan LIGA\n"
	.string "POKéMON, perlu kamu tahu.$"

Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace:
	.string "Kami menggunakan MACHO BRACE ini untuk\n"
	.string "memperkuat POKéMON kami secara lebih\l"
	.string "efektif dalam pelatihan.\p"
	.string "Karena kamu telah mengalahkan\n"
	.string "kami semua di sini,\n"
	.string "Aku tidak tahu apakah kamu\n"
	.string "membutuhkannya, tapi kami\l"
	.string "ingin kamu memiliki MACHO BRACE kami.$"

Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles:
	.string "Ketika berbicara tentang pertarungan POKéMON,\n"
	.string "kami cenderung sangat bersemangat.$"

Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers:
	.string "Mama lebih kuat dari Ayah.\p"
	.string "Aku lebih kuat dari Mama.\p"
	.string "Dan Nenek lebih kuat dariku!\p"
	.string "Tapi kakak laki-lakiku bahkan lebih kuat\n"
	.string "dari Nenek.$"

Route111_WinstrateFamilysHouse_Text_GrandsonStrong:
	.string "Tidak diragukan lagi kamu kuat.\p"
	.string "Tapi jika kamu bertarung dengan cucuku,\n"
	.string "kamu akan menangis frustrasi.\p"
	.string "Dia jauh lebih kuat dari TRAINER mana pun\n"
	.string "yang keluarga kami kenal.\p"
	.string "Dia pasti sedang menantang JUARA LIGA\n"
	.string "POKéMON sekarang.\p"
	.string "Mengenal cucuku, dia mungkin sudah menjadi\n"
	.string "JUARA!$"

Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort:
	.string "Cucuku pasti sedang menantang JUARA\n"
	.string "LIGA POKéMON sekarang.\p"
	.string "Mengenal cucuku, dia mungkin sudah menjadi\n"
	.string "JUARA!$"

