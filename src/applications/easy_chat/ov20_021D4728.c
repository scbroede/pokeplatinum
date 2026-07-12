#include "applications/easy_chat/ov20_021D4728.h"

#include <nitro.h>
#include <string.h>

#include "constants/heap.h"

#include "applications/easy_chat/main.h"
#include "applications/easy_chat/ov20_021D2098.h"
#include "applications/easy_chat/struct_ov20_021D2128_decl.h"

#include "bg_window.h"
#include "easy_chat_word_list.h"
#include "font.h"
#include "graphics.h"
#include "heap.h"
#include "message.h"
#include "narc.h"
#include "sprite.h"
#include "string_gf.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "text.h"

#include "res/text/bank/easy_chat.h"

typedef struct {
    void *ncerBuffer;
    NNSG2dCellDataBank *unk_04;
    void *nanrBuffer;
    NNSG2dAnimBankData *unk_0C;
} UnkStruct_ov20_021D4B2C;

typedef struct UnkStruct_ov20_021D4AD4_t {
    UnkStruct_ov20_021D2128 *unk_00;
    const EasyChatApp *app;
    const EasyChatWordList *unusedWordList;
    BgConfig *bgConfig;
    SpriteList *unk_10;
    Sprite *unk_14;
    Sprite *unk_18;
    UnkStruct_ov20_021D4B2C unk_1C;
    u16 unk_2C[8][77];
    SysTask *unk_4FC;
} UnkStruct_ov20_021D4AD4;

typedef struct {
    UnkStruct_ov20_021D4AD4 *unk_00;
    int unk_04;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 x1;
    u16 y1;
    u16 unk_12;
    u16 x2;
    u16 y2;
} UnkStruct_ov20_021D4BA4;

static void ov20_021D4874(UnkStruct_ov20_021D4AD4 *param0, NARC *param1);
static void ov20_021D48C4(UnkStruct_ov20_021D4AD4 *param0, NARC *param1);
static void ov20_021D498C(Window *param0, BgConfig *param1, const String *param2, int param3);
static void ov20_021D4A24(UnkStruct_ov20_021D4AD4 *param0, NARC *param1);
static void ov20_021D4AD4(UnkStruct_ov20_021D4AD4 *param0);
static void ov20_021D4AF8(UnkStruct_ov20_021D4B2C *param0, NARC *param1, u32 param2, u32 param3);
static void ov20_021D4B2C(UnkStruct_ov20_021D4B2C *param0);
static void ov20_021D4C40(SysTask *param0, void *param1);
static Sprite *ov20_021D4B40(UnkStruct_ov20_021D4AD4 *param0, NNSG2dImageProxy *param1, NNSG2dImagePaletteProxy *param2, UnkStruct_ov20_021D4B2C *param3, int param4, int param5, int param6, int param7);

UnkStruct_ov20_021D4AD4 *ov20_021D4728(UnkStruct_ov20_021D2128 *param0, const EasyChatApp *param1, const EasyChatWordList *wordList)
{
    UnkStruct_ov20_021D4AD4 *v0 = Heap_Alloc(HEAP_ID_35, sizeof(UnkStruct_ov20_021D4AD4));

    v0->unk_00 = param0;
    v0->app = param1;
    v0->unusedWordList = wordList;
    v0->bgConfig = ov20_021D2E04(param0);
    v0->unk_10 = ov20_021D2E08(param0);
    v0->unk_14 = NULL;
    v0->unk_18 = NULL;
    v0->unk_4FC = NULL;

    return v0;
}

void ov20_021D4764(UnkStruct_ov20_021D4AD4 *param0)
{
    ov20_021D4AD4(param0);
    Heap_Free(param0);
}

