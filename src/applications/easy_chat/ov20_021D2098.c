#include "applications/easy_chat/ov20_021D2098.h"

#include <nitro.h>
#include <string.h>

#include "applications/easy_chat/categories.h"
#include "applications/easy_chat/confirm_cancel_menu.h"
#include "applications/easy_chat/interface.h"
#include "applications/easy_chat/main.h"
#include "applications/easy_chat/ov20_021D40E8.h"
#include "applications/easy_chat/ov20_021D4728.h"
#include "applications/easy_chat/struct_ov20_021D4210_decl.h"
#include "applications/easy_chat/struct_ov20_021D4AD4_decl.h"

#include "bg_window.h"
#include "easy_chat_word_list.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "narc.h"
#include "render_oam.h"
#include "screen_fade.h"
#include "sprite.h"
#include "sprite_util.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "system.h"

typedef struct UnkStruct_ov20_021D2128_t {
    SysTask *unk_00;
    SysTask *unk_04;
    SysTask *unk_08[4];
    const EasyChatApp *app;
    const EasyChatWordList *wordList;
    BgConfig *bgConfig;
    SpriteList *unk_24;
    G2dRenderer unk_28;
    NNSG2dImageProxy unk_1B4[2];
    NNSG2dImagePaletteProxy unk_1FC[2];
    NNSG2dCellDataBank *unk_224[2];
    NNSG2dCellAnimBankData *unk_22C[2];
    void *unk_234[2];
    void *unk_23C[2];
    EasyChatInterfaceContext *unk_244;
    EasyChatConfirmCancelMenu *unk_248;
    EasyChatCategoriesContext *unk_24C;
    EasyChatWordMenu *unk_250;
    UnkStruct_ov20_021D4AD4 *unk_254;
} UnkStruct_ov20_021D2128;

typedef struct {
    UnkStruct_ov20_021D2128 *unk_00;
    const EasyChatApp *app;
    const EasyChatWordList *wordList;
    u32 unk_0C;
    int unk_10;
    int unk_14;
} UnkStruct_ov20_021D2238;

static void ov20_021D2178(SysTask *param0, void *param1);
static void ov20_021D217C(SysTask *param0, void *param1);
static void ov20_021D2238(UnkStruct_ov20_021D2238 *param0);
static void ov20_021D2260(SysTask *param0, void *param1);
static void ov20_021D2370(UnkStruct_ov20_021D2238 *param0, NARC *param1);
static void ov20_021D2414(SysTask *param0, void *param1);
static void ov20_021D24EC(UnkStruct_ov20_021D2238 *param0);
static void ov20_021D2570(SysTask *param0, void *param1);
static void ov20_021D25C0(SysTask *param0, void *param1);
static void ov20_021D25EC(SysTask *param0, void *param1);
static void ov20_021D2630(SysTask *param0, void *param1);
static void ov20_021D2660(SysTask *param0, void *param1);
static void ov20_021D26D8(SysTask *param0, void *param1);
static void ov20_021D2740(SysTask *param0, void *param1);
static void ov20_021D27E4(SysTask *param0, void *param1);
static void ov20_021D2848(SysTask *param0, void *param1);
static void ov20_021D28E8(SysTask *param0, void *param1);
static void ov20_021D29BC(SysTask *param0, void *param1);
static void ov20_021D2A9C(SysTask *param0, void *param1);
static void ov20_021D2B74(SysTask *param0, void *param1);
static void ov20_021D2B94(SysTask *param0, void *param1);
static void ov20_021D2BB4(SysTask *param0, void *param1);
static void ov20_021D2BD4(SysTask *param0, void *param1);
static void ov20_021D2BF4(SysTask *param0, void *param1);
static void ov20_021D2C44(SysTask *param0, void *param1);
static void ov20_021D2C60(SysTask *param0, void *param1);
static void ov20_021D2CB0(SysTask *param0, void *param1);
static void ov20_021D2D00(SysTask *param0, void *param1);
static void ov20_021D2D1C(SysTask *param0, void *param1);
static void ov20_021D2D3C(SysTask *param0, void *param1);
static void ov20_021D2D84(SysTask *param0, void *param1);
static void ov20_021D2DA0(SysTask *param0, void *param1);
static void ov20_021D2DBC(SysTask *param0, void *param1);
static void ov20_021D2DD8(SysTask *param0, void *param1);

