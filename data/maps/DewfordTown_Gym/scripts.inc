DewfordTown_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordTown_Gym_OnTransition
	.byte 0

DewfordTown_Gym_OnTransition:
	call DewfordTown_Gym_EventScript_SetFlashLevel
	end

DewfordTown_Gym_EventScript_SetFlashLevel::
	goto_if_defeated TRAINER_BRAWLY_1, DewfordTown_Gym_EventScript_SetLightsOn
	call DewfordTown_Gym_EventScript_CountTrainersDefeated
	copyvar VAR_0x8001, VAR_0x8000
	goto_if_eq VAR_0x8000, 0, DewfordTown_Gym_EventScript_SetFlashLevel7
	goto_if_eq VAR_0x8000, 1, DewfordTown_Gym_EventScript_SetFlashLevel6
	goto_if_eq VAR_0x8000, 2, DewfordTown_Gym_EventScript_SetFlashLevel5
	goto_if_eq VAR_0x8000, 3, DewfordTown_Gym_EventScript_SetFlashLevel4
	goto_if_eq VAR_0x8000, 4, DewfordTown_Gym_EventScript_SetFlashLevel3
	goto_if_eq VAR_0x8000, 5, DewfordTown_Gym_EventScript_SetFlashLevel2
	goto DewfordTown_Gym_EventScript_SetFlashLevel1

DewfordTown_Gym_EventScript_SetLightsOn::
	setflashlevel 0
	return

@ Brightest
DewfordTown_Gym_EventScript_SetFlashLevel1::
	setflashlevel 1
	return

DewfordTown_Gym_EventScript_SetFlashLevel2::
	setflashlevel 2
	return

DewfordTown_Gym_EventScript_SetFlashLevel3::
	setflashlevel 3
	return

DewfordTown_Gym_EventScript_SetFlashLevel4::
	setflashlevel 4
	return

DewfordTown_Gym_EventScript_SetFlashLevel5::
	setflashlevel 5
	return

DewfordTown_Gym_EventScript_SetFlashLevel6::
	setflashlevel 6
	return

@ Darkest
DewfordTown_Gym_EventScript_SetFlashLevel7::
	setflashlevel 7
	return

DewfordTown_Gym_EventScript_BrightenRoom::
	call DewfordTown_Gym_EventScript_CountTrainersDefeated
	nop1
	goto_if_eq VAR_0x8000, VAR_0x8001, DewfordTown_Gym_EventScript_NoLightChange
	copyvar VAR_0x8001, VAR_0x8000
	goto_if_eq VAR_0x8000, 1, DewfordTown_Gym_EventScript_AnimateFlash1Trainer
	goto_if_eq VAR_0x8000, 2, DewfordTown_Gym_EventScript_AnimateFlash2Trainers
	goto_if_eq VAR_0x8000, 3, DewfordTown_Gym_EventScript_AnimateFlash3Trainers
	goto_if_eq VAR_0x8000, 4, DewfordTown_Gym_EventScript_AnimateFlash4Trainers
	goto_if_eq VAR_0x8000, 5, DewfordTown_Gym_EventScript_AnimateFlash5Trainers
	goto_if_eq VAR_0x8000, 6, DewfordTown_Gym_EventScript_AnimateFlash6Trainers

DewfordTown_Gym_EventScript_NoLightChange::
	return

@ NOTE: A little confusingly, a larger animateflash param value is a smaller flash radius
DewfordTown_Gym_EventScript_AnimateFlash1Trainer::
	playse SE_SWITCH
	animateflash 6
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash2Trainers::
	playse SE_SWITCH
	animateflash 5
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash3Trainers::
	playse SE_SWITCH
	animateflash 4
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash4Trainers::
	playse SE_SWITCH
	animateflash 3
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash5Trainers::
	playse SE_SWITCH
	animateflash 2
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlash6Trainers::
	playse SE_SWITCH
	animateflash 1
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_AnimateFlashFullBrightness::
	playse SE_SWITCH
	animateflash 0
	call DewfordTown_Gym_EventScript_SetFlashLevel
	return

DewfordTown_Gym_EventScript_CountTrainersDefeated::
	setvar VAR_0x8000, 0
	goto_if_not_defeated TRAINER_TAKAO, DewfordTown_Gym_EventScript_CheckJocelyn
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckJocelyn::
	goto_if_not_defeated TRAINER_JOCELYN, DewfordTown_Gym_EventScript_CheckLaura
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckLaura::
	goto_if_not_defeated TRAINER_LAURA, DewfordTown_Gym_EventScript_CheckBrenden
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckBrenden::
	goto_if_not_defeated TRAINER_BRENDEN, DewfordTown_Gym_EventScript_CheckCristian
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckCristian::
	goto_if_not_defeated TRAINER_CRISTIAN, DewfordTown_Gym_EventScript_CheckLilith
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_CheckLilith::
	goto_if_not_defeated TRAINER_LILITH, DewfordTown_Gym_EventScript_StopCountingTrainers
	addvar VAR_0x8000, 1
