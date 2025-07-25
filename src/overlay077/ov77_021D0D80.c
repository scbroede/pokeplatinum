#include <nitro.h>
#include <string.h>

#include "constants/screen.h"
#include "constants/species.h"

#include "struct_defs/struct_0207C690.h"
#include "struct_defs/struct_02099F80.h"

#include "overlay077/const_ov77_021D742C.h"

#include "bg_window.h"
#include "brightness_controller.h"
#include "camera.h"
#include "easy3d.h"
#include "easy3d_object.h"
#include "font.h"
#include "fx_util.h"
#include "graphics.h"
#include "gx_layers.h"
#include "heap.h"
#include "main.h"
#include "math_util.h"
#include "message.h"
#include "narc.h"
#include "overlay_manager.h"
#include "screen_fade.h"
#include "sound.h"
#include "sound_playback.h"
#include "strbuf.h"
#include "system.h"
#include "text.h"
#include "unk_0202419C.h"
#include "unk_02024220.h"

FS_EXTERN_OVERLAY(overlay77);
FS_EXTERN_OVERLAY(overlay89);
FS_EXTERN_OVERLAY(overlay97);
FS_EXTERN_OVERLAY(d_startmenu);

typedef struct {
    int unk_00;
    NNSG3dRenderObj unk_04;
    NNSG3dResMdl *unk_58;
    NNSG3dResFileHeader *unk_5C;
    void *unk_60;
    void *unk_64;
    NNSG3dAnmObj *unk_68;
    NNSG3dAnmObj *unk_6C;
    NNSFndAllocator unk_70;
    VecFx32 unk_80;
    VecFx32 unk_8C;
    VecFx32 unk_98;
    Camera *camera1;
    Camera *camera2;
    int unk_AC;
    Easy3DObject unk_B0;
    Easy3DAnim unk_128;
    Easy3DAnim unk_13C;
    Easy3DModel unk_150;
    Easy3DObject unk_160;
    Easy3DAnim unk_1D8;
    Easy3DAnim unk_1EC;
    Easy3DModel unk_200;
    u32 unk_210;
    int unk_214;
    int unk_218;
    fx32 unk_21C;
    int unk_220;
    u8 unk_224;
    u8 unk_225;
} UnkStruct_ov77_021D1208;

typedef struct {
    int unk_00;
    UnkStruct_ov77_021D1208 unk_04;
} UnkStruct_ov77_021D17B4_sub1;

typedef struct {
    int unk_00;
    UnkStruct_ov77_021D1208 unk_04;
    u16 unk_22A;
    Window unk_22C;
    VecFx32 unk_23C;
    VecFx32 unk_248;
    BOOL unk_254;
    VecFx32 unk_258;
    VecFx32 unk_264;
    VecFx32 unk_270;
    VecFx32 unk_27C;
    VecFx16 unk_288;
    VecFx16 unk_28E;
    u16 unk_294;
    u16 unk_296;
    fx32 unk_298;
    BOOL unk_29C;
    BOOL unk_2A0;
    int unk_2A4;
    int unk_2A8;
    int unk_2AC;
} UnkStruct_ov77_021D1568;

typedef struct {
    int heapID;
    BgConfig *unk_04;
    GenericPointerData *unk_08;
    UnkStruct_ov77_021D17B4_sub1 unk_0C;
    UnkStruct_ov77_021D1568 unk_238;
    u16 unk_4E8;
    int unk_4EC;
    int unk_4F0;
    int unk_4F4;
    int unk_4F8;
    int unk_4FC;
} UnkStruct_ov77_021D17B4;

extern const ApplicationManagerTemplate Unk_020F8A48;
extern const ApplicationManagerTemplate Unk_020F8AB4;
extern const ApplicationManagerTemplate gOpeningCutsceneAppTemplate;

static void ov77_021D1D48(BgConfig *param0, int param1);
void EnqueueApplication(FSOverlayID param0, const ApplicationManagerTemplate *param1);
static int ov77_021D0D80(ApplicationManager *appMan, int *param1);
static int ov77_021D0E3C(ApplicationManager *appMan, int *param1);
static int ov77_021D10FC(ApplicationManager *appMan, int *param1);
static void ov77_021D1178(void *param0);
static void ov77_021D1184(void);
static void ov77_021D17B4(UnkStruct_ov77_021D17B4 *param0);
static void ov77_021D1908(UnkStruct_ov77_021D17B4 *param0);
static void ov77_021D11CC(UnkStruct_ov77_021D17B4 *param0);
static void ov77_021D11FC(UnkStruct_ov77_021D17B4 *param0);
static void ov77_021D1208(UnkStruct_ov77_021D1208 *param0, int param1, int param2, int param3);
static void ov77_021D14E4(UnkStruct_ov77_021D1208 *param0);
static void ov77_021D1568(UnkStruct_ov77_021D1568 *param0, UnkStruct_ov77_021D1208 *param1);
static BOOL ov77_021D11A4(void);
static BOOL ov77_021D1A60(UnkStruct_ov77_021D1568 *param0, BgConfig *param1, int param2);
static BOOL ov77_021D1DF0(UnkStruct_ov77_021D1568 *param0, BgConfig *param1, int heapID);
static BOOL ov77_021D20E4(UnkStruct_ov77_021D1568 *param0, BgConfig *param1, int param2);
static BOOL ov77_021D21C0(UnkStruct_ov77_021D1568 *param0, BgConfig *param1, int param2);
static void ov77_021D1300(UnkStruct_ov77_021D1208 *param0, int heapID);
static void ov77_021D1514(UnkStruct_ov77_021D1208 *param0);
static void ov77_021D1704(UnkStruct_ov77_021D1208 *param0);
static void ov77_021D1984(UnkStruct_ov77_021D1568 *param0, UnkStruct_ov77_021D1208 *param1);
static void ov77_021D25AC(Camera *camera);
static void ov77_021D2214(BgConfig *param0, int param1, UnkStruct_ov77_021D1568 *param2);
static void ov77_021D2428(BgConfig *param0, int param1, UnkStruct_ov77_021D1568 *param2);
static void ov77_021D24C8(UnkStruct_ov77_021D1568 *param0);
static void ov77_021D2438(UnkStruct_ov77_021D1568 *param0);

