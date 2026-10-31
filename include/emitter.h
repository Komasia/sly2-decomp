/* EMITTER (class 29) and EXPLO (class 32), both derived from XFM: each points at a reference-counted EMITB (emitter
 * settings block, shared between clones) at +0xE4. EXPLG (class 31) keeps an array of child explosions there instead. */
#ifndef EMITTER_H
#define EMITTER_H
#include "so.h"

typedef struct EMITB {
    /* 0x00 */ int cref;               /* clones share the block */
    /* 0x04 */ char unk_0x04[0xd4 - 0x04];
    /* 0xd4 */ float sExpand;          /* particle (RIP) expansion, copied to the RIPG (Sly 1: emitp.emitrip.sExpand) */
} EMITB;

typedef struct EMITTER {
    /* 0x000 */ XFM xfm;
    /* 0x0e0 */ int fValuesChanged;    /* set when the settings change; OnEmitterValuesChanged clears it */
    /* 0x0e4 */ EMITB *pemitb;
    /* 0x0e8 */ char unk_0xe8[0x114 - 0xe8];
    /* 0x114 */ int fAutoPause;
    /* 0x118 */ char unk_0x118[0x148 - 0x118];
    /* 0x148 */ float tUnpause;        /* g_clock.t at which a paused emitter resumes; -1: not paused */
    /* 0x14c */ struct RIPG *pripg;
} EMITTER;

/* Sly 1 ensure.h: whether a Pemitb/PemitterEnsure caller reads or writes the settings */
#ifndef ENSK_DEFINED
#define ENSK_DEFINED
typedef enum ENSK { ENSK_Get = 0, ENSK_Set = 1 } ENSK;
#endif

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
