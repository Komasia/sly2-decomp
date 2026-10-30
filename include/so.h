/* Sly 2 LO / SO object layout (partial), for C and C++ sources.
 *
 * Offsets come from the matched code and the Sly 2 types in Lilly's ports (src/hand files marked
 * "ported from Lilly's personal Sly 2 decomp"). In Sly 2, SO derives directly from LO (class ids: LO = 2,
 * SO = 48). Fields whose meaning is unknown keep an offset-based name (gUnkXX, unk_0xXX).
 *
 * Virtual calls: every object starts with BASIC (pframe, psidebag, prefnodeFirst) followed by the g++ 2.x
 * vtable pointer at +0x0C. A vtable entry is {this-delta, pfn}; entry 0 is reserved, so virtual slot n is
 * pvt[n + 1]. VT_* below are entry indices (slot + 1) of the slots named so far (see scratchpad r2_renames).
 */
#ifndef SO_H
#define SO_H
#include "common.h"
#include "mat.h"

#ifndef SLY2_QWORD
#define SLY2_QWORD
typedef int qword __attribute__((mode(TI)));
#endif

typedef struct VTE { short d; short pad; void *pfn; } VTE;   /* g++ 2.x vtable entry */

/* vtable entry indices (slot + 1) */
enum {
    VT_HandleMessage = 5,   /* slot 4 */
    VT_Init = 7,            /* slot 6 */
    VT_OnAdd = 11,          /* slot 10 */
    VT_OnRemove = 12,       /* slot 11 */
    VT_LoadFromBrx = 14,    /* slot 13 */
    VT_PostLoad = 15,       /* slot 14 */
    VT_Update = 16,         /* slot 15 */
    VT_ProjectTransform = 17, /* slot 16 */
    VT_RenderSelf = 19,     /* slot 18 */
    VT_Clone = 41,          /* slot 40 */
    VT_UpdateSoBounds = 49  /* slot 48, introduced by SO */
};

typedef struct DLE { void *next; void *prev; } DLE;          /* doubly-linked list entry */
typedef struct DL { void *head; void *tail; int ibDle; } DL;  /* list head; ibDle = offset of the DLE in an item */

struct SO;

/* root of every game object: two reference pointers, the head of its reference list, then the vptr */
typedef struct BASIC {
    /* 0x00 */ void *pframe;         /* CRefPtr<CFrame> */
    /* 0x04 */ void *psidebag;       /* CRefPtr<CSidebag> */
    /* 0x08 */ void *prefnodeFirst;
    /* 0x0c */ VTE *pvt;
} BASIC;

/* transform node: world matrix at +0x40, update stamp at +0xA4 */
typedef struct XF {
    /* 0x00 */ char unk_0x00[0x40];
    /* 0x40 */ struct MATRIX4 matWorld;
    /* 0x80 */ char unk_0x80[0x10];
    /* 0x90 */ int nUnk90;
    /* 0x94 */ int unk_0x94;
    /* 0x98 */ short nKindUnk98;
    /* 0x9a */ short unk_0x9a[3];
    /* 0xa0 */ int nUnkA0;
    /* 0xa4 */ int nStamp;
    /* 0xa8 */ int unk_0xa8[2];
    /* 0xb0 */ qword qwPosUnkB0;
    /* 0xc0 */ char unk_0xc0[0x30];
    /* 0xf0 */ int anUnkF0[3];
} XF;

/* SO::psobounds: shared bounds record, owned by the SO in its first field */
typedef struct SOBOUNDS {
    /* 0x00 */ struct SO *pso;
    /* 0x04 */ int unk_0x04[7];
    /* 0x20 */ float gUnk20;        /* copy of the owner's SO::gUnk13c */
} SOBOUNDS;

typedef struct LO {
    /* 0x00 */ void *pframe;
    /* 0x04 */ void *psidebag;
    /* 0x08 */ void *prefnodeFirst;
    /* 0x0c */ VTE *pvt;
    /* 0x10 */ struct SO *psoParent;
    /* 0x14 */ void *ploroot;
    /* 0x18 */ int oid;
    /* 0x1c */ void *sleOid;
    /* 0x20 */ void *sleCid;
    /* 0x24 */ DLE dleChild;
    /* 0x2c */ char cpaloFindSwObjects;
    /* 0x2d */ uchar grfvis;
    /* 0x2e */ long nUnk48 : 4;    /* bits 48.. of the qword at 0x28 */
               long busyk : 4;
               ulong fRemoved : 1;  /* bit 56 */
               ulong fUnk57 : 1;
               ulong fUnk58 : 1;
               ulong fUnk59 : 1;
               ulong fInWorld : 1;  /* bit 60 */
    /* 0x30 */ float gUnk30;
    /* 0x34 */ void *plorunFirst;
    /* 0x38 */ float sBusy;
    /* 0x3c */ void *ppxr;
    /* 0x40 */ int grfUnk40;
    /* 0x44 */ int unk_0x44[3];
} LO;

typedef struct GEOM {
    int cpos;
    struct VECTOR *apos;
    int csurf;
    void *asurf;
    int cedge;
    void *aedge;
} GEOM;

