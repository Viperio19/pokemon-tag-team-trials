#include "global.h"
#include "clock.h"
#include "new_game.h"
#include "random.h"
#include "clock.h"
#include "pokemon.h"
#include "roamer.h"
#include "pokemon_size_record.h"
#include "script.h"
#include "lottery_corner.h"
#include "play_time.h"
#include "mauville_old_man.h"
#include "match_call.h"
#include "lilycove_lady.h"
#include "load_save.h"
#include "pokeblock.h"
#include "dewford_trend.h"
#include "berry.h"
#include "rtc.h"
#include "easy_chat.h"
#include "event_data.h"
#include "money.h"
#include "trainer_hill.h"
#include "trainer_tower.h"
#include "tv.h"
#include "coins.h"
#include "text.h"
#include "overworld.h"
#include "mail.h"
#include "battle_records.h"
#include "item.h"
#include "pokedex.h"
#include "apprentice.h"
#include "frontier_util.h"
#include "pokedex.h"
#include "save.h"
#include "link_rfu.h"
#include "main.h"
#include "contest.h"
#include "item_menu.h"
#include "pokemon_storage_system.h"
#include "pokemon_jump.h"
#include "decoration_inventory.h"
#include "secret_base.h"
#include "string_util.h"
#include "player_pc.h"
#include "field_specials.h"
#include "berry_powder.h"
#include "mystery_gift.h"
#include "union_room_chat.h"
#include "constants/map_groups.h"
#include "constants/items.h"
#include "difficulty.h"
#include "follower_npc.h"
#include "field_control_avatar.h"
#include "script_pokemon_util.h"

extern const u8 EventScript_ResetAllMapFlags[];
extern const u8 EventScript_ResetAllMapFlagsFrlg[];
extern const u8 EventScript_ResetAllMapFlagsTARC[];

static void ClearFrontierRecord(void);
static void WarpToFirstMap(void);
static void ResetMiniGamesRecords(void);
static void ResetItemFlags(void);
static void ResetDexNav(void);
static void InitTARCData(void);
static void InitTagTeamTrailsMultiplayerData(void);

EWRAM_DATA bool8 gDifferentSaveFile = FALSE;
EWRAM_DATA bool8 gEnableContestDebugging = FALSE;

static const struct ContestWinner sContestWinnerPicDummy =
{
    .monName = _(""),
    .trainerName = _("")
};

void SetTrainerId(u32 trainerId, u8 *dst)
{
    dst[0] = trainerId;
    dst[1] = trainerId >> 8;
    dst[2] = trainerId >> 16;
    dst[3] = trainerId >> 24;
}

u32 GetTrainerId(u8 *trainerId)
{
    return (trainerId[3] << 24) | (trainerId[2] << 16) | (trainerId[1] << 8) | (trainerId[0]);
}

void CopyTrainerId(u8 *dst, u8 *src)
{
    s32 i;
    for (i = 0; i < TRAINER_ID_LENGTH; i++)
        dst[i] = src[i];
}

static void InitPlayerTrainerIds()
{
    u32 trainerId = (Random() << 16) | GetGeneratedTrainerIdLower();
    u32 trainerIdFRLG = (GetGeneratedTrainerIdLower() << 16) | Random();
    SetTrainerId(trainerId, gSaveBlock2Ptr->playerTrainerId);
    SetTrainerId(trainerIdFRLG, gSaveBlock2Ptr->player2TrainerId);
}

// L=A isnt set here for some reason.
static void SetDefaultOptions(void)
{
    gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_FAST;
    gSaveBlock2Ptr->optionsWindowFrameType = 0;
    gSaveBlock2Ptr->optionsSound = OPTIONS_SOUND_STEREO;
    gSaveBlock2Ptr->optionsBattleStyle = OPTIONS_BATTLE_STYLE_SHIFT;
    gSaveBlock2Ptr->optionsBattleSceneOff = FALSE;
    gSaveBlock2Ptr->regionMapZoom = FALSE;
}

static void ClearPokedexFlags(void)
{
    memset(&gSaveBlock1Ptr->dexCaught, 0, sizeof(gSaveBlock1Ptr->dexCaught));
    memset(&gSaveBlock1Ptr->dexSeen, 0, sizeof(gSaveBlock1Ptr->dexSeen));
    memset(&gSaveBlock1Ptr->dexCaught2, 0, sizeof(gSaveBlock1Ptr->dexCaught2));
    memset(&gSaveBlock1Ptr->dexSeen2, 0, sizeof(gSaveBlock1Ptr->dexSeen2));
}

