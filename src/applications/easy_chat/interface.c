#include "applications/easy_chat/interface.h"

#include <nitro.h>

#include "constants/charcode.h"
#include "constants/items.h"

#include "applications/easy_chat/main.h"
#include "applications/easy_chat/ov20_021D2098.h"
#include "applications/easy_chat/struct_ov20_021D2128_decl.h"

#include "bg_window.h"
#include "charcode.h"
#include "colored_arrow.h"
#include "coordinates.h"
#include "easy_chat_word_list.h"
#include "easy_chat_words.h"
#include "font.h"
#include "graphics.h"
#include "heap.h"
#include "message.h"
#include "narc.h"
#include "render_window.h"
#include "sprite.h"
#include "string_gf.h"
#include "string_template.h"
#include "text.h"

#include "res/graphics/windows/pl_winframe.naix"
#include "res/text/bank/easy_chat.h"

#define EASY_CHAT_INTERFACE_LINE_HEIGHT 16

#define EASY_CHAT_WORD_SLOT_WIDTH 96

#define WHOLE_WINDOW_CURSOR_X 128
#define WHOLE_WINDOW_CURSOR_Y 24

enum StringParseState {
    SENTENCE_PARSE_STATE_NORMAL = 0,
    SENTENCE_PARSE_STATE_FORMAT_ARG,
    SENTENCE_PARSE_STATE_LINE_BREAK,
    SENTENCE_PARSE_STATE_EOS,
};

static void EasyChatInterface_LoadPalettes(EasyChatInterfaceContext *ctx, NARC *narc);
static void EasyChatInterface_InitWordSlots(EasyChatInterfaceContext *ctx);
static void EasyChatInterface_InitSprites(EasyChatInterfaceContext *ctx);
static u32 EasyChatInterface_DrawSentence(EasyChatInterfaceContext *ctx);
static void EasyChatSentenceParser_Init(EasyChatSentenceParser *sentenceParser, EasyChatInterfaceContext *ctx);
static void EasyChatSentenceParser_Free(EasyChatSentenceParser *sentenceParser);
static int EasyChatInterface_ParseSentence(EasyChatSentenceParser *sentenceParser, String *out);
static void GetCursorCoordsFromSlotCoords(const CoordinatesS16 *slotCoords, CoordinatesS16 *out);
static void EasyChatInterface_DrawWordSlot(Window *window, const CoordinatesS16 *slotCoords);
static void EasyChatInterface_PrintWord(EasyChatInterfaceContext *ctx, Window *window, const CoordinatesS16 *slotCoords, u16 word);
static void EasyChatInterface_SetCursorBlink(EasyChatInterfaceContext *ctx, BOOL blink);

EasyChatInterfaceContext *EasyChatInterfaceContext_New(UnkStruct_ov20_021D2128 *param0, const EasyChatApp *app, const EasyChatWordList *wordList)
{
    EasyChatInterfaceContext *ctx = Heap_Alloc(HEAP_ID_35, sizeof(EasyChatInterfaceContext));

    ctx->unk_00 = param0;
    ctx->app = app;
    ctx->unusedWordList = wordList;
    ctx->cursorSprite = NULL;
    ctx->rightArrowSprite = NULL;
    ctx->leftArrowSprite = NULL;
    ctx->string = String_Init(128, HEAP_ID_35);
    ctx->loader = MessageLoader_Init(MSG_LOADER_PRELOAD_ENTIRE_BANK, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_EASY_CHAT, HEAP_ID_35);
    ctx->arrow = ColoredArrow_New(HEAP_ID_35);

    return ctx;
}

void EasyChatInterfaceContext_Free(EasyChatInterfaceContext *ctx)
{
    if (ctx->arrow) {
        ColoredArrow_Free(ctx->arrow);
    }

    if (ctx->cursorSprite) {
        Sprite_Delete(ctx->cursorSprite);
    }

    if (ctx->rightArrowSprite) {
        Sprite_Delete(ctx->rightArrowSprite);
    }

    if (ctx->leftArrowSprite) {
        Sprite_Delete(ctx->leftArrowSprite);
    }

    if (ctx->loader) {
        MessageLoader_Free(ctx->loader);
    }

    if (ctx->string) {
        String_Free(ctx->string);
    }

    Window_Remove(&ctx->entryWindow);
    Window_Remove(&ctx->textWindow);
    Window_Remove(&ctx->yesNoMenuWindow);
    Heap_Free(ctx);
}

