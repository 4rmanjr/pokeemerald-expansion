AquaHideout_1F_MapScripts::
	.byte 0

@ The below two entrance guards give hints about what to do to progress the story
AquaHideout_1F_EventScript_HideoutEntranceGrunt1::
	lock
	faceplayer
	goto_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, AquaHideout_1F_EventScript_SlateportHint1
	goto_if_set FLAG_RECEIVED_RED_OR_BLUE_ORB, AquaHideout_1F_EventScript_MagmaHideoutHint1
	msgbox AquaHideout_1F_Text_OurBossIsSnatchingSomething, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_MagmaHideoutHint1::
	msgbox AquaHideout_1F_Text_WhereMightMagmaHideoutBe, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_SlateportHint1::
	msgbox AquaHideout_1F_Text_BossWentToJackASubmarine, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_HideoutEntranceGrunt2::
	lock
	faceplayer
	goto_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, AquaHideout_1F_EventScript_SlateportHint2
	goto_if_set FLAG_RECEIVED_RED_OR_BLUE_ORB, AquaHideout_1F_EventScript_MagmaHideoutHint2
	msgbox AquaHideout_1F_Text_BossIsOnRoute122, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_MagmaHideoutHint2::
	msgbox AquaHideout_1F_Text_TeamMagmaAtMtChimney, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_SlateportHint2::
	msgbox AquaHideout_1F_Text_BossIsInSlateportCity, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_1, AquaHideout_1F_Text_Grunt1Intro, AquaHideout_1F_Text_Grunt1Defeat, AquaHideout_1F_EventScript_Grunt1Defeated
	msgbox AquaHideout_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_1F_EventScript_Grunt1Defeated::
	msgbox AquaHideout_1F_Text_Grunt1PostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_Text_OurBossIsSnatchingSomething:
	.string "Apa? Apa? Mau apa kamu dengan\n"
	.string "TIM AQUA?\p"
	.string "BOS kami tidak di sini! Dia pergi\n"
	.string "merebut sesuatu yang penting!\p"
	.string "… …\n"
	.string "Ke mana dia pergi?\p"
	.string "Wahaha! Apa kamu pikir aku akan\n"
	.string "memberitahumu hal sepenting itu?$"

AquaHideout_1F_Text_WhereMightMagmaHideoutBe:
	.string "Apa? Apa?\n"
	.string "Kamu kroco TIM MAGMA?\p"
	.string "Kudengar TIM MAGMA mencoba\n"
	.string "membangkitkan POKéMON hebat di\l"
	.string "MARKAS mereka.\p"
	.string "Tapi di mana ya MARKAS mereka?$"

AquaHideout_1F_Text_BossWentToJackASubmarine:
	.string "Apa? Apa? Mau apa kamu dengan\n"
	.string "TIM AQUA?\p"
	.string "BOS kami tidak di sini!\n"
	.string "Dia pergi membajak kapal selam!\p"
	.string "… …\n"
	.string "Ke mana dia pergi?\p"
	.string "Wahaha! Apa kamu pikir aku akan\n"
	.string "memberitahumu hal sepenting itu?$"

AquaHideout_1F_Text_BossIsOnRoute122:
	.string "Apa? Apa? Mau apa kamu dengan\n"
	.string "TIM AQUA?\p"
	.string "BOS kami tidak di sini! Dia sedang menuju\n"
	.string "GUNUNG PYRE di RUTE 122!\p"
	.string "… …\n"
	.string "Kenapa dia pergi?\p"
	.string "Wahaha! Apa kamu pikir aku akan\n"
	.string "memberitahumu hal sepenting itu?$"

AquaHideout_1F_Text_TeamMagmaAtMtChimney:
	.string "Apa? Apa?\n"
	.string "Kamu kroco TIM MAGMA?\p"
	.string "Kudengar TIM MAGMA mengincar\n"
	.string "POKéMON hebat di GUNUNG CHIMNEY.\p"
	.string "Tapi seperti apa POKéMON itu?$"

AquaHideout_1F_Text_BossIsInSlateportCity:
	.string "Apa? Apa? Mau apa kamu dengan\n"
	.string "TIM AQUA?\p"
	.string "BOS kami tidak di sini!\n"
	.string "Dia sedang menuju KOTA SLATEPORT!\p"
	.string "… …\n"
	.string "Kenapa dia pergi?\p"
	.string "Wahaha! Apa kamu pikir aku akan\n"
	.string "memberitahumu hal sepenting itu?$"

AquaHideout_1F_Text_Grunt1Intro:
	.string "Ayiyiyi!\n"
	.string "Orang mencurigakan terlihat!$"

AquaHideout_1F_Text_Grunt1Defeat:
	.string "Grrrrr…\n"
	.string "Aku kalah!$"

AquaHideout_1F_Text_Grunt1PostBattle:
	.string "Aku kalah demi TIM,\n"
	.string "tapi tugasku sudah selesai…$"