const ApplicationManagerTemplate gTitleScreenAppTemplate = {
    ov77_021D0D80,
    ov77_021D0E3C,
    ov77_021D10FC,
    0xffffffff
};

static int ov77_021D0D80(ApplicationManager *appMan, int *param1)
{
    UnkStruct_ov77_021D17B4 *v0;
    int heapID = HEAP_ID_DISTORTION_WORLD_WARP;

    SetScreenColorBrightness(DS_SCREEN_MAIN, FADE_TO_BLACK);
    SetScreenColorBrightness(DS_SCREEN_SUB, FADE_TO_BLACK);

    G2S_BlendNone();
    G2_BlendNone();

    SetVBlankCallback(NULL, NULL);
    SetHBlankCallback(NULL, NULL);

    GXLayers_DisableEngineALayers();
    GXLayers_DisableEngineBLayers();

    GX_SetVisiblePlane(0);
    GXS_SetVisiblePlane(0);

    SetAutorepeat(4, 8);
    Heap_Create(HEAP_ID_APPLICATION, heapID, 0x40000);

    v0 = ApplicationManager_NewData(appMan, sizeof(UnkStruct_ov77_021D17B4), heapID);
    memset(v0, 0, sizeof(UnkStruct_ov77_021D17B4));

    v0->heapID = heapID;
    v0->unk_4E8 = 0;
    v0->unk_4F8 = 0;

    ov77_021D1184();
    ov77_021D17B4(v0);
    ov77_021D11CC(v0);

    SetVBlankCallback(ov77_021D1178, (void *)v0);
    GXLayers_TurnBothDispOn();

    return 1;
}

static int ov77_021D0E3C(ApplicationManager *appMan, int *param1)
{
    UnkStruct_ov77_021D17B4 *v0 = ApplicationManager_Data(appMan);

    switch (*param1) {
    case 0:
        if (ov77_021D1A60(&v0->unk_238, v0->unk_04, v0->heapID) == 1) {
            v0->unk_238.unk_00 = 0;

            if (gSystem.unk_6C == 0) {
                v0->unk_4EC = 30 * 1;
                v0->unk_238.unk_29C = 1;
                v0->unk_238.unk_2A0 = 0;
                *param1 = 2;
            } else {
                v0->unk_4EC = 0;
                gSystem.unk_6C = 0;
                v0->unk_238.unk_2A0 = 1;
                *param1 = 1;
            }
        }
        break;
    case 1:
        if (ov77_021D1DF0(&v0->unk_238, v0->unk_04, v0->heapID) == 1) {
            v0->unk_238.unk_00 = 0;
            *param1 = 2;
        }
        break;
    case 2:
        Sound_SetScene(SOUND_SCENE_NONE);
        Sound_SetSceneAndPlayBGM(SOUND_SCENE_1, SEQ_TITLE01, 1);
        *param1 = 3;
        break;
    case 3:
        if (v0->unk_4EC) {
            v0->unk_4EC--;

            v0->unk_238.unk_254 = 0;
            ov77_021D20E4(&v0->unk_238, v0->unk_04, v0->heapID);
            break;
        } else {
            v0->unk_238.unk_254 = 1;
            ov77_021D20E4(&v0->unk_238, v0->unk_04, v0->heapID);
        }

        v0->unk_4F8++;

        if (((gSystem.pressedKeys & PAD_BUTTON_A) == PAD_BUTTON_A) || ((gSystem.pressedKeys & PAD_BUTTON_START) == PAD_BUTTON_START)) {
            v0->unk_4E8 = 1;
            Sound_FadeOutBGM(0, 60);
            Sound_PlayPokemonCry(SPECIES_GIRATINA, 1);
            ov77_021D1D48(v0->unk_04, v0->heapID);
            *param1 = 4;
            break;
        }

        if ((gSystem.heldKeys & (PAD_BUTTON_B | PAD_KEY_UP | PAD_BUTTON_SELECT)) == (PAD_BUTTON_B | PAD_KEY_UP | PAD_BUTTON_SELECT)) {
            v0->unk_4E8 = 2;
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_UNK_0, FADE_TYPE_UNK_0, FADE_TO_BLACK, 6, 1, v0->heapID);
            *param1 = 6;
            break;
        }

        if (v0->unk_4F8 > 30 * 30) {
            v0->unk_4E8 = 3;
            gSystem.unk_6C = 1;
            {
                GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 0);
            }
            Sound_FadeOutBGM(0, 60);
            *param1 = 5;
            break;
        }
        break;
    case 4:
        v0->unk_238.unk_254 = 0;
        ov77_021D20E4(&v0->unk_238, v0->unk_04, v0->heapID);

        if ((++v0->unk_4FC) == 10) {
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_UNK_0, FADE_TYPE_UNK_0, FADE_TO_WHITE, 6, 1, v0->heapID);
        }

        if ((Sound_IsPokemonCryPlaying() == 0) && (IsScreenFadeDone() == TRUE) && (v0->unk_4FC >= 10)) {
            Sound_StopBGM(SEQ_TITLE01, 0);

            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 0);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 0);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 0);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 0);
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_UNK_1, FADE_TYPE_UNK_1, FADE_TO_WHITE, 6, 1, v0->heapID);
            *param1 = 6;
        }
        break;
    case 5:
        v0->unk_238.unk_254 = 0;
        ov77_021D20E4(&v0->unk_238, v0->unk_04, v0->heapID);

        if (Sound_IsFadeActive() == FALSE) {
            Sound_StopBGM(SEQ_TITLE01, 0);
            StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_UNK_0, FADE_TYPE_UNK_0, FADE_TO_WHITE, 6, 1, v0->heapID);
            *param1 = 6;
        }
        break;
    case 6:
        if (IsScreenFadeDone() == TRUE) {
            if (ov77_021D21C0(&v0->unk_238, v0->unk_04, v0->heapID) == 1) {
                return 1;
            }
        }
        break;
    }

    return 0;
}