DewfordTown_Gym_EventScript_StopCountingTrainers::
	return

DewfordTown_Gym_EventScript_Brawly::
	trainerbattle_single TRAINER_BRAWLY_1, DewfordTown_Gym_Text_BrawlyIntro, DewfordTown_Gym_Text_BrawlyDefeat, DewfordTown_Gym_EventScript_BrawlyDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, DewfordTown_Gym_EventScript_BrawlyRematch
	goto_if_unset FLAG_RECEIVED_TM_BULK_UP, DewfordTown_Gym_EventScript_GiveBulkUp2
	msgbox DewfordTown_Gym_Text_BrawlyPostBattle, MSGBOX_DEFAULT
	release
	end

DewfordTown_Gym_EventScript_BrawlyDefeated::
	call DewfordTown_Gym_EventScript_AnimateFlashFullBrightness
	message DewfordTown_Gym_Text_ReceivedKnuckleBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox DewfordTown_Gym_Text_KnuckleBadgeInfoTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_DEWFORD_GYM
	setflag FLAG_BADGE02_GET
	addvar VAR_PETALBURG_GYM_STATE, 1
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	setvar VAR_0x8008, 2
	call Common_EventScript_SetGymTrainers
	call DewfordTown_Gym_EventScript_GiveBulkUp
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox DewfordTown_Gym_Text_RegisteredBrawly, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_BRAWLY_MATCH_CALL
	setvar VAR_ROXANNE_CALL_STEP_COUNTER, 0
	setflag FLAG_ENABLE_ROXANNE_FIRST_CALL
	release
	end

DewfordTown_Gym_EventScript_GiveBulkUp::
	giveitem ITEM_TM_BULK_UP
	goto_if_eq VAR_RESULT, 0, Common_EventScript_BagIsFull
	msgbox DewfordTown_Gym_Text_ExplainBulkUp, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_BULK_UP
	return

DewfordTown_Gym_EventScript_GiveBulkUp2:
	giveitem ITEM_TM_BULK_UP
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	msgbox DewfordTown_Gym_Text_ExplainBulkUp, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_BULK_UP
	release
	end

DewfordTown_Gym_EventScript_BrawlyRematch::
	trainerbattle_rematch_double TRAINER_BRAWLY_1, DewfordTown_Gym_Text_BrawlyPreRematch, DewfordTown_Gym_Text_BrawlyRematchDefeat, DewfordTown_Gym_Text_BrawlyRematchNeedTwoMons
	msgbox DewfordTown_Gym_Text_BrawlyPostRematch, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_Takao::
	trainerbattle_single TRAINER_TAKAO, DewfordTown_Gym_Text_TakaoIntro, DewfordTown_Gym_Text_TakaoDefeat, DewfordTown_Gym_EventScript_TakaoBrightenRoom
	msgbox DewfordTown_Gym_Text_TakaoPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_TakaoBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Jocelyn::
	trainerbattle_single TRAINER_JOCELYN, DewfordTown_Gym_Text_JocelynIntro, DewfordTown_Gym_Text_JocelynDefeat, DewfordTown_Gym_EventScript_JocelynBrightenRoom
	msgbox DewfordTown_Gym_Text_JocelynPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_JocelynBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Laura::
	trainerbattle_single TRAINER_LAURA, DewfordTown_Gym_Text_LauraIntro, DewfordTown_Gym_Text_LauraDefeat, DewfordTown_Gym_EventScript_LauraBrightenRoom
	msgbox DewfordTown_Gym_Text_LauraPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_LauraBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Brenden::
	trainerbattle_single TRAINER_BRENDEN, DewfordTown_Gym_Text_BrendenIntro, DewfordTown_Gym_Text_BrendenDefeat, DewfordTown_Gym_EventScript_BrendenBrightenRoom
	msgbox DewfordTown_Gym_Text_BrendenPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_BrendenBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Cristian::
	trainerbattle_single TRAINER_CRISTIAN, DewfordTown_Gym_Text_CristianIntro, DewfordTown_Gym_Text_CristianDefeat, DewfordTown_Gym_EventScript_CristianBrightenRoom
	msgbox DewfordTown_Gym_Text_CristianPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_CristianBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_Lilith::
	trainerbattle_single TRAINER_LILITH, DewfordTown_Gym_Text_LilithIntro, DewfordTown_Gym_Text_LilithDefeat, DewfordTown_Gym_EventScript_LilithBrightenRoom
	msgbox DewfordTown_Gym_Text_LilithPostBattle, MSGBOX_AUTOCLOSE
	end

