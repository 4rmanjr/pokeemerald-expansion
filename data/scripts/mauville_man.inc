MauvilleCity_PokemonCenter_1F_EventScript_MauvilleOldMan::
	special Script_GetCurrentMauvilleMan
	switch VAR_RESULT
	case MAUVILLE_MAN_BARD, MauvilleCity_PokemonCenter_1F_EventScript_Bard
	case MAUVILLE_MAN_HIPSTER, MauvilleCity_PokemonCenter_1F_EventScript_Hipster
	case MAUVILLE_MAN_TRADER, MauvilleCity_PokemonCenter_1F_EventScript_Trader
	case MAUVILLE_MAN_STORYTELLER, MauvilleCity_PokemonCenter_1F_EventScript_Storyteller
	case MAUVILLE_MAN_GIDDY, MauvilleCity_PokemonCenter_1F_EventScript_Giddy
	end

@ Bard
MauvilleCity_PokemonCenter_1F_EventScript_Bard::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToHearMySong, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_PlaySong
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineSong
	end

MauvilleCity_PokemonCenter_1F_EventScript_PlaySong::
	setvar VAR_0x8004, FALSE  @ Play his current song
	special PlayBardSong
	delay 60
	special HasBardSongBeenChanged
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_AskToWriteLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_WishICouldPlaySongForOthers, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineSong::
	msgbox MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues1, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_AskToWriteLyrics::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToWriteSomeLyrics, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics
	end

MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics::
	setvar VAR_0x8004, EASY_CHAT_TYPE_BARD_SONG
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_LetMeSingItForYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, TRUE  @ Play the new song
	special PlayBardSong
	delay 60
	msgbox MauvilleCity_PokemonCenter_1F_Text_ThatHowYouWantedSongToGo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics
	special SaveBardSongLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_IllSingThisSongForAWhile, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics::
	msgbox MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues2, MSGBOX_DEFAULT
	release
	end

@ Hipster
MauvilleCity_PokemonCenter_1F_EventScript_Hipster::
	lock
	faceplayer
	setflag FLAG_UNLOCKED_TRENDY_SAYINGS
	msgbox MauvilleCity_PokemonCenter_1F_Text_TeachWhatsHipAndHappening, MSGBOX_DEFAULT
	special HasHipsterTaughtWord
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_TryTeachWord
	msgbox MauvilleCity_PokemonCenter_1F_Text_IAlreadyTaughtYou, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTeachWord::
	special HipsterTryTeachWord
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_TeachWord
	msgbox MauvilleCity_PokemonCenter_1F_Text_IveGotNothingNewToTeach, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TeachWord::
	msgbox MauvilleCity_PokemonCenter_1F_Text_HaveYouHeardOfWord, MSGBOX_DEFAULT
	special SetHipsterTaughtWord
	release
	end

@ Trader
MauvilleCity_PokemonCenter_1F_Text_WantToTradeDecor:
	.string "Hai, aku TRADER.\n"
	.string "Mau bertukar dekorasi denganku?$"

MauvilleCity_PokemonCenter_1F_Text_TraderFeelingTheBlues:
	.string "Oh…\n"
	.string "Kamu membuatku merasa sedih…$"

MauvilleCity_PokemonCenter_1F_Text_WeveAlreadyTraded:
	.string "Tapi kita sudah bertukar dekorasi,\n"
	.string "kamu dan aku.$"

MauvilleCity_PokemonCenter_1F_Text_PickADecorItem:
	.string "Jika kamu melihat barang dekorasi apa pun\n"
	.string "yang kamu inginkan dariku, katakan saja.$"

MauvilleCity_PokemonCenter_1F_Text_YouDontWantAnything:
	.string "Kamu tidak menginginkan apa pun?\n"
	.string "Aku merasa tidak diinginkan…$"

MauvilleCity_PokemonCenter_1F_Text_OnceBelongedToPlayerDoYouWantIt:
	.string "Barang dekorasi itu pernah dimiliki\n"
	.string "oleh {STR_VAR_1}.\p"
	.string "Apakah kamu menginginkannya?$"

