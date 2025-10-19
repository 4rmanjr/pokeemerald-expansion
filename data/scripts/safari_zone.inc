SafariZone_EventScript_OutOfBallsMidBattle::
	setvar VAR_SAFARI_ZONE_STATE, 1
	special ExitSafariMode
	setwarp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 2, 5
	end

SafariZone_EventScript_Exit::
	setvar VAR_SAFARI_ZONE_STATE, 1
	special ExitSafariMode
	warp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 2, 5
	waitstate
	end

SafariZone_EventScript_RetirePrompt::
	lockall
	msgbox SafariZone_Text_WouldYouLikeToExit, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SafariZone_EventScript_Retire
	releaseall
	end

SafariZone_EventScript_Retire::
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_TimesUp::
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_TimesUp
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_OutOfBalls::
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_OutOfBalls
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

EventScript_PokeBlockFeeder::
	lockall
	special GetPokeblockFeederInFront
	goto_if_ne VAR_RESULT, 0xFFFF, SafariZone_EventScript_PokeblockPresent
	msgbox SafariZone_Text_PlacePokeblockOnFeeder, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SafariZone_EventScript_ChoosePokeblock
	releaseall
	end

SafariZone_EventScript_ChoosePokeblock::
	fadescreen FADE_TO_BLACK
	special OpenPokeblockCaseOnFeeder
	waitstate
	goto_if_ne VAR_RESULT, 0xFFFF, SafariZone_EventScript_PokeblockPlaced
#ifdef BUGFIX
	releaseall  @ Only gets called from EventScript_PokeBlockFeeder which uses lockall.
#endif
	end

SafariZone_EventScript_PokeblockPlaced::
	message SafariZone_Text_PokeblockWasPlaced
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_EventScript_PokeblockPresent::
	message SafariZone_Text_PokeblockStillHere
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_Text_WouldYouLikeToExit:
	.string "Apakah kamu ingin keluar dari SAFARI\n"
	.string "ZONE sekarang?$"

SafariZone_Text_TimesUp:
	.string "Ding-dong! Waktu habis!\n"
	.string "Permainan SAFARI-mu berakhir.$"

SafariZone_Text_OutOfBalls:
	.string "SAFARI BALLS-mu habis.\n"
	.string "Permainan SAFARI-mu berakhir.$"

SafariZone_Text_PlacePokeblockOnFeeder:
	.string "Apakah kamu ingin meletakkan {POKEBLOCK}\n"
	.string "di {POKEBLOCK} FEEDER?$"

SafariZone_Text_PokeblockStillHere:
	.string "{STR_VAR_1} yang kamu tinggalkan\n"
	.string "sebelumnya masih ada di sini.$"

SafariZone_Text_PokeblockWasPlaced:
	.string "{STR_VAR_1} diletakkan\n"
	.string "di {POKEBLOCK} FEEDER.$"

Route121_SafariZoneEntrance_Text_WelcomeToSafariZone:
	.string "Selamat datang di SAFARI ZONE!\p"
	.string "Di sini, kamu bisa menyaksikan banyak jenis\n"
	.string "POKéMON yang jarang terlihat di HOENN.\p"
	.string "Dan, kamu akan melihat mereka dalam keadaan\n"
	.string "liar, tidak terlatih di habitat alami.\p"
	.string "Terlebih lagi, kami telah membuka\n"
	.string "gerbang untuk POKéMON TRAINERS.\p"
	.string "Kamu dianjurkan untuk menangkap POKéMON\n"
	.string "untuk disimpan!\p"
	.string "Masuk dan nikmati SAFARI ZONE!$"

Route121_SafariZoneEntrance_Text_WelcomeFirstTime:
	.string "Selamat datang di SAFARI ZONE!\n"
	.string "Apakah ini pertama kalinya kamu di sini?$"

Route121_SafariZoneEntrance_Text_ComeInAndEnjoy:
	.string "Masuk dan nikmati SAFARI ZONE!$"

Route121_SafariZoneEntrance_Text_FirstTimeInfo:
	.string "Ketika kamu memasuki SAFARI ZONE, kamu\n"
	.string "memulai dengan 30 SAFARI BALLS untuk\l"
	.string "menangkap POKéMON.\p"
	.string "Permainan SAFARI berakhir ketika kamu\n"
	.string "kehabisan SAFARI BALLS, atau ketika kamu\l"
	.string "telah berjalan 500 langkah.\p"
	.string "Masuk dan nikmati SAFARI ZONE!$"

