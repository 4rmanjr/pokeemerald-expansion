ProfileMan_EventScript_Man::
	lock
	faceplayer
	goto_if_set FLAG_SYS_CHAT_USED, ProfileMan_EventScript_GivenProfileBefore
	msgbox ProfileMan_Text_CollectTrainerProfiles, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeProfile
	end

ProfileMan_EventScript_AskToSeeProfile::
	msgbox ProfileMan_Text_MayISeeYourProfile, MSGBOX_DEFAULT
	multichoice 17, 6, MULTI_YESNOINFO_2, FALSE
	switch VAR_RESULT
	case 0, ProfileMan_EventScript_CreateProfile
	case 1, ProfileMan_EventScript_DeclineShowProfile
	case 2, ProfileMan_EventScript_Info
	case MULTI_B_PRESSED, ProfileMan_EventScript_DeclineShowProfile
	end

ProfileMan_EventScript_Info::
	msgbox ProfileMan_Text_EasyChatExplanation, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeProfile
	end

ProfileMan_EventScript_CreateProfile::
	msgbox ProfileMan_Text_LetsSeeItThen, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, EASY_CHAT_TYPE_PROFILE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, ProfileMan_EventScript_CancelShowProfile
	goto_if_eq VAR_RESULT, 1, ProfileMan_EventScript_ShowProfile
	end

ProfileMan_EventScript_CancelShowProfile::
	msgbox ProfileMan_Text_NotIntoItRightNow, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_ShowProfile::
	setvar VAR_0x8004, 0
	special ShowEasyChatProfile
	waitmessage
	delay 80
	msgbox ProfileMan_Text_FantasticProfile, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_DeclineShowProfile::
	msgbox ProfileMan_Text_ImagineYouWouldHaveWonderfulProfile, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_GivenProfileBefore::
	msgbox ProfileMan_Text_YouHaveWonderfulSmile, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeNewProfile
	end

ProfileMan_EventScript_AskToSeeNewProfile::
	msgbox ProfileMan_Text_MayISeeYourNewProfile, MSGBOX_DEFAULT
	multichoice 17, 6, MULTI_YESNOINFO_2, FALSE
	switch VAR_RESULT
	case 0, ProfileMan_EventScript_CreateNewProfile
	case 1, ProfileMan_EventScript_DeclineNewProfile
	case 2, ProfileMan_EventScript_InfoNewProfile
	case MULTI_B_PRESSED, ProfileMan_EventScript_DeclineNewProfile
	end

ProfileMan_EventScript_InfoNewProfile::
	msgbox ProfileMan_Text_EasyChatExplanation, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeNewProfile
	end

ProfileMan_EventScript_CreateNewProfile::
	msgbox ProfileMan_Text_EvenBetterThanLastProfile, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, EASY_CHAT_TYPE_PROFILE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, ProfileMan_EventScript_CancelShowProfile
	goto_if_eq VAR_RESULT, 1, ProfileMan_EventScript_ShowProfile
	end

ProfileMan_EventScript_DeclineNewProfile::
	msgbox ProfileMan_Text_LikeProfileWayItIs, MSGBOX_DEFAULT
	release
	end

@ Unused
ProfileMan_EventScript_Ret::
	return

ProfileMan_Text_CollectTrainerProfiles:
	.string "Halo, TRAINER!\n"
	.string "Kamu punya senyum yang indah.\p"
	.string "Aku punya hobi--mengumpulkan profil\n"
	.string "POKéMON TRAINERS.$"

ProfileMan_Text_MayISeeYourProfile:
	.string "Jadi, bagaimana?\n"
	.string "Bolehkah aku melihat profilmu?$"

ProfileMan_Text_EasyChatExplanation:
	.string "Kamu membuat profilmu sendiri dengan\n"
	.string "menggabungkan empat kata atau frasa.\p"
	.string "Ini, aku akan menunjukkan contoh\n"
	.string "profil menggunakan empat bagian teks.\p"
	.string "Kamu bisa mengganti keempat bagian itu\n"
	.string "dengan bagian teks lain sesukamu\l"
	.string "untuk membuat profilmu sendiri.\p"
	.string "Ada banyak bagian teks yang\n"
	.string "bisa kamu gunakan.\p"
	.string "Mereka diatur dalam kelompok seperti\n"
	.string "POKéMON, gaya hidup, dan hobi agar\l"
	.string "lebih mudah mencarinya.\p"
	.string "Jadi, pertama, pilih kelompok teks\n"
	.string "untuk menampilkan daftar pilihan.\p"
	.string "Kemudian, pilih pilihan yang kamu inginkan.\p"
	.string "Ulangi untuk pilihan teks yang tersisa,\n"
	.string "dan kamu akan punya profilmu sendiri.$"

ProfileMan_Text_LetsSeeItThen:
	.string "Ya! Terima kasih!\n"
	.string "Jadi, mari kita lihat.$"

ProfileMan_Text_ImagineYouWouldHaveWonderfulProfile:
	.string "Oh, tidak, benarkah?\p"
	.string "Aku membayangkan seseorang sepertimu akan\n"
	.string "memiliki profil yang indah…$"

ProfileMan_Text_NotIntoItRightNow:
	.string "Oh? Kamu tidak tertarik sekarang?\p"
	.string "Yah, kapan saja boleh!$"

ProfileMan_Text_YouHaveWonderfulSmile:
	.string "Halo, TRAINER!\n"
	.string "Kamu punya senyum yang indah.$"

ProfileMan_Text_MayISeeYourNewProfile:
	.string "Bolehkah aku melihat profil barumu?$"

ProfileMan_Text_EvenBetterThanLastProfile:
	.string "Ya! Terima kasih!\p"
	.string "Aku harap ini bahkan lebih baik dari profil\n"
	.string "yang kamu tunjukkan sebelumnya.$"

ProfileMan_Text_LikeProfileWayItIs:
	.string "Oh, kamu suka profilmu apa adanya.\p"
	.string "Aku tidak menyalahkanmu--ini adalah profil\n"
	.string "yang indah apa adanya sekarang.$"

ProfileMan_Text_FantasticProfile:
	.string "F-fantastis!\p"
	.string "Profilmu, ini luar biasa!\n"
	.string "Ini benar-benar menggambarkan dirimu.\p"
	.string "Wah, siapa pun yang mendengar profil ini pasti\n"
	.string "akan terpikat olehmu!\p"
	.string "Terima kasih!$"

@ Unused
ProfileMan_Text_YouKnowSecretSaying:
	.string "Oh?\n"
	.string "Kamu tahu ucapan rahasia itu!\p"
	.string "Itu berarti kamu sekarang adalah anggota\n"
	.string "dari MYSTERY EVENT CLUB!$"