static int ov77_021D10FC(ApplicationManager *appMan, int *param1)
{
    UnkStruct_ov77_021D17B4 *v0 = ApplicationManager_Data(appMan);
    int heapID = v0->heapID;
    int v2 = v0->unk_4E8;

    SetVBlankCallback(NULL, NULL);

    ov77_021D11FC(v0);
    ov77_021D1908(v0);

    ApplicationManager_FreeData(appMan);
    Heap_Destroy(heapID);

    switch (v2) {
    default:
    case 1:
        EnqueueApplication(0xffffffff, &Unk_020F8AB4);
        break;
    case 2:
        EnqueueApplication(0xffffffff, &Unk_020F8A48);
        break;
    case 3:
        Sound_SetScene(SOUND_SCENE_NONE);
        EnqueueApplication(FS_OVERLAY_ID(overlay77), &gOpeningCutsceneAppTemplate);
        break;
    }

    return 1;
}

static void ov77_021D1178(void *param0)
{
    UnkStruct_ov77_021D17B4 *v0 = param0;
    Bg_RunScheduledUpdates(v0->unk_04);
}

static void ov77_021D1184(void)
{
    UnkStruct_02099F80 v0 = {
        GX_VRAM_BG_128_B,
        GX_VRAM_BGEXTPLTT_NONE,
        GX_VRAM_SUB_BG_128_C,
        GX_VRAM_SUB_BGEXTPLTT_0123_H,
        GX_VRAM_OBJ_NONE,
        GX_VRAM_OBJEXTPLTT_NONE,
        GX_VRAM_SUB_OBJ_NONE,
        GX_VRAM_SUB_OBJEXTPLTT_NONE,
        GX_VRAM_TEX_0_A,
        GX_VRAM_TEXPLTT_0_G
    };

    GXLayers_SetBanks(&v0);
}

static BOOL ov77_021D11A4(void)
{
    if (((gSystem.pressedKeys & PAD_BUTTON_A) == PAD_BUTTON_A) || ((gSystem.pressedKeys & PAD_BUTTON_START) == PAD_BUTTON_START) || ((gSystem.pressedKeys & PAD_BUTTON_SELECT) == PAD_BUTTON_SELECT)) {
        return 1;
    }

    return 0;
}

static void ov77_021D11CC(UnkStruct_ov77_021D17B4 *param0)
{
    param0->unk_08 = sub_02024220(param0->heapID, 0, 1, 0, 4, NULL);
    G2_SetBG0Priority(1);
}

static void ov77_021D11FC(UnkStruct_ov77_021D17B4 *param0)
{
    sub_020242C4(param0->unk_08);
}

static void ov77_021D1208(UnkStruct_ov77_021D1208 *param0, int param1, int param2, int heapID)
{
    void *v0;
    void *v1;
    NNSG3dResTex *v2;

    Heap_FndInitAllocatorForExpHeap(&param0->unk_70, heapID, 4);

    param0->unk_5C = NARC_AllocAndReadWholeMemberByIndexPair(NARC_INDEX_DEMO__TITLE__TITLEDEMO, param1, heapID);
    param0->unk_60 = NARC_AllocAndReadWholeMemberByIndexPair(NARC_INDEX_DEMO__TITLE__TITLEDEMO, param2, heapID);
    param0->unk_64 = NARC_AllocAndReadWholeMemberByIndexPair(NARC_INDEX_DEMO__TITLE__TITLEDEMO, 2, heapID);

    Easy3D_InitRenderObjFromResource(&param0->unk_04, &param0->unk_58, &param0->unk_5C);

    v0 = NNS_G3dGetAnmByIdx(param0->unk_60, 0);
    v1 = NNS_G3dGetAnmByIdx(param0->unk_64, 0);

    param0->unk_68 = NNS_G3dAllocAnmObj(&param0->unk_70, v0, param0->unk_58);
    param0->unk_6C = NNS_G3dAllocAnmObj(&param0->unk_70, v1, param0->unk_58);

    v2 = NNS_G3dGetTex(param0->unk_5C);

    NNS_G3dAnmObjInit(param0->unk_68, v0, param0->unk_58, v2);
    NNS_G3dAnmObjInit(param0->unk_6C, v1, param0->unk_58, v2);
    NNS_G3dRenderObjAddAnmObj(&param0->unk_04, param0->unk_68);
    NNS_G3dRenderObjAddAnmObj(&param0->unk_04, param0->unk_6C);

    {
        VecFx32 v3 = { 0, 0, 0 };
        VecFx32 v4 = { FX32_ONE, FX32_ONE, FX32_ONE };
        VecFx32 v5 = { 0, 0, 0 };

        param0->unk_80 = v3;
        param0->unk_8C = v4;
        param0->unk_98 = v5;
    }

    param0->unk_AC = 0;

    ov77_021D1300(param0, heapID);
}

static void ov77_021D1300(UnkStruct_ov77_021D1208 *param0, int heapID)
{
    NARC *v0 = NARC_ctor(NARC_INDEX_DEMO__TITLE__TITLEDEMO, heapID);

    {
        Easy3DModel_LoadFrom(&param0->unk_150, v0, 19, heapID);

        NNS_G3dMdlUseMdlAlpha(param0->unk_150.model);
        NNS_G3dMdlUseMdlPolygonID(param0->unk_150.model);

        Easy3DAnim_LoadFrom(&param0->unk_128, &param0->unk_150, v0, 21, heapID, &param0->unk_70);
        Easy3DAnim_SetFrame(&param0->unk_128, 0);

        Easy3DAnim_LoadFrom(&param0->unk_13C, &param0->unk_150, v0, 20, heapID, &param0->unk_70);
        Easy3DAnim_SetFrame(&param0->unk_13C, 0);

        Easy3DObject_Init(&param0->unk_B0, &param0->unk_150);

        Easy3DObject_SetPosition(&param0->unk_B0, 0, 0, 0);
        Easy3DObject_SetScale(&param0->unk_B0, (FX32_ONE), (FX32_ONE), (FX32_ONE));
        Easy3DObject_SetVisibility(&param0->unk_B0, 1);

        Easy3DObject_AddAnim(&param0->unk_B0, &param0->unk_128);
        Easy3DObject_AddAnim(&param0->unk_B0, &param0->unk_13C);
    }

    {
        Easy3DModel_LoadFrom(&param0->unk_200, v0, 16, heapID);
        NNS_G3dMdlUseMdlAlpha(param0->unk_200.model);
        NNS_G3dMdlUseMdlPolygonID(param0->unk_200.model);

        Easy3DAnim_LoadFrom(&param0->unk_1D8, &param0->unk_200, v0, 18, heapID, &param0->unk_70);
        Easy3DAnim_SetFrame(&param0->unk_1D8, 0);

        Easy3DAnim_LoadFrom(&param0->unk_1EC, &param0->unk_200, v0, 17, heapID, &param0->unk_70);
        Easy3DAnim_SetFrame(&param0->unk_1EC, 0);

        Easy3DObject_Init(&param0->unk_160, &param0->unk_200);

        Easy3DObject_SetPosition(&param0->unk_160, 0, 0, 0);
        Easy3DObject_SetScale(&param0->unk_160, (FX32_ONE), (FX32_ONE), (FX32_ONE));
        Easy3DObject_SetVisibility(&param0->unk_160, 1);

        Easy3DObject_AddAnim(&param0->unk_160, &param0->unk_1D8);
        Easy3DObject_AddAnim(&param0->unk_160, &param0->unk_1EC);
    }

    NARC_dtor(v0);

    param0->unk_214 = ((0x10000 - 0x3fef) - (0x10000 - 0x1c7d)) / 30;
    param0->unk_218 = (0x10000 - 0x1c7d);
    param0->unk_21C = (FX32_ONE);
    param0->unk_220 = (120 << 8);
}

