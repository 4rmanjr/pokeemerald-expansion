MauvilleCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MauvilleCity_OnTransition
	.byte 0

MauvilleCity_OnTransition:
	setflag FLAG_VISITED_MAUVILLE_CITY
	clearflag FLAG_FORCE_MIRAGE_TOWER_VISIBLE
	clearflag FLAG_HIDE_SLATEPORT_MUSEUM_POPULATION
	setflag FLAG_SYS_TV_START
	clearflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	setvar VAR_MAUVILLE_GYM_STATE, 0
	call_if_set FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON, MauvilleCity_EventScript_MoveWattsonBackToGym
	end

MauvilleCity_EventScript_MoveWattsonBackToGym::
	clearflag FLAG_HIDE_MAUVILLE_GYM_WATTSON
	setflag FLAG_HIDE_MAUVILLE_CITY_WATTSON
	setflag FLAG_WATTSON_REMATCH_AVAILABLE
	return

MauvilleCity_EventScript_Boy::
	msgbox MauvilleCity_Text_NurseHurtMonBackToHealth, MSGBOX_NPC
	end

MauvilleCity_EventScript_Maniac::
	msgbox MauvilleCity_Text_AllSortsOfPeopleComeThrough, MSGBOX_NPC
	end

MauvilleCity_EventScript_Woman::
	msgbox MauvilleCity_Text_RydelVeryGenerous, MSGBOX_NPC
	end

MauvilleCity_EventScript_RichBoy::
	msgbox MauvilleCity_Text_PokemonCanJumpYouOnBike, MSGBOX_NPC
	end

MauvilleCity_EventScript_CitySign::
	msgbox MauvilleCity_Text_CitySign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GymSign::
	msgbox MauvilleCity_Text_GymSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_BikeShopSign::
	msgbox MauvilleCity_Text_BikeShopSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GameCornerSign::
	msgbox MauvilleCity_Text_GameCornerSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_SchoolKidM::
	lock
	faceplayer
	goto_if_set FLAG_TV_EXPLAINED, MauvilleCity_EventScript_TVExplained
	msgbox MauvilleCity_Text_ExplainTV, MSGBOX_DEFAULT
	setflag FLAG_TV_EXPLAINED
	release
	end

MauvilleCity_EventScript_TVExplained::
	msgbox MauvilleCity_Text_BeenCheckingOutTV, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_UncleAskPlayerToBattleWally
	msgbox MauvilleCity_Text_UncleHesTooPeppy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_UncleAskPlayerToBattleWally::
	msgbox MauvilleCity_Text_UncleCanYouBattleWally, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_Wally::
	lockall
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_WallyRequestBattleAgain
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWantToChallengeGym, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_UncleYourePushingIt, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_WallyWeCanBeatAnyone, MSGBOX_DEFAULT
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_Delay48
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWillYouBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_EventScript_BattleWallyPrompt::
	call_if_eq VAR_RESULT, YES, MauvilleCity_EventScript_BattleWally
	goto_if_eq VAR_RESULT, NO, MauvilleCity_EventScript_DeclineWallyBattle
	closemessage
	switch VAR_FACING
	case DIR_NORTH, MauvilleCity_EventScript_WallyAndUncleExitNorth
	case DIR_EAST, MauvilleCity_EventScript_WallyAndUncleExitEast
	end

MauvilleCity_EventScript_WallyAndUncleExitNorth::
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth1
	applymovement LOCALID_MAUVILLE_WALLY, MauvilleCity_Movement_WallyExitNorth1
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitNorth1
	waitmovement 0
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerFaceUncleNorth
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleApproachPlayerNorth
	waitmovement 0
	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth2
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitNorth2
	applymovement LOCALID_MAUVILLE_WALLY, MauvilleCity_Movement_WallyExitNorth2
	waitmovement 0
	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_WallyAndUncleExitEast::
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast1
	applymovement LOCALID_MAUVILLE_WALLY, MauvilleCity_Movement_WallyExitEast1
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitEast1
	waitmovement 0
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleApproachPlayerEast
	waitmovement 0
	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast2
	applymovement LOCALID_MAUVILLE_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitEast2
	applymovement LOCALID_MAUVILLE_WALLY, MauvilleCity_Movement_WallyExitEast2
	waitmovement 0
	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_DefeatedWally::
	removeobject LOCALID_MAUVILLE_WALLY
	removeobject LOCALID_MAUVILLE_WALLYS_UNCLE
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLYS_UNCLE
	setflag FLAG_DEFEATED_WALLY_MAUVILLE
	setvar VAR_WALLY_CALL_STEP_COUNTER, 0
	setflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	call_if_eq VAR_FACING, DIR_NORTH, MauvilleCity_EventScript_ScottApproachPlayerNorth
	call_if_eq VAR_FACING, DIR_EAST, MauvilleCity_EventScript_ScottApproachPlayerEast
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox MauvilleCity_Text_ScottYouDidntHoldBack, MSGBOX_DEFAULT
	closemessage
	addvar VAR_SCOTT_STATE, 1
	call_if_eq VAR_FACING, DIR_NORTH, MauvilleCity_EventScript_ScottExitNorth
	call_if_eq VAR_FACING, DIR_EAST, MauvilleCity_EventScript_ScottExitEast
	removeobject LOCALID_MAUVILLE_SCOTT
	releaseall
	end

