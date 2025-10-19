SlateportCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SlateportCity_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SlateportCity_OnFrame
	.byte 0

SlateportCity_OnTransition:
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 0
	call SlateportCity_EventScript_EnterSlateport
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_MovePeopleForSternInterview
	call_if_eq VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1, SlateportCity_EventScript_SetReadyForScottScene
	end

SlateportCity_EventScript_EnterSlateport::
	setflag FLAG_VISITED_SLATEPORT_CITY
	setvar VAR_CONTEST_HALL_STATE, 0
	setflag FLAG_HIDE_SLATEPORT_CITY_CONTEST_REPORTER
	return

SlateportCity_EventScript_MovePeopleForSternInterview::
	setobjectxyperm LOCALID_SLATEPORT_CAPT_STERN, 28, 13
	setobjectxyperm LOCALID_SLATEPORT_OLD_WOMAN, 25, 13
	setobjectxyperm LOCALID_SLATEPORT_RICH_BOY, 25, 14
	setobjectxyperm LOCALID_SLATEPORT_COOK, 27, 16
	setobjectxyperm LOCALID_SLATEPORT_GIRL, 28, 16
	setobjectxyperm LOCALID_SLATEPORT_FAT_MAN, 29, 16
	setobjectxyperm LOCALID_SLATEPORT_MAN_1, 31, 14
	setobjectmovementtype LOCALID_SLATEPORT_CAPT_STERN, MOVEMENT_TYPE_FACE_DOWN
	setobjectmovementtype LOCALID_SLATEPORT_OLD_WOMAN, MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT
	setobjectmovementtype LOCALID_SLATEPORT_RICH_BOY, MOVEMENT_TYPE_FACE_UP_AND_RIGHT
	setobjectmovementtype LOCALID_SLATEPORT_COOK, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_SLATEPORT_GIRL, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_SLATEPORT_FAT_MAN, MOVEMENT_TYPE_FACE_UP
	setobjectmovementtype LOCALID_SLATEPORT_MAN_1, MOVEMENT_TYPE_FACE_LEFT
	return

SlateportCity_EventScript_SetReadyForScottScene::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_eq VAR_0x8004, 30, SlateportCity_EventScript_MoveScottLeft
	setobjectxyperm LOCALID_SLATEPORT_SCOTT, 23, 27
	setobjectmovementtype LOCALID_SLATEPORT_SCOTT, MOVEMENT_TYPE_FACE_RIGHT
	return

SlateportCity_EventScript_MoveScottLeft::
	setobjectxyperm LOCALID_SLATEPORT_SCOTT, 22, 27
	setobjectmovementtype LOCALID_SLATEPORT_SCOTT, MOVEMENT_TYPE_FACE_RIGHT
	return

SlateportCity_OnFrame:
	map_script_2 VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1, SlateportCity_EventScript_ScottScene
	.2byte 0

SlateportCity_EventScript_ScottScene::
	lockall
	addobject LOCALID_SLATEPORT_SCOTT
	applymovement LOCALID_PLAYER, SlateportCity_Movement_PlayerFaceScott
	applymovement LOCALID_SLATEPORT_SCOTT, SlateportCity_Movement_ScottApproachPlayer
	waitmovement 0
	msgbox SlateportCity_Text_YouDroveTeamAquaAway, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_SCOTT, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 60
	msgbox SlateportCity_Text_MaybeThisTrainer, MSGBOX_DEFAULT
	applymovement LOCALID_SLATEPORT_SCOTT, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox SlateportCity_Text_LetsRegisterEachOther, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox SlateportCity_Text_RegisteredScott, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_SCOTT_MATCH_CALL
	msgbox SlateportCity_Text_KeepEyeOnTrainersBeSeeingYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_SCOTT, SlateportCity_Movement_ScottExit
	waitmovement 0
	removeobject LOCALID_SLATEPORT_SCOTT
	setobjectxyperm LOCALID_SLATEPORT_SCOTT, 10, 12
	setobjectmovementtype LOCALID_SLATEPORT_SCOTT, MOVEMENT_TYPE_FACE_DOWN
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 2
	addvar VAR_SCOTT_STATE, 1
	releaseall
	end

SlateportCity_Movement_PlayerFaceScott:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

SlateportCity_Movement_ScottApproachPlayer:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_Movement_ScottExit:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

SlateportCity_EventScript_EnergyGuru::
	lock
	faceplayer
	message SlateportCity_Text_EnergyGuruSellWhatYouNeed
	waitmessage
	pokemart SlateportCity_Pokemart_EnergyGuru
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_Pokemart_EnergyGuru:
	.2byte ITEM_PROTEIN
	.2byte ITEM_IRON
	.2byte ITEM_CARBOS
	.2byte ITEM_ZINC
	.2byte ITEM_CALCIUM
	.2byte ITEM_HP_UP
	pokemartlistend

SlateportCity_EventScript_EffortRibbonWoman::
	lock
	faceplayer
	bufferleadmonspeciesname STR_VAR_1
	msgbox SlateportCity_Text_OhYourPokemon, MSGBOX_DEFAULT
	specialvar VAR_RESULT, LeadMonHasEffortRibbon
	call_if_eq VAR_RESULT, TRUE, SlateportCity_EventScript_MonHasEffortRibbon
	specialvar VAR_RESULT, Special_AreLeadMonEVsMaxedOut
	call_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_MonEVsNotMaxed
	msgbox SlateportCity_Text_PleaseGiveItThisEffortRibbon, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message SlateportCity_Text_ReceivedEffortRibbon
	waitfanfare
	msgbox SlateportCity_Text_PutEffortRibbonOnMon, MSGBOX_DEFAULT
	special GiveLeadMonEffortRibbon
	release
	end

