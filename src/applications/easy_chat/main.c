#include "applications/easy_chat/main.h"

#include <nitro.h>

#include "applications/easy_chat/abc_mode.h"
#include "applications/easy_chat/defs.h"
#include "applications/easy_chat/ov20_021D2098.h"
#include "applications/easy_chat/struct_ov20_021D2128_decl.h"

#include "easy_chat_args.h"
#include "easy_chat_sentence.h"
#include "easy_chat_word_list.h"
#include "easy_chat_words.h"
#include "heap.h"
#include "overlay_manager.h"
#include "sound.h"
#include "sound_playback.h"
#include "string_gf.h"
#include "system.h"
#include "touch_screen.h"
#include "touch_screen_actions.h"

enum EasyChatTouchButton {
    TOUCH_BUTTON_GROUP_MODE = 0,
    TOUCH_BUTTON_ABC_MODE,
    TOUCH_BUTTON_PAGE_UP,
    TOUCH_BUTTON_PAGE_DOWN,
    TOUCH_BUTTON_NONE,
};

#define EC_JOY_NEW(buttons)    (easyChatApp->pressedKeys & (buttons))
#define EC_JOY_REPEAT(buttons) (easyChatApp->pressedKeysRepeatable & (buttons))

static EasyChatApp *EasyChatApp_New(ApplicationManager *appMan);
static void EasyChatSentencePicker_Init(EasyChatSentencePicker *sentencePicker, EasyChatSentence *sentence);
static void EasyChat_FreeAppData(EasyChatApp *easyChatApp, ApplicationManager *appMan);
static int EasyChat_Main_Initial(EasyChatApp *easyChatApp, int *param1);
static int EasyChat_Main_OneWord(EasyChatApp *easyChatApp, int *param1);
static int EasyChat_Main_TwoWords(EasyChatApp *easyChatApp, int *param1);
static int EasyChat_Main_Sentence(EasyChatApp *easyChatApp, int *param1);
static int EasyChat_Main_SelectConfirmOrCancel(EasyChatApp *easyChatApp, int *param1);
static int EasyChat_Main_SelectCategory(EasyChatApp *easyChatApp, int *param1);
static BOOL EasyChat_IsCurrentCategoryNonEmpty(EasyChatApp *easyChatApp);
static BOOL EasyChat_HandleCategoryCursorMovement(EasyChatApp *easyChatApp);
static BOOL EasyChat_HandleGroupModeCursorMovement(EasyChatApp *easyChatApp);
static BOOL EasyChat_HandleABCModeCursorMovement(EasyChatApp *easyChatApp);
static void EasyChatWordPicker_Init(EasyChatWordPicker *wordPicker, EasyChatApp *easyChatApp);
static int EasyChat_Main_SelectWord(EasyChatApp *easyChatApp, int *param1);
static int EasyChat_HandleSelectWordInput(EasyChatWordPicker *wordPicker, u16 param1);
static int EasyChatWordPicker_PageUp(EasyChatWordPicker *wordPicker);
static int EasyChatWordPicker_PageDown(EasyChatWordPicker *wordPicker);
static BOOL EasyChat_SetSelectedWord(EasyChatApp *easyChatApp);
static void EasyChat_SetTaskFunc(EasyChatApp *easyChatApp, EasyChatTaskFunc param1);
static void ov20_021D1C5C(EasyChatApp *easyChatApp, int *param1);
static void ov20_021D1C90(EasyChatApp *easyChatApp, int *param1);
static void ov20_021D1DBC(EasyChatApp *easyChatApp, int *param1);
static BOOL ov20_021D1E70(EasyChatApp *easyChatApp);
static BOOL EasyChat_IsEntryComplete(EasyChatApp *easyChatApp);
static void ov20_021D1ED4(UnkStruct_ov20_021D1F34 *param0, int param1, int param2);
static int ov20_021D1EDC(UnkStruct_ov20_021D1F34 *param0, u16 param1);
static void ov20_021D1F38(EasyChatApp *easyChatApp, int *param1);

BOOL EasyChat_Init(ApplicationManager *appMan, int *state)
{
    EasyChatApp *easyChatApp;

    switch (*state) {
    case 0:
        Sound_SetSceneAndPlayBGM(SOUND_SCENE_SUB_62, SEQ_NONE, 0);
        Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_34, 32768);
        Heap_Create(HEAP_ID_APPLICATION, HEAP_ID_35, 163840);
        easyChatApp = EasyChatApp_New(appMan);
        ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_00);
        (*state)++;
        break;
    case 1:
        easyChatApp = ApplicationManager_Data(appMan);

        if (ov20_021D21F8(easyChatApp->unk_14)) {
            if (easyChatApp->type == EASY_CHAT_TYPE_SENTENCE) {
                easyChatApp->unk_64 = ov20_021D2DF4(easyChatApp->unk_14);
            } else {
                easyChatApp->unk_64 = 0;
            }

            return 1;
        }

        break;
    }

    return 0;
}

BOOL EasyChat_Main(ApplicationManager *appMan, int *state)
{
    EasyChatApp *easyChatApp = ApplicationManager_Data(appMan);

    easyChatApp->pressedKeys = gSystem.pressedKeys;
    easyChatApp->heldKeysUnused = gSystem.heldKeys;
    easyChatApp->pressedKeysRepeatable = gSystem.pressedKeysRepeatable;

    TouchScreenActions_HandleAction(easyChatApp->buttonAction);

    if (easyChatApp->taskFunc != NULL) {
        easyChatApp->taskFunc(easyChatApp, &easyChatApp->taskFuncState);
        return FALSE;
    } else {
        return easyChatApp->mainFunc(easyChatApp, &easyChatApp->state);
    }
}

static void EasyChat_TouchButtonCallback(u32 buttonIndex, enum TouchScreenButtonState buttonState, void *data)
{
    EasyChatApp *easyChatApp = data;

    switch (buttonState) {
    case TOUCH_BUTTON_PRESSED:
        easyChatApp->touchedButtonIndex = buttonIndex;

        switch (buttonIndex) {
        case TOUCH_BUTTON_PAGE_UP:
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_25);
            break;
        case TOUCH_BUTTON_PAGE_DOWN:
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_26);
            break;
        }

        break;
    case TOUCH_BUTTON_RELEASED:
    case TOUCH_BUTTON_HELD_OUT_OF_BOUNDS:
        switch (buttonIndex) {
        case TOUCH_BUTTON_PAGE_UP:
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_27);
            break;
        case TOUCH_BUTTON_PAGE_DOWN:
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_28);
            break;
        }

        easyChatApp->touchedButtonIndex = TOUCH_BUTTON_NONE;
        break;
    case TOUCH_BUTTON_HELD:
        if (buttonIndex == TOUCH_BUTTON_PAGE_UP || buttonIndex == TOUCH_BUTTON_PAGE_DOWN) {
            easyChatApp->touchedButtonIndex = buttonIndex;
        }
        break;
    default:
        easyChatApp->touchedButtonIndex = TOUCH_BUTTON_NONE;
        break;
    }
}

