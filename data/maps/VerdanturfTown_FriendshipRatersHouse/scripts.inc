VerdanturfTown_FriendshipRatersHouse_MapScripts::
	.byte 0

VerdanturfTown_FriendshipRatersHouse_EventScript_FriendshipRater::
	lock
	faceplayer
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_SeeHowMuchPokemonLikesYou, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	switch VAR_RESULT
	case FRIENDSHIP_NONE, VerdanturfTown_FriendshipRatersHouse_EventScript_DetestsYou
	case FRIENDSHIP_1_TO_49, VerdanturfTown_FriendshipRatersHouse_EventScript_VeryWary
	case FRIENDSHIP_50_TO_99, VerdanturfTown_FriendshipRatersHouse_EventScript_NotUsedToYou
	case FRIENDSHIP_100_TO_149, VerdanturfTown_FriendshipRatersHouse_EventScript_GettingUsedToYou
	case FRIENDSHIP_150_TO_199, VerdanturfTown_FriendshipRatersHouse_EventScript_LikesYouQuiteALot
	case FRIENDSHIP_200_TO_254, VerdanturfTown_FriendshipRatersHouse_EventScript_VeryHappy
	case FRIENDSHIP_MAX, VerdanturfTown_FriendshipRatersHouse_EventScript_AdoresYou
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_DetestsYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_DetestsYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_VeryWary::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_VeryWary, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_NotUsedToYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_NotUsedToYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_GettingUsedToYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_GettingUsedToYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_LikesYouQuiteALot::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_LikesYouQuiteALot, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_VeryHappy::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_VeryHappy, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_AdoresYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_AdoresYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_Pikachu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_Pikachu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

VerdanturfTown_FriendshipRatersHouse_Text_SeeHowMuchPokemonLikesYou:
	.string "Coba aku lihat POKéMON-mu.\n"
	.string "Aku akan memeriksa seberapa besar ia menyukaimu.\p"
	.string "Oh.\n"
	.string "POKéMON-mu…$"

VerdanturfTown_FriendshipRatersHouse_Text_AdoresYou:
	.string "Ia memujamu.\n"
	.string "Tidak mungkin ia bisa mencintaimu lebih lagi.\l"
	.string "Aku bahkan merasa senang melihatnya.$"

VerdanturfTown_FriendshipRatersHouse_Text_VeryHappy:
	.string "Ia terlihat sangat bahagia.\n"
	.string "Ia jelas sangat menyukaimu.$"

VerdanturfTown_FriendshipRatersHouse_Text_LikesYouQuiteALot:
	.string "Ia cukup menyukaimu.\n"
	.string "Sepertinya ia ingin sedikit dimanja.$"

VerdanturfTown_FriendshipRatersHouse_Text_GettingUsedToYou:
	.string "Ia mulai terbiasa denganmu.\n"
	.string "Sepertinya ia percaya padamu.$"

VerdanturfTown_FriendshipRatersHouse_Text_NotUsedToYou:
	.string "Ia belum terlalu terbiasa denganmu.\n"
	.string "Ia tidak mencintai maupun membencimu.$"

VerdanturfTown_FriendshipRatersHouse_Text_VeryWary:
	.string "Ia sangat waspada.\n"
	.string "Ada kekejaman menakutkan di matanya.\l"
	.string "Ia tidak begitu menyukaimu sama sekali.$"

VerdanturfTown_FriendshipRatersHouse_Text_DetestsYou:
	.string "Ini agak sulit bagiku untuk mengatakannya…\p"
	.string "POKéMON-mu benar-benar membencimu.\n"
	.string "Bukankah itu membuatmu tidak nyaman?$"

VerdanturfTown_FriendshipRatersHouse_Text_Pikachu:
	.string "PIKACHU: Pika pika!$"

