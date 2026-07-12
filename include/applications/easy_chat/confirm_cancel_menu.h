#ifndef POKEPLATINUM_EASY_CHAT_CONFIRM_CANCEL_MENU_H
#define POKEPLATINUM_EASY_CHAT_CONFIRM_CANCEL_MENU_H

#include "applications/easy_chat/main.h"
#include "applications/easy_chat/struct_ov20_021D2128_decl.h"

#include "easy_chat_word_list.h"
#include "narc.h"

typedef struct EasyChatConfirmCancelMenu {
    UnkStruct_ov20_021D2128 *unk_00;
    const EasyChatApp *unusedApp;
    const EasyChatWordList *unusedWordList;
    Sprite *cursorSprite;
} EasyChatConfirmCancelMenu;

EasyChatConfirmCancelMenu *EasyChatConfirmCancelMenu_New(UnkStruct_ov20_021D2128 *param0, const EasyChatApp *app, const EasyChatWordList *wordList);
void EasyChatConfirmCancelMenu_Free(EasyChatConfirmCancelMenu *menu);
void EasyChatConfirmCancelMenu_Draw(EasyChatConfirmCancelMenu *menu, NARC *narc);
void EasyChatConfirmCancelMenu_StopCursorBlink(EasyChatConfirmCancelMenu *menu);
void EasyChatConfirmCancelMenu_StartCursorBlink(EasyChatConfirmCancelMenu *menu);
void EasyChatConfirmCancelMenu_SetCursorDrawFlag(EasyChatConfirmCancelMenu *menu, BOOL draw);
BOOL EasyChatConfirmCancelMenu_GetCursorDrawFlag(EasyChatConfirmCancelMenu *menu);
void EasyChatConfirmCancelMenu_SetCursorPosition(EasyChatConfirmCancelMenu *menu, int selection);
void EasyChatConfirmCancelMenu_Hide(EasyChatConfirmCancelMenu *menu);
void EasyChatConfirmCancelMenu_Show(EasyChatConfirmCancelMenu *menu);

#endif // POKEPLATINUM_EASY_CHAT_CONFIRM_CANCEL_MENU_H