BOOL EasyChat_Exit(ApplicationManager *appMan, int *state)
{
    EasyChat_FreeAppData(ApplicationManager_Data(appMan), appMan);

    Heap_Destroy(HEAP_ID_34);
    Heap_Destroy(HEAP_ID_35);

    return TRUE;
}

static EasyChatApp *EasyChatApp_New(ApplicationManager *appMan)
{
    static const TouchScreenRect rects[] = {
        [TOUCH_BUTTON_GROUP_MODE] = { .rect = { .top = 24, .bottom = 80, .left = 24, .right = 112 } },
        [TOUCH_BUTTON_ABC_MODE] = { .rect = { .top = 112, .bottom = 168, .left = 24, .right = 112 } },
        [TOUCH_BUTTON_PAGE_UP] = { .rect = { .top = 40, .bottom = 72, .left = 176, .right = 208 } },
        [TOUCH_BUTTON_PAGE_DOWN] = { .rect = { .top = 120, .bottom = 152, .left = 176, .right = 208 } },
        { TOUCHSCREEN_TABLE_TERMINATOR, 0, 0, 0 },
    };
    EasyChatApp *easyChatApp = ApplicationManager_NewData(appMan, sizeof(EasyChatApp), HEAP_ID_34);

    easyChatApp->args = ApplicationManager_Args(appMan);
    easyChatApp->type = EasyChatArgs_GetType(easyChatApp->args);

    EasyChatArgs_GetContent(easyChatApp->args, easyChatApp->words, &easyChatApp->sentence);

    if (easyChatApp->type == EASY_CHAT_TYPE_SENTENCE) {
        EasyChatSentencePicker_Init(&easyChatApp->sentencePicker, &easyChatApp->sentence);
    }

    easyChatApp->wordList = EasyChatWordList_New(HEAP_ID_34, easyChatApp->args);
    easyChatApp->unk_14 = ov20_021D2098(easyChatApp, easyChatApp->wordList);
    easyChatApp->buttonAction = TouchScreenActions_RegisterHandler(rects, NELEMS(rects), EasyChat_TouchButtonCallback, easyChatApp, HEAP_ID_34);
    easyChatApp->dummy = 0;
    easyChatApp->dummy2 = 0;
    easyChatApp->mode = 0;
    easyChatApp->taskFunc = NULL;
    easyChatApp->taskFuncState = 0;
    easyChatApp->mainFunc = EasyChat_Main_Initial;
    easyChatApp->state = 0;
    easyChatApp->currentWordSlot = 0;

    EasyChat_SetTaskFunc(easyChatApp, ov20_021D1C5C);

    return easyChatApp;
}

static void EasyChatSentencePicker_Init(EasyChatSentencePicker *sentencePicker, EasyChatSentence *sentence)
{
    sentencePicker->type = EasyChatSentence_GetType(sentence);
    sentencePicker->idsOfCurrentType = EasyChatSentence_GetBankEntryCountForType(sentencePicker->type);
    sentencePicker->id = EasyChatSentence_GetID(sentence);
}

static void EasyChatSentencePicker_ScrollRight(EasyChatSentencePicker *sentencePicker, EasyChatSentence *sentence)
{
    sentencePicker->id++;

    if (sentencePicker->id >= sentencePicker->idsOfCurrentType) {
        sentencePicker->id = 0;
        sentencePicker->type++;

        if (sentencePicker->type >= EASY_CHAT_SENTENCE_TYPE_COUNT) {
            sentencePicker->type = 0;
        }

        sentencePicker->idsOfCurrentType = EasyChatSentence_GetBankEntryCountForType(sentencePicker->type);
    }

    EasyChatSentence_SetTypeAndID(sentence, sentencePicker->type, sentencePicker->id);
}

static void EasyChatSentencePicker_ScrollLeft(EasyChatSentencePicker *sentencePicker, EasyChatSentence *sentence)
{
    sentencePicker->id--;

    if (sentencePicker->id < 0) {
        sentencePicker->type--;

        if (sentencePicker->type < 0) {
            sentencePicker->type = EASY_CHAT_SENTENCE_TYPE_COUNT - 1;
        }

        sentencePicker->idsOfCurrentType = EasyChatSentence_GetBankEntryCountForType(sentencePicker->type);
        sentencePicker->id = sentencePicker->idsOfCurrentType - 1;
    }

    EasyChatSentence_SetTypeAndID(sentence, sentencePicker->type, sentencePicker->id);
}

static void EasyChat_FreeAppData(EasyChatApp *easyChatApp, ApplicationManager *appMan)
{
    TouchScreenActions_Free(easyChatApp->buttonAction);
    ov20_021D2128(easyChatApp->unk_14);
    EasyChatWordList_Free(easyChatApp->wordList);
    ApplicationManager_FreeData(appMan);
}

static void EasyChat_SetMainFunc(EasyChatApp *easyChatApp, EasyChatMainFunc func)
{
    easyChatApp->mainFunc = func;
    easyChatApp->state = 0;
}

static int EasyChat_Main_Initial(EasyChatApp *easyChatApp, int *param1)
{
    static const EasyChatMainFunc funcs[] = {
        [EASY_CHAT_TYPE_ONE_WORD] = EasyChat_Main_OneWord,
        [EASY_CHAT_TYPE_TWO_WORDS] = EasyChat_Main_TwoWords,
        [EASY_CHAT_TYPE_SENTENCE] = EasyChat_Main_Sentence,
    };

    return funcs[easyChatApp->type](easyChatApp, param1);
}