void EasyChatInterface_Draw(EasyChatInterfaceContext *ctx, NARC *narc)
{
    BgConfig *bgConfig = ov20_021D2E04(ctx->unk_00);

    EasyChatInterface_LoadPalettes(ctx, narc);
    Graphics_LoadTilemapToBgLayerFromOpenNARC(narc, 0, bgConfig, BG_LAYER_MAIN_0, 0, 0, TRUE, HEAP_ID_35);

    u32 baseTile = Graphics_LoadTilesToBgLayerFromOpenNARC(narc, 1, bgConfig, 0, 0, 0, TRUE, HEAP_ID_35) / TILE_SIZE_4BPP;

    Window_Add(bgConfig, &ctx->entryWindow, BG_LAYER_MAIN_0, 3, 1, 27, 4, 0, baseTile);
    baseTile += 27 * 4;

    Window_Add(bgConfig, &ctx->textWindow, BG_LAYER_MAIN_0, 2, 21, 27, 2, 11, baseTile);
    baseTile += 27 * 2;

    Window_Add(bgConfig, &ctx->yesNoMenuWindow, BG_LAYER_MAIN_0, 23, 15, 8, 4, 11, baseTile);
    baseTile += 8 * 4;

    Graphics_LoadTilesToBgLayer(NARC_INDEX_GRAPHIC__PL_WINFRAME, standard_system_NCGR, bgConfig, BG_LAYER_MAIN_0, baseTile, 0, FALSE, HEAP_ID_35);
    ctx->baseTile = baseTile;
    baseTile += STANDARD_WINDOW_TILE_COUNT;

    Graphics_LoadPalette(NARC_INDEX_GRAPHIC__PL_WINFRAME, standard_system_NCLR, PAL_LOAD_MAIN_BG, PLTT_OFFSET(14), PALETTE_SIZE_BYTES, HEAP_ID_35);
    LoadMessageBoxGraphics(bgConfig, BG_LAYER_MAIN_0, baseTile, 15, EasyChat_GetFrame(ctx->app), HEAP_ID_35);
    Window_DrawMessageBox(&ctx->textWindow, baseTile, 15);
    Window_PutToTilemap(&ctx->entryWindow);
    Window_PutToTilemap(&ctx->textWindow);

    EasyChatInterface_InitWordSlots(ctx);
    EasyChatInterface_DrawEntryWindow(ctx);
    EasyChatInterface_PrintMessage(ctx, EC_MESSAGE_TYPE_INSTRUCTIONS);
    EasyChatInterface_InitSprites(ctx);

    Bg_CopyTilemapBufferToVRAM(bgConfig, BG_LAYER_MAIN_0);
}

static void EasyChatInterface_LoadPalettes(EasyChatInterfaceContext *ctx, NARC *narc)
{
    Graphics_LoadPaletteFromOpenNARC(narc, 6, PAL_LOAD_MAIN_BG, 0, 14 * PALETTE_SIZE_BYTES, HEAP_ID_35);

    NNSG2dPaletteData *plttData;
    void *nclrBuffer = Graphics_GetPlttDataFromOpenNARC(narc, 6, &plttData, HEAP_ID_35);

    MI_CpuCopy16(plttData->pRawData, ctx->palettes, sizeof(ctx->palettes));
    DC_FlushRange(ctx->palettes, sizeof(ctx->palettes));

    Heap_Free(nclrBuffer);
}

static void EasyChatInterface_LoadEntryWindowPalette(EasyChatInterfaceContext *ctx)
{
    if (EasyChat_GetType(ctx->app) == EASY_CHAT_TYPE_SENTENCE) {
        GX_LoadBGPltt(ctx->palettes[1 + EasyChat_GetSentenceType(ctx->app)], 0, PALETTE_SIZE_BYTES);
    } else {
        GX_LoadBGPltt(ctx->palettes[0], 0, PALETTE_SIZE_BYTES);
    }
}

static void EasyChatInterface_InitWordSlots(EasyChatInterfaceContext *ctx)
{
    switch (EasyChat_GetType(ctx->app)) {
    case EASY_CHAT_TYPE_ONE_WORD:
        ctx->wordSlotCoords[0].x = 104;
        ctx->wordSlotCoords[0].y = 16;
        ctx->wordSlotCount = 1;
        break;
    case EASY_CHAT_TYPE_TWO_WORDS:
        ctx->wordSlotCoords[0].x = 48;
        ctx->wordSlotCoords[0].y = 16;
        ctx->wordSlotCoords[1].x = 160;
        ctx->wordSlotCoords[1].y = 16;
        ctx->wordSlotCount = 2;
        break;
    case EASY_CHAT_TYPE_SENTENCE:
        ctx->wordSlotCount = 0;
        break;
    }
}

