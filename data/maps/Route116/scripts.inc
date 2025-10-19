Route116_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route116_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route116_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route116_OnFrame
	.byte 0

Route116_OnTransition:
	call_if_set FLAG_RECOVERED_DEVON_GOODS, Route116_EventScript_SetWandasBoyfriendPos
	call_if_eq VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_HideMapNamePopup
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_116_NORTH, AbnormalWeather_StartGroudonWeather
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_116_SOUTH, AbnormalWeather_StartGroudonWeather
	end

Route116_EventScript_SetWandasBoyfriendPos::
	setobjectxyperm LOCALID_ROUTE116_WANDAS_BF, 38, 10
	return

Route116_OnLoad:
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_116_NORTH, AbnormalWeather_EventScript_PlaceTilesRoute116North
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_116_SOUTH, AbnormalWeather_EventScript_PlaceTilesRoute116South
	end

Route116_OnFrame:
	map_script_2 VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_EndEventAndCleanup_1
	.2byte 0

Route116_EventScript_WandasBoyfriend::
	lock
	faceplayer
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, Route116_EventScript_BoyfriendGruntLeftTunnel
	goto_if_set FLAG_DEVON_GOODS_STOLEN, Route116_EventScript_BoyfriendGruntInTunnel
	msgbox Route116_Text_WantToDigTunnel, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_BoyfriendGruntLeftTunnel::
	msgbox Route116_Text_GoonHightailedItOutOfTunnel, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_BoyfriendGruntInTunnel::
	msgbox Route116_Text_DiggingTunnelWhenGoonOrderedMeOut, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_DevonEmployee::
	lock
	faceplayer
	goto_if_set FLAG_MET_DEVON_EMPLOYEE, Route116_EventScript_TryGiveRepeatBallAgain
	msgbox Route116_Text_ThankYouTokenOfAppreciation, MSGBOX_DEFAULT
	goto Route116_EventScript_GiveRepeatBall
	end

Route116_EventScript_GiveRepeatBall::
	setflag FLAG_MET_DEVON_EMPLOYEE
	giveitem ITEM_REPEAT_BALL
	goto_if_eq VAR_RESULT, FALSE, Route116_EventScript_NoRoomForRepeatBall
	msgbox Route116_Text_NewBallAvailableAtMart, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, Route116_EventScript_DevonEmployeeExit
	call_if_eq VAR_FACING, DIR_SOUTH, Route116_EventScript_DevonEmployeeExit
	call_if_eq VAR_FACING, DIR_WEST, Route116_EventScript_DevonEmployeeExit
	call_if_eq VAR_FACING, DIR_EAST, Route116_EventScript_DevonEmployeeExitEast
	removeobject VAR_LAST_TALKED
	clearflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_EMPLOYEE
	setflag FLAG_RECEIVED_REPEAT_BALL
	release
	end

Route116_EventScript_DevonEmployeeExit::
	applymovement VAR_LAST_TALKED, Route116_Movement_DevonEmployeeExit
	waitmovement 0
	return

Route116_EventScript_DevonEmployeeExitEast::
	applymovement VAR_LAST_TALKED, Route116_Movement_DevonEmployeeExitEast
	waitmovement 0
	return

Route116_EventScript_TryGiveRepeatBallAgain::
	msgbox Route116_Text_TokenOfAppreciation, MSGBOX_DEFAULT
	goto Route116_EventScript_GiveRepeatBall
	end

Route116_EventScript_NoRoomForRepeatBall::
	msgbox Route116_Text_BagIsJamPacked, MSGBOX_DEFAULT
	release
	end

Route116_Movement_DevonEmployeeExit:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route116_Movement_DevonEmployeeExitEast:
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

Route116_EventScript_RouteSignRustboro::
	msgbox Route116_Text_RouteSignRustboro, MSGBOX_SIGN
	end

Route116_EventScript_RusturfTunnelSign::
	msgbox Route116_Text_RusturfTunnelSign, MSGBOX_SIGN
	end

Route116_EventScript_TunnelersRestHouseSign::
	msgbox Route116_Text_TunnelersRestHouse, MSGBOX_SIGN
	end

Route116_EventScript_TrainerTipsBToStopEvolution::
	msgbox Route116_Text_TrainerTipsBToStopEvolution, MSGBOX_SIGN
	end

Route116_EventScript_TrainerTipsBagHasPockets::
	msgbox Route116_Text_TrainerTipsBagHasPockets, MSGBOX_SIGN
	end

