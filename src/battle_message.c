#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_message.h"
#include "battle_setup.h"
#include "battle_tower.h"
#include "battle_z_move.h"
#include "data.h"
#include "event_data.h"
#include "frontier_util.h"
#include "graphics.h"
#include "international_string_util.h"
#include "item.h"
#include "link.h"
#include "menu.h"
#include "palette.h"
#include "recorded_battle.h"
#include "string_util.h"
#include "strings.h"
#include "test_runner.h"
#include "text.h"
#include "trainer_hill.h"
#include "trainer_slide.h"
#include "window.h"
#include "line_break.h"
#include "constants/abilities.h"
#include "constants/battle_dome.h"
#include "constants/battle_string_ids.h"
#include "constants/frontier_util.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/opponents.h"
#include "constants/species.h"
#include "constants/trainers.h"
#include "constants/trainer_hill.h"
#include "constants/weather.h"

struct BattleWindowText
{
    u8 fillValue;
    u8 fontId;
    u8 x;
    u8 y;
    u8 letterSpacing;
    u8 lineSpacing;
    u8 speed;
    u8 fgColor;
    u8 bgColor;
    u8 shadowColor;
};

#if TESTING
EWRAM_DATA u16 sBattlerAbilities[MAX_BATTLERS_COUNT] = {0};
#else
static EWRAM_DATA u16 sBattlerAbilities[MAX_BATTLERS_COUNT] = {0};
#endif
EWRAM_DATA struct BattleMsgData *gBattleMsgDataPtr = NULL;

// todo: make some of those names less vague: attacker/target vs pkmn, etc.

static const u8 sText_EmptyString4[] = _("");

const u8 gText_PkmnShroudedInMist[] = _("Tim {B_ATK_TEAM1} diselimuti oleh kabut!");
const u8 gText_PkmnGettingPumped[] = _("{B_DEF_NAME_WITH_PREFIX} menjadi bersemangat!");
const u8 gText_PkmnsXPreventsSwitching[] = _("{B_BUFF1} mencegah switch dengan Ability {B_LAST_ABILITY}-nya!\p");
const u8 gText_StatSharply[] = _("drastis ");
const u8 gText_StatRose[] = _("meningkat!");
const u8 gText_StatFell[] = _("turun!");
const u8 gText_DefendersStatRose[] = _("{B_BUFF1} milik {B_DEF_NAME_WITH_PREFIX} {B_BUFF2}");
static const u8 sText_GotAwaySafely[] = _("{PLAY_SE SE_FLEE}Kamu berhasil kabur dengan aman!\p");
static const u8 sText_PlayerDefeatedLinkTrainer[] = _("Kamu mengalahkan {B_LINK_OPPONENT1_NAME}!");
static const u8 sText_TwoLinkTrainersDefeated[] = _("Kamu mengalahkan {B_LINK_OPPONENT1_NAME} and {B_LINK_OPPONENT2_NAME}!");
static const u8 sText_PlayerLostAgainstLinkTrainer[] = _("Kamu kalah melawan {B_LINK_OPPONENT1_NAME}!");
static const u8 sText_PlayerLostToTwo[] = _("Kamu kalah dari {B_LINK_OPPONENT1_NAME} dan {B_LINK_OPPONENT2_NAME}!");
static const u8 sText_PlayerBattledToDrawLinkTrainer[] = _("Pertarunganmu seri melawan {B_LINK_OPPONENT1_NAME}!");
static const u8 sText_PlayerBattledToDrawVsTwo[] = _("Pertarunganmu seri melawan {B_LINK_OPPONENT1_NAME} dan {B_LINK_OPPONENT2_NAME}!");
static const u8 sText_WildFled[] = _("{PLAY_SE SE_FLEE}{B_LINK_OPPONENT1_NAME} kabur!"); //not in gen 5+, replaced with match was forfeited text
static const u8 sText_TwoWildFled[] = _("{PLAY_SE SE_FLEE}{B_LINK_OPPONENT1_NAME} dan {B_LINK_OPPONENT2_NAME} kabur!"); //not in gen 5+, replaced with match was forfeited text
static const u8 sText_PlayerDefeatedLinkTrainerTrainer1[] = _("Kamu mengalahkan {B_TRAINER1_NAME_WITH_CLASS}!\p");
static const u8 sText_OpponentMon1Appeared[] = _("{B_OPPONENT_MON1_NAME} muncul!\p");
static const u8 sText_WildPkmnAppeared[] = _("Kamu bertemu seekor {B_OPPONENT_MON1_NAME} liar!\p");
static const u8 sText_LegendaryPkmnAppeared[] = _("Kamu bertemu seekor {B_OPPONENT_MON1_NAME} liar!\p");
static const u8 sText_WildPkmnAppearedPause[] = _("Kamu bertemu seekor {B_OPPONENT_MON1_NAME} liar!{PAUSE 127}");
static const u8 sText_TwoWildPkmnAppeared[] = _("Wah! {B_OPPONENT_MON1_NAME} dan {B_OPPONENT_MON2_NAME} liar muncul!\p");
static const u8 sText_Trainer1WantsToBattle[] = _("Kamu ditantang oleh {B_TRAINER1_NAME_WITH_CLASS}!\p");
static const u8 sText_LinkTrainerWantsToBattle[] = _("Kamu ditantang oleh {B_LINK_OPPONENT1_NAME}!");
static const u8 sText_TwoLinkTrainersWantToBattle[] = _("Kamu ditantang oleh {B_LINK_OPPONENT1_NAME} and {B_LINK_OPPONENT2_NAME}!");
static const u8 sText_Trainer1SentOutPkmn[] = _("{B_TRAINER1_NAME_WITH_CLASS} mengeluarkan {B_OPPONENT_MON1_NAME}!");
static const u8 sText_Trainer1SentOutTwoPkmn[] = _("{B_TRAINER1_NAME_WITH_CLASS} mengeluarkan {B_OPPONENT_MON1_NAME} and {B_OPPONENT_MON2_NAME}!");
static const u8 sText_Trainer1SentOutPkmn2[] = _("{B_TRAINER1_NAME_WITH_CLASS} mengeluarkan {B_BUFF1}!");
static const u8 sText_LinkTrainerSentOutPkmn[] = _("{B_LINK_OPPONENT1_NAME} mengeluarkan {B_OPPONENT_MON1_NAME}!");
static const u8 sText_LinkTrainerSentOutTwoPkmn[] = _("{B_LINK_OPPONENT1_NAME} mengeluarkan {B_OPPONENT_MON1_NAME} and {B_OPPONENT_MON2_NAME}!");
static const u8 sText_TwoLinkTrainersSentOutPkmn[] = _("{B_LINK_OPPONENT1_NAME} mengeluarkan {B_LINK_OPPONENT_MON1_NAME}! {B_LINK_OPPONENT2_NAME} mengeluarkan {B_LINK_OPPONENT_MON2_NAME}!");
static const u8 sText_LinkTrainerSentOutPkmn2[] = _("{B_LINK_OPPONENT1_NAME} mengeluarkan {B_BUFF1}!");
static const u8 sText_LinkTrainerMultiSentOutPkmn[] = _("{B_LINK_SCR_TRAINER_NAME} mengeluarkan {B_BUFF1}!");
static const u8 sText_GoPkmn[] = _("Maju! {B_PLAYER_MON1_NAME}!");
static const u8 sText_GoTwoPkmn[] = _("Maju! {B_PLAYER_MON1_NAME} dan {B_PLAYER_MON2_NAME}!");
static const u8 sText_GoPkmn2[] = _("Maju! {B_BUFF1}!");
static const u8 sText_DoItPkmn[] = _("Aku serahkan padamu, {B_BUFF1}!");
static const u8 sText_GoForItPkmn[] = _("Ayo serang, {B_BUFF1}!");
static const u8 sText_JustALittleMorePkmn[] = _("Sedikit lagi! Bertahanlah, {B_BUFF1}!"); //currently unused, will require code changes
static const u8 sText_YourFoesWeakGetEmPkmn[] = _("Musuhmu lemah! Habisi dia, {B_BUFF1}!");
static const u8 sText_LinkPartnerSentOutPkmnGoPkmn[] = _("{B_LINK_PARTNER_NAME} mengeluarkan {B_LINK_PLAYER_MON2_NAME}! Go! {B_LINK_PLAYER_MON1_NAME}!");
static const u8 sText_PkmnSwitchOut[] = _("{B_BUFF1}, switch out! Kembalilah!"); //currently unused, I believe its used for when you switch on a pokemon in shift mode
static const u8 sText_PkmnThatsEnough[] = _("{B_BUFF1}, cukup! Kembalilah!");
static const u8 sText_PkmnComeBack[] = _("{B_BUFF1}, kembali!");
static const u8 sText_PkmnOkComeBack[] = _("Baiklah, {B_BUFF1}! Kembalilah!");
static const u8 sText_PkmnGoodComeBack[] = _("Kerja bagus, {B_BUFF1}! Kembalilah!");
static const u8 sText_Trainer1WithdrewPkmn[] = _("{B_TRAINER1_NAME_WITH_CLASS} menarik {B_BUFF1}!");
static const u8 sText_LinkTrainer1WithdrewPkmn[] = _("{B_LINK_OPPONENT1_NAME} menarik {B_BUFF1}!");
static const u8 sText_LinkTrainer2WithdrewPkmn[] = _("{B_LINK_SCR_TRAINER_NAME} menarik {B_BUFF1}!");
static const u8 sText_WildPkmnPrefix[] = _("Si liar ");
static const u8 sText_FoePkmnPrefix[] = _("Pihak lawan ");
static const u8 sText_WildPkmnPrefixLower[] = _("si liar ");
static const u8 sText_FoePkmnPrefixLower[] = _("Pihak lawan ");
static const u8 sText_EmptyString8[] = _("");
static const u8 sText_FoePkmnPrefix2[] = _("Lawan");
static const u8 sText_AllyPkmnPrefix[] = _("Kawan");
static const u8 sText_FoePkmnPrefix3[] = _("Lawan");
static const u8 sText_AllyPkmnPrefix2[] = _("Kawan");
static const u8 sText_FoePkmnPrefix4[] = _("Lawan");
static const u8 sText_AllyPkmnPrefix3[] = _("Kawan");
static const u8 sText_AttackerUsedX[] = _("{B_ATK_NAME_WITH_PREFIX} menggunakan {B_BUFF3}!");
static const u8 sText_ExclamationMark[] = _("!");
static const u8 sText_ExclamationMark2[] = _("!");
static const u8 sText_ExclamationMark3[] = _("!");
static const u8 sText_ExclamationMark4[] = _("!");
static const u8 sText_ExclamationMark5[] = _("!");
static const u8 sText_HP[] = _("HP");
static const u8 sText_Attack[] = _("Attack");
static const u8 sText_Defense[] = _("Defense");
static const u8 sText_Speed[] = _("Speed");
static const u8 sText_SpAttack[] = _("Sp. Atk");
static const u8 sText_SpDefense[] = _("Sp. Def");
static const u8 sText_Accuracy[] = _("accuracy");
static const u8 sText_Evasiveness[] = _("evasiveness");

const u8 *const gStatNamesTable[NUM_BATTLE_STATS] =
{
    [STAT_HP]      = sText_HP,
    [STAT_ATK]     = sText_Attack,
    [STAT_DEF]     = sText_Defense,
    [STAT_SPEED]   = sText_Speed,
    [STAT_SPATK]   = sText_SpAttack,
    [STAT_SPDEF]   = sText_SpDefense,
    [STAT_ACC]     = sText_Accuracy,
    [STAT_EVASION] = sText_Evasiveness,
};
const u8 *const gPokeblockWasTooXStringTable[FLAVOR_COUNT] =
{
    [FLAVOR_SPICY]  = COMPOUND_STRING("terlalu pedas!"),
    [FLAVOR_DRY]    = COMPOUND_STRING("terlalu sepat!"),
    [FLAVOR_SWEET]  = COMPOUND_STRING("terlalu manis!"),
    [FLAVOR_BITTER] = COMPOUND_STRING("terlalu pahit!"),
    [FLAVOR_SOUR]   = COMPOUND_STRING("terlalu asam!"),
};

static const u8 sText_Someones[] = _("Seseorang");
static const u8 sText_Lanettes[] = _("LANETTE"); //no decapitalize until it is everywhere
static const u8 sText_EnigmaBerry[] = _("ENIGMA BERRY"); //no decapitalize until it is everywhere
static const u8 sText_BerrySuffix[] = _(" BERRY"); //no decapitalize until it is everywhere
const u8 gText_EmptyString3[] = _("");

static const u8 sText_TwoInGameTrainersDefeated[] = _("Kamu mengalahkan {B_TRAINER1_NAME_WITH_CLASS} and {B_TRAINER2_NAME_WITH_CLASS}!\p");

// New battle strings.
const u8 gText_drastically[] = _("drastis ");
const u8 gText_severely[] = _("drastis ");
static const u8 sText_TerrainReturnedToNormal[] = _("Medan kembali normal!"); // Unused