UnkStruct_ov20_021D2128 *ov20_021D2098(const EasyChatApp *param0, const EasyChatWordList *wordList)
{
    UnkStruct_ov20_021D2128 *v0 = Heap_Alloc(HEAP_ID_35, sizeof(UnkStruct_ov20_021D2128));

    if (v0) {
        int v1;

        SetVBlankCallback(NULL, NULL);
        DisableHBlank();

        v0->app = param0;
        v0->wordList = wordList;

        NNS_G2dInitOamManagerModule();
        RenderOam_Init(0, 128, 0, 32, 0, 128, 0, 32, 35);

        v0->unk_24 = SpriteList_InitRendering(128, &v0->unk_28, HEAP_ID_35);
        v0->bgConfig = BgConfig_New(HEAP_ID_35);
        v0->unk_00 = SysTask_Start(ov20_021D2178, v0, 2);
        v0->unk_04 = ov20_021D2170(ov20_021D217C, v0, 1);

        for (v1 = 0; v1 < 4; v1++) {
            v0->unk_08[v1] = NULL;
        }
    }

    return v0;
}

void ov20_021D2128(UnkStruct_ov20_021D2128 *param0)
{
    if (param0) {
        int v0;

        SetVBlankCallback(NULL, NULL);

        for (v0 = 0; v0 < 4; v0++) {
            if (param0->unk_08[v0]) {
                SysTask_Done(param0->unk_08[v0]);
            }
        }

        SysTask_Done(param0->unk_00);
        SysTask_Done(param0->unk_04);

        RenderOam_Free();
        SpriteList_Delete(param0->unk_24);

        Heap_Free(param0->bgConfig);
        Heap_Free(param0);
    }
}

SysTask *ov20_021D2170(SysTaskFunc param0, void *param1, int param2)
{
    return SysTask_ExecuteOnVBlank(param0, param1, param2);
}

static void ov20_021D2178(SysTask *param0, void *param1)
{
    return;
}

static void ov20_021D217C(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2128 *v0 = param1;

    SpriteList_Update(v0->unk_24);
    RenderOam_Transfer();

    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

void ov20_021D21A0(UnkStruct_ov20_021D2128 *param0, int param1)
{
    static const SysTaskFunc v0[] = {
        [EASY_CHAT_SYSTASK_00] = ov20_021D2260,
        [EASY_CHAT_SYSTASK_01] = ov20_021D2414,
        [EASY_CHAT_SYSTASK_02] = ov20_021D2570,
        [EASY_CHAT_SYSTASK_03] = ov20_021D25C0,
        [EASY_CHAT_SYSTASK_04] = ov20_021D25EC,
        [EASY_CHAT_SYSTASK_05] = ov20_021D2630,
        [EASY_CHAT_SYSTASK_06] = ov20_021D2660,
        [EASY_CHAT_SYSTASK_07] = ov20_021D27E4,
        [EASY_CHAT_SYSTASK_08] = ov20_021D2848,
        [EASY_CHAT_SYSTASK_09] = ov20_021D28E8,
        [EASY_CHAT_SYSTASK_10] = ov20_021D29BC,
        [EASY_CHAT_SYSTASK_11] = ov20_021D2A9C,
        [EASY_CHAT_SYSTASK_12] = ov20_021D2B74,
        [EASY_CHAT_SYSTASK_13] = ov20_021D2B94,
        [EASY_CHAT_SYSTASK_14] = ov20_021D2BB4,
        [EASY_CHAT_SYSTASK_15] = ov20_021D2BD4,
        [EASY_CHAT_SYSTASK_16] = ov20_021D2BF4,
        [EASY_CHAT_SYSTASK_17] = ov20_021D2C44,
        [EASY_CHAT_SYSTASK_18] = ov20_021D2C60,
        [EASY_CHAT_SYSTASK_19] = ov20_021D2CB0,
        [EASY_CHAT_SYSTASK_20] = ov20_021D2D00,
        [EASY_CHAT_SYSTASK_21] = ov20_021D2D1C,
        [EASY_CHAT_SYSTASK_22] = ov20_021D2D3C,
        [EASY_CHAT_SYSTASK_23] = ov20_021D26D8,
        [EASY_CHAT_SYSTASK_24] = ov20_021D2740,
        [EASY_CHAT_SYSTASK_25] = ov20_021D2D84,
        [EASY_CHAT_SYSTASK_26] = ov20_021D2DA0,
        [EASY_CHAT_SYSTASK_27] = ov20_021D2DBC,
        [EASY_CHAT_SYSTASK_28] = ov20_021D2DD8,
    };

    if (param1 < NELEMS(v0)) {
        UnkStruct_ov20_021D2238 *v1 = Heap_Alloc(HEAP_ID_35, sizeof(UnkStruct_ov20_021D2238));

        if (v1) {
            int v2;

            v1->unk_14 = 0;
            v1->unk_0C = param1;
            v1->unk_00 = param0;
            v1->app = param0->app;
            v1->wordList = param0->wordList;

            for (v2 = 0; v2 < 4; v2++) {
                if (param0->unk_08[v2] == NULL) {
                    v1->unk_10 = v2;
                    param0->unk_08[v2] = SysTask_Start(v0[param1], v1, 1);
                    break;
                }
            }
        }
    } else {
        GF_ASSERT(FALSE);
    }
}

BOOL ov20_021D21F8(UnkStruct_ov20_021D2128 *param0)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        if (param0->unk_08[v0] != NULL) {
            return 0;
        }
    }

    return 1;
}