void ClearAllContestWinnerPics(void)
{
    s32 i;

    ClearContestWinnerPicsInContestHall();

    // Clear Museum paintings
    for (i = MUSEUM_CONTEST_WINNERS_START; i < NUM_CONTEST_WINNERS; i++)
        gSaveBlock1Ptr->contestWinners[i] = sContestWinnerPicDummy;
}

static void ClearFrontierRecord(void)
{
    CpuFill32(0, &gSaveBlock2Ptr->frontier, sizeof(gSaveBlock2Ptr->frontier));

    gSaveBlock2Ptr->frontier.opponentNames[0][0] = EOS;
    gSaveBlock2Ptr->frontier.opponentNames[1][0] = EOS;
}

static void WarpToFirstMap(void)
{
    SetPlayer2Pos(MAP_GROUP(MAP_VOLCANION_CAVE_1F), MAP_NUM(MAP_VOLCANION_CAVE_1F), 19, 22, DIR_NORTH, 3);
    SetWarpDestination(MAP_GROUP(MAP_VOLCANION_CAVE_1F), MAP_NUM(MAP_VOLCANION_CAVE_1F), WARP_ID_NONE, 19, 22);
    WarpIntoMap();
}

void Sav2_ClearSetDefault(void)
{
    ClearSav2();
    SetDefaultOptions();
}

void ResetMenuAndMonGlobals(void)
{
    gDifferentSaveFile = FALSE;
    ResetPokedexScrollPositions();
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetBagScrollPositions();
    ResetPokeblockScrollPositions();
}

void NewGameInitData(void)
{
#if IS_FRLG
    u8 rivalName[PLAYER_NAME_LENGTH + 1];
#endif
    if (gSaveFileStatus == SAVE_STATUS_EMPTY || gSaveFileStatus == SAVE_STATUS_CORRUPT)
        RtcReset();

#if IS_FRLG
    StringCopy(rivalName, gSaveBlock1Ptr->rivalName);
#endif
    gDifferentSaveFile = TRUE;
    gSaveBlock2Ptr->encryptionKey = 0;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetPokedex();
    ClearFrontierRecord();
    ClearSav1();
    ClearSav3();
    ClearAllMail();
    gSaveBlock2Ptr->specialSaveWarpFlags = 0;
    gSaveBlock2Ptr->gcnLinkFlags = 0;
    InitPlayerTrainerIds();
    PlayTimeCounter_Reset();
    ClearPokedexFlags();
    InitEventData();
    ClearTVShowData();
    ResetGabbyAndTy();
    ClearSecretBases();
    ClearBerryTrees();
    SetMoney(&gSaveBlock1Ptr->money, 3000);
    gSaveBlock1Ptr->money2 = 5000;
    SetCoins(0);
    ResetLinkContestBoolean();
    ResetGameStats();
    ClearAllContestWinnerPics();
    ClearPlayerLinkBattleRecords();
    InitSeedotSizeRecord();
    InitLotadSizeRecord();
    gPartiesCount[B_TRAINER_PLAYER] = 0;
    ZeroPlayerPartyMons();
    ResetPokemonStorageSystem();
    DeactivateAllRoamers();
    gSaveBlock1Ptr->registeredItem = ITEM_NONE;
    ClearBag();
    NewGameInitPCItems();
    ClearPokeblocks();
    ClearDecorationInventories();
    InitEasyChatPhrases();
    SetMauvilleOldMan();
    InitDewfordTrend();
    ResetFanClub();
    ResetLotteryCorner();
    UpdateDailySeed();
    if (IS_MULTIPLAYER)
        InitTagTeamTrailsMultiplayerData(); 
    else
        InitTARCData();
    WarpToFirstMap();
    RunScriptImmediately(EventScript_ResetAllMapFlagsTARC);
#if IS_FRLG
        StringCopy(gSaveBlock1Ptr->rivalName, rivalName);
#endif
    ResetMiniGamesRecords();
    InitUnionRoomChatRegisteredTexts();
    InitLilycoveLady();
    ResetAllApprenticeData();
    ClearRankingHallRecords();
    InitMatchCallCounters();
    ClearMysteryGift();
    WipeTrainerNameRecords();
    ResetTrainerHillResults();
    ResetTrainerTowerResults();
    ResetContestLinkResults();
    SetCurrentDifficultyLevel(DIFFICULTY_NORMAL);
    ResetItemFlags();
    ResetDexNav();
    ClearFollowerNPCData();
}