const u8 *const gBattleStringsTable[STRINGID_COUNT] =
{
    [STRINGID_TRAINER1LOSETEXT]                     = COMPOUND_STRING("{B_TRAINER1_LOSE_TEXT}"),
    [STRINGID_PKMNGAINEDEXP]                        = COMPOUND_STRING("{B_BUFF1} mendapatkan{B_BUFF2} {B_BUFF3} Exp. Poin!\p"),
    [STRINGID_PKMNGREWTOLV]                         = COMPOUND_STRING("{B_BUFF1} naik level\nmenjadi Lv. {B_BUFF2}!{WAIT_SE}\p"),
    [STRINGID_PKMNLEARNEDMOVE]                      = COMPOUND_STRING("{B_BUFF1} telah mempelajari {B_BUFF2}!{WAIT_SE}\p"),
    [STRINGID_TRYTOLEARNMOVE1]                      = COMPOUND_STRING("{B_BUFF1} ingin mempelajari gerakan {B_BUFF2}.\p"),
    [STRINGID_TRYTOLEARNMOVE2]                      = COMPOUND_STRING("Namun, {B_BUFF1} sudah mengetahui empat gerakan.\p"),
    [STRINGID_TRYTOLEARNMOVE3]                      = COMPOUND_STRING("Apakah langkah lain harus dilupakan, diganti dengan {B_BUFF2}?"),
    [STRINGID_PKMNFORGOTMOVE]                       = COMPOUND_STRING("{B_BUFF1} melupakan {B_BUFF2}…\p"),
    [STRINGID_STOPLEARNINGMOVE]                     = COMPOUND_STRING("{PAUSE 32}Apa kamu ingin menyerah, membantu {B_BUFF1} belajar {B_BUFF2}?"),
    [STRINGID_DIDNOTLEARNMOVE]                      = COMPOUND_STRING("{B_BUFF1} tidak mempelajari {B_BUFF2}.\p"),
    [STRINGID_PKMNLEARNEDMOVE2]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} telah mempelajari {B_BUFF1}!"),
    [STRINGID_ATTACKMISSED]                         = COMPOUND_STRING("Serangan {B_ATK_NAME_WITH_PREFIX} meleset!"),
    [STRINGID_PKMNPROTECTEDITSELF]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} melindungi dirinya sendiri!"),
    [STRINGID_STATSWONTINCREASE2]                   = COMPOUND_STRING("Statistik {B_ATK_NAME_WITH_PREFIX} tidak akan meningkat lebih tinggi lagi!"),
    [STRINGID_AVOIDEDDAMAGE]                        = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} berhasil menghindari kerusakan dengan {B_DEF_ABILITY}!"), //not in gen 5+, ability popup
    [STRINGID_ITDOESNTAFFECT]                       = COMPOUND_STRING("Hal ini tidak memengaruhi {B_DEF_NAME_WITH_PREFIX2}…"),
    [STRINGID_ATTACKERFAINTED]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} pingsan!\p"),
    [STRINGID_TARGETFAINTED]                        = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} pingsan!\p"),
    [STRINGID_PLAYERGOTMONEY]                       = COMPOUND_STRING("Dapat ¥{B_BUFF1} karena menang!\p"),
    [STRINGID_PLAYERWHITEOUT]                       = COMPOUND_STRING("Kamu tidak punya Pokémon lagi yang bisa bertarung!\p"),
    [STRINGID_PLAYERWHITEOUT2_WILD]                 = COMPOUND_STRING("Kamu panik dan menjatuhkan ¥{B_BUFF1}…"),
    [STRINGID_PLAYERWHITEOUT2_TRAINER]              = COMPOUND_STRING("Kamu memberikan ¥{B_BUFF1} kepada pemenang…"),
    [STRINGID_PLAYERWHITEOUT3]                      = COMPOUND_STRING("Kamu merasa kewalahan karena kekalahanmu!"),
    [STRINGID_PREVENTSESCAPE]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} mencegah pelarian dengan {B_SCR_ABILITY}!\p"),
    [STRINGID_HITXTIMES]                            = COMPOUND_STRING("Pokémon tersebut terkena {B_BUFF1} kali!"), //SV has dynamic plural here
    [STRINGID_PKMNFELLASLEEP]                       = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} tertidur!"),
    [STRINGID_PKMNMADESLEEP]                        = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX2} ditidurkan oleh {B_BUFF1} {B_SCR_NAME_WITH_PREFIX}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNALREADYASLEEP]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} sudah tertidur!"),
    [STRINGID_PKMNALREADYASLEEP2]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} sudah tertidur!"),
    [STRINGID_PKMNWASPOISONED]                      = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} keracunan!"),
    [STRINGID_PKMNPOISONEDBY]                       = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} keracunan oleh {B_BUFF1} {B_SCR_NAME_WITH_PREFIX2}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNHURTBYPOISON]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terluka karena racunnya!"),
    [STRINGID_PKMNALREADYPOISONED]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} sudah keracunan!"),
    [STRINGID_PKMNBADLYPOISONED]                    = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} keracunan parah!"),
    [STRINGID_PKMNENERGYDRAINED]                    = COMPOUND_STRING("Energi {B_DEF_NAME_WITH_PREFIX} terkuras!"),
    [STRINGID_PKMNWASBURNED]                        = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} terbakar!"),
    [STRINGID_PKMNBURNEDBY]                         = COMPOUND_STRING("Ability {B_BUFF1} milik {B_SCR_NAME_WITH_PREFIX} membakar {B_EFF_NAME_WITH_PREFIX2}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNHURTBYBURN]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terluka oleh luka bakarnya!"),
    [STRINGID_PKMNWASFROZEN]                        = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} membeku total!"),
    [STRINGID_PKMNFROZENBY]                         = COMPOUND_STRING("{B_BUFF1} dari {B_SCR_NAME_WITH_PREFIX} membekukan {B_EFF_NAME_WITH_PREFIX2}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNISFROZEN]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} membeku total!"),
    [STRINGID_PKMNWASDEFROSTED]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} telah mencair!"),
    [STRINGID_PKMNWASDEFROSTED2]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} telah mencair!"),
    [STRINGID_PKMNWASDEFROSTEDBY]                   = COMPOUND_STRING("{B_CURRENT_MOVE} milik {B_ATK_NAME_WITH_PREFIX} melelehkan es!"),
    [STRINGID_PKMNWASPARALYZED]                     = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} lumpuh, mungkin ia tak bisa bergerak!"),
    [STRINGID_PKMNWASPARALYZEDBY]                   = COMPOUND_STRING("Ability {B_BUFF1} milik {B_SCR_NAME_WITH_PREFIX} melumpuhkan {B_EFF_NAME_WITH_PREFIX2}, mungkin ia tak bisa bergerak!"), //not in gen 5+, ability popup
    [STRINGID_PKMNISPARALYZED]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} tak bisa bergerak karena lumpuh!"),
    [STRINGID_PKMNISALREADYPARALYZED]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} sudah lumpuh!"),
    [STRINGID_PKMNHEALEDPARALYSIS]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} sembuh dari kelumpuhan!"),
    [STRINGID_PKMNDREAMEATEN]                       = COMPOUND_STRING("Mimpi {B_DEF_NAME_WITH_PREFIX} telah dimakan!"), //not in gen 5+, expansion doesn't use anymore
    [STRINGID_STATSWONTINCREASE]                    = COMPOUND_STRING("{B_BUFF1} milik {B_ATK_NAME_WITH_PREFIX} tak bisa lebih tinggi lagi!"),
    [STRINGID_STATSWONTDECREASE]                    = COMPOUND_STRING("{B_BUFF1} milik {B_DEF_NAME_WITH_PREFIX} tak bisa lebih rendah lagi!"),
    [STRINGID_TEAMSTOPPEDWORKING]                   = COMPOUND_STRING("Efek {B_BUFF1} tim-mu berhenti bekerja!"), //unused
    [STRINGID_FOESTOPPEDWORKING]                    = COMPOUND_STRING("Efek {B_BUFF1} tim musuh berhenti bekerja!"), //unused
    [STRINGID_PKMNISCONFUSED]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} sedang bingung!"),
    [STRINGID_PKMNHEALEDCONFUSION]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} sadar dari kebingungannya!"),
    [STRINGID_PKMNWASCONFUSED]                      = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} menjadi bingung!"),
    [STRINGID_PKMNALREADYCONFUSED]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} sudah bingung!"),
    [STRINGID_PKMNFELLINLOVE]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} jatuh cinta!"),
    [STRINGID_PKMNINLOVE]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} jatuh cinta pada {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNIMMOBILIZEDBYLOVE]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} tak bisa bergerak karena cinta!"),
    [STRINGID_PKMNBLOWNAWAY]                        = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} terhempas!"), //unused
    [STRINGID_PKMNCHANGEDTYPE]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} berubah menjadi tipe {B_BUFF1}!"),
    [STRINGID_PKMNFLINCHED]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} tersentak dan tak bisa bergerak!"),
    [STRINGID_PKMNREGAINEDHEALTH]                   = COMPOUND_STRING("HP milik {B_DEF_NAME_WITH_PREFIX} pulih kembali."),
    [STRINGID_PKMNHPFULL]                           = COMPOUND_STRING("HP milik {B_DEF_NAME_WITH_PREFIX} sudah penuh!"),
    [STRINGID_PKMNRAISEDSPDEF]                      = COMPOUND_STRING("Light Screen membuat tim {B_ATK_TEAM2} lebih kuat terhadap special moves!"),
    [STRINGID_PKMNRAISEDDEF]                        = COMPOUND_STRING("Reflect membuat tim {B_ATK_TEAM2} lebih kuat terhadap physical moves!"),
    [STRINGID_PKMNCOVEREDBYVEIL]                    = COMPOUND_STRING("Tim {B_ATK_TEAM1} menyelimuti diri dengan selubung mistis!"),
    [STRINGID_PKMNUSEDSAFEGUARD]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} dilindungi oleh Safeguard!"),
    [STRINGID_PKMNSAFEGUARDEXPIRED]                 = COMPOUND_STRING("Tim {B_ATK_TEAM1} tidak lagi dilindungi oleh Safeguard!"),
    [STRINGID_PKMNWENTTOSLEEP]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} tertidur!"), //not in gen 5+
    [STRINGID_PKMNSLEPTHEALTHY]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} tidur dan memulihkan HP-nya!"),
    [STRINGID_PKMNWHIPPEDWHIRLWIND]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menciptakan angin puyuh!"),
    [STRINGID_PKMNTOOKSUNLIGHT]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menyerap cahaya!"),
    [STRINGID_PKMNLOWEREDHEAD]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menyembunyikan kepalanya!"),
    [STRINGID_PKMNISGLOWING]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} diselimuti cahaya terang!"),
    [STRINGID_PKMNFLEWHIGH]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terbang tinggi!"),
    [STRINGID_PKMNDUGHOLE]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menggali lubang ke bawah tanah!"),
    [STRINGID_PKMNSQUEEZEDBYBIND]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} diremas oleh {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNTRAPPEDINVORTEX]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} terjebak dalam pusaran!"),
    [STRINGID_PKMNWRAPPEDBY]                        = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} dililit oleh {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNCLAMPED]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menjepit {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNHURTBY]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terluka oleh {B_BUFF1}!"),
    [STRINGID_PKMNFREEDFROM]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terbebas dari {B_BUFF1}!"),
    [STRINGID_PKMNCRASHED]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terus melaju dan menabrak!"),
    [STRINGID_PKMNSHROUDEDINMIST]                   = gText_PkmnShroudedInMist,
    [STRINGID_PKMNPROTECTEDBYMIST]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} dilindungi oleh kabut!"),
    [STRINGID_PKMNGETTINGPUMPED]                    = gText_PkmnGettingPumped,
    [STRINGID_PKMNHITWITHRECOIL]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terkena damage dari recoil!"),
    [STRINGID_PKMNPROTECTEDITSELF2]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} melindungi dirinya!"),
    [STRINGID_PKMNBUFFETEDBYSANDSTORM]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terhempas badai pasir!"),
    [STRINGID_PKMNPELTEDBYHAIL]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terhempas badai es!"),
    [STRINGID_PKMNSEEDED]                           = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} ditanami benih!"),
    [STRINGID_PKMNEVADEDATTACK]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} menghindari serangan!"),
    [STRINGID_PKMNSAPPEDBYLEECHSEED]                = COMPOUND_STRING("Kesehatan {B_ATK_NAME_WITH_PREFIX} dihisap oleh Leech Seed!"),
    [STRINGID_PKMNFASTASLEEP]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} tertidur pulas."),
    [STRINGID_PKMNWOKEUP]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terbangun!"),
    [STRINGID_PKMNUPROARKEPTAWAKE]                  = COMPOUND_STRING("Tapi keributan membuat {B_SCR_NAME_WITH_PREFIX2} tetap terjaga!"),
    [STRINGID_PKMNWOKEUPINUPROAR]                   = COMPOUND_STRING("Keributan itu membangunkan {B_EFF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNCAUSEDUPROAR]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} membuat keributan!"),
    [STRINGID_PKMNMAKINGUPROAR]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} sedang membuat keributan!"),
    [STRINGID_PKMNCALMEDDOWN]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menjadi tenang."),
    [STRINGID_PKMNCANTSLEEPINUPROAR]                = COMPOUND_STRING("Tapi {B_DEF_NAME_WITH_PREFIX2} tak bisa tidur dalam keributan!"),
    [STRINGID_PKMNSTOCKPILED]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menimbun {B_BUFF1}!"),
    [STRINGID_PKMNCANTSTOCKPILE]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} tak bisa menimbun lagi!"), //I think this was replaced with just "But it failed!"
    [STRINGID_PKMNCANTSLEEPINUPROAR2]               = COMPOUND_STRING("Tapi {B_DEF_NAME_WITH_PREFIX2} tak bisa tidur dalam keributan!"),
    [STRINGID_UPROARKEPTPKMNAWAKE]                  = COMPOUND_STRING("Tapi keributan membuat {B_DEF_NAME_WITH_PREFIX2} tetap terjaga!"),
    [STRINGID_PKMNSTAYEDAWAKEUSING]                 = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} tetap terjaga berkat Ability {B_DEF_ABILITY}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNSTORINGENERGY]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} sedang menyimpan energi!"),
    [STRINGID_PKMNUNLEASHEDENERGY]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} melepaskan energinya!"),
    [STRINGID_PKMNFATIGUECONFUSION]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menjadi bingung karena kelelahan!"),
    [STRINGID_PLAYERPICKEDUPMONEY]                  = COMPOUND_STRING("Kamu mengambil ¥{B_BUFF1}!\p"),
    [STRINGID_PKMNUNAFFECTED]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} tidak terpengaruh!"),
    [STRINGID_PKMNTRANSFORMEDINTO]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} berubah menjadi {B_BUFF1}!"),
    [STRINGID_PKMNMADESUBSTITUTE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} membuat substitute!"),
    [STRINGID_PKMNHASSUBSTITUTE]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} sudah memiliki substitute!"),
    [STRINGID_SUBSTITUTEDAMAGED]                    = COMPOUND_STRING("Substitute menerima damage untuk {B_DEF_NAME_WITH_PREFIX2}!\p"),
    [STRINGID_PKMNSUBSTITUTEFADED]                  = COMPOUND_STRING("Substitute milik {B_DEF_NAME_WITH_PREFIX} menghilang!\p"),
    [STRINGID_PKMNMUSTRECHARGE]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} harus recharge!"),
    [STRINGID_PKMNRAGEBUILDING]                     = COMPOUND_STRING("Kemarahan {B_DEF_NAME_WITH_PREFIX} memuncak!"),
    [STRINGID_PKMNMOVEWASDISABLED]                  = COMPOUND_STRING("{B_BUFF1} milik {B_DEF_NAME_WITH_PREFIX} dinonaktifkan!"),
    [STRINGID_PKMNMOVEISDISABLED]                   = COMPOUND_STRING("{B_CURRENT_MOVE} milik {B_ATK_NAME_WITH_PREFIX} nonaktif!\p"),
    [STRINGID_PKMNMOVEDISABLEDNOMORE]               = COMPOUND_STRING("Move milik {B_ATK_NAME_WITH_PREFIX} tidak lagi nonaktif!"),
    [STRINGID_PKMNGOTENCORE]                        = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} harus melakukan encore!"),
    [STRINGID_PKMNGOTENCOREDMOVE]                   = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} hanya bisa menggunakan {B_CURRENT_MOVE}!\p"),
    [STRINGID_PKMNENCOREENDED]                      = COMPOUND_STRING("Encore milik {B_ATK_NAME_WITH_PREFIX} berakhir!"),
    [STRINGID_PKMNTOOKAIM]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} membidik {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNSKETCHEDMOVE]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} meniru {B_BUFF1}!"),
    [STRINGID_PKMNTRYINGTOTAKEFOE]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} berharap membawa serta penyerangnya!"),
    [STRINGID_PKMNTOOKFOE]                          = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} membawa serta penyerangnya!"),
    [STRINGID_PKMNREDUCEDPP]                        = COMPOUND_STRING("PP milik {B_DEF_NAME_WITH_PREFIX} berkurang!"),
    [STRINGID_PKMNSTOLEITEM]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} mencuri {B_LAST_ITEM} milik {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_TARGETCANTESCAPENOW]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} tidak bisa kabur lagi!"),
    [STRINGID_PKMNFELLINTONIGHTMARE]                = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} mulai bermimpi buruk!"),
    [STRINGID_PKMNLOCKEDINNIGHTMARE]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terkurung dalam mimpi buruk!"),
    [STRINGID_PKMNLAIDCURSE]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} memotong HP-nya dan mengutuk {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNAFFLICTEDBYCURSE]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terkena dampak kutukan!"),
    [STRINGID_SPIKESSCATTERED]                      = COMPOUND_STRING("Spikes tersebar di sekitar tim {B_DEF_TEAM2}!"),
    [STRINGID_PKMNHURTBYSPIKES]                     = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} terluka oleh Spikes!"),
    [STRINGID_PKMNIDENTIFIED]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} teridentifikasi!"),
    [STRINGID_PKMNPERISHCOUNTFELL]                  = COMPOUND_STRING("Hitungan 'perish' {B_ATK_NAME_WITH_PREFIX} turun menjadi {B_BUFF1}!"),
    [STRINGID_PKMNBRACEDITSELF]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} mempersiapkan diri!"),
    [STRINGID_PKMNENDUREDHIT]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} berhasil menahan serangan!"),
    [STRINGID_MAGNITUDESTRENGTH]                    = COMPOUND_STRING("Magnitude {B_BUFF1}!"),
    [STRINGID_PKMNCUTHPMAXEDATTACK]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} memotong HP-nya dan memaksimalkan Attack!"),
    [STRINGID_PKMNCOPIEDSTATCHANGES]                = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} meniru perubahan stat milik {B_EFF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNGOTFREE]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terbebas dari {B_BUFF1} milik {B_DEF_NAME_WITH_PREFIX2}!"), //not in gen 5+, generic rapid spin?
    [STRINGID_PKMNSHEDLEECHSEED]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} melepaskan Leech Seed!"), //not in gen 5+, generic rapid spin?
    [STRINGID_PKMNBLEWAWAYSPIKES]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menyingkirkan Spikes!"), //not in gen 5+, generic rapid spin?
    [STRINGID_PKMNFLEDFROMBATTLE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} kabur dari pertarungan!"),
    [STRINGID_PKMNFORESAWATTACK]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} meramalkan sebuah serangan!"),
    [STRINGID_PKMNTOOKATTACK]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} menerima serangan {B_BUFF1}!"),
    [STRINGID_PKMNATTACK]                           = COMPOUND_STRING("Serangan {B_BUFF1}!"), //not in gen 5+, expansion doesn't use anymore
    [STRINGID_PKMNCENTERATTENTION]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} menjadi pusat perhatian!"),
    [STRINGID_PKMNCHARGINGPOWER]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} mulai mengisi kekuatan!"),
    [STRINGID_NATUREPOWERTURNEDINTO]                = COMPOUND_STRING("Nature Power berubah menjadi {B_CURRENT_MOVE}!"),
    [STRINGID_PKMNSTATUSNORMAL]                     = COMPOUND_STRING("Status {B_ATK_NAME_WITH_PREFIX} kembali normal!"),
    [STRINGID_PKMNHASNOMOVESLEFT]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} tidak punya move lagi yang bisa dipakai!\p"),
    [STRINGID_PKMNSUBJECTEDTOTORMENT]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} terkena torment!"),
    [STRINGID_PKMNCANTUSEMOVETORMENT]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} tak bisa pakai move yang sama 2x karena torment!\p"),
    [STRINGID_PKMNTIGHTENINGFOCUS]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} sedang mengencangkan fokusnya!"),
    [STRINGID_PKMNFELLFORTAUNT]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} terpancing oleh taunt!"),
    [STRINGID_PKMNCANTUSEMOVETAUNT]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} tak bisa pakai {B_CURRENT_MOVE} setelah terkena taunt!\p"),
    [STRINGID_PKMNREADYTOHELP]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} siap membantu {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNSWITCHEDITEMS]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menukar item dengan targetnya!"),
    [STRINGID_PKMNCOPIEDFOE]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} meniru Ability milik {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNMADEWISH]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} membuat permohonan!"), //unused
    [STRINGID_PKMNWISHCAMETRUE]                     = COMPOUND_STRING("Permohonan {B_BUFF1} terkabul!"),
    [STRINGID_PKMNPLANTEDROOTS]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menanam akarnya!"),
    [STRINGID_PKMNABSORBEDNUTRIENTS]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menyerap nutrisi dengan akarnya!"),
    [STRINGID_PKMNANCHOREDITSELF]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} menancapkan diri dengan akarnya!"),
    [STRINGID_PKMNWASMADEDROWSY]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} menjadi mengantuk!"),
    [STRINGID_PKMNKNOCKEDOFF]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menjatuhkan {B_LAST_ITEM} milik {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNSWAPPEDABILITIES]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menukar Ability dengan targetnya!"),
    [STRINGID_PKMNSEALEDOPPONENTMOVE]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menyegel semua move target yang sama dengannya!"),
    [STRINGID_PKMNCANTUSEMOVESEALED]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} tak bisa pakai {B_CURRENT_MOVE} yang disegel!\p"),
    [STRINGID_PKMNWANTSGRUDGE]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} ingin targetnya menaruh dendam!"),
    [STRINGID_PKMNLOSTPPGRUDGE]                     = COMPOUND_STRING("{B_BUFF1} milik {B_ATK_NAME_WITH_PREFIX} kehabisan PP karena dendam!"),
    [STRINGID_PKMNSHROUDEDITSELF]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menyelimuti diri dengan Magic Coat!"),
    [STRINGID_PKMNMOVEBOUNCED]                      = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} memantulkan kembali {B_CURRENT_MOVE}!"),
    [STRINGID_PKMNWAITSFORTARGET]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menunggu target untuk bergerak!"),
    [STRINGID_PKMNSNATCHEDMOVE]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} merebut move milik {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNMADEITRAIN]                       = COMPOUND_STRING("{B_SCR_ABILITY} milik {B_SCR_NAME_WITH_PREFIX} menurunkan hujan!"), //not in gen 5+, ability popup
    [STRINGID_PKMNRAISEDSPEED]                      = COMPOUND_STRING("{B_SCR_ABILITY} milik {B_SCR_NAME_WITH_PREFIX} menaikkan Speed-nya!"), //not in gen 5+, ability popup
    [STRINGID_PKMNPROTECTEDBY]                      = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} dilindungi oleh {B_DEF_ABILITY}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNPREVENTSUSAGE]                    = COMPOUND_STRING("{B_DEF_ABILITY} milik {B_DEF_NAME_WITH_PREFIX} mencegah {B_ATK_NAME_WITH_PREFIX2} menggunakan {B_CURRENT_MOVE}!"), //I don't see this in SV text
    [STRINGID_PKMNRESTOREDHPUSING]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} memulihkan HP berkat {B_DEF_ABILITY}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNCHANGEDTYPEWITH]                  = COMPOUND_STRING("{B_DEF_ABILITY} milik {B_DEF_NAME_WITH_PREFIX} mengubahnya jadi tipe {B_BUFF1}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNPREVENTSPARALYSISWITH]            = COMPOUND_STRING("{B_LAST_ABILITY} milik {B_DEF_NAME_WITH_PREFIX} mencegah kelumpuhan!"), //not in gen 5+, ability popup
    [STRINGID_PKMNPREVENTSROMANCEWITH]              = COMPOUND_STRING("{B_DEF_ABILITY} milik {B_DEF_NAME_WITH_PREFIX} mencegah jatuh cinta!"), //not in gen 5+, ability popup
    [STRINGID_PKMNPREVENTSPOISONINGWITH]            = COMPOUND_STRING("{B_LAST_ABILITY} milik {B_DEF_NAME_WITH_PREFIX} mencegah keracunan!"), //not in gen 5+, ability popup
    [STRINGID_PKMNPREVENTSCONFUSIONWITH]            = COMPOUND_STRING("{B_DEF_ABILITY} milik {B_DEF_NAME_WITH_PREFIX} mencegah kebingungan!"), //not in gen 5+, ability popup
    [STRINGID_PKMNRAISEDFIREPOWERWITH]              = COMPOUND_STRING("{B_DEF_ABILITY} milik {B_DEF_NAME_WITH_PREFIX} menaikkan kekuatan moves tipe Fire!"), //not in gen 5+, ability popup
    [STRINGID_PKMNANCHORSITSELFWITH]                = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} menancapkan diri dengan {B_DEF_ABILITY}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNCUTSATTACKWITH]                   = COMPOUND_STRING("{B_SCR_ABILITY} milik {B_SCR_NAME_WITH_PREFIX} memotong Attack {B_DEF_NAME_WITH_PREFIX2}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNPREVENTSSTATLOSSWITH]             = COMPOUND_STRING("{B_SCR_ABILITY} milik {B_SCR_NAME_WITH_PREFIX} mencegah penurunan stat!"), //not in gen 5+, ability popup
    [STRINGID_PKMNHURTSWITH]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terluka oleh {B_BUFF1} milik {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNTRACED]                           = COMPOUND_STRING("Ia meniru {B_BUFF2} milik {B_BUFF1}!"),
    [STRINGID_STATSHARPLY]                          = gText_StatSharply,
    [STRINGID_STATROSE]                             = gText_StatRose,
    [STRINGID_STATHARSHLY]                          = COMPOUND_STRING("drastis "),
    [STRINGID_STATFELL]                             = gText_StatFell,
    [STRINGID_ATTACKERSSTATROSE]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1} {B_BUFF2}"),
    [STRINGID_DEFENDERSSTATROSE]                    = gText_DefendersStatRose,
    [STRINGID_ATTACKERSSTATFELL]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX}'s {B_BUFF1} {B_BUFF2}"),
    [STRINGID_DEFENDERSSTATFELL]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX}'s {B_BUFF1} {B_BUFF2}"),
    [STRINGID_CRITICALHIT]                          = COMPOUND_STRING("Serangan kritis!"),
    [STRINGID_ONEHITKO]                             = COMPOUND_STRING("Satu pukulan KO!"),
    [STRINGID_123POOF]                              = COMPOUND_STRING("Satu…{PAUSE 10}dua…{PAUSE 10}tiga…{PAUSE 10}{PAUSE 20}{PLAY_SE SE_BALL_BOUNCE_1}tara!\p"),
    [STRINGID_ANDELLIPSIS]                          = COMPOUND_STRING("Dan…\p"),
    [STRINGID_NOTVERYEFFECTIVE]                     = COMPOUND_STRING("Tidak terlalu efektif…"),
    [STRINGID_SUPEREFFECTIVE]                       = COMPOUND_STRING("Ini sangat efektif!"),
    [STRINGID_GOTAWAYSAFELY]                        = sText_GotAwaySafely,
    [STRINGID_WILDPKMNFLED]                         = COMPOUND_STRING("{PLAY_SE SE_FLEE}{B_BUFF1} liar kabur!"),
    [STRINGID_NORUNNINGFROMTRAINERS]                = COMPOUND_STRING("Tidak bisa kabur dari pertarungan Trainer!\p"),
    [STRINGID_CANTESCAPE]                           = COMPOUND_STRING("Kamu tidak bisa kabur!\p"),
    [STRINGID_DONTLEAVEBIRCH]                       = COMPOUND_STRING("PROF. BIRCH: Jangan tinggalkan aku seperti ini!\p"), //no decapitalize until it is everywhere
    [STRINGID_BUTNOTHINGHAPPENED]                   = COMPOUND_STRING("Tapi tidak terjadi apa-apa!"),
    [STRINGID_BUTITFAILED]                          = COMPOUND_STRING("Tapi gagal!"),
    [STRINGID_ITHURTCONFUSION]                      = COMPOUND_STRING("Ia melukai dirinya sendiri karena bingung!"),
    [STRINGID_MIRRORMOVEFAILED]                     = COMPOUND_STRING("Mirror Move gagal!"), //not in gen 5+, uses "but it failed"
    [STRINGID_STARTEDTORAIN]                        = COMPOUND_STRING("Hujan mulai turun!"),
    [STRINGID_DOWNPOURSTARTED]                      = COMPOUND_STRING("Hujan deras mulai turun!"), // corresponds to DownpourText in pokegold and pokecrystal and is used by Rain Dance in GSC
    [STRINGID_RAINCONTINUES]                        = COMPOUND_STRING("Hujan terus turun."), //not in gen 5+
    [STRINGID_DOWNPOURCONTINUES]                    = COMPOUND_STRING("Hujan deras terus berlanjut."), // unused
    [STRINGID_RAINSTOPPED]                          = COMPOUND_STRING("Hujan berhenti."),
    [STRINGID_SANDSTORMBREWED]                      = COMPOUND_STRING("Badai pasir menerpa!"),
    [STRINGID_SANDSTORMRAGES]                       = COMPOUND_STRING("Badai pasir mengamuk."),
    [STRINGID_SANDSTORMSUBSIDED]                    = COMPOUND_STRING("Badai pasir mereda."),
    [STRINGID_SUNLIGHTGOTBRIGHT]                    = COMPOUND_STRING("Cahaya matahari menjadi terik!"),
    [STRINGID_SUNLIGHTSTRONG]                       = COMPOUND_STRING("Cahaya matahari sangat kuat."), //not in gen 5+
    [STRINGID_SUNLIGHTFADED]                        = COMPOUND_STRING("Cahaya matahari meredup."),
    [STRINGID_STARTEDHAIL]                          = COMPOUND_STRING("Hujan es mulai turun!"),
    [STRINGID_HAILCONTINUES]                        = COMPOUND_STRING("Hujan es terus turun."),
    [STRINGID_HAILSTOPPED]                          = COMPOUND_STRING("Hujan es berhenti."),
    [STRINGID_FAILEDTOSPITUP]                       = COMPOUND_STRING("Tapi gagal memuntahkan apa pun!"), //not in gen 5+, uses "but it failed"
    [STRINGID_FAILEDTOSWALLOW]                      = COMPOUND_STRING("Tapi gagal menelan apa pun!"), //not in gen 5+, uses "but it failed"
    [STRINGID_WINDBECAMEHEATWAVE]                   = COMPOUND_STRING("Angin berubah menjadi Heat Wave!"), //unused
    [STRINGID_STATCHANGESGONE]                      = COMPOUND_STRING("Semua perubahan stat dihilangkan!"),
    [STRINGID_COINSSCATTERED]                       = COMPOUND_STRING("Koin tersebar di mana-mana!"),
    [STRINGID_TOOWEAKFORSUBSTITUTE]                 = COMPOUND_STRING("Tapi HP yang tersisa tidak cukup untuk membuat substitute!"),
    [STRINGID_SHAREDPAIN]                           = COMPOUND_STRING("Para petarung berbagi rasa sakit!"),
    [STRINGID_BELLCHIMED]                           = COMPOUND_STRING("Sebuah lonceng berbunyi!"),
    [STRINGID_FAINTINTHREE]                         = COMPOUND_STRING("Semua Pokémon yang mendengar lagu akan pingsan dalam tiga giliran!"),
    [STRINGID_NOPPLEFT]                             = COMPOUND_STRING("Tidak ada PP tersisa untuk move ini!\p"), //not in gen 5+
    [STRINGID_BUTNOPPLEFT]                          = COMPOUND_STRING("Tapi tidak ada PP tersisa untuk move itu!"),
    [STRINGID_PLAYERUSEDITEM]                       = COMPOUND_STRING("Kamu menggunakan {B_LAST_ITEM}!"),
    [STRINGID_WALLYUSEDITEM]                        = COMPOUND_STRING("WALLY menggunakan {B_LAST_ITEM}!"), //no decapitalize until it is everywhere
    [STRINGID_TRAINERBLOCKEDBALL]                   = COMPOUND_STRING("Trainer itu menahan Poké Ball-mu!"),
    [STRINGID_DONTBEATHIEF]                         = COMPOUND_STRING("Jangan jadi pencuri!"),
    [STRINGID_ITDODGEDBALL]                         = COMPOUND_STRING("Ia menghindari Poké Ball-mu! Pokémon ini tak bisa ditangkap!"),
    [STRINGID_YOUMISSEDPKMN]                        = COMPOUND_STRING("Lemparanmu meleset dari Pokémon!"),
    [STRINGID_PKMNBROKEFREE]                        = COMPOUND_STRING("Oh tidak! Pokémon itu berhasil lepas!"),
    [STRINGID_ITAPPEAREDCAUGHT]                     = COMPOUND_STRING("Aww! Kelihatannya sudah tertangkap!"),
    [STRINGID_AARGHALMOSTHADIT]                     = COMPOUND_STRING("Aargh! Hampir saja dapat!"),
    [STRINGID_SHOOTSOCLOSE]                         = COMPOUND_STRING("Gah! Padahal sudah dekat sekali!"),
    [STRINGID_GOTCHAPKMNCAUGHTPLAYER]               = COMPOUND_STRING("Dapat! {B_DEF_NAME} tertangkap!{WAIT_SE}{PLAY_BGM MUS_CAUGHT}\p"),
    [STRINGID_GOTCHAPKMNCAUGHTWALLY]                = COMPOUND_STRING("Dapat! {B_DEF_NAME} tertangkap!{WAIT_SE}{PLAY_BGM MUS_CAUGHT}{PAUSE 127}"),
    [STRINGID_GIVENICKNAMECAPTURED]                 = COMPOUND_STRING("Apakah kamu ingin memberi {B_DEF_NAME} nama panggilan?"),
    [STRINGID_PKMNSENTTOPC]                         = COMPOUND_STRING("{B_DEF_NAME} telah dikirim ke PC milik {B_PC_CREATOR_NAME}!"), //Still used lanette's pc since terminology is different
    [STRINGID_PKMNDATAADDEDTODEX]                   = COMPOUND_STRING("Data {B_DEF_NAME} telah ditambahkan ke Pokédex!\p"),
    [STRINGID_ITISRAINING]                          = COMPOUND_STRING("Hujan turun!"),
    [STRINGID_SANDSTORMISRAGING]                    = COMPOUND_STRING("Badai pasir sedang mengamuk!"),
    [STRINGID_CANTESCAPE2]                          = COMPOUND_STRING("Kamu tidak berhasil kabur!\p"),
    [STRINGID_PKMNIGNORESASLEEP]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} mengabaikan perintah dan terus tidur!"),
    [STRINGID_PKMNIGNOREDORDERS]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} mengabaikan perintah!"),
    [STRINGID_PKMNBEGANTONAP]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} mulai tidur siang!"),
    [STRINGID_PKMNLOAFING]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} sedang bermalas-malasan!"),
    [STRINGID_PKMNWONTOBEY]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} tidak mau patuh!"),
    [STRINGID_PKMNTURNEDAWAY]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} membuang muka!"),
    [STRINGID_PKMNPRETENDNOTNOTICE]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} pura-pura tidak sadar!"),
    [STRINGID_ENEMYABOUTTOSWITCHPKMN]               = COMPOUND_STRING("{B_TRAINER1_NAME_WITH_CLASS} akan mengeluarkan {B_BUFF2}.\pGanti Pokémon-mu?"),
    [STRINGID_CREPTCLOSER]                          = COMPOUND_STRING("{B_PLAYER_NAME} merayap mendekati {B_OPPONENT_MON1_NAME}!"), //safari
    [STRINGID_CANTGETCLOSER]                        = COMPOUND_STRING("{B_PLAYER_NAME} tidak bisa lebih dekat lagi!"), //safari
    [STRINGID_PKMNWATCHINGCAREFULLY]                = COMPOUND_STRING("{B_OPPONENT_MON1_NAME} mengamati dengan saksama!"), //safari
    [STRINGID_PKMNCURIOUSABOUTX]                    = COMPOUND_STRING("{B_OPPONENT_MON1_NAME} penasaran dengan {B_BUFF1}!"), //safari
    [STRINGID_PKMNENTHRALLEDBYX]                    = COMPOUND_STRING("{B_OPPONENT_MON1_NAME} terpikat oleh {B_BUFF1}!"), //safari
    [STRINGID_PKMNIGNOREDX]                         = COMPOUND_STRING("{B_OPPONENT_MON1_NAME} sama sekali mengabaikan {B_BUFF1}!"), //safari
    [STRINGID_THREWPOKEBLOCKATPKMN]                 = COMPOUND_STRING("{B_PLAYER_NAME} melempar {POKEBLOCK} ke {B_OPPONENT_MON1_NAME}!"), //safari
    [STRINGID_OUTOFSAFARIBALLS]                     = COMPOUND_STRING("{PLAY_SE SE_DING_DONG}PENGUMUMAN: Safari Ball habis! Permainan selesai!\p"), //safari
    [STRINGID_PKMNSITEMCUREDPARALYSIS]              = COMPOUND_STRING("{B_LAST_ITEM} milik {B_SCR_NAME_WITH_PREFIX} menyembuhkan kelumpuhannya!"),
    [STRINGID_PKMNSITEMCUREDPOISON]                 = COMPOUND_STRING("{B_LAST_ITEM} milik {B_SCR_NAME_WITH_PREFIX} menyembuhkan racunnya!"),
    [STRINGID_PKMNSITEMHEALEDBURN]                  = COMPOUND_STRING("{B_LAST_ITEM} milik {B_SCR_NAME_WITH_PREFIX} menyembuhkan luka bakarnya!"),
    [STRINGID_PKMNSITEMDEFROSTEDIT]                 = COMPOUND_STRING("{B_LAST_ITEM} milik {B_SCR_NAME_WITH_PREFIX} mencairkannya!"),
    [STRINGID_PKMNSITEMWOKEIT]                      = COMPOUND_STRING("{B_LAST_ITEM} milik {B_SCR_NAME_WITH_PREFIX} membangunkannya!"),
    [STRINGID_PKMNSITEMSNAPPEDOUT]                  = COMPOUND_STRING("{B_LAST_ITEM} milik {B_SCR_NAME_WITH_PREFIX} menyadarkannya dari bingung!"),
    [STRINGID_PKMNSITEMCUREDPROBLEM]                = COMPOUND_STRING("{B_LAST_ITEM} milik {B_SCR_NAME_WITH_PREFIX} menyembuhkan masalah {B_BUFF1}-nya!"),
    [STRINGID_PKMNSITEMRESTOREDHEALTH]              = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} memulihkan HP-nya dengan {B_LAST_ITEM}!"),
    [STRINGID_PKMNSITEMRESTOREDPP]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} memulihkan PP move {B_BUFF1} dengan {B_LAST_ITEM}!"),
    [STRINGID_PKMNSITEMRESTOREDSTATUS]              = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} memulihkan stat-nya dengan {B_LAST_ITEM}!"),
    [STRINGID_PKMNSITEMRESTOREDHPALITTLE]           = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} memulihkan sedikit HP dengan {B_LAST_ITEM}!"),
    [STRINGID_ITEMALLOWSONLYYMOVE]                  = COMPOUND_STRING("{B_LAST_ITEM} hanya mengizinkan penggunaan {B_CURRENT_MOVE}!\p"),
    [STRINGID_PKMNHUNGONWITHX]                      = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} bertahan berkat {B_LAST_ITEM}-nya!"),
    [STRINGID_EMPTYSTRING3]                         = gText_EmptyString3,
    [STRINGID_PKMNSXPREVENTSBURNS]                  = COMPOUND_STRING("{B_LAST_ABILITY} milik {B_DEF_NAME_WITH_PREFIX} mencegah luka bakar!"), //not in gen 5+, ability popup
    [STRINGID_PKMNSXBLOCKSY]                        = COMPOUND_STRING("{B_DEF_ABILITY} milik {B_DEF_NAME_WITH_PREFIX} menahan {B_CURRENT_MOVE}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNSXRESTOREDHPALITTLE2]             = COMPOUND_STRING("{B_ATK_ABILITY} milik {B_ATK_NAME_WITH_PREFIX} memulihkan sedikit HP!"), //not in gen 5+, ability popup
    [STRINGID_PKMNSXWHIPPEDUPSANDSTORM]             = COMPOUND_STRING("{B_SCR_ABILITY} milik {B_SCR_NAME_WITH_PREFIX} menciptakan badai pasir!"), //not in gen 5+, ability popup
    [STRINGID_PKMNSXPREVENTSYLOSS]                  = COMPOUND_STRING("{B_SCR_ABILITY} milik {B_SCR_NAME_WITH_PREFIX} mencegah hilangnya {B_BUFF1}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNSXINFATUATEDY]                    = COMPOUND_STRING("{B_DEF_ABILITY} milik {B_DEF_NAME_WITH_PREFIX} membuat {B_ATK_NAME_WITH_PREFIX2} jatuh cinta!"), //not in gen 5+, ability popup
    [STRINGID_PKMNSXMADEYINEFFECTIVE]               = COMPOUND_STRING("{B_DEF_ABILITY} milik {B_DEF_NAME_WITH_PREFIX} membuat {B_CURRENT_MOVE} tak berefek!"), //not in gen 5+, ability popup
    [STRINGID_PKMNSXCUREDYPROBLEM]                  = COMPOUND_STRING("{B_SCR_ABILITY} milik {B_SCR_NAME_WITH_PREFIX} menyembuhkan masalah {B_BUFF1}-nya!"), //not in gen 5+, ability popup
    [STRINGID_ITSUCKEDLIQUIDOOZE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menyedot cairan lengket!"),
    [STRINGID_PKMNTRANSFORMED]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} berubah wujud!"),
    [STRINGID_ELECTRICITYWEAKENED]                  = COMPOUND_STRING("Kekuatan listrik melemah!"),
    [STRINGID_FIREWEAKENED]                         = COMPOUND_STRING("Kekuatan api melemah!"),
    [STRINGID_PKMNHIDUNDERWATER]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} bersembunyi di bawah air!"),
    [STRINGID_PKMNSPRANGUP]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} melompat ke atas!"),
    [STRINGID_HMMOVESCANTBEFORGOTTEN]               = COMPOUND_STRING("HM moves tidak bisa dilupakan sekarang.\p"),
    [STRINGID_XFOUNDONEY]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menemukan sebuah {B_LAST_ITEM}!"),
    [STRINGID_PLAYERDEFEATEDTRAINER1]               = sText_PlayerDefeatedLinkTrainerTrainer1,
