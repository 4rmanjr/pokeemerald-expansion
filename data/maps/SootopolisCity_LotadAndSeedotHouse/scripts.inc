SootopolisCity_LotadAndSeedotHouse_MapScripts::
	.byte 0

SootopolisCity_LotadAndSeedotHouse_EventScript_SeedotBrother::
	special GetSeedotSizeRecordInfo
	lock
	faceplayer
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigSeedot, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	copyvar VAR_RESULT, VAR_0x8004
	goto_if_eq VAR_RESULT, PARTY_NOTHING_CHOSEN, SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowSeedot
	special CompareSeedotSize
	goto_if_eq VAR_RESULT, 1, SootopolisCity_LotadAndSeedotHouse_EventScript_NotSeedot
	goto_if_eq VAR_RESULT, 2, SootopolisCity_LotadAndSeedotHouse_EventScript_SmallSeedot
	goto_if_eq VAR_RESULT, 3, SootopolisCity_LotadAndSeedotHouse_EventScript_BigSeedot
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowSeedot::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigSeedot, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NotSeedot::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotSeedot, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_SmallSeedot::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerSeedot, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_BigSeedot::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_GoshMightBeBiggerThanLotad, MSGBOX_DEFAULT
	giveitem ITEM_ELIXIR
	goto_if_eq VAR_RESULT, FALSE, SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir1
	closemessage
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir1::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull1, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_LotadBrother::
	special GetLotadSizeRecordInfo
	lock
	faceplayer
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigLotad, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	copyvar VAR_RESULT, VAR_0x8004
	goto_if_eq VAR_RESULT, PARTY_NOTHING_CHOSEN, SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowLotad
	special CompareLotadSize
	goto_if_eq VAR_RESULT, 1, SootopolisCity_LotadAndSeedotHouse_EventScript_NotLotad
	goto_if_eq VAR_RESULT, 2, SootopolisCity_LotadAndSeedotHouse_EventScript_SmallLotad
	goto_if_eq VAR_RESULT, 3, SootopolisCity_LotadAndSeedotHouse_EventScript_BigLotad
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_CancelShowLotad::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigLotad, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NotLotad::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotLotad, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_SmallLotad::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerLotad, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_BigLotad::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_WowMightBeBiggerThanSeedot, MSGBOX_DEFAULT
	giveitem ITEM_ELIXIR
	goto_if_eq VAR_RESULT, FALSE, SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir2
	closemessage
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_NoRoomForElixir2::
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull2, MSGBOX_DEFAULT
	release
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_SeedotSizeRecord::
	special GetSeedotSizeRecordInfo
	lockall
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BiggestSeedotInHistory, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_LotadAndSeedotHouse_EventScript_LotadSizeRecord::
	special GetLotadSizeRecordInfo
	lockall
	msgbox SootopolisCity_LotadAndSeedotHouse_Text_BiggestLotadInHistory, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigSeedot:
	.string "Apakah kamu tahu POKéMON SEEDOT?\n"
	.string "Jarang sekali terlihat di SOOTOPOLIS.\p"
	.string "Pokoknya, aku suka SEEDOT besar.\n"
	.string "Makin besar makin bagus.\p"
	.string "Tapi adikku, dia bilang LOTAD\n"
	.string "lebih besar.\p"
	.string "Itu konyol.\n"
	.string "SEEDOT harus lebih besar dari itu!\p"
	.string "Hah? Kamu punya SEEDOT?\n"
	.string "T-t-tolong, tunjukkan padaku!$"

SootopolisCity_LotadAndSeedotHouse_Text_GoshMightBeBiggerThanLotad:
	.string "{STR_VAR_2}!\n"
	.string "Ya ampun, ini besar sekali!\p"
	.string "Bahkan mungkin mengalahkan LOTAD besar\n"
	.string "yang dilihat adikku!\p"
	.string "Terima kasih sudah menunjukkannya.\n"
	.string "Ini hadiah dariku!$"

@ Unused
SootopolisCity_LotadAndSeedotHouse_Text_ReceivedPotion1:
	.string "{PLAYER} mendapatkan POTION.$"

SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull1:
	.string "Hah?\n"
	.string "TASmu penuh sesak.$"

SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerSeedot:
	.string "{STR_VAR_2}, benarkah?\p"
	.string "Hmm… Aku pernah melihat SEEDOT yang\n"
	.string "lebih besar dari ini.$"

SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotSeedot:
	.string "Oh, ini cukup menarik…\n"
	.string "Tapi ini bukan SEEDOT!$"

SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigSeedot:
	.string "Kamu tidak punya SEEDOT besar?\n"
	.string "Sayang sekali…\p"
	.string "Jika kamu mendapatkan SEEDOT besar,\n"
	.string "tolong tunjukkan padaku.$"

SootopolisCity_LotadAndSeedotHouse_Text_BiggestSeedotInHistory:
	.string "SEEDOT terbesar dalam sejarah!\n"
	.string "Raksasa {STR_VAR_2}'s {STR_VAR_3}!\p"
	.string "SEEDOT yang lebih besar dari LOTAD\n"
	.string "selalu kuinginkan!$"

SootopolisCity_LotadAndSeedotHouse_Text_PleaseShowMeBigLotad:
	.string "Apakah kamu tahu POKéMON LOTAD?\n"
	.string "Jarang terlihat di SOOTOPOLIS.\p"
	.string "Aku suka, maksudku sangat suka, LOTAD\n"
	.string "besar!\p"
	.string "Kakakku bilang SEEDOT\n"
	.string "lebih besar.\p"
	.string "Tapi itu salah! Semua orang tahu bahwa\n"
	.string "LOTAD jauh lebih besar.\p"
	.string "Hah? Kamu punya LOTAD?\n"
	.string "T-t-tolong tunjukkan padaku!$"

SootopolisCity_LotadAndSeedotHouse_Text_WowMightBeBiggerThanSeedot:
	.string "{STR_VAR_2}!\n"
	.string "Wow, itu besar sekali!\p"
	.string "Bahkan mungkin lebih besar dari SEEDOT\n"
	.string "besar yang kakakku lihat.\p"
	.string "Terima kasih sudah menunjukkannya!\n"
	.string "Ini hadiah dariku!$"

@ Unused
SootopolisCity_LotadAndSeedotHouse_Text_ReceivedPotion2:
	.string "{PLAYER} mendapatkan POTION.$"

SootopolisCity_LotadAndSeedotHouse_Text_BagCrammedFull2:
	.string "Hah?\n"
	.string "TASmu penuh sesak.$"

SootopolisCity_LotadAndSeedotHouse_Text_SeenBiggerLotad:
	.string "{STR_VAR_2}?\p"
	.string "Hmm… Aku pernah melihat LOTAD yang\n"
	.string "lebih besar dari yang ini.$"

SootopolisCity_LotadAndSeedotHouse_Text_ThatsNotLotad:
	.string "Wah, ini lumayan juga!\n"
	.string "Tapi ini bukan LOTAD!$"

SootopolisCity_LotadAndSeedotHouse_Text_DontHaveBigLotad:
	.string "Kamu tidak punya LOTAD besar?\n"
	.string "Sungguh mengecewakan…\p"
	.string "Jika kamu mendapatkan LOTAD besar,\n"
	.string "tolong tunjukkan padaku!$"

SootopolisCity_LotadAndSeedotHouse_Text_BiggestLotadInHistory:
	.string "LOTAD terbesar dalam sejarah!\n"
	.string "Raksasa {STR_VAR_2}'s {STR_VAR_3}!\p"
	.string "LOTAD yang lebih besar dari SEEDOT\n"
	.string "selalu kuinginkan!$"