BOOL ov20_021D2210(UnkStruct_ov20_021D2128 *param0, int param1)
{
    int v0;

    for (v0 = 0; v0 < 4; v0++) {
        if (param0->unk_08[v0] != NULL) {
            UnkStruct_ov20_021D2238 *v1 = SysTask_GetParam(param0->unk_08[v0]);

            if (v1->unk_0C == param1) {
                return 0;
            }
        }
    }

    return 1;
}

static void ov20_021D2238(UnkStruct_ov20_021D2238 *param0)
{
    SysTask_Done(param0->unk_00->unk_08[param0->unk_10]);
    param0->unk_00->unk_08[param0->unk_10] = NULL;
    Heap_Free(param0);
}

static void ov20_021D2260(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;

    GXLayers_DisableEngineALayers();
    GXLayers_DisableEngineBLayers();
    GX_SetVisiblePlane(0);
    GXS_SetVisiblePlane(0);

    GX_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_64K);
    GXS_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_32K);

    NARC *narc = NARC_ctor(NARC_INDEX_GRAPHIC__PMSI, HEAP_ID_35);

    ov20_021D24EC(v0);
    ov20_021D2370(v0, narc);

    v0->unk_00->unk_244 = EasyChatInterfaceContext_New(v0->unk_00, v0->app, v0->wordList);
    EasyChatInterface_Draw(v0->unk_00->unk_244, narc);

    v0->unk_00->unk_248 = EasyChatConfirmCancelMenu_New(v0->unk_00, v0->app, v0->wordList);
    EasyChatConfirmCancelMenu_Draw(v0->unk_00->unk_248, narc);

    v0->unk_00->unk_24C = EasyChatCategoriesContext_New(v0->unk_00, v0->app, v0->wordList);
    EasyChatCategories_DrawInterface(v0->unk_00->unk_24C, narc);

    v0->unk_00->unk_250 = EasyChatWordMenu_New(v0->unk_00, v0->app, v0->wordList);
    ov20_021D41A8(v0->unk_00->unk_250);

    v0->unk_00->unk_254 = ov20_021D4728(v0->unk_00, v0->app, v0->wordList);
    ov20_021D4774(v0->unk_00->unk_254, narc);

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_OBJ, TRUE);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_OBJ, TRUE);
    GX_DispOn();

    NARC_dtor(narc);

    ov20_021D2238(v0);
}