[STRINGID_SOOTHINGAROMA]                        = COMPOUND_STRING("Aroma menenangkan menyebar ke seluruh area!"),
    [STRINGID_ITEMSCANTBEUSEDNOW]                   = COMPOUND_STRING("Item tidak bisa dipakai sekarang.{PAUSE 64}"), //not in gen 5+, i think
    [STRINGID_FORXCOMMAYZ]                          = COMPOUND_STRING("Untuk {B_SCR_NAME_WITH_PREFIX2}, {B_LAST_ITEM} {B_BUFF1}"), //not in gen 5+, expansion doesn't use anymore
    [STRINGID_USINGITEMSTATOFPKMNROSE]              = COMPOUND_STRING("Menggunakan {B_LAST_ITEM}, {B_BUFF1} dari {B_SCR_NAME_WITH_PREFIX2} {B_BUFF2}"), //todo: update this, will require code changes
    [STRINGID_PKMNUSEDXTOGETPUMPED]                 = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} menggunakan {B_LAST_ITEM} untuk bersemangat!"),
    [STRINGID_PKMNSXMADEYUSELESS]                   = COMPOUND_STRING("{B_DEF_ABILITY} milik {B_DEF_NAME_WITH_PREFIX} membuat {B_CURRENT_MOVE} tak berguna!"), //not in gen 5+, ability popup
    [STRINGID_PKMNTRAPPEDBYSANDTOMB]                = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} terjebak dalam pasir hisap!"),
    [STRINGID_EMPTYSTRING4]                         = COMPOUND_STRING(""),
    [STRINGID_ABOOSTED]                             = COMPOUND_STRING(" yang ditingkatkan"),
    [STRINGID_PKMNSXINTENSIFIEDSUN]                 = COMPOUND_STRING("{B_SCR_ABILITY} milik {B_SCR_NAME_WITH_PREFIX} mengintensifkan sinar matahari!"), //not in gen 5+, ability popup
    [STRINGID_PKMNMAKESGROUNDMISS]                  = COMPOUND_STRING("{B_DEF_ABILITY} milik {B_DEF_NAME_WITH_PREFIX} membuat moves tipe Ground gagal!"), //not in gen 5+, ability popup
    [STRINGID_YOUTHROWABALLNOWRIGHT]                = COMPOUND_STRING("Kamu akan lempar Bola sekarang, kan? A… Aku akan berusaha!"),
    [STRINGID_PKMNSXTOOKATTACK]                     = COMPOUND_STRING("{B_DEF_ABILITY} milik {B_DEF_NAME_WITH_PREFIX} menerima serangan!"), //In gen 5+ but without naming the ability
    [STRINGID_PKMNCHOSEXASDESTINY]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} memilih Doom Desire sebagai takdirnya!"),
    [STRINGID_PKMNLOSTFOCUS]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} kehilangan fokus dan tak bisa bergerak!"),
    [STRINGID_USENEXTPKMN]                          = COMPOUND_STRING("Gunakan Pokémon berikutnya?"),
    [STRINGID_PKMNFLEDUSINGITS]                     = COMPOUND_STRING("{PLAY_SE SE_FLEE}{B_ATK_NAME_WITH_PREFIX} kabur menggunakan {B_LAST_ITEM}!\p"),
    [STRINGID_PKMNFLEDUSING]                        = COMPOUND_STRING("{PLAY_SE SE_FLEE}{B_ATK_NAME_WITH_PREFIX} kabur menggunakan {B_ATK_ABILITY}!\p"), //not in gen 5+
    [STRINGID_PKMNWASDRAGGEDOUT]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} ditarik keluar!\p"),
    [STRINGID_PREVENTEDFROMWORKING]                 = COMPOUND_STRING("{B_DEF_ABILITY} milik {B_DEF_NAME_WITH_PREFIX} mencegah {B_BUFF1} {B_SCR_NAME_WITH_PREFIX2} bekerja!"), //unused
    [STRINGID_PKMNSITEMNORMALIZEDSTATUS]            = COMPOUND_STRING("{B_LAST_ITEM} milik {B_SCR_NAME_WITH_PREFIX} menormalkan statusnya!"),
    [STRINGID_TRAINER1USEDITEM]                     = COMPOUND_STRING("{B_ATK_TRAINER_NAME_WITH_CLASS} menggunakan {B_LAST_ITEM}!"),
    [STRINGID_BOXISFULL]                            = COMPOUND_STRING("Box sudah penuh! Kamu tak bisa menangkap lagi!\p"),
    [STRINGID_PKMNAVOIDEDATTACK]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} menghindari serangan!"),
    [STRINGID_PKMNSXMADEITINEFFECTIVE]              = COMPOUND_STRING("{B_SCR_ABILITY} milik {B_SCR_NAME_WITH_PREFIX} membuatnya tak berefek!"), //not in gen 5+, ability popup
    [STRINGID_PKMNSXPREVENTSFLINCHING]              = COMPOUND_STRING("{B_EFF_ABILITY} milik {B_EFF_NAME_WITH_PREFIX} mencegah flinch!"), //not in gen 5+, ability popup
    [STRINGID_PKMNALREADYHASBURN]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} sudah terbakar!"),
    [STRINGID_STATSWONTDECREASE2]                   = COMPOUND_STRING("Stat milik {B_DEF_NAME_WITH_PREFIX} tak bisa lebih rendah lagi!"),
    [STRINGID_PKMNSXBLOCKSY2]                       = COMPOUND_STRING("{B_SCR_ABILITY} milik {B_SCR_NAME_WITH_PREFIX} menahan {B_CURRENT_MOVE}!"), //not in gen 5+, ability popup
    [STRINGID_PKMNSXWOREOFF]                        = COMPOUND_STRING("Efek {B_BUFF1} tim {B_ATK_TEAM1} telah habis!"),
    [STRINGID_PKMNRAISEDDEFALITTLE]                 = COMPOUND_STRING("{B_CURRENT_MOVE} milik {B_ATK_PREFIX1} menaikkan sedikit DEFENSE!"), //expansion doesn't use anymore
    [STRINGID_PKMNRAISEDSPDEFALITTLE]               = COMPOUND_STRING("{B_CURRENT_MOVE} milik {B_ATK_PREFIX1} menaikkan sedikit SP. DEF!"), //expansion doesn't use anymore
    [STRINGID_THEWALLSHATTERED]                     = COMPOUND_STRING("Dindingnya hancur!"), //not in gen5+, uses "your teams light screen wore off!" etc instead
    [STRINGID_PKMNSXPREVENTSYSZ]                    = COMPOUND_STRING("{B_ATK_ABILITY} milik {B_ATK_NAME_WITH_PREFIX} mencegah {B_DEF_ABILITY} {B_DEF_NAME_WITH_PREFIX2} bekerja!"),
    [STRINGID_PKMNSXCUREDITSYPROBLEM]               = COMPOUND_STRING("{B_SCR_ABILITY} milik {B_SCR_NAME_WITH_PREFIX} menyembuhkan masalah {B_BUFF1}-nya!"), //not in gen 5+, ability popup
    [STRINGID_ATTACKERCANTESCAPE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} tidak bisa kabur!"),
    [STRINGID_PKMNOBTAINEDX]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} memperoleh {B_BUFF1}."),
    [STRINGID_PKMNOBTAINEDX2]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} memperoleh {B_BUFF2}."),
    [STRINGID_PKMNOBTAINEDXYOBTAINEDZ]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} memperoleh {B_BUFF1}.\p{B_DEF_NAME_WITH_PREFIX} memperoleh {B_BUFF2}."),
    [STRINGID_BUTNOEFFECT]                          = COMPOUND_STRING("Tapi tidak ada efeknya!"),
    [STRINGID_PKMNSXHADNOEFFECTONY]                 = COMPOUND_STRING("Target dilindungi oleh {B_LAST_ABILITY}!"), //not in gen 5+, ability popup
    [STRINGID_TWOENEMIESDEFEATED]                   = sText_TwoInGameTrainersDefeated,
    [STRINGID_TRAINER2LOSETEXT]                     = COMPOUND_STRING("{B_TRAINER2_LOSE_TEXT}"),
    [STRINGID_PKMNINCAPABLEOFPOWER]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} sepertinya tak mampu memakai kekuatannya!"),
    [STRINGID_GLINTAPPEARSINEYE]                    = COMPOUND_STRING("Kilatan muncul di mata {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNGETTINGINTOPOSITION]              = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} sedang mengambil posisi!"),
    [STRINGID_PKMNBEGANGROWLINGDEEPLY]              = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} mulai menggeram dalam!"),
    [STRINGID_PKMNEAGERFORMORE]                     = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} bersemangat untuk lagi!"),
    [STRINGID_DEFEATEDOPPONENTBYREFEREE]            = COMPOUND_STRING("{B_PLAYER_MON1_NAME} mengalahkan lawan {B_OPPONENT_MON1_NAME} berdasarkan keputusan WASIT!"),
    [STRINGID_LOSTTOOPPONENTBYREFEREE]              = COMPOUND_STRING("{B_PLAYER_MON1_NAME} kalah dari lawan {B_OPPONENT_MON1_NAME} berdasarkan keputusan WASIT!"),
    [STRINGID_TIEDOPPONENTBYREFEREE]                = COMPOUND_STRING("{B_PLAYER_MON1_NAME} seri dengan lawan {B_OPPONENT_MON1_NAME} berdasarkan keputusan WASIT!"),
    [STRINGID_QUESTIONFORFEITMATCH]                 = COMPOUND_STRING("Apakah kamu ingin menyerah dan keluar dari pertandingan sekarang?"),
    [STRINGID_FORFEITEDMATCH]                       = COMPOUND_STRING("Pertandingan ini diserahkan."),
    [STRINGID_PKMNTRANSFERREDSOMEONESPC]            = gText_PkmnTransferredSomeonesPC,
    [STRINGID_PKMNTRANSFERREDLANETTESPC]            = gText_PkmnTransferredLanettesPC,
    [STRINGID_PKMNBOXSOMEONESPCFULL]                = gText_PkmnTransferredSomeonesPCBoxFull,
    [STRINGID_PKMNBOXLANETTESPCFULL]                = gText_PkmnTransferredLanettesPCBoxFull,
    [STRINGID_TRAINER1WINTEXT]                      = COMPOUND_STRING("{B_TRAINER1_WIN_TEXT}"),
    [STRINGID_TRAINER2WINTEXT]                      = COMPOUND_STRING("{B_TRAINER2_WIN_TEXT}"),
[STRINGID_ENDUREDSTURDY]                        = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} menahan serangan berkat {B_DEF_ABILITY}!"),
    [STRINGID_POWERHERB]                            = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terisi penuh berkat {B_LAST_ITEM}!"),
    [STRINGID_HURTBYITEM]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terluka oleh {B_LAST_ITEM}!"),
    [STRINGID_PSNBYITEM]                            = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} terkena racun parah dari {B_LAST_ITEM}!"),
    [STRINGID_BRNBYITEM]                            = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} terbakar oleh {B_LAST_ITEM}!"),
    [STRINGID_DEFABILITYIN]                         = COMPOUND_STRING("Ability {B_DEF_ABILITY} milik {B_DEF_NAME_WITH_PREFIX} aktif!"),
    [STRINGID_GRAVITYINTENSIFIED]                   = COMPOUND_STRING("Gravitasi menguat!"),
    [STRINGID_TARGETIDENTIFIED]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} teridentifikasi!"),
    [STRINGID_TARGETWOKEUP]                         = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} terbangun!"),
    [STRINGID_PKMNSTOLEANDATEITEM]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} mencuri dan memakan {B_LAST_ITEM} milik targetnya!"),
    [STRINGID_TAILWINDBLEW]                         = COMPOUND_STRING("Tailwind berhembus dari belakang tim {B_ATK_TEAM2}!"),
    [STRINGID_PKMNWENTBACK]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} kembali pada {B_ATK_TRAINER_NAME}!"),
    [STRINGID_PKMNCANTUSEITEMSANYMORE]              = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} tidak bisa memakai item lagi!"),
    [STRINGID_PKMNFLUNG]                            = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} melempar {B_LAST_ITEM}-nya!"),
    [STRINGID_PKMNPREVENTEDFROMHEALING]             = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} terhalang untuk memulihkan diri!"),
    [STRINGID_PKMNSWITCHEDATKANDDEF]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menukar stat Attack dan Defense-nya!"),
    [STRINGID_PKMNSABILITYSUPPRESSED]               = COMPOUND_STRING("Ability milik {B_DEF_NAME_WITH_PREFIX} ditekan!"),
    [STRINGID_SHIELDEDFROMCRITICALHITS]             = COMPOUND_STRING("Lucky Chant melindungi tim {B_ATK_TEAM2} dari critical hit!"),
    [STRINGID_SWITCHEDATKANDSPATK]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menukar semua perubahan Attack dan Sp. Atk\pdengan targetnya!"),
    [STRINGID_SWITCHEDDEFANDSPDEF]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menukar semua perubahan Defense dan Sp. Def\pdengan targetnya!"),
    [STRINGID_PKMNACQUIREDABILITY]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} memperoleh {B_DEF_ABILITY}!"),
    [STRINGID_POISONSPIKESSCATTERED]                = COMPOUND_STRING("Duri beracun tersebar di sekitar tim {B_DEF_TEAM2}!"),
    [STRINGID_PKMNSWITCHEDSTATCHANGES]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menukar perubahan stat dengan targetnya!"),
    [STRINGID_PKMNSURROUNDEDWITHVEILOFWATER]        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menyelimuti diri dengan selubung air!"),
    [STRINGID_PKMNLEVITATEDONELECTROMAGNETISM]      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} melayang dengan elektromagnetisme!"),
    [STRINGID_PKMNTWISTEDDIMENSIONS]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} memutarbalikkan dimensi!"),
    [STRINGID_POINTEDSTONESFLOAT]                   = COMPOUND_STRING("Batu runcing melayang di udara sekitar tim {B_DEF_TEAM2}!"),
    [STRINGID_CLOAKEDINMYSTICALMOONLIGHT]           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} diselimuti cahaya bulan mistis!"),
    [STRINGID_TRAPPEDBYSWIRLINGMAGMA]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} terjebak oleh pusaran magma!"),
    [STRINGID_VANISHEDINSTANTLY]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menghilang seketika!"),
    [STRINGID_PROTECTEDTEAM]                        = COMPOUND_STRING("{B_CURRENT_MOVE} melindungi tim {B_ATK_TEAM2}!"),
    [STRINGID_SHAREDITSGUARD]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} berbagi pertahanan dengan target!"),
    [STRINGID_SHAREDITSPOWER]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} berbagi kekuatan dengan target!"),
    [STRINGID_SWAPSDEFANDSPDEFOFALLPOKEMON]         = COMPOUND_STRING("Area aneh tercipta, stat Defense dan Sp. Def tertukar!"),
    [STRINGID_BECAMENIMBLE]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menjadi gesit!"),
    [STRINGID_HURLEDINTOTHEAIR]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} terlempar ke udara!"),
    [STRINGID_HELDITEMSLOSEEFFECTS]                 = COMPOUND_STRING("Area aneh tercipta, efek item yang dipegang Pokémon hilang!"),
    [STRINGID_FELLSTRAIGHTDOWN]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} jatuh lurus ke bawah!"),
    [STRINGID_TARGETCHANGEDTYPE]                    = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} berubah menjadi tipe {B_BUFF1}!"),
    [STRINGID_PKMNACQUIREDSIMPLE]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} memperoleh Simple!"), //shouldn't directly use the name
    [STRINGID_EMPTYSTRING5]                         = sText_EmptyString4,
    [STRINGID_KINDOFFER]                            = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} menerima tawaran baik!"),
    [STRINGID_RESETSTARGETSSTATLEVELS]              = COMPOUND_STRING("Perubahan stat milik {B_DEF_NAME_WITH_PREFIX} dihapus!"),
    [STRINGID_EMPTYSTRING6]                         = sText_EmptyString4,
    [STRINGID_ALLYSWITCHPOSITION]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} dan {B_SCR_NAME_WITH_PREFIX2} bertukar tempat!"),
    [STRINGID_RESTORETARGETSHEALTH]                 = COMPOUND_STRING("HP milik {B_DEF_NAME_WITH_PREFIX} pulih kembali!"),
    [STRINGID_TOOKPJMNINTOTHESKY]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} membawa {B_DEF_NAME_WITH_PREFIX2} ke angkasa!"),
    [STRINGID_FREEDFROMSKYDROP]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} terbebas dari Sky Drop!"),
    [STRINGID_POSTPONETARGETMOVE]                   = COMPOUND_STRING("Move milik {B_DEF_NAME_WITH_PREFIX} ditunda!"),
    [STRINGID_REFLECTTARGETSTYPE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menjadi setipe dengan {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_TRANSFERHELDITEM]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} menerima {B_LAST_ITEM} dari {B_ATK_NAME_WITH_PREFIX2}"),
    [STRINGID_EMBARGOENDS]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} bisa menggunakan item lagi!"),
    [STRINGID_ELECTROMAGNETISM]                     = COMPOUND_STRING("elektromagnetisme"),
    [STRINGID_BUFFERENDS]                           = COMPOUND_STRING("Efek {B_BUFF1} pada {B_ATK_NAME_WITH_PREFIX} telah habis!"),
    [STRINGID_TELEKINESISENDS]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terbebas dari telekinesis!"),
    [STRINGID_TAILWINDENDS]                         = COMPOUND_STRING("Tailwind tim {B_ATK_TEAM1} mereda!"),
    [STRINGID_LUCKYCHANTENDS]                       = COMPOUND_STRING("Lucky Chant tim {B_ATK_TEAM1} telah habis!"),
    [STRINGID_TRICKROOMENDS]                        = COMPOUND_STRING("Dimensi yang terputar kembali normal!"),
    [STRINGID_WONDERROOMENDS]                       = COMPOUND_STRING("Wonder Room berakhir, stat Defense dan Sp. Def kembali normal!"),
    [STRINGID_MAGICROOMENDS]                        = COMPOUND_STRING("Magic Room berakhir, efek item yang dipegang kembali normal!"),
    [STRINGID_MUDSPORTENDS]                         = COMPOUND_STRING("Efek dari Mud Sport telah memudar."),
    [STRINGID_WATERSPORTENDS]                       = COMPOUND_STRING("Efek dari Water Sport telah memudar."),
    [STRINGID_GRAVITYENDS]                          = COMPOUND_STRING("Gravitasi kembali normal!"),
    [STRINGID_AQUARINGHEAL]                         = COMPOUND_STRING("Selubung air memulihkan HP milik {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_ELECTRICTERRAINENDS]                  = COMPOUND_STRING("Listrik menghilang dari medan pertempuran."),
    [STRINGID_MISTYTERRAINENDS]                     = COMPOUND_STRING("Kabut menghilang dari medan pertempuran."),
    [STRINGID_PSYCHICTERRAINENDS]                   = COMPOUND_STRING("Keanehan menghilang dari medan pertempuran!"),
    [STRINGID_GRASSYTERRAINENDS]                    = COMPOUND_STRING("Rerumputan menghilang dari medan pertempuran."),
    [STRINGID_TARGETABILITYSTATRAISE]               = COMPOUND_STRING("{B_DEF_ABILITY} milik {B_DEF_NAME_WITH_PREFIX} menaikkan {B_BUFF1}-nya!"),
    [STRINGID_TARGETSSTATWASMAXEDOUT]               = COMPOUND_STRING("{B_DEF_ABILITY} milik {B_DEF_NAME_WITH_PREFIX} memaksimalkan {B_BUFF1}-nya!"),
    [STRINGID_ATTACKERABILITYSTATRAISE]             = COMPOUND_STRING("{B_SCR_ABILITY} milik {B_SCR_NAME_WITH_PREFIX} menaikkan {B_BUFF1}-nya!"),
    [STRINGID_POISONHEALHPUP]                       = COMPOUND_STRING("Racun itu memulihkan sedikit HP {B_ATK_NAME_WITH_PREFIX2}!"), //don't think this message is displayed anymore
    [STRINGID_BADDREAMSDMG]                         = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} tersiksa!"),
    [STRINGID_MOLDBREAKERENTERS]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} mematahkan cetakan!"),
    [STRINGID_TERAVOLTENTERS]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} memancarkan aura yang meledak!"),
    [STRINGID_TURBOBLAZEENTERS]                     = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} memancarkan aura yang membara!"),
[STRINGID_SLOWSTARTENTERS]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} lambat untuk memulai!"),
    [STRINGID_SLOWSTARTEND]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} akhirnya mulai beraksi!"),
    [STRINGID_SOLARPOWERHPDROP]                     = COMPOUND_STRING("{B_ATK_ABILITY} milik {B_ATK_NAME_WITH_PREFIX} memakan korban!"), //don't think this message is displayed anymore
    [STRINGID_AFTERMATHDMG]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terluka!"),
    [STRINGID_ANTICIPATIONACTIVATES]                = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} bergidik!"),
    [STRINGID_FOREWARNACTIVATES]                    = COMPOUND_STRING("{B_SCR_ABILITY} memperingati {B_SCR_NAME_WITH_PREFIX2} akan {B_BUFF1} milik {B_EFF_NAME_WITH_PREFIX2}!"),
    [STRINGID_ICEBODYHPGAIN]                        = COMPOUND_STRING("{B_ATK_ABILITY} milik {B_ATK_NAME_WITH_PREFIX} memulihkannya sedikit!"), //don't think this message is displayed anymore
    [STRINGID_SNOWWARNINGHAIL]                      = COMPOUND_STRING("Hujan es mulai turun!"),
    [STRINGID_FRISKACTIVATES]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} memeriksa {B_DEF_NAME_WITH_PREFIX2} dan menemukan {B_LAST_ITEM}!"),
    [STRINGID_UNNERVEENTERS]                        = COMPOUND_STRING("Tim {B_EFF_TEAM1} terlalu gugup untuk makan Berry!"),
    [STRINGID_HARVESTBERRY]                         = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} memanen {B_LAST_ITEM}-nya!"),
    [STRINGID_MAGICBOUNCEACTIVATES]                 = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} memantulkan kembali {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_PROTEANTYPECHANGE]                    = COMPOUND_STRING("{B_ATK_ABILITY} milik {B_ATK_NAME_WITH_PREFIX} mengubahnya jadi tipe {B_BUFF1}!"),
    [STRINGID_SYMBIOSISITEMPASS]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} memberikan {B_LAST_ITEM} ke {B_EFF_NAME_WITH_PREFIX2} lewat {B_LAST_ABILITY}!"),
    [STRINGID_STEALTHROCKDMG]                       = COMPOUND_STRING("Batu runcing menusuk {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_TOXICSPIKESABSORBED]                  = COMPOUND_STRING("Duri beracun menghilang dari sekitar tim {B_EFF_TEAM2}!"),
    [STRINGID_TOXICSPIKESPOISONED]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} terkena racun!"),
    [STRINGID_TOXICSPIKESBADLYPOISONED]             = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} terkena racun parah!"),
    [STRINGID_STICKYWEBSWITCHIN]                    = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} terperangkap di jaring lengket!"),
    [STRINGID_HEALINGWISHCAMETRUE]                  = COMPOUND_STRING("Permohonan penyembuhan terkabul untuk {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_HEALINGWISHHEALED]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} pulih kembali!"),
    [STRINGID_LUNARDANCECAMETRUE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} diselimuti cahaya bulan mistis!"),
    [STRINGID_CURSEDBODYDISABLED]                    = COMPOUND_STRING("{B_BUFF1} milik {B_ATK_NAME_WITH_PREFIX} dinonaktifkan oleh {B_DEF_ABILITY} {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_ATTACKERACQUIREDABILITY]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} memperoleh {B_ATK_ABILITY}!"),
    [STRINGID_TARGETABILITYSTATLOWER]               = COMPOUND_STRING("{B_DEF_ABILITY} milik {B_DEF_NAME_WITH_PREFIX} menurunkan {B_BUFF1}-nya!"),
    [STRINGID_TARGETSTATWONTGOHIGHER]               = COMPOUND_STRING("{B_BUFF1} milik {B_DEF_NAME_WITH_PREFIX} tak bisa lebih tinggi lagi!"),
    [STRINGID_PKMNMOVEBOUNCEDABILITY]               = COMPOUND_STRING("{B_CURRENT_MOVE} milik {B_ATK_NAME_WITH_PREFIX} dipantulkan oleh {B_DEF_ABILITY} {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_IMPOSTERTRANSFORM]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} berubah menjadi {B_DEF_NAME_WITH_PREFIX2} berkat {B_LAST_ABILITY}!"),
    [STRINGID_ASSAULTVESTDOESNTALLOW]               = COMPOUND_STRING("Efek dari {B_LAST_ITEM} mencegah penggunaan status moves!\p"),
    [STRINGID_GRAVITYPREVENTSUSAGE]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} tak bisa pakai {B_CURRENT_MOVE} karena gravitasi!\p"),
    [STRINGID_HEALBLOCKPREVENTSUSAGE]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terhalang untuk memulihkan diri!\p"),
    [STRINGID_NOTDONEYET]                           = COMPOUND_STRING("Efek move ini belum selesai!\p"),
    [STRINGID_STICKYWEBUSED]                        = COMPOUND_STRING("Jaring lengket telah dipasang di sekitar tim {B_DEF_TEAM2}!"),
    [STRINGID_QUASHSUCCESS]                         = COMPOUND_STRING("Move milik {B_DEF_NAME_WITH_PREFIX} ditunda!"),
    [STRINGID_PKMNBLEWAWAYTOXICSPIKES]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menyingkirkan Toxic Spikes!"),
    [STRINGID_PKMNBLEWAWAYSTICKYWEB]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menyingkirkan Sticky Web!"),
    [STRINGID_PKMNBLEWAWAYSTEALTHROCK]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menyingkirkan Stealth Rock!"),
    [STRINGID_IONDELUGEON]                          = COMPOUND_STRING("Hujan ion membasahi medan pertempuran!"),
    [STRINGID_TOPSYTURVYSWITCHEDSTATS]              = COMPOUND_STRING("Semua perubahan stat pada {B_DEF_NAME_WITH_PREFIX2} dibalik!"),
    [STRINGID_TERRAINBECOMESMISTY]                  = COMPOUND_STRING("Kabut berputar di medan pertempuran!"),
    [STRINGID_TERRAINBECOMESGRASSY]                 = COMPOUND_STRING("Rerumputan tumbuh menutupi medan pertempuran!"),
    [STRINGID_TERRAINBECOMESELECTRIC]               = COMPOUND_STRING("Arus listrik mengaliri medan pertempuran!"),
    [STRINGID_TERRAINBECOMESPSYCHIC]                = COMPOUND_STRING("Medan pertempuran menjadi aneh!"),
    [STRINGID_TARGETELECTRIFIED]                    = COMPOUND_STRING("Move milik {B_DEF_NAME_WITH_PREFIX} telah dialiri listrik!"),
    [STRINGID_MEGAEVOREACTING]                      = COMPOUND_STRING("{B_LAST_ITEM} milik {B_ATK_NAME_WITH_PREFIX} bereaksi dengan Mega Ring {B_ATK_TRAINER_NAME}!"), //actually displays the type of mega ring in inventory, but we didnt implement them :(
    [STRINGID_MEGAEVOEVOLVED]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} Mega Evolve menjadi Mega {B_BUFF1}!"),
    [STRINGID_DRASTICALLY]                          = gText_drastically,
    [STRINGID_SEVERELY]                             = gText_severely,
    [STRINGID_INFESTATION]                          = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} dihinggapi oleh {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_NOEFFECTONTARGET]                     = COMPOUND_STRING("Tidak akan berefek pada {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_BURSTINGFLAMESHIT]                    = COMPOUND_STRING("Ledakan api mengenai {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_BESTOWITEMGIVING]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} menerima {B_LAST_ITEM} dari {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_THIRDTYPEADDED]                       = COMPOUND_STRING("Tipe {B_BUFF1} ditambahkan ke {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_FELLFORFEINT]                         = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} terkecoh oleh tipuan!"),
    [STRINGID_POKEMONCANNOTUSEMOVE]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} tidak bisa menggunakan {B_CURRENT_MOVE}!"),
    [STRINGID_COVEREDINPOWDER]                      = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} diselimuti bubuk!"),
    [STRINGID_POWDEREXPLODES]                       = COMPOUND_STRING("Saat api menyentuh bubuk di Pokémon, bubuk itu meledak!"),
    [STRINGID_BELCHCANTSELECT]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} belum makan Berry, jadi tidak bisa bersendawa!\p"),
    [STRINGID_SPECTRALTHIEFSTEAL]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} mencuri peningkatan stat target!"),
    [STRINGID_GRAVITYGROUNDING]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} jatuh dari langit karena gravitasi!"),
    [STRINGID_MISTYTERRAINPREVENTS]                 = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} menyelimuti diri dengan kabut pelindung!"),
    [STRINGID_GRASSYTERRAINHEALS]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} dipulihkan oleh medan berumput!"),
    [STRINGID_ELECTRICTERRAINPREVENTS]              = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} menyelimuti diri dengan medan listrik!"),
    [STRINGID_PSYCHICTERRAINPREVENTS]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} menyelimuti diri dengan medan psychic!"),