MauvilleCity_EventScript_ScottApproachPlayerNorth::
	addobject LOCALID_MAUVILLE_SCOTT
	applymovement LOCALID_MAUVILLE_SCOTT, MauvilleCity_Movement_ScottApproachPlayerNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottApproachPlayerEast::
	setobjectxyperm LOCALID_MAUVILLE_SCOTT, 12, 13
	addobject LOCALID_MAUVILLE_SCOTT
	applymovement LOCALID_MAUVILLE_SCOTT, MauvilleCity_Movement_ScottApproachPlayerEast
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitNorth::
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitNorth
	applymovement LOCALID_MAUVILLE_SCOTT, MauvilleCity_Movement_ScottExitNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitEast::
	applymovement LOCALID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitEast
	applymovement LOCALID_MAUVILLE_SCOTT, MauvilleCity_Movement_ScottExitEast
	waitmovement 0
	return

MauvilleCity_EventScript_BattleWally::
	msgbox MauvilleCity_Text_WallyHereICome, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_MAUVILLE, MauvilleCity_Text_WallyDefeat
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyIllGoBackToVerdanturf, MSGBOX_DEFAULT
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_ThankYouNotEnoughToBattle, MSGBOX_DEFAULT
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_UncleNoNeedToBeDown, MSGBOX_DEFAULT
	return

MauvilleCity_EventScript_DeclineWallyBattle::
	setflag FLAG_DECLINED_WALLY_BATTLE_MAUVILLE
	msgbox MauvilleCity_Text_WallyMyUncleWontKnowImStrong, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallyRequestBattleAgain::
	applymovement LOCALID_MAUVILLE_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_WallyPleaseBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_Movement_WallyExitNorth1:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	step_end

MauvilleCity_Movement_WallyExitEast1:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallyExitNorth2:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_WallyExitEast2:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth2:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast2:
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitNorth:
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitEast:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast1:
	delay_16
	walk_in_place_faster_down
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth1:
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_WallysUncleExitNorth1:
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

MauvilleCity_Movement_WallysUncleExitEast1:
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_PlayerFaceUncleNorth:
	delay_16
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerNorth:
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerEast:
	walk_right
	walk_up
	step_end

MauvilleCity_Movement_WallysUncleExitNorth2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallysUncleExitEast2:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_ScottApproachPlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

MauvilleCity_Movement_ScottApproachPlayerEast:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

MauvilleCity_Movement_ScottExitNorth:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_ScottExitEast:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_EventScript_Wattson::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON, MauvilleCity_EventScript_ReceivedThunderbolt
	goto_if_eq VAR_NEW_MAUVILLE_STATE, 2, MauvilleCity_EventScript_CompletedNewMauville
	goto_if_set FLAG_GOT_BASEMENT_KEY_FROM_WATTSON, MauvilleCity_EventScript_BegunNewMauville
	msgbox MauvilleCity_Text_WattsonNeedFavorTakeKey, MSGBOX_DEFAULT
	giveitem ITEM_BASEMENT_KEY
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_BASEMENT_KEY_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_BegunNewMauville::
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_CompletedNewMauville::
	msgbox MauvilleCity_Text_WattsonThanksTakeTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_THUNDERBOLT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_TM_THUNDERBOLT_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_ReceivedThunderbolt::
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_RegisterWallyCall::
	lockall
	pokenavcall MauvilleCity_Text_WallyPokenavCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MauvilleCity_Text_RegisteredWally, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WALLY_MATCH_CALL
	clearflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	releaseall
	end

MauvilleCity_Text_UncleHesTooPeppy:
	.string "PAMAN: Gara-gara POKéMON anak ini jadi\n"
	.string "lebih bersemangat, kurasa…\l"
	.string "Tapi dia jadi terlalu bersemangat…$"

MauvilleCity_Text_WallyWantToChallengeGym:
	.string "WALLY: Ayolah, PAMAN, kumohon?\p"
	.string "Aku ingin menantang GYM ini dan melihat\n"
	.string "seberapa hebat aku sekarang.\p"
	.string "Kumohon? Boleh ya, kumohon?$"