SlateportCity_EventScript_MonEVsNotMaxed::
	msgbox SlateportCity_Text_GoForItLittleHarder, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_MonHasEffortRibbon::
	msgbox SlateportCity_Text_EffortRibbonLooksGoodOnIt, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Cook::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_CookSternInterview
	msgbox SlateportCity_Text_SeaweedFullOfLife, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_CookSternInterview::
	msgbox SlateportCity_Text_CaptainComeBackWithBigFish, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_OldWoman::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_OldWomanSternInterview
	msgbox SlateportCity_Text_HowTownIsBornAndGrows, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_OldWomanSternInterview::
	msgbox SlateportCity_Text_CaptSternBeingInterviewed, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Girl::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_GirlSternInterview
	goto_if_set FLAG_RECEIVED_SECRET_POWER, SlateportCity_EventScript_GirlSecretBase
	msgbox SlateportCity_Text_SlateportWonderfulPlace, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_GirlSternInterview::
	msgbox SlateportCity_Text_InterviewerSoCool, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_GirlSecretBase::
	msgbox SlateportCity_Text_BuyBricksSoDecorWontGetDirty, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_RichBoy::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_RichBoySternInterview
	msgbox SlateportCity_Text_GoingToCompeteInBattleTent, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_RichBoySternInterview::
	msgbox SlateportCity_Text_SternSaysDiscoveredSomething, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_FatMan::
	goto_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_FatManSternInterview
	msgbox SlateportCity_Text_BushedHikingFromMauville, MSGBOX_NPC
	end

SlateportCity_EventScript_FatManSternInterview::
	msgbox SlateportCity_Text_AmIOnTV, MSGBOX_SIGN
	end

SlateportCity_EventScript_Man1::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_Man1SternInterview
	msgbox SlateportCity_Text_EveryoneCallsHimCaptStern, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Man1SternInterview::
	msgbox SlateportCity_Text_CaptainsACelebrity, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Woman1::
	lock
	faceplayer
	goto_if_set FLAG_DOCK_REJECTED_DEVON_GOODS, SlateportCity_EventScript_Woman1AquaGone
	msgbox SlateportCity_Text_WhatsLongLineOverThere, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Woman1AquaGone::
	msgbox SlateportCity_Text_VisitedMuseumOften, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_BattleTentSign::
	msgbox SlateportCity_Text_BattleTentSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_SternsShipyardSign::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_EventScript_SternsShipyardFerryComplete
	goto_if_set FLAG_BADGE07_GET, SlateportCity_EventScript_SternsShipyardNearsCompletion
	msgbox SlateportCity_Text_SternsShipyardWantedSign, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_SternsShipyardNearsCompletion::
	msgbox SlateportCity_Text_SternsShipyardNearsCompletion, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_SternsShipyardFerryComplete::
	msgbox SlateportCity_Text_SternsShipyardFerryComplete, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_PokemonFanClubSign::
	msgbox SlateportCity_Text_PokemonFanClubSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_OceanicMuseumSign::
	msgbox SlateportCity_Text_OceanicMuseumSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_CitySign::
	msgbox SlateportCity_Text_CitySign, MSGBOX_SIGN
	end

SlateportCity_EventScript_MarketSign::
	msgbox SlateportCity_Text_MarketSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_HarborSign::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_EventScript_HarborSignFerryComplete
	msgbox SlateportCity_Text_HarborFerryUnderConstruction, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_HarborSignFerryComplete::
	msgbox SlateportCity_Text_HarborSign, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_EventScript_NameRatersHouseSign::
	msgbox SlateportCity_Text_NameRatersHouseSign, MSGBOX_SIGN
	end

SlateportCity_EventScript_Maniac::
	lock
	faceplayer
	call_if_eq VAR_SLATEPORT_CITY_STATE, 1, SlateportCity_EventScript_ManiacSternInterview
	msgbox SlateportCity_Text_GetNameRaterToHelpYou, MSGBOX_DEFAULT
	release
	end

@ Unclear if the text here was meant to be different, but its not
SlateportCity_EventScript_ManiacSternInterview::
	msgbox SlateportCity_Text_GetNameRaterToHelpYou, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_Woman2::
	msgbox SlateportCity_Text_CantChangeTradeMonName, MSGBOX_NPC
	end

SlateportCity_EventScript_Sailor1::
	msgbox SlateportCity_Text_SeaIsSoWet, MSGBOX_NPC
	end

SlateportCity_EventScript_Sailor2::
	msgbox SlateportCity_Text_SinkOldBoats, MSGBOX_NPC
	end

SlateportCity_EventScript_PokefanF::
	msgbox SlateportCity_Text_BuyTooMuch, MSGBOX_NPC
	end

SlateportCity_EventScript_Man2::
	msgbox SlateportCity_Text_BattleTentBuiltRecently, MSGBOX_NPC
	end

SlateportCity_EventScript_AquaGrunt1::
	lock
	faceplayer
	msgbox SlateportCity_Text_QuitPushing, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt2::
	lock
	faceplayer
	msgbox SlateportCity_Text_AquaHasPolicy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt3::
	lock
	faceplayer
	msgbox SlateportCity_Text_BossIsBrilliant, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt4::
	lock
	faceplayer
	msgbox SlateportCity_Text_WhatsNewSchemeIWonder, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt5::
	lock
	faceplayer
	msgbox SlateportCity_Text_ShouldTakeItAll, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_5, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt6::
	lock
	faceplayer
	msgbox SlateportCity_Text_DontButtIn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_6, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt7::
	lock
	faceplayer
	msgbox SlateportCity_Text_RemindsMeOfLongLineForGames, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_7, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt8::
	lock
	faceplayer
	msgbox SlateportCity_Text_WhyAreWeLiningUp, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_8, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_AquaGrunt9::
	lock
	faceplayer
	playse SE_PIN
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_Delay48
	waitmovement 0
	msgbox SlateportCity_Text_WhatDoYouWant, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_FaceOriginalDirection
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, SlateportCity_Movement_DelayAquaGrunt
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_Text_IllReadSignForYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_FaceOriginalDirection
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, SlateportCity_Movement_DelayAquaGrunt
	waitmovement 0
	msgbox SlateportCity_Text_SaysSomethingLikeSeaIsEndless, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_FacePlayer
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, SlateportCity_Movement_DelayAquaGrunt
	waitmovement 0
	applymovement LOCALID_SLATEPORT_GRUNT_9, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_Movement_DelayAquaGrunt:
	delay_16
	delay_16
	step_end

