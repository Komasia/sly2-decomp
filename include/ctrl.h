/* CTRL: a controller of a transform record (XF) of an object: the base of CTRLASEG, CTRLPOS, CTRLLOOKAT,
 * CTRLTARGET, ... (C++ classes with virtuals). Layout: SafeHouse port (xf.h CTRL). */
#ifndef CTRL_H
#define CTRL_H

struct ALO;
struct XF;

typedef struct CTRL {
    /* 0x00 */ int kind;             /* field: SafeHouse port */
    /* 0x04 */ struct ALO *palo;     /* field: SafeHouse port - the record's object */
    /* 0x08 */ struct XF *pxf;       /* field: SafeHouse port */
    /* 0x0c */ int prio;             /* field: SafeHouse port (higher first) */
    /* 0x10 */ struct CTRL *pnext;   /* field: SafeHouse port */
    /* 0x14 */ int mode;             /* field: SafeHouse port - the record's mode while it is the head */
} CTRL;

#endif
