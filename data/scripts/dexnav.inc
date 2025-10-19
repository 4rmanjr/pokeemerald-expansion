EventScript_StartDexNavBattle::
	lock
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER Common_Movement_ExclamationMark
	waitmovement 0
	waitse
	dowildbattle	
	release
	end

EventScript_NotFoundNearby::
	msgbox sText_NotFoundNearby, MSGBOX_SIGN
	end

EventScript_MovedTooFast::
	msgbox sText_TryMovingSlower, MSGBOX_SIGN
	end

EventScript_PokemonGotAway::
	msgbox sText_PokemonGotAway, MSGBOX_SIGN
	end

EventScript_LostSignal::
	msgbox sText_LostSignal, MSGBOX_SIGN
	end

EventScript_TooDark::
	msgbox sText_TooDark, MSGBOX_SIGN
	end

sText_NotFoundNearby:
	.string "Tidak dapat ditemukan di dekat sini.\n"
	.string "Coba cari di area yang berbeda!$"

sText_TryMovingSlower:
	.string "POKéMON-nya kabur!\n"
	.string "Coba bergerak lebih pelan.$"

sText_PokemonGotAway:
	.string "POKéMON-nya kabur!$"

sText_LostSignal:
	.string "Tidak ada reaksi.\n"
	.string "Sinyal hilang!$"

sText_TooDark:
	.string "Terlalu gelap untuk mencari\nPOKéMON!$"