static void ov20_021D2370(UnkStruct_ov20_021D2238 *param0, NARC *param1)
{
    UnkStruct_ov20_021D2128 *v0 = param0->unk_00;

    NNS_G2dInitImagePaletteProxy(&(v0->unk_1FC[0]));
    NNS_G2dInitImagePaletteProxy(&(v0->unk_1FC[1]));

    NNS_G2dInitImageProxy(&(v0->unk_1B4[0]));
    NNS_G2dInitImageProxy(&(v0->unk_1B4[1]));

    Graphics_LoadImageMappingFromOpenNARC(param1, 9, 1, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 35, &(v0->unk_1B4[0]));
    Graphics_LoadPartialPaletteFromOpenNARC(param1, 10, NNS_G2D_VRAM_TYPE_2DMAIN, 0, 35, &(v0->unk_1FC[0]));

    v0->unk_234[0] = Graphics_GetCellBankFromOpenNARC(param1, 7, 1, &(v0->unk_224[0]), HEAP_ID_35);
    v0->unk_23C[0] = Graphics_GetAnimBankFromOpenNARC(param1, 8, 1, &(v0->unk_22C[0]), HEAP_ID_35);
    v0->unk_234[1] = NULL;
    v0->unk_23C[1] = NULL;
}

static void ov20_021D2414(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_OUT, FADE_TYPE_BRIGHTNESS_OUT, COLOR_BLACK, 5, 1, HEAP_ID_35);
        v0->unk_14++;
        break;
    case 1:
        if (IsScreenFadeDone()) {
            int v2;

            EasyChatInterfaceContext_Free(v0->unk_00->unk_244);
            EasyChatConfirmCancelMenu_Free(v0->unk_00->unk_248);
            EasyChatCategoriesContext_Free(v0->unk_00->unk_24C);
            EasyChatWordMenu_Free(v0->unk_00->unk_250);
            ov20_021D4764(v0->unk_00->unk_254);

            for (v2 = 0; v2 < 2; v2++) {
                if (v1->unk_234[v2] != NULL) {
                    Heap_Free(v1->unk_234[v2]);
                }

                if (v1->unk_23C[v2] != NULL) {
                    Heap_Free(v1->unk_23C[v2]);
                }
            }

            Bg_FreeTilemapBuffer(v1->bgConfig, BG_LAYER_MAIN_0);
            Bg_FreeTilemapBuffer(v1->bgConfig, BG_LAYER_MAIN_1);
            Bg_FreeTilemapBuffer(v1->bgConfig, BG_LAYER_MAIN_2);
            Bg_FreeTilemapBuffer(v1->bgConfig, BG_LAYER_MAIN_3);
            Bg_FreeTilemapBuffer(v1->bgConfig, BG_LAYER_SUB_0);

            ov20_021D2238(v0);
        }
        break;
    }
}