MauvilleCity_PokemonCenter_1F_Text_YouDontHaveAnyDecor:
	.string "Uh… Tunggu sebentar. Kamu tidak punya\n"
	.string "sepotong pun dekorasi!$"

MauvilleCity_PokemonCenter_1F_Text_PickTheDecorToTrade:
	.string "Oke, pilih dekorasi yang akan\n"
	.string "kamu tukarkan kepadaku.$"

MauvilleCity_PokemonCenter_1F_Text_YouDontWantToTrade:
	.string "Kamu tidak mau bertukar denganku?\n"
	.string "Aku merasa tidak diinginkan…$"

MauvilleCity_PokemonCenter_1F_Text_YouveNoRoomForThis:
	.string "Kamu sudah punya semua {STR_VAR_2} yang bisa\n"
	.string "disimpan. Kamu tidak punya ruang untuk ini.$"

MauvilleCity_PokemonCenter_1F_Text_SoWellTradeTheseDecor:
	.string "Oke, jadi kita akan menukar {STR_VAR_3} milikku\n"
	.string "dengan {STR_VAR_2} milikmu?$"

MauvilleCity_PokemonCenter_1F_Text_ThatDecorIsInUse:
	.string "Dekorasi itu sedang digunakan.\n"
	.string "Kamu tidak bisa menukarnya.$"

MauvilleCity_PokemonCenter_1F_Text_SendDecorToYourPC:
	.string "Kalau begitu kita akan bertukar!\n"
	.string "Aku akan mengirim dekorasiku ke PC-mu.$"

MauvilleCity_PokemonCenter_1F_Text_CantTradeThatOne:
	.string "Ups! Maaf! Itu adalah barang\n"
	.string "dekorasi yang sangat langka.\l"
	.string "Aku tidak bisa menukarnya!\p"
	.string "Bisakah aku menawarkanmu yang lain?$"

MauvilleCity_PokemonCenter_1F_EventScript_Trader::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_WantToTradeDecor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineTrade
	special GetTraderTradedFlag
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_AlreadyTraded
	message MauvilleCity_PokemonCenter_1F_Text_PickADecorItem
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineTrade::
	msgbox MauvilleCity_PokemonCenter_1F_Text_TraderFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_AlreadyTraded::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WeveAlreadyTraded, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive::
	special TraderMenuGetDecoration
	waitstate
	goto_if_eq VAR_0x8004, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelPickDecor
	goto_if_eq VAR_0x8004, 0xFFFF, MauvilleCity_PokemonCenter_1F_EventScript_InvalidDecor
	msgbox MauvilleCity_PokemonCenter_1F_Text_OnceBelongedToPlayerDoYouWantIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_PickDifferentDecor
	special DoesPlayerHaveNoDecorations
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_DontHaveAnyDecor
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	end

MauvilleCity_PokemonCenter_1F_EventScript_CancelPickDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontWantAnything, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_InvalidDecor::
	message MauvilleCity_PokemonCenter_1F_Text_CantTradeThatOne
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDifferentDecor::
	message MauvilleCity_PokemonCenter_1F_Text_PickADecorItem
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_DontHaveAnyDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontHaveAnyDecor, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive::
	msgbox MauvilleCity_PokemonCenter_1F_Text_PickTheDecorToTrade, MSGBOX_DEFAULT
	special TraderShowDecorationMenu
	waitstate
	goto_if_eq VAR_0x8006, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelGiveDecor
	goto_if_eq VAR_0x8006, 0xFFFF, MauvilleCity_PokemonCenter_1F_EventScript_DecorInUse
	special IsDecorationCategoryFull
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_NoRoomForDecor
	msgbox MauvilleCity_PokemonCenter_1F_Text_SoWellTradeTheseDecor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	special TraderDoDecorationTrade
	msgbox MauvilleCity_PokemonCenter_1F_Text_SendDecorToYourPC, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_CancelGiveDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontWantToTrade, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DecorInUse::
	msgbox MauvilleCity_PokemonCenter_1F_Text_ThatDecorIsInUse, MSGBOX_DEFAULT
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	end