static int EasyChat_Main_OneWord(EasyChatApp *easyChatApp, int *param1)
{
    switch (*param1) {
    case 0:
        if (easyChatApp->touchedButtonIndex == TOUCH_BUTTON_GROUP_MODE && easyChatApp->mode != GROUP_MODE
            || easyChatApp->touchedButtonIndex == TOUCH_BUTTON_ABC_MODE && easyChatApp->mode != ABC_MODE
            || EC_JOY_NEW(PAD_BUTTON_SELECT)) {
            EasyChat_SetTaskFunc(easyChatApp, ov20_021D1F38);
            break;
        }

        if (EC_JOY_NEW(PAD_KEY_DOWN | PAD_BUTTON_START)) {
            Sound_PlayEffect(SEQ_SE_CONFIRM);
            easyChatApp->confirmOrCancelCursorPos = 0;
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_04);
            *param1 = 1;
            break;
        }

        if (EC_JOY_NEW(PAD_BUTTON_B)) {
            Sound_PlayEffect(SEQ_SE_CONFIRM);
            EasyChat_SetTaskFunc(easyChatApp, ov20_021D1DBC);
            break;
        }

        if (EC_JOY_NEW(PAD_BUTTON_A)) {
            Sound_PlayEffect(SEQ_SE_CONFIRM);
            easyChatApp->categoryCursorPos = 0;
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_06);
            *param1 = 2;
            break;
        }
        break;
    case 1:
        if (ov20_021D21F8(easyChatApp->unk_14)) {
            EasyChat_SetMainFunc(easyChatApp, EasyChat_Main_SelectConfirmOrCancel);
        }
        break;
    case 2:
        if (ov20_021D21F8(easyChatApp->unk_14)) {
            EasyChat_SetMainFunc(easyChatApp, EasyChat_Main_SelectCategory);
        }
        break;
    }

    return 0;
}

static int EasyChat_Main_TwoWords(EasyChatApp *easyChatApp, int *param1)
{
    switch (*param1) {
    case 0:
        if (easyChatApp->touchedButtonIndex == TOUCH_BUTTON_GROUP_MODE && easyChatApp->mode != GROUP_MODE
            || easyChatApp->touchedButtonIndex == TOUCH_BUTTON_ABC_MODE && easyChatApp->mode != ABC_MODE
            || EC_JOY_NEW(PAD_BUTTON_SELECT)) {
            EasyChat_SetTaskFunc(easyChatApp, ov20_021D1F38);
            break;
        }

        if (EC_JOY_NEW(PAD_KEY_DOWN | PAD_BUTTON_START)) {
            Sound_PlayEffect(SEQ_SE_CONFIRM);
            easyChatApp->confirmOrCancelCursorPos = 0;
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_04);
            *param1 = 1;
            break;
        }

        if (EC_JOY_NEW(PAD_KEY_LEFT)) {
            if (easyChatApp->currentWordSlot != 0) {
                Sound_PlayEffect(SEQ_SE_CONFIRM);
                easyChatApp->currentWordSlot = 0;
                ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_12);
            }
            break;
        }

        if (EC_JOY_NEW(PAD_KEY_RIGHT)) {
            if (easyChatApp->currentWordSlot == 0) {
                Sound_PlayEffect(SEQ_SE_CONFIRM);
                easyChatApp->currentWordSlot = 1;
                ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_12);
            }
            break;
        }

        if (EC_JOY_NEW(PAD_BUTTON_B)) {
            Sound_PlayEffect(SEQ_SE_CONFIRM);
            EasyChat_SetTaskFunc(easyChatApp, ov20_021D1DBC);
            break;
        }

        if (EC_JOY_NEW(PAD_BUTTON_A)) {
            Sound_PlayEffect(SEQ_SE_CONFIRM);
            easyChatApp->categoryCursorPos = 0;
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_06);
            *param1 = 2;
            break;
        }
        break;
    case 1:
        if (ov20_021D21F8(easyChatApp->unk_14)) {
            EasyChat_SetMainFunc(easyChatApp, EasyChat_Main_SelectConfirmOrCancel);
        }
        break;
    case 2:
        if (ov20_021D21F8(easyChatApp->unk_14)) {
            EasyChat_SetMainFunc(easyChatApp, EasyChat_Main_SelectCategory);
        }
        break;
    }

    return 0;
}

static int EasyChat_Main_Sentence(EasyChatApp *easyChatApp, int *param1)
{
    switch (*param1) {
    case 0:
        easyChatApp->unk_64 = ov20_021D2DF4(easyChatApp->unk_14);
        *param1 = 1;
    case 1:
        if (easyChatApp->touchedButtonIndex == TOUCH_BUTTON_GROUP_MODE && easyChatApp->mode != GROUP_MODE
            || easyChatApp->touchedButtonIndex == TOUCH_BUTTON_ABC_MODE && easyChatApp->mode != ABC_MODE
            || EC_JOY_NEW(PAD_BUTTON_SELECT)) {
            EasyChat_SetTaskFunc(easyChatApp, ov20_021D1F38);
            break;
        }

        if (EC_JOY_NEW(PAD_KEY_UP)) {
            if ((easyChatApp->unk_64) && (easyChatApp->currentWordSlot != 0)) {
                Sound_PlayEffect(SEQ_SE_CONFIRM);
                easyChatApp->currentWordSlot--;
                ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_12);
            }
            break;
        }

        if (EC_JOY_NEW(PAD_KEY_DOWN)) {
            Sound_PlayEffect(SEQ_SE_CONFIRM);

            if ((easyChatApp->unk_64) && (easyChatApp->currentWordSlot < (easyChatApp->unk_64 - 1))) {
                easyChatApp->currentWordSlot++;
                ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_12);
            } else {
                easyChatApp->confirmOrCancelCursorPos = 0;
                ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_04);
                *param1 = 3;
                break;
            }
        }

        if (EC_JOY_NEW(PAD_BUTTON_START) || (EC_JOY_NEW(PAD_BUTTON_A) && (easyChatApp->unk_64 == 0))) {
            Sound_PlayEffect(SEQ_SE_CONFIRM);
            easyChatApp->confirmOrCancelCursorPos = 0;
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_04);
            *param1 = 3;
            break;
        }

        if (EC_JOY_REPEAT(PAD_KEY_LEFT)) {
            Sound_PlayEffect(SEQ_SE_CONFIRM);
            easyChatApp->currentWordSlot = 0;
            EasyChatSentencePicker_ScrollLeft(&easyChatApp->sentencePicker, &easyChatApp->sentence);
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_03);
            *param1 = 2;
            break;
        }

        if (EC_JOY_REPEAT(PAD_KEY_RIGHT)) {
            Sound_PlayEffect(SEQ_SE_CONFIRM);
            easyChatApp->currentWordSlot = 0;
            EasyChatSentencePicker_ScrollRight(&easyChatApp->sentencePicker, &easyChatApp->sentence);
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_03);
            *param1 = 2;
            break;
        }

        if (EC_JOY_NEW(PAD_BUTTON_B)) {
            Sound_PlayEffect(SEQ_SE_CONFIRM);
            EasyChat_SetTaskFunc(easyChatApp, ov20_021D1DBC);
            break;
        }

        if (EC_JOY_NEW(PAD_BUTTON_A)) {
            Sound_PlayEffect(SEQ_SE_CONFIRM);
            easyChatApp->categoryCursorPos = 0;
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_06);
            *param1 = 4;
            break;
        }
        break;
    case 2:
        if (ov20_021D2210(easyChatApp->unk_14, 3)) {
            *param1 = 0;
        }
        break;
    case 3:
        if (ov20_021D21F8(easyChatApp->unk_14)) {
            EasyChat_SetMainFunc(easyChatApp, EasyChat_Main_SelectConfirmOrCancel);
        }
        break;
    case 4:
        if (ov20_021D21F8(easyChatApp->unk_14)) {
            EasyChat_SetMainFunc(easyChatApp, EasyChat_Main_SelectCategory);
        }
        break;
    }

    return 0;
}

