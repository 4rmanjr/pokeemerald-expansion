Route116_TunnelersRestHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route116_TunnelersRestHouse_OnTransition
	.byte 0

Route116_TunnelersRestHouse_OnTransition:
	setflag FLAG_LANDMARK_TUNNELERS_REST_HOUSE
	end

Route116_TunnelersRestHouse_EventScript_Tunneler1::
	msgbox Route116_TunnelersRestHouse_Text_WeHadToStopBoring, MSGBOX_NPC
	end

Route116_TunnelersRestHouse_EventScript_Tunneler2::
	msgbox Route116_TunnelersRestHouse_Text_ManDiggingHisWayToVerdanturf, MSGBOX_NPC
	end

Route116_TunnelersRestHouse_EventScript_Tunneler3::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, Route116_TunnelersRestHouse_EventScript_TunnelOpened
	msgbox Route116_TunnelersRestHouse_Text_GetToVerdanturfWithoutTunnel, MSGBOX_DEFAULT
	release
	end

Route116_TunnelersRestHouse_EventScript_TunnelOpened::
	msgbox Route116_TunnelersRestHouse_Text_TunnelHasGoneThrough, MSGBOX_DEFAULT
	release
	end

Route116_TunnelersRestHouse_Text_WeHadToStopBoring:
	.string "Terowongan RUSTURF itu…\p"
	.string "Awalnya, kami punya kru besar yang\n"
	.string "mengebor batu dengan mesin terbaru.\l"
	.string "Tapi, kami harus berhenti.\p"
	.string "Ternyata kami akan memberikan dampak\n"
	.string "negatif pada POKéMON liar di\l"
	.string "daerah itu.\p"
	.string "Jadi, kami tidak punya pekerjaan lain\n"
	.string "selain bermalas-malasan di sini.$"

Route116_TunnelersRestHouse_Text_ManDiggingHisWayToVerdanturf:
	.string "Ada seorang pria yang menggali jalannya\n"
	.string "ke VERDANTURF sendirian.\l"
	.string "Dia sangat ingin lewat.\p"
	.string "Dia bilang kalau dia menggali sedikit\n"
	.string "demi sedikit tanpa menggunakan mesin,\l"
	.string "dia tidak akan mengganggu POKéMON,\l"
	.string "dan dia akan menghindari merusak\l"
	.string "lingkungan alam.\p"
	.string "Aku ingin tahu apakah dia sudah berhasil\n"
	.string "lewat.$"

Route116_TunnelersRestHouse_Text_GetToVerdanturfWithoutTunnel:
	.string "Untuk sampai ke VERDANTURF tanpa\n"
	.string "menggunakan TEROWONGAN ini, kamu harus\l"
	.string "menyeberangi laut ke DEWFORD, berlayar\l"
	.string "ke SLATEPORT, lalu melewati MAUVILLE.$"

Route116_TunnelersRestHouse_Text_TunnelHasGoneThrough:
	.string "Apa kamu dengar? TEROWONGAN ke VERDANTURF\n"
	.string "sudah tembus!\p"
	.string "Terkadang, jika kamu berharap dengan\n"
	.string "sangat kuat, mimpi bisa jadi kenyataan.$"