static void ov77_021D14E4(UnkStruct_ov77_021D1208 *param0)
{
    ov77_021D1514(param0);

    NNS_G3dFreeAnmObj(&param0->unk_70, param0->unk_68);
    NNS_G3dFreeAnmObj(&param0->unk_70, param0->unk_6C);

    Heap_FreeToHeap(param0->unk_60);
    Heap_FreeToHeap(param0->unk_64);
    Heap_FreeToHeap(param0->unk_5C);
}

static void ov77_021D1514(UnkStruct_ov77_021D1208 *param0)
{
    Easy3DModel_Release(&param0->unk_150);
    Easy3DAnim_Release(&param0->unk_128, &param0->unk_70);
    Easy3DAnim_Release(&param0->unk_13C, &param0->unk_70);

    Easy3DModel_Release(&param0->unk_200);
    Easy3DAnim_Release(&param0->unk_1D8, &param0->unk_70);
    Easy3DAnim_Release(&param0->unk_1EC, &param0->unk_70);
}

static void ov77_021D1568(UnkStruct_ov77_021D1568 *param0, UnkStruct_ov77_021D1208 *param1)
{
    MtxFx33 v0 = { FX32_ONE, 0, 0, 0, FX32_ONE, 0, 0, 0, FX32_ONE };

    if ((param0->unk_29C == 0) && (param0->unk_2A0 == 1)) {
        ov77_021D25AC(param1->camera2);
        Camera_ComputeProjectionMatrix(0, param1->camera2);
        Camera_SetAsActive(param1->camera2);
    } else {
        Camera_ComputeProjectionMatrix(0, param1->camera1);
        Camera_SetAsActive(param1->camera1);
    }

    {
        fx32 v1;

        param0->unk_2A8 += 2;
        param0->unk_2A8 %= 360;

        v1 = CalcSineDegrees_Wraparound((param0->unk_2A8 * 0xffff) / 360);
        v1 *= 0.30;

        param1->unk_80.y -= v1;
    }

    switch (param1->unk_00) {
    case 0:
        break;
    case 1:
        sub_020241B4();
        G3_RequestSwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_W);
        param1->unk_00 = 0;
        break;
    case 2:
        sub_020241B4();
        Camera_ComputeViewMatrix();
        MTX_Rot33Vec(&v0, &param1->unk_98);

        if (param0->unk_29C == 0) {
            if (param0->unk_2A0 == 1) {
                ov77_021D1704(param1);
            } else {
                (void)0;
            }
        } else {
            DC_FlushAll();
            Easy3D_DrawRenderObj(&param1->unk_04, &param1->unk_80, &v0, &param1->unk_8C);
        }

        switch (param1->unk_AC) {
        case 0:
            param1->unk_68->frame = 0;
            param1->unk_6C->frame = 0;
            break;
        case 1:
            if (param1->unk_68->frame == 0) {
                param1->unk_AC = 0;
                break;
            }
        case 2:
            param1->unk_68->frame += (FX32_ONE);
            param1->unk_6C->frame += (FX32_ONE);

            if (param1->unk_68->frame == NNS_G3dAnmObjGetNumFrame(param1->unk_68)) {
                param1->unk_68->frame = 0;
            }

            if (param1->unk_6C->frame == NNS_G3dAnmObjGetNumFrame(param1->unk_6C)) {
                param1->unk_6C->frame = 0;
            }
            break;
        }

        G3_RequestSwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_W);
        break;
    }
}

static void ov77_021D1704(UnkStruct_ov77_021D1208 *param0)
{
    if (param0->unk_224 == 1) {
        if (Easy3DAnim_Update(&param0->unk_128, FX32_ONE) == 1) {
            param0->unk_224 = 2;
        }
    }

    if (param0->unk_225 == 1) {
        if (Easy3DAnim_Update(&param0->unk_13C, FX32_ONE) == 1) {
            param0->unk_225 = 2;
        }
    }

    Easy3DAnim_UpdateLooped(&param0->unk_1D8, FX32_ONE);
    Easy3DAnim_UpdateLooped(&param0->unk_1EC, FX32_ONE);

    NNS_G3dGePushMtx();

    {
        Easy3DObject_Draw(&param0->unk_160);

        if ((param0->unk_224 != 2) || (param0->unk_225 != 2)) {
            Easy3DObject_Draw(&param0->unk_B0);
        } else {
            Easy3DObject_SetVisibility(&param0->unk_B0, 0);
        }
    }

    NNS_G3dGePopMtx(1);
}

