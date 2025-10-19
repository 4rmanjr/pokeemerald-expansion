MysteryGiftScript_MysticTicket::
	setvaddress MysteryGiftScript_MysticTicket
	lock
	faceplayer
	vgoto_if_set FLAG_RECEIVED_MYSTIC_TICKET, MysticTicket_Obtained
	vgoto_if_set FLAG_CAUGHT_LUGIA, MysticTicket_Obtained
	vgoto_if_set FLAG_CAUGHT_HO_OH, MysticTicket_Obtained
	checkitem ITEM_MYSTIC_TICKET
	vgoto_if_eq VAR_RESULT, TRUE, MysticTicket_Obtained
	vmessage sText_MysticTicketForYou
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_MYSTIC_TICKET
	vgoto_if_eq VAR_RESULT, FALSE, MysticTicket_NoBagSpace
	giveitem ITEM_MYSTIC_TICKET
	setflag FLAG_ENABLE_SHIP_NAVEL_ROCK
	setflag FLAG_RECEIVED_MYSTIC_TICKET
	vmessage sText_MysticTicketUseAtPort
	waitmessage
	waitbuttonpress
	release
	end

MysticTicket_NoBagSpace:
	vmessage sText_MysticTicketBagFull
	waitmessage
	waitbuttonpress
	release
	end

MysticTicket_Obtained:
	vmessage sText_MysticTicketThankYou
	waitmessage
	waitbuttonpress
	release
	end

sText_MysticTicketForYou:
	.string "Terima kasih telah menggunakan\n"
	.string "Sistem MYSTERY GIFT.\p"
	.string "Kamu pasti {PLAYER}.\n"
	.string "Ada tiket di sini untukmu.$"

sText_MysticTicketUseAtPort:
	.string "Sepertinya ini untuk digunakan di\n"
	.string "pelabuhan KOTA LILYCOVE.\p"
	.string "Mengapa tidak mencobanya dan melihat\n"
	.string "tentang apa itu?$"

sText_MysticTicketThankYou:
	.string "Terima kasih telah menggunakan\n"
	.string "Sistem MYSTERY GIFT.$"

sText_MysticTicketBagFull:
	.string "Oh, maaf, {PLAYER}.\n"
	.string "KANTONG KEY ITEMS TAS-mu penuh.\p"
	.string "Silakan simpan sesuatu di PC-mu,\n"
	.string "lalu kembali untuk ini.$"
