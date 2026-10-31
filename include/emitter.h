/* EMITTER (class 29) and EXPLO (class 32), both derived from XFM: each points at a reference-counted EMITB (emitter
 * settings block, shared between clones) at +0xE4. EXPLG (class 31) keeps an array of child explosions there instead. */
#ifndef EMITTER_H
#define EMITTER_H
#include "so.h"

typedef struct EMITB {
    /* 0x00 */ int cref;               /* clones share the block */
} EMITB;

typedef struct EMITTER {
    /* 0x000 */ XFM xfm;
    /* 0x0e0 */ int unk_0xe0;
    /* 0x0e4 */ EMITB *pemitb;
} EMITTER;

typedef struct EXPLO {
    /* 0x000 */ XFM xfm;
    /* 0x0e0 */ int unk_0xe0;
    /* 0x0e4 */ EMITB *pemitb;
} EXPLO;

typedef struct EXPLG {
    /* 0x000 */ XFM xfm;
    /* 0x0e0 */ int cpexpl;
    /* 0x0e4 */ void **apexpl;
} EXPLG;

#endif
