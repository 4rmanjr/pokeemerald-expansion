MysteryGiftScript_VisitingTrainer::
	setvaddress MysteryGiftScript_VisitingTrainer
	special ValidateEReaderTrainer
	vgoto_if_eq VAR_RESULT, 0, MysteryGiftScript_VisitingTrainerArrived
	lock
	faceplayer
	vmessage sText_MysteryGiftVisitingTrainerInstructions
	waitmessage
	waitbuttonpress
	release
	end

MysteryGiftScript_VisitingTrainerArrived:
	lock
	faceplayer
	vmessage sText_MysteryGiftVisitingTrainerArrived
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftVisitingTrainerInstructions:
	.string "Terima kasih telah menggunakan\n"
	.string "Sistem MYSTERY GIFT.\p"
	.string "Dengan memegang WONDER CARD ini, kamu\n"
	.string "dapat mengikuti survei di\l"
	.string "POKéMON MART.\p"
	.string "Gunakan survei ini untuk mengundang\n"
	.string "TRAINER ke KOTA SOOTOPOLIS.\p"
	.string "…Izinkan aku memberimu kata sandi\n"
	.string "rahasia untuk survei:\p"
	.string "“BERIKAN AKU\n"
	.string "TRAINER HEBAT”\p"
	.string "Tulis itu di survei dan kirimkan\n"
	.string "ke SISTEM KOMUNIKASI\l"
	.string "NIRKABEL.$"

sText_MysteryGiftVisitingTrainerArrived:
	.string "Terima kasih telah menggunakan\n"
	.string "Sistem MYSTERY GIFT.\p"
	.string "Seorang TRAINER telah tiba di\n"
	.string "KOTA SOOTOPOLIS mencarimu.\p"
	.string "Kami harap kamu akan menikmati\n"
	.string "bertarung melawan TRAINER yang berkunjung.\p"
	.string "Kamu dapat mengundang TRAINER lain dengan\n"
	.string "memasukkan kata sandi lain.\p"
	.string "Coba cari kata sandi lain\n"
	.string "yang mungkin berhasil.$"
