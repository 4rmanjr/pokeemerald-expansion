SlateportCity_PokemonFanClub_MapScripts::
	.byte 0

SlateportCity_PokemonFanClub_EventScript_Chairman::
	lock
	faceplayer
	goto_if_unset FLAG_ENTERED_CONTEST, SlateportCity_PokemonFanClub_EventScript_ChairmanNotEnteredContest
	call_if_unset FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN, SlateportCity_PokemonFanClub_EventScript_MeetChairman
	switch VAR_SLATEPORT_FAN_CLUB_STATE
	case 0, SlateportCity_PokemonFanClub_EventScript_ChairmanFirstAssessment
	case 1, SlateportCity_PokemonFanClub_EventScript_ChairmanTryAssessPokemon
	case 2, SlateportCity_PokemonFanClub_EventScript_NoMoreScarves
	release
	end

SlateportCity_PokemonFanClub_EventScript_ChairmanFirstAssessment::
	setvar VAR_SLATEPORT_FAN_CLUB_STATE, 1
	msgbox SlateportCity_PokemonFanClub_Text_AllowMeToExamineYourPokemon, MSGBOX_DEFAULT
	goto SlateportCity_PokemonFanClub_EventScript_ChairmanAssessLeadMon
	end

SlateportCity_PokemonFanClub_EventScript_ChairmanTryAssessPokemon::
	setvar VAR_TEMP_2, 0
	call_if_set FLAG_RECEIVED_YELLOW_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_set FLAG_RECEIVED_GREEN_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_set FLAG_RECEIVED_PINK_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_set FLAG_RECEIVED_BLUE_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_set FLAG_RECEIVED_RED_SCARF, SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf
	call_if_eq VAR_TEMP_2, CONTEST_CATEGORIES_COUNT, SlateportCity_PokemonFanClub_EventScript_ReceivedAllScarves
	goto_if_eq VAR_SLATEPORT_FAN_CLUB_STATE, 2, SlateportCity_PokemonFanClub_EventScript_NoMoreScarves
	msgbox SlateportCity_PokemonFanClub_Text_HowIsYourPokemonGrowing, MSGBOX_DEFAULT
	goto SlateportCity_PokemonFanClub_EventScript_ChairmanAssessLeadMon
	end

SlateportCity_PokemonFanClub_EventScript_NoMoreScarves::
	msgbox SlateportCity_PokemonFanClub_Text_NothingElseToGiveYou, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_ChairmanAssessLeadMon::
	msgbox SlateportCity_PokemonFanClub_Text_HmHmISee, MSGBOX_DEFAULT
	setvar VAR_TEMP_1, 0
	call_if_unset FLAG_RECEIVED_YELLOW_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonTough
	call_if_unset FLAG_RECEIVED_GREEN_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonSmart
	call_if_unset FLAG_RECEIVED_PINK_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonCute
	call_if_unset FLAG_RECEIVED_BLUE_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonBeauty
	call_if_unset FLAG_RECEIVED_RED_SCARF, SlateportCity_PokemonFanClub_EventScript_CheckMonCool
	bufferleadmonspeciesname STR_VAR_1
	switch VAR_TEMP_1
	case 0, SlateportCity_PokemonFanClub_EventScript_NoHighConditions
	case 1, SlateportCity_PokemonFanClub_EventScript_GiveRedScarf
	case 2, SlateportCity_PokemonFanClub_EventScript_GiveBlueScarf
	case 3, SlateportCity_PokemonFanClub_EventScript_GivePinkScarf
	case 4, SlateportCity_PokemonFanClub_EventScript_GiveGreenScarf
	case 5, SlateportCity_PokemonFanClub_EventScript_GiveYellowScarf
	release
	end

SlateportCity_PokemonFanClub_EventScript_ReceivedAllScarves::
	setvar VAR_SLATEPORT_FAN_CLUB_STATE, 2
	return

SlateportCity_PokemonFanClub_EventScript_CountReceivedScarf::
	addvar VAR_TEMP_2, 1
	return

