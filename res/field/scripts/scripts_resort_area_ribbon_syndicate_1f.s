#include "macros/scrcmd.inc"
#include "res/text/bank/resort_area_ribbon_syndicate_1f.h"
#include "generated/ribbons.h"

    .data

    ScriptEntry _00C0
    ScriptEntry _00D6
    ScriptEntry _0269
    ScriptEntry _027C
    ScriptEntry _02BA
    ScriptEntry _02D9
    ScriptEntry _003F
    ScriptEntry _0022
    ScriptEntryEnd

_0022:
    GoToIfSet FLAG_UNK_0x00FA, _002F
    End

_002F:
    SetObjectEventPos 0, 16, 14
    SetObjectEventDir 0, DIR_SOUTH
    End

_003F:
    LockAll
    WaitTime 20, VAR_RESULT
    ScrCmd_22F VAR_0x8004
    GoToIfLt VAR_0x8004, 10, _0078
    SetVar VAR_UNK_0x40A7, 1
    SetFlag FLAG_UNK_0x00FA
    BufferPlayerName 0
    Message 1
    CloseMessage
    ApplyMovement 0, _00AC
    WaitMovement
    ReleaseAll
    End

_0078:
    Message 0
    CloseMessage
    WaitTime 20, VAR_RESULT
    FadeScreen 6, 1, 0, 0
    WaitFadeScreen
    Warp MAP_HEADER_RESORT_AREA, 0, 0x338, 0x1C6, 1
    FadeScreen 6, 1, 1, 0
    WaitFadeScreen
    ReleaseAll
    End

    .balign 4, 0
_00AC:
    FaceWest
    LockDir
    WalkNormalEast
    UnlockDir
    EndMovement

_00C0:
    BufferPlayerName 0
    PlayFanfare SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message 2
    WaitABXPadPress
    CloseMessage
    ReleaseAll
    End

_00D6:
    PlayFanfare SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GetFirstNonEggInParty VAR_0x8000
    BufferPlayerName 0
    BufferPartyMonSpecies 2, VAR_0x8000
    GetPartyMonRibbon VAR_RESULT, VAR_0x8000, RIBBON_GORGEOUS_ROYAL
    GoToIfEq VAR_RESULT, 1, _0244
    GetPartyMonRibbon VAR_RESULT, VAR_0x8000, RIBBON_ROYAL
    GoToIfEq VAR_RESULT, 1, _01E7
    GetPartyMonRibbon VAR_RESULT, VAR_0x8000, RIBBON_GORGEOUS
    GoToIfEq VAR_RESULT, 1, _018A
    GoTo _012F

_012F:
    ShowMoney 20, 2
    Message 3
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_NO, _025C
    GoToIfNotEnoughMoney 10000, _024F
    AddToGameRecord RECORD_MONEY_SPENT, 10000
    RemoveMoney 10000
    UpdateMoneyDisplay
    PlayFanfare SEQ_SE_DP_REGI
    WaitFanfare SEQ_SE_DP_REGI
    Message 7
    Message 8
    WaitABXPadPress
    SetPartyMonRibbon VAR_0x8000, RIBBON_GORGEOUS
    CloseMessage
    HideMoney
    ReleaseAll
    End

_018A:
    ShowMoney 20, 2
    Message 4
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_NO, _025C
    GoToIfNotEnoughMoney 100000, _024F
    AddToGameRecordBigValue RECORD_MONEY_SPENT, 100000
    RemoveMoney 100000
    UpdateMoneyDisplay
    PlayFanfare SEQ_SE_DP_REGI
    WaitFanfare SEQ_SE_DP_REGI
    Message 9
    Message 10
    WaitABXPadPress
    SetPartyMonRibbon VAR_0x8000, RIBBON_ROYAL
    CloseMessage
    HideMoney
    ReleaseAll
    End

_01E7:
    ShowMoney 20, 2
    Message 5
    ShowYesNoMenu VAR_RESULT
    GoToIfEq VAR_RESULT, MENU_NO, _025C
    GoToIfNotEnoughMoney 999999, _024F
    AddToGameRecordBigValue RECORD_MONEY_SPENT, 999999
    RemoveMoney 999999
    UpdateMoneyDisplay
    PlayFanfare SEQ_SE_DP_REGI
    WaitFanfare SEQ_SE_DP_REGI
    Message 11
    Message 12
    WaitABXPadPress
    SetPartyMonRibbon VAR_0x8000, RIBBON_GORGEOUS_ROYAL
    CloseMessage
    HideMoney
    ReleaseAll
    End

_0244:
    Message 6
    WaitABXPadPress
    CloseMessage
    ReleaseAll
    End

_024F:
    Message 13
    WaitABXPadPress
    CloseMessage
    HideMoney
    ReleaseAll
    End

_025C:
    Message 14
    WaitABXPadPress
    CloseMessage
    HideMoney
    ReleaseAll
    End

_0269:
    PlayFanfare SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    Message 15
    WaitABXPadPress
    CloseMessage
    ReleaseAll
    End

_027C:
    PlayFanfare SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    GetPlayerGender VAR_RESULT
    GoToIfEq VAR_RESULT, GENDER_MALE, _02A4
    GoToIfEq VAR_RESULT, GENDER_FEMALE, _02AF
    End

_02A4:
    Message 16
    WaitABXPadPress
    CloseMessage
    ReleaseAll
    End

_02AF:
    Message 17
    WaitABXPadPress
    CloseMessage
    ReleaseAll
    End

_02BA:
    PlayFanfare SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    WaitFanfare SEQ_SE_CONFIRM
    PlayCry SPECIES_SKITTY
    Message 18
    WaitCry
    WaitABXPadPress
    CloseMessage
    ReleaseAll
    End

_02D9:
    PlayFanfare SEQ_SE_CONFIRM
    LockAll
    FacePlayer
    WaitFanfare SEQ_SE_CONFIRM
    PlayCry SPECIES_PSYDUCK
    Message 19
    WaitCry
    WaitABXPadPress
    CloseMessage
    ReleaseAll
    End
