Route119_WeatherInstitute_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route119_WeatherInstitute_2F_OnTransition
	.byte 0

Route119_WeatherInstitute_2F_OnTransition:
	call_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Route119_WeatherInstitute_2F_EventScript_SetScientistPosAquaHere
	call_if_eq VAR_WEATHER_INSTITUTE_STATE, 1, Route119_WeatherInstitute_2F_EventScript_SetScientistPosAquaGone
	call_if_set FLAG_SYS_GAME_CLEAR, Route119_WeatherInstitute_2F_EventScript_SetScientistPosGameClear
	end

Route119_WeatherInstitute_2F_EventScript_SetScientistPosAquaHere::
	setobjectxyperm LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, 1, 6
	setobjectmovementtype LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, MOVEMENT_TYPE_FACE_RIGHT
	return

Route119_WeatherInstitute_2F_EventScript_SetScientistPosAquaGone::
	setobjectxyperm LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, 4, 6
	setobjectmovementtype LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, MOVEMENT_TYPE_FACE_RIGHT
	return

Route119_WeatherInstitute_2F_EventScript_SetScientistPosGameClear::
	setobjectxyperm LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, 2, 2
	setobjectmovementtype LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, MOVEMENT_TYPE_FACE_UP
	return

Route119_WeatherInstitute_2F_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_5, Route119_WeatherInstitute_2F_Text_Grunt5Intro, Route119_WeatherInstitute_2F_Text_Grunt5Defeat
	msgbox Route119_WeatherInstitute_2F_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_2F_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_2, Route119_WeatherInstitute_2F_Text_Grunt2Intro, Route119_WeatherInstitute_2F_Text_Grunt2Defeat
	msgbox Route119_WeatherInstitute_2F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_2F_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_3, Route119_WeatherInstitute_2F_Text_Grunt3Intro, Route119_WeatherInstitute_2F_Text_Grunt3Defeat
	msgbox Route119_WeatherInstitute_2F_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_2F_EventScript_Shelly::
	trainerbattle_single TRAINER_SHELLY_WEATHER_INSTITUTE, Route119_WeatherInstitute_2F_Text_ShellyIntro, Route119_WeatherInstitute_2F_Text_ShellyDefeat, Route119_WeatherInstitute_2F_EventScript_ShellyDefeated
	msgbox Route119_WeatherInstitute_2F_Text_ShellyPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_2F_EventScript_ShellyDefeated::
	msgbox Route119_WeatherInstitute_2F_Text_ShellyPostBattle, MSGBOX_DEFAULT
	closemessage
	addobject LOCALID_WEATHER_INSTITUTE_2F_GRUNT_3
	applymovement LOCALID_WEATHER_INSTITUTE_2F_GRUNT_3, Route119_WeatherInstitute_2F_Movement_GruntApproachShelly
	applymovement LOCALID_PLAYER, Route119_WeatherInstitute_2F_Movement_ShovePlayerOutOfWay
	waitmovement 0
	msgbox Route119_WeatherInstitute_2F_Text_TeamMagmaJustPassedBy, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_WEATHER_INSTITUTE_2F_SHELLY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WEATHER_INSTITUTE_2F_SHELLY, Common_Movement_Delay48
	waitmovement 0
	msgbox Route119_WeatherInstitute_2F_Text_WeHaveToHurryToMtPyre, MSGBOX_DEFAULT
	closemessage
	setvar VAR_WEATHER_INSTITUTE_STATE, 1
	clearflag FLAG_HIDE_WEATHER_INSTITUTE_2F_WORKERS
	fadedefaultbgm
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_ROUTE_119_TEAM_AQUA
	setflag FLAG_HIDE_WEATHER_INSTITUTE_2F_AQUA_GRUNT_M
	removeobject LOCALID_WEATHER_INSTITUTE_2F_GRUNT_1
	removeobject LOCALID_WEATHER_INSTITUTE_2F_GRUNT_2
	removeobject LOCALID_WEATHER_INSTITUTE_2F_SHELLY
	removeobject LOCALID_WEATHER_INSTITUTE_2F_GRUNT_4
	removeobject LOCALID_WEATHER_INSTITUTE_2F_GRUNT_3
	applymovement LOCALID_PLAYER, Route119_WeatherInstitute_2F_Movement_PlayerReturnToPosition
	waitmovement 0
	fadescreen FADE_FROM_BLACK
	applymovement LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST, Route119_WeatherInstitute_2F_Movement_ScientistApproachPlayer
	waitmovement 0
	copyobjectxytoperm LOCALID_WEATHER_INSTITUTE_2F_SCIENTIST
	goto Route119_WeatherInstitute_2F_EventScript_ReceiveCastform
	end

Route119_WeatherInstitute_2F_EventScript_ReceiveCastform::
	msgbox Route119_WeatherInstitute_2F_Text_ThanksPleaseTakePokemon, MSGBOX_DEFAULT
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CASTFORM_NORMAL
	givemon SPECIES_CASTFORM_NORMAL, 25, ITEM_MYSTIC_WATER
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, Route119_WeatherInstitute_2F_EventScript_ReceiveCastformParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, Route119_WeatherInstitute_2F_EventScript_ReceiveCastformPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

