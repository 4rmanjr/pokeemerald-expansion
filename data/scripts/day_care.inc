Route117_EventScript_DaycareMan::
	lock
	faceplayer
	special GetDaycareMonNicknames
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_EGG_WAITING, Route117_EventScript_DaycareEggWaiting
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route117_EventScript_CheckOnOneMon
	goto_if_eq VAR_RESULT, DAYCARE_TWO_MONS, Route117_EventScript_CheckOnTwoMons
	msgbox Route117_Text_SeeWifeIfYoudLikeMeToRaiseMon, MSGBOX_DEFAULT
	release
	end

Route117_EventScript_DaycareEggWaiting::
	msgbox Route117_Text_DoYouWantEgg, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route117_EventScript_DaycareAcceptEgg
	msgbox Route117_Text_IWillKeepDoYouWantIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route117_EventScript_DaycareAcceptEgg
	msgbox Route117_Text_IllKeepIt, MSGBOX_DEFAULT
	clearflag FLAG_PENDING_DAYCARE_EGG
	special RejectEggFromDayCare
	release
	end

Route117_EventScript_DaycareAcceptEgg::
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_ne VAR_RESULT, PARTY_SIZE, Route117_EventScript_DaycareReceiveEgg
	msgbox Route117_Text_YouHaveNoRoomForIt, MSGBOX_DEFAULT
	release
	end

Route117_EventScript_DaycareReceiveEgg::
	message Route117_Text_ReceivedEgg
	playfanfare MUS_LEVEL_UP
	waitfanfare
	waitbuttonpress
	msgbox Route117_Text_TakeGoodCareOfIt, MSGBOX_DEFAULT
	special GiveEggFromDaycare
	clearflag FLAG_PENDING_DAYCARE_EGG
	release
	end

Route117_EventScript_CheckMonReceivedMail::
	specialvar VAR_RESULT, CheckDaycareMonReceivedMail
	call_if_eq VAR_RESULT, 1, Route117_EventScript_MonReceivedMail
	return

Route117_EventScript_MonReceivedMail::
	msgbox Route117_Text_FriendlyWithOtherTrainersMon, MSGBOX_DEFAULT
	return

Route117_EventScript_CheckOnOneMon::
	special GetDaycareMonNicknames
	msgbox Route117_Text_YourMonIsDoingFine, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route117_EventScript_CheckMonReceivedMail
	release
	end

Route117_EventScript_CheckOnTwoMons::
	special GetDaycareMonNicknames
	msgbox Route117_Text_YourMonsAreDoingFine, MSGBOX_DEFAULT
	special SetDaycareCompatibilityString
	special ShowFieldMessageStringVar4
	waitmessage
	waitbuttonpress
	setvar VAR_0x8004, 0
	call Route117_EventScript_CheckMonReceivedMail
	setvar VAR_0x8004, 1
	call Route117_EventScript_CheckMonReceivedMail
	release
	end

Route117_PokemonDayCare_EventScript_DaycareWoman::
	lock
	faceplayer
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_EGG_WAITING, Route117_PokemonDayCare_EventScript_EggWaiting
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route117_PokemonDayCare_EventScript_OneMonInDaycare
	goto_if_eq VAR_RESULT, DAYCARE_TWO_MONS, Route117_PokemonDayCare_EventScript_TwoMonsInDaycare
	msgbox Route117_PokemonDayCare_Text_WouldYouLikeUsToRaiseAMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route117_PokemonDayCare_EventScript_GiveMonToRaise
	msgbox Route117_PokemonDayCare_Text_FineThenComeAgain, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_GiveMonToRaise::
	specialvar VAR_RESULT, CountPartyNonEggMons
	goto_if_eq VAR_RESULT, 1, Route117_PokemonDayCare_EventScript_OnlyOneMon
	specialvar VAR_RESULT, CountPartyAliveNonEggMons
	goto_if_eq VAR_RESULT, 2, Route117_PokemonDayCare_EventScript_OnlyTwoAliveMons
	msgbox Route117_PokemonDayCare_Text_WhichMonShouldWeRaise, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special ChooseSendDaycareMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route117_PokemonDayCare_EventScript_ComeAgain
	specialvar VAR_RESULT, CountPartyAliveNonEggMons_IgnoreVar0x8004Slot
	goto_if_eq VAR_RESULT, 0, Route117_PokemonDayCare_EventScript_OnlyOneAliveMon
	specialvar VAR_0x8005, GetSelectedMonNicknameAndSpecies
	waitse
	playmoncry VAR_0x8005, CRY_MODE_NORMAL
	msgbox Route117_PokemonDayCare_Text_WellRaiseYourMon, MSGBOX_DEFAULT
	waitmoncry
	special StoreSelectedPokemonInDaycare
	callnative UpdateFollowingPokemon
	incrementgamestat GAME_STAT_USED_DAYCARE
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route117_PokemonDayCare_EventScript_CanRaiseOneMore
	release
	end