SlateportCity_EventScript_AquaGrunt10::
	msgbox SlateportCity_Text_ShouldveBroughtMyGameBoy, MSGBOX_SIGN
	end

SlateportCity_EventScript_AquaGrunt11::
	lock
	faceplayer
	msgbox SlateportCity_Text_HotSpringsAfterOperation, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GRUNT_11, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_EventScript_DollClerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration SlateportCity_PokemartDecor_Dolls
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_PokemartDecor_Dolls:
	.2byte DECOR_AZURILL_DOLL
	.2byte DECOR_MARILL_DOLL
	.2byte DECOR_SKITTY_DOLL
	pokemartlistend

SlateportCity_EventScript_ComeBackWithSecretPower::
	msgbox gText_ComeBackWithSecretPower, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_DecorClerk::
	lock
	faceplayer
	goto_if_unset FLAG_RECEIVED_SECRET_POWER, SlateportCity_EventScript_ComeBackWithSecretPower
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration SlateportCity_PokemartDecor
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_PokemartDecor:
	.2byte DECOR_RED_BRICK
	.2byte DECOR_BLUE_BRICK
	.2byte DECOR_YELLOW_BRICK
	.2byte DECOR_RED_BALLOON
	.2byte DECOR_BLUE_BALLOON
	.2byte DECOR_YELLOW_BALLOON
	.2byte DECOR_C_LOW_NOTE_MAT
	.2byte DECOR_D_NOTE_MAT
	.2byte DECOR_E_NOTE_MAT
	.2byte DECOR_F_NOTE_MAT
	.2byte DECOR_G_NOTE_MAT
	.2byte DECOR_A_NOTE_MAT
	.2byte DECOR_B_NOTE_MAT
	.2byte DECOR_C_HIGH_NOTE_MAT
	pokemartlistend

SlateportCity_EventScript_PowerTMClerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart SlateportCity_Pokemart_PowerTMs
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
SlateportCity_Pokemart_PowerTMs:
	.2byte ITEM_TM_HIDDEN_POWER
	.2byte ITEM_TM_SECRET_POWER
	pokemartlistend

@ Scene with Capt Sterns interview and Team Aqua announcing plans to steal Submarine
SlateportCity_EventScript_CaptStern::
	lockall
	msgbox SlateportCity_Text_SternMoveAheadWithExploration, MSGBOX_DEFAULT
	msgbox SlateportCity_Text_GabbyWonderfulThanksForInterview, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_GABBY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 10
	applymovement LOCALID_SLATEPORT_TY, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 25
	applymovement LOCALID_SLATEPORT_CAPT_STERN, SlateportCity_Movement_SternWatchGabbyAndTyExit
	applymovement LOCALID_PLAYER, SlateportCity_Movement_PlayerFaceStern
	applymovement LOCALID_SLATEPORT_GABBY, SlateportCity_Movement_GabbyExit
	applymovement LOCALID_SLATEPORT_TY, SlateportCity_Movement_TyExit
	waitmovement 0
	removeobject LOCALID_SLATEPORT_GABBY
	removeobject LOCALID_SLATEPORT_TY
	msgbox SlateportCity_Text_SternWhewFirstInterview, MSGBOX_DEFAULT
	applymovement LOCALID_SLATEPORT_CAPT_STERN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_Text_OhPlayerWeMadeDiscovery, MSGBOX_DEFAULT
	playbgm MUS_ENCOUNTER_AQUA, FALSE
	msgbox SlateportCity_Text_AquaWillAssumeControlOfSubmarine, MSGBOX_DEFAULT
	applymovement LOCALID_SLATEPORT_COOK, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_SLATEPORT_FAT_MAN, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_SLATEPORT_OLD_WOMAN, SlateportCity_Movement_OldWomanConcern
	applymovement LOCALID_SLATEPORT_RICH_BOY, Common_Movement_QuestionMark
	applymovement LOCALID_SLATEPORT_MAN_1, SlateportCity_Movement_ManConcern
	waitmovement 0
	applymovement LOCALID_SLATEPORT_CAPT_STERN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox SlateportCity_Text_SternWhatWasAllThat, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement LOCALID_SLATEPORT_CAPT_STERN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_SLATEPORT_CAPT_STERN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_SLATEPORT_CAPT_STERN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_Text_FromHarborTryingToTakeSub, MSGBOX_DEFAULT
	msgbox SlateportCity_Text_PleaseComeWithMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SLATEPORT_CAPT_STERN, SlateportCity_Movement_SternEnterHarbor
	applymovement LOCALID_PLAYER, SlateportCity_Movement_PlayerEnterHarbor
	waitmovement 0
	removeobject LOCALID_SLATEPORT_CAPT_STERN
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_CAPTAIN_STERN
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_SUBMARINE_SHADOW
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_AQUA_GRUNT
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_ARCHIE
	setvar VAR_SLATEPORT_CITY_STATE, 2
	warp MAP_SLATEPORT_CITY_HARBOR, 11, 14
	waitstate
	releaseall
	end

SlateportCity_Movement_OldWomanConcern:
	delay_16
	delay_16
	emote_question_mark
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