Route119_WeatherInstitute_2F_EventScript_ReceiveCastformParty::
	call Route119_WeatherInstitute_2F_EventScript_ReceivedCastformFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route119_WeatherInstitute_2F_EventScript_ExplainCastform
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto Route119_WeatherInstitute_2F_EventScript_ExplainCastform
	end

Route119_WeatherInstitute_2F_EventScript_ReceiveCastformPC::
	call Route119_WeatherInstitute_2F_EventScript_ReceivedCastformFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route119_WeatherInstitute_2F_EventScript_SendCastformToPC
	call Common_EventScript_NameReceivedBoxMon
	goto Route119_WeatherInstitute_2F_EventScript_SendCastformToPC
	end

Route119_WeatherInstitute_2F_EventScript_SendCastformToPC::
	call Common_EventScript_TransferredToPC
	goto Route119_WeatherInstitute_2F_EventScript_ExplainCastform
	end

Route119_WeatherInstitute_2F_EventScript_ReceivedCastformFanfare::
	playfanfare MUS_OBTAIN_ITEM
	message Route119_WeatherInstitute_2F_Text_PlayerReceivedCastform
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_CASTFORM_NORMAL
	return

Route119_WeatherInstitute_2F_EventScript_ExplainCastform::
	msgbox Route119_WeatherInstitute_2F_Text_PokemonChangesWithWeather, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_CASTFORM
	release
	end

Route119_WeatherInstitute_2F_EventScript_ScientistMentionWeather::
	goto_if_set FLAG_SYS_GAME_CLEAR, Route119_WeatherInstitute_2F_EventScript_TryStartAbnormalWeather
	msgbox Route119_WeatherInstitute_2F_Text_ChangingWeatherRidiculous, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_2F_EventScript_TryStartAbnormalWeather::
	setvar VAR_0x8004, 0
	call_if_set FLAG_DEFEATED_KYOGRE, Route119_WeatherInstitute_2F_EventScript_LegendaryDefeated
	call_if_set FLAG_DEFEATED_GROUDON, Route119_WeatherInstitute_2F_EventScript_LegendaryDefeated
	goto_if_eq VAR_0x8004, 2, Route119_WeatherInstitute_2F_EventScript_NoAbnormalWeather  @ Both defeated
	call_if_unset FLAG_TEMP_2, Route119_WeatherInstitute_2F_EventScript_CreateAbnormalWeather
	specialvar VAR_RESULT, GetAbnormalWeatherMapNameAndType
	goto_if_eq VAR_RESULT, 1, Route119_WeatherInstitute_2F_EventScript_KyogreWeather
	msgbox Route119_WeatherInstitute_2F_Text_GroudonWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_2F_EventScript_KyogreWeather::
	msgbox Route119_WeatherInstitute_2F_Text_KyogreWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_2F_EventScript_CreateAbnormalWeather::
	special CreateAbnormalWeatherEvent
	setflag FLAG_TEMP_2
	return

Route119_WeatherInstitute_2F_EventScript_LegendaryDefeated::
	addvar VAR_0x8004, 1
	return

Route119_WeatherInstitute_2F_EventScript_NoAbnormalWeather::
	msgbox Route119_WeatherInstitute_2F_Text_NoAbnormalWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_2F_Movement_GruntApproachShelly:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

Route119_WeatherInstitute_2F_Movement_ShovePlayerOutOfWay:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	ride_water_current_up
	walk_in_place_faster_down
	step_end

Route119_WeatherInstitute_2F_Movement_PlayerReturnToPosition:
	slide_down
	walk_in_place_faster_left
	step_end

Route119_WeatherInstitute_2F_Movement_ScientistApproachPlayer:
	walk_right
	walk_right
	walk_right
	step_end

Route119_WeatherInstitute_2F_EventScript_WeatherScientist::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CASTFORM, Route119_WeatherInstitute_2F_EventScript_ScientistMentionWeather
	goto Route119_WeatherInstitute_2F_EventScript_ReceiveCastform
	end

Route119_WeatherInstitute_2F_Text_Grunt2Intro:
	.string "INSTITUT ini menciptakan jenis\n"
	.string "POKéMON yang berhubungan dengan\l"
	.string "cuaca. Kami di sini untuk mengambilnya!$"

Route119_WeatherInstitute_2F_Text_Grunt2Defeat:
	.string "Rencana kami digagalkan oleh anak kecil?$"

Route119_WeatherInstitute_2F_Text_Grunt2PostBattle:
	.string "Jika POKéMON yang mereka buat di sini bisa\n"
	.string "mengendalikan cuaca dengan bebas, maka kami\l"
	.string "dari TIM AQUA pasti membutuhkannya!$"

Route119_WeatherInstitute_2F_Text_Grunt3Intro:
	.string "Kami TIM AQUA!\n"
	.string "Kami muncul di mana pun ada sesuatu\l"
	.string "yang langka ditemukan!$"