MauvilleCity_Text_UncleYourePushingIt:
	.string "PAMAN: Tunggu dulu, WALLY.\p"
	.string "Sejak kamu mulai hidup dengan POKéMON,\n"
	.string "kamu memang jadi jauh lebih kuat.\p"
	.string "Tapi apa kamu tidak merasa memaksakan\n"
	.string "diri dengan tiba-tiba menantang GYM?$"

MauvilleCity_Text_WallyWeCanBeatAnyone:
	.string "WALLY: Aku tidak memaksakan diri.\p"
	.string "Jika aku dan RALTS bekerja sama,\n"
	.string "kami bisa mengalahkan siapa saja!$"

MauvilleCity_Text_WallyWillYouBattleMe:
	.string "WALLY: Oh! Hai, {PLAYER}!\p"
	.string "Aku sudah jauh lebih kuat sejak kita\n"
	.string "terakhir bertemu.\p"
	.string "{PLAYER}, aku ingin kamu dan PAMAN-ku\n"
	.string "mengerti itu.\p"
	.string "{PLAYER}, kumohon, maukah kamu\n"
	.string "bertarung denganku?$"

MauvilleCity_Text_WallyMyUncleWontKnowImStrong:
	.string "WALLY: Oh… Kalau kamu tidak mau\n"
	.string "bertarung, {PLAYER}, PAMAN-ku tidak akan\l"
	.string "tahu kalau aku sudah jadi sangat kuat.$"

MauvilleCity_Text_UncleCanYouBattleWally:
	.string "PAMAN: {PLAYER}{KUN}, kan?\n"
	.string "Atas nama WALLY, bisakah aku memintamu\l"
	.string "bertarung dengannya sekali saja?\p"
	.string "Kurasa dia tidak akan mau mendengarkan\n"
	.string "alasan apa pun sekarang.$"

MauvilleCity_Text_WallyPleaseBattleMe:
	.string "WALLY: {PLAYER}, kumohon!\n"
	.string "Bertarunglah denganku, kumohon.$"

MauvilleCity_Text_WallyHereICome:
	.string "WALLY: {PLAYER}, terima kasih.\p"
	.string "Oke… Aku datang!$"

MauvilleCity_Text_WallyDefeat:
	.string "WALLY: … … … … … … …\p"
	.string "… … … … … … … …\p"
	.string "Aku kalah…$"

MauvilleCity_Text_WallyIllGoBackToVerdanturf:
	.string "WALLY: PAMAN…\n"
	.string "Aku akan kembali ke VERDANTURF…$"

MauvilleCity_Text_ThankYouNotEnoughToBattle:
	.string "{PLAYER}, terima kasih.\n"
	.string "Menjadi TRAINER itu sulit, ya?\p"
	.string "Tidak cukup hanya punya POKéMON dan\n"
	.string "membuat mereka bertarung. Bukan itu\l"
	.string "inti menjadi TRAINER sejati.$"

MauvilleCity_Text_UncleNoNeedToBeDown:
	.string "PAMAN: WALLY, tidak perlu begitu\n"
	.string "bersedih.\p"
	.string "Kenapa, apa yang menghalangimu untuk\n"
	.string "menjadi lebih kuat dan lebih kuat lagi?\p"
	.string "Ayo, kita pulang.\n"
	.string "Semua orang menunggumu.$"

MauvilleCity_Text_UncleVisitUsSometime:
	.string "PAMAN: {PLAYER}{KUN}, aku baru sadar\n"
	.string "kamu pasti TRAINER yang mengawasi\l"
	.string "WALLY saat dia menangkap POKéMON-nya.\p"
	.string "Kenapa kamu tidak mengunjungi kami di\n"
	.string "VERDANTURF kapan-kapan?\l"
	.string "Aku yakin WALLY akan senang.$"


MauvilleCity_Text_WallyPokenavCall:
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "WALLY: Oh, halo, {PLAYER}!\p"
	.string "Aku hanya ingin memberitahumu bahwa\n"
	.string "pamanku membelikanku POKéNAV!\p"
	.string "Sekarang aku bisa menghubungimu\n"
	.string "kapan saja, {PLAYER}!\p"
	.string "… … … … … …\n"
	.string "… … … … … Klik!$"

MauvilleCity_Text_RegisteredWally:
	.string "Mendaftarkan WALLY\n"
	.string "di POKéNAV.$"

MauvilleCity_Text_ScottYouDidntHoldBack:
	.string "SCOTT: Hehe…\n"
	.string "Aku menonton pertandingan itu!\p"
	.string "Kamu berteman dengan anak laki-laki itu,\n"
	.string "WALLY, kan?\p"
	.string "Tapi kamu tidak menahan diri dan\n"
	.string "mengalahkannya dengan mengesankan.\p"
	.string "Yeah! Itulah inti dari pertarungan\n"
	.string "POKéMON yang sesungguhnya!\p"
	.string "Aku mengidolakan TRAINER seperti itu!\p"
	.string "… … … … … …\n"
	.string "Aku akan mendukungmu!$"