Route117_PokemonDayCare_EventScript_ComeAgain::
	msgbox Route117_PokemonDayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_CanRaiseOneMore::
	msgbox Route117_PokemonDayCare_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route117_PokemonDayCare_EventScript_GiveMonToRaise
	goto Route117_PokemonDayCare_EventScript_ComeAgain
	end

Route117_PokemonDayCare_EventScript_OnlyOneMon::
	msgbox Route117_PokemonDayCare_Text_YouHaveJustOneMon, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_OnlyOneAliveMon::
	msgbox Route117_PokemonDayCare_Text_WhatWillYouBattleWith, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_OnlyTwoAliveMons::
	msgbox Route117_PokemonDayCare_Text_YoullBeLeftWithJustOne, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_EggWaiting::
	msgbox Route117_PokemonDayCare_Text_HusbandWasLookingForYou, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_YourMonHasGrownXLevels::
	msgbox Route117_PokemonDayCare_Text_YourMonHasGrownXLevels, MSGBOX_DEFAULT
	return

Route117_PokemonDayCare_EventScript_DisplayLevelsGained::
	specialvar VAR_RESULT, GetNumLevelsGainedFromDaycare
	call_if_ne VAR_RESULT, 0, Route117_PokemonDayCare_EventScript_YourMonHasGrownXLevels
	return

Route117_PokemonDayCare_EventScript_OneMonInDaycare::
	msgbox Route117_PokemonDayCare_Text_GoodToSeeYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route117_PokemonDayCare_EventScript_DisplayLevelsGained
	msgbox Route117_PokemonDayCare_Text_WeCanRaiseOneMore, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route117_PokemonDayCare_EventScript_GiveMonToRaise
	msgbox Route117_PokemonDayCare_Text_TakeYourMonBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route117_PokemonDayCare_EventScript_TryRetrieveMon
	goto Route117_PokemonDayCare_EventScript_ComeAgain
	end

Route117_PokemonDayCare_EventScript_TryRetrieveMon::
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_eq VAR_RESULT, PARTY_SIZE, Route117_PokemonDayCare_EventScript_NoRoom
	specialvar VAR_RESULT, GetDaycareState
	setvar VAR_0x8004, 0
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route117_PokemonDayCare_EventScript_CostPrompt
	special ShowDaycareLevelMenu
	waitstate
	copyvar VAR_0x8004, VAR_RESULT
	goto_if_eq VAR_RESULT, DAYCARE_EXITED_LEVEL_MENU, Route117_PokemonDayCare_EventScript_ComeAgain
	goto Route117_PokemonDayCare_EventScript_CostPrompt
	end

Route117_PokemonDayCare_EventScript_CostPrompt::
	special GetDaycareCost
	msgbox Route117_PokemonDayCare_Text_ItWillCostX, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route117_PokemonDayCare_EventScript_CheckEnoughMoney
	goto Route117_PokemonDayCare_EventScript_ComeAgain
	end

Route117_PokemonDayCare_EventScript_CheckEnoughMoney::
	specialvar VAR_RESULT, IsEnoughForCostInVar0x8005
	goto_if_eq VAR_RESULT, 1, Route117_PokemonDayCare_EventScript_RetrieveMon
	msgbox Route117_PokemonDayCare_Text_NotEnoughMoney, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_EventScript_RetrieveMon::
	applymovement LOCALID_DAYCARE_LADY, Route117_PokemonDayCare_Movement_RetrieveDaycareMon
	waitmovement 0
	specialvar VAR_RESULT, TakePokemonFromDaycare
	special SubtractMoneyFromVar0x8005
	playse SE_SHOP
	msgbox Route117_PokemonDayCare_Text_HeresYourMon, MSGBOX_DEFAULT
	waitse
	playmoncry VAR_RESULT, CRY_MODE_NORMAL
	msgbox Route117_PokemonDayCare_Text_TookBackMon, MSGBOX_DEFAULT
	waitmoncry
	specialvar VAR_RESULT, GetDaycareState
	goto_if_eq VAR_RESULT, DAYCARE_ONE_MON, Route117_PokemonDayCare_EventScript_AskRetrieveOtherMon
	goto Route117_PokemonDayCare_EventScript_ComeAgain
	end