static int EasyChat_Main_SelectConfirmOrCancel(EasyChatApp *easyChatApp, int *param1)
{
    switch (*param1) {
    case 0:
        if (ov20_021D21F8(easyChatApp->unk_14)) {
            if (easyChatApp->touchedButtonIndex == TOUCH_BUTTON_GROUP_MODE && easyChatApp->mode != GROUP_MODE
                || easyChatApp->touchedButtonIndex == TOUCH_BUTTON_ABC_MODE && easyChatApp->mode != ABC_MODE
                || EC_JOY_NEW(PAD_BUTTON_SELECT)) {
                EasyChat_SetTaskFunc(easyChatApp, ov20_021D1F38);
                break;
            }

            if (EC_JOY_NEW(PAD_KEY_LEFT | PAD_KEY_RIGHT)) {
                Sound_PlayEffect(SEQ_SE_CONFIRM);
                easyChatApp->confirmOrCancelCursorPos ^= 1;
                ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_13);
                break;
            }

            if (EC_JOY_NEW(PAD_BUTTON_START)) {
                Sound_PlayEffect(SEQ_SE_CONFIRM);
                easyChatApp->confirmOrCancelCursorPos = 0;
                ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_13);
                break;
            }

            if (EC_JOY_NEW(PAD_KEY_UP)) {
                Sound_PlayEffect(SEQ_SE_CONFIRM);
                ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_05);
                *param1 = 5;
                break;
            }

            if (EC_JOY_NEW(PAD_BUTTON_A)) {
                Sound_PlayEffect(SEQ_SE_CONFIRM);

                if (easyChatApp->confirmOrCancelCursorPos == 0) {
                    *param1 = 1;
                    break;
                } else {
                    *param1 = 2;
                    break;
                }
            }

            if (EC_JOY_NEW(PAD_BUTTON_B)) {
                Sound_PlayEffect(SEQ_SE_CONFIRM);
                *param1 = 2;
                break;
            }
        }
        break;
    case 1:
        *param1 = 3;
        EasyChat_SetTaskFunc(easyChatApp, ov20_021D1C90);
        break;
    case 2:
        *param1 = 4;
        EasyChat_SetTaskFunc(easyChatApp, ov20_021D1DBC);
        break;
    case 3:
    case 4:
        *param1 = 0;
        break;
    case 5:
        if (ov20_021D21F8(easyChatApp->unk_14)) {
            EasyChat_SetMainFunc(easyChatApp, EasyChat_Main_Initial);
        }
        break;
    }

    return 0;
}

static int EasyChat_Main_SelectCategory(EasyChatApp *easyChatApp, int *param1)
{
    switch (*param1) {
    case 0:
        if (ov20_021D2210(easyChatApp->unk_14, 15) == 0) {
            break;
        }

        if (easyChatApp->touchedButtonIndex == TOUCH_BUTTON_GROUP_MODE && easyChatApp->mode != GROUP_MODE
            || easyChatApp->touchedButtonIndex == TOUCH_BUTTON_ABC_MODE && easyChatApp->mode != ABC_MODE
            || EC_JOY_NEW(PAD_BUTTON_SELECT)) {
            Sound_PlayEffect(SEQ_SE_DP_BUTTON9);
            easyChatApp->mode ^= 1;
            easyChatApp->categoryCursorPos = 0;
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_24);
            *param1 = 2;
            break;
        }

        if (EC_JOY_NEW(PAD_BUTTON_B)) {
            Sound_PlayEffect(SEQ_SE_CONFIRM);
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_07);
            easyChatApp->nextMainFunc = EasyChat_Main_Initial;
            *param1 = 1;
            break;
        }

        if (EC_JOY_NEW(PAD_BUTTON_A)) {
            if (easyChatApp->categoryCursorPos == EASY_CHAT_CANCEL) {
                Sound_PlayEffect(SEQ_SE_CONFIRM);
                ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_07);
                easyChatApp->nextMainFunc = EasyChat_Main_Initial;
                *param1 = 1;
            } else if (EasyChat_IsCurrentCategoryNonEmpty(easyChatApp)) {
                Sound_PlayEffect(SEQ_SE_CONFIRM);
                EasyChatWordPicker_Init(&easyChatApp->wordPicker, easyChatApp);
                easyChatApp->nextMainFunc = EasyChat_Main_SelectWord;
                ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_08);
                *param1 = 1;
            } else {
                Sound_PlayEffect(SEQ_SE_DP_CUSTOM06);
            }
            break;
        }

        if (EasyChat_HandleCategoryCursorMovement(easyChatApp)) {
            Sound_PlayEffect(SEQ_SE_CONFIRM);
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_14);
            break;
        }
        break;
    case 1:
        if (ov20_021D21F8(easyChatApp->unk_14)) {
            EasyChat_SetMainFunc(easyChatApp, easyChatApp->nextMainFunc);
        }
        break;
    case 2:
        if (ov20_021D2210(easyChatApp->unk_14, 24)) {
            *param1 = 0;
        }
        break;
    }

    return 0;
}

static BOOL EasyChat_IsCurrentCategoryNonEmpty(EasyChatApp *easyChatApp)
{
    if (easyChatApp->mode == GROUP_MODE) {
        return EasyChatWordList_GetGroupWordCount(easyChatApp->wordList, easyChatApp->categoryCursorPos) != 0;
    } else {
        return EasyChatWordList_GetLetterWordCount(easyChatApp->wordList, easyChatApp->categoryCursorPos) != 0;
    }
}