void ov20_021D4774(UnkStruct_ov20_021D4AD4 *param0, NARC *narc)
{
    Graphics_LoadPaletteFromOpenNARC(narc, 21, PAL_LOAD_SUB_BG, 0, PALETTE_SIZE_BYTES * 2, HEAP_ID_35);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(narc, 11, param0->bgConfig, 4, 0, 0, 1, HEAP_ID_35);

    ov20_021D4874(param0, narc);
    ov20_021D48C4(param0, narc);

    if (EasyChat_GetMode(param0->app) == GROUP_MODE) {
        Bg_CopyToTilemapRect(param0->bgConfig, 4, 3, 3, 11, 7, param0->unk_2C[3], 0, 0, 11, 7);
        Bg_CopyToTilemapRect(param0->bgConfig, 4, 3, 14, 11, 7, param0->unk_2C[4], 0, 0, 11, 7);
    } else {
        Bg_CopyToTilemapRect(param0->bgConfig, 4, 3, 3, 11, 7, param0->unk_2C[0], 0, 0, 11, 7);
        Bg_CopyToTilemapRect(param0->bgConfig, 4, 3, 14, 11, 7, param0->unk_2C[7], 0, 0, 11, 7);
    }

    ov20_021D4A24(param0, narc);
    Bg_CopyTilemapBufferToVRAM(param0->bgConfig, BG_LAYER_SUB_0);
}

static void ov20_021D4874(UnkStruct_ov20_021D4AD4 *param0, NARC *narc)
{
    static const u16 v0[] = {
        12,
        13,
        14,
        15,
        16,
        17,
        18,
        19,
    };

    for (int i = 0; i < NELEMS(v0); i++) {
        NNSG2dScreenData *screenData;
        void *nscrBuffer = Graphics_GetScrnDataFromOpenNARC(narc, v0[i], TRUE, &screenData, HEAP_ID_35);

        if (nscrBuffer) {
            MI_CpuCopy16(screenData->rawData, param0->unk_2C[i], 77 * 2);
            DC_FlushRange(param0->unk_2C[i], 77 * 2);
            Heap_Free(nscrBuffer);
        }
    }
}

static void ov20_021D48C4(UnkStruct_ov20_021D4AD4 *param0, NARC *narc)
{
    Font_InitManager(FONT_SUBSCREEN, HEAP_ID_SYSTEM);
    String *v0 = MessageBank_GetNewStringFromNARC(NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_EASY_CHAT, EasyChat_Text_GroupMode, HEAP_ID_35);
    String *v1 = MessageBank_GetNewStringFromNARC(NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_EASY_CHAT, EasyChat_Text_ABCMode, HEAP_ID_35);

    NNSG2dCharacterData *charData;
    void *ncgrBuffer = Graphics_GetCharDataFromOpenNARC(narc, 20, TRUE, &charData, HEAP_ID_35);

    if (ncgrBuffer) {
        Window window;

        Window_Init(&window);
        window.bgConfig = param0->bgConfig;
        window.width = 11;
        window.height = 57;
        window.colorMode = 0;
        window.pixels = charData->pRawData;
        ov20_021D498C(&window, param0->bgConfig, v0, 0);
        window.pixels = (u8 *)(charData->pRawData) + (11 * 7 * 4 * 0x20);
        ov20_021D498C(&window, param0->bgConfig, v1, 0);
        DC_FlushRange(charData->pRawData, charData->szByte);
        Bg_LoadTiles(param0->bgConfig, BG_LAYER_SUB_0, charData->pRawData, charData->szByte, 0);
        Heap_Free(ncgrBuffer);
    }

    String_Free(v1);
    String_Free(v0);
    Font_Free(FONT_SUBSCREEN);
}

static const s16 Unk_ov20_021D52EC[] = {
    22,
    (22 + 56 * 1) - 1,
    (22 + 56 * 2) - 2,
    (22 + 56 * 3) - 1,
};

static void ov20_021D498C(Window *param0, BgConfig *unused, const String *param2, int param3)
{
    int i;
    u32 numLines = String_NumLines(param2);
    String *line = String_Init(32, HEAP_ID_35);
    param3 += ((2 - numLines) * 16) / 2;

    for (i = 0; i < numLines; i++) {
        String_CopyLineNum(line, param2, i);
        int xOffset = Font_CalcCenterAlignment(FONT_SUBSCREEN, line, 0, 88);
        for (int v0 = 0; v0 < NELEMS(Unk_ov20_021D52EC); v0++) {
            int yOffset = Unk_ov20_021D52EC[v0] + param3;
            Text_AddPrinterWithParamsAndColor(param0, FONT_SUBSCREEN, line, xOffset, yOffset, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 3), NULL);
        }
        param3 += 16;
    }
    String_Free(line);
}

