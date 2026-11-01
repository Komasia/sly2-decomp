/* Sly 2 world (SW, class 1, 0x4790 bytes; Sly 1 sw.c), partial: only the fields the cleaned sources use, with Lilly's
 * Sly 2 names (src/hand/func_0020E3C0.cpp / func_0020F318.cpp, "ported from Lilly's personal Sly 2 decomp"). The
 * offsets were checked against the matched code (counter pairs at 0x3D78..0x3D84, the lighting setters at
 * 0x3E10..0x3E24, the two 12-byte allocation arrays at 0x39D0 / 0x39D8). The game's world is g_sw (Lilly: g_sw). */
#ifndef SW_H
#define SW_H
#include "so.h"

typedef struct SWREC12 { int an[3]; } SWREC12;   /* 12-byte record (meaning unknown) */

typedef struct SW {
    /* 0x0000 */ BASIC basic;
    /* 0x0010 */ char unk_0x10[0x39d0 - 0x10];
    /* 0x39d0 */ SWREC12 *aUnk39d0;        /* 12-byte records, handed out by func_00210100 */
    /* 0x39d4 */ int cUnk39d4;
    /* 0x39d8 */ SWREC12 *aUnk39d8;        /* 12-byte records, handed out by func_00210120 */
    /* 0x39dc */ int cUnk39dc;
    /* 0x39e0 */ char unk_0x39e0[0x3d78 - 0x39e0];
    /* 0x3d78 */ int cHandsOff;           /* > 0: the player has no control (FUSR_HandsOff) */
    /* 0x3d7c */ int cNoPause;            /* > 0: the game may not be paused (FUSR_NoPause) */
    /* 0x3d80 */ int cUnk3d80;
    /* 0x3d84 */ int cUnk3d84;
    /* 0x3d88 */ char unk_0x3d88[0x3e10 - 0x3d88];
    /* 0x3e10 */ qword hsvLight;
    /* 0x3e20 */ float gLightScale;
    /* 0x3e24 */ float gMidtone;
    /* 0x3e28 */ char unk_0x3e28[0x4790 - 0x3e28];
} SW;

extern SW g_sw;   /* the world (Lilly: g_sw) */

#endif