Route117_PokemonDayCare_EventScript_AskRetrieveOtherMon::
	msgbox Route117_PokemonDayCare_Text_TakeOtherOneBackToo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route117_PokemonDayCare_EventScript_TryRetrieveMon
	goto Route117_PokemonDayCare_EventScript_ComeAgain
	end

Route117_PokemonDayCare_EventScript_NoRoom::
	msgbox Route117_PokemonDayCare_Text_YourTeamIsFull, MSGBOX_DEFAULT
	release
	end

Route117_PokemonDayCare_Movement_RetrieveDaycareMon:
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	face_right
	delay_16
	delay_16
	face_up
	walk_slow_up
	set_invisible
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	face_down
	set_visible
	walk_slow_down
	step_end

@ Unused. Possibly a commented script, or a typo end added to the above Movement script
Route117_PokemonDayCare_EventScript_UnusedEnd::
	end

Route117_PokemonDayCare_EventScript_TwoMonsInDaycare::
	msgbox Route117_PokemonDayCare_Text_GoodToSeeYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0
	call Route117_PokemonDayCare_EventScript_DisplayLevelsGained
	setvar VAR_0x8004, 1
	call Route117_PokemonDayCare_EventScript_DisplayLevelsGained
	msgbox Route117_PokemonDayCare_Text_TakeYourMonBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route117_PokemonDayCare_EventScript_TryRetrieveMon
	msgbox Route117_PokemonDayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

@ Unused
Route117_PokemonDayCare_EventScript_UnusedRetrieveMon::
	special ShowDaycareLevelMenu
	waitstate
	goto_if_eq VAR_RESULT, 2, Route117_PokemonDayCare_EventScript_ComeAgain
	copyvar VAR_0x8004, VAR_RESULT
	specialvar VAR_RESULT, TakePokemonFromDaycare
	msgbox Route117_PokemonDayCare_Text_HeresYourMon, MSGBOX_DEFAULT
	msgbox Route117_PokemonDayCare_Text_ComeAgain, MSGBOX_DEFAULT
	release
	end

EventScript_EggHatch::
	lockall
	msgbox Text_EggHatchHuh, MSGBOX_DEFAULT
	special EggHatch
	waitstate
	releaseall
	end

Route117_Text_SeeWifeIfYoudLikeMeToRaiseMon:
	.string "Aku adalah DAY-CARE MAN.\p"
	.string "Aku membantu merawat POKéMON\n"
	.string "berharga para TRAINER.\p"
	.string "Jika kamu ingin aku membesarkan POKéMON-mu,\n"
	.string "bicaralah dengan istriku.$"

Route117_Text_DoYouWantEgg:
	.string "Ah, kamu!\p"
	.string "Kami sedang membesarkan POKéMON-mu,\n"
	.string "dan astaga, kami terkejut!\p"
	.string "POKéMON-mu punya EGG!\p"
	.string "Kami tidak tahu bagaimana itu bisa ada di sana,\n"
	.string "tapi POKéMON-mu memilikinya.\p"
	.string "Kamu menginginkannya, bukan?$"

Route117_Text_YourMonIsDoingFine:
	.string "Ah, kamu! Senang melihatmu.\n"
	.string "{STR_VAR_1}-mu baik-baik saja.$"

Route117_Text_IllKeepIt:
	.string "Baiklah, aku akan menyimpannya.\n"
	.string "Terima kasih!$"

Route117_Text_YouHaveNoRoomForIt:
	.string "Kamu tidak punya tempat untuk itu…\n"
	.string "Kembalilah setelah kamu punya tempat.$"

Route117_Text_ReceivedEgg:
	.string "{PLAYER} menerima EGG dari\n"
	.string "DAY-CARE MAN.$"

Route117_Text_TakeGoodCareOfIt:
	.string "Rawatlah baik-baik.$"

Route117_Text_FriendlyWithOtherTrainersMon:
	.string "Ngomong-ngomong, tentang {STR_VAR_1}-mu,\n"
	.string "itu tampak akrab dengan {STR_VAR_2}'s {STR_VAR_3}.\p"
	.string "Aku bahkan mungkin melihatnya menerima\n"
	.string "selembar MAIL.$"

@ Unused
Route117_Text_SeeWifeIfYouWantToPickUpMon:
	.string "Jika kamu ingin mengambil POKéMON-mu,\n"
	.string "bicaralah dengan istriku.$"