static void ov20_021D24EC(UnkStruct_ov20_021D2238 *param0)
{
    static const GXBanks v0 = {
        GX_VRAM_BG_128_B,
        GX_VRAM_BGEXTPLTT_NONE,
        GX_VRAM_SUB_BG_128_C,
        GX_VRAM_SUB_BGEXTPLTT_NONE,
        GX_VRAM_OBJ_64_E,
        GX_VRAM_OBJEXTPLTT_NONE,
        GX_VRAM_SUB_OBJ_16_I,
        GX_VRAM_SUB_OBJEXTPLTT_NONE,
        GX_VRAM_TEX_0_A,
        GX_VRAM_TEXPLTT_01_FG
    };
    static const GraphicsModes v1 = {
        GX_DISPMODE_GRAPHICS,
        GX_BGMODE_0,
        GX_BGMODE_0,
        GX_BG0_AS_2D,
    };
    static const BgTemplate v2 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x800,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xd800,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0,
        .areaOver = 0,
        .mosaic = FALSE,
    };
    static const BgTemplate v3 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x1000,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_512x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xe000,
        .charBase = GX_BG_CHARBASE_0x10000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 1,
        .areaOver = 0,
        .mosaic = FALSE,
    };
    static const BgTemplate v4 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x800,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xf000,
        .charBase = GX_BG_CHARBASE_0x18000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 2,
        .areaOver = 0,
        .mosaic = FALSE,
    };
    static const BgTemplate v5 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x800,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xf800,
        .charBase = GX_BG_CHARBASE_0x08000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 3,
        .areaOver = 0,
        .mosaic = FALSE,
    };
    static const BgTemplate v6 = {
        .x = 0,
        .y = 0,
        .bufferSize = 0x800,
        .baseTile = 0,
        .screenSize = BG_SCREEN_SIZE_256x256,
        .colorMode = GX_BG_COLORMODE_16,
        .screenBase = GX_BG_SCRBASE_0xe000,
        .charBase = GX_BG_CHARBASE_0x00000,
        .bgExtPltt = GX_BG_EXTPLTT_01,
        .priority = 0,
        .areaOver = 0,
        .mosaic = FALSE,
    };
    UnkStruct_ov20_021D2128 *v7 = param0->unk_00;

    GX_SetDispSelect(GX_DISP_SELECT_MAIN_SUB);
    GX_SetGraphicsMode(GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BG0_AS_3D);

    GXLayers_SetBanks(&v0);
    SetAllGraphicsModes(&v1);

    Bg_InitFromTemplate(v7->bgConfig, BG_LAYER_MAIN_0, &v2, 0);
    Bg_InitFromTemplate(v7->bgConfig, BG_LAYER_MAIN_1, &v3, 0);
    Bg_InitFromTemplate(v7->bgConfig, BG_LAYER_MAIN_2, &v4, 0);
    Bg_InitFromTemplate(v7->bgConfig, BG_LAYER_MAIN_3, &v5, 0);

    Bg_InitFromTemplate(v7->bgConfig, BG_LAYER_SUB_0, &v6, 0);
}

static void ov20_021D2570(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, COLOR_BLACK, 5, 1, HEAP_ID_35);
        v0->unk_14++;
        break;
    case 1:
        if (IsScreenFadeDone()) {
            v0->unk_14++;
        }
        break;
    default:
        ov20_021D2238(v0);
        break;
    }
}

static void ov20_021D25C0(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    EasyChatInterface_DrawEntryWindow(v1->unk_244);
    EasyChatInterface_SetCursorPosition(v1->unk_244, EasyChat_GetCurrentWordSlot(v0->app));

    ov20_021D2238(v0);
}

static void ov20_021D25EC(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    EasyChatInterface_SetCursorDrawFlag(v1->unk_244, 0);
    EasyChatInterface_HideSentenceSelectionArrows(v1->unk_244);

    EasyChatConfirmCancelMenu_SetCursorDrawFlag(v1->unk_248, 1);
    EasyChatConfirmCancelMenu_SetCursorPosition(v1->unk_248, ov20_021D1FD4(v1->app));

    ov20_021D2238(v0);
}

static void ov20_021D2630(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    EasyChatConfirmCancelMenu_SetCursorDrawFlag(v1->unk_248, 0);
    EasyChatInterface_DrawSentenceSelectionArrows(v1->unk_244);
    EasyChatInterface_SetCursorDrawFlag(v1->unk_244, 1);
    ov20_021D2238(v0);
}

static void ov20_021D2660(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        EasyChatInterface_StopCursorBlink(v1->unk_244);
        EasyChatInterface_HideSentenceSelectionArrows(v1->unk_244);
        ov20_021D3EF8(v1->unk_24C);
        v0->unk_14++;
        break;
    case 1:
        if (ov20_021D3F10(v1->unk_24C)) {
            EasyChatConfirmCancelMenu_Hide(v1->unk_248);
            EasyChatCategories_SetCursorPosition(v1->unk_24C, EasyChat_GetCategoryCursorPos(v1->app));
            EasyChatCategories_SetCursorDrawFlag(v1->unk_24C, 1);
            ov20_021D2238(v0);
        }
        break;
    }
}