MauvilleCity_PokemonCenter_1F_EventScript_NoRoomForDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouveNoRoomForThis, MSGBOX_DEFAULT
	release
	end

@ Storyteller
MauvilleCity_PokemonCenter_1F_Text_WillYouHearMyTale:
	.string "Aku adalah PENDONGENG.\n"
	.string "Aku akan menceritakan kisah-kisah\l"
	.string "TRAINER legendaris.\p"
	.string "Maukah kamu mendengar ceritaku?$"

MauvilleCity_PokemonCenter_1F_Text_StorytellerFeelingTheBlues:
	.string "Oh…\n"
	.string "Kamu membuatku merasa sedih…$"

MauvilleCity_PokemonCenter_1F_Text_WhichTaleToTell:
	.string "Aku tahu legenda-legenda ini.\n"
	.string "Kisah mana yang ingin kamu dengar?$"

MauvilleCity_PokemonCenter_1F_Text_IKnowNoTales:
	.string "Tapi, aku tidak tahu TRAINER legendaris.\n"
	.string "Maka, aku tidak tahu cerita.\p"
	.string "Di mana seseorang dapat menemukan TRAINER yang\n"
	.string "layak untuk kisah legendaris?$"

MauvilleCity_PokemonCenter_1F_Text_YouDidStatXTimes:
	.string "Apa itu?!\n"
	.string "Kamu… Kamu…\p"
	.string "{STR_VAR_2}\n"
	.string "{STR_VAR_1} kali?!\p"
	.string "Itu memang luar biasa!\n"
	.string "Ini adalah kelahiran legenda baru!$"

MauvilleCity_PokemonCenter_1F_Text_CouldThereBeOtherLegends:
	.string "Itu membuatku berpikir, mungkinkah ada\n"
	.string "TRAINER lain dengan legenda yang lebih mengesankan\l"
	.string "menanti untuk ditemukan?$"

MauvilleCity_PokemonCenter_1F_Text_HaveYouAnyLegendaryTales:
	.string "Apakah kamu seorang TRAINER?\p"
	.string "Kalau begitu, ceritakan padaku, apakah kamu punya kisah\n"
	.string "yang sedikit pun legendaris?$"

@ Unused
MauvilleCity_PokemonCenter_1F_Text_HearAnotherLegendaryTale:
	.string "Ngomong-ngomong… Maukah kamu mendengar\n"
	.string "kisah legendaris lainnya?$"

MauvilleCity_PokemonCenter_1F_Text_NotWorthyOfLegend:
	.string "Hmm…\n"
	.string "Aku tidak puas…\p"
	.string "Aku berharap kamu akan memberiku berita yang\n"
	.string "layak disebut legenda.$"

