SlateportCity_OceanicMuseum_1F_MapScripts::
	.byte 0

SlateportCity_OceanicMuseum_1F_EventScript_EntranceAttendant::
	msgbox SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFeeLeft::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFeeRight::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee::
	showmoneybox 0, 0
	msgbox SlateportCity_OceanicMuseum_1F_Text_WouldYouLikeToEnter, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_OceanicMuseum_1F_EventScript_CheckMoneyForFee
	closemessage
	hidemoneybox
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_CheckMoneyForFee::
	checkmoney 50
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_OceanicMuseum_1F_EventScript_NotEnoughMoney
	playse SE_SHOP
	removemoney 50
	updatemoneybox
	msgbox SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 1
	hidemoneybox
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_NotEnoughMoney::
	goto_if_unset FLAG_DELIVERED_DEVON_GOODS, SlateportCity_OceanicMuseum_1F_EventScript_AllowEntranceAnyway
	msgbox SlateportCity_OceanicMuseum_1F_Text_NotEnoughMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_AllowEntranceAnyway::
	msgbox SlateportCity_OceanicMuseum_1F_Text_CatchUpWithYourGroup, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 1
	hidemoneybox
	releaseall
	end

SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter:
	walk_down
	step_end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_AquaExistForGoodOfAll, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OurBossIsntHere, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WouldStuffHereMakeMeRich, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt4::
	msgbox SlateportCity_OceanicMuseum_1F_Text_CanLearnForNefariousDeeds, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt5::
	msgbox SlateportCity_OceanicMuseum_1F_Text_RustboroBungled, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt6::
	msgbox SlateportCity_OceanicMuseum_1F_Text_DidntHaveMoney, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_WhirlpoolExperiment::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WhirlpoolExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_WaterfallExperiment::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WaterfallExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanSoilDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanSoilDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_BeachSandDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_BeachSandDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact1, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact2, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact3, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_FossilDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_FossilDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_DepthMeasuringMachine::
	msgbox SlateportCity_OceanicMuseum_1F_Text_DepthMeasuringMachine, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_LearnAboutSeaForBattling, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_SternIsRoleModel, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_MustBePokemonWeDontKnow, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron4::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WantSeaPokemon, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGrunt::
	lock
	faceplayer
	delay 8
	playse SE_PIN
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, Common_Movement_Delay48
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_1F_Text_RememberMeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_THIEF
	goto_if_eq VAR_RESULT, 0, SlateportCity_OceanicMuseum_1F_EventScript_NoRoomForThief
	setflag FLAG_RECEIVED_TM_THIEF
	msgbox SlateportCity_OceanicMuseum_1F_Text_HopeINeverSeeYouAgain, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_FACING, DIR_NORTH, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitNorth
	goto_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitSouth
	goto_if_eq VAR_FACING, DIR_WEST, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast
	goto_if_eq VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitNorth::
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitNorth
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExitNorth
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitSouth::
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast::
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitWestEast
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited::
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_FAMILIAR_AQUA_GRUNT
	playse SE_EXIT
	removeobject LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT
	release
	end

SlateportCity_OceanicMuseum_1F_EventScript_NoRoomForThief::
	msgbox SlateportCity_OceanicMuseum_1F_Text_YouHaveToTakeThis, MSGBOX_DEFAULT
	release
	end

SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitNorth:
	delay_16
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitWestEast:
	delay_16
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit:
	face_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	delay_8
	step_end

SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExitNorth:
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	delay_8
	step_end

SlateportCity_OceanicMuseum_1F_Text_WouldYouLikeToEnter:
	.string "Selamat datang di MUSEUM KELAUTAN.\p"
	.string "Biaya masuknya ¥50.\n"
	.string "Maukah kamu masuk?$"

SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself:
	.string "Silakan bersenang-senang.$"

SlateportCity_OceanicMuseum_1F_Text_NotEnoughMoney:
	.string "Oh? Maaf, tapi sepertinya kamu tidak\n"
	.string "punya cukup uang.$"

SlateportCity_OceanicMuseum_1F_Text_CatchUpWithYourGroup:
	.string "Oh? Kamu bersama rombongan yang\n"
	.string "masuk lebih awal?\p"
	.string "Kamu satu-satunya yang terlambat.\n"
	.string "Sebaiknya kamu segera menyusul mereka!$"

SlateportCity_OceanicMuseum_1F_Text_AquaExistForGoodOfAll:
	.string "Kami, TEAM AQUA, ada untuk kebaikan\n"
	.string "semua!$"

SlateportCity_OceanicMuseum_1F_Text_OurBossIsntHere:
	.string "Kami disuruh berkumpul di sini,\n"
	.string "jadi kami melakukannya, tapi…\p"
	.string "BOS kami, tulang punggungnya, tidak ada di sini.$"

SlateportCity_OceanicMuseum_1F_Text_WouldStuffHereMakeMeRich:
	.string "Jika aku mencuri barang-barang di sini,\n"
	.string "apakah itu akan membuatku kaya?$"

SlateportCity_OceanicMuseum_1F_Text_CanLearnForNefariousDeeds:
	.string "Apa yang aku pelajari di sini, bisa\n"
	.string "aku gunakan untuk perbuatan jahat…$"

SlateportCity_OceanicMuseum_1F_Text_RustboroBungled:
	.string "Jika anak buah kami tidak mengacau\n"
	.string "di RUSTBORO, kami tidak akan ada di sini!$"

SlateportCity_OceanicMuseum_1F_Text_DidntHaveMoney:
	.string "Aku tidak punya ¥50, jadi butuh waktu\n"
	.string "lama untuk melewati resepsionis.$"

