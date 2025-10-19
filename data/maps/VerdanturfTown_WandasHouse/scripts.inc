VerdanturfTown_WandasHouse_MapScripts::
	.byte 0

VerdanturfTown_WandasHouse_EventScript_Wally::
	lock
	faceplayer
	goto_if_set FLAG_WALLY_SPEECH, VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeech, MSGBOX_DEFAULT
	setflag FLAG_WALLY_SPEECH
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech::
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeechShort, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff
	msgbox VerdanturfTown_WandasHouse_Text_WallysNextDoor, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff::
	msgbox VerdanturfTown_WandasHouse_Text_WallySlippedOff, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyGoneThatFar, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandasBoyfriend::
	msgbox VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay, MSGBOX_NPC
	end

VerdanturfTown_WandasHouse_EventScript_Wanda::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WandaDontWorry
	goto_if_set FLAG_DEFEATED_WALLY_MAUVILLE, VerdanturfTown_WandasHouse_EventScript_MeetWanda
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_MeetWanda::
	msgbox VerdanturfTown_WandasHouse_Text_MeetWanda, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandaDontWorry::
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAunt::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen::
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened::
	msgbox VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_Text_StrongerSpeech:
	.string "WALLY: Aku kalah darimu, {PLAYER}, tapi\n"
	.string "aku tidak merasa sedih lagi.\p"
	.string "Karena aku punya tujuan baru dalam hidup.\n"
	.string "Bersama dengan RALTS-ku, aku akan\l"
	.string "menantang POKéMON GYM dan menjadi\l"
	.string "TRAINER yang hebat.\p"
	.string "Tolong perhatikan aku, {PLAYER}.\n"
	.string "Aku akan menjadi lebih kuat darimu.\p"
	.string "Ketika aku sudah kuat, aku akan menantangmu\n"
	.string "untuk bertarung lagi.$"

VerdanturfTown_WandasHouse_Text_StrongerSpeechShort:
	.string "WALLY: Tolong perhatikan aku, {PLAYER}.\n"
	.string "Aku akan menjadi lebih kuat darimu.\p"
	.string "Ketika aku sudah kuat, aku akan menantangmu\n"
	.string "untuk bertarung lagi.$"

VerdanturfTown_WandasHouse_Text_WallysNextDoor:
	.string "PAMAN: Oh! {PLAYER}{KUN}!\n"
	.string "WALLY ada di sebelah.\p"
	.string "Tapi, Nak, ada sesuatu yang harus\n"
	.string "aku beritahukan padamu.\p"
	.string "Lingkungan alami ini memberikan\n"
	.string "keajaiban bagi kesehatan WALLY.\p"
	.string "Mungkin bukan hanya lingkungannya.\n"
	.string "Bisa jadi POKéMON yang memberikan\l"
	.string "harapan pada anak itu.$"

VerdanturfTown_WandasHouse_Text_WallySlippedOff:
	.string "WALLY sudah pergi…\n"
	.string "Dia menyelinap pergi sendiri…$"

VerdanturfTown_WandasHouse_Text_WallyGoneThatFar:
	.string "PAMAN: Benarkah?\n"
	.string "WALLY sudah pergi sejauh itu sendirian…\p"
	.string "Yah, aku harus memberinya pujian--dia\n"
	.string "putra adikku.$"

VerdanturfTown_WandasHouse_Text_MeetWanda:
	.string "WANDA: Kamu siapa?\n"
	.string "Oh, benar, aku mengerti!\p"
	.string "Kamu {PLAYER} yang diceritakan\n"
	.string "WALLY padaku.\p"
	.string "Aku sepupu WALLY.\n"
	.string "Senang bertemu denganmu!\p"
	.string "Aku rasa WALLY menjadi jauh lebih\n"
	.string "ceria dan sehat sejak dia datang ke sini.$"

VerdanturfTown_WandasHouse_Text_DontWorryAboutWally:
	.string "WANDA: Jangan khawatirkan WALLY.\n"
	.string "Dia akan baik-baik saja.\p"
	.string "Aku kenal sepupuku, dan dia juga\n"
	.string "punya POKéMON bersamanya.$"

VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay:
	.string "Berkat kamu, aku bisa melihat\n"
	.string "pacarku setiap hari.\l"
	.string "Senang? Tentu saja aku senang!$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven:
	.string "Pacar putriku adalah orang yang sangat\n"
	.string "bertekad dan bersemangat.\p"
	.string "Dia terus menggali terowongan\n"
	.string "hanya agar bisa bertemu putriku.\p"
	.string "Putriku sedikit khawatir,\n"
	.string "jadi dia sering pergi ke terowongan.$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging:
	.string "Luar biasa. Pacar putriku\n"
	.string "menggali terowongan dengan tangan!\p"
	.string "Ini sangat luar biasa!$"

VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally:
	.string "Jika sesuatu terjadi pada WALLY,\n"
	.string "aku tidak akan pernah bisa melihat\l"
	.string "orang tuanya di PETALBURG…$"

VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande:
	.string "WALLY ada di EVER GRANDE?\p"
	.string "Orang tuanya di PETALBURG pasti\n"
	.string "akan terkejut mendengarnya!$"

