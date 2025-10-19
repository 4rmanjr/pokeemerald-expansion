Route111_OldLadysRestStop_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route111_OldLadysRestStop_OnTransition
	.byte 0

Route111_OldLadysRestStop_OnTransition:
	setflag FLAG_LANDMARK_OLD_LADY_REST_SHOP
	end

Route111_OldLadysRestStop_EventScript_OldLady::
	lock
	faceplayer
	msgbox Route111_OldLadysRestStop_Text_RestUpHere, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route111_OldLadysRestStop_EventScript_Rest
	goto_if_eq VAR_RESULT, NO, Route111_OldLadysRestStop_EventScript_DeclineRest
	end

Route111_OldLadysRestStop_EventScript_Rest::
	msgbox Route111_OldLadysRestStop_Text_TakeYourTimeRestUp, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox Route111_OldLadysRestStop_Text_StillTiredTakeAnotherRest, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route111_OldLadysRestStop_EventScript_Rest
	goto_if_eq VAR_RESULT, NO, Route111_OldLadysRestStop_EventScript_DeclineRest
	end

Route111_OldLadysRestStop_EventScript_DeclineRest::
	msgbox Route111_OldLadysRestStop_Text_DontNeedToBeShy, MSGBOX_DEFAULT
	release
	end

Route111_OldLadysRestStop_Text_RestUpHere:
	.string "Oh, sayang, sayang.\n"
	.string "Bukankah POKéMON-mu kelelahan?\p"
	.string "Jika kamu mau, istirahatlah di sini.\n"
	.string "Itu ide yang bagus! Kamu harus melakukannya.$"

Route111_OldLadysRestStop_Text_TakeYourTimeRestUp:
	.string "Benar sekali.\n"
	.string "Luangkan waktumu dan istirahatlah!$"

Route111_OldLadysRestStop_Text_StillTiredTakeAnotherRest:
	.string "Oh, sayang, sayang.\n"
	.string "Apakah POKéMON-mu masih lelah?\p"
	.string "Kamu harus beristirahat lagi di sini.\n"
	.string "Itu ide yang bagus. Kamu harus melakukannya.$"

Route111_OldLadysRestStop_Text_DontNeedToBeShy:
	.string "Begitukah?\n"
	.string "Kamu tidak perlu malu tentang itu.$"

