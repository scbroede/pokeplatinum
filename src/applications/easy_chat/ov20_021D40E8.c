#include "applications/easy_chat/ov20_021D40E8.h"

#include <nitro.h>
#include <string.h>

#include "applications/easy_chat/main.h"
#include "applications/easy_chat/ov20_021D2098.h"
#include "applications/easy_chat/ov20_021D4E38.h"
#include "applications/easy_chat/struct_ov20_021D2128_decl.h"
#include "applications/easy_chat/struct_ov20_021D4E8C.h"
#include "applications/easy_chat/struct_ov20_021D4FF0.h"

#include "bg_window.h"
#include "easy_chat_word_list.h"
#include "enums.h"
#include "heap.h"
#include "sprite.h"
#include "string_gf.h"
#include "text.h"

typedef struct EasyChatWordMenu_t {
    UnkStruct_ov20_021D2128 *unk_00;
    const EasyChatApp *app;
    const EasyChatWordList *unusedWordList;
    BgConfig *bgConfig;
    Window unk_10;
    Window unk_20;
    Sprite *cursorSprite;
    Sprite *upArrowSprite;
    Sprite *downArrowSprite;
    String *string;
    UnkStruct_ov20_021D4FF0 unk_40;
    UnkStruct_ov20_021D4E8C unk_60;
    u32 unk_80;
    GXWndPlane plane;
    int visibleWindow;
    int unk_8C;
    int unk_90;
} EasyChatWordMenu;

static void ov20_021D4210(EasyChatWordMenu *menu);
static void ov20_021D45AC(EasyChatWordMenu *menu, int param1);
static void ov20_021D4638(EasyChatWordMenu *menu);
static void EasyChatWordMenu_PrintWord(EasyChatWordMenu *menu, u32 param1, u32 param2);

EasyChatWordMenu *EasyChatWordMenu_New(UnkStruct_ov20_021D2128 *param0, const EasyChatApp *app, const EasyChatWordList *wordList)
{
    EasyChatWordMenu *menu = Heap_Alloc(HEAP_ID_35, sizeof(EasyChatWordMenu));

    menu->unk_00 = param0;
    menu->app = app;
    menu->unusedWordList = wordList;
    menu->bgConfig = ov20_021D2E04(param0);
    menu->string = String_Init(32, HEAP_ID_35);

    Window_Add(menu->bgConfig, &menu->unk_10, BG_LAYER_MAIN_2, 4, 0, 26, 32, 12, 1);
    Window_Add(menu->bgConfig, &menu->unk_20, BG_LAYER_MAIN_2, 0, 0, 12, 4, 12, 1);

    menu->cursorSprite = NULL;
    menu->upArrowSprite = NULL;
    menu->downArrowSprite = NULL;

    return menu;
}

void EasyChatWordMenu_Free(EasyChatWordMenu *menu)
{
    if (menu->cursorSprite) {
        Sprite_Delete(menu->cursorSprite);
    }

    if (menu->upArrowSprite) {
        Sprite_Delete(menu->upArrowSprite);
    }

    if (menu->downArrowSprite) {
        Sprite_Delete(menu->downArrowSprite);
    }

    if (menu->string) {
        String_Free(menu->string);
    }

    Window_Remove(&menu->unk_20);
    Window_Remove(&menu->unk_10);
    Heap_Free(menu);
}

void ov20_021D41A8(EasyChatWordMenu *menu)
{
    BgConfig *bgConfig = ov20_021D2E04(menu->unk_00);

    Bg_ClearTilesRange(BG_LAYER_MAIN_2, TILE_SIZE_4BPP, 0, HEAP_ID_35);
    Bg_FillTilemapRect(bgConfig, BG_LAYER_MAIN_2, 0, 0, 0, 32, 32, 12);

    Window_FillTilemap(&menu->unk_10, 0);
    Window_PutToTilemap(&menu->unk_10);
    Window_LoadTiles(&menu->unk_10);
    Bg_CopyTilemapBufferToVRAM(bgConfig, BG_LAYER_MAIN_2);

    ov20_021D4210(menu);

    Bg_ToggleLayer(BG_LAYER_MAIN_2, FALSE);
}

