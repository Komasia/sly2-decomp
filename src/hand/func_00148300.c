/* CheckLoRoot: a root's activation checked at once (AddLo), as the world update's pass does: by its activation kind
 * (+0x28 bits 52..55: 1 always, 2 never, 0 / 3 within its radius of the camera / the player while its mask meets the
 * camera's flags); a root coming in is put in the world's active list (SW +0x2C) and registered (vt slot 23), one
 * going out unregistered (vt slot 22) and taken out. Nothing is done while D_003E0E70 is set.
 * Layout: SafeHouse port (activate.h). */
/* Match notes (Claude agent): case 2 before case 0, and a block-local r per case (so the sRadius load ties to f20). */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct LO {
    /* 0x00 */ char pad[0xC];
    /* 0x0c */ VTENT *vt;
    /* 0x10 */ char pad1[0x14 - 0x10];
    /* 0x14 */ int pnode;       /* the root's node: the active list's entry */
    /* 0x18 */ char pad2[0x28 - 0x18];
    /* 0x28 */ long grf;        /* bits 52..55: the activation kind (SafeHouse st); byte 0x2D: the mask */
    /* 0x30 */ char pad3[8];
    /* 0x38 */ float sRadius;   /* field: SafeHouse port */
};
/* the camera (g_cm): its flags and position, the activation's viewpoint */
struct CM { char pad[0x14]; int grfCm; char pad2[0x90 - 0x18]; qword posCm; };
struct SW { char pad[0x2C]; char dlActive[4]; };   /* +0x2C the active nodes (a DL) */
#define LOST_Radius       0
#define LOST_Always       1
#define LOST_Never        2
#define LOST_RadiusPlayer 3
#define VTS_UnregisterLoTree 22
#define VTS_RegisterLoTree   23
extern int D_003E0E70;     /* set: no activation checks */
extern struct CM g_cm;
void *PloPlayerPo__FP2SW(void);
qword PosOfLo__FP2LO(void *p);
int FFindDlEntry__FP2DLPv(void *pdl, int pnode);
void AppendDlEntry__FP2DLPv(void *pdl, int pnode);
void RemoveDlEntry__FP2DLPv(void *pdl, int pnode);
static __inline__ float GDistSq(qword a, qword b)
{
    qword d, t;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n"
        "vaddw.x %1, $vf0, $vf0w\n"
        "vadday.x ACC, %0, %0y\n"
        "vmaddz.x %0, %1, %0z" : "+j"(d), "=j"(t));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
// name: SafeHouse port (CheckLoRoot)
void CheckLoRoot__FP2SWP2LO(struct SW *psw, struct LO *plo)
{
    int grfCm;
    qword posCm, posPo;
    void *ppo;
    int fIn, pnode;
    if (D_003E0E70) return;
    posCm = g_cm.posCm;
    grfCm = g_cm.grfCm;
    ppo = PloPlayerPo__FP2SW();
    if (ppo) posPo = PosOfLo__FP2LO(ppo);
    else posPo = posCm;
    pnode = plo->pnode;
    switch ((int)((plo->grf << 8) >> 60)) {
    case LOST_Always:
        fIn = 1;
        break;
    case LOST_Never:
        fIn = 0;
        break;
    case LOST_Radius:
        if (grfCm & ((unsigned char *)plo)[0x2D]) {
            float r;   /* the radius squared */
            fIn = 1;
            r = plo->sRadius * plo->sRadius;
            fIn = GDistSq(PosOfLo__FP2LO(plo), posCm) < r;
        } else {
            fIn = 0;
        }
        break;
    case LOST_RadiusPlayer:
        if (grfCm & ((unsigned char *)plo)[0x2D]) {
            float r;   /* the radius squared */
            fIn = 1;
            r = plo->sRadius * plo->sRadius;
            fIn = GDistSq(PosOfLo__FP2LO(plo), posPo) < r;
        } else {
            fIn = 0;
        }
        break;
    }
    if (fIn == FFindDlEntry__FP2DLPv(psw->dlActive, pnode)) return;
    if (fIn) {
        AppendDlEntry__FP2DLPv(psw->dlActive, pnode);
        ((void (*)(void *))plo->vt[VTS_RegisterLoTree].pfn)(VT_THIS(plo, &plo->vt[VTS_RegisterLoTree]));
    } else {
        ((void (*)(void *))plo->vt[VTS_UnregisterLoTree].pfn)(VT_THIS(plo, &plo->vt[VTS_UnregisterLoTree]));
        RemoveDlEntry__FP2DLPv(psw->dlActive, pnode);
    }
}