static void ov77_021D17B4(UnkStruct_ov77_021D17B4 *param0)
{
    param0->unk_04 = BgConfig_New(param0->heapID);

    {
        GraphicsModes v0 = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_3D
        };

        SetAllGraphicsModes(&v0);
    }

    {
        BgTemplate v1 = {
            0,
            0,
            0x800,
            0,
            1,
            GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0x2800,
            GX_BG_CHARBASE_0x04000,
            GX_BG_EXTPLTT_01,
            0,
            0,
            0,
            0
        };

        Bg_InitFromTemplate(param0->unk_04, BG_LAYER_SUB_0, &v1, 0);
    }
    {
        BgTemplate v2 = {
            0,
            0,
            0x1000,
            0,
            3,
            GX_BG_COLORMODE_256,
            GX_BG_SCRBASE_0x3000,
            GX_BG_CHARBASE_0x08000,
            GX_BG_EXTPLTT_01,
            0,
            0,
            0,
            0
        };

        Bg_InitFromTemplate(param0->unk_04, BG_LAYER_SUB_1, &v2, 0);
    }
    {
        BgTemplate v3 = {
            0,
            0,
            0x1000,
            0,
            3,
            GX_BG_COLORMODE_256,
            GX_BG_SCRBASE_0x3800,
            GX_BG_CHARBASE_0x10000,
            GX_BG_EXTPLTT_23,
            0,
            0,
            0,
            0
        };

        Bg_InitFromTemplate(param0->unk_04, BG_LAYER_SUB_2, &v3, 0);
    }
    {
        BgTemplate v4 = {
            0,
            0,
            0x800,
            0,
            1,
            GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0x3800,
            GX_BG_CHARBASE_0x04000,
            GX_BG_EXTPLTT_01,
            0,
            0,
            0,
            0
        };

        Bg_InitFromTemplate(param0->unk_04, BG_LAYER_MAIN_1, &v4, 0);
    }

    {
        BgTemplate v5 = {
            0,
            0,
            0x800,
            0,
            1,
            GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0x2000,
            GX_BG_CHARBASE_0x00000,
            GX_BG_EXTPLTT_01,
            3,
            0,
            0,
            0
        };

        Bg_InitFromTemplate(param0->unk_04, BG_LAYER_MAIN_3, &v5, 0);
    }
    {
        BgTemplate v6 = {
            0,
            0,
            0x800,
            0,
            1,
            GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0x2000,
            GX_BG_CHARBASE_0x00000,
            GX_BG_EXTPLTT_01,
            3,
            0,
            0,
            0
        };

        Bg_InitFromTemplate(param0->unk_04, BG_LAYER_SUB_3, &v6, 0);
    }

    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 0);
    Bg_MaskPalette(BG_LAYER_MAIN_0, 0x0);
    Bg_MaskPalette(BG_LAYER_SUB_0, 0x0);
}

static void ov77_021D1908(UnkStruct_ov77_021D17B4 *param0)
{
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 0);
    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 0);
    Bg_FreeTilemapBuffer(param0->unk_04, BG_LAYER_SUB_0);
    Bg_FreeTilemapBuffer(param0->unk_04, BG_LAYER_SUB_1);
    Bg_FreeTilemapBuffer(param0->unk_04, BG_LAYER_SUB_2);
    Bg_FreeTilemapBuffer(param0->unk_04, BG_LAYER_MAIN_1);
    Bg_FreeTilemapBuffer(param0->unk_04, BG_LAYER_MAIN_3);
    Bg_FreeTilemapBuffer(param0->unk_04, BG_LAYER_SUB_3);
    Heap_FreeToHeap(param0->unk_04);
}

static void ov77_021D1984(UnkStruct_ov77_021D1568 *param0, UnkStruct_ov77_021D1208 *param1)
{
    VecFx32 v0 = { 0, 0, 0 };
    CameraAngle v1 = { 0, 0, 0, 0 };
    int v2;

    if (param0->unk_29C == 1) {
        return;
    }

    if (param1->unk_210 < 60) {
        v0.z = -0xa00;
        Camera_Move(&v0, param1->camera2);
    }

    if (param1->unk_210 == 75) {
        param1->unk_224 = 1;
        param1->unk_225 = 1;
    }

    if (param1->unk_210 >= 250) {
        v1 = Camera_GetAngle(param1->camera2);
        v1.x = param1->unk_218;

        Camera_SetAngleAroundTarget(&v1, param1->camera2);

        param1->unk_218 += param1->unk_214;

        if (param1->unk_218 < (0x10000 - 0x3fef)) {
            param1->unk_218 = (0x10000 - 0x3fef);

            Camera_AdjustFOV(-(param1->unk_220 >> 8), param1->camera2);
            param1->unk_220 -= 0x280;

            if (param1->unk_220 < (16 << 8)) {
                param1->unk_220 = (16 << 8);
            }
        }
    }

    if (param1->unk_218 >= (0x10000 - 0x3fef)) {
        (void)0;
    }

    param1->unk_210++;
}

static const WindowTemplate Unk_ov77_021D72D0 = {
    0x4,
    0x2,
    0x13,
    0x1C,
    0x2,
    0x2,
    0x1
};

