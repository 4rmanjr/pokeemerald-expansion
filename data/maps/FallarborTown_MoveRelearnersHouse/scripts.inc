FallarborTown_MoveRelearnersHouse_MapScripts::
	.byte 0

FallarborTown_MoveRelearnersHouse_EventScript_MoveRelearner::
	lockall
	applymovement LOCALID_MOVE_RELEARNER, Common_Movement_FacePlayer
	waitmovement 0
	goto_if_set FLAG_TEMP_1, FallarborTown_MoveRelearnersHouse_EventScript_AskTeachMove
	msgbox FallarborTown_MoveRelearnersHouse_Text_ImTheMoveTutor, MSGBOX_DEFAULT
	setflag FLAG_TEMP_1
	goto FallarborTown_MoveRelearnersHouse_EventScript_AskTeachMove
	end

FallarborTown_MoveRelearnersHouse_EventScript_AskTeachMove::
	checkitem ITEM_HEART_SCALE
	goto_if_eq VAR_RESULT, FALSE, FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	msgbox FallarborTown_MoveRelearnersHouse_Text_ThatsAHeartScaleWantMeToTeachMove, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	end

FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon::
	msgbox FallarborTown_MoveRelearnersHouse_Text_TutorWhichMon, MSGBOX_DEFAULT
	special ChooseMonForMoveRelearner
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, FallarborTown_MoveRelearnersHouse_EventScript_CantTeachEgg
	goto_if_eq VAR_0x8005, 0, FallarborTown_MoveRelearnersHouse_EventScript_NoMoveToTeachMon
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMove
	end

FallarborTown_MoveRelearnersHouse_EventScript_ChooseMove::
	msgbox FallarborTown_MoveRelearnersHouse_Text_TeachWhichMove, MSGBOX_DEFAULT
	special TeachMoveRelearnerMove
	waitstate
	goto_if_eq VAR_0x8004, 0, FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	msgbox FallarborTown_MoveRelearnersHouse_Text_HandedOverHeartScale, MSGBOX_DEFAULT
	removeitem ITEM_HEART_SCALE
	goto FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	end

FallarborTown_MoveRelearnersHouse_EventScript_NoMoveToTeachMon::
	msgbox FallarborTown_MoveRelearnersHouse_Text_DontHaveMoveToTeachPokemon, MSGBOX_DEFAULT
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	end

FallarborTown_MoveRelearnersHouse_EventScript_CantTeachEgg::
	msgbox FallarborTown_MoveRelearnersHouse_Text_CantTeachEgg, MSGBOX_DEFAULT
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	end

FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale::
	msgbox FallarborTown_MoveRelearnersHouse_Text_ComeBackWithHeartScale, MSGBOX_DEFAULT
	releaseall
	end

FallarborTown_MoveRelearnersHouse_Text_ImTheMoveTutor:
	.string "Aku adalah GURU JURUS.\p"
	.string "Aku tahu semua jurus yang dipelajari\n"
	.string "POKéMON--semuanya--dan aku bisa\l"
	.string "mengajarkan jurus-jurus itu pada POKéMON.\p"
	.string "Aku bisa mengajarkan jurus pada POKéMON\n"
	.string "milikmu jika kamu mau.\p"
	.string "Aku akan melakukannya dengan imbalan\n"
	.string "HEART SCALE. Aku sedang mengumpulkannya\l"
	.string "sekarang.$"

FallarborTown_MoveRelearnersHouse_Text_ThatsAHeartScaleWantMeToTeachMove:
	.string "Oh! Itu dia! Itu benar-benar\n"
	.string "HEART SCALE asli!\p"
	.string "Biar kutebak, kamu ingin aku mengajarkan\n"
	.string "sebuah jurus?$"

FallarborTown_MoveRelearnersHouse_Text_TutorWhichMon:
	.string "POKéMON mana yang butuh diajari?$"

FallarborTown_MoveRelearnersHouse_Text_TeachWhichMove:
	.string "Jurus mana yang harus kuajarkan?$"

FallarborTown_MoveRelearnersHouse_Text_DontHaveMoveToTeachPokemon:
	.string "Maaf…\p"
	.string "Sepertinya tidak ada jurus yang bisa\n"
	.string "kuajarkan pada POKéMON itu.$"

FallarborTown_MoveRelearnersHouse_Text_HandedOverHeartScale:
	.string "Satu HEART SCALE diserahkan\n"
	.string "sebagai gantinya.$"

FallarborTown_MoveRelearnersHouse_Text_ComeBackWithHeartScale:
	.string "Jika POKéMON-mu perlu belajar jurus,\n"
	.string "kembalilah dengan membawa HEART SCALE.$"

FallarborTown_MoveRelearnersHouse_Text_CantTeachEgg:
	.string "Hah? Tidak ada satu pun jurus yang\n"
	.string "bisa kuajarkan pada TELUR.$"

