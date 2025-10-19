SSTidalRooms_MapScripts::
	.byte 0

SSTidalRooms_EventScript_SnatchGiver::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_SNATCH, SSTidalRooms_EventScript_ExplainSnatch
	msgbox SSTidalRooms_Text_NotSuspiciousTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_SNATCH
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_SNATCH
	msgbox SSTidalRooms_Text_ExplainSnatch, MSGBOX_DEFAULT
	release
	end

SSTidalRooms_EventScript_ExplainSnatch::
	msgbox SSTidalRooms_Text_ExplainSnatch, MSGBOX_DEFAULT
	release
	end

SSTidalRooms_EventScript_Bed::
	lockall
	msgbox SSTidalRooms_Text_TakeRestOnBed, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	call SSTidalRooms_EventScript_ProgessCruiseAfterBed
	releaseall
	end

SSTidalRooms_EventScript_Colton::
	trainerbattle_single TRAINER_COLTON, SSTidalRooms_Text_ColtonIntro, SSTidalRooms_Text_ColtonDefeat
	msgbox SSTidalRooms_Text_ColtonPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Micah::
	trainerbattle_single TRAINER_MICAH, SSTidalRooms_Text_MicahIntro, SSTidalRooms_Text_MicahDefeat
	msgbox SSTidalRooms_Text_MicahPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Thomas::
	trainerbattle_single TRAINER_THOMAS, SSTidalRooms_Text_ThomasIntro, SSTidalRooms_Text_ThomasDefeat
	msgbox SSTidalRooms_Text_ThomasPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Jed::
	trainerbattle_double TRAINER_LEA_AND_JED, SSTidalRooms_Text_JedIntro, SSTidalRooms_Text_JedDefeat, SSTidalRooms_Text_JedNotEnoughMons
	msgbox SSTidalRooms_Text_JedPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Lea::
	trainerbattle_double TRAINER_LEA_AND_JED, SSTidalRooms_Text_LeaIntro, SSTidalRooms_Text_LeaDefeat, SSTidalRooms_Text_LeaNotEnoughMons
	msgbox SSTidalRooms_Text_LeaPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Garret::
	trainerbattle_single TRAINER_GARRET, SSTidalRooms_Text_GarretIntro, SSTidalRooms_Text_GarretDefeat
	msgbox SSTidalRooms_Text_GarretPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Naomi::
	trainerbattle_single TRAINER_NAOMI, SSTidalRooms_Text_NaomiIntro, SSTidalRooms_Text_NaomiDefeat
	msgbox SSTidalRooms_Text_NaomiPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_Text_TakeRestOnBed:
	.string "Ada tempat tidur…\n"
	.string "Ayo kita beristirahat.$"

SSTidalRooms_Text_ColtonIntro:
	.string "Aku sering berlayar ke LILYCOVE CITY.\p"
	.string "Aku suka mengikuti CONTEST,\n"
	.string "tahu tidak.$"

SSTidalRooms_Text_ColtonDefeat:
	.string "Itu pertandingan yang menyenangkan!$"

SSTidalRooms_Text_ColtonPostBattle:
	.string "Aku sangat bersemangat membayangkan jenis\n"
	.string "POKéMON apa yang akan aku lihat di\l"
	.string "CONTEST berikutnya. Antisipasinya mendebarkan!$"

SSTidalRooms_Text_MicahIntro:
	.string "Apakah teman-temanmu kuat?$"

SSTidalRooms_Text_MicahDefeat:
	.string "Teman-temanmu, memang, kuat.$"

SSTidalRooms_Text_MicahPostBattle:
	.string "Teman tidak harus manusia.\n"
	.string "Bagiku, POKéMON adalah teman berharga!$"

SSTidalRooms_Text_ThomasIntro:
	.string "Anak kecil…\n"
	.string "Apakah kamu mengetuk pintu?$"

SSTidalRooms_Text_ThomasDefeat:
	.string "Kekalahan harus diterima tanpa tergesa-gesa\n"
	.string "atau panik.$"

SSTidalRooms_Text_ThomasPostBattle:
	.string "Tidak pernah gelisah dalam situasi apa pun\n"
	.string "adalah kode etik GENTLEMAN.$"

SSTidalRooms_Text_JedIntro:
	.string "JED: Aku sedikit malu tentang ini, tapi…\n"
	.string "Kami akan menunjukkan kekuatan cinta-cintaan kami!$"

SSTidalRooms_Text_JedDefeat:
	.string "JED: Huh…$"

SSTidalRooms_Text_JedPostBattle:
	.string "JED: Ini pertama kalinya kekuatan\n"
	.string "cinta-cintaan kami tidak bisa menang!\l"
	.string "Kamu pasti TRAINER yang luar biasa!$"

SSTidalRooms_Text_JedNotEnoughMons:
	.string "JED: Kamu hanya punya satu POKéMON?\n"
	.string "Bukankah itu terlalu sepi?$"

SSTidalRooms_Text_LeaIntro:
	.string "LEA: Aku merasa sedikit konyol, tapi…\n"
	.string "Kami akan menunjukkan kekuatan cinta-cintaan kami!$"

SSTidalRooms_Text_LeaDefeat:
	.string "LEA: Oh, boo!$"

SSTidalRooms_Text_LeaPostBattle:
	.string "LEA: Aku tidak percaya!\n"
	.string "Kekuatan cinta-cintaan kami gagal…\l"
	.string "Kamu pasti TRAINER yang luar biasa!$"

SSTidalRooms_Text_LeaNotEnoughMons:
	.string "LEA: Aku ingin bertarung…\n"
	.string "Tapi kamu bahkan tidak punya dua POKéMON…$"

SSTidalRooms_Text_GarretIntro:
	.string "Ah, kamu datang tepat waktu.\p"
	.string "Aku bosan, tahu tidak.\n"
	.string "Kamu bisa menghiburku.$"

SSTidalRooms_Text_GarretDefeat:
	.string "…Cukup sudah.$"

SSTidalRooms_Text_GarretPostBattle:
	.string "Mungkin aku akan meminta Ayah untuk\n"
	.string "membelikan yacht untukku.\l"
	.string "Sebuah yacht untukku dan POKéMON!$"

SSTidalRooms_Text_NaomiIntro:
	.string "Oh, kamu TRAINER yang sangat menggemaskan.\n"
	.string "Mau minum teh?\l"
	.string "Atau kamu lebih suka bertarung?$"

SSTidalRooms_Text_NaomiDefeat:
	.string "Aku mengerti.\n"
	.string "Kamu tipe yang aktif.$"

SSTidalRooms_Text_NaomiPostBattle:
	.string "Pelayaran keliling dunia dengan kapal\n"
	.string "pesiar mewah memang punya daya tariknya,\n"
	.string "harus kuakui…\p"
	.string "Tapi, aku akui ada sisi menarik\n"
	.string "dalam tur HOENN dengan feri.$"

SSTidalRooms_Text_NotSuspiciousTakeThis:
	.string "Uh… Hai! Aku… aku tidak bertingkah\n"
	.string "mencurigakan! Uh… Kamu bisa ambil ini! Gratis!\p"
	.string "Ini… Jujur saja, aku tidak SNATCH dari\n"
	.string "siapa pun! Aku tidak akan pernah melakukan\n"
	.string "hal seperti itu!\l"
	.string "Ini bersih! Kamu bisa menggunakannya!$"

SSTidalRooms_Text_ExplainSnatch:
	.string "SNATCH mencuri efek menguntungkan\n"
	.string "dari gerakan tertentu sebelum dapat\l"
	.string "digunakan oleh musuh atau sekutu.$"