MauvilleCity_PokemonCenter_1F_Text_IWishMorePeopleWereInterested:
	.string "Aku berharap lebih banyak orang tertarik\n"
	.string "mendengar kisah epikku tentang TRAINER\l"
	.string "legendaris.$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameTitle::
	.string "TRAINER yang Suka Menyimpan$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameAction::
	.string "Menyimpan permainan$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini menyimpan permainan\n"
	.string "{STR_VAR_1} kali!\p"
	.string "TRAINER yang lebih berhati-hati dari\n"
	.string "{STR_VAR_3} tidak akan pernah ditemukan!$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedTitle::
	.string "TRAINER Pelopor Tren$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedAction::
	.string "Memulai tren$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini memulai tren baru\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} sedang menciptakan tren untuk seluruh\n"
	.string "wilayah HOENN!$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedTitle::
	.string "TRAINER Penanam BERRY$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedAction::
	.string "Menanam BERRY$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini menanam BERRY\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} adalah pencinta BERRY\n"
	.string "yang legendaris!$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesTitle::
	.string "TRAINER Pencinta SEPEDA$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesAction::
	.string "Menukar SEPEDA$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini menukar SEPEDA\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} pasti sangat mencintai SEPEDA\n"
	.string "dengan mendalam dan penuh gairah!$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsTitle::
	.string "TRAINER yang Diwawancarai$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsAction::
	.string "Diwawancarai$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini diwawancarai\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} pasti seorang TRAINER yang\n"
	.string "menarik banyak perhatian!$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesTitle::
	.string "TRAINER yang Suka Bertarung$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesAction::
	.string "Bertarung$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini bertarung {STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} pasti seorang TRAINER yang\n"
	.string "tidak pernah menolak kesempatan untuk bertarung!$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtTitle::
	.string "TRAINER Penangkap POKéMON$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtAction::
	.string "Menangkap POKéMON$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini menangkap\n"
	.string "{STR_VAR_1} POKéMON!\p"
	.string "{STR_VAR_3} adalah penangkap POKéMON\n"
	.string "liar yang legendaris!$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtTitle::
	.string "TRAINER Pemancing$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtAction::
	.string "Menangkap POKéMON dengan PANCING$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini menangkap\n"
	.string "{STR_VAR_1} POKéMON saat memancing!\p"
	.string "{STR_VAR_3} adalah ahli memancing\n"
	.string "yang legendaris!$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedTitle::
	.string "TRAINER Penangkar TELUR$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedAction::
	.string "Mengerami TELUR$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini menetaskan {STR_VAR_1} POKéMON\n"
	.string "dari TELUR!\p"
	.string "{STR_VAR_3} adalah penangkar TELUR\n"
	.string "yang legendaris!$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedTitle::
	.string "TRAINER Pengevolusi$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedAction::
	.string "Mengevolusikan POKéMON$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini membuat {STR_VAR_1} POKéMON\n"
	.string "berevolusi!\p"
	.string "{STR_VAR_3} adalah pengevolusi POKéMON\n"
	.string "terhebat!$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterTitle::
	.string "TRAINER Pencinta POKéMON CENTER$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterAction::
	.string "Menggunakan POKéMON CENTER$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini menyembuhkan POKéMON\n"
	.string "{STR_VAR_1} kali di POKéMON CENTER!\p"
	.string "Tidak ada pencinta POKéMON CENTER\n"
	.string "yang lebih hebat dari {STR_VAR_3}!$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeTitle::
	.string "TRAINER Rumahan$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeAction::
	.string "Mengistirahatkan POKéMON di rumah$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini menyembuhkan POKéMON\n"
	.string "{STR_VAR_1} kali di rumah!\p"
	.string "Tidak ada yang lebih betah di rumah\n"
	.string "daripada {STR_VAR_3}!$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesTitle::
	.string "TRAINER Pencinta SAFARI$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesAction::
	.string "Memasuki SAFARI ZONE$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini pergi ke SAFARI ZONE\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} adalah TRAINER yang sisi liarnya\n"
	.string "harus keluar di SAFARI ZONE!$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutTitle::
	.string "TRAINER Penggila CUT$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutAction::
	.string "Menggunakan CUT$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini menggunakan CUT\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} adalah TRAINER yang pasti\n"
	.string "suka CUT!$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashTitle::
	.string "TRAINER Penghancur BATU$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashAction::
	.string "Menghancurkan batu$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini menggunakan ROCK SMASH\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} pasti seorang TRAINER yang\n"
	.string "tidak bisa membiarkan batu tidak hancur!$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesTitle::
	.string "TRAINER Pencinta Pindah$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesAction::
	.string "Memindahkan SECRET BASE$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini memindahkan SECRET BASE\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} adalah TRAINER yang suka\n"
	.string "pindah rumah sering!$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashTitle::
	.string "TRAINER Penggila SPLASH$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashAction::
	.string "Menggunakan SPLASH$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini menggunakan SPLASH\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} adalah TRAINER yang pasti suka\n"
	.string "bermain air!$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleTitle::
	.string "TRAINER Ulet$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleAction::
	.string "Terpaksa menggunakan STRUGGLE$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini harus mengandalkan STRUGGLE\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} adalah TRAINER yang ulet\n"
	.string "yang tidak pernah menyerah pada kesulitan!$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsTitle::
	.string "Juara SLOT$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsAction::
	.string "Memenangkan jackpot di SLOT$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini memenangkan jackpot di\n"
	.string "SLOT {STR_VAR_1} kali.\p"
	.string "{STR_VAR_3} adalah TRAINER yang beruntung\n"
	.string "di SLOT!$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsTitle::
	.string "Juara ROULETTE$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsAction::
	.string "Memenangkan ROULETTE berturut-turut$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini memenangkan ROULETTE\n"
	.string "{STR_VAR_1} kali berturut-turut.\p"
	.string "{STR_VAR_3} beruntung saat bola\n"
	.string "memantul di ROULETTE!$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesTitle::
	.string "Penantang BATTLE TOWER$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesAction::
	.string "Mengambil tantangan BATTLE TOWER$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini mengikuti tantangan BATTLE TOWER\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} adalah TRAINER yang bercita-cita\n"
	.string "untuk keunggulan di BATTLE TOWER!$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksTitle::
	.string "TRAINER Pencinta Blend$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksAction::
	.string "Membuat {POKEBLOCK}S$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini membuat {POKEBLOCK}S\n"
	.string "{STR_VAR_1} kali!\p"
	.string "Tidak ada yang lebih baik dalam menggunakan BERRY\n"
	.string "BLENDER daripada {STR_VAR_3}!$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsTitle::
	.string "TRAINER Pencinta KONTEST$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsAction::
	.string "Mengikuti KONTEST$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini mengikuti KONTEST\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} pasti suka memamerkan\n"
	.string "POKéMON kepada orang lain!$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsTitle::
	.string "Master KONTEST$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsAction::
	.string "Memenangkan KONTEST$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini memenangkan KONTEST\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} pasti seorang master KONTEST\n"
	.string "yang luar biasa!$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedTitle::
	.string "Pembeli Bahagia$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedAction::
	.string "Berbelanja$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini membeli barang di toko\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} pasti salah satu dari orang-orang\n"
	.string "yang terlahir untuk berbelanja.$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderTitle::
	.string "TRAINER Penemu Item$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderAction::
	.string "Menggunakan ITEMFINDER$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini menggunakan ITEMFINDER\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} pasti suka menyisir tanah\n"
	.string "untuk mencari item tersembunyi!$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedTitle::
	.string "TRAINER Basah Kuyup Hujan$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedAction::
	.string "Kena hujan$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini basah kuyup karena hujan\n"
	.string "{STR_VAR_1} kali!\p"
	.string "Karismanya {STR_VAR_3} bahkan pasti\n"
	.string "menarik hujan!$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexTitle::
	.string "Pembaca POKéDEX yang Tekun$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexAction::
	.string "Memeriksa POKéDEX$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini memeriksa POKéDEX\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} pasti suka memeriksa\n"
	.string "POKéMON di POKéDEX!$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsTitle::
	.string "Kolektor RIBBON$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsAction::
	.string "Menerima RIBBON$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini menerima RIBBON\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} pasti seorang TRAINER yang\n"
	.string "suka mengumpulkan RIBBON!$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedTitle::
	.string "TRAINER Pelompat Tebing$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedAction::
	.string "Melompat dari tebing$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini melompat dari tebing\n"
	.string "{STR_VAR_1} kali!\p"
	.string "Jika ada tebing untuk dilompati,\n"
	.string "{STR_VAR_3} tidak bisa mengabaikannya!$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedTitle::
	.string "Penonton TV Legendaris$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedAction::
	.string "Menonton TV$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini menonton TV\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} pasti suka menonton TV!$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockTitle::
	.string "TRAINER Sadar Waktu$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockAction::
	.string "Memeriksa waktu$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini memeriksa waktu\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} pasti seorang TRAINER yang\n"
	.string "tepat waktu dan sadar waktu.$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryTitle::
	.string "Penyihir LOTERE POKéMON$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryAction::
	.string "Memenangkan LOTERE POKéMON$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini memenangkan LOTERE POKéMON\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} pasti punya banyak teman\n"
	.string "untuk bertukar POKéMON!$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareTitle::
	.string "TRAINER Pengguna DAY CARE$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareAction::
	.string "Meninggalkan POKéMON di DAY CARE$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini meninggalkan POKéMON di\n"
	.string "DAY CARE {STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} pasti seorang yang sangat ambisius\n"
	.string "yang memelihara POKéMON secara agresif!$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarTitle::
	.string "TRAINER Pencinta CABLE CAR$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarAction::
	.string "Mengendarai CABLE CAR$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini mengendarai CABLE CAR\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} pasti seorang TRAINER yang sibuk\n"
	.string "yang selalu naik turun!$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsTitle::
	.string "TRAINER Pencinta Pemandian Air Panas$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsAction::
	.string "Mandi di pemandian air panas$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsStory::
	.string "Ini adalah kisah seorang TRAINER\n"
	.string "bernama {STR_VAR_3}.\p"
	.string "TRAINER ini mandi di pemandian air panas\n"
	.string "{STR_VAR_1} kali!\p"
	.string "{STR_VAR_3} pasti seorang TRAINER dengan\n"
	.string "kulit sehalus bayi!$"


