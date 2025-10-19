Route114_FossilManiacsTunnel_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_FossilManiacsTunnel_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route114_FossilManiacsTunnel_OnLoad
	.byte 0

Route114_FossilManiacsTunnel_OnTransition:
	call_if_set FLAG_SYS_GAME_CLEAR, Route114_FossilManiacsTunnel_EventScript_MoveFossilManiac
	end

Route114_FossilManiacsTunnel_EventScript_MoveFossilManiac::
	setobjectxyperm LOCALID_FOSSIL_MANIAC, 6, 5
	setobjectmovementtype LOCALID_FOSSIL_MANIAC, MOVEMENT_TYPE_FACE_DOWN
	return

Route114_FossilManiacsTunnel_OnLoad:
	call_if_unset FLAG_SYS_GAME_CLEAR, Route114_FossilManiacsTunnel_EventScript_CloseDesertUnderpass
	end

Route114_FossilManiacsTunnel_EventScript_CloseDesertUnderpass::
	setmetatile 6, 1, METATILE_Fallarbor_RedRockWall, TRUE
	setmetatile 6, 2, METATILE_Fallarbor_RedRockWall, TRUE
	return

Route114_FossilManiacsTunnel_EventScript_ManiacMentionCaveIn::
	lockall
	applymovement LOCALID_FOSSIL_MANIAC, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox Route114_FossilManiacsTunnel_Text_NotSafeThatWay, MSGBOX_DEFAULT
	setvar VAR_FOSSIL_MANIAC_STATE, 2
	releaseall
	end

Route114_FossilManiacsTunnel_EventScript_FossilManiac::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_REVIVED_FOSSIL_MON, Route114_FossilManiacsTunnel_EventScript_PlayerRevivedFossil
	checkitem ITEM_ROOT_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil
	checkitem ITEM_CLAW_FOSSIL
	goto_if_eq VAR_RESULT, TRUE, Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil
	msgbox Route114_FossilManiacsTunnel_Text_LookInDesertForFossils, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_EventScript_PlayerHasFossil::
	msgbox Route114_FossilManiacsTunnel_Text_DevonCorpRevivingFossils, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_EventScript_PlayerRevivedFossil::
	msgbox Route114_FossilManiacsTunnel_Text_FossilsAreWonderful, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsTunnel_Text_LookInDesertForFossils:
	.string "Aku FOSSIL MANIAC…\n"
	.string "Aku orang baik yang menyukai FOSSIL…\p"
	.string "Kamu mau FOSSIL?\p"
	.string "Tapi FOSSIL di sekitar sini\n"
	.string "milikku semua… Tidak ada untukmu…\p"
	.string "Jika kamu tidak bisa hidup tanpa\n"
	.string "FOSSIL, carilah di gurun yang ada\l"
	.string "batu-batu besar dan pasir yang mungkin\l"
	.string "menyembunyikan FOSSIL…$"

Route114_FossilManiacsTunnel_Text_DevonCorpRevivingFossils:
	.string "Kamu menemukan FOSSIL, kan?\n"
	.string "Itu bagus sekali… Sangat indah…\p"
	.string "Apa yang akan kamu lakukan dengan\n"
	.string "FOSSIL itu?\p"
	.string "Dari yang kudengar, DEVON sedang\n"
	.string "melakukan penelitian untuk menghidupkan\l"
	.string "kembali POKéMON dari FOSSIL…\p"
	.string "Aku sangat menyukai FOSSIL-ku, jadi aku\n"
	.string "tidak akan pernah melakukan hal seperti itu…$"

Route114_FossilManiacsTunnel_Text_FossilsAreWonderful:
	.string "FOSSIL sangat… Menakjubkan…\n"
	.string "Sangat indah…$"

Route114_FossilManiacsTunnel_Text_NotSafeThatWay:
	.string "Oh…\n"
	.string "Jalan itu tidak aman…\p"
	.string "Aku sedang menggali, kamu tahu…\n"
	.string "Saat seluruh dinding runtuh…\p"
	.string "Kurasa sekarang ada gua raksasa\n"
	.string "di bawah sana…\p"
	.string "Tapi aku membiarkannya karena kurasa\n"
	.string "tidak ada FOSSIL di sana…$"