static BOOL ov77_021D1A60(UnkStruct_ov77_021D1568 *param0, BgConfig *param1, int param2)
{
    ov77_021D24C8(param0);
    ov77_021D2214(param1, param2, param0);
    ov77_021D1208(&param0->unk_04, 1, 0, param2);

    G3X_AntiAlias(1);
    G3X_AlphaBlend(1);

    {
        param0->unk_23C.x = param0->unk_270.x;
        param0->unk_23C.y = param0->unk_270.y;
        param0->unk_23C.z = param0->unk_270.z;
        param0->unk_248.x = param0->unk_258.x;
        param0->unk_248.y = param0->unk_258.y;
        param0->unk_248.z = param0->unk_258.z;
        param0->unk_04.camera1 = Camera_Alloc(param2);

        Camera_InitWithTargetAndPosition(&param0->unk_23C, &param0->unk_248, 0xb60, 0, 0, param0->unk_04.camera1);
        Camera_SetClipping(0, (FX32_ONE * 300), param0->unk_04.camera1);
        Camera_ComputeProjectionMatrix(0, param0->unk_04.camera1);
        Camera_SetAsActive(param0->unk_04.camera1);
    }
    {
        static const CameraAngle v0 = {
            (0x10000 - 0x1c7d),
            ((0 * 0xffff) / 360),
            ((0 * 0xffff) / 360),
        };
        VecFx32 v1 = { 0, 0, 0 };

        param0->unk_04.camera2 = Camera_Alloc(param2);

        Camera_InitWithTarget(&v1, (160 << FX32_SHIFT), &v0, ((22 * 0xffff) / 360), 0, 0, param0->unk_04.camera2);
        Camera_SetClipping(0, (FX32_ONE * 300), param0->unk_04.camera2);

        {
            VecFx32 v2 = { 0, 0, (0xa00 * 60) };
            Camera_Move(&v2, param0->unk_04.camera2);
        }

        Camera_SetAsActive(param0->unk_04.camera2);
    }
    {
        NNS_G3dGlbLightVector(0, param0->unk_288.x, param0->unk_288.y, param0->unk_288.z);
        NNS_G3dGlbLightColor(0, 0x7fff);
        NNS_G3dGlbLightVector(1, param0->unk_28E.x, param0->unk_28E.y, param0->unk_28E.z);
        NNS_G3dGlbLightColor(1, 0x7fff);
    }
    {
        G3X_AntiAlias(1);
    }

    gSystem.whichScreenIs3D = DS_SCREEN_SUB;
    GXLayers_SwapDisplay();
    param0->unk_04.unk_00 = 2;

    return 1;
}

static void ov77_021D1C10(UnkStruct_ov77_021D1568 *param0)
{
    BOOL v0 = 1;
    fx32 v1;
    fx32 v2 = 60;

    v1 = (param0->unk_27C.x - param0->unk_270.x) / v2;
    param0->unk_23C.x += (v1);

    v1 = (param0->unk_27C.y - param0->unk_270.y) / v2;
    param0->unk_23C.y += (v1);

    v1 = (param0->unk_27C.z - param0->unk_270.z) / v2;
    param0->unk_23C.z += (v1);

    v1 = (param0->unk_264.x - param0->unk_258.x) / v2;
    param0->unk_248.x += (v1);

    v1 = (param0->unk_264.y - param0->unk_258.y) / v2;
    param0->unk_248.y += (v1);

    v1 = (param0->unk_264.z - param0->unk_258.z) / v2;
    param0->unk_248.z += (v1);
}

static void ov77_021D1CC0(BgConfig *param0, int param1)
{
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_1);
    {
        BgTemplate v0 = {
            0,
            0,
            0x800,
            0,
            1,
            GX_BG_COLORMODE_16,
            GX_BG_SCRBASE_0x3000,
            GX_BG_CHARBASE_0x00000,
            GX_BG_EXTPLTT_01,
            1,
            0,
            0,
            0
        };

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_1, &v0, 0);
    }

    Graphics_LoadTilesToBgLayer(NARC_INDEX_DEMO__TITLE__TITLEDEMO, 23, param0, 5, 0, 0, 0, param1);
    Graphics_LoadTilemapToBgLayer(NARC_INDEX_DEMO__TITLE__TITLEDEMO, 25, param0, 5, 0, 0, 0, param1);

    G2_BlendNone();
    G2S_SetBlendAlpha(GX_BLEND_PLANEMASK_BG1, GX_BLEND_PLANEMASK_BG3, 10, 10);

    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 1);
}

static void ov77_021D1D48(BgConfig *param0, int param1)
{
    Bg_FreeTilemapBuffer(param0, BG_LAYER_SUB_0);

    {
        BgTemplate v0 = {
            0,
            0,
            0x1000,
            0,
            3,
            GX_BG_COLORMODE_256,
            GX_BG_SCRBASE_0x2800,
            GX_BG_CHARBASE_0x10000,
            GX_BG_EXTPLTT_23,
            2,
            0,
            0,
            0
        };

        Bg_InitFromTemplate(param0, BG_LAYER_SUB_0, &v0, 0);
    }

    Graphics_LoadTilemapToBgLayer(NARC_INDEX_DEMO__TITLE__TITLEDEMO, 22, param0, 4, 0, 0, 0, param1);

    G2S_SetBG0Priority(0);
    G2S_SetBG1Priority(1);
    G2S_SetBG2Priority(0);
    G2S_SetBG3Priority(2);

    Bg_SetOffset(param0, BG_LAYER_SUB_2, 0, 0);
    Bg_SetOffset(param0, BG_LAYER_SUB_2, 3, +1);

    G2S_SetBlendAlpha(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1, GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3, 26, 10);

    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 1);
}