Route116_EventScript_Briney::
	lock
	faceplayer
	msgbox Route116_Text_ScoundrelMadeOffWithPeeko, MSGBOX_DEFAULT
	setvar VAR_ROUTE116_STATE, 2
	release
	end

Route116_EventScript_BrineyTrigger::
	lockall
	applymovement LOCALID_ROUTE116_BRINEY, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox Route116_Text_ScoundrelMadeOffWithPeeko, MSGBOX_DEFAULT
	setvar VAR_ROUTE116_STATE, 2
	releaseall
	end

Route116_EventScript_GlassesMan::
	lock
	faceplayer
	checkitem ITEM_BLACK_GLASSES
	goto_if_eq VAR_RESULT, TRUE, Route116_EventScript_PlayerHasGlasses
	specialvar VAR_RESULT, FoundBlackGlasses
	goto_if_eq VAR_RESULT, TRUE, Route116_EventScript_FoundGlassesNotOnPlayer
	msgbox Route116_Text_CanYouHelpMeFindGlasses, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_FoundGlassesNotOnPlayer::
	msgbox Route116_Text_CantFindGlassesNotHere, MSGBOX_DEFAULT
	closemessage
	goto Route116_EventScript_GlassesManExit
	end

Route116_EventScript_PlayerHasGlasses::
	msgbox Route116_Text_CanYouHelpMeFindGlasses, MSGBOX_DEFAULT
	msgbox Route116_Text_MayISeeThoseGlasses, MSGBOX_DEFAULT
	specialvar VAR_RESULT, FoundBlackGlasses
	goto_if_eq VAR_RESULT, TRUE, Route116_EventScript_FoundGlassesOnPlayer
	msgbox Route116_Text_NotWhatImLookingFor, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_FoundGlassesOnPlayer::
	msgbox Route116_Text_NotWhatImLookingForMaybeTheyArentHere, MSGBOX_DEFAULT
	closemessage
	goto Route116_EventScript_GlassesManExit
	end

Route116_EventScript_GlassesManExit::
	delay 20
	call_if_eq VAR_FACING, DIR_NORTH, Route116_EventScript_GlassesManExitNormal
	call_if_eq VAR_FACING, DIR_SOUTH, Route116_EventScript_GlassesManExitNormal
	call_if_eq VAR_FACING, DIR_WEST, Route116_EventScript_GlassesManExitNormal
	call_if_eq VAR_FACING, DIR_EAST, Route116_EventScript_GlassesManExitEast
	removeobject VAR_LAST_TALKED
	release
	end

Route116_EventScript_GlassesManExitNormal::
	applymovement VAR_LAST_TALKED, Route116_Movement_GlassesManExit
	waitmovement 0
	return

Route116_EventScript_GlassesManExitEast::
	applymovement VAR_LAST_TALKED, Route116_Movement_GlassesManExitEast
	waitmovement 0
	return

Route116_Movement_GlassesManExit:
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

Route116_Movement_GlassesManExitEast:
	walk_up
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

Route116_EventScript_Joey::
	trainerbattle_single TRAINER_JOEY, Route116_Text_JoeyIntro, Route116_Text_JoeyDefeat
	msgbox Route116_Text_JoeyPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Jose::
	trainerbattle_single TRAINER_JOSE, Route116_Text_JoseIntro, Route116_Text_JoseDefeat
	msgbox Route116_Text_JosePostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Jerry::
	trainerbattle_single TRAINER_JERRY_1, Route116_Text_JerryIntro, Route116_Text_JerryDefeat, Route116_EventScript_TryRegisterJerryAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route116_EventScript_RematchJerry
	setvar VAR_0x8004, TRAINER_JERRY_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, Route116_EventScript_TryRegisterJerry
	msgbox Route116_Text_JerryPostBattle, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_TryRegisterJerryAfterBattle::
	goto_if_set FLAG_HAS_MATCH_CALL, Route116_EventScript_RegisterJerryAfterBattle
	release
	end

Route116_EventScript_RegisterJerryAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route116_Text_JerryRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_JERRY_1
	release
	end

Route116_EventScript_TryRegisterJerry::
	goto_if_set FLAG_HAS_MATCH_CALL, Route116_EventScript_RegisterJerry
	msgbox Route116_Text_JerryPostBattle, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_RegisterJerry::
	msgbox Route116_Text_JerryRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_JERRY_1
	release
	end

