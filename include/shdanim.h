/* Sly 2 shader-texture animations (Sly 1 shd.h SAA / shdanim.h): SAA (class 138, abstract) and its subclasses
 * LOOP (139), PINGPONG (140), SHUFFLE (141), EYES (142), SCROLLER (143), CIRCLER (144). Partial layout from the
 * matched Sly 2 code: in Sly 2 the SAA is a BASIC-derived object (vtable at +0x0C) and the subclass fields start at
 * +0x50 (Sly 1: +0x2C); the frame count of the animated shader is kept in the SAA itself. */
#ifndef SHDANIM_H
#define SHDANIM_H
#include "so.h"

/* animation settings from the level file (Sly 1 SAAF, with eight more bytes in front) */
typedef struct SAAF {
    /* 0x00 */ char unk_0x00[0xc];
    /* 0x0c */ float dtLoopMin;
    /* 0x10 */ float dtLoopMax;
    /* 0x14 */ float dtPauseMin;
    /* 0x18 */ float dtPauseMax;
} SAAF;

typedef struct SAA {
    /* 0x00 */ BASIC basic;
    /* 0x10 */ float tUpdates;         /* g_clock.t of the last update */
    /* 0x14 */ int oid;                /* shader the animation drives */
    /* 0x18 */ int unk_0x18;
    /* 0x1c */ int cframe;             /* frames of the animated shader */
    /* 0x20 */ char unk_0x20[0x34 - 0x20];
    /* 0x34 */ int sai;                /* SAI (shader animation instance), not mapped */
    /* 0x38 */ char unk_0x38[0x50 - 0x38];
} SAA;

typedef struct LOOP {
    /* 0x00 */ SAA saa;
    /* 0x50 */ float dtLoopMin;
    /* 0x54 */ float dtLoopMax;
    /* 0x58 */ float dtPauseMin;
    /* 0x5c */ float dtPauseMax;
    /* 0x60 */ float dframe;           /* frames per second of the current loop */
    /* 0x64 */ float iframe;
    /* 0x68 */ float dtPause;
    /* 0x6c */ float dtPauseRemaining;
} LOOP;

typedef struct SCROLLER {
    /* 0x00 */ SAA saa;
    /* 0x50 */ float duSpeed;
    /* 0x54 */ float dvSpeed;
    /* 0x58 */ float du;
    /* 0x5c */ float dv;
    /* 0x60 */ float su;
    /* 0x64 */ float sv;
} SCROLLER;

typedef struct CIRCLER {
    /* 0x00 */ SAA saa;
    /* 0x50 */ float radsSpeed;
    /* 0x54 */ float radius;
    /* 0x58 */ float duCenter;
    /* 0x5c */ float dvCenter;
} CIRCLER;

/* shader header (partial) */
typedef struct SHD {
    /* 0x00 */ int oid;
} SHD;

#endif
