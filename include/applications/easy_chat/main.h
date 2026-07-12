#ifndef POKEPLATINUM_APPLICATIONS_EASY_CHAT_MAIN_H
#define POKEPLATINUM_APPLICATIONS_EASY_CHAT_MAIN_H

#include "applications/easy_chat/defs.h"
#include "applications/easy_chat/struct_ov20_021D2128_decl.h"

#include "easy_chat_args.h"
#include "easy_chat_sentence.h"
#include "easy_chat_word_list.h"
#include "overlay_manager.h"
#include "string_gf.h"
#include "touch_screen_actions.h"

typedef struct EasyChatApp EasyChatApp;

typedef int (*EasyChatMainFunc)(EasyChatApp *easyChatApp, int *state);
typedef void (*EasyChatTaskFunc)(EasyChatApp *easyChatApp, int *state);

typedef struct {
    u8 unk_00;
    u8 unk_01;
} UnkStruct_ov20_021D1F34;

typedef struct EasyChatWordPicker {
    u16 listPos;
    u16 maxListPos;
    u16 wordCount;
    u8 cursorXPos;
    u8 cursorYPos;
    int listPosDelta;
} EasyChatWordPicker;

typedef struct EasyChatSentencePicker {
    s16 type;
    s8 id;
    s8 idsOfCurrentType;
} EasyChatSentencePicker;

typedef struct EasyChatApp {
    EasyChatArgs *args;
    u32 type;
    EasyChatSentence sentence;
    u16 words[MAX_EASY_CHAT_WORDS];
    UnkStruct_ov20_021D2128 *unk_14;
    EasyChatWordList *wordList;
    int state;
    EasyChatMainFunc mainFunc;
    EasyChatMainFunc nextMainFunc;
    int taskFuncState;
    EasyChatTaskFunc taskFunc;
    u16 pressedKeys;
    u16 heldKeysUnused;
    u16 pressedKeysRepeatable;
    int touchedButtonIndex;
    u8 padding[4];
    TouchScreenActions *buttonAction;
    int dummy;
    int dummy2;
    u16 confirmOrCancelCursorPos;
    u16 currentWordSlot;
    u16 categoryCursorPos;
    u16 prevCategoryCursorPos;
    EasyChatWordPicker wordPicker;
    EasyChatSentencePicker sentencePicker;
    u8 unk_64;
    u8 mode;
    UnkStruct_ov20_021D1F34 unk_66;
} EasyChatApp;

BOOL EasyChat_Init(ApplicationManager *appMan, int *state);
BOOL EasyChat_Main(ApplicationManager *appMan, int *state);
BOOL EasyChat_Exit(ApplicationManager *appMan, int *state);
u32 EasyChat_GetType(const EasyChatApp *easyChatApp);
u32 EasyChat_GetInstructionBankEntry(const EasyChatApp *easyChatApp);
u32 EasyChat_GetMode(const EasyChatApp *easyChatApp);
u32 EasyChat_GetSentenceType(const EasyChatApp *easyChatApp);
u16 EasyChat_GetWordAtSlot(const EasyChatApp *easyChatApp, int slot);
String *EasyChat_GetSentenceTemplateString(const EasyChatApp *easyChatApp, enum HeapID heapID);
u32 EasyChat_GetCurrentWordSlot(const EasyChatApp *easyChatApp);
u32 ov20_021D1FD4(const EasyChatApp *easyChatApp);
u32 EasyChat_GetCategoryCursorPos(const EasyChatApp *easyChatApp);
u32 EasyChat_GetCurrentCategoryWordCount(const EasyChatApp *easyChatApp);
void EasyChat_GetWordStringAtIndex(const EasyChatApp *easyChatApp, u32 index, String *out);
u32 EasyChat_GetWordPickerCursorPos(const EasyChatApp *easyChatApp);
int EasyChat_GetWordPickerScrollDistance(const EasyChatApp *easyChatApp);
BOOL EasyChat_CanScrollWordPickerUp(const EasyChatApp *easyChatApp);
BOOL EasyChat_CanScrollWordPickerDown(const EasyChatApp *easyChatApp);
int EasyChat_GetFrame(const EasyChatApp *easyChatApp);
u32 ov20_021D208C(const EasyChatApp *easyChatApp);

#endif // POKEPLATINUM_APPLICATIONS_EASY_CHAT_MAIN_H
