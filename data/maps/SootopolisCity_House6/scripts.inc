SootopolisCity_House6_MapScripts::
	.byte 0

SootopolisCity_House6_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_WAILMER_DOLL, SootopolisCity_House6_EventScript_ReceivedWailmerDoll
	msgbox SootopolisCity_House6_Text_FirstGuestInWhileTakeDoll, MSGBOX_YESNO
	call_if_eq VAR_RESULT, NO, SootopolisCity_House6_EventScript_DeclineWailmerDoll
	msgbox SootopolisCity_House6_Text_TakeGoodCareOfIt, MSGBOX_DEFAULT
	givedecoration DECOR_WAILMER_DOLL
	goto_if_eq VAR_RESULT, FALSE, SootopolisCity_House6_EventScript_NoRoomForWailmerDoll
	setflag FLAG_RECEIVED_WAILMER_DOLL
	release
	end

SootopolisCity_House6_EventScript_DeclineWailmerDoll::
	msgbox SootopolisCity_House6_Text_DontWantThisDoll, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House6_EventScript_ReceivedWailmerDoll::
	msgbox SootopolisCity_House6_Text_LovePlushDolls, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House6_EventScript_NoRoomForWailmerDoll::
	bufferdecorationname STR_VAR_2, DECOR_WAILMER_DOLL
	msgbox gText_NoRoomLeftForAnother, MSGBOX_DEFAULT
	msgbox SootopolisCity_House6_Text_IllHoldItForYou, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House6_Text_FirstGuestInWhileTakeDoll:
	.string "Halo! Kamu tamu pertama kami\n"
	.string "setelah sekian lama.\p"
	.string "Kamu membuat hariku cerah, jadi aku\n"
	.string "akan memberimu BONEKA WAILMER besar.$"

SootopolisCity_House6_Text_TakeGoodCareOfIt:
	.string "Jaga baik-baik!$"

SootopolisCity_House6_Text_IllHoldItForYou:
	.string "Oh, kamu mau, tapi tidak sekarang?\n"
	.string "Baiklah, kalau begitu aku akan menyimpannya untukmu.$"

SootopolisCity_House6_Text_DontWantThisDoll:
	.string "Kamu yakin?\n"
	.string "Kamu tidak mau BONEKA ini?$"

SootopolisCity_House6_Text_LovePlushDolls:
	.string "Aku suka BONEKA mewah!$"