[STRINGID_SAFETYGOGGLESPROTECTED]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} tidak terpengaruh berkat {B_LAST_ITEM}-nya!"),
    [STRINGID_FLOWERVEILPROTECTED]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} menyelimuti diri dengan selubung kelopak!"),
    [STRINGID_SWEETVEILPROTECTED]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} tak bisa tertidur karena selubung manis!"),
    [STRINGID_AROMAVEILPROTECTED]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} dilindungi oleh selubung aromatik!"),
    [STRINGID_CELEBRATEMESSAGE]                     = COMPOUND_STRING("Selamat, {B_PLAYER_NAME}!"),
    [STRINGID_USEDINSTRUCTEDMOVE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} mengikuti instruksi {B_BUFF1}!"),
    [STRINGID_THROATCHOPENDS]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} bisa memakai sound-based move lagi!"),
    [STRINGID_PKMNCANTUSEMOVETHROATCHOP]            = COMPOUND_STRING("Efek dari Throat Chop mencegah {B_ATK_NAME_WITH_PREFIX2} memakai move tertentu!\p"),
    [STRINGID_LASERFOCUS]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} berkonsentrasi penuh!"),
    [STRINGID_GEMACTIVATES]                         = COMPOUND_STRING("{B_LAST_ITEM} memperkuat kekuatan {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_BERRYDMGREDUCES]                      = COMPOUND_STRING("{B_LAST_ITEM} melemahkan damage yang diterima {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_AIRBALLOONFLOAT]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} melayang di udara dengan Air Balloon-nya!"),
    [STRINGID_AIRBALLOONPOP]                        = COMPOUND_STRING("Air Balloon milik {B_DEF_NAME_WITH_PREFIX} pecah!"),
    [STRINGID_INCINERATEBURN]                       = COMPOUND_STRING("{B_LAST_ITEM} milik {B_EFF_NAME_WITH_PREFIX} hangus terbakar!"),
    [STRINGID_BUGBITE]                              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} mencuri dan memakan {B_LAST_ITEM} milik targetnya!"),
    [STRINGID_ILLUSIONWOREOFF]                      = COMPOUND_STRING("Ilusi milik {B_SCR_NAME_WITH_PREFIX} telah pudar!"),
    [STRINGID_ATTACKERCUREDTARGETSTATUS]            = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menyembuhkan masalah {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_ATTACKERLOSTFIRETYPE]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} membakar dirinya sendiri!"),
    [STRINGID_HEALERCURE]                           = COMPOUND_STRING("{B_LAST_ABILITY} milik {B_ATK_NAME_WITH_PREFIX} menyembuhkan masalah {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_SCRIPTINGABILITYSTATRAISE]            = COMPOUND_STRING("{B_SCR_ABILITY} milik {B_SCR_NAME_WITH_PREFIX} menaikkan {B_BUFF1}-nya!"),
    [STRINGID_RECEIVERABILITYTAKEOVER]              = COMPOUND_STRING("{B_SCR_ABILITY} milik {B_SCR_NAME_WITH_PREFIX} diambil alih!"),
    [STRINGID_PKNMABSORBINGPOWER]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} sedang menyerap kekuatan!"),
    [STRINGID_NOONEWILLBEABLETORUNAWAY]             = COMPOUND_STRING("Tidak ada yang bisa kabur di giliran berikutnya!"),
    [STRINGID_DESTINYKNOTACTIVATES]                 = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} jatuh cinta karena {B_LAST_ITEM}!"),
    [STRINGID_CLOAKEDINAFREEZINGLIGHT]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} diselimuti cahaya beku!"),
    [STRINGID_CLEARAMULETWONTLOWERSTATS]            = COMPOUND_STRING("Efek dari {B_LAST_ITEM} yang dipegang {B_SCR_NAME_WITH_PREFIX2} mencegah stat-nya turun!"),
    [STRINGID_FERVENTWISHREACHED]                   = COMPOUND_STRING("Harapan kuat {B_ATK_TRAINER_NAME} telah mencapai {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_AIRLOCKACTIVATES]                     = COMPOUND_STRING("Efek dari cuaca menghilang."),
    [STRINGID_PRESSUREENTERS]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} memancarkan tekanannya!"),
    [STRINGID_DARKAURAENTERS]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} memancarkan aura kegelapan!"),
    [STRINGID_FAIRYAURAENTERS]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} memancarkan aura peri!"),
    [STRINGID_AURABREAKENTERS]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} membalikkan semua aura Pokémon lain!"),
    [STRINGID_COMATOSEENTERS]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} sedang mengantuk!"),
    [STRINGID_SCREENCLEANERENTERS]                  = COMPOUND_STRING("Semua 'screen' di arena dibersihkan!"),
    [STRINGID_FETCHEDPOKEBALL]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} menemukan sebuah {B_LAST_ITEM}!"),
    [STRINGID_BATTLERABILITYRAISEDSTAT]             = COMPOUND_STRING("{B_SCR_ABILITY} milik {B_SCR_NAME_WITH_PREFIX} menaikkan {B_BUFF1}-nya!"),
    [STRINGID_ASANDSTORMKICKEDUP]                   = COMPOUND_STRING("Badai pasir menerpa!"),
    [STRINGID_PKMNSWILLPERISHIN3TURNS]              = COMPOUND_STRING("Kedua Pokémon akan pingsan dalam tiga giliran!"),  //don't think this message is displayed anymore
    [STRINGID_ABILITYRAISEDSTATDRASTICALLY]         = COMPOUND_STRING("{B_DEF_ABILITY} menaikkan {B_BUFF1} milik {B_DEF_NAME_WITH_PREFIX2} secara drastis!"),
    [STRINGID_AURAFLAREDTOLIFE]                     = COMPOUND_STRING("Aura milik {B_DEF_NAME_WITH_PREFIX} menyala!"),
    [STRINGID_ASONEENTERS]                          = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} memiliki dua Ability!"),
    [STRINGID_CURIOUSMEDICINEENTERS]                = COMPOUND_STRING("Perubahan stat milik {B_EFF_NAME_WITH_PREFIX} dihapus!"),
    [STRINGID_CANACTFASTERTHANKSTO]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} bisa bergerak lebih cepat berkat {B_BUFF1}-nya!"),
    [STRINGID_MICLEBERRYACTIVATES]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} meningkatkan accuracy move berikutnya dengan {B_LAST_ITEM}!"),
    [STRINGID_PKMNSHOOKOFFTHETAUNT]                 = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} terbebas dari taunt!"),
    [STRINGID_PKMNGOTOVERITSINFATUATION]            = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} sembuh dari jatuh cintanya!"),
    [STRINGID_ITEMCANNOTBEREMOVED]                  = COMPOUND_STRING("Item milik {B_ATK_NAME_WITH_PREFIX} tidak bisa dilepas!"),
    [STRINGID_STICKYBARBTRANSFER]                   = COMPOUND_STRING("{B_LAST_ITEM} menempelkan diri ke {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNBURNHEALED]                       = COMPOUND_STRING("Luka bakar {B_DEF_NAME_WITH_PREFIX} telah sembuh!"),
    [STRINGID_REDCARDACTIVATE]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} mengangkat Red Card-nya terhadap {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_EJECTBUTTONACTIVATE]                  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} diganti keluar dengan {B_LAST_ITEM}!"),
    [STRINGID_ATKGOTOVERINFATUATION]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} sembuh dari jatuh cintanya!"),
    [STRINGID_TORMENTEDNOMORE]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} tidak lagi tersiksa!"),
    [STRINGID_HEALBLOCKEDNOMORE]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} sembuh dari 'heal block'-nya!"),
    [STRINGID_ATTACKERBECAMEFULLYCHARGED]           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terisi penuh karena ikatannya dengan trainer!\p"),
    [STRINGID_ATTACKERBECAMEASHSPECIES]             = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menjadi Ash-Greninja!\p"),
    [STRINGID_EXTREMELYHARSHSUNLIGHT]               = COMPOUND_STRING("Cahaya matahari menjadi sangat terik!"),
    [STRINGID_EXTREMESUNLIGHTFADED]                 = COMPOUND_STRING("Cahaya matahari yang sangat terik meredup!"),
    [STRINGID_MOVEEVAPORATEDINTHEHARSHSUNLIGHT]     = COMPOUND_STRING("Serangan tipe Water menguap di bawah cahaya matahari yang terik!"),
    [STRINGID_EXTREMELYHARSHSUNLIGHTWASNOTLESSENED] = COMPOUND_STRING("Cahaya matahari yang sangat terik tidak berkurang sama sekali!"),
    [STRINGID_HEAVYRAIN]                            = COMPOUND_STRING("Hujan yang sangat deras mulai turun!"),
    [STRINGID_HEAVYRAINLIFTED]                      = COMPOUND_STRING("Hujan deras telah berhenti!"),
    [STRINGID_MOVEFIZZLEDOUTINTHEHEAVYRAIN]         = COMPOUND_STRING("Serangan tipe Fire padam di tengah hujan deras!"),
    [STRINGID_NORELIEFROMHEAVYRAIN]                 = COMPOUND_STRING("Tidak ada jeda dari hujan deras ini!"),
    [STRINGID_MYSTERIOUSAIRCURRENT]                 = COMPOUND_STRING("Angin kencang misterius melindungi Pokémon tipe Flying!"),
    [STRINGID_STRONGWINDSDISSIPATED]                = COMPOUND_STRING("Angin kencang misterius telah menghilang!"),
    [STRINGID_MYSTERIOUSAIRCURRENTBLOWSON]          = COMPOUND_STRING("Angin kencang misterius terus berhembus!"),
    [STRINGID_ATTACKWEAKENEDBSTRONGWINDS]           = COMPOUND_STRING("Angin kencang misterius melemahkan serangan!"),
    [STRINGID_STUFFCHEEKSCANTSELECT]                = COMPOUND_STRING("Tidak bisa menggunakan move karena tidak punya Berry!\p"),
    [STRINGID_PKMNREVERTEDTOPRIMAL]                 = COMPOUND_STRING("Primal Reversion {B_SCR_NAME_WITH_PREFIX}! Ia kembali ke wujud primalnya!"),
    [STRINGID_BUTPOKEMONCANTUSETHEMOVE]             = COMPOUND_STRING("Tapi {B_ATK_NAME_WITH_PREFIX2} tak bisa menggunakan move itu!"),
    [STRINGID_BUTHOOPACANTUSEIT]                    = COMPOUND_STRING("Tapi {B_ATK_NAME_WITH_PREFIX2} tak bisa memakainya dalam wujudnya sekarang!"),
    [STRINGID_BROKETHROUGHPROTECTION]               = COMPOUND_STRING("Ia menembus perlindungan {B_DEF_NAME_WITH_PREFIX2}!"),
[STRINGID_ABILITYALLOWSONLYMOVE]                = COMPOUND_STRING("{B_ATK_ABILITY} hanya izinkan penggunaan {B_CURRENT_MOVE}!\p"),
    [STRINGID_SWAPPEDABILITIES]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} menukar Ability dengan targetnya!"),
    [STRINGID_PASTELVEILPROTECTED]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} dilindungi oleh selubung pastel!"),
    [STRINGID_PASTELVEILENTERS]                     = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} sembuh dari keracunannya!"),
    [STRINGID_BATTLERTYPECHANGEDTO]                 = COMPOUND_STRING("Tipe {B_SCR_NAME_WITH_PREFIX} berubah menjadi {B_BUFF1}!"),
    [STRINGID_BOTHCANNOLONGERESCAPE]                = COMPOUND_STRING("Kedua Pokémon tidak bisa kabur!"),
    [STRINGID_CANTESCAPEDUETOUSEDMOVE]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} tak bisa kabur lagi karena memakai No Retreat!"),
    [STRINGID_PKMNBECAMEWEAKERTOFIRE]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} menjadi lebih lemah terhadap api!"),
    [STRINGID_ABOUTTOUSEPOLTERGEIST]                = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} akan diserang oleh {B_BUFF1}-nya!"),
    [STRINGID_CANTESCAPEBECAUSEOFCURRENTMOVE]       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} tak bisa kabur lagi karena Octolock!"),
    [STRINGID_NEUTRALIZINGGASENTERS]                = COMPOUND_STRING("Gas penetral memenuhi area!"),
    [STRINGID_NEUTRALIZINGGASOVER]                  = COMPOUND_STRING("Efek dari gas penetral telah hilang!"),
    [STRINGID_TARGETTOOHEAVY]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} terlalu berat untuk diangkat!"),
    [STRINGID_PKMNTOOKTARGETHIGH]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} membawa {B_DEF_NAME_WITH_PREFIX2} ke angkasa!"),
    [STRINGID_PKMNINSNAPTRAP]                       = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} terjebak dalam perangkap jepret!"),
    [STRINGID_METEORBEAMCHARGING]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} dipenuhi dengan kekuatan luar angkasa!"),
    [STRINGID_HEATUPBEAK]                           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} mulai memanaskan paruhnya!"),
    [STRINGID_COURTCHANGE]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menukar efek pertarungan di kedua sisi arena!"),
    [STRINGID_ZPOWERSURROUNDS]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menyelimuti diri dengan Z-Power!"),
    [STRINGID_ZMOVEUNLEASHED]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} melepaskan Z-Move kekuatan penuh!"),
    [STRINGID_ZMOVERESETSSTATS]                     = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} memulihkan stat-nya dengan Z-Power!"),
    [STRINGID_ZMOVEALLSTATSUP]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} meningkatkan stat-nya dengan Z-Power!"),
    [STRINGID_ZMOVEZBOOSTCRIT]                      = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} meningkatkan rasio critical-hit dengan Z-Power!"),
    [STRINGID_ZMOVERESTOREHP]                       = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} memulihkan HP-nya dengan Z-Power!"),
    [STRINGID_ZMOVESTATUP]                          = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} meningkatkan stat-nya dengan Z-Power!"),
    [STRINGID_ZMOVEHPTRAP]                          = COMPOUND_STRING("HP milik {B_SCR_NAME_WITH_PREFIX} dipulihkan oleh Z-Power!"),
    [STRINGID_ATTACKEREXPELLEDTHEPOISON]            = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} berhasil mengeluarkan racun agar kamu tak khawatir!"),
    [STRINGID_ATTACKERSHOOKITSELFAWAKE]             = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} membangunkan diri agar kamu tak khawatir!"),
    [STRINGID_ATTACKERBROKETHROUGHPARALYSIS]        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} mengumpulkan tenaga untuk sembuh dari lumpuh agar kamu tak khawatir!"),
    [STRINGID_ATTACKERHEALEDITSBURN]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menyembuhkan luka bakarnya dengan tekad agar kamu tak khawatir!"),
    [STRINGID_ATTACKERMELTEDTHEICE]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} melelehkan es dengan tekad membara agar kamu tak khawatir!"),
    [STRINGID_TARGETTOUGHEDITOUT]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} bertahan agar kamu tidak sedih!"),
    [STRINGID_ATTACKERLOSTELECTRICTYPE]             = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} kehabisan semua listriknya!"),
    [STRINGID_ATTACKERSWITCHEDSTATWITHTARGET]       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menukar {B_BUFF1} dengan targetnya!"),
    [STRINGID_BEINGHITCHARGEDPKMNWITHPOWER]         = COMPOUND_STRING("Terkena {B_CURRENT_MOVE} mengisi {B_DEF_NAME_WITH_PREFIX2} dengan kekuatan!"),
    [STRINGID_SUNLIGHTACTIVATEDABILITY]             = COMPOUND_STRING("Cahaya matahari terik mengaktifkan Protosynthesis {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_STATWASHEIGHTENED]                    = COMPOUND_STRING("{B_BUFF1} milik {B_SCR_NAME_WITH_PREFIX} meningkat pesat!"),
    [STRINGID_ELECTRICTERRAINACTIVATEDABILITY]      = COMPOUND_STRING("Electric Terrain mengaktifkan Quark Drive {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_ABILITYWEAKENEDSURROUNDINGMONSSTAT]   = COMPOUND_STRING("{B_SCR_ABILITY} milik {B_SCR_NAME_WITH_PREFIX} melemahkan {B_BUFF1} semua Pokémon di sekitar!\p"),
    [STRINGID_ATTACKERGAINEDSTRENGTHFROMTHEFALLEN]  = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} mendapat kekuatan dari yang tumbang!"),
    [STRINGID_PKMNSABILITYPREVENTSABILITY]          = COMPOUND_STRING("{B_SCR_ABILITY} milik {B_SCR_NAME_WITH_PREFIX} mencegah {B_DEF_ABILITY} {B_DEF_NAME_WITH_PREFIX2} bekerja!"), //not in gen 5+, ability popup
    [STRINGID_PREPARESHELLTRAP]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} memasang perangkap cangkang!"),
    [STRINGID_SHELLTRAPDIDNTWORK]                   = COMPOUND_STRING("Perangkap cangkang {B_ATK_NAME_WITH_PREFIX} tidak bekerja!"),
    [STRINGID_SPIKESDISAPPEAREDFROMTEAM]            = COMPOUND_STRING("Spikes menghilang dari sekitar tim {B_ATK_TEAM2}!"),
    [STRINGID_TOXICSPIKESDISAPPEAREDFROMTEAM]       = COMPOUND_STRING("Duri beracun menghilang dari sekitar tim {B_ATK_TEAM2}!"),
    [STRINGID_STICKYWEBDISAPPEAREDFROMTEAM]         = COMPOUND_STRING("Jaring lengket menghilang dari sekitar tim {B_ATK_TEAM2}!"),
    [STRINGID_STEALTHROCKDISAPPEAREDFROMTEAM]       = COMPOUND_STRING("Batu runcing menghilang dari sekitar tim {B_ATK_TEAM2}!"),
    [STRINGID_COULDNTFULLYPROTECT]                  = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} tak bisa melindungi diri sepenuhnya dan terluka!"),
    [STRINGID_STOCKPILEDEFFECTWOREOFF]              = COMPOUND_STRING("Efek timbunan {B_ATK_NAME_WITH_PREFIX} telah hilang!"),
    [STRINGID_PKMNREVIVEDREADYTOFIGHT]              = COMPOUND_STRING("{B_BUFF1} dihidupkan kembali dan siap bertarung lagi!"),
    [STRINGID_ITEMRESTOREDSPECIESHEALTH]            = COMPOUND_STRING("HP milik {B_BUFF1} telah pulih."),
    [STRINGID_ITEMCUREDSPECIESSTATUS]               = COMPOUND_STRING("Status {B_BUFF1} telah sembuh!"),
    [STRINGID_ITEMRESTOREDSPECIESPP]                = COMPOUND_STRING("PP milik {B_BUFF1} telah pulih!"),
    [STRINGID_THUNDERCAGETRAPPED]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menjebak {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNHURTBYFROSTBITE]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terluka oleh frostbite-nya!"),
    [STRINGID_PKMNGOTFROSTBITE]                     = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} terkena frostbite!"),
    [STRINGID_PKMNSITEMHEALEDFROSTBITE]             = COMPOUND_STRING("{B_LAST_ITEM} milik {B_SCR_NAME_WITH_PREFIX} menyembuhkan frostbite-nya!"),
    [STRINGID_ATTACKERHEALEDITSFROSTBITE]           = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menyembuhkan frostbite-nya dengan tekad agar kamu tak khawatir!"),
    [STRINGID_PKMNFROSTBITEHEALED]                  = COMPOUND_STRING("Frostbite {B_DEF_NAME_WITH_PREFIX} telah sembuh!"),
    [STRINGID_PKMNFROSTBITEHEALED2]                 = COMPOUND_STRING("Frostbite {B_ATK_NAME_WITH_PREFIX} telah sembuh!"),
    [STRINGID_PKMNFROSTBITEHEALEDBY]                = COMPOUND_STRING("{B_CURRENT_MOVE} milik {B_ATK_NAME_WITH_PREFIX} menyembuhkan frostbite-nya!"),
    [STRINGID_MIRRORHERBCOPIED]                     = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} memakai Mirror Herb untuk meniru perubahan stat lawannya!"),
    [STRINGID_STARTEDSNOW]                          = COMPOUND_STRING("Salju mulai turun!"),
    [STRINGID_SNOWCONTINUES]                        = COMPOUND_STRING("Salju terus turun."), //not in gen 5+ (lol)
    [STRINGID_SNOWSTOPPED]                          = COMPOUND_STRING("Salju berhenti."),
    [STRINGID_SNOWWARNINGSNOW]                      = COMPOUND_STRING("Salju mulai turun!"),
    [STRINGID_PKMNITEMMELTED]                       = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} mengkorosi {B_LAST_ITEM} milik {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_ULTRABURSTREACTING]                   = COMPOUND_STRING("Cahaya terang akan meledak dari {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_ULTRABURSTCOMPLETED]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} mendapatkan kekuatan sejatinya lewat Ultra Burst!"),
    [STRINGID_TEAMGAINEDEXP]                        = COMPOUND_STRING("Sisa tim-mu mendapat Exp. Points berkat Exp. Share!\p"),
    [STRINGID_CURRENTMOVECANTSELECT]                = COMPOUND_STRING("{B_BUFF1} tidak bisa digunakan!\p"),
    [STRINGID_TARGETISBEINGSALTCURED]               = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} sedang diawetkan dengan garam!"),