DewfordTown_Gym_EventScript_LilithBrightenRoom::
	call DewfordTown_Gym_EventScript_BrightenRoom
	release
	end

DewfordTown_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_DEWFORD_GYM, DewfordTown_Gym_EventScript_GymGuidePostVictory
	msgbox DewfordTown_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

DewfordTown_Gym_EventScript_GymGuidePostVictory::
	msgbox DewfordTown_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

DewfordTown_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE02_GET, DewfordTown_Gym_EventScript_GymStatueCertified
	goto DewfordTown_Gym_EventScript_GymStatue
	end

DewfordTown_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE02_GET, DewfordTown_Gym_EventScript_GymStatueCertified
	goto DewfordTown_Gym_EventScript_GymStatue
	end

DewfordTown_Gym_EventScript_GymStatueCertified::
	msgbox DewfordTown_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Gym_EventScript_GymStatue::
	msgbox DewfordTown_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Gym_Text_GymGuideAdvice:
	.string "Hei, apa kabar, calon JUARA\n"
	.string "{PLAYER}?\p"
	.string "GYM LEADER DEWFORD, BRAWLY, menggunakan\n"
	.string "POKéMON tipe FIGHTING.\p"
	.string "Melawannya dengan POKéMON tipe NORMAL\n"
	.string "sama saja cari masalah.\p"
	.string "POKéMON FIGHTING akan menghajar POKéMON\n"
	.string "NORMAL dengan serius, jadi hati-hatilah!\p"
	.string "Lebih buruk lagi, GYM ini gelap seperti\n"
	.string "dasar lautan.\p"
	.string "Tapi akan menjadi lebih terang setelah\n"
	.string "mengalahkan TRAINER yang menghalangimu.\p"
	.string "Hei, oke, maju!$"

DewfordTown_Gym_Text_GymGuidePostVictory:
	.string "Whoah! Di sini jadi terlalu terang!\p"
	.string "Masa depanmu juga cerah!$"

DewfordTown_Gym_Text_TakaoIntro:
	.string "Kekuatan adalah kebenaran!\n"
	.string "Ayo!$"

DewfordTown_Gym_Text_TakaoDefeat:
	.string "Kekuatan tidak cukup…$"

DewfordTown_Gym_Text_TakaoPostBattle:
	.string "Keahlianmu mengalahkan kekuatanku!\n"
	.string "Teknikmu patut dipuji!$"

DewfordTown_Gym_Text_JocelynIntro:
	.string "Tidak perlu melibatkan BRAWLY!\p"
	.string "Aku akan menghancurkanmu!$"

DewfordTown_Gym_Text_JocelynDefeat:
	.string "Tapi… Bagaimana?\n"
	.string "Bagaimana aku bisa kalah semudah ini?$"

DewfordTown_Gym_Text_JocelynPostBattle:
	.string "Aku tidak akan menyia-nyiakan kekalahan ini.\n"
	.string "Aku akan menggunakannya untuk memotivasiku\lberlatih!\p"
	.string "Suatu hari nanti aku akan menjadi GYM LEADER…\p"
	.string "Tidak, aku akan menjadi JUARA LIGA\n"
	.string "POKéMON!$"

DewfordTown_Gym_Text_LauraIntro:
	.string "Jangan berani-beraninya meremehkanku!\n"
	.string "Bukan salahku jika kamu menangis!$"

DewfordTown_Gym_Text_LauraDefeat:
	.string "Waaaaaaah!\n"
	.string "Aku kalah!$"

DewfordTown_Gym_Text_LauraPostBattle:
	.string "Aku bertarung dalam gelap untuk membuat\n"
	.string "hatiku lebih kuat.\p"
	.string "Tapi karena sangat gelap, aku tidak pernah\n"
	.string "bisa melihat wajah BRAWLY…$"

DewfordTown_Gym_Text_LilithIntro:
	.string "Ufufu…\n"
	.string "Apa kamu tersandung-sandung dalam gelap?$"

DewfordTown_Gym_Text_LilithDefeat:
	.string "Oh, kamu…\n"
	.string "Aku tidak mau kenal kamu!$"

DewfordTown_Gym_Text_LilithPostBattle:
	.string "Kamu pantas tersesat dan kembali lagi\n"
	.string "ke pintu masuk!$"

DewfordTown_Gym_Text_BrendenIntro:
	.string "Akan kutunjukkan semangat seorang\n"
	.string "pelaut!$"

DewfordTown_Gym_Text_BrendenDefeat:
	.string "Bagaimana ini bisa terjadi?\n"
	.string "Tidak biasanya aku kalah seperti ini!$"