Route121_SafariZoneEntrance_Text_WouldYouLikeToPlay:
	.string "Selamat datang di SAFARI ZONE!\p"
	.string "Semua yang bisa kamu tangkap hanya dengan ¥500!\n"
	.string "Apakah kamu ingin bermain SAFARI Game?$"

Route121_SafariZoneEntrance_Text_PlayAnotherTime:
	.string "Baik.\n"
	.string "Silakan bermain lain kali!$"

Route121_SafariZoneEntrance_Text_NotEnoughMoney:
	.string "Uangmu tidak cukup.\n"
	.string "Maaf.$"

Route121_SafariZoneEntrance_Text_ThatWillBe500Please:
	.string "Itu akan menjadi ¥500, tolong.$"

Route121_SafariZoneEntrance_Text_HereAreYourSafariBalls:
	.string "Ini SAFARI BALLS-mu.$"

Route121_SafariZoneEntrance_Text_Received30SafariBalls:
	.string "{PLAYER} menerima 30 SAFARI BALLS.$"

Route121_SafariZoneEntrance_Text_PleaseEnjoyYourself:
	.string "Kami akan memberitahumu ketika permainanmu\n"
	.string "selesai.\p"
	.string "Jadi, sampai saat itu, nikmati dirimu, ya!\n"
	.string "Pergilah dalam petualangan liarmu!$"

Route121_SafariZoneEntrance_Text_PCIsFull:
	.string "Permisi!\n"
	.string "PC BOX-mu penuh.$"

Route121_SafariZoneEntrance_Text_YouNeedPokeblockCase:
	.string "Permisi!\n"
	.string "Kamu sepertinya tidak punya {POKEBLOCK} CASE.\p"
	.string "Permainan SAFARI-mu akan jauh lebih\n"
	.string "berhasil jika kamu menggunakan {POKEBLOCK}S.\p"
	.string "Silakan kembali dengan {POKEBLOCK} CASE.\p"
	.string "Kamu bisa mendapatkan {POKEBLOCK} CASE dari\n"
	.string "LILYCOVE CONTEST HALL.$"

SafariZone_South_Text_StillHaveTimeExit:
	.string "Kamu masih punya waktu. Apakah kamu ingin\n"
	.string "keluar dari SAFARI ZONE sekarang?$"

SafariZone_South_Text_EnjoyTheRestOfYourAdventure:
	.string "Silakan nikmati sisa petualangan\n"
	.string "liarmu!$"

SafariZone_South_Text_ExitEarlyThankYouForPlaying:
	.string "Baik.\p"
	.string "Aku akan mengambil kembali sisa SAFARI\n"
	.string "BALLS-mu.\p"
	.string "Terima kasih telah bermain.\n"
	.string "Kami harap bisa bertemu lagi.$"

SafariZone_South_Text_GoodLuck:
	.string "Semoga berhasil!\p"
	.string "Jika kamu butuh sesuatu, jangan ragu\n"
	.string "untuk memberitahuku, ya!$"

SafariZone_South_Text_Boy:
	.string "Tahukah kamu?\p"
	.string "Jika kamu meletakkan {POKEBLOCK} di kotak itu,\n"
	.string "POKéMON akan berkumpul.$"

SafariZone_South_Text_Man:
	.string "Aku ingin masuk lebih dalam, tapi aku\n"
	.string "lupa membawa BIKE.\p"
	.string "Ada yang memberitahuku bahwa POKéMON langka\n"
	.string "hidup di daerah terpencil.$"

SafariZone_Southwest_Text_Woman:
	.string "Terkadang, ketika aku melemparkan {POKEBLOCK} ke\n"
	.string "POKéMON, itu diabaikan.\p"
	.string "Apakah POKéMON punya suka dan tidak suka\n"
	.string "tentang apa yang mereka makan?$"

SafariZone_Northwest_Text_Man:
	.string "Terengah-engah… Terengah-engah…\n"
	.string "Aku…berhasil keluar dari sini…tapi…\p"
	.string "Aku kelelahan… Aku tidak punya\n"
	.string "energi untuk menangkap POKéMON…$"