Route119_WeatherInstitute_2F_Text_Grunt3Defeat:
	.string "Kamu berhasil mengalahkanku!$"

Route119_WeatherInstitute_2F_Text_Grunt3PostBattle:
	.string "Kamu tidak tahu apa yang sedang\n"
	.string "diusahakan oleh TIM AQUA!\l"
	.string "Jangan menghalangi jalan kami!$"

Route119_WeatherInstitute_2F_Text_Grunt5Intro:
	.string "Jangan bilang kamu juga mencari\n"
	.string "POKéMON cuaca itu?\p"
	.string "Tidak boleh!\n"
	.string "Kami di sini untuk mendapatkannya duluan!$"

Route119_WeatherInstitute_2F_Text_Grunt5Defeat:
	.string "Oh, lihatlah POKéMON-ku?$"

Route119_WeatherInstitute_2F_Text_Grunt5PostBattle:
	.string "Hmph, jadi kenapa?\n"
	.string "Apa yang kami inginkan…\p"
	.string "Apa yang benar-benar kami inginkan tidak ada di sini…\n"
	.string "Ihihihihi…$"

Route119_WeatherInstitute_2F_Text_ShellyIntro:
	.string "Ahahahaha!\p"
	.string "Kamu akan ikut campur dalam urusan\n"
	.string "TIM AQUA?\p"
	.string "Kamu benar-benar tidak takut,\n"
	.string "bodoh, atau keduanya!\p"
	.string "Kamu sangat lucu, sampai menjijikkan!\n"
	.string "Akan kubungkam kamu, anak kecil!$"

Route119_WeatherInstitute_2F_Text_ShellyDefeat:
	.string "Ahahahaha!\n"
	.string "Kamu menjijikkan kuatnya!$"

Route119_WeatherInstitute_2F_Text_ShellyPostBattle:
	.string "Sudah cukup buruk TIM MAGMA\n"
	.string "berbuat kesalahan, tapi sekarang ada kamu!\p"
	.string "Apa yang membuatmu ingin mengintip\n"
	.string "urusan kami, sih?$"

Route119_WeatherInstitute_2F_Text_TeamMagmaJustPassedBy:
	.string "Ada situasi di sini!\p"
	.string "Gerombolan TIM MAGMA baru saja melewati\n"
	.string "INSTITUT CUACA.\p"
	.string "Mereka tampaknya menuju\n"
	.string "GUNUNG PYRE!$"

Route119_WeatherInstitute_2F_Text_WeHaveToHurryToMtPyre:
	.string "Apa?!\p"
	.string "Kita tidak bisa membuang waktu lagi di sini!\n"
	.string "Kita juga harus segera ke GUNUNG PYRE!\p"
	.string "Ahahahaha!\n"
	.string "TIM MAGMA, tunggu saja!$"

Route119_WeatherInstitute_2F_Text_ThanksPleaseTakePokemon:
	.string "Terima kasih!\n"
	.string "Berkat kamu, kami aman!\p"
	.string "Mungkin ini cara yang aneh untuk berterima kasih,\n"
	.string "tapi ambillah POKéMON ini.$"

@ Unused
Route119_WeatherInstitute_2F_Text_NoRoomForPokemon:
	.string "Hm? Kamu sepertinya tidak punya tempat\n"
	.string "untuk POKéMON ini.$"

Route119_WeatherInstitute_2F_Text_PlayerReceivedCastform:
	.string "{PLAYER} mendapatkan CASTFORM!$"

Route119_WeatherInstitute_2F_Text_PokemonChangesWithWeather:
	.string "POKéMON itu berubah bentuk sesuai\n"
	.string "dengan kondisi cuaca.\p"
	.string "Ada banyak di INSTITUT ini-silakan\n"
	.string "ambil saja.$"

Route119_WeatherInstitute_2F_Text_ChangingWeatherRidiculous:
	.string "Aku telah meneliti hujan selama bertahun-tahun,\n"
	.string "tetapi konyol rasanya berpikir bahwa\l"
	.string "manusia bisa mengubah cuaca sesuka hati.$"

Route119_WeatherInstitute_2F_Text_GroudonWeather:
	.string "Aku melacak pola cuaca di\n"
	.string "wilayah HOENN.\p"
	.string "Saat ini, kekeringan telah tercatat\n"
	.string "di {STR_VAR_1}.\p"
	.string "Mungkinkah itu berarti, di suatu tempat dekat\n"
	.string "{STR_VAR_1}…$"

Route119_WeatherInstitute_2F_Text_KyogreWeather:
	.string "Aku melacak pola cuaca di\n"
	.string "wilayah HOENN.\p"
	.string "Saat ini, curah hujan tinggi telah\n"
	.string "tercatat di {STR_VAR_1}.\p"
	.string "Mungkinkah itu berarti, di suatu tempat dekat\n"
	.string "{STR_VAR_1}…$"

Route119_WeatherInstitute_2F_Text_NoAbnormalWeather:
	.string "Kondisi cuaca abnormal tidak\n"
	.string "lagi dilaporkan.\p"
	.string "Curah hujan sesekali adalah berkah,\n"
	.string "sungguh.$"