static void EasyChatInterface_InitSprites(EasyChatInterfaceContext *ctx)
{
    SpriteResourcesHeader v0;
    CoordinatesS16 coords;

    if (ctx->wordSlotCount != 0) {
        GetCursorCoordsFromSlotCoords(&ctx->wordSlotCoords[0], &coords);
    } else {
        coords.x = WHOLE_WINDOW_CURSOR_X;
        coords.y = WHOLE_WINDOW_CURSOR_Y;
    }

    ov20_021D2E0C(ctx->unk_00, &v0, 0, 0);
    ctx->cursorSprite = ov20_021D2E50(ctx->unk_00, &v0, coords.x, coords.y, 0, NNS_G2D_VRAM_TYPE_2DMAIN);

    EasyChatInterface_SetCursorBlink(ctx, TRUE);

    ctx->rightArrowSprite = ov20_021D2E50(ctx->unk_00, &v0, 6, 24, 1, NNS_G2D_VRAM_TYPE_2DMAIN);
    Sprite_SetAnim(ctx->rightArrowSprite, 13);

    ctx->leftArrowSprite = ov20_021D2E50(ctx->unk_00, &v0, 250, 24, 1, NNS_G2D_VRAM_TYPE_2DMAIN);
    Sprite_SetAnim(ctx->leftArrowSprite, 12);

    if (EasyChat_GetType(ctx->app) != EASY_CHAT_TYPE_SENTENCE) {
        Sprite_SetDrawFlag(ctx->leftArrowSprite, FALSE);
        Sprite_SetDrawFlag(ctx->rightArrowSprite, FALSE);
    }
}

void EasyChatInterface_DrawEntryWindow(EasyChatInterfaceContext *ctx)
{
    EasyChatInterface_LoadEntryWindowPalette(ctx);
    Window_FillTilemap(&ctx->entryWindow, 13);

    switch (EasyChat_GetType(ctx->app)) {
    case EASY_CHAT_TYPE_ONE_WORD:
        EasyChatInterface_DrawWordSlot(&ctx->entryWindow, &ctx->wordSlotCoords[0]);
        EasyChatInterface_PrintWord(ctx, &ctx->entryWindow, &ctx->wordSlotCoords[0], EasyChat_GetWordAtSlot(ctx->app, 0));
        break;
    case EASY_CHAT_TYPE_TWO_WORDS:
        EasyChatInterface_DrawWordSlot(&ctx->entryWindow, &ctx->wordSlotCoords[0]);
        EasyChatInterface_DrawWordSlot(&ctx->entryWindow, &ctx->wordSlotCoords[1]);
        EasyChatInterface_PrintWord(ctx, &ctx->entryWindow, &ctx->wordSlotCoords[0], EasyChat_GetWordAtSlot(ctx->app, 0));
        EasyChatInterface_PrintWord(ctx, &ctx->entryWindow, &ctx->wordSlotCoords[1], EasyChat_GetWordAtSlot(ctx->app, 1));
        break;
    case EASY_CHAT_TYPE_SENTENCE:
        ctx->wordSlotCount = EasyChatInterface_DrawSentence(ctx);
        break;
    }

    Window_LoadTiles(&ctx->entryWindow);
}

