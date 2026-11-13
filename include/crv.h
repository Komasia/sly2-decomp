/* CRV: a path curve (Sly 1 CRV / CRVL / CRVC; Sly 2's PATH objects, cid 0x0A, code 0x1E5D80..0x1E7D90): a linear or
 * cubic curve through points with parameters (times) and distances along it. It is part of the path object, so the
 * offsets below are from the object. Layout: SafeHouse port (crv.h CRV); only the fields the C sources use. */
#ifndef CRV_H
#define CRV_H

typedef struct CRV {
    /* 0x000 */ char pad0[0xe0];
    /* 0x0e0 */ int crvk;           /* field: SafeHouse port (0 linear, else cubic) */
    /* 0x0e4 */ int fClosed;        /* field: SafeHouse port */
    /* 0x0e8 */ int cpoint;         /* the number of points */
    /* 0x0ec */ float *ag;          /* field: SafeHouse port - the points' parameters */
    /* 0x0f0 */ float *as;          /* field: SafeHouse port - the points' distances (world) */
    /* 0x0f4 */ char padF4[0x148 - 0xf4];
    /* 0x148 */ int isegCached;     /* field: SafeHouse port - the segment whose sub-lengths are cached (-1: none) */
    /* 0x14c */ char pad14C[0x178 - 0x14c];
    /* 0x178 */ int iseg;           /* field: SafeHouse port - the last segment found */
} CRV;

#endif