Route117_Text_YourMonsAreDoingFine:
	.string "Ah, kamu! {STR_VAR_1} dan\n"
	.string "{STR_VAR_2}-mu baik-baik saja.$"

Route117_Text_IWillKeepDoYouWantIt:
	.string "Aku benar-benar akan menyimpannya.\n"
	.string "Kamu menginginkannya, bukan?$"

Route117_PokemonDayCare_Text_WouldYouLikeUsToRaiseAMon:
	.string "Aku adalah DAY-CARE LADY.\p"
	.string "Kami bisa membesarkan POKéMON untukmu.\p"
	.string "Apakah kamu ingin kami membesarkan satu?$"

Route117_PokemonDayCare_Text_WhichMonShouldWeRaise:
	.string "POKéMON mana yang harus kami besarkan untuk\n"
	.string "kamu?$"

Route117_PokemonDayCare_Text_WellRaiseYourMon:
	.string "Baiklah, kami akan membesarkan {STR_VAR_1}-mu\n"
	.string "untuk sementara.\p"
	.string "Kembalilah nanti untuk mengambilnya.$"

Route117_PokemonDayCare_Text_WeCanRaiseOneMore:
	.string "Kami bisa membesarkan dua POKéMON-mu.\n"
	.string "Apakah kamu ingin kami membesarkan satu lagi?$"

Route117_PokemonDayCare_Text_HusbandWasLookingForYou:
	.string "Suamiku mencarimu.$"

Route117_PokemonDayCare_Text_FineThenComeAgain:
	.string "Oh, baiklah.\n"
	.string "Kembalilah lagi.$"

Route117_PokemonDayCare_Text_NotEnoughMoney:
	.string "Uangmu tidak cukup…$"

Route117_PokemonDayCare_Text_TakeOtherOneBackToo:
	.string "Apakah kamu akan mengambil yang lain,\n"
	.string "juga?$"

Route117_PokemonDayCare_Text_ComeAgain:
	.string "Baik.\n"
	.string "Kembalilah lagi.$"

Route117_PokemonDayCare_Text_GoodToSeeYou:
	.string "Ah, kamu! Senang melihatmu.\n"
	.string "POKéMON-mu pasti baik-baik saja!$"

Route117_PokemonDayCare_Text_YourMonHasGrownXLevels:
	.string "Berdasarkan level, {STR_VAR_1}-mu telah\n"
	.string "bertambah {STR_VAR_2}.$"

Route117_PokemonDayCare_Text_YourTeamIsFull:
	.string "Tim POKéMON-mu penuh.\n"
	.string "Buatlah ruang, lalu datanglah menemuiku.$"

@ Unused
Route117_PokemonDayCare_Text_TakeBackWhichMon:
	.string "POKéMON mana yang akan kamu ambil kembali?$"

Route117_PokemonDayCare_Text_ItWillCostX:
	.string "Jika kamu ingin {STR_VAR_1}-mu kembali,\n"
	.string "itu akan berharga ¥{STR_VAR_2}.$"

Route117_PokemonDayCare_Text_HeresYourMon:
	.string "Sempurna!\n"
	.string "Ini POKéMON-mu.$"

Route117_PokemonDayCare_Text_TookBackMon:
	.string "{PLAYER} mengambil kembali {STR_VAR_1} dari\n"
	.string "DAY-CARE LADY.$"

Route117_PokemonDayCare_Text_YouHaveJustOneMon:
	.string "Oh? Tapi kamu hanya punya satu\n"
	.string "POKéMON.\p"
	.string "Kembalilah lain kali.$"

Route117_PokemonDayCare_Text_TakeYourMonBack:
	.string "Apakah kamu akan mengambil POKéMON-mu kembali?$"

Route117_PokemonDayCare_Text_WhatWillYouBattleWith:
	.string "Jika kamu meninggalkanku POKéMON itu,\n"
	.string "dengan apa kamu akan bertarung?\p"
	.string "Kembalilah lain kali.$"

Text_EggHatchHuh:
	.string "Hah?$"

Route117_PokemonDayCare_Text_YoullBeLeftWithJustOne:
	.string "Hah?\n"
	.string "Sekarang, sekarang.\p"
	.string "Jika kamu meninggalkan POKéMON itu\n"
	.string "padaku, kamu hanya akan punya satu.\p"
	.string "Kamu akan lebih baik jika kamu menangkap\n"
	.string "lebih banyak, aku berani bilang.$"