SlateportCity_PokemonFanClub_EventScript_NoHighConditions::
	msgbox SlateportCity_PokemonFanClub_Text_GiveMonMorePokeblocks, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveRedScarf::
	checkitemspace ITEM_RED_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_RED_SCARF
	giveitem ITEM_RED_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainRedScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveBlueScarf::
	checkitemspace ITEM_BLUE_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_BLUE_SCARF
	giveitem ITEM_BLUE_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainBlueScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GivePinkScarf::
	checkitemspace ITEM_PINK_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_PINK_SCARF
	giveitem ITEM_PINK_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainPinkScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveGreenScarf::
	checkitemspace ITEM_GREEN_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_GREEN_SCARF
	giveitem ITEM_GREEN_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainGreenScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveYellowScarf::
	checkitemspace ITEM_YELLOW_SCARF
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf
	msgbox SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_YELLOW_SCARF
	giveitem ITEM_YELLOW_SCARF
	msgbox SlateportCity_PokemonFanClub_Text_ExplainYellowScarf, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_NoRoomForScarf::
	msgbox SlateportCity_PokemonFanClub_Text_NoSpaceForReward, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_CheckMonCool::
	specialvar VAR_RESULT, CheckLeadMonCool
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonCool
	return

SlateportCity_PokemonFanClub_EventScript_SetMonCool::
	setvar VAR_TEMP_1, 1
	return

SlateportCity_PokemonFanClub_EventScript_CheckMonBeauty::
	specialvar VAR_RESULT, CheckLeadMonBeauty
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonBeauty
	return

SlateportCity_PokemonFanClub_EventScript_SetMonBeauty::
	setvar VAR_TEMP_1, 2
	return

SlateportCity_PokemonFanClub_EventScript_CheckMonCute::
	specialvar VAR_RESULT, CheckLeadMonCute
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonCute
	return

SlateportCity_PokemonFanClub_EventScript_SetMonCute::
	setvar VAR_TEMP_1, 3
	return

SlateportCity_PokemonFanClub_EventScript_CheckMonSmart::
	specialvar VAR_RESULT, CheckLeadMonSmart
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonSmart
	return

SlateportCity_PokemonFanClub_EventScript_SetMonSmart::
	setvar VAR_TEMP_1, 4
	return

SlateportCity_PokemonFanClub_EventScript_CheckMonTough::
	specialvar VAR_RESULT, CheckLeadMonTough
	call_if_eq VAR_RESULT, TRUE, SlateportCity_PokemonFanClub_EventScript_SetMonTough
	return

SlateportCity_PokemonFanClub_EventScript_SetMonTough::
	setvar VAR_TEMP_1, 5
	return

SlateportCity_PokemonFanClub_EventScript_ChairmanNotEnteredContest::
	goto_if_set FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN, SlateportCity_PokemonFanClub_EventScript_ChairmanEnterContest
	msgbox SlateportCity_PokemonFanClub_Text_MeetChairman, MSGBOX_DEFAULT
	setflag FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN
	release
	end

SlateportCity_PokemonFanClub_EventScript_ChairmanEnterContest::
	msgbox SlateportCity_PokemonFanClub_Text_LikeToSeeEnteredContestPokemon, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_MeetChairman::
	msgbox SlateportCity_PokemonFanClub_Text_MeetChairman, MSGBOX_DEFAULT
	setflag FLAG_MET_SLATEPORT_FANCLUB_CHAIRMAN
	return

SlateportCity_PokemonFanClub_EventScript_SootheBellWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SOOTHE_BELL, SlateportCity_PokemonFanClub_EventScript_ReceivedSootheBell
	msgbox SlateportCity_PokemonFanClub_Text_ShowMePokemonThatLoveYou, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	goto_if_ge VAR_RESULT, FRIENDSHIP_150_TO_199, SlateportCity_PokemonFanClub_EventScript_GiveSootheBell
	release
	end

SlateportCity_PokemonFanClub_EventScript_GiveSootheBell::
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox SlateportCity_PokemonFanClub_Text_PokemonAdoresYou, MSGBOX_DEFAULT
	giveitem ITEM_SOOTHE_BELL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_SOOTHE_BELL
	release
	end

SlateportCity_PokemonFanClub_EventScript_ReceivedSootheBell::
	msgbox SlateportCity_PokemonFanClub_Text_TreatPokemonWithLove, MSGBOX_DEFAULT
	release
	end

SlateportCity_PokemonFanClub_EventScript_Man::
	msgbox SlateportCity_PokemonFanClub_Text_PokemonDontLikeFainting, MSGBOX_NPC
	end