DewfordTown_Gym_Text_BrendenPostBattle:
	.string "Oh, ya! Kamu layak bertemu\n"
	.string "dengan GYM LEADER kami.$"

DewfordTown_Gym_Text_CristianIntro:
	.string "Jika kamu ingin lewat, kamu harus\n"
	.string "melewatiku dulu!$"

DewfordTown_Gym_Text_CristianDefeat:
	.string "Grrrrr!\n"
	.string "Terlalu kuat!$"

DewfordTown_Gym_Text_CristianPostBattle:
	.string "Kamu menang!\n"
	.string "Kejar LENCANA itu!$"

DewfordTown_Gym_Text_BrawlyIntro:
	.string "Aku BRAWLY!\n"
	.string "GYM LEADER DEWFORD!\p"
	.string "Aku telah terombang-ambing di ombak ganas\n"
	.string "daerah ini, dan aku menjadi tangguh\l"
	.string "di gua yang gelap gulita!\p"
	.string "Jadi kamu ingin menantangku?\n"
	.string "Coba kulihat kemampuanmu!$"

DewfordTown_Gym_Text_BrawlyDefeat:
	.string "Whoah, wow! Kamu membuat gebrakan\n"
	.string "yang jauh lebih besar dari dugaanku!\p"
	.string "Kamu mengalahkanku!\p"
	.string "Oke, kamu berhasil.\n"
	.string "Ambil LENCANA GYM ini!$"

DewfordTown_Gym_Text_ReceivedKnuckleBadge:
	.string "KNUCKLE BADGE diterima\n"
	.string "dari BRAWLY.$"

DewfordTown_Gym_Text_KnuckleBadgeInfoTakeThis:
	.string "KNUCKLE BADGE membuat semua POKéMON\n"
	.string "hingga Level 30, bahkan yang kamu\l"
	.string "dapatkan dari pertukaran, patuh tanpa\l"
	.string "tanya.\p"
	.string "Dan, kamu akan bisa menggunakan jurus HM\n"
	.string "FLASH di luar pertarungan.\p"
	.string "Jika mau, gunakan juga TECHNICAL\n"
	.string "MACHINE ini.$"

DewfordTown_Gym_Text_ExplainBulkUp:
	.string "TM08 itu berisi BULK UP.\p"
	.string "Itu adalah jurus yang meningkatkan status\n"
	.string "ATTACK dan DEFENSE.\p"
	.string "… … … … … …$"

DewfordTown_Gym_Text_RegisteredBrawly:
	.string "GYM LEADER BRAWLY terdaftar\n"
	.string "di POKéNAV.$"

DewfordTown_Gym_Text_BrawlyPostBattle:
	.string "Aku bisa melihat bakatmu menjadi gelombang\n"
	.string "raksasa yang akan menimbulkan badai\l"
	.string "kekaguman di antara para TRAINER suatu\l"
	.string "hari nanti!$"

DewfordTown_Gym_Text_GymStatue:
	.string "POKéMON GYM KOTA DEWFORD$"

DewfordTown_Gym_Text_GymStatueCertified:
	.string "POKéMON GYM KOTA DEWFORD\p"
	.string "TRAINER BERSERTIFIKAT BRAWLY:\n"
	.string "{PLAYER}$"

DewfordTown_Gym_Text_BrawlyPreRematch:
	.string "BRAWLY: Ombak mungkin surut, tapi selalu\n"
	.string "kembali ke pantai.\p"
	.string "Bakat sebesar gelombang raksasa sepertimu…\n"
	.string "Aku tahu kamu akan kembali!\p"
	.string "Tunjukkan padaku seberapa jauh lebih hebat\n"
	.string "dirimu sekarang!$"

DewfordTown_Gym_Text_BrawlyRematchDefeat:
	.string "Wow!\n"
	.string "Kalah lagi!$"

DewfordTown_Gym_Text_BrawlyPostRematch:
	.string "BRAWLY: Pertarungan itu luas dan dalam.\n"
	.string "Kamu tidak bisa melihat dasarnya.\l"
	.string "Sama seperti lautan HOENN!$"

DewfordTown_Gym_Text_BrawlyRematchNeedTwoMons:
	.string "BRAWLY: Ombak mungkin surut, tapi selalu\n"
	.string "kembali ke pantai.\p"
	.string "Bakat sebesar gelombang raksasa sepertimu…\n"
	.string "Aku tahu kamu akan kembali!\p"
	.string "Oh? Kamu hanya punya satu POKéMON\n"
	.string "yang bisa bertarung.\p"
	.string "Maaf, tapi aku ingin kamu kembali dengan\n"
	.string "setidaknya dua POKéMON.$"