static void ResetMiniGamesRecords(void)
{
    CpuFill16(0, &gSaveBlock2Ptr->berryCrush, sizeof(struct BerryCrush));
    SetBerryPowder(&gSaveBlock2Ptr->berryCrush.berryPowderAmount, 0);
    ResetPokemonJumpRecords();
    CpuFill16(0, &gSaveBlock2Ptr->berryPick, sizeof(struct BerryPickingResults));
}

static void ResetItemFlags(void)
{
#if OW_SHOW_ITEM_DESCRIPTIONS == OW_ITEM_DESCRIPTIONS_FIRST_TIME
    memset(&gSaveBlock3Ptr->itemFlags, 0, sizeof(gSaveBlock3Ptr->itemFlags));
#endif
}

static void ResetDexNav(void)
{
#if USE_DEXNAV_SEARCH_LEVELS == TRUE
    memset(gSaveBlock3Ptr->dexNavSearchLevels, 0, sizeof(gSaveBlock3Ptr->dexNavSearchLevels));
#endif
    gSaveBlock3Ptr->dexNavChain = 0;
}

static void InitTagTeamTrailsMultiplayerData()
{
    FlagSet(FLAG_SYS_POKEDEX_GET);
    FlagSet(FLAG_SYS_POKEMON_GET);
    FlagSet(FLAG_SYS_B_DASH);
    FlagSet(FLAG_OVERWRITE_MET_LOCATION_NEW_GAME);
    HandleSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_POOCHYENA), FLAG_SET_CAUGHT_BOTH, 0);

    if (IS_PLAYER_ONE)
    {
        FlagSet(FLAG_BADGE05_GET);
        FlagSet(FLAG_BADGE08_GET);
        AddBagItem(ITEM_GREAT_BALL, 10);
        ScriptGiveMon(SPECIES_CARVANHA, 20, ITEM_NONE);
    }
    else
    {
        FlagSet(FLAG_BADGE02_GET);
        FlagSet(FLAG_BADGE03_GET);
        AddBagItem(ITEM_POKE_BALL, 10);
        ScriptGiveMon(SPECIES_NUMEL, 20, ITEM_NONE);
    }

    FlagClear(FLAG_OVERWRITE_MET_LOCATION_NEW_GAME);
}

static void InitTARCData(void)
{
    FlagSet(FLAG_SYS_POKEDEX_GET);
    FlagSet(FLAG_SYS_POKEMON_GET);
    FlagSet(FLAG_SYS_B_DASH);

    FlagSet(FLAG_BADGE02_GET);
    FlagSet(FLAG_BADGE03_GET);
    FlagSet(FLAG_P2_BADGE05_GET);
    FlagSet(FLAG_P2_BADGE08_GET);

    FlagSet(FLAG_OVERWRITE_MET_LOCATION_NEW_GAME);

    HandleSetPokedexFlag(SpeciesToNationalPokedexNum(SPECIES_POOCHYENA), FLAG_SET_CAUGHT_BOTH, 0);

    AddBagItem(ITEM_POKE_BALL, 10);
    ScriptGiveMon(SPECIES_NUMEL, 20, ITEM_NONE);
    SwitchParties();
    SwitchTrainerData();
    SWAP(gSaveBlock1Ptr->bag, gSaveBlock1Ptr->bag2, gLoadedSaveData.bag);

    gSaveBlock2Ptr->player ^= 1;

    AddBagItem(ITEM_GREAT_BALL, 10);
    ScriptGiveMon(SPECIES_CARVANHA, 20, ITEM_NONE);
    SwitchParties();
    SwitchTrainerData();
    SWAP(gSaveBlock1Ptr->bag, gSaveBlock1Ptr->bag2, gLoadedSaveData.bag);

    gSaveBlock2Ptr->player ^= 1;

    FlagClear(FLAG_OVERWRITE_MET_LOCATION_NEW_GAME);

    struct BoulderPos *pos;
    
    for (u32 i = 0; i < 3; i++)
    {
        for (u32 j = 0; j < 32; j++)
        {
            pos = &gSaveBlock1Ptr->boulderPos[i][j];
            
            pos->x = 0;
            pos->y = 0;
        }
    }
}