static u32 EasyChatInterface_DrawSentence(EasyChatInterfaceContext *ctx)
{
    // overwritten below, this is to ensure string has the correct size
    String *string = EasyChat_GetSentenceTemplateString(ctx->app, HEAP_ID_35);
    int x, y, wordIndex;
    x = y = wordIndex = 0;
    BOOL loop = TRUE;

    EasyChatSentenceParser_Init(&ctx->sentenceParser, ctx);

    while (loop) {
        switch (EasyChatInterface_ParseSentence(&ctx->sentenceParser, string)) {
        case SENTENCE_PARSE_STATE_NORMAL:
            Text_AddPrinterWithParamsAndColor(&ctx->entryWindow, FONT_MESSAGE, string, x, y, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(3, 4, 13), NULL);
            x += Font_CalcStringWidth(FONT_MESSAGE, string, 0);
            break;
        case SENTENCE_PARSE_STATE_FORMAT_ARG:
            x += 2;
            ctx->wordSlotCoords[wordIndex].x = x + EASY_CHAT_WORD_SLOT_WIDTH / 2;
            ctx->wordSlotCoords[wordIndex].y = y + EASY_CHAT_INTERFACE_LINE_HEIGHT / 2;
            EasyChatInterface_DrawWordSlot(&ctx->entryWindow, &ctx->wordSlotCoords[wordIndex]);
            u16 word = EasyChat_GetWordAtSlot(ctx->app, wordIndex);

            if (word != WORD_NONE) {
                EasyChatInterface_PrintWord(ctx, &ctx->entryWindow, &ctx->wordSlotCoords[wordIndex], word);
            }

            wordIndex++;
            x += (2 + EASY_CHAT_WORD_SLOT_WIDTH);
            break;
        case SENTENCE_PARSE_STATE_LINE_BREAK:
            y += EASY_CHAT_INTERFACE_LINE_HEIGHT;
            x = 0;
            break;
        case SENTENCE_PARSE_STATE_EOS:
            loop = FALSE;
            break;
        }
    }

    EasyChatSentenceParser_Free(&ctx->sentenceParser);
    String_Free(string);

    return wordIndex;
}

static void EasyChatSentenceParser_Init(EasyChatSentenceParser *sentenceParser, EasyChatInterfaceContext *ctx)
{
    sentenceParser->string = EasyChat_GetSentenceTemplateString(ctx->app, HEAP_ID_35);
    sentenceParser->iter = String_GetData(sentenceParser->string);

    if (*sentenceParser->iter == CHAR_FORMAT_ARG) {
        sentenceParser->state = SENTENCE_PARSE_STATE_FORMAT_ARG;
    } else {
        sentenceParser->state = SENTENCE_PARSE_STATE_NORMAL;
    }
}

static void EasyChatSentenceParser_Free(EasyChatSentenceParser *sentenceParser)
{
    String_Free(sentenceParser->string);
}

static int EasyChatInterface_ParseSentence(EasyChatSentenceParser *sentenceParser, String *out)
{
    const charcode_t *start = sentenceParser->iter;
    int ret;

    switch (sentenceParser->state) {
    case SENTENCE_PARSE_STATE_NORMAL:
        while (sentenceParser->state == SENTENCE_PARSE_STATE_NORMAL) {
            switch (*sentenceParser->iter) {
            case CHAR_CR:
                sentenceParser->state = SENTENCE_PARSE_STATE_LINE_BREAK;
                break;
            case CHAR_EOS:
                sentenceParser->state = SENTENCE_PARSE_STATE_EOS;
                break;
            case CHAR_FORMAT_ARG:
                sentenceParser->state = SENTENCE_PARSE_STATE_FORMAT_ARG;
                break;
            default:
                sentenceParser->iter++;
                break;
            }
        }

        String_CopyNumChars(out, start, (sentenceParser->iter - start) + 1);
        return SENTENCE_PARSE_STATE_NORMAL;
    case SENTENCE_PARSE_STATE_FORMAT_ARG:
        sentenceParser->iter = CharCode_SkipFormatArg(sentenceParser->iter);
        ret = SENTENCE_PARSE_STATE_FORMAT_ARG;
        break;
    case SENTENCE_PARSE_STATE_LINE_BREAK:
        sentenceParser->iter++;
        ret = SENTENCE_PARSE_STATE_LINE_BREAK;
        break;
    case SENTENCE_PARSE_STATE_EOS:
    default:
        return SENTENCE_PARSE_STATE_EOS;
    }

    switch (*sentenceParser->iter) {
    case CHAR_CR:
        sentenceParser->state = SENTENCE_PARSE_STATE_LINE_BREAK;
        break;
    case CHAR_EOS:
        sentenceParser->state = SENTENCE_PARSE_STATE_EOS;
        break;
    case CHAR_FORMAT_ARG:
        sentenceParser->state = SENTENCE_PARSE_STATE_FORMAT_ARG;
        break;
    default:
        sentenceParser->state = SENTENCE_PARSE_STATE_NORMAL;
        break;
    }

    return ret;
}

