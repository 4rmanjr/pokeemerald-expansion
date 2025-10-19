SlateportCity_NameRatersHouse_MapScripts::
	.byte 0

SlateportCity_NameRatersHouse_EventScript_NameRater::
	lock
	faceplayer
	msgbox SlateportCity_NameRatersHouse_Text_PleasedToRateMonNickname, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_NameRatersHouse_EventScript_ChooseMonToRate
	goto_if_eq VAR_RESULT, NO, SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_ChooseMonToRate::
	msgbox SlateportCity_NameRatersHouse_Text_CritiqueWhichMonNickname, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_ne VAR_0x8004, PARTY_NOTHING_CHOSEN, SlateportCity_NameRatersHouse_EventScript_RateMonNickname
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_DeclineNameRate::
	msgbox SlateportCity_NameRatersHouse_Text_DoVisitAgain, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_RateMonNickname::
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, SlateportCity_NameRatersHouse_EventScript_CantRateEgg
	special BufferMonNickname
	special IsMonOTIDNotPlayers
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	specialvar VAR_RESULT, MonOTNameNotPlayer
	special BufferMonNickname
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT
	msgbox SlateportCity_NameRatersHouse_Text_FineNameSuggestBetterOne, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_NameRatersHouse_EventScript_ChangeNickname
	goto_if_eq VAR_RESULT, NO, SlateportCity_NameRatersHouse_EventScript_DeclineNameRate
	end

SlateportCity_NameRatersHouse_EventScript_CantRateEgg::
	msgbox SlateportCity_NameRatersHouse_Text_ThatIsMerelyAnEgg, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_PlayerNotMonsOT::
	msgbox SlateportCity_NameRatersHouse_Text_MagnificentName, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_ChangeNickname::
	msgbox SlateportCity_NameRatersHouse_Text_WhatShallNewNameBe, MSGBOX_DEFAULT
	call Common_EventScript_NameReceivedPartyMon
	specialvar VAR_RESULT, TryPutNameRaterShowOnTheAir
	special BufferMonNickname
	goto_if_eq VAR_RESULT, TRUE, SlateportCity_NameRatersHouse_EventScript_NewNameDifferent
	msgbox SlateportCity_NameRatersHouse_Text_NameNoDifferentYetSuperior, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_EventScript_NewNameDifferent::
	msgbox SlateportCity_NameRatersHouse_Text_MonShallBeKnownAsName, MSGBOX_DEFAULT
	release
	end

SlateportCity_NameRatersHouse_Text_PleasedToRateMonNickname:
	.string "Hai, hai! Aku NAME RATER!\n"
	.string "Aku peramal nama!\p"
	.string "Aku akan dengan senang hati menilai\n"
	.string "nama panggilan POKéMON-mu.$"

SlateportCity_NameRatersHouse_Text_CritiqueWhichMonNickname:
	.string "Nama panggilan POKéMON mana yang\n"
	.string "harus aku kritik?$"

SlateportCity_NameRatersHouse_Text_FineNameSuggestBetterOne:
	.string "Hmmm… {STR_VAR_1}, ya? Itu\n"
	.string "nama yang cukup bagus yang kamu berikan.\p"
	.string "Tapi! Bagaimana jika aku\n"
	.string "menyarankan nama yang sedikit lebih baik?$"

SlateportCity_NameRatersHouse_Text_WhatShallNewNameBe:
	.string "Ah, bagus. Lalu, apa nama\n"
	.string "panggilan barunya?$"

SlateportCity_NameRatersHouse_Text_MonShallBeKnownAsName:
	.string "Selesai! Mulai sekarang, POKéMON ini\n"
	.string "akan dikenal sebagai {STR_VAR_1}!\p"
	.string "Ini nama yang lebih baik dari sebelumnya!\n"
	.string "Betapa beruntungnya kamu!$"

SlateportCity_NameRatersHouse_Text_DoVisitAgain:
	.string "Aku mengerti.\n"
	.string "Datanglah berkunjung lagi.$"

SlateportCity_NameRatersHouse_Text_NameNoDifferentYetSuperior:
	.string "Selesai! Mulai sekarang, POKéMON ini\n"
	.string "akan dikenal sebagai {STR_VAR_1}!\p"
	.string "Tidak ada bedanya dengan sebelumnya,\n"
	.string "namun, ini jauh lebih unggul!\p"
	.string "Betapa beruntungnya kamu!$"

SlateportCity_NameRatersHouse_Text_MagnificentName:
	.string "Hmmm… {STR_VAR_1}!\p"
	.string "Ini nama panggilan yang luar biasa!\n"
	.string "Benar-benar tanpa cela!\p"
	.string "Kamu akan baik-baik saja untuk menghargai\n"
	.string "{STR_VAR_1}-mu sekarang dan selamanya.$"

SlateportCity_NameRatersHouse_Text_ThatIsMerelyAnEgg:
	.string "Sekarang, sekarang.\n"
	.string "Itu hanyalah EGG!$"