static BOOL ov77_021D1DF0(UnkStruct_ov77_021D1568 *param0, BgConfig *param1, int heapID)
{
    BOOL v0 = 0;

    if (ov77_021D11A4() == 1) {
        param0->unk_29C = 1;
        param0->unk_2A0 = 0;
        FinishScreenFade();
        BrightnessController_ResetScreenController(BRIGHTNESS_BOTH_SCREENS);
        return 1;
    }

    switch (param0->unk_00) {
    case 0:
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
        param0->unk_296 = 0;
        param0->unk_22A = 15 + 252;
        StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_UNK_1, FADE_TYPE_UNK_1, FADE_TO_BLACK, 15, 3, heapID);
        param0->unk_00 = 1;
        break;
    case 1:
        if (IsScreenFadeDone() == TRUE) {
            if (param0->unk_22A) {
                param0->unk_22A--;
            } else {
                param0->unk_22A = 2;
                param0->unk_00 = 2;
            }
        }
        break;
    case 2:
        if ((BrightnessController_IsTransitionComplete(BRIGHTNESS_MAIN_SCREEN) == TRUE) && (BrightnessController_IsTransitionComplete(BRIGHTNESS_SUB_SCREEN) == TRUE)) {
            if (param0->unk_22A) {
                BrightnessController_StartTransition(10, 16, 0, (GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2), BRIGHTNESS_MAIN_SCREEN);
                BrightnessController_StartTransition(10, 16, 0, (GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BD), BRIGHTNESS_SUB_SCREEN);
                param0->unk_296 = 2;
                param0->unk_22A--;
                param0->unk_00 = 3;
            } else {
                param0->unk_22A = 0;
                param0->unk_00 = 4;
            }
        }
        break;
    case 3:
        if ((BrightnessController_IsTransitionComplete(BRIGHTNESS_MAIN_SCREEN) == TRUE) && (BrightnessController_IsTransitionComplete(BRIGHTNESS_SUB_SCREEN) == TRUE)) {
            BrightnessController_StartTransition(10, 0, 16, (GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2), BRIGHTNESS_MAIN_SCREEN);
            BrightnessController_StartTransition(10, 0, 16, (GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BD), BRIGHTNESS_SUB_SCREEN);
            param0->unk_296 = 3;
            param0->unk_00 = 2;
        }
        break;
    case 4:
        if (param0->unk_22A) {
            param0->unk_22A--;
        } else {
            param0->unk_22A = 1;
            param0->unk_00 = 5;
        }
        break;
    case 5:
        if (IsScreenFadeDone() == TRUE) {
            if (param0->unk_22A) {
                StartScreenFade(FADE_BOTH_SCREENS, FADE_TYPE_UNK_0, FADE_TYPE_UNK_0, FADE_TO_WHITE, 5, 2, heapID);
                param0->unk_296 = 2;
                param0->unk_22A--;
                param0->unk_00 = 6;
            } else {
                param0->unk_22A = 10;
                param0->unk_00 = 8;
                param0->unk_29C = 1;
                SetScreenColorBrightness(DS_SCREEN_MAIN, FADE_TO_BLACK);
            }
        }
        break;
    case 6:
        if (IsScreenFadeDone() == TRUE) {
            param0->unk_2A0 = 0;
            {
                GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG1, 1);
            }
            param0->unk_04.unk_AC = 2;
            StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_UNK_1, FADE_TYPE_UNK_1, FADE_TO_WHITE, 16, 3, heapID);
            param0->unk_00 = 5;
        }
        break;
    case 8:
        if (param0->unk_22A) {
            param0->unk_22A--;
        } else {
            param0->unk_00 = 7;
        }
        break;
    case 7:
        StartScreenFade(FADE_MAIN_ONLY, FADE_TYPE_UNK_1, FADE_TYPE_UNK_1, FADE_TO_BLACK, 48, 1, heapID);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        param0->unk_00 = 9;
        param0->unk_2A4 = 0;
        break;
    case 9: {
        ov77_021D1C10(param0);
        Camera_SetTarget(&param0->unk_23C, param0->unk_04.camera1);
        Camera_SetPosition(&param0->unk_248, param0->unk_04.camera1);

        param0->unk_2A4++;

        if (param0->unk_2A4 >= 60) {
            {
                GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
            }
            {
                ov77_021D1CC0(param1, heapID);
            }
            StartScreenFade(FADE_SUB_ONLY, FADE_TYPE_UNK_1, FADE_TYPE_UNK_1, FADE_TO_WHITE, 16, 3, heapID);
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 1);
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);
            param0->unk_22A = 90;
            param0->unk_00 = 10;
        }
    } break;
    case 10:
        if (param0->unk_22A) {
            param0->unk_22A--;
        } else {
            if (IsScreenFadeDone() == TRUE) {
                v0 = 1;
            }
        }
        break;
    }

    ov77_021D2438(param0);
    ov77_021D1984(param0, &param0->unk_04);
    ov77_021D1568(param0, &param0->unk_04);

    return v0;
}

static BOOL ov77_021D20E4(UnkStruct_ov77_021D1568 *param0, BgConfig *param1, int param2)
{
    BOOL v0 = 0;

    switch (param0->unk_00) {
    case 0:
        Camera_SetTarget(&param0->unk_27C, param0->unk_04.camera1);
        Camera_SetPosition(&param0->unk_264, param0->unk_04.camera1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG0, 1);
        GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG3, 1);
        GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG3, 1);

        {
            GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG2, 1);
        }

        {
            GXLayers_EngineAToggleLayers(GX_PLANEMASK_BG1, 1);
        }

        ResetScreenMasterBrightness(DS_SCREEN_MAIN);
        ResetScreenMasterBrightness(DS_SCREEN_SUB);

        param0->unk_04.unk_AC = 2;
        NNS_G3dGlbLightColor(1, 0x7fff);

        {
            ov77_021D1CC0(param1, param2);
        }

        param0->unk_22A = 0;
        param0->unk_00 = 1;
        break;
    case 1:
        if (param0->unk_254 == 1) {
            if (param0->unk_22A == 0) {
                {
                    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 1);
                }
            } else if (param0->unk_22A == 0x10) {
                {
                    GXLayers_EngineBToggleLayers(GX_PLANEMASK_BG0, 0);
                }
            }
        } else {
            (void)0;
        }

        param0->unk_22A++;
        param0->unk_22A &= 0x1f;

        v0 = 1;
        break;
    }

    ov77_021D1568(param0, &param0->unk_04);

    return v0;
}

static BOOL ov77_021D21C0(UnkStruct_ov77_021D1568 *param0, BgConfig *param1, int param2)
{
    Camera_Delete(param0->unk_04.camera1);
    Camera_Delete(param0->unk_04.camera2);

    ov77_021D14E4(&param0->unk_04);
    ov77_021D2428(param1, param2, param0);

    G2_BlendNone();
    G3X_EdgeMarking(0);

    gSystem.whichScreenIs3D = DS_SCREEN_MAIN;
    GXLayers_SwapDisplay();

    return 1;
}

