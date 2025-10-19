MauvilleCity_BikeShop_MapScripts::
	.byte 0

MauvilleCity_BikeShop_EventScript_Rydel::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_BIKE, MauvilleCity_BikeShop_EventScript_AskSwitchBikes
	goto_if_set FLAG_DECLINED_BIKE, MauvilleCity_BikeShop_EventScript_SkipGreeting
	msgbox MauvilleCity_BikeShop_Text_RydelGreeting, MSGBOX_DEFAULT
	msgbox MauvilleCity_BikeShop_Text_DidYouComeFromFarAway, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_YesFar
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_NotFar
	end

MauvilleCity_BikeShop_EventScript_SkipGreeting::
	msgbox MauvilleCity_BikeShop_Text_DidYouComeFromFarAway, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_YesFar
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_NotFar
	end

MauvilleCity_BikeShop_EventScript_ChooseBike::
	message MauvilleCity_BikeShop_Text_ExplainBikesChooseWhichOne
	waitmessage
	multichoice 21, 8, MULTI_BIKE, TRUE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_GetMachBike
	case 1, MauvilleCity_BikeShop_EventScript_GetAcroBike
	end

MauvilleCity_BikeShop_EventScript_NotFar::
	setflag FLAG_DECLINED_BIKE
	msgbox MauvilleCity_BikeShop_Text_GuessYouDontNeedBike, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_YesFar::
	setflag FLAG_RECEIVED_BIKE
	goto MauvilleCity_BikeShop_EventScript_ChooseBike
	end

MauvilleCity_BikeShop_EventScript_GetMachBike::
	msgbox MauvilleCity_BikeShop_Text_ChoseMachBike, MSGBOX_DEFAULT
	giveitem ITEM_MACH_BIKE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_GetAcroBike::
	msgbox MauvilleCity_BikeShop_Text_ChoseAcroBike, MSGBOX_DEFAULT
	giveitem ITEM_ACRO_BIKE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_ComeBackToSwitchBikes, MSGBOX_DEFAULT
	special SwapRegisteredBike
	release
	end

MauvilleCity_BikeShop_EventScript_AskSwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_WantToSwitchBikes, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_SwitchBikes
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_KeepBike
	end

@ If the player does not have a bike on them Rydel assumes its stored in the PC
MauvilleCity_BikeShop_EventScript_SwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_IllSwitchBikes, MSGBOX_DEFAULT
	checkitem ITEM_ACRO_BIKE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_BikeShop_EventScript_SwitchAcroForMach
	checkitem ITEM_MACH_BIKE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_BikeShop_EventScript_SwitchMachForAcro
	msgbox MauvilleCity_BikeShop_Text_OhYourBikeIsInPC, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_KeepBike::
	msgbox MauvilleCity_BikeShop_Text_HappyYouLikeIt, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_SwitchAcroForMach::
	incrementgamestat GAME_STAT_TRADED_BIKES
	msgbox MauvilleCity_BikeShop_Text_ExchangedAcroForMach, MSGBOX_DEFAULT
	removeitem ITEM_ACRO_BIKE
	giveitem ITEM_MACH_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_SwitchMachForAcro::
	incrementgamestat GAME_STAT_TRADED_BIKES
	msgbox MauvilleCity_BikeShop_Text_ExchangedMachForAcro, MSGBOX_DEFAULT
	removeitem ITEM_MACH_BIKE
	giveitem ITEM_ACRO_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_Assistant::
	msgbox MauvilleCity_BikeShop_Text_HandbooksAreInBack, MSGBOX_NPC
	end

MauvilleCity_BikeShop_EventScript_MachBikeHandbook::
	message MauvilleCity_BikeShop_Text_MachHandbookWhichPage
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage::
	multichoice 0, 0, MULTI_MACH_BIKE_INFO, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_HowToRide
	case 1, MauvilleCity_BikeShop_EventScript_HowToTurn
	case 2, MauvilleCity_BikeShop_EventScript_SandySlopes
	case 3, MauvilleCity_BikeShop_EventScript_ExitMachHandbook
	case MULTI_B_PRESSED, MauvilleCity_BikeShop_EventScript_ExitMachHandbook
	end