static void ov20_021D4A24(UnkStruct_ov20_021D4AD4 *param0, NARC *narc)
{
    NNSG2dImagePaletteProxy paletteProxy;
    NNSG2dImageProxy imageProxy;

    NNS_G2dInitImagePaletteProxy(&paletteProxy);
    NNS_G2dInitImageProxy(&imageProxy);

    Graphics_LoadPartialPaletteFromOpenNARC(narc, 25, NNS_G2D_VRAM_TYPE_2DSUB, 0, 35, &paletteProxy);
    Graphics_LoadImageMappingFromOpenNARC(narc, 24, 1, 0, 0, NNS_G2D_VRAM_TYPE_2DSUB, 0, 35, &imageProxy);

    ov20_021D4AF8(&(param0->unk_1C), narc, 22, 23);

    param0->unk_14 = ov20_021D4B40(param0, &imageProxy, &paletteProxy, &param0->unk_1C, 192, 56, 0, 0);
    Sprite_SetAnim(param0->unk_14, 0);
    Sprite_SetDrawFlag(param0->unk_14, FALSE);

    param0->unk_18 = ov20_021D4B40(param0, &imageProxy, &paletteProxy, &param0->unk_1C, 192, 136, 0, 0);
    Sprite_SetAnim(param0->unk_18, 2);
    Sprite_SetDrawFlag(param0->unk_18, FALSE);
}

static void ov20_021D4AD4(UnkStruct_ov20_021D4AD4 *param0)
{
    if (param0->unk_14) {
        Sprite_Delete(param0->unk_14);
    }

    if (param0->unk_18) {
        Sprite_Delete(param0->unk_18);
    }

    ov20_021D4B2C(&param0->unk_1C);
}

static void ov20_021D4AF8(UnkStruct_ov20_021D4B2C *param0, NARC *narc, u32 param2, u32 param3)
{
    param0->ncerBuffer = Graphics_GetCellBankFromOpenNARC(narc, param2, TRUE, &param0->unk_04, HEAP_ID_35);
    param0->nanrBuffer = Graphics_GetAnimBankFromOpenNARC(narc, param3, TRUE, &param0->unk_0C, HEAP_ID_35);
}

static void ov20_021D4B2C(UnkStruct_ov20_021D4B2C *param0)
{
    Heap_Free(param0->ncerBuffer);
    Heap_Free(param0->nanrBuffer);
}

static Sprite *ov20_021D4B40(UnkStruct_ov20_021D4AD4 *param0, NNSG2dImageProxy *imageProxy, NNSG2dImagePaletteProxy *paletteProxy, UnkStruct_ov20_021D4B2C *param3, int param4, int param5, int param6, int param7)
{
    SpriteResourcesHeader v0;
    v0.imageProxy = imageProxy;
    v0.paletteProxy = paletteProxy;
    v0.cellBank = param3->unk_04;
    v0.cellAnimBank = param3->unk_0C;
    v0.priority = param6;
    v0.charData = NULL;
    v0.multiCellBank = NULL;
    v0.multiCellAnimBank = NULL;
    v0.isVRamTransfer = 0;

    SpriteListTemplate v1;
    v1.list = param0->unk_10;
    v1.resourceData = &v0;
    v1.position.x = param4 * FX32_ONE;
    v1.position.y = (param5 + 192) * FX32_ONE;
    v1.position.z = 0;
    v1.priority = param7;
    v1.vramType = NNS_G2D_VRAM_TYPE_2DSUB;
    v1.heapID = HEAP_ID_35;

    Sprite *v2 = SpriteList_Add(&v1);

    if (v2) {
        Sprite_SetAnimateFlag(v2, TRUE);
        Sprite_SetAnimSpeed(v2, ((FX32_ONE * 2) / 2));
    }

    return v2;
}