SlateportCity_Movement_ManConcern:
	emote_question_mark
	walk_in_place_faster_up
	delay_16
	walk_in_place_faster_down
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

SlateportCity_Movement_GabbyExit:
	delay_16
	walk_left
	walk_left
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

SlateportCity_Movement_TyExit:
	walk_down
	walk_left
	walk_left
	walk_left
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

SlateportCity_Movement_Unused:
	walk_down
	walk_in_place_faster_up
	step_end

SlateportCity_Movement_SternEnterHarbor:
	walk_right
	walk_up
	walk_up
	set_invisible
	step_end

SlateportCity_Movement_SternWatchGabbyAndTyExit:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_down
	walk_left
	step_end

SlateportCity_Movement_PlayerEnterHarbor:
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_right
	walk_up
	step_end

SlateportCity_Movement_PlayerFaceStern:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_down
	step_end

SlateportCity_EventScript_Ty::
	msgbox SlateportCity_Text_BigSmileForCamera, MSGBOX_SIGN
	end

SlateportCity_EventScript_Gabby::
	msgbox SlateportCity_Text_MostInvaluableExperience, MSGBOX_SIGN
	end

SlateportCity_EventScript_Man3::
	msgbox SlateportCity_Text_WonderIfLighthouseStartlesPokemon, MSGBOX_NPC
	end

SlateportCity_EventScript_BerryPowderClerk::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_POWDER_JAR, SlateportCity_EventScript_ReceivedPowderJar
	msgbox SlateportCity_Text_ExplainBerries, MSGBOX_DEFAULT
	giveitem ITEM_POWDER_JAR
	setflag FLAG_RECEIVED_POWDER_JAR
	msgbox SlateportCity_Text_ExplainBerryPowder, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_ReceivedPowderJar::
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, HasEnoughBerryPowder
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_ExplainBerryPowder
	msgbox SlateportCity_Text_BroughtMeSomeBerryPowder, MSGBOX_DEFAULT
	special DisplayBerryPowderVendorMenu
	goto SlateportCity_EventScript_ChooseBerryPowderItem
	end

SlateportCity_EventScript_ExplainBerryPowder::
	msgbox SlateportCity_Text_ExplainBerryPowder, MSGBOX_DEFAULT
	release
	end

SlateportCity_EventScript_ChooseBerryPowderItem::
	message SlateportCity_Text_ExchangeWhatWithIt
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_BERRY_POWDER_VENDOR
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, SlateportCity_EventScript_EnergyPowder
	case 1, SlateportCity_EventScript_EnergyRoot
	case 2, SlateportCity_EventScript_HealPowder
	case 3, SlateportCity_EventScript_RevivalHerb
	case 4, SlateportCity_EventScript_Protein
	case 5, SlateportCity_EventScript_Iron
	case 6, SlateportCity_EventScript_Carbos
	case 7, SlateportCity_EventScript_Calcium
	case 8, SlateportCity_EventScript_Zinc
	case 9, SlateportCity_EventScript_HPUp
	case 10, SlateportCity_EventScript_PPUp
	case 11, SlateportCity_EventScript_CancelPowderItemSelect
	case MULTI_B_PRESSED, SlateportCity_EventScript_CancelPowderItemSelect
	end

SlateportCity_EventScript_EnergyPowder::
	bufferitemname STR_VAR_1, ITEM_ENERGY_POWDER
	setvar VAR_0x8008, ITEM_ENERGY_POWDER
	setvar VAR_0x8009, 50
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_EnergyRoot::
	bufferitemname STR_VAR_1, ITEM_ENERGY_ROOT
	setvar VAR_0x8008, ITEM_ENERGY_ROOT
	setvar VAR_0x8009, 80
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_HealPowder::
	bufferitemname STR_VAR_1, ITEM_HEAL_POWDER
	setvar VAR_0x8008, ITEM_HEAL_POWDER
	setvar VAR_0x8009, 50
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_RevivalHerb::
	bufferitemname STR_VAR_1, ITEM_REVIVAL_HERB
	setvar VAR_0x8008, ITEM_REVIVAL_HERB
	setvar VAR_0x8009, 300
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Protein::
	bufferitemname STR_VAR_1, ITEM_PROTEIN
	setvar VAR_0x8008, ITEM_PROTEIN
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Iron::
	bufferitemname STR_VAR_1, ITEM_IRON
	setvar VAR_0x8008, ITEM_IRON
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Carbos::
	bufferitemname STR_VAR_1, ITEM_CARBOS
	setvar VAR_0x8008, ITEM_CARBOS
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Calcium::
	bufferitemname STR_VAR_1, ITEM_CALCIUM
	setvar VAR_0x8008, ITEM_CALCIUM
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_Zinc::
	bufferitemname STR_VAR_1, ITEM_ZINC
	setvar VAR_0x8008, ITEM_ZINC
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_HPUp::
	bufferitemname STR_VAR_1, ITEM_HP_UP
	setvar VAR_0x8008, ITEM_HP_UP
	setvar VAR_0x8009, 1000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_PPUp::
	bufferitemname STR_VAR_1, ITEM_PP_UP
	setvar VAR_0x8008, ITEM_PP_UP
	setvar VAR_0x8009, 3000
	goto SlateportCity_EventScript_TryBuyBerryPowderItem
	end

SlateportCity_EventScript_CancelPowderItemSelect::
	msgbox SlateportCity_Text_ComeBackToTradeBerryPowder, MSGBOX_DEFAULT
	special RemoveBerryPowderVendorMenu
	release
	end