SlateportCity_PokemonFanClub_EventScript_Twin::
	msgbox SlateportCity_PokemonFanClub_Text_MonEnjoyedProtein, MSGBOX_NPC
	end

SlateportCity_PokemonFanClub_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox SlateportCity_PokemonFanClub_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SlateportCity_PokemonFanClub_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox SlateportCity_PokemonFanClub_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SlateportCity_PokemonFanClub_EventScript_Azumarill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZUMARILL, CRY_MODE_NORMAL
	msgbox SlateportCity_PokemonFanClub_Text_Azumarill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SlateportCity_PokemonFanClub_Text_MeetChairman:
	.string "Ehem! Aku adalah KETUA\n"
	.string "POKéMON FAN CLUB!\p"
	.string "Sebagai KETUA, aku tentu saja\n"
	.string "yang paling penting!\p"
	.string "Tidak ada yang bisa mengalahkanku\n"
	.string "dalam hal melatih POKéMON. Tidak ada!\p"
	.string "Baiklah, izinkan aku memberitahumu tentang\n"
	.string "POKéMON CONTEST.\p"
	.string "Itu adalah acara di mana seseorang dapat\n"
	.string "memamerkan POKéMON untuk dilihat dunia!\p"
	.string "Namun, mereka diadakan di kota-kota yang\n"
	.string "jauh, jadi aku tidak bisa sering berpartisipasi.\p"
	.string "Itulah mengapa kami berkumpul di sini\n"
	.string "untuk memamerkan POKéMON kami, dan\l"
	.string "meminta orang lain menunjukkan milik mereka.$"

SlateportCity_PokemonFanClub_Text_LikeToSeeEnteredContestPokemon:
	.string "POKéMON milik TRAINER yang sudah\n"
	.string "mengikuti POKéMON CONTEST…\l"
	.string "Itu, aku ingin melihatnya.$"

SlateportCity_PokemonFanClub_Text_AllowMeToExamineYourPokemon:
	.string "Ehem! Aku lihat kamu sudah berpartisipasi\n"
	.string "dalam POKéMON CONTEST!\p"
	.string "Tolong! Izinkan aku memeriksa bagaimana\n"
	.string "kamu melatih POKéMON-mu.\p"
	.string "Aku sangat senang melihat POKéMON\n"
	.string "yang dilatih oleh TRAINER lain.\p"
	.string "Ekspresi bahagia POKéMON\n"
	.string "yang dilatih dengan benar…\p"
	.string "Mata ramah TRAINER yang\n"
	.string "merawat dan melatih POKéMON…\p"
	.string "Pikiran itu saja sudah memenuhi\n"
	.string "hatiku dengan sukacita yang meluap-luap.\p"
	.string "Oh! Aku mohon maaf!\n"
	.string "Maafkan aku karena banyak bicara!\p"
	.string "Tolong! Izinkan aku memeriksa seberapa\n"
	.string "banyak POKéMON-mu tumbuh!$"

SlateportCity_PokemonFanClub_Text_HowIsYourPokemonGrowing:
	.string "Bagaimana POKéMON-mu tumbuh?\n"
	.string "Izinkan aku memeriksanya.$"

SlateportCity_PokemonFanClub_Text_HmHmISee:
	.string "Hm, hm…\n"
	.string "Aku mengerti…$"

SlateportCity_PokemonFanClub_Text_GiveMonMorePokeblocks:
	.string "Hmmm… Tidak buruk, tapi juga tidak\n"
	.string "bagus…\p"
	.string "Kamu, TRAINER, harus lebih\n"
	.string "berusaha dalam melatih POKéMON ini!\p"
	.string "Sebagai contoh, bolehkah aku menyarankan\n"
	.string "agar kamu memberinya lebih banyak {POKEBLOCK}S?$"

SlateportCity_PokemonFanClub_Text_NoSpaceForReward:
	.string "Oh, astaga…\p"
	.string "POKéMON-mu tumbuh dengan sangat baik,\n"
	.string "jadi kamu pantas mendapatkan hadiah.\p"
	.string "Sayangnya, kamu tidak punya tempat\n"
	.string "untuk ini di TAS-mu.$"