SlateportCity_OceanicMuseum_1F_Text_LearnAboutSeaForBattling:
	.string "Aku ingin belajar tentang laut dan\n"
	.string "menggunakan pengetahuan itu untuk bertarung.$"

SlateportCity_OceanicMuseum_1F_Text_SternIsRoleModel:
	.string "Aku jadi sangat gembira dan lengket\n"
	.string "saat melihat laut!\p"
	.string "Bagiku, KAPTEN STERN adalah\n"
	.string "panutan nomor satu!$"

SlateportCity_OceanicMuseum_1F_Text_MustBePokemonWeDontKnow:
	.string "Laut itu luas tak berujung, dan\n"
	.string "sangat dalam…\p"
	.string "Pasti ada banyak POKéMON yang\n"
	.string "tidak kita ketahui.$"

SlateportCity_OceanicMuseum_1F_Text_WantSeaPokemon:
	.string "Aku ingin POKéMON laut.\p"
	.string "Menurutku akan terasa dingin dan menyenangkan\n"
	.string "untuk dipeluk.$"

SlateportCity_OceanicMuseum_1F_Text_RememberMeTakeThis:
	.string "Aiyeeeh!\n"
	.string "Apa yang kamu lakukan di sini?\p"
	.string "Aku? Aku anggota TEAM AQUA\n"
	.string "yang kamu kalahkan sebelumnya, ingat?\l"
	.string "Di RUSTURF TUNNEL?\p"
	.string "Ini, ambil ini!\n"
	.string "Kamu harus memaafkanku!$"

SlateportCity_OceanicMuseum_1F_Text_HopeINeverSeeYouAgain:
	.string "TM itu, lebih cocok untukmu\n"
	.string "daripada aku.\p"
	.string "Semoga aku tidak pernah melihatmu lagi!\n"
	.string "Wahahaha!$"

SlateportCity_OceanicMuseum_1F_Text_YouHaveToTakeThis:
	.string "Aww, ayolah!\n"
	.string "Kamu harus mengambil ini dan biarkan aku pergi!$"

SlateportCity_OceanicMuseum_1F_Text_WhirlpoolExperiment:
	.string "Cairan biru berputar di dalam\n"
	.string "wadah kaca.\p"
	.string "“Ini adalah percobaan untuk menciptakan\n"
	.string "WHIRLPOOL secara artifisial menggunakan angin.”$"

SlateportCity_OceanicMuseum_1F_Text_WaterfallExperiment:
	.string "Bola merah bergerak naik turun\n"
	.string "di dalam wadah kaca.\p"
	.string "“Ini adalah percobaan mensimulasikan\n"
	.string "AIR TERJUN menggunakan daya apung bola.”$"

SlateportCity_OceanicMuseum_1F_Text_OceanSoilDisplay:
	.string "Ini adalah sampel tanah dari dasar\n"
	.string "laut.\p"
	.string "“Selama bertahun-tahun, sisa-sisa\n"
	.string "makhluk hidup mengendap di dasar\l"
	.string "laut, membentuk lapisan sedimen.\p"
	.string "“Dengan menganalisis lapisan-lapisan ini,\n"
	.string "masa lalu kuno terungkap.”$"

SlateportCity_OceanicMuseum_1F_Text_BeachSandDisplay:
	.string "Ini adalah sampel pasir pantai.\p"
	.string "“Batu-batu dari gunung terbawa\n"
	.string "oleh sungai di mana mereka\l"
	.string "terkikis dan tergerus.\p"
	.string "“Mereka berkurang menjadi butiran dan\n"
	.string "berakhir sebagai pasir di pantai.”$"

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact1:
	.string "“MINIFAKTA KELAUTAN 1\n"
	.string "Mengapa air laut berwarna biru?\p"
	.string "“Cahaya terdiri dari banyak warna.\p"
	.string "“Ketika cahaya melewati air,\n"
	.string "sebagian besar jenis cahaya kehilangan warna.\p"
	.string "“Namun, cahaya biru mempertahankan\n"
	.string "warnanya, membuat laut tampak biru.”$"

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact2:
	.string "“MINIFAKTA KELAUTAN 2\n"
	.string "Mengapa laut asin?\p"
	.string "“Air laut mengandung garam terlarut\n"
	.string "dalam bentuk ion natrium dan klorin.\p"
	.string "“Ion-ion ini merembes keluar dari bebatuan\n"
	.string "dan terbawa ke laut oleh hujan.\p"
	.string "“Konsentrasi garam terlarut\n"
	.string "membuat laut asin.”$"

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact3:
	.string "“MINIFAKTA KELAUTAN 3\n"
	.string "Mana yang lebih besar? Laut atau daratan?\p"
	.string "“Laut menutupi sekitar 70% dari\n"
	.string "planet, dan sisanya adalah daratan.\p"
	.string "“Oleh karena itu, laut lebih dari dua kali\n"
	.string "ukuran daratan.”$"

SlateportCity_OceanicMuseum_1F_Text_FossilDisplay:
	.string "Ini adalah fosil dengan punggung bergelombang.\p"
	.string "“Tanah di dasar laut terkikis\n"
	.string "oleh pasang surut.\p"
	.string "“Air laut yang mengalir menandai tanah\n"
	.string "dengan punggung dan lembah kecil.\p"
	.string "“Jika tanah ini menjadi fosil, itu\n"
	.string "disebut tanda riak.”$"

SlateportCity_OceanicMuseum_1F_Text_DepthMeasuringMachine:
	.string "Sebuah mesin aneh berputar di bawah\n"
	.string "kubah kaca.\p"
	.string "Mungkin itu untuk mengukur kedalaman\n"
	.string "sesuatu…$"