SlateportCity_EventScript_TryBuyBerryPowderItem::
	msgbox SlateportCity_Text_ExchangeBerryPowderForItem, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SlateportCity_EventScript_ChooseBerryPowderItem
	copyvar VAR_0x8004, VAR_0x8009
	specialvar VAR_RESULT, HasEnoughBerryPowder
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_NotEnoughBerryPowder
	giveitem VAR_0x8008
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_EventScript_NoRoomForBerryPowderItem
	copyvar VAR_0x8004, VAR_0x8009
	special TakeBerryPowder
	special PrintPlayerBerryPowderAmount
	msgbox SlateportCity_Text_FineBerryPowderTradeSomethingElse, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_EventScript_ChooseBerryPowderItem
	msgbox SlateportCity_Text_WhenYouGetMoreBringItToMe, MSGBOX_DEFAULT
	special RemoveBerryPowderVendorMenu
	release
	end

SlateportCity_EventScript_NoRoomForBerryPowderItem::
	msgbox gText_TheBagIsFull, MSGBOX_DEFAULT
	special RemoveBerryPowderVendorMenu
	release
	end

SlateportCity_EventScript_NotEnoughBerryPowder::
	msgbox SlateportCity_Text_DontHaveEnoughBerryPowder, MSGBOX_DEFAULT
	goto SlateportCity_EventScript_ChooseBerryPowderItem
	end

SlateportCity_EventScript_ScottBattleTentScene::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	opendoor 10, 12
	waitdooranim
	addobject LOCALID_SLATEPORT_SCOTT
	applymovement LOCALID_PLAYER, SlateportCity_Movement_PushPlayerDown
	applymovement LOCALID_SLATEPORT_SCOTT, SlateportCity_Movement_ScottExitBattleTent
	waitmovement 0
	closedoor 10, 12
	waitdooranim
	msgbox SlateportCity_Text_TakingBattleTentChallenge, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, SlateportCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_SLATEPORT_SCOTT, SlateportCity_Movement_ScottExitAfterBattleTent
	waitmovement 0
	removeobject LOCALID_SLATEPORT_SCOTT
	addvar VAR_SCOTT_STATE, 1
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 3
	releaseall
	end

SlateportCity_Movement_PushPlayerDown:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

SlateportCity_Movement_PlayerWatchScottExit:
	delay_16
	walk_in_place_faster_right
	step_end

SlateportCity_Movement_ScottExitBattleTent:
	delay_8
	walk_down
	step_end

SlateportCity_Movement_ScottExitAfterBattleTent:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_EventScript_BerryCrushRankingsSign::
	lockall
	special ShowBerryCrushRankings
	waitstate
	releaseall
	end

SlateportCity_Text_EnergyGuruSellWhatYouNeed:
	.string "Aku ENERGY GURU! Aku akan melakukannya dan\n"
	.string "menjual apa yang kamu butuhkan!$"

SlateportCity_Text_OhYourPokemon:
	.string "Oh?\n"
	.string "{STR_VAR_1}-mu…$"

SlateportCity_Text_PleaseGiveItThisEffortRibbon:
	.string "Melakukannya dengan luar biasa!\p"
	.string "Sebagai hadiahnya, tolong berikan\n"
	.string "EFFORT RIBBON ini.$"

SlateportCity_Text_ReceivedEffortRibbon:
	.string "{PLAYER} mendapatkan EFFORT RIBBON.$"

SlateportCity_Text_PutEffortRibbonOnMon:
	.string "{PLAYER} memasang EFFORT RIBBON\n"
	.string "pada {STR_VAR_1}.$"

SlateportCity_Text_GoForItLittleHarder:
	.string "Kamu harus berusaha sedikit lebih keras.\p"
	.string "Jika kamu berhasil, aku akan memberikan\n"
	.string "sesuatu yang bagus untuk POKéMON-mu.$"

SlateportCity_Text_EffortRibbonLooksGoodOnIt:
	.string "Oh! {STR_VAR_1}-mu, EFFORT RIBBON itu\n"
	.string "sangat cocok!$"

SlateportCity_Text_WonderIfLighthouseStartlesPokemon:
	.string "Cahaya mercusuar mencapai\n"
	.string "puluhan mil jauhnya.\p"
	.string "Aku ingin tahu apakah itu tidak\n"
	.string "mengejutkan POKéMON di laut.$"

SlateportCity_Text_SeaweedFullOfLife:
	.string "Ooh, lihat ini!\p"
	.string "Rumput laut yang bisa kamu dapatkan\n"
	.string "di sekitar sini segar dan penuh kehidupan.\p"
	.string "Wah, sepertinya bahkan bisa bangkit\n"
	.string "dan menyerang!$"

SlateportCity_Text_HowTownIsBornAndGrows:
	.string "Di mana air bersih, hasil panen\n"
	.string "melimpah berkumpul.\p"
	.string "Dan di mana orang-orang berkumpul,\n"
	.string "pasar segera dimulai.\p"
	.string "Begitulah sebuah kota lahir dan tumbuh.$"

SlateportCity_Text_SlateportWonderfulPlace:
	.string "Berbelanja di mana kamu bisa\n"
	.string "menghirup aroma laut…\p"
	.string "SLATEPORT adalah tempat yang indah!$"

SlateportCity_Text_BuyBricksSoDecorWontGetDirty:
	.string "Jika kamu meletakkan DOLLS atau CUSHIONS\n"
	.string "di lantai, mereka akan kotor.\p"
	.string "Aku akan membeli BRICKS agar DOLLS\n"
	.string "dan CUSHIONS-ku tidak kotor\l"
	.string "saat aku meninggalkannya.$"

SlateportCity_Text_GoingToCompeteInBattleTent:
	.string "Wroooar! Aku juga akan berkompetisi\n"
	.string "di BATTLE TENT!\p"
	.string "Tapi sebelum itu, aku harus\n"
	.string "menangkap beberapa POKéMON!$"

SlateportCity_Text_BushedHikingFromMauville:
	.string "Fiuh… Aku lelah sekali…\p"
	.string "Aku mendaki dari MAUVILLE CITY.\n"
	.string "Tapi, wah, kota ini besar sekali.\p"
	.string "Jika aku tahu ini, aku pasti sudah\n"
	.string "naik BIKE ke sini.$"

