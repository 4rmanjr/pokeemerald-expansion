SootopolisCity_Gym_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SootopolisCity_Gym_1F_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, SootopolisCity_Gym_1F_OnResume
	map_script MAP_SCRIPT_ON_LOAD, SootopolisCity_Gym_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, SootopolisCity_Gym_1F_OnTransition
	.byte 0

SootopolisCity_Gym_1F_OnTransition:
	setvar VAR_ICE_STEP_COUNT, 1
	end

SootopolisCity_Gym_1F_OnResume:
	setstepcallback STEP_CB_SOOTOPOLIS_ICE
	end

SootopolisCity_Gym_1F_OnLoad:
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special SetSootopolisGymCrackedIceMetatiles
	end

SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles::
	goto_if_lt VAR_ICE_STEP_COUNT, 8, SootopolisCity_Gym_1F_EventScript_StopCheckingStairs  @ All stairs ice
	goto_if_lt VAR_ICE_STEP_COUNT, 28, SootopolisCity_Gym_1F_EventScript_OpenFirstStairs
	goto_if_lt VAR_ICE_STEP_COUNT, 67, SootopolisCity_Gym_1F_EventScript_OpenFirstAndSecondStairs
	setmetatile 8, 4, METATILE_SootopolisGym_Stairs, FALSE
	setmetatile 8, 5, METATILE_SootopolisGym_Stairs, FALSE
SootopolisCity_Gym_1F_EventScript_OpenFirstAndSecondStairs::
	setmetatile 8, 10, METATILE_SootopolisGym_Stairs, FALSE
	setmetatile 8, 11, METATILE_SootopolisGym_Stairs, FALSE
SootopolisCity_Gym_1F_EventScript_OpenFirstStairs::
	setmetatile 8, 15, METATILE_SootopolisGym_Stairs, FALSE
	setmetatile 8, 16, METATILE_SootopolisGym_Stairs, FALSE
SootopolisCity_Gym_1F_EventScript_StopCheckingStairs::
	return

SootopolisCity_Gym_1F_OnFrame:
	map_script_2 VAR_ICE_STEP_COUNT, 8, SootopolisCity_Gym_1F_EventScript_UnlockFirstStairs
	map_script_2 VAR_ICE_STEP_COUNT, 28, SootopolisCity_Gym_1F_EventScript_UnlockSecondStairs
	map_script_2 VAR_ICE_STEP_COUNT, 67, SootopolisCity_Gym_1F_EventScript_UnlockThirdStairs
	map_script_2 VAR_ICE_STEP_COUNT, 0, SootopolisCity_Gym_1F_EventScript_FallThroughIce
	.2byte 0

SootopolisCity_Gym_1F_EventScript_UnlockFirstStairs::
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_UnlockSecondStairs::
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_UnlockThirdStairs::
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_FallThroughIce::
	lockall
	delay 20
	applymovement LOCALID_PLAYER, SootopolisCity_Gym_1F_Movement_FallThroughIce
	waitmovement 0
	playse SE_FALL
	delay 60
	warphole MAP_SOOTOPOLIS_CITY_GYM_B1F
	waitstate
	end

SootopolisCity_Gym_1F_Movement_FallThroughIce:
	set_invisible
	step_end

SootopolisCity_Gym_1F_EventScript_Juan::
	trainerbattle_single TRAINER_JUAN_1, SootopolisCity_Gym_1F_Text_JuanIntro, SootopolisCity_Gym_1F_Text_JuanDefeat, SootopolisCity_Gym_1F_EventScript_JuanDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, SootopolisCity_Gym_1F_EventScript_JuanRematch
	goto_if_unset FLAG_RECEIVED_TM_WATER_PULSE, SootopolisCity_Gym_1F_EventScript_GiveWaterPulse2
	goto_if_unset FLAG_BADGE06_GET, SootopolisCity_Gym_1F_EventScript_GoGetFortreeBadge
	msgbox SootopolisCity_Gym_1F_Text_JuanPostBattle, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_JuanDefeated::
	message SootopolisCity_Gym_1F_Text_ReceivedRainBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox SootopolisCity_Gym_1F_Text_ExplainRainBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_SOOTOPOLIS_GYM
	setflag FLAG_BADGE08_GET
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_RESIDENTS
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_STEVEN
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_WALLACE
	setvar VAR_SOOTOPOLIS_CITY_STATE, 6
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_MAN_1
	setvar VAR_0x8008, 8
	call Common_EventScript_SetGymTrainers
	call SootopolisCity_Gym_1F_EventScript_GiveWaterPulse
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox SootopolisCity_Gym_1F_Text_RegisteredJuan, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_JUAN_MATCH_CALL
	release
	end