static void ov77_021D2214(BgConfig *param0, int heapID, UnkStruct_ov77_021D1568 *param2)
{
    {
        int v0, v1;

        Graphics_LoadTilesToBgLayer(NARC_INDEX_DEMO__TITLE__TITLEDEMO, 23, param0, 7, 0, 0, 0, heapID);
        Graphics_LoadTilesToBgLayer(NARC_INDEX_DEMO__TITLE__TITLEDEMO, 26, param0, 3, 0, 0, 0, heapID);
        Graphics_LoadTilemapToBgLayer(NARC_INDEX_DEMO__TITLE__TITLEDEMO, 24, param0, 7, 0, 0, 0, heapID);
        Graphics_LoadTilemapToBgLayer(NARC_INDEX_DEMO__TITLE__TITLEDEMO, 27, param0, 3, 0, 0, 0, heapID);

        v0 = 7;
        v1 = 6;

        Graphics_LoadPalette(NARC_INDEX_DEMO__TITLE__TITLEDEMO, v0, 4, 0, 0, heapID);
        Graphics_LoadPalette(NARC_INDEX_DEMO__TITLE__TITLEDEMO, v1, 0, 0, 0, heapID);
    }
    {
        int v2, v3;

        v2 = 12;
        v3 = 11;

        Graphics_LoadTilesToBgLayer(NARC_INDEX_DEMO__TITLE__TITLEDEMO, v2, param0, 6, 0, 0, 0, heapID);
        Graphics_LoadPalette(NARC_INDEX_DEMO__TITLE__TITLEDEMO, v3, 6, 0x4000, 0, heapID);
        Graphics_LoadTilemapToBgLayer(NARC_INDEX_DEMO__TITLE__TITLEDEMO, 22, param0, 6, 0, 0, 0, heapID);
    }
    {
        Graphics_LoadTilesToBgLayer(NARC_INDEX_DEMO__TITLE__OP_DEMO, 14, param0, 5, 0, 0, 0, heapID);
        Graphics_LoadPalette(NARC_INDEX_DEMO__TITLE__OP_DEMO, 13, 6, 0x2000, 0, heapID);
        Graphics_LoadTilemapToBgLayer(NARC_INDEX_DEMO__TITLE__OP_DEMO, 12, param0, 5, 0, 0, 0, heapID);
    }
    {
        Graphics_LoadTilesToBgLayer(NARC_INDEX_DEMO__TITLE__TITLEDEMO, 5, param0, 1, 0, 0, 0, heapID);
        Graphics_LoadTilemapToBgLayer(NARC_INDEX_DEMO__TITLE__TITLEDEMO, 3, param0, 1, 0, 0, 0, heapID);
        Graphics_LoadPalette(NARC_INDEX_DEMO__TITLE__TITLEDEMO, 4, 0, 32 * 1, 32 * 3, heapID);
    }

    Bg_MaskPalette(BG_LAYER_MAIN_0, 0x0);
    Bg_MaskPalette(BG_LAYER_SUB_0, 0x0);

    {
        MessageLoader *v4;
        Strbuf *v5;
        u32 v6;

        Bg_ClearTilesRange(4, 32, 0, heapID);

        v4 = MessageLoader_Init(MESSAGE_LOADER_NARC_HANDLE, NARC_INDEX_MSGDATA__PL_MSG, TEXT_BANK_UNK_0609, heapID);
        v5 = Strbuf_Init(64, heapID);

        Window_AddFromTemplate(param0, &param2->unk_22C, &Unk_ov77_021D72D0);
        Window_FillRectWithColor(&param2->unk_22C, 0, 0, 0, 28 * 8, 2 * 8);
        MessageLoader_GetStrbuf(v4, 0, v5);

        v6 = Font_CalcCenterAlignment(FONT_SYSTEM, v5, 1, param2->unk_22C.width * 8);

        Text_AddPrinterWithParamsColorAndSpacing(&param2->unk_22C, FONT_SYSTEM, v5, v6, 0, TEXT_SPEED_INSTANT, TEXT_COLOR(1, 1, 0), 1, 0, NULL);
        Strbuf_Free(v5);
        MessageLoader_Free(v4);

        {
            u16 v7 = 0x15;
            u16 v8 = 0x15;

            Bg_LoadPalette(4, &v7, 2, (16 * 2) * 2 + 2 * 1);
            Bg_LoadPalette(4, &v8, 2, (16 * 2) * 2 + 2 * 2);
        }
    }
}

static void ov77_021D2428(BgConfig *param0, int param1, UnkStruct_ov77_021D1568 *param2)
{
    Window_Remove(&param2->unk_22C);
}

static void ov77_021D2438(UnkStruct_ov77_021D1568 *param0)
{
    switch (param0->unk_296) {
    case 0:
        param0->unk_294 = 5;
        param0->unk_296 = 1;
        break;
    case 1:
        break;
    case 2:
        param0->unk_294 += 2;

        if (param0->unk_294 >= 0x1f) {
            param0->unk_294 = 0x1f;
            param0->unk_296 = 1;
        }
        break;
    case 3:
        param0->unk_294 -= 2;

        if (param0->unk_294 <= 5) {
            param0->unk_294 = 5;
            param0->unk_296 = 1;
        }
        break;
    }

    NNS_G3dGlbLightColor(1, (((param0->unk_294 << 0) & 0x1f) | ((param0->unk_294 << 5) & 0x3e0) | ((param0->unk_294 << 10) & 0x7c00)));
}

static void ov77_021D24C8(UnkStruct_ov77_021D1568 *param0)
{
    param0->unk_258.x = (((fx32)0x00001000L) * 0);
    param0->unk_258.y = (((fx32)0x00001000L) * 192);
    param0->unk_258.z = (((fx32)0x00001000L) * 600);

    param0->unk_264.x = (((fx32)0x00001000L) * -64);
    param0->unk_264.y = (((fx32)0x00001000L) * 192);
    param0->unk_264.z = (((fx32)0x00001000L) * 484);

    param0->unk_270.x = (((fx32)0x00001000L) * 0);
    param0->unk_270.y = (((fx32)0x00001000L) * 100);
    param0->unk_270.z = (((fx32)0x00001000L) * -18);

    param0->unk_27C.x = (((fx32)0x00001000L) * 0);
    param0->unk_27C.y = (((fx32)0x00001000L) * 100);
    param0->unk_27C.z = (((fx32)0x00001000L) * -18);

    param0->unk_288.x = 2267;
    param0->unk_288.y = -1953;
    param0->unk_288.z = -2797;

    param0->unk_28E.x = -2267;
    param0->unk_28E.y = 1953;
    param0->unk_28E.z = -2797;
    param0->unk_298 = (FX32_ONE * 3);

    {
        VecFx32 v0, v1;

        VEC_Subtract(&param0->unk_27C, &param0->unk_264, &v0);
        VEC_Normalize(&v0, &v1);

        param0->unk_288.x = v1.x;
        param0->unk_288.y = v1.y;
        param0->unk_288.z = v1.z;
    }
}

static void ov77_021D25AC(Camera *camera)
{
    return;
}