MauvilleCity_BikeShop_EventScript_HowToRide::
	message MauvilleCity_BikeShop_Text_HowToRideMachBike
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_HowToTurn::
	message MauvilleCity_BikeShop_Text_HowToTurnMachBike
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_SandySlopes::
	message MauvilleCity_BikeShop_Text_SandySlopes
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ExitMachHandbook::
	release
	end

MauvilleCity_BikeShop_EventScript_AcroBikeHandbook::
	message MauvilleCity_BikeShop_Text_AcroHandbookWhichPage
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage::
	multichoice 0, 0, MULTI_ACRO_BIKE_INFO, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_Wheelies
	case 1, MauvilleCity_BikeShop_EventScript_BunnyHops
	case 2, MauvilleCity_BikeShop_EventScript_Jumps
	case 3, MauvilleCity_BikeShop_EventScript_ExitAcroHandbook
	case MULTI_B_PRESSED, MauvilleCity_BikeShop_EventScript_ExitAcroHandbook
	end

MauvilleCity_BikeShop_EventScript_Wheelies::
	message MauvilleCity_BikeShop_Text_Wheelies
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_BunnyHops::
	message MauvilleCity_BikeShop_Text_BunnyHops
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_Jumps::
	message MauvilleCity_BikeShop_Text_Jumps
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ExitAcroHandbook::
	release
	end

MauvilleCity_BikeShop_Text_RydelGreeting:
	.string "Wah, wah, siapa ini?\n"
	.string "Pelanggan yang sangat bersemangat!\p"
	.string "Aku? Panggil saja aku RYDEL.\n"
	.string "Aku pemilik toko sepeda ini.$"

MauvilleCity_BikeShop_Text_DidYouComeFromFarAway:
	.string "RYDEL: RUNNING SHOES-mu…\n"
	.string "Kotor sekali.\p"
	.string "Apa kamu datang dari jauh?$"

MauvilleCity_BikeShop_Text_GuessYouDontNeedBike:
	.string "RYDEL: Begitukah?\p"
	.string "Kalau begitu, kurasa kamu tidak butuh\n"
	.string "SEPEDA-ku.$"

MauvilleCity_BikeShop_Text_ExplainBikesChooseWhichOne:
	.string "RYDEL: Hm, hm… … … … …\p"
	.string "Kamu bilang kamu datang jauh-jauh\n"
	.string "dari LITTLEROOT?\p"
	.string "Astaga!\n"
	.string "Itu jauh sekali!\p"
	.string "Kalau kamu punya salah satu SEPEDA-ku,\n"
	.string "kamu bisa pergi ke mana saja dengan mudah\l"
	.string "sambil merasakan belaian angin!\p"
	.string "Begini saja!\n"
	.string "Aku akan memberimu SEPEDA!\p"
	.string "Oh, tunggu sebentar!\p"
	.string "Aku lupa memberitahumu ada dua jenis\n"
	.string "SEPEDA!\p"
	.string "Yaitu MACH BIKE dan\n"
	.string "ACRO BIKE!\p"
	.string "MACH BIKE untuk pesepeda yang ingin\n"
	.string "merasakan angin dengan tubuh mereka!\p"
	.string "Dan ACRO BIKE untuk mereka yang lebih\n"
	.string "suka bersepeda teknis!\p"
	.string "Aku orang yang baik hati, jadi kamu bisa\n"
	.string "mendapatkan yang mana saja yang kamu suka!\p"
	.string "Mana yang akan kamu pilih?$"

MauvilleCity_BikeShop_Text_ChoseMachBike:
	.string "{PLAYER} memilih MACH BIKE.$"

MauvilleCity_BikeShop_Text_ChoseAcroBike:
	.string "{PLAYER} memilih ACRO BIKE.$"

MauvilleCity_BikeShop_Text_ComeBackToSwitchBikes:
	.string "RYDEL: Jika kamu ingin menukar\n"
	.string "SEPEDA, temui saja aku!$"

MauvilleCity_BikeShop_Text_WantToSwitchBikes:
	.string "RYDEL: Oh? Apa kamu berpikir untuk\n"
	.string "menukar SEPEDA?$"

MauvilleCity_BikeShop_Text_IllSwitchBikes:
	.string "RYDEL: Oke, tidak masalah!\n"
	.string "Aku akan menukarkan SEPEDA untukmu!$"

MauvilleCity_BikeShop_Text_ExchangedMachForAcro:
	.string "MACH BIKE ditukar dengan\n"
	.string "ACRO BIKE.$"