static void ov20_021D26D8(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        ov20_021D4BA4(v1->unk_254);
        v0->unk_14++;
        break;
    case 1:
        ov20_021D40A8(v1->unk_24C);
        v0->unk_14++;
        break;
    case 2:
        if (ov20_021D40DC(v1->unk_24C)
            && ov20_021D4C2C(v1->unk_254)) {
            ov20_021D4084(v1->unk_24C);
            ov20_021D2238(v0);
        }
        break;
    }
}

static void ov20_021D2740(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        ov20_021D4BA4(v1->unk_254);
        v0->unk_14++;
        break;
    case 1:
        EasyChatCategories_SetCursorDrawFlag(v1->unk_24C, 0);
        ov20_021D40A8(v1->unk_24C);
        v0->unk_14++;
        break;
    case 2:
        if (ov20_021D40DC(v1->unk_24C)) {
            ov20_021D4084(v1->unk_24C);
            v0->unk_14++;
        }
        break;
    case 3:
        if (ov20_021D4C2C(v1->unk_254)) {
            EasyChatCategories_SetCursorPosition(v1->unk_24C, EasyChat_GetCategoryCursorPos(v1->app));
            EasyChatCategories_SetCursorDrawFlag(v1->unk_24C, 1);
            ov20_021D2238(v0);
        }
        break;
    }
}

static void ov20_021D27E4(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        EasyChatConfirmCancelMenu_Show(v1->unk_248);
        EasyChatCategories_SetCursorDrawFlag(v1->unk_24C, 0);
        ov20_021D3F60(v1->unk_24C);
        v0->unk_14++;
        break;
    case 1:
        if (ov20_021D3F84(v1->unk_24C)) {
            EasyChatInterface_DrawSentenceSelectionArrows(v1->unk_244);
            EasyChatInterface_StartCursorBlink(v1->unk_244);
            ov20_021D2238(v0);
        }
        break;
    }
}

static void ov20_021D2848(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        ov20_021D4294(v1->unk_250);
        EasyChatCategories_SetCursorDrawFlag(v1->unk_24C, 0);
        ov20_021D4004(v1->unk_24C);
        v0->unk_14++;
        break;
    case 1:
        if (ov20_021D4020(v1->unk_24C)) {
            ov20_021D42E4(v1->unk_250);
            v0->unk_14++;
        }
        break;
    case 2:
        if (ov20_021D4390(v1->unk_250)) {
            ov20_021D4480(v1->unk_250, EasyChat_GetWordPickerCursorPos(v1->app));
            EasyChatWordMenu_SetSpriteDrawFlags(v1->unk_250, 1);
            ov20_021D4DBC(v1->unk_254, 1);
            ov20_021D2238(v0);
        }
        break;
    }
}

static void ov20_021D28E8(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        ov20_021D4BA4(v1->unk_254);
        v0->unk_14++;
        break;
    case 1:
        EasyChatWordMenu_SetSpriteDrawFlags(v1->unk_250, 0);
        ov20_021D4DBC(v1->unk_254, 0);
        ov20_021D43B4(v1->unk_250);
        v0->unk_14++;
        break;
    case 2:
        if (ov20_021D43D8(v1->unk_250)) {
            ov20_021D4084(v1->unk_24C);
            v0->unk_14++;
        }
        break;
    case 3:
        ov20_021D403C(v1->unk_24C);
        v0->unk_14++;
        break;
    case 4:
        if (ov20_021D4078(v1->unk_24C)
            && ov20_021D4C2C(v1->unk_254)) {
            EasyChatCategories_SetCursorPosition(v1->unk_24C, EasyChat_GetCategoryCursorPos(v1->app));
            EasyChatCategories_SetCursorDrawFlag(v1->unk_24C, 1);
            ov20_021D2238(v0);
        }
        break;
    }
}