static void GetWordSlotOriginCoordsFromCentered(const CoordinatesS16 *slotCoords, CoordinatesS16 *out)
{
    out->x = slotCoords->x - EASY_CHAT_WORD_SLOT_WIDTH / 2;
    out->y = slotCoords->y - EASY_CHAT_INTERFACE_LINE_HEIGHT / 2;
}

static void GetCursorCoordsFromSlotCoords(const CoordinatesS16 *slotCoords, CoordinatesS16 *out)
{
    out->x = slotCoords->x + 3 * 8;
    out->y = slotCoords->y + 1 * 8;
}

static void EasyChatInterface_DrawWordSlot(Window *window, const CoordinatesS16 *slotCoords)
{
    CoordinatesS16 coords;
    GetWordSlotOriginCoordsFromCentered(slotCoords, &coords);

    Window_FillRectWithColor(window, 14, coords.x, coords.y, EASY_CHAT_WORD_SLOT_WIDTH, EASY_CHAT_INTERFACE_LINE_HEIGHT);
}

static void EasyChatInterface_PrintWord(EasyChatInterfaceContext *ctx, Window *window, const CoordinatesS16 *slotCoords, u16 word)
{
    if (word != WORD_NONE) {
        CoordinatesS16 coords;
        GetWordSlotOriginCoordsFromCentered(slotCoords, &coords);
        EasyChatWord_ToString(word, ctx->string);

        u32 unused = Font_CalcStringWidth(FONT_MESSAGE, ctx->string, 0);

        Text_AddPrinterWithParamsAndColor(window, FONT_MESSAGE, ctx->string, coords.x, coords.y, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(5, 6, 14), NULL);
    }
}

u32 EasyChatInterface_GetWordSlotCount(const EasyChatInterfaceContext *ctx)
{
    return ctx->wordSlotCount;
}

void EasyChatInterface_PrintMessage(EasyChatInterfaceContext *ctx, enum EasyChatMessageType messageType)
{
    Window_FillTilemap(&ctx->textWindow, 9);

    switch (messageType) {
    case EC_MESSAGE_TYPE_INSTRUCTIONS: {
        // effectively unused because none of the messages in this bank are templates
        StringTemplate *template = StringTemplate_New(2, 60, HEAP_ID_SYSTEM);
        String *string = String_Init(300, HEAP_ID_SYSTEM);

        StringTemplate_SetBagPocketName(template, 0, POCKET_ITEMS);
        MessageLoader_GetString(ctx->loader, EasyChat_GetInstructionBankEntry(ctx->app), ctx->string);
        StringTemplate_Format(template, string, ctx->string);
        Text_AddPrinterWithParamsAndColor(&ctx->textWindow, FONT_MESSAGE, string, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 9), NULL);

        String_Free(string);
        StringTemplate_Free(template);
    } break;
    case EC_MESSAGE_TYPE_CONFIRM_ANSWER:
        MessageLoader_GetString(ctx->loader, EasyChat_Text_IsThisYourAnswer, ctx->string);
        Text_AddPrinterWithParamsAndColor(&ctx->textWindow, FONT_MESSAGE, ctx->string, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 9), NULL);
        break;
    case EC_MESSAGE_TYPE_PLEASE_ENTER:
        MessageLoader_GetString(ctx->loader, EasyChat_Text_PleaseEnterPhraseOrWord, ctx->string);
        Text_AddPrinterWithParamsAndColor(&ctx->textWindow, FONT_MESSAGE, ctx->string, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 9), NULL);
        break;
    case EC_MESSAGE_TYPE_CONFIRM_QUIT:
        MessageLoader_GetString(ctx->loader, EasyChat_Text_QuitWithoutDoingAnything, ctx->string);
        Text_AddPrinterWithParamsAndColor(&ctx->textWindow, FONT_MESSAGE, ctx->string, 0, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 9), NULL);
        break;
    }

    Window_LoadTiles(&ctx->textWindow);
}

void EasyChatInterface_StopCursorBlink(EasyChatInterfaceContext *ctx)
{
    EasyChatInterface_SetCursorBlink(ctx, FALSE);
}

void EasyChatInterface_StartCursorBlink(EasyChatInterfaceContext *ctx)
{
    EasyChatInterface_SetCursorBlink(ctx, TRUE);
}

void EasyChatInterface_SetCursorDrawFlag(EasyChatInterfaceContext *ctx, BOOL draw)
{
    Sprite_SetDrawFlag(ctx->cursorSprite, draw);
    EasyChatInterface_SetCursorBlink(ctx, TRUE);
}

