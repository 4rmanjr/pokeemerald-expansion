Route109_SeashoreHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route109_SeashoreHouse_OnTransition
	.byte 0

Route109_SeashoreHouse_OnTransition:
	setflag FLAG_LANDMARK_SEASHORE_HOUSE
	end

Route109_SeashoreHouse_EventScript_Owner::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_6_SODA_POP, Route109_SeashoreHouse_EventScript_AlreadyReceivedSodaPop
	goto_if_set FLAG_DEFEATED_SEASHORE_HOUSE, Route109_SeashoreHouse_EventScript_DefeatedTrainers
	goto_if_set FLAG_TEMP_2, Route109_SeashoreHouse_EventScript_AlreadyGaveIntroduction
	msgbox Route109_SeashoreHouse_Text_SeashoreHouseIntro, MSGBOX_DEFAULT
	setflag FLAG_TEMP_2
	release
	end

Route109_SeashoreHouse_EventScript_AlreadyGaveIntroduction::
	msgbox Route109_SeashoreHouse_Text_ShowMeSomeHotMatches, MSGBOX_DEFAULT
	release
	end

Route109_SeashoreHouse_EventScript_DefeatedTrainers::
	msgbox Route109_SeashoreHouse_Text_TakeTheseSodaPopBottles, MSGBOX_DEFAULT
	giveitem ITEM_SODA_POP, 6
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_BagFull
	setflag FLAG_RECEIVED_6_SODA_POP
	release
	end

Route109_SeashoreHouse_EventScript_BagFull::
	msgbox Route109_SeashoreHouse_Text_BagFull, MSGBOX_DEFAULT
	release
	end

Route109_SeashoreHouse_EventScript_AlreadyReceivedSodaPop::
	showmoneybox 0, 0
	msgbox Route109_SeashoreHouse_Text_WantToBuySodaPop, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route109_SeashoreHouse_EventScript_BuySodaPop
	msgbox Route109_SeashoreHouse_Text_ThatsTooBad, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_BuySodaPop::
	checkmoney 300
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_NotEnoughMoney
	checkitemspace ITEM_SODA_POP
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_NotEnoughSpace
	msgbox Route109_SeashoreHouse_Text_HereYouGo, MSGBOX_DEFAULT
	removemoney 300
	updatemoneybox
.if OW_SHOW_ITEM_DESCRIPTIONS != OW_ITEM_DESCRIPTIONS_OFF
	hidemoneybox
	giveitem ITEM_SODA_POP
.else
	giveitem ITEM_SODA_POP
	hidemoneybox
.endif
	release
	end

Route109_SeashoreHouse_EventScript_NotEnoughMoney::
	msgbox Route109_SeashoreHouse_Text_NotEnoughMoney, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_NotEnoughSpace::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_Dwayne::
	trainerbattle_single TRAINER_DWAYNE, Route109_SeashoreHouse_Text_DwayneIntro, Route109_SeashoreHouse_Text_DwayneDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_DwaynePostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_Johanna::
	trainerbattle_single TRAINER_JOHANNA, Route109_SeashoreHouse_Text_JohannaIntro, Route109_SeashoreHouse_Text_JohannaDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_JohannaPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_Simon::
	trainerbattle_single TRAINER_SIMON, Route109_SeashoreHouse_Text_SimonIntro, Route109_SeashoreHouse_Text_SimonDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_SimonPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_CheckTrainersCompletion::
	goto_if_not_defeated TRAINER_DWAYNE, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	goto_if_not_defeated TRAINER_JOHANNA, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	goto_if_not_defeated TRAINER_SIMON, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	setflag FLAG_DEFEATED_SEASHORE_HOUSE
	release
	end

Route109_SeashoreHouse_EventScript_TrainersNotCompleted::
	release
	end

Route109_SeashoreHouse_Text_SeashoreHouseIntro:
	.string "Aku pemilik RUMAH PANTAI.\n"
	.string "Tapi kamu bisa memanggilku MR. SEA!\p"
	.string "Yang paling Aku suka adalah melihat\n"
	.string "pertarungan POKéMON yang seru.\p"
	.string "Biarkan Aku melihat hatimu membara!\p"
	.string "Jika kamu bisa mengalahkan semua TRAINER\n"
	.string "di sini, Aku akan menghargai usahamu.$"

Route109_SeashoreHouse_Text_ShowMeSomeHotMatches:
	.string "Tunjukkan padaku pertandingan yang seru!\p"
	.string "Aku menjalankan RUMAH PANTAI ini hanya\n"
	.string "untuk alasan itu saja!$"

Route109_SeashoreHouse_Text_TakeTheseSodaPopBottles:
	.string "Kamu sangat bersemangat!\n"
	.string "Pertarungan itu berkobar!\l"
	.string "Aku lebih dari sekadar puas!\p"
	.string "Sebagai ucapan terima kasih karena telah\n"
	.string "menunjukkan semangatmu, Aku ingin kamu mengambil ini.\p"
	.string "Ini setengah lusin botol SODA POP!$"

Route109_SeashoreHouse_Text_BagFull:
	.string "Oh, tapi hei, TAS-mu penuh sesak.\n"
	.string "Aku akan menyimpannya untukmu.$"

Route109_SeashoreHouse_Text_WantToBuySodaPop:
	.string "Mau beli SODA POP?\n"
	.string "POKéMON menyukainya!\p"
	.string "Hanya ¥300 sebotol!\n"
	.string "Belilah!$"

Route109_SeashoreHouse_Text_HereYouGo:
	.string "Ini dia!$"

Route109_SeashoreHouse_Text_NotEnoughMoney:
	.string "Kamu tidak punya uang.$"

Route109_SeashoreHouse_Text_ThatsTooBad:
	.string "Tidak?\n"
	.string "Sayang sekali.$"

Route109_SeashoreHouse_Text_DwayneIntro:
	.string "Jika kamu mencari pertarungan di\n"
	.string "RUMAH PANTAI, kamu tidak akan menemukan\l"
	.string "TRAINER yang lebih bersemangat dariku, kawan!$"

Route109_SeashoreHouse_Text_DwayneDefeated:
	.string "Itu pertarungan yang seru!\n"
	.string "Aku bisa menerima kekalahan itu, kawan!$"

Route109_SeashoreHouse_Text_DwaynePostBattle:
	.string "Kapan pun Aku di SLATEPORT, Aku menikmati\n"
	.string "pertarungan seru dan SODA POP dingin!$"

Route109_SeashoreHouse_Text_JohannaIntro:
	.string "Pertarungan yang membosankan tidak sebanding\n"
	.string "dengan usaha.\p"
	.string "Pertarungan yang membara itulah yang\n"
	.string "menguatkan TRAINER dan POKéMON!$"

Route109_SeashoreHouse_Text_JohannaDefeated:
	.string "Itu panas!$"

Route109_SeashoreHouse_Text_JohannaPostBattle:
	.string "Fiuh, Aku haus sekali.\n"
	.string "Mungkin Aku akan minum SODA POP.$"

Route109_SeashoreHouse_Text_SimonIntro:
	.string "Aku akan menunjukkan padamu betapa hebatnya\n"
	.string "POKéMON-ku, tapi jangan menangis!$"

Route109_SeashoreHouse_Text_SimonDefeated:
	.string "…Aku kalah, tapi Aku tidak akan menangis…$"

Route109_SeashoreHouse_Text_SimonPostBattle:
	.string "Jika salah satu POKéMON-ku tahu jurus\n"
	.string "untuk membawaku menyeberangi air di\l"
	.string "punggungnya, Aku bisa membuang ban dalam ini.$"

