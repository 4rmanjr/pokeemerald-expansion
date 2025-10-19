Route114_LanettesHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_LanettesHouse_OnTransition
	.byte 0

Route114_LanettesHouse_OnTransition:
	setflag FLAG_LANDMARK_LANETTES_HOUSE
	end

Route114_LanettesHouse_EventScript_Lanette::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_DOLL_LANETTE, Route114_LanettesHouse_EventScript_OfferAdvice
	setflag FLAG_SYS_PC_LANETTE
	msgbox Route114_LanettesHouse_Text_EverythingClutteredKeepThis, MSGBOX_DEFAULT
	givedecoration DECOR_LOTAD_DOLL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowNoRoomForDecor
	setflag FLAG_RECEIVED_DOLL_LANETTE
	release
	end

Route114_LanettesHouse_EventScript_OfferAdvice::
	msgbox Route114_LanettesHouse_Text_OrganizeYourBoxes, MSGBOX_DEFAULT
	release
	end

Route114_LanettesHouse_EventScript_Notebook::
	lockall
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route114_LanettesHouse_EventScript_NotebookPage2
	msgbox Route114_LanettesHouse_Text_ClosedTheNotebook, MSGBOX_DEFAULT
	releaseall
	end

Route114_LanettesHouse_EventScript_NotebookPage2::
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage2, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, Route114_LanettesHouse_EventScript_NotebookPage3
	releaseall
	end

Route114_LanettesHouse_EventScript_NotebookPage3::
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage3, MSGBOX_DEFAULT
	return

Route114_LanettesHouse_EventScript_PC::
	msgbox Route114_LanettesHouse_Text_EmailFromBill, MSGBOX_SIGN
	end

Route114_LanettesHouse_Text_EverythingClutteredKeepThis:
	.string "LANETTE: Oh! {PLAYER}{KUN}!\p"
	.string "Maaf semuanya berantakan…\n"
	.string "Jika aku terlalu asyik meneliti,\l"
	.string "beginilah jadinya…\p"
	.string "Ini memalukan… Tolong rahasiakan\n"
	.string "ini sebagai imbalan untuk ini.$"

Route114_LanettesHouse_Text_OrganizeYourBoxes:
	.string "Bolehkah aku memberimu saran tentang\n"
	.string "Sistem Penyimpanan POKéMON-ku?\p"
	.string "Kamu harus mengatur KOTAK-mu agar\n"
	.string "kamu bisa tahu POKéMON mana yang ada di dalamnya.$"

Route114_LanettesHouse_Text_ResearchNotesPage1:
	.string "Ini catatan penelitian LANETTE.\n"
	.string "Ada informasi tentang KOTAK.\p"
	.string "Rancang KOTAK untuk menampung 30 POKéMON\n"
	.string "masing-masing.\p"
	.string "Setiap TRAINER seharusnya bisa menyimpan\n"
	.string "420 POKéMON di sistem PC.\p"
	.string "Lanjutkan membaca?$"

Route114_LanettesHouse_Text_ResearchNotesPage2:
	.string "Sistem penandaan harus ditambahkan untuk\n"
	.string "membuat POKéMON lebih mudah diatur.\p"
	.string "Nama dan desain wallpaper setiap\n"
	.string "KOTAK akan dibuat dapat diubah untuk\l"
	.string "menyenangkan POKéMON yang disimpan.\p"
	.string "Lanjutkan membaca?$"

Route114_LanettesHouse_Text_ResearchNotesPage3:
	.string "Saat menyimpan POKéMON, seharusnya\n"
	.string "dikirim ke KOTAK yang terakhir diperiksa.\p"
	.string "Jika KOTAK itu penuh, POKéMON yang\n"
	.string "diterima akan disimpan di KOTAK berikutnya.\p"
	.string "Dengan kata lain, saat sebuah KOTAK\n"
	.string "diperiksa, itu akan otomatis terpilih\l"
	.string "sebagai KOTAK tempat POKéMON dikirim.$"

Route114_LanettesHouse_Text_ClosedTheNotebook:
	.string "{PLAYER} menutup buku catatan.$"

Route114_LanettesHouse_Text_EmailFromBill:
	.string "Ada e-mail dari seseorang di\n"
	.string "PC.\p"
	.string "“… … … … … … …\p"
	.string "“Sistem Penyimpananmu menawarkan lebih\n"
	.string "banyak kenyamanan daripada milikku.\p"
	.string "“Sistem ini memiliki banyak fitur yang\n"
	.string "ramah pengguna sehingga menyenangkan\l"
	.string "dan berguna juga.\p"
	.string "“Aku bangga telah menjadi bagian\n"
	.string "dalam pengembangannya.\p"
	.string "“Semoga kamu terus melanjutkan\n"
	.string "penelitian di Sistem Penyimpanan.\p"
	.string "“Dari BILL\n"
	.string "… … … … … … … …”$"