Route116_EventScript_RematchJerry::
	trainerbattle_rematch TRAINER_JERRY_1, Route116_Text_JerryRematchIntro, Route116_Text_JerryRematchDefeat
	msgbox Route116_Text_JerryPostRematch, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Clark::
	trainerbattle_single TRAINER_CLARK, Route116_Text_ClarkIntro, Route116_Text_ClarkDefeat
	msgbox Route116_Text_ClarkPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Janice::
	trainerbattle_single TRAINER_JANICE, Route116_Text_JaniceIntro, Route116_Text_JaniceDefeat
	msgbox Route116_Text_JanicePostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Karen::
	trainerbattle_single TRAINER_KAREN_1, Route116_Text_KarenIntro, Route116_Text_KarenDefeat, Route116_EventScript_TryRegisterKarenAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route116_EventScript_RematchKaren
	setvar VAR_0x8004, TRAINER_KAREN_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, Route116_EventScript_TryRegisterKaren
	msgbox Route116_Text_KarenPostBattle, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_TryRegisterKarenAfterBattle::
	goto_if_set FLAG_HAS_MATCH_CALL, Route116_EventScript_RegisterKarenAfterBattle
	release
	end

Route116_EventScript_RegisterKarenAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route116_Text_KarenRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_KAREN_1
	release
	end

Route116_EventScript_TryRegisterKaren::
	goto_if_set FLAG_HAS_MATCH_CALL, Route116_EventScript_RegisterKaren
	msgbox Route116_Text_KarenPostBattle, MSGBOX_DEFAULT
	release
	end

Route116_EventScript_RegisterKaren::
	msgbox Route116_Text_KarenRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_KAREN_1
	release
	end

Route116_EventScript_RematchKaren::
	trainerbattle_rematch TRAINER_KAREN_1, Route116_Text_KarenRematchIntro, Route116_Text_KarenRematchDefeat
	msgbox Route116_Text_KarenPostRematch, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Sarah::
	trainerbattle_single TRAINER_SARAH, Route116_Text_SarahIntro, Route116_Text_SarahDefeat
	msgbox Route116_Text_SarahPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Dawson::
	trainerbattle_single TRAINER_DAWSON, Route116_Text_DawsonIntro, Route116_Text_DawsonDefeat
	msgbox Route116_Text_DawsonPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Devan::
	trainerbattle_single TRAINER_DEVAN, Route116_Text_DevanIntro, Route116_Text_DevanDefeat
	msgbox Route116_Text_DevanPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_EventScript_Johnson::
	trainerbattle_single TRAINER_JOHNSON, Route116_Text_JohnsonIntro, Route116_Text_JohnsonDefeat
	msgbox Route116_Text_JohnsonPostBattle, MSGBOX_AUTOCLOSE
	end

Route116_Text_ScoundrelMadeOffWithPeeko:
	.string "Aduh, bagaimana ini?\p"
	.string "PEEKO dan aku sedang\n"
	.string "berjalan-jalan, lalu kami disergap\l"
	.string "oleh penjahat aneh…\p"
	.string "Bajingan itu kabur membawa PEEKO\n"
	.string "kesayanganku!\p"
	.string "Rrrrooooooaaaar! PEEKO!$"

Route116_Text_WantToDigTunnel:
	.string "Nnn… Raungan!\p"
	.string "Aku mau menggali terowongan itu!$"

Route116_Text_DiggingTunnelWhenGoonOrderedMeOut:
	.string "Nnn… Raungan! Ada apa ini?\p"
	.string "Aku sedang menggali terowongan\n"
	.string "tanpa alat saat ada preman yang\l"
	.string "mengusirku!\p"
	.string "Terowongan itu penuh dengan POKéMON\n"
	.string "yang sensitif terhadap suara keras.\l"
	.string "Mereka bisa mengamuk.\p"
	.string "Itu sebabnya kami berhenti memakai\n"
	.string "alat berat untuk menggali…\p"
	.string "Aku khawatir preman itu akan\n"
	.string "melakukan hal bodoh dan membuat\l"
	.string "POKéMON-POKéMON itu mengamuk.$"

Route116_Text_GoonHightailedItOutOfTunnel:
	.string "Nnn… Raungan!\p"
	.string "Preman bodoh itu lari\n"
	.string "terbirit-birit dari terowongan! Aku\l"
	.string "bisa kembali menggali!$"

