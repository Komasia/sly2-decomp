/* BUTTON (class 83, derived from SO) and VOLBTN (class 24, derived from class 22, an XFM) share the BTN component
 * (Sly 1 btn.c), embedded right after the parent part. The BUTTON / VOLBTN entry points around 0x1490A0 / 0x149718
 * forward to the BTN functions at 0x1487A0..0x148B78; arguments after the first reach them unchanged in registers. */
#ifndef BUTTON_H
#define BUTTON_H
#include "so.h"

typedef struct BTN {
    /* 0x00 */ void *paloOwner;        /* the BUTTON / VOLBTN the component belongs to */
    /* 0x04 */ char unk_0x04[0x0c];
} BTN;

typedef struct BUTTON {
    /* 0x000 */ SO so;
    /* 0x150 */ BTN btn;
} BUTTON;

typedef struct VOLBTN {
    /* 0x000 */ XFM xfm;
    /* 0x0e0 */ char unk_0xe0[0x50];   /* class 22 */
    /* 0x130 */ BTN btn;
} VOLBTN;

#endif