[STRINGID_TARGETISHURTBYSALTCURE]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terluka oleh {B_BUFF1}!"),
    [STRINGID_TARGETCOVEREDINSTICKYCANDYSYRUP]      = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} terlapisi oleh sirup permen lengket!"),
    [STRINGID_SHARPSTEELFLOATS]                     = COMPOUND_STRING("Potongan baja tajam mulai melayang di sekitar Pokémon tim {B_DEF_TEAM2}!"),
    [STRINGID_SHARPSTEELDMG]                        = COMPOUND_STRING("Baja tajam itu menusuk {B_DEF_NAME_WITH_PREFIX2}!"),
    [STRINGID_PKMNBLEWAWAYSHARPSTEEL]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menyingkirkan baja tajam!"),
    [STRINGID_SHARPSTEELDISAPPEAREDFROMTEAM]        = COMPOUND_STRING("Potongan baja di sekitar Pokémon tim {B_ATK_TEAM2} menghilang!"),
    [STRINGID_TEAMTRAPPEDWITHVINES]                 = COMPOUND_STRING("Pokémon tim {B_DEF_TEAM1} terperangkap oleh sulur!"),
    [STRINGID_PKMNHURTBYVINES]                      = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terluka oleh serangan G-Max Vine Lash!"),
    [STRINGID_TEAMCAUGHTINVORTEX]                   = COMPOUND_STRING("Pokémon tim {B_DEF_TEAM1} terperangkap dalam pusaran air!"),
    [STRINGID_PKMNHURTBYVORTEX]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terluka oleh pusaran G-Max Cannonade!"),
    [STRINGID_TEAMSURROUNDEDBYFIRE]                 = COMPOUND_STRING("Pokémon tim {B_DEF_TEAM1} dikelilingi oleh api!"),
    [STRINGID_PKMNBURNINGUP]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terbakar dalam api G-Max Wildfire!"),
    [STRINGID_TEAMSURROUNDEDBYROCKS]                = COMPOUND_STRING("Pokémon tim {B_DEF_TEAM1} dikelilingi oleh bebatuan!"),
    [STRINGID_PKMNHURTBYROCKSTHROWN]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terluka oleh batu yang dilempar G-Max Volcalith!"),
    [STRINGID_MOVEBLOCKEDBYDYNAMAX]                 = COMPOUND_STRING("Move itu ditahan oleh kekuatan Dynamax!"),
    [STRINGID_ZEROTOHEROTRANSFORMATION]             = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} mengalami transformasi heroik!"),
    [STRINGID_THETWOMOVESBECOMEONE]                 = COMPOUND_STRING("Kedua move telah menjadi satu! Ini adalah move gabungan!{PAUSE 16}"),
    [STRINGID_ARAINBOWAPPEAREDONSIDE]               = COMPOUND_STRING("Pelangi muncul di langit di sisi tim {B_ATK_TEAM2}!"),
    [STRINGID_THERAINBOWDISAPPEARED]                = COMPOUND_STRING("Pelangi di sisi tim {B_ATK_TEAM2} menghilang!"),
    [STRINGID_WAITINGFORPARTNERSMOVE]               = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} sedang menunggu move {B_ATK_PARTNER_NAME}…{PAUSE 16}"),
    [STRINGID_SEAOFFIREENVELOPEDSIDE]               = COMPOUND_STRING("Lautan api menyelimuti tim {B_DEF_TEAM2}!"),
    [STRINGID_HURTBYTHESEAOFFIRE]                   = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} terluka oleh lautan api!"),
    [STRINGID_THESEAOFFIREDISAPPEARED]              = COMPOUND_STRING("Lautan api di sekitar tim {B_ATK_TEAM2} menghilang!"),
    [STRINGID_SWAMPENVELOPEDSIDE]                   = COMPOUND_STRING("Rawa menyelimuti tim {B_DEF_TEAM2}!"),
    [STRINGID_THESWAMPDISAPPEARED]                  = COMPOUND_STRING("Rawa di sekitar tim {B_ATK_TEAM2} menghilang!"),
    [STRINGID_PKMNTELLCHILLINGRECEPTIONJOKE]        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} bersiap menceritakan lelucon yang sangat garing!"),
    [STRINGID_HOSPITALITYRESTORATION]               = COMPOUND_STRING("{B_EFF_NAME_WITH_PREFIX} meminum semua matcha yang dibuat {B_SCR_NAME_WITH_PREFIX2}!"),
    [STRINGID_ELECTROSHOTCHARGING]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menyerap listrik!"),
    [STRINGID_ITEMWASUSEDUP]                        = COMPOUND_STRING("{B_LAST_ITEM} telah habis terpakai…"),
    [STRINGID_ATTACKERLOSTITSTYPE]                  = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} kehilangan tipe {B_BUFF1}-nya!"),
    [STRINGID_SHEDITSTAIL]                          = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} melepaskan ekornya untuk membuat umpan!"),
    [STRINGID_CLOAKEDINAHARSHLIGHT]                 = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} diselimuti cahaya terang!"),
    [STRINGID_SUPERSWEETAROMAWAFTS]                 = COMPOUND_STRING("Aroma super manis tercium dari sirup yang melapisi {B_ATK_NAME_WITH_PREFIX2}!"),
    [STRINGID_DIMENSIONSWERETWISTED]                = COMPOUND_STRING("Dimensi telah diputarbalikkan!"),
    [STRINGID_BIZARREARENACREATED]                  = COMPOUND_STRING("Area aneh tercipta, efek item yang dipegang Pokémon hilang!"),
    [STRINGID_BIZARREAREACREATED]                   = COMPOUND_STRING("Area aneh tercipta, stat Defense dan Sp. Def tertukar!"),
    [STRINGID_TIDYINGUPCOMPLETE]                    = COMPOUND_STRING("Pembersihan selesai!"),
    [STRINGID_PKMNTERASTALLIZEDINTO]                = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} melakukan Terastal menjadi tipe {B_BUFF1}!"),
    [STRINGID_BOOSTERENERGYACTIVATES]               = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} menggunakan {B_LAST_ITEM} untuk mengaktifkan {B_SCR_ABILITY}!"),
    [STRINGID_FOGCREPTUP]                           = COMPOUND_STRING("Kabut tebal mulai menyelimuti!"),
    [STRINGID_FOGISDEEP]                            = COMPOUND_STRING("Kabutnya tebal…"),
    [STRINGID_FOGLIFTED]                            = COMPOUND_STRING("Kabut menghilang."),
    [STRINGID_PKMNMADESHELLGLEAM]                   = COMPOUND_STRING("{B_DEF_NAME_WITH_PREFIX} membuat cangkangnya berkilau! Ini mengubah type matchup!"),
    [STRINGID_FICKLEBEAMDOUBLED]                    = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} mengerahkan segalanya untuk serangan ini!"),
    [STRINGID_COMMANDERACTIVATES]                   = COMPOUND_STRING("{B_SCR_NAME_WITH_PREFIX} ditelan oleh Dondozo dan menjadi komandan Dondozo!"),
    [STRINGID_POKEFLUTECATCHY]                      = COMPOUND_STRING("{B_PLAYER_NAME} memainkan {B_LAST_ITEM}.\pWah, nada yang menarik!"),
    [STRINGID_POKEFLUTE]                            = COMPOUND_STRING("{B_PLAYER_NAME} memainkan {B_LAST_ITEM}."),
    [STRINGID_MONHEARINGFLUTEAWOKE]                 = COMPOUND_STRING("Pokémon yang mendengar seruling itu terbangun!"),
    [STRINGID_SUNLIGHTISHARSH]                      = COMPOUND_STRING("Sinar mataharinya terik!"),
    [STRINGID_ITISHAILING]                          = COMPOUND_STRING("Hujan es turun!"),
    [STRINGID_ITISSNOWING]                          = COMPOUND_STRING("Salju turun!"),
    [STRINGID_ISCOVEREDWITHGRASS]                   = COMPOUND_STRING("Medan pertempuran tertutup rumput!"),
    [STRINGID_MISTSWIRLSAROUND]                     = COMPOUND_STRING("Kabut berputar di medan pertempuran!"),
    [STRINGID_ELECTRICCURRENTISRUNNING]             = COMPOUND_STRING("Arus listrik mengaliri medan pertempuran!"),
    [STRINGID_SEEMSWEIRD]                           = COMPOUND_STRING("Medan pertempuran terasa aneh!"),
    [STRINGID_WAGGLINGAFINGER]                      = COMPOUND_STRING("Menggoyangkan jari membuatnya memakai {B_CURRENT_MOVE}!"),
    [STRINGID_BLOCKEDBYSLEEPCLAUSE]                 = COMPOUND_STRING("Sleep Clause membuat {B_DEF_NAME_WITH_PREFIX2} tetap terjaga!"),
    [STRINGID_SUPEREFFECTIVETWOFOES]                = COMPOUND_STRING("Sangat efektif pada {B_DEF_NAME_WITH_PREFIX2} dan {B_DEF_PARTNER_NAME}!"),
    [STRINGID_NOTVERYEFFECTIVETWOFOES]              = COMPOUND_STRING("Tidak terlalu efektif pada {B_DEF_NAME_WITH_PREFIX2} dan {B_DEF_PARTNER_NAME}!"),
    [STRINGID_ITDOESNTAFFECTTWOFOES]                = COMPOUND_STRING("Tidak berefek pada {B_DEF_NAME_WITH_PREFIX2} dan {B_DEF_PARTNER_NAME}…"),
    [STRINGID_SENDCAUGHTMONPARTYORBOX]              = COMPOUND_STRING("Tambahkan {B_DEF_NAME} ke dalam party?"),
    [STRINGID_PKMNSENTTOPCAFTERCATCH]               = gText_PkmnSentToPCAfterCatch,
    [STRINGID_PKMNDYNAMAXED]                        = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menjadi besar dalam wujud Dynamax-nya!"),
    [STRINGID_PKMNGIGANTAMAXED]                     = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} menjadi besar dalam wujud Gigantamax-nya!"),
    [STRINGID_TIMETODYNAMAX]                        = COMPOUND_STRING("Saatnya Dynamax!"),
    [STRINGID_TIMETOGIGANTAMAX]                     = COMPOUND_STRING("Saatnya Gigantamax!"),
    [STRINGID_QUESTIONFORFEITBATTLE]                = COMPOUND_STRING("Apakah kamu ingin menyerah dan keluar sekarang? Keluar berarti kalah."),
    [STRINGID_POWERCONSTRUCTPRESENCEOFMANY]         = COMPOUND_STRING("Kamu merasakan kehadiran banyak pihak!"),
    [STRINGID_POWERCONSTRUCTTRANSFORM]              = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} berubah menjadi Complete Forme-nya!"),
    [STRINGID_ABILITYSHIELDPROTECTS]                = COMPOUND_STRING("Ability {B_ATK_NAME_WITH_PREFIX} dilindungi oleh efek {B_LAST_ITEM}-nya!"),
};

const u16 gTrainerUsedItemStringIds[] =
{
    STRINGID_PLAYERUSEDITEM, STRINGID_TRAINER1USEDITEM
};

const u16 gZEffectStringIds[] =
{
    [B_MSG_Z_RESET_STATS] = STRINGID_ZMOVERESETSSTATS,
    [B_MSG_Z_ALL_STATS_UP]= STRINGID_ZMOVEALLSTATSUP,
    [B_MSG_Z_BOOST_CRITS] = STRINGID_ZMOVEZBOOSTCRIT,
    [B_MSG_Z_FOLLOW_ME]   = STRINGID_PKMNCENTERATTENTION,
    [B_MSG_Z_RECOVER_HP]  = STRINGID_ZMOVERESTOREHP,
    [B_MSG_Z_STAT_UP]     = STRINGID_ZMOVESTATUP,
    [B_MSG_Z_HP_TRAP]     = STRINGID_ZMOVEHPTRAP,
};

const u16 gMentalHerbCureStringIds[] =
{
    [B_MSG_MENTALHERBCURE_INFATUATION] = STRINGID_ATKGOTOVERINFATUATION,
    [B_MSG_MENTALHERBCURE_TAUNT]       = STRINGID_BUFFERENDS,
    [B_MSG_MENTALHERBCURE_ENCORE]      = STRINGID_PKMNENCOREENDED,
    [B_MSG_MENTALHERBCURE_TORMENT]     = STRINGID_TORMENTEDNOMORE,
    [B_MSG_MENTALHERBCURE_HEALBLOCK]   = STRINGID_HEALBLOCKEDNOMORE,
    [B_MSG_MENTALHERBCURE_DISABLE]     = STRINGID_PKMNMOVEDISABLEDNOMORE,
};

const u16 gStartingStatusStringIds[B_MSG_STARTING_STATUS_COUNT] =
{
    [B_MSG_TERRAIN_SET_MISTY]    = STRINGID_TERRAINBECOMESMISTY,
    [B_MSG_TERRAIN_SET_ELECTRIC] = STRINGID_TERRAINBECOMESELECTRIC,
    [B_MSG_TERRAIN_SET_PSYCHIC]  = STRINGID_TERRAINBECOMESPSYCHIC,
    [B_MSG_TERRAIN_SET_GRASSY]   = STRINGID_TERRAINBECOMESGRASSY,
    [B_MSG_SET_TRICK_ROOM]       = STRINGID_DIMENSIONSWERETWISTED,
    [B_MSG_SET_MAGIC_ROOM]       = STRINGID_BIZARREARENACREATED,
    [B_MSG_SET_WONDER_ROOM]      = STRINGID_BIZARREAREACREATED,
    [B_MSG_SET_TAILWIND]         = STRINGID_TAILWINDBLEW,
    [B_MSG_SET_RAINBOW]          = STRINGID_ARAINBOWAPPEAREDONSIDE,
    [B_MSG_SET_SEA_OF_FIRE]      = STRINGID_SEAOFFIREENVELOPEDSIDE,
    [B_MSG_SET_SWAMP]            = STRINGID_SWAMPENVELOPEDSIDE,
};

const u16 gTerrainStringIds[B_MSG_TERRAIN_COUNT] =
{
    [B_MSG_TERRAIN_SET_MISTY] = STRINGID_TERRAINBECOMESMISTY,
    [B_MSG_TERRAIN_SET_ELECTRIC] = STRINGID_TERRAINBECOMESELECTRIC,
    [B_MSG_TERRAIN_SET_PSYCHIC] = STRINGID_TERRAINBECOMESPSYCHIC,
    [B_MSG_TERRAIN_SET_GRASSY] = STRINGID_TERRAINBECOMESGRASSY,
    [B_MSG_TERRAIN_END_MISTY] = STRINGID_MISTYTERRAINENDS,
    [B_MSG_TERRAIN_END_ELECTRIC] = STRINGID_ELECTRICTERRAINENDS,
    [B_MSG_TERRAIN_END_PSYCHIC] = STRINGID_PSYCHICTERRAINENDS,
    [B_MSG_TERRAIN_END_GRASSY] = STRINGID_GRASSYTERRAINENDS,
};

const u16 gTerrainPreventsStringIds[] =
{
    [B_MSG_TERRAINPREVENTS_MISTY]    = STRINGID_MISTYTERRAINPREVENTS,
    [B_MSG_TERRAINPREVENTS_ELECTRIC] = STRINGID_ELECTRICTERRAINPREVENTS,
    [B_MSG_TERRAINPREVENTS_PSYCHIC]  = STRINGID_PSYCHICTERRAINPREVENTS
};

const u16 gHealingWishStringIds[] =
{
    STRINGID_HEALINGWISHCAMETRUE,
    STRINGID_LUNARDANCECAMETRUE
};

const u16 gDmgHazardsStringIds[] =
{
    [B_MSG_PKMNHURTBYSPIKES]   = STRINGID_PKMNHURTBYSPIKES,
    [B_MSG_STEALTHROCKDMG]     = STRINGID_STEALTHROCKDMG,
    [B_MSG_SHARPSTEELDMG]      = STRINGID_SHARPSTEELDMG,
    [B_MSG_POINTEDSTONESFLOAT] = STRINGID_POINTEDSTONESFLOAT,
    [B_MSG_SPIKESSCATTERED]    = STRINGID_SPIKESSCATTERED,
    [B_MSG_SHARPSTEELFLOATS]   = STRINGID_SHARPSTEELFLOATS,
};

const u16 gSwitchInAbilityStringIds[] =
{
    [B_MSG_SWITCHIN_MOLDBREAKER] = STRINGID_MOLDBREAKERENTERS,
    [B_MSG_SWITCHIN_TERAVOLT] = STRINGID_TERAVOLTENTERS,
    [B_MSG_SWITCHIN_TURBOBLAZE] = STRINGID_TURBOBLAZEENTERS,
    [B_MSG_SWITCHIN_SLOWSTART] = STRINGID_SLOWSTARTENTERS,
    [B_MSG_SWITCHIN_UNNERVE] = STRINGID_UNNERVEENTERS,
    [B_MSG_SWITCHIN_ANTICIPATION] = STRINGID_ANTICIPATIONACTIVATES,
    [B_MSG_SWITCHIN_FOREWARN] = STRINGID_FOREWARNACTIVATES,
    [B_MSG_SWITCHIN_PRESSURE] = STRINGID_PRESSUREENTERS,
    [B_MSG_SWITCHIN_DARKAURA] = STRINGID_DARKAURAENTERS,
    [B_MSG_SWITCHIN_FAIRYAURA] = STRINGID_FAIRYAURAENTERS,
    [B_MSG_SWITCHIN_AURABREAK] = STRINGID_AURABREAKENTERS,
    [B_MSG_SWITCHIN_COMATOSE] = STRINGID_COMATOSEENTERS,
    [B_MSG_SWITCHIN_SCREENCLEANER] = STRINGID_SCREENCLEANERENTERS,
    [B_MSG_SWITCHIN_ASONE] = STRINGID_ASONEENTERS,
    [B_MSG_SWITCHIN_CURIOUS_MEDICINE] = STRINGID_CURIOUSMEDICINEENTERS,
    [B_MSG_SWITCHIN_PASTEL_VEIL] = STRINGID_PASTELVEILENTERS,
    [B_MSG_SWITCHIN_NEUTRALIZING_GAS] = STRINGID_NEUTRALIZINGGASENTERS,
};

const u16 gMissStringIds[] =
{
    [B_MSG_MISSED]      = STRINGID_ATTACKMISSED,
    [B_MSG_PROTECTED]   = STRINGID_PKMNPROTECTEDITSELF,
    [B_MSG_AVOIDED_ATK] = STRINGID_PKMNAVOIDEDATTACK,
    [B_MSG_AVOIDED_DMG] = STRINGID_AVOIDEDDAMAGE,
    [B_MSG_GROUND_MISS] = STRINGID_PKMNMAKESGROUNDMISS
};

const u16 gNoEscapeStringIds[] =
{
    [B_MSG_CANT_ESCAPE]          = STRINGID_CANTESCAPE,
    [B_MSG_DONT_LEAVE_BIRCH]     = STRINGID_DONTLEAVEBIRCH,
    [B_MSG_PREVENTS_ESCAPE]      = STRINGID_PREVENTSESCAPE,
    [B_MSG_CANT_ESCAPE_2]        = STRINGID_CANTESCAPE2,
    [B_MSG_ATTACKER_CANT_ESCAPE] = STRINGID_ATTACKERCANTESCAPE
};

const u16 gMoveWeatherChangeStringIds[] =
{
    [B_MSG_STARTED_RAIN]      = STRINGID_STARTEDTORAIN,
    [B_MSG_STARTED_DOWNPOUR]  = STRINGID_DOWNPOURSTARTED, // Unused
    [B_MSG_WEATHER_FAILED]    = STRINGID_BUTITFAILED,
    [B_MSG_STARTED_SANDSTORM] = STRINGID_SANDSTORMBREWED,
    [B_MSG_STARTED_SUNLIGHT]  = STRINGID_SUNLIGHTGOTBRIGHT,
    [B_MSG_STARTED_HAIL]      = STRINGID_STARTEDHAIL,
    [B_MSG_STARTED_SNOW]      = STRINGID_STARTEDSNOW,
    [B_MSG_STARTED_FOG]       = STRINGID_FOGCREPTUP, // Unused, can use for custom moves that set fog
};

const u16 gWeatherEndsStringIds[B_MSG_WEATHER_END_COUNT] =
{
    [B_MSG_WEATHER_END_RAIN]         = STRINGID_RAINSTOPPED,
    [B_MSG_WEATHER_END_SUN]          = STRINGID_SUNLIGHTFADED,
    [B_MSG_WEATHER_END_SANDSTORM]    = STRINGID_SANDSTORMSUBSIDED,
    [B_MSG_WEATHER_END_HAIL]         = STRINGID_HAILSTOPPED,
    [B_MSG_WEATHER_END_SNOW]         = STRINGID_SNOWSTOPPED,
    [B_MSG_WEATHER_END_FOG]          = STRINGID_FOGLIFTED,
    [B_MSG_WEATHER_END_STRONG_WINDS] = STRINGID_STRONGWINDSDISSIPATED,
};

const u16 gWeatherTurnStringIds[] =
{
    [B_MSG_WEATHER_TURN_RAIN]         = STRINGID_RAINCONTINUES,
    [B_MSG_WEATHER_TURN_DOWNPOUR]     = STRINGID_DOWNPOURCONTINUES,
    [B_MSG_WEATHER_TURN_SUN]          = STRINGID_SUNLIGHTSTRONG,
    [B_MSG_WEATHER_TURN_SANDSTORM]    = STRINGID_SANDSTORMRAGES,
    [B_MSG_WEATHER_TURN_HAIL]         = STRINGID_HAILCONTINUES,
    [B_MSG_WEATHER_TURN_SNOW]         = STRINGID_SNOWCONTINUES,
    [B_MSG_WEATHER_TURN_FOG]          = STRINGID_FOGISDEEP,
    [B_MSG_WEATHER_TURN_STRONG_WINDS] = STRINGID_MYSTERIOUSAIRCURRENTBLOWSON,
};

const u16 gSandStormHailDmgStringIds[] =
{
    [B_MSG_SANDSTORM] = STRINGID_PKMNBUFFETEDBYSANDSTORM,
    [B_MSG_HAIL]      = STRINGID_PKMNPELTEDBYHAIL
};

const u16 gProtectLikeUsedStringIds[] =
{
    [B_MSG_PROTECTED_ITSELF] = STRINGID_PKMNPROTECTEDITSELF2,
    [B_MSG_BRACED_ITSELF]    = STRINGID_PKMNBRACEDITSELF,
    [B_MSG_PROTECT_FAILED]   = STRINGID_BUTITFAILED,
    [B_MSG_PROTECTED_TEAM]   = STRINGID_PROTECTEDTEAM,
};

const u16 gReflectLightScreenSafeguardStringIds[] =
{
    [B_MSG_SIDE_STATUS_FAILED]     = STRINGID_BUTITFAILED,
    [B_MSG_SET_REFLECT_SINGLE]     = STRINGID_PKMNRAISEDDEF,
    [B_MSG_SET_REFLECT_DOUBLE]     = STRINGID_PKMNRAISEDDEF,
    [B_MSG_SET_LIGHTSCREEN_SINGLE] = STRINGID_PKMNRAISEDSPDEF,
    [B_MSG_SET_LIGHTSCREEN_DOUBLE] = STRINGID_PKMNRAISEDSPDEF,
    [B_MSG_SET_SAFEGUARD]          = STRINGID_PKMNCOVEREDBYVEIL,
};

const u16 gLeechSeedStringIds[] =
{
    [B_MSG_LEECH_SEED_SET]   = STRINGID_PKMNSEEDED,
    [B_MSG_LEECH_SEED_MISS]  = STRINGID_PKMNEVADEDATTACK,
    [B_MSG_LEECH_SEED_FAIL]  = STRINGID_ITDOESNTAFFECT,
    [B_MSG_LEECH_SEED_DRAIN] = STRINGID_PKMNSAPPEDBYLEECHSEED,
    [B_MSG_LEECH_SEED_OOZE]  = STRINGID_ITSUCKEDLIQUIDOOZE,
};

const u16 gRestUsedStringIds[] =
{
    [B_MSG_REST]          = STRINGID_PKMNWENTTOSLEEP,
    [B_MSG_REST_STATUSED] = STRINGID_PKMNSLEPTHEALTHY
};

const u16 gUproarOverTurnStringIds[] =
{
    [B_MSG_UPROAR_CONTINUES] = STRINGID_PKMNMAKINGUPROAR,
    [B_MSG_UPROAR_ENDS]      = STRINGID_PKMNCALMEDDOWN
};

const u16 gStockpileUsedStringIds[] =
{
    [B_MSG_STOCKPILED]     = STRINGID_PKMNSTOCKPILED,
    [B_MSG_CANT_STOCKPILE] = STRINGID_PKMNCANTSTOCKPILE,
};

const u16 gWokeUpStringIds[] =
{
    [B_MSG_WOKE_UP]        = STRINGID_PKMNWOKEUP,
    [B_MSG_WOKE_UP_UPROAR] = STRINGID_PKMNWOKEUPINUPROAR
};

const u16 gSwallowFailStringIds[] =
{
    [B_MSG_SWALLOW_FAILED]  = STRINGID_FAILEDTOSWALLOW,
    [B_MSG_SWALLOW_FULL_HP] = STRINGID_PKMNHPFULL
};

const u16 gUproarAwakeStringIds[] =
{
    [B_MSG_CANT_SLEEP_UPROAR]  = STRINGID_PKMNCANTSLEEPINUPROAR2,
    [B_MSG_UPROAR_KEPT_AWAKE]  = STRINGID_UPROARKEPTPKMNAWAKE,
};

const u16 gStatUpStringIds[] =
{
    [B_MSG_ATTACKER_STAT_ROSE] = STRINGID_ATTACKERSSTATROSE,
    [B_MSG_DEFENDER_STAT_ROSE] = STRINGID_DEFENDERSSTATROSE,
    [B_MSG_STAT_WONT_INCREASE] = STRINGID_STATSWONTINCREASE,
    [B_MSG_STAT_ROSE_EMPTY]    = STRINGID_EMPTYSTRING3,
    [B_MSG_STAT_ROSE_ITEM]     = STRINGID_USINGITEMSTATOFPKMNROSE,
    [B_MSG_USED_DIRE_HIT]      = STRINGID_PKMNUSEDXTOGETPUMPED,
};

const u16 gStatDownStringIds[] =
{
    [B_MSG_ATTACKER_STAT_FELL] = STRINGID_ATTACKERSSTATFELL,
    [B_MSG_DEFENDER_STAT_FELL] = STRINGID_DEFENDERSSTATFELL,
    [B_MSG_STAT_WONT_DECREASE] = STRINGID_STATSWONTDECREASE,
    [B_MSG_STAT_FELL_EMPTY]    = STRINGID_EMPTYSTRING3,
};

// Index copied from move's index in sTrappingMoves
const u16 gWrappedStringIds[NUM_TRAPPING_MOVES] =
{
    [B_MSG_WRAPPED_BIND]        = STRINGID_PKMNSQUEEZEDBYBIND,     // MOVE_BIND
    [B_MSG_WRAPPED_WRAP]        = STRINGID_PKMNWRAPPEDBY,          // MOVE_WRAP
    [B_MSG_WRAPPED_FIRE_SPIN]   = STRINGID_PKMNTRAPPEDINVORTEX,    // MOVE_FIRE_SPIN
    [B_MSG_WRAPPED_CLAMP]       = STRINGID_PKMNCLAMPED,            // MOVE_CLAMP
    [B_MSG_WRAPPED_WHIRLPOOL]   = STRINGID_PKMNTRAPPEDINVORTEX,    // MOVE_WHIRLPOOL
    [B_MSG_WRAPPED_SAND_TOMB]   = STRINGID_PKMNTRAPPEDBYSANDTOMB,  // MOVE_SAND_TOMB
    [B_MSG_WRAPPED_MAGMA_STORM] = STRINGID_TRAPPEDBYSWIRLINGMAGMA, // MOVE_MAGMA_STORM
    [B_MSG_WRAPPED_INFESTATION] = STRINGID_INFESTATION,            // MOVE_INFESTATION
    [B_MSG_WRAPPED_SNAP_TRAP]   = STRINGID_PKMNINSNAPTRAP,         // MOVE_SNAP_TRAP
    [B_MSG_WRAPPED_THUNDER_CAGE]= STRINGID_THUNDERCAGETRAPPED,     // MOVE_THUNDER_CAGE
};

const u16 gMistUsedStringIds[] =
{
    [B_MSG_SET_MIST]    = STRINGID_PKMNSHROUDEDINMIST,
    [B_MSG_MIST_FAILED] = STRINGID_BUTITFAILED
};

const u16 gFocusEnergyUsedStringIds[] =
{
    [B_MSG_GETTING_PUMPED]      = STRINGID_PKMNGETTINGPUMPED,
    [B_MSG_FOCUS_ENERGY_FAILED] = STRINGID_BUTITFAILED
};

const u16 gTransformUsedStringIds[] =
{
    [B_MSG_TRANSFORMED]      = STRINGID_PKMNTRANSFORMEDINTO,
    [B_MSG_TRANSFORM_FAILED] = STRINGID_BUTITFAILED
};

const u16 gSubstituteUsedStringIds[] =
{
    [B_MSG_SET_SUBSTITUTE]    = STRINGID_PKMNMADESUBSTITUTE,
    [B_MSG_SUBSTITUTE_FAILED] = STRINGID_TOOWEAKFORSUBSTITUTE
};