SlateportCity_Text_EveryoneCallsHimCaptStern:
	.string "STERN, orang yang membangun MUSEUM,\n"
	.string "juga merupakan pemimpin tim eksplorasi\l"
	.string "bawah laut.\p"
	.string "Jadi, semua orang memanggilnya KAPTEN STERN.$"

SlateportCity_Text_WhatsLongLineOverThere:
	.string "Apa itu di sana?\n"
	.string "Antrean panjang itu…$"

SlateportCity_Text_VisitedMuseumOften:
	.string "Ketika aku masih kecil, aku sering\n"
	.string "mengunjungi MUSEUM.\p"
	.string "Aku dulu bermimpi tentang misteri\n"
	.string "laut setelah melihat pameran.$"

SlateportCity_Text_QuitPushing:
	.string "Hei! Jangan mendorong!\n"
	.string "Ini antrean, tidakkah kamu lihat?$"

SlateportCity_Text_AquaHasPolicy:
	.string "TEAM AQUA memiliki kebijakan\n"
	.string "untuk berkumpul dan membubarkan diri\l"
	.string "di lokasi operasi.$"

SlateportCity_Text_BossIsBrilliant:
	.string "BOS kami sangat brilian.\p"
	.string "Apa yang ingin dia lakukan dengan\n"
	.string "MUSEUM sekarang?$"

SlateportCity_Text_WhatsNewSchemeIWonder:
	.string "Apa rencana barunya, ya?\p"
	.string "BOS kami menyeramkan kalau marah, jadi\n"
	.string "aku sebaiknya tidak mengacau…$"

SlateportCity_Text_ShouldTakeItAll:
	.string "Jika ada sesuatu yang kami butuhkan di\n"
	.string "MUSEUM, kami harus mengambil semuanya!$"

SlateportCity_Text_DontButtIn:
	.string "Hei, kamu di sana!\n"
	.string "Jangan ikut campur!$"

SlateportCity_Text_RemindsMeOfLongLineForGames:
	.string "Antrean panjang, ya?\p"
	.string "Itu mengingatkanku pada saat-saat aku\n"
	.string "mengantre untuk membeli game laris…$"

SlateportCity_Text_WhyAreWeLiningUp:
	.string "Mengapa kita harus mengantre dan membayar?\n"
	.string "Kita harus langsung masuk saja!$"

SlateportCity_Text_WhatDoYouWant:
	.string "Apa?\n"
	.string "Apa yang kamu inginkan?$"

SlateportCity_Text_IllReadSignForYou:
	.string "Kamu ingin membaca tanda ini?\n"
	.string "Aku akan membacakannya untukmu!$"

SlateportCity_Text_SaysSomethingLikeSeaIsEndless:
	.string "Coba kulihat…\p"
	.string "Um… Aku rasa itu mengatakan sesuatu\n"
	.string "seperti “kehidupan di laut tak ada habisnya.”\p"
	.string "Yup, aku cukup yakin begitu\n"
	.string "katanya.$"

SlateportCity_Text_ShouldveBroughtMyGameBoy:
	.string "Mengeluh…\p"
	.string "Seharusnya aku membawa Game Boy\n"
	.string "Advance-ku agar tidak bosan mengantre…\p"
	.string "Mengeluh…$"

SlateportCity_Text_HotSpringsAfterOperation:
	.string "Setelah operasi ini selesai, aku akan\n"
	.string "membawamu ke spa air panas!\p"
	.string "Begitulah kata pemimpin kami.\n"
	.string "Aku tidak sabar!$"

SlateportCity_Text_SeaIsSoWet:
	.string "Laut itu sangat luas…\p"
	.string "Mungkinkah laut ini tercipta dari\n"
	.string "air mata POKéMON?$"

SlateportCity_Text_SinkOldBoats:
	.string "Tahukah kamu apa yang mereka lakukan\n"
	.string "dengan kapal tua yang terlalu reyot untuk berlayar?\p"
	.string "Mereka menenggelamkannya di laut agar\n"
	.string "menjadi habitat bagi POKéMON.$"

SlateportCity_Text_BuyTooMuch:
	.string "Setiap kali aku berkunjung ke sini, aku\n"
	.string "terbawa suasana dan membeli terlalu banyak.$"

SlateportCity_Text_GetNameRaterToHelpYou:
	.string "Jika kamu ingin mengubah nama panggilan\n"
	.string "POKéMON-mu, kamu harus meminta bantuan\l"
	.string "NAME RATER.$"

SlateportCity_Text_CantChangeTradeMonName:
	.string "POKéMON apa pun yang kamu dapatkan\n"
	.string "dalam pertukaran, kamu tidak bisa mengubah nama panggilannya.\p"
	.string "Cinta TRAINER aslinya untuk POKéMON itu\n"
	.string "ada di nama panggilannya.$"

SlateportCity_Text_BattleTentBuiltRecently:
	.string "Baru-baru ini, sebuah BATTLE TENT\n"
	.string "dibangun di SLATEPORT.\p"
	.string "GYM memang menyenangkan, tapi BATTLE\n"
	.string "TENT juga luar biasa dengan caranya sendiri.\p"
	.string "Kamu harus mencari POKéMON tangguh\n"
	.string "untuk BATTLE TENT!$"

SlateportCity_Text_CaptSternBeingInterviewed:
	.string "Aku berharap itu adalah bintang terkenal\n"
	.string "agar aku bisa mendapatkan tanda tangan.\p"
	.string "Tapi siapa yang sedang diwawancarai itu?\n"
	.string "Bukankah itu KAPTEN STERN?$"