SootopolisCity_Gym_1F_EventScript_GiveWaterPulse::
	giveitem ITEM_TM_WATER_PULSE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox SootopolisCity_Gym_1F_Text_ExplainWaterPulse, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_WATER_PULSE
	return

SootopolisCity_Gym_1F_EventScript_GiveWaterPulse2::
	giveitem ITEM_TM_WATER_PULSE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox SootopolisCity_Gym_1F_Text_ExplainWaterPulse, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_WATER_PULSE
	release
	end

SootopolisCity_Gym_1F_EventScript_GoGetFortreeBadge::
	msgbox SootopolisCity_Gym_1F_Text_GoGetFortreeBadge, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_JuanRematch::
	trainerbattle_rematch_double TRAINER_JUAN_1, SootopolisCity_Gym_1F_Text_JuanPreRematch, SootopolisCity_Gym_1F_Text_JuanRematchDefeat, SootopolisCity_Gym_1F_Text_JuanRematchNeedTwoMons
	msgbox SootopolisCity_Gym_1F_Text_JuanPostRematch, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_1F_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SOOTOPOLIS_GYM, SootopolisCity_Gym_1F_EventScript_GymGuidePostVictory
	msgbox SootopolisCity_Gym_1F_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_GymGuidePostVictory::
	msgbox SootopolisCity_Gym_1F_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE08_GET, SootopolisCity_Gym_1F_EventScript_GymStatueCertified
	goto SootopolisCity_Gym_1F_EventScript_GymStatue
	end

SootopolisCity_Gym_1F_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE08_GET, SootopolisCity_Gym_1F_EventScript_GymStatueCertified
	goto SootopolisCity_Gym_1F_EventScript_GymStatue
	end

SootopolisCity_Gym_1F_EventScript_GymStatueCertified::
	msgbox SootopolisCity_Gym_1F_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_Gym_1F_EventScript_GymStatue::
	msgbox SootopolisCity_Gym_1F_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_Gym_1F_Text_GymGuideAdvice:
	.string "Yo! Bagaimana kabarmu, {PLAYER} calon\n"
	.string "CHAMPION?\p"
	.string "PEMIMPIN GYM SOOTOPOLIS, JUAN, adalah\n"
	.string "master POKéMON tipe AIR.\p"
	.string "Dan, untuk mencapai JUAN, lantai es\n"
	.string "akan menghambat kemajuanmu…\p"
	.string "Dengar, maaf, tapi itu saja nasihat\n"
	.string "yang aku punya untukmu.\p"
	.string "Sisa perjalanan, kamu harus\n"
	.string "melakukannya sendiri!$"

SootopolisCity_Gym_1F_Text_GymGuidePostVictory:
	.string "Yow! Kamu bahkan telah mengalahkan JUAN,\n"
	.string "yang konon terbaik di seluruh HOENN!\p"
	.string "Oke! Periksa KARTU TRAINER-mu.\p"
	.string "Jika kamu sudah mendapatkan semua BADGE,\n"
	.string "kamu siap untuk tantangan POKéMON LEAGUE!$"

SootopolisCity_Gym_1F_Text_JuanIntro:
	.string "Izinkan aku bertanya padamu.\n"
	.string "Apakah kamu tahu?\l"
	.string "Ah, aku tidak boleh malu-malu begitu.\p"
	.string "Akulah yang mengajari WALLACE segala\n"
	.string "sesuatu tentang POKéMON.\p"
	.string "Dulu, aku telah menyerahkan posisiku\n"
	.string "sebagai PEMIMPIN GYM.\p"
	.string "Sebagai gantinya, aku mempercayakan\n"
	.string "GYM ini kepada WALLACE.\p"
	.string "Namun, ada alasan kuat yang muncul\n"
	.string "bagiku untuk kembali.\p"
	.string "Ah, tapi cukup bicara.\n"
	.string "Mari kita mulai pertandingan kita, ya?\p"
	.string "Tolong, kamu akan menjadi saksi\n"
	.string "seni kami.\p"
	.string "Ilusi air yang megah yang diukir\n"
	.string "oleh POKéMON dan diriku sendiri!$"

@ NOTE: This defeat text actually causes a buffer overflow. It's about 50 bytes too long for
@ the gDisplayedStringBattle buffer that it's put into, and it stomps all over the gBattleTextBuffs
@ after, as well as the otherwise unused array after that. One wonders if that's the reason for
@ the existence of that unused array of ints.
SootopolisCity_Gym_1F_Text_JuanDefeat:
	.string "Ahahaha, luar biasa!\n"
	.string "Baiklah, kamu adalah pemenangnya.\p"
	.string "Darimu, aku merasakan kilauan cemerlang\n"
	.string "keterampilan yang akan mengatasi segalanya.\p"
	.string "Namun, dibandingkan dengan aku atau\n"
	.string "bahkan WALLACE, kamu kurang elegan.\p"
	.string "Mungkin aku harus meminjamkanmu\n"
	.string "pakaianku?\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "Hahaha, aku hanya bercanda!\p"
	.string "Daripada pakaianku, aku akan\n"
	.string "memberimu ini, RAIN BADGE!$"