static BOOL EasyChat_HandleCategoryCursorMovement(EasyChatApp *easyChatApp)
{
    static BOOL (*const funcs[])(EasyChatApp *easyChatApp) = {
        [GROUP_MODE] = EasyChat_HandleGroupModeCursorMovement,
        [ABC_MODE] = EasyChat_HandleABCModeCursorMovement,
    };

    return funcs[easyChatApp->mode](easyChatApp);
}

static BOOL EasyChat_HandleGroupModeCursorMovement(EasyChatApp *easyChatApp)
{
    static const struct {
        u8 up;
        u8 down;
        u8 left;
        u8 right;
    } adjacentGroups[] = {
        [GROUP_POKEMON] = { .up = EASY_CHAT_CANCEL, .down = GROUP_MOVE_2, .left = GROUP_MOVE, .right = GROUP_POKEMON_2 },
        [GROUP_POKEMON_2] = { .up = EASY_CHAT_CANCEL, .down = GROUP_STATUS, .left = GROUP_POKEMON, .right = GROUP_MOVE },
        [GROUP_MOVE] = { .up = EASY_CHAT_CANCEL, .down = GROUP_TRAINER, .left = GROUP_POKEMON_2, .right = GROUP_POKEMON },
        [GROUP_MOVE_2] = { .up = GROUP_POKEMON, .down = GROUP_PEOPLE, .left = GROUP_TRAINER, .right = GROUP_STATUS },
        [GROUP_STATUS] = { .up = GROUP_POKEMON_2, .down = GROUP_GREETINGS, .left = GROUP_MOVE_2, .right = GROUP_TRAINER },
        [GROUP_TRAINER] = { .up = GROUP_MOVE, .down = GROUP_LIFESTYLE, .left = GROUP_STATUS, .right = GROUP_MOVE_2 },
        [GROUP_PEOPLE] = { .up = GROUP_MOVE_2, .down = GROUP_FEELINGS, .left = GROUP_LIFESTYLE, .right = GROUP_GREETINGS },
        [GROUP_GREETINGS] = { .up = GROUP_STATUS, .down = GROUP_TOUGH_WORDS, .left = GROUP_PEOPLE, .right = GROUP_LIFESTYLE },
        [GROUP_LIFESTYLE] = { .up = GROUP_TRAINER, .down = GROUP_UNION, .left = GROUP_GREETINGS, .right = GROUP_PEOPLE },
        [GROUP_FEELINGS] = { .up = GROUP_PEOPLE, .down = EASY_CHAT_CANCEL, .left = GROUP_UNION, .right = GROUP_TOUGH_WORDS },
        [GROUP_TOUGH_WORDS] = { .up = GROUP_GREETINGS, .down = EASY_CHAT_CANCEL, .left = GROUP_FEELINGS, .right = GROUP_UNION },
        [GROUP_UNION] = { .up = GROUP_LIFESTYLE, .down = EASY_CHAT_CANCEL, .left = GROUP_TOUGH_WORDS, .right = GROUP_FEELINGS },
        [GROUP_MODE_CANCEL_INDEX] = { .up = GROUP_FEELINGS, .down = GROUP_POKEMON, .left = EASY_CHAT_CANCEL, .right = EASY_CHAT_CANCEL },
    };
    u32 cursorPos = easyChatApp->categoryCursorPos;

    // useless because the index is hardcoded below for this case anyway
    if (cursorPos == EASY_CHAT_CANCEL) {
        cursorPos = GROUP_MODE_CANCEL_INDEX;
    }

    if (easyChatApp->categoryCursorPos != EASY_CHAT_CANCEL) {
        easyChatApp->prevCategoryCursorPos = easyChatApp->categoryCursorPos;

        if (EC_JOY_REPEAT(PAD_KEY_UP)) {
            easyChatApp->categoryCursorPos = adjacentGroups[cursorPos].up;
            return TRUE;
        }

        if (EC_JOY_REPEAT(PAD_KEY_DOWN)) {
            easyChatApp->categoryCursorPos = adjacentGroups[cursorPos].down;
            return TRUE;
        }

        if (EC_JOY_REPEAT(PAD_KEY_LEFT)) {
            easyChatApp->categoryCursorPos = adjacentGroups[cursorPos].left;
            return TRUE;
        }

        if (EC_JOY_REPEAT(PAD_KEY_RIGHT)) {
            easyChatApp->categoryCursorPos = adjacentGroups[cursorPos].right;
            return TRUE;
        }
    } else {
        if (EC_JOY_REPEAT(PAD_KEY_UP)) {
            easyChatApp->categoryCursorPos = adjacentGroups[GROUP_MODE_CANCEL_INDEX].up + (easyChatApp->prevCategoryCursorPos % 3);
            return TRUE;
        }

        if (EC_JOY_REPEAT(PAD_KEY_DOWN)) {
            easyChatApp->categoryCursorPos = adjacentGroups[GROUP_MODE_CANCEL_INDEX].down + (easyChatApp->prevCategoryCursorPos % 3);
            return TRUE;
        }
    }

    return FALSE;
}

static BOOL EasyChat_HandleABCModeCursorMovement(EasyChatApp *easyChatApp)
{
    if (easyChatApp->categoryCursorPos != EASY_CHAT_CANCEL) {
        int cursorPos = EASY_CHAT_NOTHING_CHOSEN;

        if (EC_JOY_REPEAT(PAD_KEY_UP)) {
            cursorPos = EasyChatABCMode_GetCharAbove(easyChatApp->categoryCursorPos);
        } else if (EC_JOY_REPEAT(PAD_KEY_DOWN)) {
            cursorPos = EasyChatABCMode_GetCharBelow(easyChatApp->categoryCursorPos);
        } else if (EC_JOY_REPEAT(PAD_KEY_RIGHT)) {
            cursorPos = EasyChatABCMode_GetCharToRight(easyChatApp->categoryCursorPos);
        } else if (EC_JOY_REPEAT(PAD_KEY_LEFT)) {
            cursorPos = EasyChatABCMode_GetCharToLeft(easyChatApp->categoryCursorPos);
        }

        if (cursorPos != EASY_CHAT_NOTHING_CHOSEN) {
            easyChatApp->prevCategoryCursorPos = easyChatApp->categoryCursorPos;
            easyChatApp->categoryCursorPos = cursorPos;
            return TRUE;
        }
    } else {
        if (EC_JOY_REPEAT(PAD_KEY_UP)) {
            easyChatApp->categoryCursorPos = EasyChatABCMode_GetCharAtBottomOfColumn(easyChatApp->prevCategoryCursorPos);
            return TRUE;
        }

        if (EC_JOY_REPEAT(PAD_KEY_DOWN)) {
            easyChatApp->categoryCursorPos = EasyChatABCMode_GetCharAtTopOfColumn(easyChatApp->prevCategoryCursorPos);
            return TRUE;
        }
    }

    return FALSE;
}