SlateportCity_Text_InterviewerSoCool:
	.string "Pewawancara wanita itu sangat keren\n"
	.string "dan cantik.\p"
	.string "Ketika aku besar nanti, aku akan menjadi\n"
	.string "jurnalis internasional!$"

SlateportCity_Text_SternSaysDiscoveredSomething:
	.string "KAPTEN STERN mengatakan mereka\n"
	.string "menemukan sesuatu di dasar laut.\p"
	.string "Aku ingin tahu apa itu?\n"
	.string "Apa ya kira-kira?$"

SlateportCity_Text_CaptainComeBackWithBigFish:
	.string "Apa yang terjadi di sini?\p"
	.string "Apakah KAPTEN yang baik itu kembali\n"
	.string "dengan ikan besar dari dasar laut?$"

SlateportCity_Text_AmIOnTV:
	.string "Hei! Apa kamu menonton?\n"
	.string "Apa aku di TV?$"

SlateportCity_Text_CaptainsACelebrity:
	.string "Wawancara TV! Di sini!\n"
	.string "KAPTEN adalah selebriti!$"

SlateportCity_Text_BigSmileForCamera:
	.string "TY: Oke, KAPTEN STERN, senyum lebar\n"
	.string "untuk kamera!$"

SlateportCity_Text_MostInvaluableExperience:
	.string "GABBY: Aku mengerti, aku mengerti. Kamu\n"
	.string "telah mendapatkan pengalaman yang sangat\l"
	.string "berharga…$"

SlateportCity_Text_SternMoveAheadWithExploration:
	.string "KAPTEN STERN: Ya, memang. Kami bermaksud\n"
	.string "untuk melanjutkan eksplorasi kami.$"

SlateportCity_Text_GabbyWonderfulThanksForInterview:
	.string "GABBY: Itu luar biasa, KAPTEN STERN!\n"
	.string "Terima kasih telah meluangkan waktu dari\l"
	.string "jadwal sibukmu untuk berbicara dengan kami.\p"
	.string "Kami berharap dapat mewawancarai Anda\n"
	.string "lagi dengan berita penemuan lainnya!$"

SlateportCity_Text_SternWhewFirstInterview:
	.string "KAPTEN STERN: Fiuh…\p"
	.string "Itu pertama kalinya aku direkam untuk\n"
	.string "TV. Itu sangat menegangkan.$"

SlateportCity_Text_OhPlayerWeMadeDiscovery:
	.string "Oh! {PLAYER}{KUN}!\n"
	.string "Kamu terlihat hebat!\p"
	.string "Kami membuat penemuan besar pada\n"
	.string "eksplorasi dasar laut terakhir kami.\p"
	.string "Kami menemukan gua bawah laut di\n"
	.string "ROUTE 128.\p"
	.string "Kami pikir itu adalah habitat POKéMON\n"
	.string "yang konon sudah lama punah.$"

SlateportCity_Text_AquaWillAssumeControlOfSubmarine:
	.string "Fufufu…\n"
	.string "KAPTEN STERN, dugaanku.\p"
	.string "Kami dari TEAM AQUA akan mengambil\n"
	.string "alih kapal selammu!\p"
	.string "Keberatanmu tidak ada artinya!\n"
	.string "Kami mengharapkan kerja samamu sepenuhnya!\p"
	.string "Fufufu…\n"
	.string "Lihat dan pelajari saja apa yang telah\l"
	.string "direncanakan TEAM AQUA!$"

SlateportCity_Text_SternWhatWasAllThat:
	.string "KAPTEN STERN: Apa-apaan itu?\p"
	.string "Kedengarannya seperti seseorang\n"
	.string "menggunakan megafon…\p"
	.string "Dari mana asalnya?$"

SlateportCity_Text_FromHarborTryingToTakeSub:
	.string "Itu dari PELABUHAN!\p"
	.string "Kapal selamnya!\n"
	.string "Mereka mencoba mengambilnya!$"

SlateportCity_Text_PleaseComeWithMe:
	.string "{PLAYER}{KUN}!\n"
	.string "Tolong, ikut aku!$"

SlateportCity_Text_BattleTentSign:
	.string "BATTLE TENT LOKASI SLATEPORT\n"
	.string "“Temukan! POKéMON terhebat!”$"

SlateportCity_Text_SternsShipyardWantedSign:
	.string "STERN'S SHIPYARD\p"
	.string "“Dicari: Pelaut yang mampu berlayar\n"
	.string "di semua arus.”$"

SlateportCity_Text_SternsShipyardNearsCompletion:
	.string "STERN'S SHIPYARD\p"
	.string "“The ferry S.S. TIDAL nears\n"
	.string "completion for serving the ports of\l"
	.string "SLATEPORT and LILYCOVE.”$"

SlateportCity_Text_SternsShipyardFerryComplete:
	.string "STERN'S SHIPYARD\p"
	.string "“Boarding of the SLATEPORT-LILYCOVE\n"
	.string "ferry S.S. TIDAL is handled at the\l"
	.string "HARBOR.”$"

SlateportCity_Text_PokemonFanClubSign:
	.string "POKéMON FAN CLUB\n"
	.string "“Calling all fans of POKéMON!”$"

SlateportCity_Text_OceanicMuseumSign:
	.string "“Laut tak terbatas menopang\n"
	.string "semua kehidupan.”\p"
	.string "MUSEUM KELAUTAN$"

SlateportCity_Text_CitySign:
	.string "SLATEPORT CITY\p"
	.string "“Pelabuhan tempat manusia dan POKéMON\n"
	.string "bersilangan jalan.”$"

SlateportCity_Text_MarketSign:
	.string "SLATEPORT MARKET\n"
	.string "“Barang unik yang tidak ditemukan di tempat lain!”$"

