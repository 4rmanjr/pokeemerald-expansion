MysteryGiftScript_BattleCard::
	setvaddress MysteryGiftScript_BattleCard
	vgoto_if_set FLAG_MYSTERY_GIFT_DONE, MysteryGiftScript_BattleCardInfo
	setorcopyvar VAR_RESULT, GET_CARD_BATTLES_WON
	specialvar VAR_0x8008, GetMysteryGiftCardStat
	vgoto_if_ne VAR_0x8008, REQUIRED_CARD_BATTLES, MysteryGiftScript_BattleCardInfo
	lock
	faceplayer
	vmessage sText_MysteryGiftBattleCountCard_WonPrize
	waitmessage
	waitbuttonpress
	giveitem ITEM_POTION
	release
	setflag FLAG_MYSTERY_GIFT_DONE
	end

MysteryGiftScript_BattleCardInfo:
	lock
	faceplayer
	vmessage sText_MysteryGiftBattleCountCard
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftBattleCountCard:
	.string "Terima kasih telah menggunakan\n"
	.string "Sistem MYSTERY GIFT.\p"
	.string "BATTLE COUNT CARD-mu mencatat\n"
	.string "rekam jejak pertarunganmu melawan\l"
	.string "TRAINER dengan CARD yang sama.\p"
	.string "Cari dan lawanlah TRAINER yang\n"
	.string "memiliki CARD yang sama denganmu.\p"
	.string "Kamu dapat memeriksa peringkat keseluruhan\n"
	.string "dengan membaca NEWS.\p"
	.string "Silakan dicoba!$"

sText_MysteryGiftBattleCountCard_WonPrize:
	.string "Terima kasih telah menggunakan\n"
	.string "Sistem MYSTERY GIFT.\p"
	.string "Selamat!\p"
	.string "Kamu telah memenangkan hadiah karena\n"
	.string "memenangkan tiga pertarungan!\p"
	.string "Kami harap kamu akan terinspirasi untuk\n"
	.string "bertarung lebih banyak lagi.$"