static void EasyChatWordPicker_Init(EasyChatWordPicker *wordPicker, EasyChatApp *easyChatApp)
{
    wordPicker->listPos = 0;
    wordPicker->cursorXPos = 0;
    wordPicker->cursorYPos = 0;
    wordPicker->wordCount = EasyChat_GetCurrentCategoryWordCount(easyChatApp);
    wordPicker->listPosDelta = 0;

    if (wordPicker->wordCount > 10) {
        wordPicker->maxListPos = (wordPicker->wordCount - 10) / 2 + (wordPicker->wordCount & 1);
    } else {
        wordPicker->maxListPos = 0;
    }
}

static u32 EasyChatWordPicker_GetCursorPos(const EasyChatWordPicker *wordPicker)
{
    return wordPicker->cursorYPos * 2 + wordPicker->cursorXPos;
}

static u32 EasyChatWordPicker_CalcTrueCursorPos(const EasyChatWordPicker *wordPicker)
{
    return wordPicker->listPos * 2 + EasyChatWordPicker_GetCursorPos(wordPicker);
}

static int EasyChatWordPicker_GetListPosDelta(const EasyChatWordPicker *wordPicker)
{
    return wordPicker->listPosDelta;
}

static int EasyChatWordPicker_GetListPos(const EasyChatWordPicker *wordPicker)
{
    return wordPicker->listPos;
}

static int EasyChatWordPicker_GetMaxListPos(const EasyChatWordPicker *wordPicker)
{
    return wordPicker->maxListPos;
}

static int EasyChat_Main_SelectWord(EasyChatApp *easyChatApp, int *param1)
{
    switch (*param1) {
    case 0:
        if (easyChatApp->touchedButtonIndex == TOUCH_BUTTON_GROUP_MODE && easyChatApp->mode != GROUP_MODE
            || easyChatApp->touchedButtonIndex == TOUCH_BUTTON_ABC_MODE && easyChatApp->mode != ABC_MODE
            || EC_JOY_NEW(PAD_BUTTON_SELECT)) {
            Sound_PlayEffect(SEQ_SE_DP_BUTTON9);
            easyChatApp->categoryCursorPos = 0;
            easyChatApp->mode ^= 1;
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_09);
            easyChatApp->nextMainFunc = EasyChat_Main_SelectCategory;
            *param1 = 3;
            break;
        }

        int v0;

        if (easyChatApp->touchedButtonIndex == TOUCH_BUTTON_PAGE_UP) {
            v0 = EasyChatWordPicker_PageUp(&easyChatApp->wordPicker);
        } else if (easyChatApp->touchedButtonIndex == TOUCH_BUTTON_PAGE_DOWN) {
            v0 = EasyChatWordPicker_PageDown(&easyChatApp->wordPicker);
        } else {
            v0 = EasyChat_HandleSelectWordInput(&easyChatApp->wordPicker, easyChatApp->pressedKeysRepeatable);
        }

        switch (v0) {
        case 1:
            Sound_PlayEffect(SEQ_SE_CONFIRM);
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_15);
            return 0;
        case 2:
            Sound_PlayEffect(SEQ_SE_CONFIRM);
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_16);
            *param1 = 1;
            return 0;
        case 3:
            Sound_PlayEffect(SEQ_SE_CONFIRM);
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_16);
            *param1 = 2;
            return 0;
        }

        if (EC_JOY_NEW(PAD_BUTTON_B)) {
            Sound_PlayEffect(SEQ_SE_CONFIRM);
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_09);
            easyChatApp->nextMainFunc = EasyChat_Main_SelectCategory;
            *param1 = 3;
            break;
        }

        if (EC_JOY_NEW(PAD_BUTTON_A)) {
            Sound_PlayEffect(SEQ_SE_CONFIRM);
            EasyChat_SetSelectedWord(easyChatApp);
            easyChatApp->nextMainFunc = EasyChat_Main_Initial;
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_10);
            *param1 = 3;
            break;
        }
        break;
    case 1:
        if (ov20_021D2210(easyChatApp->unk_14, EASY_CHAT_SYSTASK_16)) {
            *param1 = 0;
        }
        break;
    case 2:
        if (ov20_021D2210(easyChatApp->unk_14, EASY_CHAT_SYSTASK_16)) {
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_15);
            *param1 = 0;
        }
        break;
    case 3:
        if (ov20_021D21F8(easyChatApp->unk_14)) {
            EasyChat_SetMainFunc(easyChatApp, easyChatApp->nextMainFunc);
            *param1 = 0;
        }
        break;
    }

    return 0;
}

static int EasyChat_HandleSelectWordInput(EasyChatWordPicker *wordPicker, u16 pressedKeysRepeatable)
{
    if (pressedKeysRepeatable & PAD_KEY_DOWN) {
        if (wordPicker->cursorYPos < 4) {
            wordPicker->cursorYPos++;
            u32 trueCursorPos = EasyChatWordPicker_CalcTrueCursorPos(wordPicker);

            if (trueCursorPos < wordPicker->wordCount) {
                return 1;
            }

            if (trueCursorPos == wordPicker->wordCount) {
                if (trueCursorPos & 1) {
                    wordPicker->cursorXPos = 0;
                    return 1;
                }
            }

            wordPicker->cursorYPos--;
            return 4;
        } else if (wordPicker->listPos < wordPicker->maxListPos) {
            wordPicker->listPosDelta = 1;
            wordPicker->listPos++;

            if (EasyChatWordPicker_CalcTrueCursorPos(wordPicker) < wordPicker->wordCount) {
                return 2;
            } else {
                wordPicker->cursorXPos = 0;
                return 3;
            }
        }

        return 4;
    }

    if (pressedKeysRepeatable & PAD_KEY_UP) {
        if (wordPicker->cursorYPos) {
            wordPicker->cursorYPos--;
            return 1;
        } else if (wordPicker->listPos) {
            wordPicker->listPosDelta = -1;
            wordPicker->listPos--;
            return 2;
        }

        return 4;
    }

    if (pressedKeysRepeatable & (PAD_KEY_LEFT | PAD_KEY_RIGHT)) {
        wordPicker->cursorXPos ^= 1;

        if (EasyChatWordPicker_CalcTrueCursorPos(wordPicker) < wordPicker->wordCount) {
            return 1;
        }

        wordPicker->cursorXPos ^= 1;
        return 4;
    }

    if (pressedKeysRepeatable & PAD_BUTTON_L) {
        return EasyChatWordPicker_PageUp(wordPicker);
    }

    if (pressedKeysRepeatable & PAD_BUTTON_R) {
        return EasyChatWordPicker_PageDown(wordPicker);
    }

    return 0;
}

