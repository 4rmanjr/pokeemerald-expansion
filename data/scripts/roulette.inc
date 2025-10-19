Roulette_EventScript_Table1::
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 0
	getpokenewsactive POKENEWS_GAME_CORNER
	goto_if_eq VAR_RESULT, FALSE, Roulette_EventScript_Play
	addvar VAR_0x8004, ROULETTE_SPECIAL_RATE
	goto Roulette_EventScript_Play
	end

Roulette_EventScript_Table2::
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 1
	getpokenewsactive POKENEWS_GAME_CORNER
	goto_if_eq VAR_RESULT, FALSE, Roulette_EventScript_Play
	addvar VAR_0x8004, ROULETTE_SPECIAL_RATE
	goto Roulette_EventScript_Play
	end

Roulette_EventScript_Play::
	special PlayRoulette
	waitstate
	end

Roulette_Text_PlayMinimumWagerIsX::
	.string "Taruhan minimum di meja ini\n"
	.string "adalah {STR_VAR_1}. Apakah kamu ingin bermain?$"

Roulette_Text_NotEnoughCoins::
	.string "Kamu tidak punya cukup COINS.$"

Roulette_Text_SpecialRateTable::
	.string "Meja tarif khusus sekarang!$"

Roulette_Text_ControlsInstruction::
	.string "Tempatkan taruhanmu dengan + Control\n"
	.string "Pad, lalu tekan Tombol A.$"

Roulette_Text_ItsAHit::
	.string "Kena!$"

Roulette_Text_Jackpot::
	.string "Jackpot!$"

Roulette_Text_NothingDoing::
	.string "Tidak ada yang terjadi!$"

Roulette_Text_YouveWonXCoins::
	.string "Kamu memenangkan {STR_VAR_1} COINS!$"

Roulette_Text_NoCoinsLeft::
	.string "Tidak ada COINS tersisa…$"

Roulette_Text_KeepPlaying::
	.string "Terus bermain?$"

Roulette_Text_BoardWillBeCleared::
	.string "Papan ROULETTE akan dihapus.$"

@ Unused
Roulette_Text_YouDontHaveACoinCase::
	.string "Kamu tidak punya COIN CASE.$"

Roulette_Text_CoinCaseIsFull::
	.string "COIN CASE-mu penuh!\n"
	.string "COINS bisa ditukar dengan hadiah.$"