SafariZone_North_Text_Fisherman:
	.string "Aku dalam misi mencari WATER POKéMON\n"
	.string "yang tidak kamu lihat di HOENN.\p"
	.string "Apakah kamu tahu di mana letak danau itu?$"

SafariZone_North_Text_Man:
	.string "Aku akan menangkap banyak POKéMON langka\n"
	.string "di sini dan menukarkannya dengan teman-temanku!$"

SafariZone_South_Text_Youngster:
	.string "Aku meletakkan {POKEBLOCK} di {POKEBLOCK} FEEDER.\n"
	.string "Tapi sepertinya sudah hilang.\p"
	.string "Kurasa POKéMON pasti memakannya\n"
	.string "tanpa aku sadari.$"

Route121_SafariZoneEntrance_Text_TrainerTip:
	.string "TIPS TRAINER SAFARI ZONE!\p"
	.string "Lemparkan {POKEBLOCK}S ke POKéMON liar agar\n"
	.string "mereka tidak mudah kabur.$"

SafariZone_Southwest_Text_RestHouseSign:
	.string "“Istirahatkan kakimu yang lelah.”\n"
	.string "REST HOUSE$"

SafariZone_RestHouse_Text_Youngster:
	.string "Aku tidak punya {POKEBLOCK}S, tapi aku menangkap\n"
	.string "cukup banyak POKéMON.\p"
	.string "Kamu bisa meningkatkan peluangmu untuk menangkap\n"
	.string "dengan mendekati mereka\l"
	.string "sebelum melempar SAFARI BALL.$"

SafariZone_RestHouse_Text_PsychicM:
	.string "Jika kamu menggunakan {POKEBLOCK}S, POKéMON liar tidak\n"
	.string "akan cepat kabur.\p"
	.string "Tidak banyak gunanya memberikan {POKEBLOCK}S kepada\n"
	.string "POKéMON yang tidak mudah kabur.$"

SafariZone_RestHouse_Text_FatMan:
	.string "Jika kamu meletakkan {POKEBLOCK} di FEEDER,\n"
	.string "POKéMON akan tertarik padanya.\p"
	.string "Aku pikir POKéMON dengan sifat yang sama\n"
	.string "tertarik oleh {POKEBLOCK} tertentu.$"

SafariZone_South_Text_AreaOffLimits1:
	.string "Area ini masih dalam pembangunan.\n"
	.string "Dilarang masuk, maaf!$"

SafariZone_Southeast_Text_ExpansionIsFinished:
	.string "Proyek perluasan SAFARI ZONE\n"
	.string "sudah selesai sekarang.\p"
	.string "Kami harap kamu akan menikmati area baru ini.$"

SafariZone_South_Text_AreaOffLimits2:
	.string "Area ini masih dalam pembangunan.\n"
	.string "Dilarang masuk, maaf!$"

SafariZone_Southeast_Text_LittleGirl:
	.string "Wow! Asyik! Aku belum pernah melihat\n"
	.string "POKéMON ini sebelumnya!$"

SafariZone_Southeast_Text_FatMan:
	.string "POKéMON di area ini semuanya\n"
	.string "baru bagiku.\p"
	.string "Dan aku diizinkan menangkap POKéMON\n"
	.string "langka ini! Keren sekali!$"

SafariZone_Southeast_Text_RichBoy:
	.string "POKéMON di sekitar sini sepertinya\n"
	.string "berasal dari tempat lain selain HOENN.$"

SafariZone_Northeast_Text_Boy:
	.string "Aku hanya punya beberapa SAFARI BALLS tersisa.\p"
	.string "Aku kesulitan memutuskan apa yang harus\n"
	.string "kutangkap.$"

SafariZone_Northeast_Text_Woman:
	.string "Aku dengar kamu bisa melihat PIKACHU di sini.\n"
	.string "Di mana mungkin ada satu?$"

SafariZone_Northeast_Text_Girl:
	.string "Oh, aduh!\n"
	.string "Aku sepertinya tidak bisa menangkap apa pun!\p"
	.string "Aku akan membuang-buang harga tiket\n"
	.string "masuk jika aku tidak menangkap sesuatu!$"
