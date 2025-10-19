SootopolisCity_House3_MapScripts::
	.byte 0

SootopolisCity_House3_EventScript_Woman::
	lock
	faceplayer
	msgbox SootopolisCity_House3_Text_JuanHasManyFansDoYou, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SootopolisCity_House3_EventScript_HaveFans
	msgbox SootopolisCity_House3_Text_LonesomeTryWorkingHarder, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House3_EventScript_HaveFans::
	msgbox SootopolisCity_House3_Text_YouMustBePrettyStrong, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House3_EventScript_Girl::
	msgbox SootopolisCity_House3_Text_TrainerFanClubWasWild, MSGBOX_NPC
	end

SootopolisCity_House3_Text_JuanHasManyFansDoYou:
	.string "Kamu seorang POKéMON TRAINER, kan?\p"
	.string "JUAN dari SOOTOPOLIS punya banyak penggemar.\n"
	.string "Bahkan lebih banyak dari muridnya WALLACE!\p"
	.string "Apakah kamu punya?$"

SootopolisCity_House3_Text_YouMustBePrettyStrong:
	.string "Oh, kalau begitu kamu pasti cukup kuat.$"

SootopolisCity_House3_Text_LonesomeTryWorkingHarder:
	.string "Oh, sayang…\n"
	.string "Itu sedikit kesepian.\p"
	.string "Cobalah bekerja sedikit lebih keras untuk\n"
	.string "mendapatkan penggemar.$"

SootopolisCity_House3_Text_TrainerFanClubWasWild:
	.string "Penggemar setia datang bahkan dari\n"
	.string "luar HOENN.\p"
	.string "Sangat liar saat aku pergi ke\n"
	.string "TRAINER FAN CLUB di LILYCOVE.$"