SlateportCity_Text_HarborFerryUnderConstruction:
	.string "SLATEPORT HARBOR\p"
	.string "“Feri S.S. TIDAL sedang dalam\n"
	.string "konstruksi di GALANGAN KAPAL.\p"
	.string "“Layanan dijadwalkan akan dimulai\n"
	.string "segera.”$"

SlateportCity_Text_HarborSign:
	.string "SLATEPORT HARBOR\p"
	.string "“Nikmati pelayaran yang menyenangkan di\n"
	.string "feri S.S. TIDAL.”$"

SlateportCity_Text_NameRatersHouseSign:
	.string "NAME RATER'S HOUSE\n"
	.string "“Nama panggilan POKéMON dinilai.”$"

SlateportCity_Text_ExplainBerries:
	.string "Jika POKéMON liar terluka, ia\n"
	.string "menyembuhkan dirinya dengan mengunyah BERRIES.\p"
	.string "Tahukah kamu itu?\p"
	.string "Seseorang melihat itu dan mendapatkan ide\n"
	.string "untuk membuat obat dari BERRIES.\p"
	.string "Tahukah kamu itu?\p"
	.string "Untuk mengubah BERRIES menjadi obat,\n"
	.string "mereka harus dihancurkan menjadi bubuk.\p"
	.string "Tahukah kamu itu?\p"
	.string "Kamu sepertinya tertarik\n"
	.string "pada BERRIES!\p"
	.string "Aku punya sesuatu yang bagus untuk\n"
	.string "orang sepertimu.$"

SlateportCity_Text_ExplainBerryPowder:
	.string "Aku baru-baru ini memasang mesin di\n"
	.string "POKéMON CENTERS untuk menghancurkan BERRIES.\p"
	.string "Mesin BERRY CRUSH ada di\n"
	.string "DIRECT CORNER di lantai atas.\p"
	.string "Tahukah kamu?\p"
	.string "Bisakah kamu membuat BERRY POWDER\n"
	.string "untukku menggunakan mesin-mesin itu?\p"
	.string "Aku bisa membuatkanmu berbagai macam obat\n"
	.string "jika kamu membawakanku banyak BERRY POWDER.$"

SlateportCity_Text_BroughtMeSomeBerryPowder:
	.string "Sudahkah kamu membawakanku\n"
	.string "BERRY POWDER?$"

SlateportCity_Text_ExchangeWhatWithIt:
	.string "Dengan apa kamu ingin\n"
	.string "menukarkannya?$"

SlateportCity_Text_ExchangeBerryPowderForItem:
	.string "Oke, kamu ingin menukar\n"
	.string "BERRY POWDER-mu dengan satu {STR_VAR_1}?$"

SlateportCity_Text_DontHaveEnoughBerryPowder:
	.string "Oh, sayang. Kamu tidak punya cukup\n"
	.string "BERRY POWDER.$"

SlateportCity_Text_FineBerryPowderTradeSomethingElse:
	.string "Ini adalah BERRY POWDER yang bagus.\n"
	.string "Ini akan membuat obat yang sangat baik.\p"
	.string "Apakah kamu ingin menukar lebih banyak\n"
	.string "BERRY POWDER-mu dengan sesuatu yang lain?$"

SlateportCity_Text_WhenYouGetMoreBringItToMe:
	.string "Oke! Jika kamu mendapatkan lebih banyak\n"
	.string "BERRY POWDER, tolong bawakan padaku!$"

SlateportCity_Text_ComeBackToTradeBerryPowder:
	.string "Kembalilah jika kamu ingin menukar\n"
	.string "BERRY POWDER-mu dengan obat.\p"
	.string "Aku selalu mengadakan bazaar di sini.\p"
	.string "Tahukah kamu?$"

SlateportCity_Text_YouDroveTeamAquaAway:
	.string "SCOTT: Hah?\n"
	.string "Aku yakin pernah bertemu denganmu sebelumnya.\p"
	.string "Sudahkah aku memperkenalkan diri?\n"
	.string "Jika belum, namaku SCOTT.\p"
	.string "Aku baru saja melihat TEAM AQUA kabur\n"
	.string "dari sini seperti disengat.\p"
	.string "Coba kutebak--kamu yang mengusir mereka?$"

SlateportCity_Text_MaybeThisTrainer:
	.string "SCOTT: Hmm…\n"
	.string "Mungkin, hanya mungkin, TRAINER ini…$"

SlateportCity_Text_LetsRegisterEachOther:
	.string "SCOTT: Baiklah! Aku rasa kamu akan\n"
	.string "menjadi teman baik.\p"
	.string "Jadi, mari kita daftarkan satu sama lain\n"
	.string "di POKéNAV kita.\p"
	.string "… … … … … …$"

SlateportCity_Text_RegisteredScott:
	.string "Mendaftarkan orang bernama SCOTT ini\n"
	.string "di POKéNAV.$"

SlateportCity_Text_KeepEyeOnTrainersBeSeeingYou:
	.string "SCOTT: Yang ingin kulakukan adalah\n"
	.string "ikut denganmu, tapi aku juga ingin\l"
	.string "mengawasi bakat orang lain.\p"
	.string "Jadi, aku akan pergi menjelajahi kota-kota\n"
	.string "lain sedikit lagi.\p"
	.string "Sampai jumpa, {PLAYER}{KUN}!$"

SlateportCity_Text_TakingBattleTentChallenge:
	.string "SCOTT: Oh, hei!\n"
	.string "Jika bukan {PLAYER}{KUN}!\p"
	.string "{PLAYER}{KUN}, coba kutebak--kamu akan\n"
	.string "mengambil tantangan BATTLE TENT?\p"
	.string "Ya! Itu ide yang bagus!\n"
	.string "Itu ide yang sangat bagus!\p"
	.string "Bagaimanapun, TRAINER yang tangguh\n"
	.string "sangat cocok untuk BATTLE TENT!\p"
	.string "Berikan usaha terbaikmu!$"