MauvilleCity_Text_WattsonNeedFavorTakeKey:
	.string "WATTSON: Oh, {PLAYER}{KUN}!\n"
	.string "Kamu terlihat sangat bersemangat!\l"
	.string "Itu hal yang bagus, wahahahaha!\p"
	.string "Baik! Sudah kuputuskan!\n"
	.string "Aku butuh bantuanmu, {PLAYER}{KUN}!\p"
	.string "MAUVILLE CITY punya sektor bawah tanah\n"
	.string "bernama NEW MAUVILLE.\p"
	.string "{PLAYER}{KUN}, aku ingin kamu ke sana dan\n"
	.string "mematikan GENERATOR.\p"
	.string "GENERATOR-nya agak rusak. Jadi tidak\n"
	.string "aman.\p"
	.string "Ini, ini KUNCI untuk masuk ke\n"
	.string "NEW MAUVILLE.$"

MauvilleCity_Text_WattsonWontBeChallenge:
	.string "WATTSON: Jangan khawatir.\n"
	.string "Itu bukan tantangan bagimu.\p"
	.string "Pintu masuk ke NEW MAUVILLE hanya perlu\n"
	.string "SURF sebentar dari ROUTE 110.\p"
	.string "Kalau begitu, aku percaya padamu!\n"
	.string "Wahahahaha!$"

MauvilleCity_Text_WattsonThanksTakeTM:
	.string "WATTSON: Wahahahaha!\p"
	.string "Sudah kuduga, {PLAYER}{KUN}! Aku tahu aku\n"
	.string "membuat pilihan yang tepat dengan\l"
	.string "memintamu!\p"
	.string "Ini ucapan terima kasihku--sebuah TM\n"
	.string "berisi THUNDERBOLT!\p"
	.string "Ayo, kamu pantas mendapatkannya!$"

MauvilleCity_Text_WattsonYoungTakeCharge:
	.string "WATTSON: Wahahahaha!\p"
	.string "Aku sangat senang melihat anak muda\n"
	.string "mengambil alih!$"

MauvilleCity_Text_NurseHurtMonBackToHealth:
	.string "Tahu tidak, pertarungan POKéMON dan\n"
	.string "sejenisnya itu keren…\p"
	.string "Tapi jika POKéMON-mu terluka, kamu harus\n"
	.string "merawatnya sampai sembuh.$"

MauvilleCity_Text_AllSortsOfPeopleComeThrough:
	.string "Jalanan di kota ini membentang ke utara\n"
	.string "dan selatan, serta timur dan barat.\p"
	.string "Karena itu, banyak sekali orang yang\n"
	.string "datang kemari.$"

MauvilleCity_Text_RydelVeryGenerous:
	.string "Sudah ke RYDEL'S CYCLES?\p"
	.string "RYDEL, pemiliknya, adalah pria yang\n"
	.string "sangat dermawan.$"

MauvilleCity_Text_PokemonCanJumpYouOnBike:
	.string "Bahkan jika kamu mengendarai SEPEDA,\n"
	.string "POKéMON liar bisa saja menyerangmu.$"

MauvilleCity_Text_CitySign:
	.string "MAUVILLE CITY\n"
	.string "“Kota ceria yang terang benderang!”$"

MauvilleCity_Text_GymSign:
	.string "MAUVILLE CITY POKéMON GYM\n"
	.string "LEADER: WATTSON\l"
	.string "“Pria ceria yang menggetarkan!”$"

MauvilleCity_Text_BikeShopSign:
	.string "“Berkendara di kerikil dan guncangkan\n"
	.string "jiwamu!”\l"
	.string "RYDEL'S CYCLES$"

MauvilleCity_Text_GameCornerSign:
	.string "“Tempat bermain untuk semua!”\n"
	.string "MAUVILLE GAME CORNER$"

MauvilleCity_Text_ExplainTV:
	.string "Hai, apa kamu suka nonton TV?\p"
	.string "Baru-baru ini ada banyak acara baru\n"
	.string "yang keren.\p"
	.string "TV itu keren. Aku pernah melihat\n"
	.string "teman-temanku di TV tiba-tiba.\p"
	.string "Dan, terkadang, mereka bahkan\n"
	.string "menayangkanmu di TV tanpa memberitahu.\p"
	.string "Aku harap suatu saat bisa masuk TV.\p"
	.string "Itulah kenapa kamu harus memeriksa TV\n"
	.string "kapan pun kamu bisa.$"

MauvilleCity_Text_BeenCheckingOutTV:
	.string "Hai, apa kamu sudah memeriksa TV?$"