SootopolisCity_Gym_1F_Text_ReceivedRainBadge:
	.string "{PLAYER} mendapatkan RAIN BADGE\n"
	.string "dari JUAN.$"

SootopolisCity_Gym_1F_Text_ExplainRainBadgeTakeThis:
	.string "Memiliki RAIN BADGE akan menjamin\n"
	.string "ketaatan penuh semua POKéMON-mu\l"
	.string "terhadap setiap perintahmu.\p"
	.string "RAIN BADGE juga memungkinkan penggunaan\n"
	.string "gerakan HM WATERFALL untuk mendaki\l"
	.string "dinding air terjun yang mengalir deras.\p"
	.string "Dan, agar kamu tidak pernah melupakan\n"
	.string "pertarungan yang kita alami, ambillah ini…$"

SootopolisCity_Gym_1F_Text_ExplainWaterPulse:
	.string "TECHNICAL MACHINE yang aku berikan padamu\n"
	.string "berisi WATER PULSE.\p"
	.string "Saat digunakan, ia sesekali akan membingungkan\n"
	.string "target dengan gelombang ultrasonik.\p"
	.string "… … … … … …$"

SootopolisCity_Gym_1F_Text_RegisteredJuan:
	.string "Mendaftarkan PEMIMPIN GYM JUAN\n"
	.string "di POKéNAV.$"

SootopolisCity_Gym_1F_Text_JuanPostBattle:
	.string "PARA TRAINER yang telah mengumpulkan\n"
	.string "semua BADGE GYM di HOENN harus\l"
	.string "menuju ke tujuan akhir.\p"
	.string "POKéMON LEAGUE.\p"
	.string "Pergilah ke ujung timur\n"
	.string "HOENN, ke pulau EVER GRANDE.\p"
	.string "Di sana, kamu akan menemukan POKéMON\n"
	.string "LEAGUE.$"

SootopolisCity_Gym_1F_Text_GoGetFortreeBadge:
	.string "Tinggal satu BADGE lagi yang harus\n"
	.string "didapatkan di HOENN.\p"
	.string "Jika kamu ingin menantang POKéMON\n"
	.string "LEAGUE, kamu harus mendapatkan BADGE\l"
	.string "terakhir dari GYM di FORTREE.$"

SootopolisCity_Gym_1F_Text_GymStatue:
	.string "POKéMON GYM KOTA SOOTOPOLIS$"

SootopolisCity_Gym_1F_Text_GymStatueCertified:
	.string "POKéMON GYM KOTA SOOTOPOLIS\p"
	.string "TRAINER BERSERTIFIKAT JUAN:\n"
	.string "{PLAYER}$"

SootopolisCity_Gym_1F_Text_JuanPreRematch:
	.string "JUAN: Ah, GYM ini telah kembali ke\n"
	.string "keadaan tenang seperti biasa…\p"
	.string "Tapi topan muda kita telah kembali\n"
	.string "untuk menguji kita lagi!\p"
	.string "Tentu saja, temanku!\p"
	.string "Aku akan senang menari bersamamu\n"
	.string "sesering yang kamu inginkan!$"

SootopolisCity_Gym_1F_Text_JuanRematchDefeat:
	.string "Ahahaha, kamu pemenangnya!\n"
	.string "Kamu telah mengalahkanku lagi!$"

SootopolisCity_Gym_1F_Text_JuanPostRematch:
	.string "JUAN: Jika aku memintamu menjadi\n"
	.string "muridku, kamu pasti akan menolak, aku yakin.\p"
	.string "Aku ingin memberikan hadiah berupa jas\n"
	.string "milikku kepadamu.\p"
	.string "Tapi lagi-lagi, kamu akan menolak.\n"
	.string "Aku membayangkan begitu.\p"
	.string "Dan itu, temanku, adalah tanda pasti\n"
	.string "dari kemuliaan!$"

SootopolisCity_Gym_1F_Text_JuanRematchNeedTwoMons:
	.string "JUAN: Ah, GYM ini telah kembali ke\n"
	.string "keadaan tenang seperti biasa…\p"
	.string "Tapi topan muda kita telah kembali\n"
	.string "untuk menguji kita lagi!\p"
	.string "Tentu saja, temanku!\n"
	.string "Aku akan senang menari bersamamu…\p"
	.string "Ah, tidak, tidak, tidak.\n"
	.string "Kamu hanya punya satu POKéMON.\p"
	.string "Aku harap kamu akan kembali dengan\n"
	.string "dua, atau mungkin lebih, POKéMON, tolong.$"

