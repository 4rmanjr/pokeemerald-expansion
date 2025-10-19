SootopolisCity_House2_MapScripts::
	.byte 0

SootopolisCity_House2_EventScript_ExpertF::
	lock
	faceplayer
	msgbox SootopolisCity_House2_Text_DidYouKnowAboutMtPyreOrbs, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, SootopolisCity_House2_EventScript_KnowAboutOrbs
	call_if_eq VAR_RESULT, NO, SootopolisCity_House2_EventScript_DontKnowAboutOrbs
	release
	end

SootopolisCity_House2_EventScript_KnowAboutOrbs::
	msgbox SootopolisCity_House2_Text_YesTwoOrbsSideBySide, MSGBOX_DEFAULT
	return

SootopolisCity_House2_EventScript_DontKnowAboutOrbs::
	msgbox SootopolisCity_House2_Text_OughtToVisitAndSee, MSGBOX_DEFAULT
	return

SootopolisCity_House2_Text_DidYouKnowAboutMtPyreOrbs:
	.string "MT. PYRE…\p"
	.string "Di puncaknya ada dua bola yang\n"
	.string "diletakkan berdampingan. Tahukah kamu?$"

SootopolisCity_House2_Text_YesTwoOrbsSideBySide:
	.string "Ya, dua bola berdampingan…\p"
	.string "Pemandangan mereka bersama…\n"
	.string "Entah bagaimana menenangkan…$"

SootopolisCity_House2_Text_OughtToVisitAndSee:
	.string "Begitukah?\n"
	.string "Mungkin kamu harus berkunjung dan melihat…$"

