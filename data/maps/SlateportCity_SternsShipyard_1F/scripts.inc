SlateportCity_SternsShipyard_1F_MapScripts::
	.byte 0

SlateportCity_SternsShipyard_1F_EventScript_Dock::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_SternsShipyard_1F_EventScript_FerryReady
	goto_if_set FLAG_BADGE07_GET, SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined
	goto_if_set FLAG_DELIVERED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran
	goto_if_set FLAG_DOCK_REJECTED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_GoFindStern
	msgbox SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails, MSGBOX_DEFAULT
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_DOCK_REJECTED_DEVON_GOODS
	setflag FLAG_HIDE_SLATEPORT_CITY_TEAM_AQUA
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_FerryReady::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_FerryIsReady, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_GoFindStern::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist1::
	msgbox SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist2::
	msgbox SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Briney::
	msgbox SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails:
	.string "Umm… Kalau ini di sini, dan itu\n"
	.string "di sana…\p"
	.string "Lalu ke mana benda ini pergi?\n"
	.string "Dan bagaimana dengan doohickey itu?\p"
	.string "Aaargh! Aku tidak mengerti\n"
	.string "ini sama sekali!$"

SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern:
	.string "Hm?\n"
	.string "Hai, aku DOCK.\p"
	.string "KAPTEN STERN menugaskanku untuk\n"
	.string "merancang feri.\p"
	.string "Oh! Itu di sana…\n"
	.string "Apakah itu DEVON GOODS?\p"
	.string "Tapi, hmm…\n"
	.string "Ini tidak akan berhasil…\p"
	.string "KAPTEN STERN pergi entah ke mana.\n"
	.string "Dia bilang ada pekerjaan yang harus dilakukan.\p"
	.string "Bisakah aku memintamu untuk mencari KAPTEN\n"
	.string "STERN dan menyerahkan ini padanya?$"

SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern:
	.string "DOCK: Ke mana KAPTEN STERN pergi, ya?\p"
	.string "Bisakah kamu mencari KAPTEN STERN dan\n"
	.string "mengantarkan paket itu padanya?$"

SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran:
	.string "DOCK: Pembuatan kapal adalah seni.\p"
	.string "Banyak hal yang tidak bisa dipecahkan\n"
	.string "hanya dengan perhitungan.\p"
	.string "Aku sangat membutuhkan nasihat dari\n"
	.string "veteran yang tahu laut…$"

SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs:
	.string "DOCK: Hai! MR. BRINEY bergabung dengan\n"
	.string "kami untuk memberikan bantuannya.\p"
	.string "Berkat pelaut veteran itu, feri\n"
	.string "perlahan-lahan mulai terbentuk.$"

SlateportCity_SternsShipyard_1F_Text_FerryIsReady:
	.string "DOCK: Feri akhirnya siap!\p"
	.string "S.S. TIDAL yang baru benar-benar\n"
	.string "keajaiban teknologi!\p"
	.string "Tapi, aku merasa kita bisa\n"
	.string "membuat sesuatu yang lebih baik lagi.\p"
	.string "Kamu tahu, tidak ada habisnya\n"
	.string "kemajuan teknologi.$"

SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock:
	.string "MR. BRINEY: Ah, {PLAYER}{KUN}!\n"
	.string "Sudah lama sekali!\p"
	.string "Ya, sejak aku bertemu denganmu, anjing\n"
	.string "laut tua ini merasa bersemangat!\p"
	.string "Jadi aku memutuskan untuk membantu DOCK\n"
	.string "membuat feri.\p"
	.string "Ya, bagaimanapun juga, feri akan dapat\n"
	.string "mengangkut banyak orang.\p"
	.string "Tapi, kamu tahu, DOCK itu benar-benar\n"
	.string "sesuatu yang istimewa.\p"
	.string "Dengan keahliannya di bidang teknologi dan\n"
	.string "pengalamanku, aku yakin kita bisa\l"
	.string "membangun kapal yang hebat, ya!$"

SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing:
	.string "Musim, cuaca, posisi bulan\n"
	.string "di langit…\p"
	.string "Ini dan kondisi lainnya membuat\n"
	.string "laut mengubah ekspresinya.\p"
	.string "Benar!\n"
	.string "Laut itu seperti makhluk hidup!$"

SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily:
	.string "Aku sangat mudah mabuk laut.\n"
	.string "Jadi aku membantu di sini saja.$"