MauvilleCity_PokemonCenter_1F_EventScript_Storyteller::
	lock
	faceplayer
	setvar VAR_0x8008, 0
	setvar VAR_0x8009, 0
	setvar VAR_0x800A, 0
	setvar VAR_0x800B, 0
	msgbox MauvilleCity_PokemonCenter_1F_Text_WillYouHearMyTale, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	specialvar VAR_RESULT, StorytellerGetFreeStorySlot
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_KnowNoTales
	message MauvilleCity_PokemonCenter_1F_Text_WhichTaleToTell
	waitmessage
	special StorytellerStoryListMenu
	waitstate
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelStorySelection
	setvar VAR_0x8008, 1
	special Script_StorytellerDisplayStory
	waitmessage
	waitbuttonpress
	specialvar VAR_RESULT, StorytellerUpdateStat
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_AreThereOtherTales
	goto MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale

MauvilleCity_PokemonCenter_1F_EventScript_CancelStorySelection::
	goto MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	end

MauvilleCity_PokemonCenter_1F_EventScript_AreThereOtherTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_CouldThereBeOtherLegends, MSGBOX_DEFAULT
	specialvar VAR_RESULT, HasStorytellerAlreadyRecorded
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_StorytellerEnd
	goto MauvilleCity_PokemonCenter_1F_EventScript_DoYouHaveAnyTales