SlateportCity_PokemonFanClub_Text_MonMostImpressiveGiveItThis:
	.string "{STR_VAR_1}-mu, ia tumbuh dengan\n"
	.string "cara yang sangat mengesankan!\l"
	.string "Ia adalah spesimen yang bagus!\p"
	.string "Tapi! Jika kamu memberinya ini,\n"
	.string "ia akan tumbuh lebih baik lagi! Sungguh!$"

SlateportCity_PokemonFanClub_Text_ExplainRedScarf:
	.string "Biarkan POKéMON memegang RED SCARF itu.\p"
	.string "Semua orang akan mengenali\n"
	.string "ketenangan POKéMON itu!$"

SlateportCity_PokemonFanClub_Text_ExplainBlueScarf:
	.string "Biarkan POKéMON memegang BLUE SCARF itu.\p"
	.string "Keindahannya akan lebih menonjol\n"
	.string "daripada sekarang!$"

SlateportCity_PokemonFanClub_Text_ExplainPinkScarf:
	.string "Biarkan POKéMON memegang PINK SCARF itu.\p"
	.string "Itu akan menonjolkan kelucuan\n"
	.string "POKéMON itu lebih lagi!$"

SlateportCity_PokemonFanClub_Text_ExplainGreenScarf:
	.string "Biarkan POKéMON memegang GREEN SCARF itu.\p"
	.string "Itu akan meningkatkan\n"
	.string "kepintaran POKéMON!$"

SlateportCity_PokemonFanClub_Text_ExplainYellowScarf:
	.string "Biarkan POKéMON memegang YELLOW SCARF itu.\p"
	.string "Itu akan sangat meningkatkan\n"
	.string "ketangguhan POKéMON-mu!$"

SlateportCity_PokemonFanClub_Text_NothingElseToGiveYou:
	.string "Maaf, tapi aku tidak punya apa-apa lagi\n"
	.string "untuk diberikan padamu! Sama sekali tidak!\p"
	.string "Bagaimanapun, kamu diberkati dengan bakat\n"
	.string "melatih POKéMON tanpa menggunakan\l"
	.string "item apa pun!$"

SlateportCity_PokemonFanClub_Text_ShowMePokemonThatLoveYou:
	.string "Aku senang melihat POKéMON yang mencintai\n"
	.string "TRAINER mereka.\p"
	.string "POKéMON sangat sensitif terhadap\n"
	.string "perasaan TRAINER mereka.\p"
	.string "Jika kamu memperlakukan POKéMON-mu\n"
	.string "dengan cinta dan perhatian, mereka akan membalasnya.\p"
	.string "Ketika POKéMON-mu mulai mencintaimu,\n"
	.string "tolong datang dan tunjukkan padaku.$"

SlateportCity_PokemonFanClub_Text_PokemonAdoresYou:
	.string "POKéMON-mu sangat memujamu.\p"
	.string "Untukmu, seorang TRAINER yang\n"
	.string "paling berbelas kasih, hadiah dari FAN CLUB!$"

SlateportCity_PokemonFanClub_Text_TreatPokemonWithLove:
	.string "POKéMON sangat sensitif terhadap\n"
	.string "perasaan TRAINER mereka.\p"
	.string "Jika kamu memperlakukan POKéMON-mu\n"
	.string "dengan cinta dan perhatian, mereka akan membalasnya.$"

SlateportCity_PokemonFanClub_Text_PokemonDontLikeFainting:
	.string "Jika kamu terus membiarkan POKéMON\n"
	.string "pingsan dalam pertarungan, ia akan membencinya.\p"
	.string "Segera, ia akan menjadi kurang percaya\n"
	.string "pada TRAINER.\p"
	.string "Dengan kata lain, ia pasti tidak akan\n"
	.string "terlalu menyukaimu.$"

SlateportCity_PokemonFanClub_Text_MonEnjoyedProtein:
	.string "Apakah POKéMON senang jika item\n"
	.string "digunakan padanya?\p"
	.string "Milikku terlihat sangat senang saat\n"
	.string "aku memberinya PROTEIN.$"

SlateportCity_PokemonFanClub_Text_Skitty:
	.string "SKITTY: Fffnyaaaah…$"

SlateportCity_PokemonFanClub_Text_Zigzagoon:
	.string "ZIGZAGOON: Kyuuu…$"

SlateportCity_PokemonFanClub_Text_Azumarill:
	.string "AZUMARILL: Marimari?$"

