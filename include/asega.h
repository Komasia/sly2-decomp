/* ASEGA: a playing animation segment (Sly 1 asega.c; Sly 2 module 0x12F8C0-0x131E18), 0x60 bytes from the slot heap
 * D_003E1224, a BASIC (the ASEG's scripts get it as their object). The running ones are in the list D_003E1218.
 * Layout: SafeHouse port (asega.h ASEGA); only the fields the C sources use. */
#ifndef ASEGA_H
#define ASEGA_H

struct ASEG;
struct ALO;
struct CTRLASEG;

typedef struct ASEGA {
    /* 0x00 */ void *pvtbasic;            /* BASIC vtable */
    /* 0x04 */ char pad4[0x10 - 0x04];    /* (the BASIC's DL links) */
    /* 0x10 */ int cref;                  /* field: SafeHouse port - references (AddRefAsega / ReleaseAsega) */
    /* 0x14 */ struct ASEG *paseg;        /* field: SafeHouse port */
    /* 0x18 */ struct ALO *palo;          /* field: SafeHouse port (null: the objects of the ASEG's namespace) */
    /* 0x1c */ float t;                   /* field: SafeHouse port */
    /* 0x20 */ float tEvent;              /* field: SafeHouse port - the event scan's time */
    /* 0x24 */ char pad24[0x34 - 0x24];
    /* 0x34 */ struct CTRLASEG *pctrlFirst;  /* field: SafeHouse port - the channels' controllers */
    /* 0x38 */ void *palink;              /* field: SafeHouse port - the scalar links */
    /* 0x3c */ int grfapl;                /* field: SafeHouse port */
    /* 0x40 */ float svt;                 /* field: SafeHouse port - the effective speed */
    /* 0x44 */ float svtLocal;            /* field: SafeHouse port - the speed asked for */
    /* 0x48 */ float svtAseg;             /* field: SafeHouse port - the ASEG's speed */
    /* 0x4c */ float svtSuck;             /* field: SafeHouse port - from the suck history */
    /* 0x50 */ int iea;                   /* field: SafeHouse port - the next timed event */
    /* 0x54 */ int ieaEnd;                /* field: SafeHouse port - the end list's next event */
    /* 0x58 */ int fSound;                /* field: SafeHouse port */
    /* 0x5c */ int pad5C;
} ASEGA;

#endif
