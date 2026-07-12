#ifndef POKEPLATINUM_EASY_CHAT_INTERFACE_H
#define POKEPLATINUM_EASY_CHAT_INTERFACE_H

#include "applications/easy_chat/main.h"
#include "applications/easy_chat/struct_ov20_021D2128_decl.h"

#include "bg_window.h"
#include "colored_arrow.h"
#include "coordinates.h"
#include "easy_chat_word_list.h"
#include "narc.h"
#include "sprite.h"
#include "string_gf.h"

typedef struct EasyChatSentenceParser {
    String *string;
    const charcode_t *iter;
    int state;
} EasyChatSentenceParser;

typedef struct EasyChatInterfaceContext {
    UnkStruct_ov20_021D2128 *unk_00;
    const EasyChatApp *app;
    const EasyChatWordList *unusedWordList;
    Window entryWindow;
    Window textWindow;
    Window yesNoMenuWindow;
    Sprite *cursorSprite;
    Sprite *rightArrowSprite;
    Sprite *leftArrowSprite;
    MessageLoader *loader;
    String *string;
    ColoredArrow *arrow;
    CoordinatesS16 wordSlotCoords[MAX_EASY_CHAT_WORDS];
    u32 wordSlotCount;
    u32 baseTile;
    EasyChatSentenceParser sentenceParser;
    u16 palettes[10][SLOTS_PER_PALETTE];
} EasyChatInterfaceContext;


enum EasyChatMessageType {
    EC_MESSAGE_TYPE_INSTRUCTIONS = 0,
    EC_MESSAGE_TYPE_PLEASE_ENTER,
    EC_MESSAGE_TYPE_CONFIRM_ANSWER,
    EC_MESSAGE_TYPE_CONFIRM_QUIT,
};

EasyChatInterfaceContext *EasyChatInterfaceContext_New(UnkStruct_ov20_021D2128 *param0, const EasyChatApp *app, const EasyChatWordList *wordList);
void EasyChatInterfaceContext_Free(EasyChatInterfaceContext *ctx);
void EasyChatInterface_Draw(EasyChatInterfaceContext *ctx, NARC *narc);
void EasyChatInterface_DrawEntryWindow(EasyChatInterfaceContext *ctx);
u32 EasyChatInterface_GetWordSlotCount(const EasyChatInterfaceContext *ctx);
void EasyChatInterface_PrintMessage(EasyChatInterfaceContext *ctx, enum EasyChatMessageType messageType);
void EasyChatInterface_StopCursorBlink(EasyChatInterfaceContext *ctx);
void EasyChatInterface_StartCursorBlink(EasyChatInterfaceContext *ctx);
void EasyChatInterface_SetCursorDrawFlag(EasyChatInterfaceContext *ctx, BOOL draw);
void EasyChatInterface_HideSentenceSelectionArrows(EasyChatInterfaceContext *ctx);
void EasyChatInterface_DrawSentenceSelectionArrows(EasyChatInterfaceContext *ctx);
void EasyChatInterface_SetCursorPosition(EasyChatInterfaceContext *ctx, int slot);
void EasyChatInterface_OpenYesNoMenu(EasyChatInterfaceContext *ctx, int selection);
void EasyChatInterface_UpdateYesNoArrow(EasyChatInterfaceContext *ctx, int selection);
void EasyChatInterface_CloseYesNoMenu(EasyChatInterfaceContext *ctx);

#endif // POKEPLATINUM_EASY_CHAT_INTERFACE_H