MauvilleCity_PokemonCenter_1F_EventScript_KnowNoTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_IKnowNoTales, MSGBOX_DEFAULT
MauvilleCity_PokemonCenter_1F_EventScript_DoYouHaveAnyTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_HaveYouAnyLegendaryTales, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	specialvar VAR_RESULT, Script_StorytellerInitializeRandomStat
	goto_if_eq VAR_RESULT, 1, MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale
	msgbox MauvilleCity_PokemonCenter_1F_Text_NotWorthyOfLegend, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDidStatXTimes, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller::
	msgbox MauvilleCity_PokemonCenter_1F_Text_StorytellerFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

@ Unused
MauvilleCity_PokemonCenter_1F_EventScript_WaitingForRecordMix::
	msgbox MauvilleCity_PokemonCenter_1F_Text_IWishMorePeopleWereInterested, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_StorytellerEnd::
	release
	end

@ Giddy
MauvilleCity_PokemonCenter_1F_Text_HearMyStory:
	.string "Aku girang sekali!\n"
	.string "Aku punya cerita seru untukmu!\p"
	.string "Maukah kamu mendengar ceritaku?$"

MauvilleCity_PokemonCenter_1F_Text_GiddyFeelingTheBlues:
	.string "Oh…\n"
	.string "Kamu membuatku jadi sedih…$"