const u16 gGotPoisonedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASPOISONED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNPOISONEDBY
};

const u16 gGotParalyzedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASPARALYZED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNWASPARALYZEDBY
};

const u16 gFellAsleepStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNFELLASLEEP,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNMADESLEEP,
};

const u16 gGotBurnedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASBURNED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNBURNEDBY
};

const u16 gGotFrostbiteStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNGOTFROSTBITE,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNGOTFROSTBITE,
};

const u16 gFrostbiteHealedStringIds[] =
{
    [B_MSG_FROSTBITE_HEALED]         = STRINGID_PKMNFROSTBITEHEALED2,
    [B_MSG_FROSTBITE_HEALED_BY_MOVE] = STRINGID_PKMNFROSTBITEHEALEDBY
};

const u16 gGotFrozenStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASFROZEN,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNFROZENBY
};

const u16 gGotDefrostedStringIds[] =
{
    [B_MSG_DEFROSTED]         = STRINGID_PKMNWASDEFROSTED2,
    [B_MSG_DEFROSTED_BY_MOVE] = STRINGID_PKMNWASDEFROSTEDBY
};

const u16 gKOFailedStringIds[] =
{
    [B_MSG_KO_MISS]       = STRINGID_ATTACKMISSED,
    [B_MSG_KO_UNAFFECTED] = STRINGID_PKMNUNAFFECTED
};

const u16 gAttractUsedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNFELLINLOVE,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNSXINFATUATEDY
};

const u16 gAbsorbDrainStringIds[] =
{
    [B_MSG_ABSORB]      = STRINGID_PKMNENERGYDRAINED,
    [B_MSG_ABSORB_OOZE] = STRINGID_ITSUCKEDLIQUIDOOZE
};

const u16 gSportsUsedStringIds[] =
{
    [B_MSG_WEAKEN_ELECTRIC] = STRINGID_ELECTRICITYWEAKENED,
    [B_MSG_WEAKEN_FIRE]     = STRINGID_FIREWEAKENED
};

const u16 gPartyStatusHealStringIds[] =
{
    [B_MSG_BELL]                     = STRINGID_BELLCHIMED,
    [B_MSG_BELL_SOUNDPROOF_ATTACKER] = STRINGID_BELLCHIMED,
    [B_MSG_BELL_SOUNDPROOF_PARTNER]  = STRINGID_BELLCHIMED,
    [B_MSG_BELL_BOTH_SOUNDPROOF]     = STRINGID_BELLCHIMED,
    [B_MSG_SOOTHING_AROMA]           = STRINGID_SOOTHINGAROMA
};

const u16 gFutureMoveUsedStringIds[] =
{
    [B_MSG_FUTURE_SIGHT] = STRINGID_PKMNFORESAWATTACK,
    [B_MSG_DOOM_DESIRE]  = STRINGID_PKMNCHOSEXASDESTINY
};

const u16 gBallEscapeStringIds[] =
{
    [BALL_NO_SHAKES]     = STRINGID_PKMNBROKEFREE,
    [BALL_1_SHAKE]       = STRINGID_ITAPPEAREDCAUGHT,
    [BALL_2_SHAKES]      = STRINGID_AARGHALMOSTHADIT,
    [BALL_3_SHAKES_FAIL] = STRINGID_SHOOTSOCLOSE
};

// Overworld weathers that don't have an associated battle weather default to "It is raining."
const u16 gWeatherStartsStringIds[] =
{
    [WEATHER_NONE]               = STRINGID_ITISRAINING,
    [WEATHER_SUNNY_CLOUDS]       = STRINGID_ITISRAINING,
    [WEATHER_SUNNY]              = STRINGID_ITISRAINING,
    [WEATHER_RAIN]               = STRINGID_ITISRAINING,
    [WEATHER_SNOW]               = (B_OVERWORLD_SNOW >= GEN_9 ? STRINGID_ITISSNOWING : STRINGID_ITISHAILING),
    [WEATHER_RAIN_THUNDERSTORM]  = STRINGID_ITISRAINING,
    [WEATHER_FOG_HORIZONTAL]     = STRINGID_FOGISDEEP,
    [WEATHER_VOLCANIC_ASH]       = STRINGID_ITISRAINING,
    [WEATHER_SANDSTORM]          = STRINGID_SANDSTORMISRAGING,
    [WEATHER_FOG_DIAGONAL]       = STRINGID_FOGISDEEP,
    [WEATHER_UNDERWATER]         = STRINGID_ITISRAINING,
    [WEATHER_SHADE]              = STRINGID_ITISRAINING,
    [WEATHER_DROUGHT]            = STRINGID_SUNLIGHTISHARSH,
    [WEATHER_DOWNPOUR]           = STRINGID_ITISRAINING,
    [WEATHER_UNDERWATER_BUBBLES] = STRINGID_ITISRAINING,
    [WEATHER_ABNORMAL]           = STRINGID_ITISRAINING
};

const u16 gTerrainStartsStringIds[] =
{
    [B_MSG_TERRAIN_SET_MISTY]    = STRINGID_MISTSWIRLSAROUND,
    [B_MSG_TERRAIN_SET_ELECTRIC] = STRINGID_ELECTRICCURRENTISRUNNING,
    [B_MSG_TERRAIN_SET_PSYCHIC]  = STRINGID_SEEMSWEIRD,
    [B_MSG_TERRAIN_SET_GRASSY]   = STRINGID_ISCOVEREDWITHGRASS,
};

const u16 gPrimalWeatherBlocksStringIds[] =
{
    [B_MSG_PRIMAL_WEATHER_FIZZLED_BY_RAIN]      = STRINGID_MOVEFIZZLEDOUTINTHEHEAVYRAIN,
    [B_MSG_PRIMAL_WEATHER_EVAPORATED_IN_SUN]    = STRINGID_MOVEEVAPORATEDINTHEHARSHSUNLIGHT,
};

const u16 gInobedientStringIds[] =
{
    [B_MSG_LOAFING]            = STRINGID_PKMNLOAFING,
    [B_MSG_WONT_OBEY]          = STRINGID_PKMNWONTOBEY,
    [B_MSG_TURNED_AWAY]        = STRINGID_PKMNTURNEDAWAY,
    [B_MSG_PRETEND_NOT_NOTICE] = STRINGID_PKMNPRETENDNOTNOTICE,
    [B_MSG_INCAPABLE_OF_POWER] = STRINGID_PKMNINCAPABLEOFPOWER
};

const u16 gSafariGetNearStringIds[] =
{
    [B_MSG_CREPT_CLOSER]    = STRINGID_CREPTCLOSER,
    [B_MSG_CANT_GET_CLOSER] = STRINGID_CANTGETCLOSER
};

const u16 gSafariPokeblockResultStringIds[] =
{
    [B_MSG_MON_CURIOUS]    = STRINGID_PKMNCURIOUSABOUTX,
    [B_MSG_MON_ENTHRALLED] = STRINGID_PKMNENTHRALLEDBYX,
    [B_MSG_MON_IGNORED]    = STRINGID_PKMNIGNOREDX
};

const u16 gBerryEffectStringIds[] =
{
    [B_MSG_CURED_PROBLEM]     = STRINGID_PKMNSITEMCUREDPROBLEM,
    [B_MSG_NORMALIZED_STATUS] = STRINGID_PKMNSITEMNORMALIZEDSTATUS
};

const u16 gStatusPreventionStringIds[] =
{
    [B_MSG_ABILITY_PREVENTS_MOVE_BURN]      = STRINGID_PKMNSXPREVENTSBURNS,
    [B_MSG_ABILITY_PREVENTS_MOVE_PARALYSIS] = STRINGID_PKMNPREVENTSPARALYSISWITH,
    [B_MSG_ABILITY_PREVENTS_MOVE_POISON]    = STRINGID_PKMNPREVENTSPOISONINGWITH,
    [B_MSG_ABILITY_PREVENTS_ABILITY_STATUS] = STRINGID_PKMNSXPREVENTSYSZ,
    [B_MSG_STATUS_HAD_NO_EFFECT]            = STRINGID_PKMNSXHADNOEFFECTONY,
    [B_MSG_ABILITY_PASTEL_VEIL]             = STRINGID_PASTELVEILPROTECTED
};

const u16 gItemSwapStringIds[] =
{
    [B_MSG_ITEM_SWAP_TAKEN] = STRINGID_PKMNOBTAINEDX,
    [B_MSG_ITEM_SWAP_GIVEN] = STRINGID_PKMNOBTAINEDX2,
    [B_MSG_ITEM_SWAP_BOTH]  = STRINGID_PKMNOBTAINEDXYOBTAINEDZ
};

const u16 gFlashFireStringIds[] =
{
    [B_MSG_FLASH_FIRE_BOOST]    = STRINGID_PKMNRAISEDFIREPOWERWITH,
    [B_MSG_FLASH_FIRE_NO_BOOST] = STRINGID_PKMNSXMADEYINEFFECTIVE
};

const u16 gCaughtMonStringIds[] =
{
    [B_MSG_SENT_SOMEONES_PC]   = STRINGID_PKMNTRANSFERREDSOMEONESPC,
    [B_MSG_SENT_LANETTES_PC]   = STRINGID_PKMNTRANSFERREDLANETTESPC,
    [B_MSG_SOMEONES_BOX_FULL]  = STRINGID_PKMNBOXSOMEONESPCFULL,
    [B_MSG_LANETTES_BOX_FULL]  = STRINGID_PKMNBOXLANETTESPCFULL,
    [B_MSG_SWAPPED_INTO_PARTY] = STRINGID_PKMNSENTTOPCAFTERCATCH,
};

const u16 gRoomsStringIds[] =
{
    STRINGID_PKMNTWISTEDDIMENSIONS, STRINGID_TRICKROOMENDS,
    STRINGID_SWAPSDEFANDSPDEFOFALLPOKEMON, STRINGID_WONDERROOMENDS,
    STRINGID_HELDITEMSLOSEEFFECTS, STRINGID_MAGICROOMENDS,
    STRINGID_EMPTYSTRING3
};

const u16 gStatusConditionsStringIds[] =
{
    STRINGID_PKMNWASPOISONED, STRINGID_PKMNBADLYPOISONED, STRINGID_PKMNWASBURNED, STRINGID_PKMNWASPARALYZED, STRINGID_PKMNFELLASLEEP, STRINGID_PKMNGOTFROSTBITE
};

const u16 gDamageNonTypesStartStringIds[] =
{
    [B_MSG_TRAPPED_WITH_VINES]  = STRINGID_TEAMTRAPPEDWITHVINES,
    [B_MSG_CAUGHT_IN_VORTEX]    = STRINGID_TEAMCAUGHTINVORTEX,
    [B_MSG_SURROUNDED_BY_FIRE]  = STRINGID_TEAMSURROUNDEDBYFIRE,
    [B_MSG_SURROUNDED_BY_ROCKS] = STRINGID_TEAMSURROUNDEDBYROCKS,
};

const u16 gDamageNonTypesDmgStringIds[] =
{
    [B_MSG_HURT_BY_VINES]        = STRINGID_PKMNHURTBYVINES,
    [B_MSG_HURT_BY_VORTEX]       = STRINGID_PKMNHURTBYVORTEX,
    [B_MSG_BURNING_UP]           = STRINGID_PKMNBURNINGUP,
    [B_MSG_HURT_BY_ROCKS_THROWN] = STRINGID_PKMNHURTBYROCKSTHROWN,
};

const u16 gDefogHazardsStringIds[] =
{
    [HAZARDS_SPIKES] = STRINGID_SPIKESDISAPPEAREDFROMTEAM,
    [HAZARDS_STICKY_WEB] = STRINGID_STICKYWEBDISAPPEAREDFROMTEAM,
    [HAZARDS_TOXIC_SPIKES] = STRINGID_TOXICSPIKESDISAPPEAREDFROMTEAM,
    [HAZARDS_STEALTH_ROCK] = STRINGID_STEALTHROCKDISAPPEAREDFROMTEAM,
    [HAZARDS_STEELSURGE] = STRINGID_SHARPSTEELDISAPPEAREDFROMTEAM,
};

const u16 gSpinHazardsStringIds[] =
{
    [HAZARDS_SPIKES] = STRINGID_PKMNBLEWAWAYSPIKES,
    [HAZARDS_STICKY_WEB] = STRINGID_PKMNBLEWAWAYSTICKYWEB,
    [HAZARDS_TOXIC_SPIKES] = STRINGID_PKMNBLEWAWAYTOXICSPIKES,
    [HAZARDS_STEALTH_ROCK] = STRINGID_PKMNBLEWAWAYSTEALTHROCK,
    [HAZARDS_STEELSURGE] = STRINGID_PKMNBLEWAWAYSHARPSTEEL,
};

const u8 gText_PkmnIsEvolving[] = _("Apa?\n{STR_VAR_1} berevolusi!");
const u8 gText_CongratsPkmnEvolved[] = _("Selamat! {STR_VAR_1}\njadi {STR_VAR_2}!{WAIT_SE}\p");
const u8 gText_PkmnStoppedEvolving[] = _("Hah? {STR_VAR_1}\ngagal berevolusi!\p");
const u8 gText_EllipsisQuestionMark[] = _("……?\p");
const u8 gText_WhatWillPkmnDo[] = _("Apa yang akan\n{B_BUFF1} lakukan?");
const u8 gText_WhatWillPkmnDo2[] = _("Apa yang akan\n{B_PLAYER_NAME} lakukan?");
const u8 gText_WhatWillWallyDo[] = _("Apa yang akan\nWALLY lakukan?");
const u8 gText_LinkStandby[] = _("{PAUSE 16}Tunggu link…");
const u8 gText_BattleMenu[] = _("Battle{CLEAR_TO 56}Bag\nPokémon{CLEAR_TO 56}Run");
const u8 gText_SafariZoneMenu[] = _("Ball{CLEAR_TO 56}{POKEBLOCK}\nGo Near{CLEAR_TO 56}Run");
const u8 gText_MoveInterfacePP[] = _("PP ");
const u8 gText_MoveInterfaceType[] = _("TYPE/");
const u8 gText_MoveInterfacePpType[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}PP\nTYPE/");
const u8 gText_MoveInterfaceDynamicColors[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}");
const u8 gText_WhichMoveToForget4[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}Lupakan\njurusan mana?");
const u8 gText_BattleYesNoChoice[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}Ya\nTidak");
const u8 gText_BattleSwitchWhich[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}Ganti\nyang mana?");
const u8 gText_BattleSwitchWhich2[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}");
const u8 gText_BattleSwitchWhich3[] = _("{UP_ARROW}");
const u8 gText_BattleSwitchWhich4[] = _("{ESCAPE 4}");
const u8 gText_BattleSwitchWhich5[] = _("-");
const u8 gText_SafariBalls[] = _("{HIGHLIGHT DARK_GRAY}Safari Balls");
const u8 gText_SafariBallLeft[] = _("{HIGHLIGHT DARK_GRAY}Sisa: $" "{HIGHLIGHT DARK_GRAY}");
const u8 gText_Sleep[] = _("tidur");
const u8 gText_Poison[] = _("racun");
const u8 gText_Burn[] = _("luka bakar");
const u8 gText_Paralysis[] = _("lumpuh");
const u8 gText_Ice[] = _("beku");
const u8 gText_Confusion[] = _("bingung");
const u8 gText_Love[] = _("cinta");
const u8 gText_SpaceAndSpace[] = _(" dan ");
const u8 gText_CommaSpace[] = _(", ");
const u8 gText_Space2[] = _(" ");
const u8 gText_LineBreak[] = _("\l");
const u8 gText_NewLine[] = _("\n");
const u8 gText_Are[] = _("adalah");
const u8 gText_Are2[] = _("adalah");
const u8 gText_BadEgg[] = _("Bad Egg");
const u8 gText_BattleWallyName[] = _("WALLY");
const u8 gText_Win[] = _("{HIGHLIGHT TRANSPARENT}Menang");
const u8 gText_Loss[] = _("{HIGHLIGHT TRANSPARENT}Kalah");
const u8 gText_Draw[] = _("{HIGHLIGHT TRANSPARENT}Seri");
static const u8 sText_SpaceIs[] = _(" adalah");
static const u8 sText_ApostropheS[] = _("'s");
const u8 gText_BattleTourney[] = _("BATTLE TOURNEY");

const u8 *const gRoundsStringTable[DOME_ROUNDS_COUNT] =
{
    [DOME_ROUND1]    = COMPOUND_STRING("Round 1"),
    [DOME_ROUND2]    = COMPOUND_STRING("Round 2"),
    [DOME_SEMIFINAL] = COMPOUND_STRING("Semifinal"),
    [DOME_FINAL]     = COMPOUND_STRING("Final"),
};

const u8 gText_TheGreatNewHope[] = _("Harapan baru yang hebat!\p");
const u8 gText_WillChampionshipDreamComeTrue[] = _("Akankah mimpi juara jadi nyata?!\p");
const u8 gText_AFormerChampion[] = _("Mantan juara!\p");
const u8 gText_ThePreviousChampion[] = _("Juara sebelumnya!\p");
const u8 gText_TheUnbeatenChampion[] = _("Juara tak terkalahkan!\p");
const u8 gText_PlayerMon1Name[] = _("{B_PLAYER_MON1_NAME}");
const u8 gText_Vs[] = _("VS");
const u8 gText_OpponentMon1Name[] = _("{B_OPPONENT_MON1_NAME}");
const u8 gText_Mind[] = _("Pikiran");
const u8 gText_Skill[] = _("Kemampuan");
const u8 gText_Body[] = _("Tubuh");
const u8 gText_Judgment[] = _("{B_BUFF1}{CLEAR 13}Penilaian{CLEAR 13}{B_BUFF2}");
static const u8 sText_TwoTrainersSentPkmn[] = _("{B_TRAINER1_NAME_WITH_CLASS} keluarkan {B_OPPONENT_MON1_NAME}!\p{B_TRAINER2_NAME_WITH_CLASS} keluarkan {B_OPPONENT_MON2_NAME}!");
static const u8 sText_Trainer2SentOutPkmn[] = _("{B_TRAINER2_NAME_WITH_CLASS} keluarkan {B_BUFF1}!");
static const u8 sText_TwoTrainersWantToBattle[] = _("Kamu ditantang oleh\n{B_TRAINER1_NAME_WITH_CLASS}\ndan {B_TRAINER2_NAME_WITH_CLASS}!\p");
static const u8 sText_InGamePartnerSentOutZGoN[] = _("{B_PARTNER_NAME_WITH_CLASS} keluarkan {B_PLAYER_MON2_NAME}!\nAyo, {B_PLAYER_MON1_NAME}!");

const u16 gBattlePalaceFlavorTextTable[] =
{
    [B_MSG_GLINT_IN_EYE]   = STRINGID_GLINTAPPEARSINEYE,
    [B_MSG_GETTING_IN_POS] = STRINGID_PKMNGETTINGINTOPOSITION,
    [B_MSG_GROWL_DEEPLY]   = STRINGID_PKMNBEGANGROWLINGDEEPLY,
    [B_MSG_EAGER_FOR_MORE] = STRINGID_PKMNEAGERFORMORE,
};

const u8 *const gRefereeStringsTable[] =
{
    [B_MSG_REF_NOTHING_IS_DECIDED] = COMPOUND_STRING("REFEREE: Jika belum ada pemenang\ndalam 3 giliran, kita lanjut\nke penilaian!"),
    [B_MSG_REF_THATS_IT]           = COMPOUND_STRING("REFEREE: Cukup! Kita lanjut ke\npenilaian untuk tentukan\npemenangnya!"),
    [B_MSG_REF_JUDGE_MIND]         = COMPOUND_STRING("REFEREE: Kategori 1, Pikiran!\nPOKéMON paling berani!\p"),
    [B_MSG_REF_JUDGE_SKILL]        = COMPOUND_STRING("REFEREE: Kategori 2, Kemampuan!\nPOKéMON paling lihai pakai\njurusan!\p"),
    [B_MSG_REF_JUDGE_BODY]         = COMPOUND_STRING("REFEREE: Kategori 3, Tubuh!\nPOKéMON paling bertenaga!\p"),
    [B_MSG_REF_PLAYER_WON]         = COMPOUND_STRING("REFEREE: Nilai: {B_BUFF1} lawan\n{B_BUFF2}! Pemenangnya\n{B_PLAYER_NAME}'s\n{B_PLAYER_MON1_NAME}!\p"),
    [B_MSG_REF_OPPONENT_WON]       = COMPOUND_STRING("REFEREE: Nilai: {B_BUFF1} lawan\n{B_BUFF2}! Pemenangnya\n{B_TRAINER1_NAME}'s\n{B_OPPONENT_MON1_NAME}!\p"),
    [B_MSG_REF_DRAW]               = COMPOUND_STRING("REFEREE: Nilai: 3 lawan 3!\nHasilnya seri!\p"),
    [B_MSG_REF_COMMENCE_BATTLE]    = COMPOUND_STRING("REFEREE: {B_PLAYER_MON1_NAME}\nVS {B_OPPONENT_MON1_NAME}!\nMulai bertarung!"),
};

static const u8 sText_Trainer1Fled[] = _( "{PLAY_SE SE_FLEE}{B_TRAINER1_NAME_WITH_CLASS} kabur!");
static const u8 sText_PlayerLostAgainstTrainer1[] = _("Kamu kalah dari\n{B_TRAINER1_NAME_WITH_CLASS}!");
static const u8 sText_PlayerBattledToDrawTrainer1[] = _("Hasil imbang melawan\n{B_TRAINER1_NAME_WITH_CLASS}!");
const u8 gText_RecordBattleToPass[] = _("Ingin simpan hasil\npertarungan di Frontier Pass?");
const u8 gText_BattleRecordedOnPass[] = _("Hasil pertarungan {B_PLAYER_NAME}\ntersimpan di Frontier Pass.");
static const u8 sText_LinkTrainerWantsToBattlePause[] = _("Kamu ditantang oleh\n{B_LINK_OPPONENT1_NAME}!\p");
static const u8 sText_TwoLinkTrainersWantToBattlePause[] = _("Kamu ditantang oleh\n{B_LINK_OPPONENT1_NAME} dan\n{B_LINK_OPPONENT2_NAME}!\p");
static const u8 sText_Your1[] = _("Milikmu");
static const u8 sText_Opposing1[] = _("Pihak lawan");
static const u8 sText_Your2[] = _("milikmu");
static const u8 sText_Opposing2[] = _("Pihak lawan");

// This is four lists of moves which use a different attack string in Japanese
// to the default. See the documentation for ChooseTypeOfMoveUsedString for more detail.
static const u16 sGrammarMoveUsedTable[] =
{
    MOVE_SWORDS_DANCE, MOVE_STRENGTH, MOVE_GROWTH,
    MOVE_HARDEN, MOVE_MINIMIZE, MOVE_SMOKESCREEN,
    MOVE_WITHDRAW, MOVE_DEFENSE_CURL, MOVE_EGG_BOMB,
    MOVE_SMOG, MOVE_BONE_CLUB, MOVE_FLASH, MOVE_SPLASH,
    MOVE_ACID_ARMOR, MOVE_BONEMERANG, MOVE_REST, MOVE_SHARPEN,
    MOVE_SUBSTITUTE, MOVE_MIND_READER, MOVE_SNORE,
    MOVE_PROTECT, MOVE_SPIKES, MOVE_ENDURE, MOVE_ROLLOUT,
    MOVE_SWAGGER, MOVE_SLEEP_TALK, MOVE_HIDDEN_POWER,
    MOVE_PSYCH_UP, MOVE_EXTREME_SPEED, MOVE_FOLLOW_ME,
    MOVE_TRICK, MOVE_ASSIST, MOVE_INGRAIN, MOVE_KNOCK_OFF,
    MOVE_CAMOUFLAGE, MOVE_ASTONISH, MOVE_ODOR_SLEUTH,
    MOVE_GRASS_WHISTLE, MOVE_SHEER_COLD, MOVE_MUDDY_WATER,
    MOVE_IRON_DEFENSE, MOVE_BOUNCE, 0,

    MOVE_TELEPORT, MOVE_RECOVER, MOVE_BIDE, MOVE_AMNESIA,
    MOVE_FLAIL, MOVE_TAUNT, MOVE_BULK_UP, 0,

    MOVE_MEDITATE, MOVE_AGILITY, MOVE_MIMIC, MOVE_DOUBLE_TEAM,
    MOVE_BARRAGE, MOVE_TRANSFORM, MOVE_STRUGGLE, MOVE_SCARY_FACE,
    MOVE_CHARGE, MOVE_WISH, MOVE_BRICK_BREAK, MOVE_YAWN,
    MOVE_FEATHER_DANCE, MOVE_TEETER_DANCE, MOVE_MUD_SPORT,
    MOVE_FAKE_TEARS, MOVE_WATER_SPORT, MOVE_CALM_MIND, 0,

    MOVE_POUND, MOVE_SCRATCH, MOVE_VISE_GRIP,
    MOVE_WING_ATTACK, MOVE_FLY, MOVE_BIND, MOVE_SLAM,
    MOVE_HORN_ATTACK, MOVE_WRAP, MOVE_THRASH, MOVE_TAIL_WHIP,
    MOVE_LEER, MOVE_BITE, MOVE_GROWL, MOVE_ROAR,
    MOVE_SING, MOVE_PECK, MOVE_ABSORB, MOVE_STRING_SHOT,
    MOVE_EARTHQUAKE, MOVE_FISSURE, MOVE_DIG, MOVE_TOXIC,
    MOVE_SCREECH, MOVE_METRONOME, MOVE_LICK, MOVE_CLAMP,
    MOVE_CONSTRICT, MOVE_POISON_GAS, MOVE_BUBBLE,
    MOVE_SLASH, MOVE_SPIDER_WEB, MOVE_NIGHTMARE, MOVE_CURSE,
    MOVE_FORESIGHT, MOVE_CHARM, MOVE_ATTRACT, MOVE_ROCK_SMASH,
    MOVE_UPROAR, MOVE_SPIT_UP, MOVE_SWALLOW, MOVE_TORMENT,
    MOVE_FLATTER, MOVE_ROLE_PLAY, MOVE_ENDEAVOR, MOVE_TICKLE,
    MOVE_COVET, 0
};

static const u8 sText_EmptyStatus[] = _("$$$$$$$");

static const struct BattleWindowText sTextOnWindowsInfo_Normal[] =
{
    [B_WIN_MSG] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 1,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    [B_WIN_ACTION_PROMPT] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    [B_WIN_ACTION_MENU] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_PP] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = B_SHOW_EFFECTIVENESS != SHOW_EFFECTIVENESS_NEVER ? 13 : 12,
        .bgColor = 14,
        .shadowColor = B_SHOW_EFFECTIVENESS != SHOW_EFFECTIVENESS_NEVER ? 15 : 11,
    },
    [B_WIN_DUMMY] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_PP_REMAINING] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 2,
        .y = 1,
        .speed = 0,
        .fgColor = 12,
        .bgColor = 14,
        .shadowColor = 11,
    },
    [B_WIN_MOVE_TYPE] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_SWITCH_PROMPT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_YESNO] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_LEVEL_UP_BOX] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_LEVEL_UP_BANNER] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = 32,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .shadowColor = 2,
    },
    [B_WIN_VS_PLAYER] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_OPPONENT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_OUTCOME_DRAW] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .shadowColor = 6,
    },
    [B_WIN_VS_OUTCOME_LEFT] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .shadowColor = 6,
    },
    [B_WIN_VS_OUTCOME_RIGHT] = {
        .fillValue = PIXEL_FILL(0x0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .shadowColor = 6,
    },
    [B_WIN_MOVE_DESCRIPTION] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = TEXT_DYNAMIC_COLOR_4,
        .bgColor = TEXT_DYNAMIC_COLOR_5,
        .shadowColor = TEXT_DYNAMIC_COLOR_6,
    },
};

