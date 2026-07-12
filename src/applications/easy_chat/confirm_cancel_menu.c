#include "applications/easy_chat/confirm_cancel_menu.h"

#include <nitro.h>

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
#include "text.h"

#include "res/text/bank/easy_chat_confirm_cancel.h"

static void EasyChatConfirmCancelMenu_PrintButtonLabel(BgConfig *bgConfig, const WindowTemplate *param1, u32 param2);
static void EasyChatConfirmCancelMenu_InitCursorSprite(EasyChatConfirmCancelMenu *param0);

EasyChatConfirmCancelMenu *EasyChatConfirmCancelMenu_New(UnkStruct_ov20_021D2128 *param0, const EasyChatApp *app, const EasyChatWordList *wordList)
{
    EasyChatConfirmCancelMenu *menu = Heap_Alloc(HEAP_ID_35, sizeof(EasyChatConfirmCancelMenu));

    menu->unk_00 = param0;
    menu->unusedApp = app;
    menu->unusedWordList = wordList;
    menu->cursorSprite = NULL;

    return menu;
}

void EasyChatConfirmCancelMenu_Free(EasyChatConfirmCancelMenu *menu)
{
    if (menu->cursorSprite) {
        Sprite_Delete(menu->cursorSprite);
    }

    Heap_Free(menu);
}

void EasyChatConfirmCancelMenu_Draw(EasyChatConfirmCancelMenu *menu, NARC *narc)
{
    static const WindowTemplate confirmWindow = {
        .bgLayer = BG_LAYER_MAIN_3,
        .tilemapLeft = 3,
        .tilemapTop = 6,
        .width = 10,
        .height = 2,
        .palette = 13,
        .baseTile = 64
    };
    
    static const WindowTemplate cancelWindow = {
        .bgLayer = BG_LAYER_MAIN_3,
        .tilemapLeft = 19,
        .tilemapTop = 6,
        .width = 10,
        .height = 2,
        .palette = 13,
        .baseTile = 84
    };

    BgConfig *bgConfig = ov20_021D2E04(menu->unk_00);

    Graphics_LoadTilemapToBgLayerFromOpenNARC(narc, 4, bgConfig, BG_LAYER_MAIN_3, 0, 0, TRUE, HEAP_ID_35);
    Graphics_LoadTilesToBgLayerFromOpenNARC(narc, 5, bgConfig, BG_LAYER_MAIN_3, 0, 0, TRUE, HEAP_ID_35);

    EasyChatConfirmCancelMenu_PrintButtonLabel(bgConfig, &confirmWindow, EasyChatConfirmCancel_Text_Confirm);
    EasyChatConfirmCancelMenu_PrintButtonLabel(bgConfig, &cancelWindow, EasyChatConfirmCancel_Text_Cancel);
    EasyChatConfirmCancelMenu_InitCursorSprite(menu);

    Bg_CopyTilemapBufferToVRAM(bgConfig, BG_LAYER_MAIN_3);
}

static void EasyChatConfirmCancelMenu_PrintButtonLabel(BgConfig *bgConfig, const WindowTemplate *template, u32 bankEntry)
{
    Window window;
    Window_AddFromTemplate(bgConfig, &window, template);
    Window_PutToTilemap(&window);
    Window_FillTilemap(&window, 14);

    String *string = MessageBank_GetNewStringFromNARC(NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_EASY_CHAT_CONFIRM_CANCEL, bankEntry, HEAP_ID_35);
    u32 xOffset = (template->width * TILE_WIDTH_PIXELS - Font_CalcStringWidth(FONT_SYSTEM, string, 0)) / 2;

    Text_AddPrinterWithParamsAndColor(&window, FONT_SYSTEM, string, xOffset, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 14), NULL);
    Window_LoadTiles(&window);
    String_Free(string);
    Window_Remove(&window);
}

static void EasyChatConfirmCancelMenu_InitCursorSprite(EasyChatConfirmCancelMenu *menu)
{
    SpriteResourcesHeader v0;

    ov20_021D2E0C(menu->unk_00, &v0, 0, 3);
    menu->cursorSprite = ov20_021D2E50(menu->unk_00, &v0, 64, 56, 5, NNS_G2D_VRAM_TYPE_2DMAIN);

    Sprite_SetAnim(menu->cursorSprite, 2);
    Sprite_SetDrawFlag(menu->cursorSprite, FALSE);
}

void EasyChatConfirmCancelMenu_StopCursorBlink(EasyChatConfirmCancelMenu *menu)
{
    Sprite_SetAnim(menu->cursorSprite, 3);
}

void EasyChatConfirmCancelMenu_StartCursorBlink(EasyChatConfirmCancelMenu *menu)
{
    Sprite_SetAnim(menu->cursorSprite, 2);
}

void EasyChatConfirmCancelMenu_SetCursorDrawFlag(EasyChatConfirmCancelMenu *menu, BOOL draw)
{
    Sprite_SetDrawFlag(menu->cursorSprite, draw);
}

BOOL EasyChatConfirmCancelMenu_GetCursorDrawFlag(EasyChatConfirmCancelMenu *menu)
{
    return Sprite_GetDrawFlag(menu->cursorSprite);
}

void EasyChatConfirmCancelMenu_SetCursorPosition(EasyChatConfirmCancelMenu *menu, int selection)
{
    VecFx32 position;

    position.z = 0;

    switch (selection) {
    case 0:
    default:
        position.x = 64 * FX32_ONE;
        position.y = 56 * FX32_ONE;
        break;
    case 1:
        position.x = 192 * FX32_ONE;
        position.y = 56 * FX32_ONE;
        break;
    }

    Sprite_SetPosition(menu->cursorSprite, &position);
    Sprite_SetAnim(menu->cursorSprite, 2);
}

void EasyChatConfirmCancelMenu_Hide(EasyChatConfirmCancelMenu *menu)
{
    Bg_SetOffset(ov20_021D2E04(menu->unk_00), BG_LAYER_MAIN_3, BG_OFFSET_UPDATE_SET_Y, 64);
}

void EasyChatConfirmCancelMenu_Show(EasyChatConfirmCancelMenu *menu)
{
    Bg_SetOffset(ov20_021D2E04(menu->unk_00), BG_LAYER_MAIN_3, BG_OFFSET_UPDATE_SET_Y, 0);
}