MauvilleCity_BikeShop_Text_ExchangedAcroForMach:
	.string "ACRO BIKE ditukar dengan\n"
	.string "MACH BIKE.$"

MauvilleCity_BikeShop_Text_HappyYouLikeIt:
	.string "RYDEL: Bagus, bagus!\n"
	.string "Aku senang kamu menyukainya!$"

MauvilleCity_BikeShop_Text_OhYourBikeIsInPC:
	.string "Oh? Apa yang terjadi dengan SEPEDA\n"
	.string "yang kuberikan padamu?\p"
	.string "Oh, aku mengerti, kamu menyimpannya\n"
	.string "menggunakan PC-mu.\p"
	.string "Baiklah, keluarkan dari penyimpanan PC,\n"
	.string "dan aku akan dengan senang hati\l"
	.string "menukarnya!\p"
	.string "Semoga angin selalu menyertaimu dalam\n"
	.string "petualanganmu!$"

MauvilleCity_BikeShop_Text_HandbooksAreInBack:
	.string "Aku belajar tentang SEPEDA sambil\n"
	.string "bekerja di sini.\p"
	.string "Jika kamu butuh saran cara mengendarai\n"
	.string "SEPEDA, ada beberapa buku panduan di\l"
	.string "belakang.$"

MauvilleCity_BikeShop_Text_MachHandbookWhichPage:
	.string "Ini buku panduan MACH BIKE.\p"
	.string "Halaman mana yang ingin kamu baca?$"

MauvilleCity_BikeShop_Text_HowToRideMachBike:
	.string "SEPEDA bergerak ke arah + Control Pad\n"
	.string "ditekan.\p"
	.string "Kecepatannya akan bertambah setelah\n"
	.string "mulai berjalan.\p"
	.string "Untuk berhenti, lepaskan + Control Pad.\n"
	.string "SEPEDA akan melambat hingga berhenti.\p"
	.string "Ingin membaca halaman lain?$"

MauvilleCity_BikeShop_Text_HowToTurnMachBike:
	.string "MACH BIKE cepat, tapi tidak bisa\n"
	.string "berhenti dengan cepat.\p"
	.string "Agak sulit untuk berbelok di tikungan.\p"
	.string "Lepaskan + Control Pad sedikit sebelum\n"
	.string "tikungan dan perlambat.\p"
	.string "Ingin membaca halaman lain?$"

MauvilleCity_BikeShop_Text_SandySlopes:
	.string "Ada lereng berpasir kecil di seluruh\n"
	.string "wilayah HOENN.\p"
	.string "Pasir yang gembur dan mudah hancur\n"
	.string "membuatnya mustahil untuk didaki secara\l"
	.string "normal.\p"
	.string "Tapi jika kamu punya MACH BIKE, kamu bisa\n"
	.string "menaiki lereng berpasir.\p"
	.string "Ingin membaca halaman lain?$"

MauvilleCity_BikeShop_Text_AcroHandbookWhichPage:
	.string "Ini buku panduan ACRO BIKE.\p"
	.string "Halaman mana yang ingin kamu baca?$"

MauvilleCity_BikeShop_Text_Wheelies:
	.string "Tekan Tombol B saat berkendara, dan\n"
	.string "roda depan akan terangkat.\p"
	.string "Kamu bisa berkeliling dengan roda depan\n"
	.string "terangkat menggunakan + Control Pad.\p"
	.string "Teknik ini disebut wheelie.\p"
	.string "Ingin membaca halaman lain?$"

MauvilleCity_BikeShop_Text_BunnyHops:
	.string "Dengan menahan Tombol B, SEPEDA-mu bisa\n"
	.string "melompat di tempat.\p"
	.string "Teknik ini disebut bunny hop.\p"
	.string "Kamu juga bisa berkendara sambil\n"
	.string "melompat.\p"
	.string "Ingin membaca halaman lain?$"

MauvilleCity_BikeShop_Text_Jumps:
	.string "Tekan Tombol B dan + Control Pad\n"
	.string "bersamaan untuk melompat.\p"
	.string "Tekan + Control Pad ke samping untuk\n"
	.string "melompat ke samping.\p"
	.string "Tekan ke belakang untuk membuat SEPEDA\n"
	.string "berubah arah saat melompat.\p"
	.string "Ingin membaca halaman lain?$"