static void ov20_021D4210(EasyChatWordMenu *menu)
{
    SpriteResourcesHeader v0;
    ov20_021D2E0C(menu->unk_00, &v0, 0, 2);

    menu->cursorSprite = ov20_021D2E50(menu->unk_00, &v0, 72, 56, 3, NNS_G2D_VRAM_TYPE_2DMAIN);
    Sprite_SetAnim(menu->cursorSprite, 8);
    Sprite_SetDrawFlag(menu->cursorSprite, FALSE);

    menu->upArrowSprite = ov20_021D2E50(menu->unk_00, &v0, 240, 64, 4, NNS_G2D_VRAM_TYPE_2DMAIN);
    Sprite_SetAnim(menu->upArrowSprite, 11);
    Sprite_SetDrawFlag(menu->upArrowSprite, FALSE);

    menu->downArrowSprite = ov20_021D2E50(menu->unk_00, &v0, 240, 144, 4, NNS_G2D_VRAM_TYPE_2DMAIN);
    Sprite_SetAnim(menu->downArrowSprite, 10);
    Sprite_SetDrawFlag(menu->downArrowSprite, FALSE);
}

void ov20_021D4294(EasyChatWordMenu *menu)
{
    Window_FillTilemap(&menu->unk_10, 0);
    ov20_021D4638(menu);

    u32 wordCount = EasyChat_GetCurrentCategoryWordCount(menu->app);

    if (wordCount > 10) {
        wordCount = 10;
    }

    u32 v1 = menu->unk_8C;

    for (u32 i = 0; i < wordCount; i++) {
        EasyChatWordMenu_PrintWord(menu, i, v1);

        if (i & 1) {
            v1 += 24;
        }
    }

    Window_LoadTiles(&menu->unk_10);
}

void ov20_021D42E4(EasyChatWordMenu *menu)
{
    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_ALL, 0, 16);
    Bg_ToggleLayer(BG_LAYER_MAIN_2, TRUE);
    G2_SetWnd1InsidePlane(GX_WND_PLANEMASK_ALL, TRUE);

    menu->plane = G2_GetWndOutsidePlane();
    menu->visibleWindow = GX_GetVisibleWnd();

    G2_SetWndOutsidePlane(GX_WND_PLANEMASK_ALL ^ GX_WND_PLANEMASK_BG2, TRUE);
    G2_SetWnd1Position(0, 46, 255, 176);
    GX_SetVisibleWnd(GX_WNDMASK_W1);

    menu->unk_80 = 0;
    ov20_021D4F1C(&menu->unk_40, GX_BLEND_PLANEMASK_BG2, GX_BLEND_ALL, 0, 124, 6 * 2);
}

BOOL ov20_021D4390(EasyChatWordMenu *menu)
{
    if (menu->unk_80 == 0) {
        return !!ov20_021D4F4C(&menu->unk_40);
    } else {
        return TRUE;
    }    
}

void ov20_021D43B4(EasyChatWordMenu *menu)
{
    menu->unk_80 = 0;
    ov20_021D4F1C(&menu->unk_40, GX_BLEND_PLANEMASK_BG2, GX_BLEND_ALL, 124, 0, (6 * 2));
}

BOOL ov20_021D43D8(EasyChatWordMenu *menu)
{
    if (menu->unk_80 == 0) {
        if (ov20_021D4F4C(&menu->unk_40)) {
            Bg_ToggleLayer(BG_LAYER_MAIN_2, FALSE);
            G2_SetWndOutsidePlane(menu->plane.planeMask, menu->plane.effect);
            GX_SetVisibleWnd(menu->visibleWindow);
            return TRUE;
        }
    } else {
        return TRUE;
    }

    return FALSE;
}

void EasyChatWordMenu_SetSpriteDrawFlags(EasyChatWordMenu *menu, BOOL draw)
{
    Sprite_SetDrawFlag(menu->cursorSprite, draw);

    if (draw) {
        Sprite_SetDrawFlag(menu->upArrowSprite, EasyChat_CanScrollWordPickerUp(menu->app));
        Sprite_SetDrawFlag(menu->downArrowSprite, EasyChat_CanScrollWordPickerDown(menu->app));
    } else {
        Sprite_SetDrawFlag(menu->upArrowSprite, FALSE);
        Sprite_SetDrawFlag(menu->downArrowSprite, FALSE);
    }
}