void EasyChatInterface_HideSentenceSelectionArrows(EasyChatInterfaceContext *ctx)
{
    if (EasyChat_GetType(ctx->app) == EASY_CHAT_TYPE_SENTENCE) {
        Sprite_SetDrawFlag(ctx->rightArrowSprite, FALSE);
        Sprite_SetDrawFlag(ctx->leftArrowSprite, FALSE);
    }
}

void EasyChatInterface_DrawSentenceSelectionArrows(EasyChatInterfaceContext *ctx)
{
    if (EasyChat_GetType(ctx->app) == EASY_CHAT_TYPE_SENTENCE) {
        Sprite_SetDrawFlag(ctx->rightArrowSprite, TRUE);
        Sprite_SetDrawFlag(ctx->leftArrowSprite, TRUE);

        Sprite_SetAnim(ctx->rightArrowSprite, 13);
        Sprite_SetAnim(ctx->leftArrowSprite, 12);
    }
}

void EasyChatInterface_SetCursorPosition(EasyChatInterfaceContext *ctx, int slot)
{
    VecFx32 position;

    if (ctx->wordSlotCount != 0) {
        CoordinatesS16 coords;
        GetCursorCoordsFromSlotCoords(&ctx->wordSlotCoords[slot], &coords);
        
        position.x = coords.x * FX32_ONE;
        position.y = coords.y * FX32_ONE;
        position.z = 0;
    } else {
        position.x = WHOLE_WINDOW_CURSOR_X * FX32_ONE;
        position.y = WHOLE_WINDOW_CURSOR_Y * FX32_ONE;
        position.z = 0;

        Sprite_SetPosition(ctx->cursorSprite, &position);
    }

    Sprite_SetPosition(ctx->cursorSprite, &position);
    EasyChatInterface_SetCursorBlink(ctx, TRUE);
}

static void EasyChatInterface_SetCursorBlink(EasyChatInterfaceContext *ctx, BOOL blink)
{
    if (ctx->wordSlotCount != 0) {
        if (blink) {
            Sprite_SetAnim(ctx->cursorSprite, 0);
        } else {
            Sprite_SetAnim(ctx->cursorSprite, 1);
        }
    } else {
        if (blink) {
            Sprite_SetAnim(ctx->cursorSprite, 14);
        } else {
            Sprite_SetAnim(ctx->cursorSprite, 15);
        }
    }
}

void EasyChatInterface_OpenYesNoMenu(EasyChatInterfaceContext *ctx, int selection)
{
    Window_FillTilemap(&ctx->yesNoMenuWindow, 9);

    MessageLoader_GetString(ctx->loader, EasyChat_Text_Yes, ctx->string);
    Text_AddPrinterWithParamsAndColor(&ctx->yesNoMenuWindow, FONT_SYSTEM, ctx->string, 14, 0, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 9), NULL);

    MessageLoader_GetString(ctx->loader, EasyChat_Text_No, ctx->string);
    Text_AddPrinterWithParamsAndColor(&ctx->yesNoMenuWindow, FONT_SYSTEM, ctx->string, 14, EASY_CHAT_INTERFACE_LINE_HEIGHT, TEXT_SPEED_NO_TRANSFER, TEXT_COLOR(1, 2, 9), NULL);

    Window_DrawStandardFrame(&ctx->yesNoMenuWindow, FALSE, ctx->baseTile, 14);
    ColoredArrow_Print(ctx->arrow, &ctx->yesNoMenuWindow, 0, selection * EASY_CHAT_INTERFACE_LINE_HEIGHT);

    Window_CopyToVRAM(&ctx->yesNoMenuWindow);
}

void EasyChatInterface_UpdateYesNoArrow(EasyChatInterfaceContext *ctx, int selection)
{
    Window_FillRectWithColor(&ctx->yesNoMenuWindow, 9, 0, 0, 14, 4 * TILE_HEIGHT_PIXELS);
    ColoredArrow_Print(ctx->arrow, &ctx->yesNoMenuWindow, 0, selection * EASY_CHAT_INTERFACE_LINE_HEIGHT);
}

void EasyChatInterface_CloseYesNoMenu(EasyChatInterfaceContext *ctx)
{
    Window_EraseStandardFrame(&ctx->yesNoMenuWindow, FALSE);
    Window_ClearAndCopyToVRAM(&ctx->yesNoMenuWindow);
}