static int EasyChatWordPicker_PageUp(EasyChatWordPicker *wordPicker)
{
    if (wordPicker->listPos) {
        if (wordPicker->listPos >= 5) {
            wordPicker->listPos -= 5;
            wordPicker->listPosDelta = -5;
        } else {
            wordPicker->listPosDelta = -wordPicker->listPos;
            wordPicker->listPos = 0;
        }

        return 2;
    }

    return 4;
}

static int EasyChatWordPicker_PageDown(EasyChatWordPicker *wordPicker)
{
    if (wordPicker->listPos < wordPicker->maxListPos) {
        if (wordPicker->listPos + 5 <= wordPicker->maxListPos) {
            wordPicker->listPosDelta = 5;
            wordPicker->listPos += 5;
        } else {
            wordPicker->listPosDelta = wordPicker->maxListPos - wordPicker->listPos;
            wordPicker->listPos = wordPicker->maxListPos;
        }

        if (EasyChatWordPicker_CalcTrueCursorPos(wordPicker) < wordPicker->wordCount) {
            return 2;
        } else {
            wordPicker->cursorXPos = 0;
            return 3;
        }
    }

    return 4;
}

static BOOL EasyChat_SetSelectedWord(EasyChatApp *easyChatApp)
{
    u32 index = EasyChatWordPicker_CalcTrueCursorPos(&easyChatApp->wordPicker);
    u16 word;

    if (easyChatApp->mode == GROUP_MODE) {
        word = EasyChatWordList_GetWordByGroupIndex(easyChatApp->wordList, easyChatApp->categoryCursorPos, index);
    } else {
        word = EasyChatWordList_GetWordByLetterIndex(easyChatApp->wordList, easyChatApp->categoryCursorPos, index);
    }

    switch (easyChatApp->type) {
    case EASY_CHAT_TYPE_ONE_WORD:
        easyChatApp->words[0] = word;
        break;
    case EASY_CHAT_TYPE_TWO_WORDS:
        easyChatApp->words[easyChatApp->currentWordSlot] = word;
        break;
    case EASY_CHAT_TYPE_SENTENCE:
        EasyChatSentence_SetWord(&easyChatApp->sentence, easyChatApp->currentWordSlot, word);
        break;
    }

    return EasyChat_IsEntryComplete(easyChatApp);
}

static int ov20_021D1C18(EasyChatApp *easyChatApp, int *param1)
{
    switch (*param1) {
    case 0:
        ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_01);
        (*param1)++;
        break;
    case 1:
        if (ov20_021D21F8(easyChatApp->unk_14)) {
            return 1;
        }
        break;
    }

    return 0;
}

static void EasyChat_SetTaskFunc(EasyChatApp *easyChatApp, EasyChatTaskFunc func)
{
    easyChatApp->taskFunc = func;
    easyChatApp->taskFuncState = 0;
}

static void EasyChat_ClearTaskFunc(EasyChatApp *easyChatApp)
{
    easyChatApp->taskFunc = NULL;
}

static void ov20_021D1C5C(EasyChatApp *easyChatApp, int *param1)
{
    switch (*param1) {
    case 0:
        ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_02);
        (*param1)++;
        break;
    case 1:
        if (ov20_021D21F8(easyChatApp->unk_14)) {
            EasyChat_ClearTaskFunc(easyChatApp);
        }
        break;
    }
}

static void ov20_021D1C90(EasyChatApp *easyChatApp, int *param1)
{
    switch (*param1) {
    case 0:
        if (ov20_021D1E70(easyChatApp) || sub_02097568(easyChatApp->args)) {
            if (EasyChat_IsEntryComplete(easyChatApp)) {
                ov20_021D1ED4(&easyChatApp->unk_66, 1, 0);
                ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_18);
                *param1 = 1;
            } else {
                ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_20);
                *param1 = 2;
            }
        } else {
            EasyChat_SetTaskFunc(easyChatApp, ov20_021D1DBC);
        }
        break;
    case 1:
        if (ov20_021D2210(easyChatApp->unk_14, 21)) {
            switch (ov20_021D1EDC(&(easyChatApp->unk_66), easyChatApp->pressedKeys)) {
            case -3:
                Sound_PlayEffect(SEQ_SE_CONFIRM);
                ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_21);
                break;
            case 1:
            case -2:
                Sound_PlayEffect(SEQ_SE_CONFIRM);
                ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_22);
                *param1 = 3;
                break;
            case 0:
                Sound_PlayEffect(SEQ_SE_CONFIRM);

                if (easyChatApp->type == EASY_CHAT_TYPE_SENTENCE) {
                    EasyChatSentence_ClearUnusedWords(&easyChatApp->sentence);
                }

                EasyChatArgs_UpdateContent(easyChatApp->args, easyChatApp->words, &easyChatApp->sentence);
                EasyChat_SetMainFunc(easyChatApp, ov20_021D1C18);
                *param1 = 3;
                break;
            }
        }
        break;
    case 2:
        if (EC_JOY_NEW(PAD_BUTTON_A | PAD_BUTTON_B | PAD_PLUS_KEY_MASK)) {
            ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_17);
            *param1 = 3;
        }
        break;
    case 3:
        if (ov20_021D21F8(easyChatApp->unk_14)) {
            EasyChat_ClearTaskFunc(easyChatApp);
        }
        break;
    }
}

static void ov20_021D1DBC(EasyChatApp *easyChatApp, int *param1)
{
    switch (*param1) {
    case 0:
        ov20_021D1ED4(&easyChatApp->unk_66, 1, 1);
        ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_19);
        *param1 = 1;
        break;
    case 1:
        if (ov20_021D2210(easyChatApp->unk_14, 21)) {
            switch (ov20_021D1EDC(&(easyChatApp->unk_66), easyChatApp->pressedKeys)) {
            case -3:
                Sound_PlayEffect(SEQ_SE_CONFIRM);
                ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_21);
                break;
            case 1:
            case -2:
                Sound_PlayEffect(SEQ_SE_CONFIRM);
                ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_22);
                *param1 = 2;
                break;
            case 0:
                Sound_PlayEffect(SEQ_SE_CONFIRM);
                EasyChat_SetMainFunc(easyChatApp, ov20_021D1C18);
                *param1 = 2;
                break;
            }
        }
        break;
    case 2:
        if (ov20_021D21F8(easyChatApp->unk_14)) {
            EasyChat_ClearTaskFunc(easyChatApp);
        }
        break;
    }
}

