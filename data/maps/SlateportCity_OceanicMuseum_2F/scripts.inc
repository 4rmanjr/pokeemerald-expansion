SlateportCity_OceanicMuseum_2F_MapScripts::
	.byte 0

SlateportCity_OceanicMuseum_2F_EventScript_CaptStern::
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, TRUE
	addobject LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter
	waitmovement 0
	addobject LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter
	waitmovement 0
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach
	waitmovement 0
	call_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts
	call_if_eq VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts
	msgbox SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts, MSGBOX_DEFAULT
	call_if_ne VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou, MSGBOX_DEFAULT
	msgbox SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	call_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth
	call_if_eq VAR_FACING, DIR_WEST, SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest
	trainerbattle_no_intro TRAINER_GRUNT_MUSEUM_1, SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat
	msgbox SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_MUSEUM_2, SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_MeddlingKid, MSGBOX_DEFAULT
	closemessage
	delay 35
	addobject LOCALID_OCEANIC_MUSEUM_2F_ARCHIE
	applymovement LOCALID_OCEANIC_MUSEUM_2F_ARCHIE, SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OCEANIC_MUSEUM_2F_ARCHIE, SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_ArchieWarning, MSGBOX_DEFAULT
	closemessage
	savebgm MUS_DUMMY
	fadedefaultbgm
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_OCEANIC_MUSEUM_2F_ARCHIE
	removeobject LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1
	removeobject LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2
	fadescreen FADE_FROM_BLACK
	delay 30
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_AQUA_GRUNTS
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs, MSGBOX_DEFAULT
	setvar VAR_0x8004, ITEM_DEVON_PARTS
	call Common_EventScript_PlayerHandedOverTheItem
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	removeobject LOCALID_OCEANIC_MUSEUM_2F_CAPT_STERN
	setflag FLAG_HIDE_ROUTE_110_TEAM_AQUA
	call_if_eq VAR_REGISTER_BIRCH_STATE, 0, SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch
	setflag FLAG_DELIVERED_DEVON_GOODS
	clearflag FLAG_HIDE_ROUTE_116_DEVON_EMPLOYEE
	setflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_EMPLOYEE
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1
	fadescreen FADE_FROM_BLACK
	release
	end

SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch::
	setvar VAR_REGISTER_BIRCH_STATE, 1
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts::
	applymovement LOCALID_OCEANIC_MUSEUM_2F_CAPT_STERN, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth::
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest::
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth:
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest:
	walk_up
	walk_left
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_Unused:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	delay_8
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer:
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle:
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter:
	walk_down
	walk_right
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated:
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter:
	walk_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	walk_fast_down
	walk_in_place_faster_up
	step_end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample1::
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample2::
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_PressureExperiment::
	msgbox SlateportCity_OceanicMuseum_2F_Text_PressureExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_HoennModel::
	msgbox SlateportCity_OceanicMuseum_2F_Text_HoennModel, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_DeepSeawaterDisplay::
	msgbox SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SurfaceSeawaterDisplay::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSTidalReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmarineReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmersibleReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSAnneReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron1::
	msgbox SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron2::
	msgbox SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron3::
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts:
	.string "Ya? Jika kamu mencari STERN,\n"
	.string "itu aku.\p"
	.string "Ah! Itu pasti suku cadang yang aku pesan\n"
	.string "dari TUAN STONE dari DEVON.\p"
	.string "Terima kasih! Itu bagus sekali!\n"
	.string "Kita bisa bersiap untuk ekspedisi sekarang.$"

SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts:
	.string "Hehehe, tunggu!\n"
	.string "Kami akan mengambil suku cadang itu!$"

SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou:
	.string "KAPTEN STERN: A-apa?\n"
	.string "Siapa kalian ini?$"

SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua:
	.string "Kami TEAM AQUA!\p"
	.string "BOS kami menginginkan suku cadang itu!\n"
	.string "Tutup mulutmu dan serahkan!$"

SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat:
	.string "Awaaaah!\n"
	.string "Seorang anak mengalahkanku!$"

SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious:
	.string "Oh, astaga, bencana apa ini…\n"
	.string "BOS pasti akan sangat marah…$"

SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis:
	.string "Huh, pengecut cengeng!\n"
	.string "Biar aku yang mengurus ini!$"

SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat:
	.string "Apa?!\n"
	.string "Aku juga kalah!$"

SlateportCity_OceanicMuseum_2F_Text_MeddlingKid:
	.string "Sekarang bagaimana? Jika kita tidak\n"
	.string "mendapatkan suku cadang, kita akan celaka!\p"
	.string "Arrgh, aku tidak menyangka akan\n"
	.string "diganggu oleh anak nakal ini!$"

SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong:
	.string "Aku datang untuk melihat mengapa\n"
	.string "begitu lama untuk merebut suku cadang, dan\l"
	.string "kalian para pengecut ditahan oleh seorang anak kecil?$"

