VerdanturfTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_OnTransition
	.byte 0

VerdanturfTown_OnTransition:
	setflag FLAG_VISITED_VERDANTURF_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	end

VerdanturfTown_EventScript_Twin::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_TwinTunnelOpen
	msgbox VerdanturfTown_Text_ManTryingToDigTunnel, MSGBOX_DEFAULT
	applymovement LOCALID_VERDANTURF_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_TwinTunnelOpen::
	msgbox VerdanturfTown_Text_ManDugTunnelForLove, MSGBOX_DEFAULT
	applymovement LOCALID_VERDANTURF_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_Man::
	msgbox VerdanturfTown_Text_AirCleanHere, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Camper::
	msgbox VerdanturfTown_Text_MakeBattleTentDebut, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_BoyTunnelOpen
	msgbox VerdanturfTown_Text_GuyTryingToBustThroughCave, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_BoyTunnelOpen::
	msgbox VerdanturfTown_Text_EasyToGetToRustboroNow, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_TownSign::
	msgbox VerdanturfTown_Text_TownSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_WandasHouseSign::
	msgbox VerdanturfTown_Text_WandasHouse, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_BattleTentSign::
	msgbox VerdanturfTown_Text_BattleTentSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_RusturfTunnelSign::
	msgbox VerdanturfTown_Text_RusturfTunnelSign, MSGBOX_SIGN
	end

VerdanturfTown_Text_ManTryingToDigTunnel:
	.string "Papa saya memberitahu saya.\p"
	.string "Katanya terowongan ini penuh dengan\n"
	.string "POKéMON penakut.\p"
	.string "Mereka sangat takut suara keras dan\n"
	.string "membuat keributan besar.\p"
	.string "Jadi mereka harus menghentikan proyek\n"
	.string "terowongan besar itu.\p"
	.string "Tapi ada satu orang. Dia mencoba menggali\n"
	.string "terowongan itu sendirian!$"

VerdanturfTown_Text_ManDugTunnelForLove:
	.string "Ada seorang pria yang menggali terowongan\n"
	.string "untuk wanita yang dicintainya.\p"
	.string "Aku tidak begitu mengerti, tapi ya sudahlah!$"

VerdanturfTown_Text_AirCleanHere:
	.string "Cara angin bertiup, abu vulkanik\n"
	.string "tidak pernah tertiup ke arah ini.\p"
	.string "Udara di sini bersih dan segar.\n"
	.string "Tinggal di sini akan sangat bermanfaat\l"
	.string "bahkan untuk orang yang lemah dan sakit-sakitan.$"

VerdanturfTown_Text_MakeBattleTentDebut:
	.string "POKéMON-ku dan aku, kami sedang dalam\n"
	.string "rentetan kemenangan beruntun.\p"
	.string "Jadi aku memutuskan untuk melakukan\n"
	.string "debut BATTLE TENT-ku di kota ini.$"

VerdanturfTown_Text_GuyTryingToBustThroughCave:
	.string "Apakah kamu melihat gua di sebelah\n"
	.string "POKéMON MART?\p"
	.string "Ada seorang pria di sana yang mencoba\n"
	.string "menghancurkan batu-batu besar agar bisa\l"
	.string "keluar ke sisi lain.\p"
	.string "Akan sangat bagus jika kita bisa lewat…\n"
	.string "Itu akan memudahkan untuk mengunjungi RUSTBORO.$"

VerdanturfTown_Text_EasyToGetToRustboroNow:
	.string "Gua di sebelah POKéMON MART itu\n"
	.string "sekarang adalah terowongan ke sisi lain.\p"
	.string "Bagus sekali--sekarang mudah untuk berbelanja\n"
	.string "produk DEVON baru di RUSTBORO.$"

VerdanturfTown_Text_TownSign:
	.string "KOTA VERDANTURF\p"
	.string "“Dataran tinggi berangin dengan\n"
	.string "aroma rumput yang manis.”$"

VerdanturfTown_Text_WandasHouse:
	.string "WANDA'S HOUSE$"

VerdanturfTown_Text_BattleTentSign:
	.string "BATTLE TENT LOKASI VERDANTURF\n"
	.string "“Manjakan Matamu dengan Pertarungan!”$"

VerdanturfTown_Text_RusturfTunnelSign:
	.string "TEROWONGAN RUSTURF\n"
	.string "“Menghubungkan RUSTBORO dan VERDANTURF\p"
	.string "“Proyek terowongan telah\n"
	.string "dibatalkan.”$"

