MysteryGiftScript_OldSeaMap::
	setvaddress MysteryGiftScript_OldSeaMap
	lock
	faceplayer
	vgoto_if_set FLAG_RECEIVED_OLD_SEA_MAP, OldSeaMap_Obtained
	vgoto_if_set FLAG_CAUGHT_MEW, OldSeaMap_Obtained
	checkitem ITEM_OLD_SEA_MAP
	vgoto_if_eq VAR_RESULT, TRUE, OldSeaMap_Obtained
	vmessage sText_MysteryGiftOldSeaMapForYou
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_OLD_SEA_MAP
	vgoto_if_eq VAR_RESULT, FALSE, OldSeaMap_NoBagSpace
	giveitem ITEM_OLD_SEA_MAP
	setflag FLAG_ENABLE_SHIP_FARAWAY_ISLAND
	setflag FLAG_RECEIVED_OLD_SEA_MAP
	vmessage sText_MysteryGiftOldSeaMapUseAtPort
	waitmessage
	waitbuttonpress
	release
	end

OldSeaMap_NoBagSpace:
	vmessage sText_MysteryGiftOldSeaMapBagFull
	waitmessage
	waitbuttonpress
	release
	end

OldSeaMap_Obtained:
	vmessage sText_MysteryGiftOldSeaMapThankYou
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftOldSeaMapForYou:
	.string "Terima kasih telah menggunakan\n"
	.string "Sistem MYSTERY GIFT.\p"
	.string "Izinkan saya konfirmasi--apakah kamu {PLAYER}?\p"
	.string "Kami menerima OLD SEA MAP ini\n"
	.string "yang ditujukan kepadamu.$"

sText_MysteryGiftOldSeaMapUseAtPort:
	.string "Sepertinya ini untuk digunakan di\n"
	.string "pelabuhan KOTA LILYCOVE.\p"
	.string "Mengapa tidak mencobanya dan melihat\n"
	.string "tentang apa itu?$"

sText_MysteryGiftOldSeaMapThankYou:
	.string "Terima kasih telah menggunakan\n"
	.string "Sistem MYSTERY GIFT.$"

sText_MysteryGiftOldSeaMapBagFull:
	.string "Oh, maaf, {PLAYER}.\n"
	.string "KANTONG KEY ITEMS TAS-mu penuh.\p"
	.string "Silakan simpan sesuatu di PC-mu,\n"
	.string "lalu kembali untuk ini.$"