static BOOL ov20_021D1E70(EasyChatApp *easyChatApp)
{
    return !EasyChatArgs_Compare(easyChatApp->args, easyChatApp->words, &easyChatApp->sentence);
}

static BOOL EasyChat_IsEntryComplete(EasyChatApp *easyChatApp)
{
    switch (easyChatApp->type) {
    case EASY_CHAT_TYPE_ONE_WORD:
        return easyChatApp->words[0] != WORD_NONE;
    case EASY_CHAT_TYPE_TWO_WORDS:
        return easyChatApp->words[0] != WORD_NONE && easyChatApp->words[1] != WORD_NONE;
    case EASY_CHAT_TYPE_SENTENCE:
        return EasyChatSentence_IsComplete(&easyChatApp->sentence);
    }

    return FALSE;
}

static void ov20_021D1ED4(UnkStruct_ov20_021D1F34 *param0, int param1, int param2)
{
    param0->unk_00 = param2;
    param0->unk_01 = param1;
}

static int ov20_021D1EDC(UnkStruct_ov20_021D1F34 *param0, u16 param1)
{
    if (param1 & PAD_KEY_UP) {
        if (param0->unk_00 == 0) {
            return -4;
        } else {
            param0->unk_00--;
            return -3;
        }
    }

    if (param1 & PAD_KEY_DOWN) {
        if (param0->unk_00 == param0->unk_01) {
            return -4;
        } else {
            param0->unk_00++;
            return -3;
        }
    }

    if (param1 & PAD_BUTTON_A) {
        return param0->unk_00;
    }

    if (param1 & PAD_BUTTON_B) {
        return -2;
    }

    return -1;
}

static u32 ov20_021D1F34(const UnkStruct_ov20_021D1F34 *param0)
{
    return param0->unk_00;
}

static void ov20_021D1F38(EasyChatApp *easyChatApp, int *param1)
{
    switch (*param1) {
    case 0:
        Sound_PlayEffect(SEQ_SE_DP_BUTTON9);
        easyChatApp->mode ^= 1;
        ov20_021D21A0(easyChatApp->unk_14, EASY_CHAT_SYSTASK_23);
        *param1 = 1;
        break;
    case 1:
        if (ov20_021D21F8(easyChatApp->unk_14)) {
            EasyChat_ClearTaskFunc(easyChatApp);
        }

        break;
    }
}

u32 EasyChat_GetType(const EasyChatApp *easyChatApp)
{
    return easyChatApp->type;
}

u32 EasyChat_GetInstructionBankEntry(const EasyChatApp *easyChatApp)
{
    return EasyChatArgs_GetInstructionBankEntry(easyChatApp->args);
}

u32 EasyChat_GetMode(const EasyChatApp *easyChatApp)
{
    return easyChatApp->mode;
}

u32 EasyChat_GetSentenceType(const EasyChatApp *easyChatApp)
{
    return EasyChatSentence_GetType(&easyChatApp->sentence);
}

u16 EasyChat_GetWordAtSlot(const EasyChatApp *easyChatApp, int slot)
{
    if (easyChatApp->type == EASY_CHAT_TYPE_SENTENCE) {
        return EasyChatSentence_GetWord(&easyChatApp->sentence, slot);
    } else {
        return easyChatApp->words[slot];
    }
}

String *EasyChat_GetSentenceTemplateString(const EasyChatApp *easyChatApp, enum HeapID heapID)
{
    return EasyChatSentence_GetTemplateString(&easyChatApp->sentence, heapID);
}

u32 EasyChat_GetCurrentWordSlot(const EasyChatApp *easyChatApp)
{
    return easyChatApp->currentWordSlot;
}

u32 ov20_021D1FD4(const EasyChatApp *easyChatApp)
{
    return easyChatApp->confirmOrCancelCursorPos;
}

u32 EasyChat_GetCategoryCursorPos(const EasyChatApp *easyChatApp)
{
    return easyChatApp->categoryCursorPos;
}

u32 EasyChat_GetCurrentCategoryWordCount(const EasyChatApp *easyChatApp)
{
    if (easyChatApp->mode == GROUP_MODE) {
        return EasyChatWordList_GetGroupWordCount(easyChatApp->wordList, easyChatApp->categoryCursorPos);
    } else {
        return EasyChatWordList_GetLetterWordCount(easyChatApp->wordList, easyChatApp->categoryCursorPos);
    }
}

void EasyChat_GetWordStringAtIndex(const EasyChatApp *easyChatApp, u32 index, String *out)
{
    if (easyChatApp->mode == GROUP_MODE) {
        EasyChatWordList_GetStringByGroupIndex(easyChatApp->wordList, easyChatApp->categoryCursorPos, index, out);
    } else {
        EasyChatWordList_GetStringByLetterIndex(easyChatApp->wordList, easyChatApp->categoryCursorPos, index, out);
    }
}

u32 EasyChat_GetWordPickerCursorPos(const EasyChatApp *easyChatApp)
{
    return EasyChatWordPicker_GetCursorPos(&easyChatApp->wordPicker);
}

int EasyChat_GetWordPickerScrollDistance(const EasyChatApp *easyChatApp)
{
    return EasyChatWordPicker_GetListPosDelta(&easyChatApp->wordPicker);
}

BOOL EasyChat_CanScrollWordPickerUp(const EasyChatApp *easyChatApp)
{
    return EasyChatWordPicker_GetListPos(&easyChatApp->wordPicker) != 0;
}

BOOL EasyChat_CanScrollWordPickerDown(const EasyChatApp *easyChatApp)
{
    return EasyChatWordPicker_GetListPos(&easyChatApp->wordPicker) < EasyChatWordPicker_GetMaxListPos(&easyChatApp->wordPicker);
}

int EasyChat_GetFrame(const EasyChatApp *easyChatApp)
{
    return EasyChatArgs_GetFrame(easyChatApp->args);
}

u32 ov20_021D208C(const EasyChatApp *easyChatApp)
{
    return ov20_021D1F34(&easyChatApp->unk_66);
}