static const struct BattleWindowText sTextOnWindowsInfo_Arena[] =
{
    [B_WIN_MSG] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 1,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    [B_WIN_ACTION_PROMPT] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    [B_WIN_ACTION_MENU] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_PP] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = B_SHOW_EFFECTIVENESS != SHOW_EFFECTIVENESS_NEVER ? 13 : 12,
        .bgColor = 14,
        .shadowColor = B_SHOW_EFFECTIVENESS != SHOW_EFFECTIVENESS_NEVER ? 15 : 11,
    },
    [B_WIN_DUMMY] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_PP_REMAINING] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 2,
        .y = 1,
        .speed = 0,
        .fgColor = 12,
        .bgColor = 14,
        .shadowColor = 11,
    },
    [B_WIN_MOVE_TYPE] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_SWITCH_PROMPT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_YESNO] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_LEVEL_UP_BOX] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_LEVEL_UP_BANNER] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = 32,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .shadowColor = 2,
    },
    [ARENA_WIN_PLAYER_NAME] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_VS] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_OPPONENT_NAME] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_MIND] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_SKILL] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_BODY] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_JUDGMENT_TITLE] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_JUDGMENT_TEXT] = {
        .fillValue = PIXEL_FILL(0x1),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 1,
        .fgColor = 2,
        .bgColor = 1,
        .shadowColor = 3,
    },
    [B_WIN_MOVE_DESCRIPTION] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .speed = 0,
        .fgColor = TEXT_DYNAMIC_COLOR_4,
        .bgColor = TEXT_DYNAMIC_COLOR_5,
        .shadowColor = TEXT_DYNAMIC_COLOR_6,
    },
};

static const struct BattleWindowText *const sBattleTextOnWindowsInfo[] =
{
    [B_WIN_TYPE_NORMAL] = sTextOnWindowsInfo_Normal,
    [B_WIN_TYPE_ARENA]  = sTextOnWindowsInfo_Arena
};

static const u8 sRecordedBattleTextSpeeds[] = {8, 4, 1, 0};

void BufferStringBattle(enum StringID stringID, u32 battler)
{
    s32 i;
    const u8 *stringPtr = NULL;

    gBattleMsgDataPtr = (struct BattleMsgData *)(&gBattleResources->bufferA[battler][4]);
    gLastUsedItem = gBattleMsgDataPtr->lastItem;
    gLastUsedAbility = gBattleMsgDataPtr->lastAbility;
    gBattleScripting.battler = gBattleMsgDataPtr->scrActive;
    gBattleStruct->scriptPartyIdx = gBattleMsgDataPtr->bakScriptPartyIdx;
    gBattleStruct->hpScale = gBattleMsgDataPtr->hpScale;
    gPotentialItemEffectBattler = gBattleMsgDataPtr->itemEffectBattler;
    gBattleStruct->stringMoveType = gBattleMsgDataPtr->moveType;

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        sBattlerAbilities[i] = gBattleMsgDataPtr->abilities[i];
    }
    for (i = 0; i < TEXT_BUFF_ARRAY_COUNT; i++)
    {
        gBattleTextBuff1[i] = gBattleMsgDataPtr->textBuffs[0][i];
        gBattleTextBuff2[i] = gBattleMsgDataPtr->textBuffs[1][i];
        gBattleTextBuff3[i] = gBattleMsgDataPtr->textBuffs[2][i];
    }

    switch (stringID)
    {
    case STRINGID_INTROMSG: // first battle msg
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        {
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                {
                    stringPtr = sText_TwoTrainersWantToBattle;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
                        stringPtr = sText_TwoLinkTrainersWantToBattlePause;
                    else
                        stringPtr = sText_TwoLinkTrainersWantToBattle;
                }
                else
                {
                    if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_UNION_ROOM)
                        stringPtr = sText_Trainer1WantsToBattle;
                    else if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
                        stringPtr = sText_LinkTrainerWantsToBattlePause;
                    else
                        stringPtr = sText_LinkTrainerWantsToBattle;
                }
            }
            else
            {
                if (BATTLE_TWO_VS_ONE_OPPONENT)
                    stringPtr = sText_Trainer1WantsToBattle;
                else if (gBattleTypeFlags & (BATTLE_TYPE_MULTI | BATTLE_TYPE_INGAME_PARTNER))
                    stringPtr = sText_TwoTrainersWantToBattle;
                else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = sText_TwoTrainersWantToBattle;
                else
                    stringPtr = sText_Trainer1WantsToBattle;
            }
        }
        else
        {
            if (gBattleTypeFlags & BATTLE_TYPE_LEGENDARY)
                stringPtr = sText_LegendaryPkmnAppeared;
            else if (IsDoubleBattle() && IsValidForBattle(GetBattlerMon(GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT))))
                stringPtr = sText_TwoWildPkmnAppeared;
            else if (gBattleTypeFlags & BATTLE_TYPE_WALLY_TUTORIAL)
                stringPtr = sText_WildPkmnAppearedPause;
            else
                stringPtr = sText_WildPkmnAppeared;
        }
        break;
    case STRINGID_INTROSENDOUT: // poke first send-out
        if (IsOnPlayerSide(battler))
        {
            if (IsDoubleBattle() && IsValidForBattle(GetBattlerMon(BATTLE_PARTNER(battler))))
            {
                if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
                    stringPtr = sText_InGamePartnerSentOutZGoN;
                else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = sText_GoTwoPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = sText_LinkPartnerSentOutPkmnGoPkmn;
                else
                    stringPtr = sText_GoTwoPkmn;
            }
            else
            {
                stringPtr = sText_GoPkmn;
            }
        }
        else
        {
            if (IsDoubleBattle() && IsValidForBattle(GetBattlerMon(BATTLE_PARTNER(battler))))
            {
                if (BATTLE_TWO_VS_ONE_OPPONENT)
                    stringPtr = sText_Trainer1SentOutTwoPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = sText_TwoTrainersSentPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                    stringPtr = sText_TwoTrainersSentPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = sText_TwoLinkTrainersSentOutPkmn;
                else if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
                    stringPtr = sText_LinkTrainerSentOutTwoPkmn;
                else
                    stringPtr = sText_Trainer1SentOutTwoPkmn;
            }
            else
            {
                if (!(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK)))
                    stringPtr = sText_Trainer1SentOutPkmn;
                else if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_UNION_ROOM)
                    stringPtr = sText_Trainer1SentOutPkmn;
                else
                    stringPtr = sText_LinkTrainerSentOutPkmn;
            }
        }
        break;
    case STRINGID_RETURNMON: // sending poke to ball msg
        if (IsOnPlayerSide(battler))
        {
            if (*(&gBattleStruct->hpScale) == 0)
                stringPtr = sText_PkmnThatsEnough;
            else if (*(&gBattleStruct->hpScale) == 1 || IsDoubleBattle())
                stringPtr = sText_PkmnComeBack;
            else if (*(&gBattleStruct->hpScale) == 2)
                stringPtr = sText_PkmnOkComeBack;
            else
                stringPtr = sText_PkmnGoodComeBack;
        }
        else
        {
            if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_LINK_OPPONENT || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = sText_LinkTrainer2WithdrewPkmn;
                else
                    stringPtr = sText_LinkTrainer1WithdrewPkmn;
            }
            else
            {
                stringPtr = sText_Trainer1WithdrewPkmn;
            }
        }
        break;
    case STRINGID_SWITCHINMON: // switch-in msg
        if (IsOnPlayerSide(gBattleScripting.battler))
        {
            if (*(&gBattleStruct->hpScale) == 0 || IsDoubleBattle())
                stringPtr = sText_GoPkmn2;
            else if (*(&gBattleStruct->hpScale) == 1)
                stringPtr = sText_DoItPkmn;
            else if (*(&gBattleStruct->hpScale) == 2)
                stringPtr = sText_GoForItPkmn;
            else
                stringPtr = sText_YourFoesWeakGetEmPkmn;
        }
        else
        {
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                {
                    if (gBattleScripting.battler == 1)
                        stringPtr = sText_Trainer1SentOutPkmn2;
                    else
                        stringPtr = sText_Trainer2SentOutPkmn;
                }
                else
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                        stringPtr = sText_LinkTrainerMultiSentOutPkmn;
                    else if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_UNION_ROOM)
                        stringPtr = sText_Trainer1SentOutPkmn2;
                    else
                        stringPtr = sText_LinkTrainerSentOutPkmn2;
                }
            }
            else
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                {
                    if (gBattleScripting.battler == 1)
                        stringPtr = sText_Trainer1SentOutPkmn2;
                    else
                        stringPtr = sText_Trainer2SentOutPkmn;
                }
                else
                {
                    stringPtr = sText_Trainer1SentOutPkmn2;
                }
            }
        }
        break;
    case STRINGID_USEDMOVE: // Pokémon used a move msg
        if (gBattleMsgDataPtr->currentMove >= MOVES_COUNT
         && !IsZMove(gBattleMsgDataPtr->currentMove)
         && !IsMaxMove(gBattleMsgDataPtr->currentMove))
            StringCopy(gBattleTextBuff3, gTypesInfo[*(&gBattleStruct->stringMoveType)].generic);
        else
            StringCopy(gBattleTextBuff3, GetMoveName(gBattleMsgDataPtr->currentMove));
        stringPtr = sText_AttackerUsedX;
        break;
    case STRINGID_BATTLEEND: // battle end
        if (gBattleTextBuff1[0] & B_OUTCOME_LINK_BATTLE_RAN)
        {
            gBattleTextBuff1[0] &= ~(B_OUTCOME_LINK_BATTLE_RAN);
            if (!IsOnPlayerSide(battler) && gBattleTextBuff1[0] != B_OUTCOME_DREW)
                gBattleTextBuff1[0] ^= (B_OUTCOME_LOST | B_OUTCOME_WON);

            if (gBattleTextBuff1[0] == B_OUTCOME_LOST || gBattleTextBuff1[0] == B_OUTCOME_DREW)
                stringPtr = sText_GotAwaySafely;
            else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                stringPtr = sText_TwoWildFled;
            else
                stringPtr = sText_WildFled;
        }
        else
        {
            if (!IsOnPlayerSide(battler) && gBattleTextBuff1[0] != B_OUTCOME_DREW)
                gBattleTextBuff1[0] ^= (B_OUTCOME_LOST | B_OUTCOME_WON);

            if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                        stringPtr = sText_TwoInGameTrainersDefeated;
                    else
                        stringPtr = sText_TwoLinkTrainersDefeated;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostToTwo;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawVsTwo;
                    break;
                }
            }
            else if (TRAINER_BATTLE_PARAM.opponentA == TRAINER_UNION_ROOM)
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    stringPtr = sText_PlayerDefeatedLinkTrainerTrainer1;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostAgainstTrainer1;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawTrainer1;
                    break;
                }
            }
            else
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    stringPtr = sText_PlayerDefeatedLinkTrainer;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostAgainstLinkTrainer;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawLinkTrainer;
                    break;
                }
            }
        }
        break;
    case STRINGID_TRAINERSLIDE:
        stringPtr = gBattleStruct->trainerSlideMsg;
        break;
    default: // load a string from the table
        if (stringID >= STRINGID_COUNT)
        {
            gDisplayedStringBattle[0] = EOS;
            return;
        }
        else
        {
            stringPtr = gBattleStringsTable[stringID];
        }
        break;
    }

    BattleStringExpandPlaceholdersToDisplayedString(stringPtr);
}

u32 BattleStringExpandPlaceholdersToDisplayedString(const u8 *src)
{
#ifndef NDEBUG
    u32 j, strWidth;
    u32 dstID = BattleStringExpandPlaceholders(src, gDisplayedStringBattle, sizeof(gDisplayedStringBattle));
    for (j = 1;; j++)
    {
        strWidth = GetStringLineWidth(0, gDisplayedStringBattle, 0, j, sizeof(gDisplayedStringBattle));
        if (strWidth == 0)
            break;
    }
    return dstID;
#else
    return BattleStringExpandPlaceholders(src, gDisplayedStringBattle, sizeof(gDisplayedStringBattle));
#endif
}

static const u8 *TryGetStatusString(u8 *src)
{
    u32 i;
    u8 status[8];
    u32 chars1, chars2;
    u8 *statusPtr;

    memcpy(status, sText_EmptyStatus, min(ARRAY_COUNT(status), ARRAY_COUNT(sText_EmptyStatus)));

    statusPtr = status;
    for (i = 0; i < ARRAY_COUNT(status); i++)
    {
        if (*src == EOS) break; // one line required to match -g
        *statusPtr = *src;
        src++;
        statusPtr++;
    }

    chars1 = *(u32 *)(&status[0]);
    chars2 = *(u32 *)(&status[4]);

    for (i = 0; i < ARRAY_COUNT(gStatusConditionStringsTable); i++)
    {
        if (chars1 == *(u32 *)(&gStatusConditionStringsTable[i][0][0])
            && chars2 == *(u32 *)(&gStatusConditionStringsTable[i][0][4]))
            return gStatusConditionStringsTable[i][1];
    }
    return NULL;
}

static void GetBattlerNick(u32 battler, u8 *dst)
{
    struct Pokemon *illusionMon = GetIllusionMonPtr(battler);
    struct Pokemon *mon = GetBattlerMon(battler);

    if (illusionMon != NULL)
        mon = illusionMon;
    GetMonData(mon, MON_DATA_NICKNAME, dst);
    StringGet_Nickname(dst);
}

#define HANDLE_NICKNAME_STRING_CASE(battler)                            \
    if (!IsOnPlayerSide(battler))                       \
    {                                                                   \
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)                     \
            toCpy = sText_FoePkmnPrefix;                                \
        else                                                            \
            toCpy = sText_WildPkmnPrefix;                               \
        while (*toCpy != EOS)                                           \
        {                                                               \
            dst[dstID] = *toCpy;                                        \
            dstID++;                                                    \
            toCpy++;                                                    \
        }                                                               \
    }                                                                   \
    GetBattlerNick(battler, text);                                      \
    toCpy = text;

#define HANDLE_NICKNAME_STRING_LOWERCASE(battler)                       \
    if (!IsOnPlayerSide(battler))                       \
    {                                                                   \
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)                     \
            toCpy = sText_FoePkmnPrefixLower;                           \
        else                                                            \
            toCpy = sText_WildPkmnPrefixLower;                          \
        while (*toCpy != EOS)                                           \
        {                                                               \
            dst[dstID] = *toCpy;                                        \
            dstID++;                                                    \
            toCpy++;                                                    \
        }                                                               \
    }                                                                   \
    GetBattlerNick(battler, text);                                      \
    toCpy = text;

static const u8 *BattleStringGetOpponentNameByTrainerId(u16 trainerId, u8 *text, u8 multiplayerId, u8 battler)
{
    const u8 *toCpy = NULL;

    if (gBattleTypeFlags & BATTLE_TYPE_SECRET_BASE)
    {
        u32 i;
        for (i = 0; i < ARRAY_COUNT(gBattleResources->secretBase->trainerName); i++)
            text[i] = gBattleResources->secretBase->trainerName[i];
        text[i] = EOS;
        ConvertInternationalString(text, gBattleResources->secretBase->language);
        toCpy = text;
    }
    else if (trainerId == TRAINER_UNION_ROOM)
    {
        toCpy = gLinkPlayers[multiplayerId ^ BIT_SIDE].name;
    }
    else if (trainerId == TRAINER_LINK_OPPONENT)
    {
        if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            toCpy = gLinkPlayers[GetBattlerMultiplayerId(battler)].name;
        else
            toCpy = gLinkPlayers[GetBattlerMultiplayerId(battler) & BIT_SIDE].name;
    }
    else if (trainerId == TRAINER_FRONTIER_BRAIN)
    {
        CopyFrontierBrainTrainerName(text);
        toCpy = text;
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
    {
        GetFrontierTrainerName(text, trainerId);
        toCpy = text;
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
    {
        GetTrainerHillTrainerName(text, trainerId);
        toCpy = text;
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_EREADER_TRAINER)
    {
        GetEreaderTrainerName(text);
        toCpy = text;
    }
    else
    {
        toCpy = GetTrainerNameFromId(trainerId);
    }

    return toCpy;
}

static const u8 *BattleStringGetOpponentName(u8 *text, u8 multiplayerId, u8 battler)
{
    const u8 *toCpy = NULL;

    switch (GetBattlerPosition(battler))
    {
    case B_POSITION_OPPONENT_LEFT:
        toCpy = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentA, text, multiplayerId, battler);
        break;
    case B_POSITION_OPPONENT_RIGHT:
        if (gBattleTypeFlags & (BATTLE_TYPE_TWO_OPPONENTS | BATTLE_TYPE_MULTI) && !BATTLE_TWO_VS_ONE_OPPONENT)
            toCpy = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentB, text, multiplayerId, battler);
        else
            toCpy = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentA, text, multiplayerId, battler);
        break;
    }

    return toCpy;
}

static const u8 *BattleStringGetPlayerName(u8 *text, u8 battler)
{
    const u8 *toCpy = NULL;

    switch (GetBattlerPosition(battler))
    {
    case B_POSITION_PLAYER_LEFT:
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            toCpy = gLinkPlayers[0].name;
        else
            toCpy = gSaveBlock2Ptr->playerName;
        break;
    case B_POSITION_PLAYER_RIGHT:
        if (((gBattleTypeFlags & BATTLE_TYPE_RECORDED) && !(gBattleTypeFlags & (BATTLE_TYPE_MULTI | BATTLE_TYPE_INGAME_PARTNER)))
            || gTestRunnerEnabled)
        {
            toCpy = gLinkPlayers[0].name;
        }
        else if ((gBattleTypeFlags & BATTLE_TYPE_LINK) && gBattleTypeFlags & (BATTLE_TYPE_RECORDED | BATTLE_TYPE_MULTI))
        {
            toCpy = gLinkPlayers[2].name;
        }
        else if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
        {
            GetFrontierTrainerName(text, gPartnerTrainerId);
            toCpy = text;
        }
        else
        {
            toCpy = gSaveBlock2Ptr->playerName;
        }
        break;
    }

    return toCpy;
}

static const u8 *BattleStringGetTrainerName(u8 *text, u8 multiplayerId, u8 battler)
{
    if (IsOnPlayerSide(battler))
        return BattleStringGetPlayerName(text, battler);
    else
        return BattleStringGetOpponentName(text, multiplayerId, battler);
}

static const u8 *BattleStringGetOpponentClassByTrainerId(u16 trainerId)
{
    const u8 *toCpy;

    if (gBattleTypeFlags & BATTLE_TYPE_SECRET_BASE)
        toCpy = gTrainerClasses[GetSecretBaseTrainerClass()].name;
    else if (trainerId == TRAINER_UNION_ROOM)
        toCpy = gTrainerClasses[GetUnionRoomTrainerClass()].name;
    else if (trainerId == TRAINER_FRONTIER_BRAIN)
        toCpy = gTrainerClasses[GetFrontierBrainTrainerClass()].name;
    else if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
        toCpy = gTrainerClasses[GetFrontierOpponentClass(trainerId)].name;
    else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
        toCpy = gTrainerClasses[GetTrainerHillOpponentClass(trainerId)].name;
    else if (gBattleTypeFlags & BATTLE_TYPE_EREADER_TRAINER)
        toCpy = gTrainerClasses[GetEreaderTrainerClassId()].name;
    else
        toCpy = gTrainerClasses[GetTrainerClassFromId(trainerId)].name;

    return toCpy;
}

// Ensure the defined length for an item name can contain the full defined length of a berry name.
// This ensures that custom Enigma Berry names will fit in the text buffer at the top of BattleStringExpandPlaceholders.
STATIC_ASSERT(BERRY_NAME_LENGTH + ARRAY_COUNT(sText_BerrySuffix) <= ITEM_NAME_LENGTH, BerryNameTooLong);

