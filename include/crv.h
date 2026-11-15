/* CRV: a path curve (Sly 1 CRV / CRVL / CRVC; Sly 2's PATH objects, cid 0x0A (CID_PATH, base XFM), code
 * 0x1E5D80..0x1E7D90): a linear or cubic (Hermite) curve through points in the object's frame, with parameters
 * (times) and distances along it in the world. It is part of the path object, so the offsets below are from the
 * object. Layout: SafeHouse port (crv.h CRV; rope.cpp, spawner.cpp); only the fields the C sources use.
 * A path that a script turns into a rope gets a ROPE simulation at +0x17C (h3_rope.h), one the AI walks a
 * PATHREC at +0x180 (h3_rope.h). */
#ifndef CRV_H
#define CRV_H

#include "vtbl.h"

#ifndef SLY2_QWORD
#define SLY2_QWORD
typedef int qword __attribute__((mode(TI)));
#endif

struct ROPE;
struct PATHREC;

/* crvk */
#define CRVK_Linear 0   /* straight segments between the points */
#define CRVK_Cubic  1   /* Hermite segments with in / out tangents (avIn / avOut) */

#define CSUB_CRV 11     /* the cached segment's sub-lengths: at parameter fractions 0, 0.1, ..., 1 */

typedef struct CRV {
    /* 0x000 */ char pad0[0xc];
    /* 0x00c */ VTENT *pvt;         /* the object's vtable (LO); slot 31 (entry 31): its world matrix */
    /* 0x010 */ char pad10[0x60 - 0x10];
    /* 0x060 */ float matLocal[4][4];   /* XFM's local matrix */
    /* 0x0a0 */ qword amatWorld[4];     /* XFM's world matrix (rows; brought up to date by func_00231368) */
    /* 0x0e0 */ int crvk;           /* field: SafeHouse port (CRVK_Linear, else cubic) */
    /* 0x0e4 */ int fClosed;        /* field: SafeHouse port - a closed curve wraps around */
    /* 0x0e8 */ int cpoint;         /* the number of points */
    /* 0x0ec */ float *ag;          /* field: SafeHouse port - the points' parameters */
    /* 0x0f0 */ float *as;          /* field: SafeHouse port - the points' distances (world) */
    /* 0x0f4 */ qword *apos;        /* field: SafeHouse port - the points (the object's frame) */
    /* 0x0f8 */ char padF8[0x100 - 0xf8];
    /* 0x100 */ qword amat[4];      /* field: SafeHouse port (mat) - the world matrix the distances were made for */
    /* 0x140 */ qword *avIn;        /* field: SafeHouse port - the points' incoming tangents (cubic) */
    /* 0x144 */ qword *avOut;       /* field: SafeHouse port - the points' outgoing tangents (cubic) */
    /* 0x148 */ int isegCached;     /* field: SafeHouse port - the segment whose sub-lengths are cached (-1: none) */
    /* 0x14c */ float asSub[CSUB_CRV];  /* field: SafeHouse port - the cached segment's sub-lengths (the last: its length) */
    /* 0x178 */ int iseg;           /* field: SafeHouse port - the last segment found */
    /* 0x17c */ struct ROPE *prope;     /* field: SafeHouse port (rope.cpp) - the rope simulation, made on first use */
    /* 0x180 */ struct PATHREC *ppathrec;   /* field: SafeHouse port (spawner.cpp) - the AI's record of the path */
} CRV;

#endif
