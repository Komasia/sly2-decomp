/* Sly 2 engine clock (Sly 1 clock.h CLOCK). Sly 2 moved t to the front and added camera / per-kind rates;
 * layout after Lilly's Sly 2 types (src/hand/func_001E3890.cpp). g_clock lives at 0x2DDED0. */
#ifndef CLOCK_H
#define CLOCK_H

typedef unsigned long long TICK;

enum CRK { CRK_Max = 9 };

typedef struct CLOCK {
    /* 0x00 */ float t;            /* game time */
    /* 0x04 */ float dt;           /* game time since the last frame */
    /* 0x08 */ float rt;
    /* 0x0c */ float rtCm;
    /* 0x10 */ float dtCm;
    /* 0x14 */ float tCm;
    /* 0x18 */ float art[CRK_Max];
    /* 0x3c */ float tReal;        /* t at the EE clock rate */
    /* 0x40 */ float dtReal;
    /* 0x44 */ int unk_0x44;
    /* 0x48 */ TICK tickFrame;
    /* 0x50 */ TICK tickLastRaw;
    /* 0x58 */ int cWrapAround;
    /* 0x5c */ int unk_0x5c;
} CLOCK;

extern CLOCK g_clock;

#endif
