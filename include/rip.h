/* RIP (a particle) and RIPG (class 87, derived from SO: the group that owns and renders particles); Sly 1 rip.c.
 * Partial layouts from the matched Sly 2 code. */
#ifndef RIP_H
#define RIP_H
#include "so.h"

struct RIPG;

typedef struct RIP {
    /* 0x00 */ int unk_0x00;
    /* 0x04 */ int cref;
    /* 0x08 */ struct RIPG *pripg;
} RIP;

typedef struct RIPG {
    /* 0x000 */ SO so;
    /* 0x150 */ char unk_0x150[0x158 - 0x150];
    /* 0x158 */ float sExpand;
    /* 0x15c */ DL dlRip;              /* the group's particles */
} RIPG;

#endif