SlateportCity_OceanicMuseum_2F_Text_ArchieWarning:
	.string "Kami adalah TEAM AQUA,\n"
	.string "dan kami mencintai laut!\p"
	.string "Dan aku adalah pemimpin TEAM AQUA,\n"
	.string "ARCHIE!\p"
	.string "Apa yang membuatmu ikut campur dengan kami?\p"
	.string "…Tidak! Tidak mungkin!\n"
	.string "Kamu bukan salah satu dari TEAM MAGMA?\p"
	.string "Tunggu, itu tidak mungkin benar.\n"
	.string "Kamu tidak berpakaian seperti itu.\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "POKéMON, manusia… Semua kehidupan\n"
	.string "bergantung pada laut.\p"
	.string "Jadi, TEAM AQUA berdedikasi untuk\n"
	.string "perluasan laut.\p"
	.string "Tidakkah kamu setuju? Apa yang kami\n"
	.string "lakukan adalah usaha yang luar biasa.\p"
	.string "Ah, baiklah…\n"
	.string "Kamu masih terlalu muda untuk memahami\l"
	.string "tujuan mulia kami.\p"
	.string "Tapi, aku peringatkan kamu, jangan\n"
	.string "pernah berpikir untuk mengganggu rencana kami lagi.\p"
	.string "Konsekuensinya akan sangat mahal\n"
	.string "bagimu!\p"
	.string "Dan jangan lupakan itu!$"

SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs:
	.string "KAPTEN STERN: Kamu…\n"
	.string "Ah, oke, kamu {PLAYER}{KUN}…\p"
	.string "Bagaimanapun, itu situasi yang tegang!\n"
	.string "Terima kasih telah menyelamatkan kami!\p"
	.string "Oh, ya, aku hampir lupa bahwa kamu\n"
	.string "bahkan membawa suku cadang dari DEVON!$"

SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo:
	.string "KAPTEN STERN: Ups!\n"
	.string "Tidak ada waktu untuk disia-siakan!\p"
	.string "Kami harus segera berangkat untuk\n"
	.string "ekspedisi dasar laut kami.\p"
	.string "Terima kasih lagi, tapi sekarang aku\n"
	.string "harus pergi!\p"
	.string "Silakan berkeliling dan lihat\n"
	.string "fasilitas kami.$"

SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip:
	.string "Aku melihat model kapal di sini.\p"
	.string "Itu mengingatkanku pada ABANDONED SHIP\n"
	.string "dekat DEWFORD TOWN…$"

SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum:
	.string "Jangan berani-beraninya berlari di dalam\n"
	.string "MUSEUM!$"

SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine:
	.string "Wow, kapal selamnya luar biasa!\n"
	.string "Aku ingin naik!$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1:
	.string "“SAMPEL KUALITAS AIR 1,” begitu\n"
	.string "labelnya.\p"
	.string "Laut itu semua terhubung, tetapi\n"
	.string "airnya sepertinya berbeda di setiap wilayah.$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2:
	.string "“SAMPEL KUALITAS AIR 2,” begitu\n"
	.string "labelnya.\p"
	.string "Apakah keasinan air laut juga\n"
	.string "berbeda di setiap wilayah?$"

SlateportCity_OceanicMuseum_2F_Text_PressureExperiment:
	.string "Sebuah bola karet mengembang dan\n"
	.string "menyusut.\p"
	.string "“Di laut, berat air itu sendiri\n"
	.string "memberikan tekanan.\p"
	.string "“Di perairan dangkal, tekanannya tidak\n"
	.string "terlalu berat.\p"
	.string "“Namun, di perairan yang sangat dalam,\n"
	.string "tekanan bisa mencapai puluhan ribu\l"
	.string "ton pada area kecil.”$"

SlateportCity_OceanicMuseum_2F_Text_HoennModel:
	.string "“MODEL WILAYAH HOENN”\p"
	.string "Ini adalah diorama miniatur wilayah\n"
	.string "HOENN.\p"
	.string "Di mana LITTLEROOT TOWN di sini?$"

SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay:
	.string "Ini adalah tampilan aliran air laut.\p"
	.string "“Dekat dasar laut, air mengalir\n"
	.string "karena perbedaan faktor-faktor seperti\l"
	.string "suhu dan salinitas.”$"

SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay:
	.string "Ini adalah tampilan aliran air laut.\p"
	.string "“Menuju permukaan, air laut mengalir\n"
	.string "sebagai arus yang didorong oleh angin.”$"

SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica:
	.string "“FERI S.S. TIDAL\p"
	.string "“Replika skala kapal yang sedang\n"
	.string "dibangun di GALANGAN KAPAL STERN.”$"

SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica:
	.string "“SUBMARINE EXPLORER 1\p"
	.string "“Replika kapal selam eksplorasi dasar\n"
	.string "laut berkinerja tinggi.”$"

SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica:
	.string "“SUBMERSIBLE POD\p"
	.string "“Replika pod ringkas tanpa awak\n"
	.string "untuk eksplorasi dasar laut.”$"

SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica:
	.string "“S.S. ANNE\p"
	.string "“Replika kapal pesiar mewah yang\n"
	.string "mengelilingi dunia.”$"