Route116_Text_ThankYouTokenOfAppreciation:
	.string "Oh! Ternyata kau!\p"
	.string "Kau orang yang tidak hanya\n"
	.string "membantuku di HUTAN PETALBURG,\l"
	.string "tetapi juga mengambil kembali\n"
	.string "paketku yang dicuri dan bahkan\l"
	.string "dengan murah hati mengantarkannya\n"
	.string "ke SLATEPORT!\p"
	.string "KAPTEN STERN juga memberitahu bahwa\n"
	.string "paketnya sudah sampai!\p"
	.string "Aku sangat, sangat berterima kasih!\p"
	.string "Ah, seandainya aku adalah awan\n"
	.string "hujan, aku akan menghujanimu dengan\l"
	.string "rasa terima kasih dan menjunjungmu\n"
	.string "sebagai pahlawan!\p"
	.string "Untukmu, PELATIH yang paling hebat,\n"
	.string "aku punya kabar baik!\p"
	.string "Baru-baru ini, perusahaan kami\n"
	.string "mengembangkan jenis POKé BALL baru.\p"
	.string "Sebagai tanda terima kasih, ini\n"
	.string "adalah hadiah kami untuk PELATIH\l"
	.string "yang hebat!$"

Route116_Text_NewBallAvailableAtMart:
	.string "POKé BALL baru kami akan tersedia\n"
	.string "di POKéMON MART di RUSTBORO.\p"
	.string "Silakan coba! Terima kasih dan\n"
	.string "sampai jumpa!$"

Route116_Text_BagIsJamPacked:
	.string "TAS-mu sudah penuh. Aku tidak bisa\n"
	.string "memberimu REPEAT BALL ini.$"

Route116_Text_TokenOfAppreciation:
	.string "Sebagai tanda terima kasih karena\n"
	.string "telah mengantar paket kami, aku\l"
	.string "punya hadiah jenis POKé BALL baru\n"
	.string "untuk PELATIH kami yang paling\l"
	.string "hebat!$"

Route116_Text_CanYouHelpMeFindGlasses:
	.string "Aku menjatuhkan kacamataku… Bisakah\n"
	.string "kau bantu mencarinya?$"

Route116_Text_MayISeeThoseGlasses:
	.string "Kacamata itu! Boleh kulihat\n"
	.string "sebentar?$"

Route116_Text_NotWhatImLookingForMaybeTheyArentHere:
	.string "Hmm… Ini adalah BLACKGLASSES. Bukan\n"
	.string "ini yang kucari…\p"
	.string "Mungkin kacamataku tidak ada di\n"
	.string "sekitar sini…$"

Route116_Text_CantFindGlassesNotHere:
	.string "Hmm… Aku tidak bisa menemukan\n"
	.string "kacamataku di mana pun… Mungkin\l"
	.string "tidak ada di sekitar sini…$"

Route116_Text_NotWhatImLookingFor:
	.string "Hmm… Ini adalah BLACKGLASSES. Bukan\n"
	.string "ini yang kucari…$"

Route116_Text_RouteSignRustboro:
	.string "RUTE 116 {LEFT_ARROW} KOTA RUSTBORO$"

Route116_Text_RusturfTunnelSign:
	.string "TEROWONGAN RUSTURF “Menghubungkan\n"
	.string "RUSTBORO dan VERDANTURF”\p"
	.string "“Proyek terowongan telah\n"
	.string "dibatalkan.”$"

Route116_Text_TunnelersRestHouse:
	.string "POS ISTIRAHAT PENGGALI TEROWONGAN$"

Route116_Text_TrainerTipsBToStopEvolution:
	.string "KIAT PELATIH\p"
	.string "Jika kau ingin menghentikan POKéMON\n"
	.string "berevolusi, tekan Tombol B saat ia\l"
	.string "mencoba berevolusi. POKéMON yang\n"
	.string "terkejut akan berhenti.\p"
	.string "Ini disebut pembatalan evolusi.$"

Route116_Text_TrainerTipsBagHasPockets:
	.string "KIAT PELATIH\p"
	.string "TAS-mu memiliki beberapa SAKU.\p"
	.string "Item yang kau peroleh otomatis\n"
	.string "ditempatkan di SAKU yang sesuai.\p"
	.string "Tidak ada PELATIH yang bisa\n"
	.string "tanpanya, mereka harus punya TAS\l"
	.string "sendiri.$"