void ov20_021D4BA4(UnkStruct_ov20_021D4AD4 *param0)
{
    UnkStruct_ov20_021D4BA4 *v0 = Heap_Alloc(HEAP_ID_35, sizeof(UnkStruct_ov20_021D4BA4));

    if (v0) {
        static const struct {
            u16 unk_00;
            u16 unk_02;
            u16 unk_04;
            u16 unk_06;
            u16 unk_08;
            u16 unk_0A;
            u16 unk_0C;
        } v1[] = {
            [GROUP_MODE] = { 0x1, 0x3, 0x3, 0x3, 0x4, 0x3, 0xE },
            [ABC_MODE] = { 0x5, 0x7, 0x3, 0xE, 0x0, 0x3, 0x3 }
        };
        int mode = EasyChat_GetMode(param0->app);

        v0->unk_00 = param0;
        v0->unk_04 = 0;
        v0->unk_08 = 0;
        v0->unk_0A = v1[mode].unk_00;
        v0->unk_0C = v1[mode].unk_02;
        v0->x1 = v1[mode].unk_04;
        v0->y1 = v1[mode].unk_06;
        v0->unk_12 = v1[mode].unk_08;
        v0->x2 = v1[mode].unk_0A;
        v0->y2 = v1[mode].unk_0C;

        param0->unk_4FC = SysTask_Start(ov20_021D4C40, v0, 1);
    } else {
        param0->unk_4FC = NULL;
    }
}

BOOL ov20_021D4C2C(UnkStruct_ov20_021D4AD4 *param0)
{
    return param0->unk_4FC == NULL;
}

static void ov20_021D4C40(SysTask *param0, void *param1)
{
    UnkStruct_ov20_021D4BA4 *v0 = param1;

    switch (v0->unk_04) {
    case 0:
        Bg_CopyToTilemapRect(v0->unk_00->bgConfig, BG_LAYER_SUB_0, v0->x1, v0->y1, 11, 7, v0->unk_00->unk_2C[v0->unk_0A], 0, 0, 11, 7);
        Bg_CopyToTilemapRect(v0->unk_00->bgConfig, BG_LAYER_SUB_0, v0->x2, v0->y2, 11, 7, v0->unk_00->unk_2C[v0->unk_12], 0, 0, 11, 7);
        Bg_CopyTilemapBufferToVRAM(v0->unk_00->bgConfig, BG_LAYER_SUB_0);

        v0->unk_0A++;
        v0->unk_04++;
        break;
    case 1:
        if (++(v0->unk_08) >= 2) {
            Bg_CopyToTilemapRect(v0->unk_00->bgConfig, BG_LAYER_SUB_0, v0->x1, v0->y1, 11, 7, v0->unk_00->unk_2C[v0->unk_0A], 0, 0, 11, 7);
            Bg_CopyTilemapBufferToVRAM(v0->unk_00->bgConfig, BG_LAYER_SUB_0);

            v0->unk_08 = 0;
            v0->unk_0A++;
            v0->unk_04++;
        }
        break;
    case 2:
        if (++(v0->unk_08) >= 4) {
            Bg_CopyToTilemapRect(v0->unk_00->bgConfig, BG_LAYER_SUB_0, v0->x1, v0->y1, 11, 7, v0->unk_00->unk_2C[v0->unk_0A], 0, 0, 11, 7);
            Bg_CopyTilemapBufferToVRAM(v0->unk_00->bgConfig, BG_LAYER_SUB_0);
            v0->unk_04++;
        }
        break;
    case 3:
        v0->unk_00->unk_4FC = NULL;
        Heap_Free(param1);
        SysTask_Done(param0);
    }
}

void ov20_021D4DBC(UnkStruct_ov20_021D4AD4 *param0, BOOL draw)
{
    if (draw) {
        Sprite_SetDrawFlag(param0->unk_14, EasyChat_CanScrollWordPickerUp(param0->app));
        Sprite_SetDrawFlag(param0->unk_18, EasyChat_CanScrollWordPickerDown(param0->app));
    } else {
        Sprite_SetDrawFlag(param0->unk_14, FALSE);
        Sprite_SetDrawFlag(param0->unk_18, FALSE);
    }
}

void ov20_021D4DF4(UnkStruct_ov20_021D4AD4 *param0, int param1, int param2)
{
    switch (param1) {
    case 0:
        switch (param2) {
        case 1:
            Sprite_SetAnim(param0->unk_14, 1);
            break;
        case 0:
            Sprite_SetAnim(param0->unk_14, 0);
            break;
        }
        break;
    case 1:
        switch (param2) {
        case 1:
            Sprite_SetAnim(param0->unk_18, 3);
            break;
        case 0:
            Sprite_SetAnim(param0->unk_18, 2);
            break;
        }
        break;
    }
}
