/* XP: a contact between two geometry entries (0xC0 bytes from the world's slot heap SW +0x3D40, module 0x1A7C18..
 * 0x1AA*: PxpAddSw, RecalcSwXpPos, RecalcSwXpMovement, FreeSwXpList and the BSP clippers). Each end is an XPD.
 * Layout: SafeHouse port (so.h XPD / XP); only the h5 range's contact files use this header (include/step.h keeps
 * its own partial XP). */
#ifndef H5_XP_H
#define H5_XP_H

typedef int qword __attribute__((mode(TI)));

struct SOE;
struct XF;
struct ALO;

/* the contact kinds (XP::xpk), SafeHouse so.h */
#define XPK_POINT_SURFACE 1
#define XPK_EDGE_SURFACE  2
#define XPK_EDGE_EDGE     3
#define XPK_SPHERE4       4
#define XPK_SPHERE5       5
#define XPK_SPHERE6       6
#define XPK_SWEPT8        8
#define XPK_SWEPT9        9

struct XPD {
    /* 0x00 */ struct SOE *psoe;      /* the geometry entry */
    /* 0x04 */ struct XF *pxf;        /* its object's transform */
    /* 0x08 */ struct ALO *paloRoot;  /* the attachment's root (the material) */
    /* 0x0c */ struct ALO *palo;      /* the entry's owner (notified) */
    /* 0x10 */ qword pos;             /* in the world */
    /* 0x20 */ qword posLocal;        /* in the object's frame */
    /* 0x30 */ qword vel;             /* the point's velocity */
};

struct XP {
    /* 0x00 */ struct XPD axpd[2];
    /* 0x80 */ qword normal;
    /* 0x90 */ float gDist;           /* the separation along the normal */
    /* 0x94 */ float mu;              /* friction */
    /* 0x98 */ float elas;            /* elasticity */
    /* 0x9c */ int xpk;               /* the kind (XPK_*) */
    /* 0xa0 */ int nTag0;             /* the kind's tags (a position, an edge, a surface) */
    /* 0xa4 */ int nTag1;
    /* 0xa8 */ int ipxp;
    /* 0xac */ struct XP *pxpNext;
    /* 0xb0 */ qword dv;              /* the ends' relative velocity (end 0 - end 1) */
};

#define H5_XP_OFFSET(t, m) ((unsigned int)&(((t *)0)->m))
typedef char H5_XP_normal[H5_XP_OFFSET(struct XP, normal) == 0x80 ? 1 : -1];
typedef char H5_XP_xpk[H5_XP_OFFSET(struct XP, xpk) == 0x9C ? 1 : -1];
typedef char H5_XP_pxpNext[H5_XP_OFFSET(struct XP, pxpNext) == 0xAC ? 1 : -1];
typedef char H5_XP_size[sizeof(struct XP) == 0xC0 ? 1 : -1];
typedef char H5_XPD_size[sizeof(struct XPD) == 0x40 ? 1 : -1];

#endif