u32 BattleStringExpandPlaceholders(const u8 *src, u8 *dst, u32 dstSize)
{
    u32 dstID = 0; // if they used dstID, why not use srcID as well?
    const u8 *toCpy = NULL;
    u8 text[max(max(max(32, TRAINER_NAME_LENGTH + 1), POKEMON_NAME_LENGTH + 1), ITEM_NAME_LENGTH)];
    u8 *textStart = &text[0];
    u8 multiplayerId;
    u8 fontId = FONT_NORMAL;

    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
        multiplayerId = gRecordedBattleMultiplayerId;
    else
        multiplayerId = GetMultiplayerId();

    // Clear destination first
    while (dstID < dstSize)
    {
        dst[dstID] = EOS;
        dstID++;
    }

    dstID = 0;
    while (*src != EOS)
    {
        toCpy = NULL;

        if (*src == PLACEHOLDER_BEGIN)
        {
            src++;
            u32 classLength = 0;
            u32 nameLength = 0;
            const u8 *classString;
            const u8 *nameString;
            switch (*src)
            {
            case B_TXT_BUFF1:
                if (gBattleTextBuff1[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff1, gStringVar1);
                    toCpy = gStringVar1;
                }
                else
                {
                    toCpy = TryGetStatusString(gBattleTextBuff1);
                    if (toCpy == NULL)
                        toCpy = gBattleTextBuff1;
                }
                break;
            case B_TXT_BUFF2:
                if (gBattleTextBuff2[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff2, gStringVar2);
                    toCpy = gStringVar2;
                }
                else
                {
                    toCpy = gBattleTextBuff2;
                }
                break;
            case B_TXT_BUFF3:
                if (gBattleTextBuff3[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff3, gStringVar3);
                    toCpy = gStringVar3;
                }
                else
                {
                    toCpy = gBattleTextBuff3;
                }
                break;
            case B_TXT_COPY_VAR_1:
                toCpy = gStringVar1;
                break;
            case B_TXT_COPY_VAR_2:
                toCpy = gStringVar2;
                break;
            case B_TXT_COPY_VAR_3:
                toCpy = gStringVar3;
                break;
            case B_TXT_PLAYER_MON1_NAME: // first player poke name
                GetBattlerNick(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT), text);
                toCpy = text;
                break;
            case B_TXT_OPPONENT_MON1_NAME: // first enemy poke name
                GetBattlerNick(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), text);
                toCpy = text;
                break;
            case B_TXT_PLAYER_MON2_NAME: // second player poke name
                GetBattlerNick(GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT), text);
                toCpy = text;
                break;
            case B_TXT_OPPONENT_MON2_NAME: // second enemy poke name
                GetBattlerNick(GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT), text);
                toCpy = text;
                break;
            case B_TXT_LINK_PLAYER_MON1_NAME: // link first player poke name
                GetBattlerNick(gLinkPlayers[multiplayerId].id, text);
                toCpy = text;
                break;
            case B_TXT_LINK_OPPONENT_MON1_NAME: // link first opponent poke name
                GetBattlerNick(gLinkPlayers[multiplayerId].id ^ 1, text);
                toCpy = text;
                break;
            case B_TXT_LINK_PLAYER_MON2_NAME: // link second player poke name
                GetBattlerNick(gLinkPlayers[multiplayerId].id ^ 2, text);
                toCpy = text;
                break;
            case B_TXT_LINK_OPPONENT_MON2_NAME: // link second opponent poke name
                GetBattlerNick(gLinkPlayers[multiplayerId].id ^ 3, text);
                toCpy = text;
                break;
            case B_TXT_ATK_NAME_WITH_PREFIX_MON1: // Unused, to change into sth else.
                break;
            case B_TXT_ATK_PARTNER_NAME: // attacker partner name
                GetBattlerNick(BATTLE_PARTNER(gBattlerAttacker), text);
                toCpy = text;
                break;
            case B_TXT_ATK_NAME_WITH_PREFIX: // attacker name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattlerAttacker)
                break;
            case B_TXT_DEF_NAME_WITH_PREFIX: // target name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattlerTarget)
                break;
            case B_TXT_DEF_NAME: // target name
                GetBattlerNick(gBattlerTarget, text);
                toCpy = text;
                break;
            case B_TXT_DEF_PARTNER_NAME: // partner target name
                GetBattlerNick(BATTLE_PARTNER(gBattlerTarget), text);
                toCpy = text;
                break;
            case B_TXT_EFF_NAME_WITH_PREFIX: // effect battler name with prefix
                HANDLE_NICKNAME_STRING_CASE(gEffectBattler)
                break;
            case B_TXT_SCR_ACTIVE_NAME_WITH_PREFIX: // scripting active battler name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattleScripting.battler)
                break;
            case B_TXT_CURRENT_MOVE: // current move name
                if (gBattleMsgDataPtr->currentMove >= MOVES_COUNT
                 && !IsZMove(gBattleMsgDataPtr->currentMove)
                 && !IsMaxMove(gBattleMsgDataPtr->currentMove))
                    toCpy = gTypesInfo[gBattleStruct->stringMoveType].generic;
                else
                    toCpy = GetMoveName(gBattleMsgDataPtr->currentMove);
                break;
            case B_TXT_LAST_MOVE: // originally used move name
                if (gBattleMsgDataPtr->originallyUsedMove >= MOVES_COUNT
                 && !IsZMove(gBattleMsgDataPtr->currentMove)
                 && !IsMaxMove(gBattleMsgDataPtr->currentMove))
                    toCpy = gTypesInfo[gBattleStruct->stringMoveType].generic;
                else
                    toCpy = GetMoveName(gBattleMsgDataPtr->originallyUsedMove);
                break;
            case B_TXT_LAST_ITEM: // last used item
                if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
                {
                    if (gLastUsedItem == ITEM_ENIGMA_BERRY_E_READER)
                    {
                        if (!(gBattleTypeFlags & BATTLE_TYPE_MULTI))
                        {
                            if ((gBattleScripting.multiplayerId != 0 && (gPotentialItemEffectBattler & BIT_SIDE))
                                || (gBattleScripting.multiplayerId == 0 && !(gPotentialItemEffectBattler & BIT_SIDE)))
                            {
                                StringCopy(text, gEnigmaBerries[gPotentialItemEffectBattler].name);
                                StringAppend(text, sText_BerrySuffix);
                                toCpy = text;
                            }
                            else
                            {
                                toCpy = sText_EnigmaBerry;
                            }
                        }
                        else
                        {
                            if (gLinkPlayers[gBattleScripting.multiplayerId].id == gPotentialItemEffectBattler)
                            {
                                StringCopy(text, gEnigmaBerries[gPotentialItemEffectBattler].name);
                                StringAppend(text, sText_BerrySuffix);
                                toCpy = text;
                            }
                            else
                            {
                                toCpy = sText_EnigmaBerry;
                            }
                        }
                    }
                    else
                    {
                        CopyItemName(gLastUsedItem, text);
                        toCpy = text;
                    }
                }
                else
                {
                    CopyItemName(gLastUsedItem, text);
                    toCpy = text;
                }
                break;
            case B_TXT_LAST_ABILITY: // last used ability
                toCpy = gAbilitiesInfo[gLastUsedAbility].name;
                break;
            case B_TXT_ATK_ABILITY: // attacker ability
                toCpy = gAbilitiesInfo[sBattlerAbilities[gBattlerAttacker]].name;
                break;
            case B_TXT_DEF_ABILITY: // target ability
                toCpy = gAbilitiesInfo[sBattlerAbilities[gBattlerTarget]].name;
                break;
            case B_TXT_SCR_ACTIVE_ABILITY: // scripting active ability
                toCpy = gAbilitiesInfo[sBattlerAbilities[gBattleScripting.battler]].name;
                break;
            case B_TXT_EFF_ABILITY: // effect battler ability
                toCpy = gAbilitiesInfo[sBattlerAbilities[gEffectBattler]].name;
                break;
            case B_TXT_TRAINER1_CLASS: // trainer class name
                toCpy = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentA);
                break;
            case B_TXT_TRAINER1_NAME: // trainer1 name
                toCpy = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentA, text, multiplayerId, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT));
                break;
            case B_TXT_TRAINER1_NAME_WITH_CLASS: // trainer1 name with trainer class
                toCpy = textStart;
                classString = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentA);
                while (classString[classLength] != EOS)
                {
                    textStart[classLength] = classString[classLength];
                    classLength++;
                }
                textStart[classLength] = CHAR_SPACE;
                textStart += classLength + 1;
                nameString = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentA, textStart, multiplayerId, GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT));
                if (nameString != textStart)
                {
                    while (nameString[nameLength] != EOS)
                    {
                        textStart[nameLength] = nameString[nameLength];
                        nameLength++;
                    }
                    textStart[nameLength] = EOS;
                }
                break;
            case B_TXT_LINK_PLAYER_NAME: // link player name
                toCpy = gLinkPlayers[multiplayerId].name;
                break;
            case B_TXT_LINK_PARTNER_NAME: // link partner name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(BATTLE_PARTNER(gLinkPlayers[multiplayerId].id))].name;
                break;
            case B_TXT_LINK_OPPONENT1_NAME: // link opponent 1 name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(BATTLE_OPPOSITE(gLinkPlayers[multiplayerId].id))].name;
                break;
            case B_TXT_LINK_OPPONENT2_NAME: // link opponent 2 name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(BATTLE_PARTNER(BATTLE_OPPOSITE(gLinkPlayers[multiplayerId].id)))].name;
                break;
            case B_TXT_LINK_SCR_TRAINER_NAME: // link scripting active name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(gBattleScripting.battler)].name;
                break;
            case B_TXT_PLAYER_NAME: // player name
                toCpy = BattleStringGetPlayerName(text, GetBattlerAtPosition(B_POSITION_PLAYER_LEFT));
                break;
            case B_TXT_TRAINER1_LOSE_TEXT: // trainerA lose text
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_WON_TEXT, TRAINER_BATTLE_PARAM.opponentA);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_WON, TRAINER_BATTLE_PARAM.opponentA);
                    toCpy = gStringVar4;
                }
                else
                {
                    toCpy = GetTrainerALoseText();
                }
                break;
            case B_TXT_TRAINER1_WIN_TEXT: // trainerA win text
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_LOST_TEXT, TRAINER_BATTLE_PARAM.opponentA);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_LOST, TRAINER_BATTLE_PARAM.opponentA);
                    toCpy = gStringVar4;
                }
                break;
            case B_TXT_26: // ?
                if (!IsOnPlayerSide(gBattleScripting.battler))
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
                        toCpy = sText_FoePkmnPrefix;
                    else
                        toCpy = sText_WildPkmnPrefix;
                    while (*toCpy != EOS)
                    {
                        dst[dstID] = *toCpy;
                        dstID++;
                        toCpy++;
                    }
                    GetMonData(&gEnemyParty[gBattleStruct->scriptPartyIdx], MON_DATA_NICKNAME, text);
                }
                else
                {
                    GetMonData(&gPlayerParty[gBattleStruct->scriptPartyIdx], MON_DATA_NICKNAME, text);
                }
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_PC_CREATOR_NAME: // lanette pc
                if (FlagGet(FLAG_SYS_PC_LANETTE))
                    toCpy = sText_Lanettes;
                else
                    toCpy = sText_Someones;
                break;
            case B_TXT_ATK_PREFIX2:
                if (IsOnPlayerSide(gBattlerAttacker))
                    toCpy = sText_AllyPkmnPrefix2;
                else
                    toCpy = sText_FoePkmnPrefix3;
                break;
            case B_TXT_DEF_PREFIX2:
                if (IsOnPlayerSide(gBattlerTarget))
                    toCpy = sText_AllyPkmnPrefix2;
                else
                    toCpy = sText_FoePkmnPrefix3;
                break;
            case B_TXT_ATK_PREFIX1:
                if (IsOnPlayerSide(gBattlerAttacker))
                    toCpy = sText_AllyPkmnPrefix;
                else
                    toCpy = sText_FoePkmnPrefix2;
                break;
            case B_TXT_DEF_PREFIX1:
                if (IsOnPlayerSide(gBattlerTarget))
                    toCpy = sText_AllyPkmnPrefix;
                else
                    toCpy = sText_FoePkmnPrefix2;
                break;
            case B_TXT_ATK_PREFIX3:
                if (IsOnPlayerSide(gBattlerAttacker))
                    toCpy = sText_AllyPkmnPrefix3;
                else
                    toCpy = sText_FoePkmnPrefix4;
                break;
            case B_TXT_DEF_PREFIX3:
                if (IsOnPlayerSide(gBattlerTarget))
                    toCpy = sText_AllyPkmnPrefix3;
                else
                    toCpy = sText_FoePkmnPrefix4;
                break;
            case B_TXT_TRAINER2_CLASS:
                toCpy = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentB);
                break;
            case B_TXT_TRAINER2_NAME:
                toCpy = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentB, text, multiplayerId, GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT));
                break;
            case B_TXT_TRAINER2_NAME_WITH_CLASS:
                toCpy = textStart;
                classString = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentB);
                while (classString[classLength] != EOS)
                {
                    textStart[classLength] = classString[classLength];
                    classLength++;
                }
                textStart[classLength] = CHAR_SPACE;
                textStart += classLength + 1;
                nameString = BattleStringGetOpponentNameByTrainerId(TRAINER_BATTLE_PARAM.opponentB, textStart, multiplayerId, GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT));
                if (nameString != textStart)
                {
                    while (nameString[nameLength] != EOS)
                    {
                        textStart[nameLength] = nameString[nameLength];
                        nameLength++;
                    }
                    textStart[nameLength] = EOS;
                }
                break;
            case B_TXT_TRAINER2_LOSE_TEXT:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_WON_TEXT, TRAINER_BATTLE_PARAM.opponentB);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_WON, TRAINER_BATTLE_PARAM.opponentB);
                    toCpy = gStringVar4;
                }
                else
                {
                    toCpy = GetTrainerBLoseText();
                }
                break;
            case B_TXT_TRAINER2_WIN_TEXT:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_LOST_TEXT, TRAINER_BATTLE_PARAM.opponentB);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_LOST, TRAINER_BATTLE_PARAM.opponentB);
                    toCpy = gStringVar4;
                }
                break;
            case B_TXT_PARTNER_CLASS:
                toCpy = gTrainerClasses[GetFrontierOpponentClass(gPartnerTrainerId)].name;
                break;
            case B_TXT_PARTNER_NAME:
                toCpy = BattleStringGetPlayerName(text, GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT));
                break;
            case B_TXT_PARTNER_NAME_WITH_CLASS:
                toCpy = textStart;
                classString = gTrainerClasses[GetFrontierOpponentClass(gPartnerTrainerId)].name;
                while (classString[classLength] != EOS)
                {
                    textStart[classLength] = classString[classLength];
                    classLength++;
                }
                textStart[classLength] = CHAR_SPACE;
                textStart += classLength + 1;
                nameString = BattleStringGetPlayerName(textStart, GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT));
                if (nameString != textStart)
                {
                    while (nameString[nameLength] != EOS)
                    {
                        textStart[nameLength] = nameString[nameLength];
                        nameLength++;
                    }
                    textStart[nameLength] = EOS;
                }
                break;
            case B_TXT_ATK_TRAINER_NAME:
                toCpy = BattleStringGetTrainerName(text, multiplayerId, gBattlerAttacker);
                break;
            case B_TXT_ATK_TRAINER_CLASS:
                switch (GetBattlerPosition(gBattlerAttacker))
                {
                case B_POSITION_PLAYER_RIGHT:
                    if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
                        toCpy = gTrainerClasses[GetFrontierOpponentClass(gPartnerTrainerId)].name;
                    break;
                case B_POSITION_OPPONENT_LEFT:
                    toCpy = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentA);
                    break;
                case B_POSITION_OPPONENT_RIGHT:
                    if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS && !BATTLE_TWO_VS_ONE_OPPONENT)
                        toCpy = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentB);
                    else
                        toCpy = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentA);
                    break;
                }
                break;
            case B_TXT_ATK_TRAINER_NAME_WITH_CLASS:
                toCpy = textStart;
                if (GetBattlerPosition(gBattlerAttacker) == B_POSITION_PLAYER_LEFT)
                {
                    textStart = StringCopy(textStart, BattleStringGetTrainerName(textStart, multiplayerId, gBattlerAttacker));
                }
                else
                {
                    classString = NULL;
                    switch (GetBattlerPosition(gBattlerAttacker))
                    {
                    case B_POSITION_PLAYER_RIGHT:
                        if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
                            classString = gTrainerClasses[GetFrontierOpponentClass(gPartnerTrainerId)].name;
                        break;
                    case B_POSITION_OPPONENT_LEFT:
                        classString = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentA);
                        break;
                    case B_POSITION_OPPONENT_RIGHT:
                        if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS && !BATTLE_TWO_VS_ONE_OPPONENT)
                            classString = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentB);
                        else
                            classString = BattleStringGetOpponentClassByTrainerId(TRAINER_BATTLE_PARAM.opponentA);
                        break;
                    }
                    classLength = 0;
                    nameLength = 0;
                    while (classString[classLength] != EOS)
                    {
                        textStart[classLength] = classString[classLength];
                        classLength++;
                    }
                    textStart[classLength] = CHAR_SPACE;
                    textStart += 1 + classLength;
                    nameString = BattleStringGetTrainerName(textStart, multiplayerId, gBattlerAttacker);
                    if (nameString != textStart)
                    {
                        while (nameString[nameLength] != EOS)
                        {
                            textStart[nameLength] = nameString[nameLength];
                            nameLength++;
                        }
                        textStart[nameLength] = EOS;
                    }
                }
                break;
            case B_TXT_ATK_TEAM1:
                if (IsOnPlayerSide(gBattlerAttacker))
                    toCpy = sText_Your1;
                else
                    toCpy = sText_Opposing1;
                break;
            case B_TXT_ATK_TEAM2:
                if (IsOnPlayerSide(gBattlerAttacker))
                    toCpy = sText_Your2;
                else
                    toCpy = sText_Opposing2;
                break;
            case B_TXT_DEF_TEAM1:
                if (IsOnPlayerSide(gBattlerTarget))
                    toCpy = sText_Your1;
                else
                    toCpy = sText_Opposing1;
                break;
            case B_TXT_DEF_TEAM2:
                if (IsOnPlayerSide(gBattlerTarget))
                    toCpy = sText_Your2;
                else
                    toCpy = sText_Opposing2;
                break;
            case B_TXT_EFF_TEAM1:
                if (IsOnPlayerSide(gEffectBattler))
                    toCpy = sText_Your1;
                else
                    toCpy = sText_Opposing1;
                break;
            case B_TXT_EFF_TEAM2:
                if (IsOnPlayerSide(gEffectBattler))
                    toCpy = sText_Your2;
                else
                    toCpy = sText_Opposing2;
                break;
            case B_TXT_ATK_NAME_WITH_PREFIX2:
                HANDLE_NICKNAME_STRING_LOWERCASE(gBattlerAttacker)
                break;
            case B_TXT_DEF_NAME_WITH_PREFIX2:
                HANDLE_NICKNAME_STRING_LOWERCASE(gBattlerTarget)
                break;
            case B_TXT_EFF_NAME_WITH_PREFIX2:
                HANDLE_NICKNAME_STRING_LOWERCASE(gEffectBattler)
                break;
            case B_TXT_SCR_ACTIVE_NAME_WITH_PREFIX2:
                HANDLE_NICKNAME_STRING_LOWERCASE(gBattleScripting.battler)
                break;
            }

            if (toCpy != NULL)
            {
                while (*toCpy != EOS)
                {
                    if (*toCpy == CHAR_SPACE)
                        dst[dstID] = CHAR_NBSP;
                    else
                        dst[dstID] = *toCpy;
                    dstID++;
                    toCpy++;
                }
            }

            if (*src == B_TXT_TRAINER1_LOSE_TEXT || *src == B_TXT_TRAINER2_LOSE_TEXT
                || *src == B_TXT_TRAINER1_WIN_TEXT || *src == B_TXT_TRAINER2_WIN_TEXT)
            {
                dst[dstID] = EXT_CTRL_CODE_BEGIN;
                dstID++;
                dst[dstID] = EXT_CTRL_CODE_PAUSE_UNTIL_PRESS;
                dstID++;
            }
        }
        else
        {
            dst[dstID] = *src;
            dstID++;
        }
        src++;
    }

    dst[dstID] = *src;
    dstID++;

    BreakStringAutomatic(dst, BATTLE_MSG_MAX_WIDTH, BATTLE_MSG_MAX_LINES, fontId, SHOW_SCROLL_PROMPT);

    return dstID;
}

static void IllusionNickHack(u32 battler, u32 partyId, u8 *dst)
{
    u32 id = PARTY_SIZE;
    // we know it's gEnemyParty
    struct Pokemon *mon = &gEnemyParty[partyId], *partnerMon;

    if (GetMonAbility(mon) == ABILITY_ILLUSION)
    {
        if (IsBattlerAlive(BATTLE_PARTNER(battler)))
            partnerMon = GetBattlerMon(BATTLE_PARTNER(battler));
        else
            partnerMon = mon;

        id = GetIllusionMonPartyId(gEnemyParty, mon, partnerMon, battler);
    }

    if (id != PARTY_SIZE)
        GetMonData(&gEnemyParty[id], MON_DATA_NICKNAME, dst);
    else
        GetMonData(mon, MON_DATA_NICKNAME, dst);
}

void ExpandBattleTextBuffPlaceholders(const u8 *src, u8 *dst)
{
    u32 srcID = 1;
    u32 value = 0;
    u8 nickname[POKEMON_NAME_LENGTH + 1];
    u16 hword;

    *dst = EOS;
    while (src[srcID] != B_BUFF_EOS)
    {
        switch (src[srcID])
        {
        case B_BUFF_STRING: // battle string
            hword = T1_READ_16(&src[srcID + 1]);
            StringAppend(dst, gBattleStringsTable[hword]);
            srcID += 3;
            break;
        case B_BUFF_NUMBER: // int to string
            switch (src[srcID + 1])
            {
            case 1:
                value = src[srcID + 3];
                break;
            case 2:
                value = T1_READ_16(&src[srcID + 3]);
                break;
            case 4:
                value = T1_READ_32(&src[srcID + 3]);
                break;
            }
            ConvertIntToDecimalStringN(dst, value, STR_CONV_MODE_LEFT_ALIGN, src[srcID + 2]);
            srcID += src[srcID + 1] + 3;
            break;
        case B_BUFF_MOVE: // move name
            StringAppend(dst, GetMoveName(T1_READ_16(&src[srcID + 1])));
            srcID += 3;
            break;
        case B_BUFF_TYPE: // type name
            StringAppend(dst, gTypesInfo[src[srcID + 1]].name);
            srcID += 2;
            break;
        case B_BUFF_MON_NICK_WITH_PREFIX: // poke nick with prefix
        case B_BUFF_MON_NICK_WITH_PREFIX_LOWER: // poke nick with lowercase prefix
            if (IsOnPlayerSide(src[srcID + 1]))
            {
                GetMonData(&gPlayerParty[src[srcID + 2]], MON_DATA_NICKNAME, nickname);
            }
            else
            {
                if (src[srcID] == B_BUFF_MON_NICK_WITH_PREFIX_LOWER)
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
                        StringAppend(dst, sText_FoePkmnPrefixLower);
                    else
                        StringAppend(dst, sText_WildPkmnPrefixLower);
                }
                else
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
                        StringAppend(dst, sText_FoePkmnPrefix);
                    else
                        StringAppend(dst, sText_WildPkmnPrefix);
                }

                GetMonData(&gEnemyParty[src[srcID + 2]], MON_DATA_NICKNAME, nickname);
            }
            StringGet_Nickname(nickname);
            StringAppend(dst, nickname);
            srcID += 3;
            break;
        case B_BUFF_STAT: // stats
            StringAppend(dst, gStatNamesTable[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_SPECIES: // species name
            StringCopy(dst, GetSpeciesName(T1_READ_16(&src[srcID + 1])));
            srcID += 3;
            break;
        case B_BUFF_MON_NICK: // poke nick without prefix
            if (src[srcID + 2] == gBattlerPartyIndexes[src[srcID + 1]])
            {
                GetBattlerNick(src[srcID + 1], dst);
            }
            else if (gBattleScripting.illusionNickHack) // for STRINGID_ENEMYABOUTTOSWITCHPKMN
            {
                gBattleScripting.illusionNickHack = 0;
                IllusionNickHack(src[srcID + 1], src[srcID + 2], dst);
                StringGet_Nickname(dst);
            }
            else
            {
                if (IsOnPlayerSide(src[srcID + 1]))
                    GetMonData(&gPlayerParty[src[srcID + 2]], MON_DATA_NICKNAME, dst);
                else
                    GetMonData(&gEnemyParty[src[srcID + 2]], MON_DATA_NICKNAME, dst);
                StringGet_Nickname(dst);
            }
            srcID += 3;
            break;
        case B_BUFF_NEGATIVE_FLAVOR: // flavor table
            StringAppend(dst, gPokeblockWasTooXStringTable[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_ABILITY: // ability names
            StringAppend(dst, gAbilitiesInfo[T1_READ_16(&src[srcID + 1])].name);
            srcID += 3;
            break;
        case B_BUFF_ITEM: // item name
            hword = T1_READ_16(&src[srcID + 1]);
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            {
                if (hword == ITEM_ENIGMA_BERRY_E_READER)
                {
                    if (gLinkPlayers[gBattleScripting.multiplayerId].id == gPotentialItemEffectBattler)
                    {
                        StringCopy(dst, gEnigmaBerries[gPotentialItemEffectBattler].name);
                        StringAppend(dst, sText_BerrySuffix);
                    }
                    else
                    {
                        StringAppend(dst, sText_EnigmaBerry);
                    }
                }
                else
                {
                    CopyItemName(hword, dst);
                }
            }
            else
            {
                CopyItemName(hword, dst);
            }
            srcID += 3;
            break;
        }
    }
}

// Loads one of two text strings into the provided buffer. This is functionally
// unused, since the value loaded into the buffer is not read; it loaded one of
// two particles (either "?" or "?") which works in tandem with ChooseTypeOfMoveUsedString
// below to effect changes in the meaning of the line.
static void UNUSED ChooseMoveUsedParticle(u8 *textBuff)
{
    s32 counter = 0;
    u32 i = 0;

    while (counter != MAX_MON_MOVES)
    {
        if (sGrammarMoveUsedTable[i] == 0)
            counter++;
        if (sGrammarMoveUsedTable[i++] == gBattleMsgDataPtr->currentMove)
            break;
    }

    if (counter >= 0)
    {
        if (counter <= 2)
            StringCopy(textBuff, sText_SpaceIs); // is
        else if (counter <= MAX_MON_MOVES)
            StringCopy(textBuff, sText_ApostropheS); // 's
    }
}

// Appends "!" to the text buffer `dst`. In the original Japanese this looked
// into the table of moves at sGrammarMoveUsedTable and varied the line accordingly.
//
// sText_ExclamationMark was a plain "!", used for any attack not on the list.
// It resulted in the translation "<NAME>'s <ATTACK>!".
//
// sText_ExclamationMark2 was "? ????!". This resulted in the translation
// "<NAME> used <ATTACK>!", which was used for all attacks in English.
//
// sText_ExclamationMark3 was "??!". This was used for those moves whose
// names were verbs, such as Recover, and resulted in translations like "<NAME>
// recovered itself!".
//
// sText_ExclamationMark4 was "? ??!" This resulted in a translation of
// "<NAME> did an <ATTACK>!".
//
// sText_ExclamationMark5 was " ????!" This resulted in a translation of
// "<NAME>'s <ATTACK> attack!".
static void UNUSED ChooseTypeOfMoveUsedString(u8 *dst)
{
    s32 counter = 0;
    s32 i = 0;

    while (*dst != EOS)
        dst++;

    while (counter != MAX_MON_MOVES)
    {
        if (sGrammarMoveUsedTable[i] == MOVE_NONE)
            counter++;
        if (sGrammarMoveUsedTable[i++] == gBattleMsgDataPtr->currentMove)
            break;
    }

    switch (counter)
    {
    case 0:
        StringCopy(dst, sText_ExclamationMark);
        break;
    case 1:
        StringCopy(dst, sText_ExclamationMark2);
        break;
    case 2:
        StringCopy(dst, sText_ExclamationMark3);
        break;
    case 3:
        StringCopy(dst, sText_ExclamationMark4);
        break;
    case 4:
        StringCopy(dst, sText_ExclamationMark5);
        break;
    }
}

void BattlePutTextOnWindow(const u8 *text, u8 windowId)
{
    const struct BattleWindowText *textInfo = sBattleTextOnWindowsInfo[gBattleScripting.windowsType];
    bool32 copyToVram;
    struct TextPrinterTemplate printerTemplate;
    u8 speed;

    if (windowId & B_WIN_COPYTOVRAM)
    {
        windowId &= ~B_WIN_COPYTOVRAM;
        copyToVram = FALSE;
    }
    else
    {
        FillWindowPixelBuffer(windowId, textInfo[windowId].fillValue);
        copyToVram = TRUE;
    }

    printerTemplate.currentChar = text;
    printerTemplate.windowId = windowId;
    printerTemplate.fontId = textInfo[windowId].fontId;
    printerTemplate.x = textInfo[windowId].x;
    printerTemplate.y = textInfo[windowId].y;
    printerTemplate.currentX = printerTemplate.x;
    printerTemplate.currentY = printerTemplate.y;
    printerTemplate.letterSpacing = textInfo[windowId].letterSpacing;
    printerTemplate.lineSpacing = textInfo[windowId].lineSpacing;
    printerTemplate.unk = 0;
    printerTemplate.fgColor = textInfo[windowId].fgColor;
    printerTemplate.bgColor = textInfo[windowId].bgColor;
    printerTemplate.shadowColor = textInfo[windowId].shadowColor;

    if (B_WIN_MOVE_NAME_1 <= windowId && windowId <= B_WIN_MOVE_NAME_4)
    {
        // We cannot check the actual width of the window because
        // B_WIN_MOVE_NAME_1 and B_WIN_MOVE_NAME_3 are 16 wide for
        // Z-move details.
        if (gBattleStruct->zmove.viewing && windowId == B_WIN_MOVE_NAME_1)
            printerTemplate.fontId = GetFontIdToFit(text, printerTemplate.fontId, printerTemplate.letterSpacing, 16 * TILE_WIDTH);
        else
            printerTemplate.fontId = GetFontIdToFit(text, printerTemplate.fontId, printerTemplate.letterSpacing, 8 * TILE_WIDTH);
    }

    if (printerTemplate.x == 0xFF)
    {
        u32 width = GetBattleWindowTemplatePixelWidth(gBattleScripting.windowsType, windowId);
        s32 alignX = GetStringCenterAlignXOffsetWithLetterSpacing(printerTemplate.fontId, printerTemplate.currentChar, width, printerTemplate.letterSpacing);
        printerTemplate.x = printerTemplate.currentX = alignX;
    }

    if (windowId == ARENA_WIN_JUDGMENT_TEXT)
        gTextFlags.useAlternateDownArrow = FALSE;
    else
        gTextFlags.useAlternateDownArrow = TRUE;

    if ((gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED)) || gTestRunnerEnabled)
        gTextFlags.autoScroll = TRUE;
    else
        gTextFlags.autoScroll = FALSE;

    if (windowId == B_WIN_MSG || windowId == ARENA_WIN_JUDGMENT_TEXT)
    {
        if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            speed = 1;
        else if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            speed = sRecordedBattleTextSpeeds[GetTextSpeedInRecordedBattle()];
        else
            speed = GetPlayerTextSpeedDelay();

        gTextFlags.canABSpeedUpPrint = 1;
    }
    else
    {
        speed = textInfo[windowId].speed;
        gTextFlags.canABSpeedUpPrint = 0;
    }

    AddTextPrinter(&printerTemplate, speed, NULL);

    if (copyToVram)
    {
        PutWindowTilemap(windowId);
        CopyWindowToVram(windowId, COPYWIN_FULL);
    }
}

void SetPpNumbersPaletteInMoveSelection(u32 battler)
{
    struct ChooseMoveStruct *chooseMoveStruct = (struct ChooseMoveStruct *)(&gBattleResources->bufferA[battler][4]);
    const u16 *palPtr = gPPTextPalette;
    u8 var;

    if (!gBattleStruct->zmove.viewing)
        var = GetCurrentPpToMaxPpState(chooseMoveStruct->currentPp[gMoveSelectionCursor[battler]],
                         chooseMoveStruct->maxPp[gMoveSelectionCursor[battler]]);
    else
        var = 3;

    gPlttBufferUnfaded[BG_PLTT_ID(5) + 12] = palPtr[(var * 2) + 0];
    gPlttBufferUnfaded[BG_PLTT_ID(5) + 11] = palPtr[(var * 2) + 1];

    CpuCopy16(&gPlttBufferUnfaded[BG_PLTT_ID(5) + 12], &gPlttBufferFaded[BG_PLTT_ID(5) + 12], PLTT_SIZEOF(1));
    CpuCopy16(&gPlttBufferUnfaded[BG_PLTT_ID(5) + 11], &gPlttBufferFaded[BG_PLTT_ID(5) + 11], PLTT_SIZEOF(1));
}

u8 GetCurrentPpToMaxPpState(u8 currentPp, u8 maxPp)
{
    if (maxPp == currentPp)
    {
        return 3;
    }
    else if (maxPp <= 2)
    {
        if (currentPp > 1)
            return 3;
        else
            return 2 - currentPp;
    }
    else if (maxPp <= 7)
    {
        if (currentPp > 2)
            return 3;
        else
            return 2 - currentPp;
    }
    else
    {
        if (currentPp == 0)
            return 2;
        if (currentPp <= maxPp / 4)
            return 1;
        if (currentPp > maxPp / 2)
            return 3;
    }

    return 0;
}