MauvilleCity_PokemonCenter_1F_Text_AlsoIWasThinking:
	.string "Oh ya, aku kepikiran…$"

MauvilleCity_PokemonCenter_1F_Text_WeShouldChatAgain:
	.string "Kurasa itu saja…\p"
	.string "Lain kali kita ngobrol lagi ya!\n"
	.string "Dah!$"

MauvilleCity_PokemonCenter_1F_EventScript_Giddy::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_HearMyStory, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_TryTellTale
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineGiddy
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTellTale::
	special GiddyShouldTellAnotherTale
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale::
	special GiddyShouldTellAnotherTale
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_GiddyStartNewTale
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales
	end

MauvilleCity_PokemonCenter_1F_EventScript_GiddyStartNewTale::
	msgbox MauvilleCity_PokemonCenter_1F_Text_AlsoIWasThinking, MSGBOX_DEFAULT
	goto MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale
	end

@ Giddy will continue to tell stories regardless of whether yes or no is selected below.
@ Each story there is a 10% chance it will be his last. Otherwise he will stop at 10 stories.
MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale::
	special GenerateGiddyLine
	special ShowFieldMessageStringVar4
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineGiddy::
	msgbox MauvilleCity_PokemonCenter_1F_Text_GiddyFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WeShouldChatAgain, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToHearMySong:
	.string "Hai, aku BARD.\n"
	.string "Maukah kamu mendengar laguku?$"

MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues1:
	.string "Oh…\n"
	.string "Kamu membuatku jadi sedih…$"

MauvilleCity_PokemonCenter_1F_Text_WishICouldPlaySongForOthers:
	.string "Oh, lagu yang sangat menyentuh…\n"
	.string "Andai saja aku bisa memainkannya untuk orang lain…$"

MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToWriteSomeLyrics:
	.string "Jadi?\n"
	.string "Bagaimana menurutmu laguku?\p"
	.string "Tapi aku kurang suka dengan liriknya.\p"
	.string "Maukah kamu menulis lirik baru untukku?$"

MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues2:
	.string "Oh…\n"
	.string "Kamu membuatku jadi sedih…$"

MauvilleCity_PokemonCenter_1F_Text_LetMeSingItForYou:
	.string "Terima kasih banyak!\n"
	.string "Biar kunyanyikan untukmu.$"

MauvilleCity_PokemonCenter_1F_Text_ThatHowYouWantedSongToGo:
	.string "Seperti itukah lagu yang kamu inginkan?$"

MauvilleCity_PokemonCenter_1F_Text_IllSingThisSongForAWhile:
	.string "Oke! Kalau begitu, sudah diputuskan.\n"
	.string "Aku akan menyanyikan lagu ini untuk sementara waktu.$"

MauvilleCity_PokemonCenter_1F_Text_TeachWhatsHipAndHappening:
	.string "Hey, yo! Mereka memanggilku HIPSTER.\n"
	.string "Aku akan mengajarimu apa yang lagi ngetren.$"

MauvilleCity_PokemonCenter_1F_Text_IAlreadyTaughtYou:
	.string "Tapi, hei, aku sudah mengajarimu apa yang\n"
	.string "lagi ngetren.\p"
	.string "Aku ingin menyebarkan kata-kata gaul ini\n"
	.string "ke orang lain.$"

MauvilleCity_PokemonCenter_1F_Text_IveGotNothingNewToTeach:
	.string "Tapi, hei, kamu sudah tahu banyak tentang\n"
	.string "apa yang lagi ngetren.\p"
	.string "Aku tidak punya hal baru untuk diajarkan padamu!$"

MauvilleCity_PokemonCenter_1F_Text_HaveYouHeardOfWord:
	.string "Hei, kamu pernah dengar kata\n"
	.string "“{STR_VAR_1}”?\p"
	.string "Artinya apa? Yah…\n"
	.string "Tanya ayah atau ibumu saja, oke?$"