static void ov20_021D29BC(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        EasyChatConfirmCancelMenu_Show(v1->unk_248);
        EasyChatWordMenu_SetSpriteDrawFlags(v1->unk_250, 0);
        ov20_021D4DBC(v1->unk_254, 0);
        ov20_021D43B4(v1->unk_250);
        v0->unk_14++;
        break;
    case 1:
        if (ov20_021D43D8(v1->unk_250)) {
            ov20_021D3FD0(v1->unk_24C);
            ov20_021D403C(v1->unk_24C);
            v0->unk_14++;
        }
        break;
    case 2:
        if (ov20_021D4078(v1->unk_24C)) {
            ov20_021D3FE0(v1->unk_24C);
            v0->unk_14++;
        }
        break;
    case 3:
        if (ov20_021D3FF8(v1->unk_24C)) {
            EasyChatInterface_DrawEntryWindow(v1->unk_244);
            EasyChatInterface_SetCursorDrawFlag(v1->unk_244, 1);
            EasyChatInterface_DrawSentenceSelectionArrows(v1->unk_244);
            EasyChatInterface_StartCursorBlink(v1->unk_244);
            ov20_021D2238(v0);
        }
    }
}

static void ov20_021D2A9C(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        EasyChatConfirmCancelMenu_Show(v1->unk_248);
        EasyChatWordMenu_SetSpriteDrawFlags(v1->unk_250, 0);
        ov20_021D4DBC(v1->unk_254, 0);
        ov20_021D43B4(v1->unk_250);
        v0->unk_14++;
        break;
    case 1:
        if (ov20_021D43D8(v1->unk_250)) {
            ov20_021D3FD0(v1->unk_24C);
            ov20_021D403C(v1->unk_24C);
            v0->unk_14++;
        }
        break;
    case 2:
        if (ov20_021D4078(v1->unk_24C)) {
            ov20_021D3FE0(v1->unk_24C);
            v0->unk_14++;
        }
        break;
    case 3:
        if (ov20_021D3FF8(v1->unk_24C)) {
            EasyChatInterface_DrawEntryWindow(v1->unk_244);
            EasyChatInterface_SetCursorDrawFlag(v1->unk_244, 0);
            EasyChatConfirmCancelMenu_SetCursorDrawFlag(v1->unk_248, 1);
            ov20_021D2238(v0);
        }
    }
}

static void ov20_021D2B74(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    EasyChatInterface_SetCursorPosition(v1->unk_244, EasyChat_GetCurrentWordSlot(v1->app));
    ov20_021D2238(v0);
}

static void ov20_021D2B94(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    EasyChatConfirmCancelMenu_SetCursorPosition(v1->unk_248, ov20_021D1FD4(v1->app));
    ov20_021D2238(v0);
}

static void ov20_021D2BB4(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    EasyChatCategories_SetCursorPosition(v1->unk_24C, EasyChat_GetCategoryCursorPos(v1->app));
    ov20_021D2238(v0);
}

static void ov20_021D2BD4(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    ov20_021D4480(v1->unk_250, EasyChat_GetWordPickerCursorPos(v1->app));
    ov20_021D2238(v0);
}

static void ov20_021D2BF4(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    switch (v0->unk_14) {
    case 0:
        ov20_021D44BC(v1->unk_250, EasyChat_GetWordPickerScrollDistance(v1->app));
        v0->unk_14++;
        break;
    case 1:
        if (ov20_021D4578(v1->unk_250)) {
            ov20_021D4DBC(v1->unk_254, 1);
            ov20_021D2238(v0);
        }
        break;
    }
}

static void ov20_021D2C44(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    EasyChatInterface_PrintMessage(v1->unk_244, EC_MESSAGE_TYPE_INSTRUCTIONS);
    ov20_021D2238(v0);
}

static void ov20_021D2C60(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    EasyChatInterface_PrintMessage(v1->unk_244, EC_MESSAGE_TYPE_CONFIRM_ANSWER);
    EasyChatInterface_OpenYesNoMenu(v1->unk_244, ov20_021D208C(v0->app));

    if (EasyChatConfirmCancelMenu_GetCursorDrawFlag(v1->unk_248)) {
        EasyChatConfirmCancelMenu_StopCursorBlink(v1->unk_248);
    } else {
        EasyChatInterface_StopCursorBlink(v1->unk_244);
    }

    ov20_021D2238(v0);
}

