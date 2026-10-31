/* Sly 2 joypad (Sly 1 joy.c / joy.h). JOY layout after Lilly's Sly 2 types (src/hand/func_001E3890.cpp) with Sly 1's
 * field names; Sly 2 embeds the RUMBLE (Sly 1: a pointer) and keeps the DMA buffer of libpad at the front. */
#ifndef JOY_H
#define JOY_H
#include "common.h"
#include "util.h"
#include "rumble.h"

enum JOYS { JOYS_Initing = 0, JOYS_Searching = 1, JOYS_Waiting = 2, JOYS_Ready = 3, JOYS_Max = 4 };
enum JOYK { JOYK_Unknown = 0, JOYK_Digital = 1, JOYK_Analog = 2, JOYK_Shock = 3, JOYK_Shock2 = 4, JOYK_Max = 5 };

/* g_grfusr bits: who is using the pad (Sly 1 FUSR; Sly 2 has more) */
enum FUSR { FUSR_Menu = 0x1, FUSR_HandsOff = 0x2, FUSR_NoPause = 0x4 };

struct JOY {
    /* 0x0000 */ byte abPadDma[0x1000];   /* scePadPortOpen buffer */
    /* 0x1000 */ int nPort;
    /* 0x1004 */ int nSlot;
    /* 0x1008 */ int term;
    /* 0x100c */ JOYS joys;
    /* 0x1010 */ JOYK joyk;
    /* 0x1014 */ float tJoys;             /* g_clock.tReal of the last state change */
    /* 0x1018 */ float tRead;
    /* 0x101c */ float tActive;
    /* 0x1020 */ int dtIdle;
    /* 0x1024 */ int unk_0x1024;
    /* 0x1028 */ int unk_0x1028;
    /* 0x102c */ int unk_0x102c[4];
    /* 0x103c */ float dxLeft;
    /* 0x1040 */ float dyLeft;
    /* 0x1044 */ float uDeflectLeft;
    /* 0x1048 */ byte bXLeft;
    /* 0x1049 */ byte bYLeft;
    /* 0x104a */ ushort unk_0x104a;
    /* 0x104c */ int fStickMovedLeft;
    /* 0x1050 */ LM almDeflect[4];
    /* 0x1070 */ float dxRight;
    /* 0x1074 */ float dyRight;
    /* 0x1078 */ float sRight;
    /* 0x107c */ byte bXRight;
    /* 0x107d */ byte bYRight;
    /* 0x107e */ ushort unk_0x107e;
    /* 0x1080 */ int fStickMovedRight;
    /* 0x1084 */ LM almDeflect2[4];
    /* 0x10a4 */ float dxdtLeft;
    /* 0x10a8 */ float dydtLeft;
    /* 0x10ac */ float dxdtRight;
    /* 0x10b0 */ float dydtRight;
    /* 0x10b4 */ uint grfbtn;             /* buttons down */
    /* 0x10b8 */ uint grfbtnPressed;      /* buttons that went down this frame */
    /* 0x10bc */ uint grfbtnLatched;
    /* 0x10c0 */ byte mpbtnpb[12];        /* pressure per button */
    /* 0x10cc */ RUMBLE rumble;
    /* 0x10e8 */ int fRumbleEnabled;
    /* 0x10ec */ float uDpad;
    /* 0x10f0 */ int unk_0x10f0[4];
};

extern JOY g_joy;
extern int g_grfjoyt;   /* what the game may read from the pad, from g_grfusr */
extern int g_grfusr;    /* FUSR_* */

void UpdateGrfjoytFromGrfusr();
void InitJoy(JOY *pjoy, int nPort, int nSlot);
void SetJoyJoys(JOY *pjoy, JOYS joys, JOYK joyk);

#endif