void ov20_021D4480(EasyChatWordMenu *menu, u32 param1)
{
    VecFx32 v0;
    u32 v1 = param1 & 1;
    u32 v2 = param1 / 2;

    v0.x = (72 + 112 * v1) * FX32_ONE;
    v0.y = (56 + 24 * v2) * FX32_ONE;
    v0.z = 0;

    Sprite_SetPosition(menu->cursorSprite, &v0);
    Sprite_SetAnim(menu->cursorSprite, 8);
}

void ov20_021D44BC(EasyChatWordMenu *menu, int param1)
{
    int v0;

    ov20_021D45AC(menu, param1);

    int v1 = menu->unk_90 + (param1 * 2);
    v0 = (menu->unk_8C + (param1 * 24)) & 255;

    int v2;
    int v3, v4, v5, v6;

    if (param1 < 0) {
        v3 = v0;
        v4 = v1;
        v5 = -(param1 * 2);
        v6 = -(4 * param1);
    } else {
        v3 = (menu->unk_8C + 120) & 255;
        v4 = menu->unk_90 + 10;
        v5 = param1 * 2;

        if ((v5 + v4) > EasyChat_GetCurrentCategoryWordCount(menu->app)) {
            v5--;
        }

        v6 = 4 * param1;
    }

    for (v2 = 0; v2 < v5; v2++) {
        EasyChatWordMenu_PrintWord(menu, v4 + v2, v3);

        if (v2 & 1) {
            v3 = (v3 + 24) & 255;
        }
    }

    menu->unk_8C = v0;
    menu->unk_90 = v1;

    Window_LoadTiles(&menu->unk_10);
    ov20_021D4E38(&(menu->unk_60), menu->bgConfig, BG_LAYER_MAIN_2, 1, param1 * 24, v6);
}

BOOL ov20_021D4578(EasyChatWordMenu *menu)
{
    if (ov20_021D4E8C(&menu->unk_60)) {
        Sprite_SetDrawFlag(menu->upArrowSprite, EasyChat_CanScrollWordPickerUp(menu->app));
        Sprite_SetDrawFlag(menu->downArrowSprite, EasyChat_CanScrollWordPickerDown(menu->app));
        return 1;
    }

    return 0;
}

static void ov20_021D45AC(EasyChatWordMenu *menu, int param1)
{
    int v0, v1;

    if (param1 > 0) {
        v0 = (menu->unk_8C + 120) & 0xff;
        v1 = (v0 + param1 * 24) & 0xff;
    } else {
        v1 = menu->unk_8C;
        v0 = (v1 + param1 * 24) & 0xff;
    }

    if (v0 < v1) {
        Window_FillRectWithColor(&menu->unk_10, 0, 0, v0, 26 * 8, (v1 - v0));
    } else {
        Window_FillRectWithColor(&menu->unk_10, 0, 0, v0, 26 * 8, 256 - v0);
        Window_FillRectWithColor(&menu->unk_10, 0, 0, 0, 26 * 8, v1);
    }
}

static void ov20_021D4638(EasyChatWordMenu *menu)
{
    menu->unk_8C = 48;
    menu->unk_90 = 0;

    Bg_SetOffset(menu->bgConfig, BG_LAYER_MAIN_2, BG_OFFSET_UPDATE_SET_Y, 0);
}

static void EasyChatWordMenu_PrintWord(EasyChatWordMenu *menu, u32 index, u32 param2)
{
    EasyChat_GetWordStringAtIndex(menu->app, index, menu->string);

    if (param2 <= 240) {
        Text_AddPrinterWithParamsAndColor(&menu->unk_10, FONT_SYSTEM, menu->string, (index & 1) * 112, param2, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
    } else {
        u32 v0 = 256 - param2;

        Window_FillTilemap(&menu->unk_20, 0);
        Text_AddPrinterWithParamsAndColor(&menu->unk_20, FONT_SYSTEM, menu->string, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 0), NULL);
        Window_BlitBitmapRect(&menu->unk_10, menu->unk_20.pixels, 0, 0, 12 * 8, 2 * 8, (index & 1) * 112, param2, 12 * 8, v0);
        Window_BlitBitmapRect(&menu->unk_10, menu->unk_20.pixels, 0, v0, 12 * 8, 2 * 8, (index & 1) * 112, 0, 12 * 8, (2 * 8) - v0);
    }
}