static void ov20_021D2CB0(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    EasyChatInterface_PrintMessage(v1->unk_244, EC_MESSAGE_TYPE_CONFIRM_QUIT);
    EasyChatInterface_OpenYesNoMenu(v1->unk_244, ov20_021D208C(v0->app));

    if (EasyChatConfirmCancelMenu_GetCursorDrawFlag(v1->unk_248)) {
        EasyChatConfirmCancelMenu_StopCursorBlink(v1->unk_248);
    } else {
        EasyChatInterface_StopCursorBlink(v1->unk_244);
    }

    ov20_021D2238(v0);
}

static void ov20_021D2D00(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    EasyChatInterface_PrintMessage(v1->unk_244, EC_MESSAGE_TYPE_PLEASE_ENTER);
    ov20_021D2238(v0);
}

static void ov20_021D2D1C(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    EasyChatInterface_UpdateYesNoArrow(v1->unk_244, ov20_021D208C(v0->app));
    ov20_021D2238(v0);
}

static void ov20_021D2D3C(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    EasyChatInterface_PrintMessage(v1->unk_244, EC_MESSAGE_TYPE_INSTRUCTIONS);
    EasyChatInterface_CloseYesNoMenu(v1->unk_244);

    if (EasyChatConfirmCancelMenu_GetCursorDrawFlag(v1->unk_248)) {
        EasyChatConfirmCancelMenu_StartCursorBlink(v1->unk_248);
    } else {
        EasyChatInterface_StartCursorBlink(v1->unk_244);
    }

    ov20_021D2238(v0);
}

static void ov20_021D2D84(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    ov20_021D4DF4(v1->unk_254, 0, 1);
    ov20_021D2238(v0);
}

static void ov20_021D2DA0(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    ov20_021D4DF4(v1->unk_254, 1, 1);
    ov20_021D2238(v0);
}

static void ov20_021D2DBC(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    ov20_021D4DF4(v1->unk_254, 0, 0);
    ov20_021D2238(v0);
}

static void ov20_021D2DD8(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D2238 *v0 = param1;
    UnkStruct_ov20_021D2128 *v1 = v0->unk_00;

    ov20_021D4DF4(v1->unk_254, 1, 0);
    ov20_021D2238(v0);
}

u32 ov20_021D2DF4(UnkStruct_ov20_021D2128 *param0)
{
    return EasyChatInterface_GetWordSlotCount(param0->unk_244);
}

BgConfig *ov20_021D2E04(UnkStruct_ov20_021D2128 *param0)
{
    return param0->bgConfig;
}

SpriteList *ov20_021D2E08(UnkStruct_ov20_021D2128 *param0)
{
    return param0->unk_24;
}

void ov20_021D2E0C(UnkStruct_ov20_021D2128 *param0, SpriteResourcesHeader *param1, u32 param2, u32 param3)
{
    param1->imageProxy = &param0->unk_1B4[param2];
    param1->paletteProxy = &param0->unk_1FC[param2];
    param1->cellBank = param0->unk_224[param2];
    param1->cellAnimBank = param0->unk_22C[param2];
    param1->priority = param3;
    param1->charData = NULL;
    param1->multiCellBank = NULL;
    param1->multiCellAnimBank = NULL;
    param1->isVRamTransfer = 0;
}

Sprite *ov20_021D2E50(UnkStruct_ov20_021D2128 *param0, SpriteResourcesHeader *param1, u32 x, u32 y, u32 priority, enum NNS_G2D_VRAM_TYPE vramType)
{
    SpriteListTemplate v0;
    Sprite *v1;
    OSIntrMode v2;

    v0.list = param0->unk_24;
    v0.resourceData = param1;
    v0.position.x = x * FX32_ONE;
    v0.position.y = y * FX32_ONE;
    v0.position.z = 0;
    v0.priority = priority;
    v0.vramType = vramType;
    v0.heapID = HEAP_ID_35;

    v2 = OS_DisableInterrupts();
    v1 = SpriteList_Add(&v0);

    OS_RestoreInterrupts(v2);

    if (v1) {
        Sprite_SetAnimateFlag(v1, 1);
        Sprite_SetAnimSpeed(v1, (FX32_ONE * 2) / 2);
    }

    return v1;
}
