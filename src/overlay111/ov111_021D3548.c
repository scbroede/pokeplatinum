#include "overlay111/ov111_021D3548.h"

#include <nitro.h>
#include <string.h>

#include "bg_window.h"
#include "render_window.h"

static const WindowTemplate Unk_ov111_021D38B8[] = {
    { 0x2, 0x2, 0x1, 0x1B, 0x4, 0xC, 0x1 },
    { 0x4, 0x18, 0xD, 0x7, 0x4, 0xD, 0x6D },
    { 0x4, 0x11, 0x3, 0xB, 0x5, 0xD, 0x89 },
    { 0x4, 0x11, 0x8, 0xB, 0x5, 0xD, 0xC0 },
    { 0x4, 0x11, 0xE, 0xB, 0x5, 0xD, 0xF7 },
    { 0x4, 0x11, 0x13, 0xB, 0x5, 0xD, 0x12E },
    { 0x4, 0xA, 0x3, 0x5, 0x3, 0xD, 0x165 },
    { 0x4, 0xA, 0x8, 0x5, 0x3, 0xD, 0x174 },
    { 0x4, 0xA, 0xE, 0x5, 0x3, 0xD, 0x183 },
    { 0x4, 0xA, 0x13, 0x5, 0x3, 0xD, 0x192 },
    { 0x2, 0xA, 0x9, 0xC, 0x4, 0xD, 0x1A1 },
    { 0x2, 0xA, 0x9, 0xC, 0x4, 0xD, 0x1A1 },
    { 0x2, 0xA, 0x9, 0xC, 0x4, 0xD, 0x1A1 },
    { 0x2, 0xA, 0x15, 0xD, 0x3, 0xD, 0x1D1 },
    { 0x2, 0xD, 0x15, 0xD, 0x3, 0xD, 0x1D1 },
    { 0x4, 0x2, 0x13, 0x1B, 0x4, 0xC, 0x1 }
};

void ov111_021D3548(BgConfig *param0, Window *param1);
void ov111_021D3578(Window *param0);
void ov111_021D3594(BgConfig *param0, Window *param1);
void ov111_021D35C0(Window *param0, int param1);

void ov111_021D3548(BgConfig *param0, Window *param1)
{
    u8 v0;
    const WindowTemplate *v1 = Unk_ov111_021D38B8;

    for (v0 = 0; v0 < 16; v0++) {
        Window_AddFromTemplate(param0, &param1[v0], &v1[v0]);
        Window_FillTilemap(&param1[v0], 0);
    }

    return;
}

void ov111_021D3578(Window *param0)
{
    u16 v0;

    for (v0 = 0; v0 < 16; v0++) {
        Window_Remove(&param0[v0]);
    }

    return;
}

void ov111_021D3594(BgConfig *param0, Window *param1)
{
    LoadStandardWindowGraphics(param0, BG_LAYER_MAIN_2, (1024 - 9), 11, 0, HEAP_ID_115);
    Window_DrawStandardFrame(param1, 1, (1024 - 9), 11);

    return;
}

void ov111_021D35C0(Window *param0, int param1)
{
    LoadMessageBoxGraphics(param0->bgConfig, Window_GetBgLayer(param0), ((1024 - 9) - (18 + 12)), 10, param1, HEAP_ID_115);
    Window_FillTilemap(param0, 15);
    Window_DrawMessageBoxWithScrollCursor(param0, 0, ((1024 - 9) - (18 + 12)), 10);

    return;
}
