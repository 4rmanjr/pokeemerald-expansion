AbandonedShip_Rooms_1F_MapScripts::
	.byte 0

AbandonedShip_Rooms_1F_EventScript_Gentleman::
	msgbox AbandonedShip_Rooms_1F_Text_TakingALookAround, MSGBOX_NPC
	end

AbandonedShip_Rooms_1F_EventScript_Demetrius::
	trainerbattle_single TRAINER_DEMETRIUS, AbandonedShip_Rooms_1F_Text_DemetriusIntro, AbandonedShip_Rooms_1F_Text_DemetriusDefeat
	msgbox AbandonedShip_Rooms_1F_Text_DemetriusPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms_1F_EventScript_Thalia::
	trainerbattle_single TRAINER_THALIA_1, AbandonedShip_Rooms_1F_Text_ThaliaIntro, AbandonedShip_Rooms_1F_Text_ThaliaDefeat, AbandonedShip_Rooms_1F_EventScript_RegisterThalia
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms_1F_EventScript_ThaliaRematch
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms_1F_EventScript_RegisterThalia::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_THALIA_1
	release
	end

AbandonedShip_Rooms_1F_EventScript_ThaliaRematch::
	trainerbattle_rematch TRAINER_THALIA_1, AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro, AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms_1F_Text_TakingALookAround:
	.string "Kapal seperti ini langka, jadi aku\n"
	.string "lihat-lihat dulu.\p"
	.string "Hmhm…\n"
	.string "Sepertinya ada kabin lain…$"

AbandonedShip_Rooms_1F_Text_ThaliaIntro:
	.string "Kenapa kamu bisa sampai ke sini?\n"
	.string "Kamu pasti penasaran!$"

AbandonedShip_Rooms_1F_Text_ThaliaDefeat:
	.string "Tak hanya penasaran, tapi juga kuat…$"

AbandonedShip_Rooms_1F_Text_ThaliaPostBattle:
	.string "Pria di sebelah…\p"
	.string "Dia bilang hanya jalan-jalan,\n"
	.string "tapi aku ragu.$"

AbandonedShip_Rooms_1F_Text_ThaliaRegister:
	.string "Kamu TRAINER yang tangguh!\n"
	.string "Biar kucatat nomormu sebagai kenangan!$"

AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro:
	.string "Kenapa kamu kembali lagi?\n"
	.string "Kamu pasti sangat penasaran!$"

AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat:
	.string "Kamu kuat sekali, ya?$"

AbandonedShip_Rooms_1F_Text_ThaliaPostRematch:
	.string "Aku yakin pria itu merencanakan sesuatu!\n"
	.string "Tingkahnya sangat mencurigakan!$"

AbandonedShip_Rooms_1F_Text_DemetriusIntro:
	.string "Waaah!\n"
	.string "Aku ketahuan! …Hah?$"

AbandonedShip_Rooms_1F_Text_DemetriusDefeat:
	.string "Oh, kamu bukan Ibuku.$"

AbandonedShip_Rooms_1F_Text_DemetriusPostBattle:
	.string "Aku ada masalah dengan Ibu, jadi aku kabur.\n"
	.string "Rahasiakan di mana aku berada, ya!$"