/* one collision part of an SO (SO::apart[i]) */
typedef struct SOPART {
    /* 0x00 */ XF *pxf;
    /* 0x04 */ struct SO *pso;
    /* 0x08 */ float gUnk08;        /* sphere radius (fUnk49 parts) */
    /* 0x0c */ int oid;
    /* 0x10 */ void *plvo;
    /* 0x14 */ short dhp;
    /* 0x16 */ ulong fUnk48 : 1;
               ulong fUnk49 : 1;    /* the part is a sphere around its XF's position */
               ulong fHidden : 1;
               ulong fUnk51 : 1;
               ulong unk_0x16 : 12;
    /* 0x18 */ uint grfzpk;
    /* 0x1c */ int nUnk1c;
    /* 0x20 */ struct MATRIX4 matWorld;
    /* 0x60 */ DLE dle;
    /* 0x68 */ char bspc[0x10];
    /* 0x78 */ GEOM geomLocal;
    /* 0x90 */ GEOM geomWorld;
    /* 0xa8 */ int nStampGeom;      /* XF::nStamp when geomWorld was last rebuilt */
    /* 0xac */ int nStampWorld;
} SOPART;

/* bounds / contact tree record of an SO (SO::ptree) */
typedef struct SOTREE {
    /* 0x00 */ qword qwMin;
    /* 0x10 */ qword qwMax;
    /* 0x20 */ qword qwCenter;
    /* 0x30 */ float sRadius;
    /* 0x34 */ DL dlpart;
    /* 0x40 */ DLE dleAwake;
    /* 0x48 */ DLE dleAll;
    /* 0x50 */ DLE dleQueue1;
    /* 0x58 */ DLE dleQueue2;
    /* 0x60 */ struct SO *psoRoot;
    /* 0x64 */ void *pxplistFirst;
    /* 0x68 */ void *pxpFirst;
    /* 0x6c */ void *pxpZap;
    /* 0x70 */ ulong grf;          /* SOTREE_f* flags */
} SOTREE;
#define SOTREE_fQueued1  1UL    /* on queue D_003E11B8 */
#define SOTREE_fQueued2  2UL    /* on queue D_003E11C4 */
#define SOTREE_fNoUpdate 4UL
#define SOTREE_fTouched  8UL
#define SOTREE_fDone     16UL

/* physics state (SO::psophys) */
typedef struct SOPHYS {
    /* 0x00 */ struct MATRIX3 momintLocal;
    /* 0x30 */ struct MATRIX3 momintInvLocal;
    /* 0x60 */ qword qwVelocity;
    /* 0x70 */ qword qwAngVelocity;
    /* 0x80 */ float dvGravity[3];     /* x, y, z (unaligned VECTOR) */
    /* 0x8c */ int unk_0x8c;
    /* 0x90 */ qword vecNormalTorque;   /* constrTorque */
    /* 0xa0 */ int nKindTorque;        /* constraint kind (CT); 3 = locked */
    /* 0xa4 */ int unk_0xa4[3];
    /* 0xb0 */ qword vecNormalForce;    /* constrForce */
    /* 0xc0 */ int nKindForce;         /* constraint kind (CT); 3 = locked */
    /* 0xc4 */ int unk_0xc4[3];
    /* 0xd0 */ float m;                 /* mass */
    /* 0xd4 */ int unk_0xd4[2];
    /* 0xdc */ void *pregent;
} SOPHYS;

typedef struct SO {
    /* 0x000 */ LO lo;
    /* 0x050 */ int cxf;
    /* 0x054 */ XF *axf;
    /* 0x058 */ XF *pxfUnk58;
    /* 0x05c */ XF *pxfUnk5c;
    /* 0x060 */ XF *pxfRoot;
    /* 0x064 */ DL dlChild;
    /* 0x070 */ LO *ploRemovedFirst;
    /* 0x074 */ int unk_0x74[3];
    /* 0x080 */ char globset[0x60];   /* GLOBSET */
    /* 0x0e0 */ int cpart;
    /* 0x0e4 */ SOPART *apart;
    /* 0x0e8 */ SOPHYS *psophys;
    /* 0x0ec */ SOTREE *ptree;
    /* 0x0f0 */ qword qwDvContact;
    /* 0x100 */ qword qwDwContact;
    /* 0x110 */ uchar agrfZpk[26];
    /* 0x12a */ uchar unk_0x12a[2];
    /* 0x12c */ float uAlpha;
    /* 0x130 */ float duAlpha;
    /* 0x134 */ SOBOUNDS *psobounds;
    /* 0x138 */ void *pxa;
    /* 0x13c */ float gUnk13c;
    /* 0x140 */ int nStampUnk140;
    /* 0x144 */ int unk_0x144;
    /* 0x148 */ char bUnk148;
    /* 0x149 */ char bUnk149;
    /* 0x14a */ ulong unk_0x14a : 4;
                long nUnk14a : 4;
                ulong nZapMode : 2;
                ulong fIgnoreFixed : 1;
                ulong unk_0x14c : 2;
                ulong fNoJtPlace : 1;
                ulong unk_0x14d : 3;
                ulong fHurtRespawns : 1;
                ulong fTreeRoot : 1;
                ulong fUnk35 : 1;
                ulong fHasIkLimbs : 1;
} SO;

#endif
