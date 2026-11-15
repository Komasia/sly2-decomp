/* h3_rope.h: the records a path object (crv.h CRV) can carry.
 * ROPE: a path's rope simulation (0x90 bytes at the path's +0x17C, made by PropeEnsure 0x1E7840 the first time a
 * script sets one of the rope options 1042..1056; module 0x1E7840..0x1E9F50). Two ends (objects' points, else the
 * path's own ends), a force (gravity), the points' world positions / velocities / rest distances; its update (the
 * path's vt slot 17, UpdatePath17 0x1E6340) by its mode. Layout: SafeHouse port (rope.cpp ROPE).
 * PATHREC: the AI's record of a path (0x9C bytes at the path's +0x180, 0x1E9C30 / 0x1E9C88): the spans of the path
 * off the AI regions and the regions under it. Layout: SafeHouse port (spawner.cpp PATHREC). */
#ifndef H3_ROPE_H
#define H3_ROPE_H

#include "crv.h"

struct LO;
struct XF;
struct NAVREGION;

/* ROPE::mode (option 1046) */
#define ROPEK_None   (-1)   /* no simulation (the path's update off) */
#define ROPEK_Spring 0      /* StepRopeSpring */
#define ROPEK_Trail  1      /* StepRopeTrail: the points pulled after the first end */
#define ROPEK_TrailPinned 2 /* the trail, its last point pinned to the second end (the path lengthened) */
#define ROPEK_SpringResample 3  /* the spring, the path re-sampled at its rest steps */

typedef struct ROPE {
    /* 0x00 */ float force[4];      /* field: SafeHouse port - option 1045 (default 0, 0, -1750) */
    /* 0x10 */ struct LO *apo[2];   /* field: SafeHouse port - the ends' objects (options 1042 / 1043) */
    /* 0x18 */ int pad18[2];
    /* 0x20 */ qword apos[2];       /* field: SafeHouse port - the ends' points in their records */
    /* 0x40 */ struct XF *apxf[2];  /* field: SafeHouse port - the ends' records (D_002C44F0: the world) */
    /* 0x48 */ CRV *ppath;          /* field: SafeHouse port - the path */
    /* 0x4c */ int mode;            /* field: SafeHouse port - ROPEK_* (option 1046) */
    /* 0x50 */ int pad50;
    /* 0x54 */ qword *apos54;       /* field: SafeHouse port - the points (world) */
    /* 0x58 */ qword *avel58;       /* field: SafeHouse port - their velocities */
    /* 0x5c */ float *as5C;         /* field: SafeHouse port - their rest distances along the rope */
} ROPE;

/* a span of a path, by distance */
typedef struct PATHSPAN {
    /* 0x0 */ float sMin;
    /* 0x4 */ float sMax;
} PATHSPAN;

#define CSPAN_PATHREC 16
#define CREG_PATHREC_MAX 64

typedef struct PATHREC {
    /* 0x00 */ CRV *ppath;          /* the path */
    /* 0x04 */ int cspanLoaded;     /* field: SafeHouse port (aseg) - the spans off the regions, at the load */
    /* 0x08 */ PATHSPAN *aspanLoaded;
    /* 0x0c */ int cspan;           /* field: SafeHouse port (aseg10) - the spans in use (UpdatePathrec adds the polygons') */
    /* 0x10 */ PATHSPAN aspan[CSPAN_PATHREC];
    /* 0x90 */ int cpreg;           /* field: SafeHouse port (apreg) - the regions under the path */
    /* 0x94 */ struct NAVREGION **apreg;
    /* 0x98 */ int nStamp;          /* field: SafeHouse port (n98) - the regions' stamp at the last update (-1: never) */
} PATHREC;

#endif
