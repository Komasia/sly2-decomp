#include "dl.h"
typedef int qword __attribute__((mode(TI)));
typedef struct DLI { DL *m_pdl; void **m_ppv; int m_ibDle; struct DLI *m_pdliNext; } DLI;
extern DLI *s_pdliFirst;
/* UpdateSwActivation: the world update's activation pass over the queue of roots to check (SW +0x20), up to the stop
 * point (+0x39A4; reset when the camera or the player moved more than S_STOP, or the camera's flags changed).
 * Each root's activation kind (LO +0x28 bits 52..55): 1 always and 2 never in (both leave the queue); 0 in within its
 * radius (+0x38) of the camera, 3 of the player, while its mask (+0x2D) meets the camera's flags; a root of kind 0 /
 * 3 whose distance to the radius is more than S_STOP beyond how far the viewpoint moved goes to the queue's end.
 * A root coming in is put in the active list (SW +0x2C) and registered (vt slot 23), one going out unregistered
 * (vt slot 22) and taken out. Layout: SafeHouse port (activate.h / activate.cpp, sw.h). */
struct LO;
struct LOVT { char pad[0xB0]; short d22; short p22; void (*pfnUnregister)(struct LO *); short d23; short p23; void (*pfnRegister)(struct LO *); };
struct LO {
    /* 0x00 */ char pad[0xC];
    /* 0x0c */ struct LOVT *pvt;
    /* 0x10 */ char pad2[0x28 - 0x10];
    /* 0x28 */ long grf;        /* bits 52..55: the activation kind (SafeHouse st); byte 0x2D: the mask */
    /* 0x30 */ float g30;
    /* 0x34 */ float g34;
    /* 0x38 */ float sRadius;   /* field: SafeHouse port */
};
struct LONODE { struct LO *ploRoot; };   /* a root's node (LO +0x14): the queue's entries */
/* the camera (g_cm): its flags and position, the activation's viewpoint */
struct CM { char pad[0x14]; int grfCm; char pad2[0x90 - 0x18]; qword posCm; };
struct SW {
    /* 0x0000 */ char pad[0x20];
    /* 0x0020 */ DL dlQueued;                     /* the queued roots (SafeHouse lsplo20) */
    /* 0x002c */ char dlActive[0x39A4 - 0x2C];    /* the active nodes (a DL) */
    /* 0x39a4 */ void *pnodeStop;                 /* field: SafeHouse port (ploStop) - the pass's stop */
    /* 0x39a8 */ int grfCmLast;                   /* field: SafeHouse port */
    /* 0x39b0 */ qword posCmLast;                 /* field: SafeHouse port */
    /* 0x39c0 */ qword posPoLast;                 /* field: SafeHouse port */
};
#define LOST_Radius       0   /* within the radius of the camera */
#define LOST_Always       1
#define LOST_Never        2
#define LOST_RadiusPlayer 3   /* within the radius of the player */
extern struct CM g_cm;
extern float D_002BD450;   /* S_STOP: a move that resets the pass's stop */
void *PloPlayerPo__FP2SW(void);
qword PosOfLo__FP2LO(void *p);
void func_00147EC8(struct SW *psw, void *pnode);   /* the node taken off the queue */
void func_00147EE8(struct SW *psw, void *pnode);   /* the node moved to the queue's end */
int FFindDlEntry__FP2DLPv(void *p, void *pv);
void AppendDlEntry__FP2DLPv(void *p, void *pv);
void RemoveDlEntry__FP2DLPv(void *p, void *pv);

static __inline__ float GDist(qword a, qword b)
{
    qword d, t;
    float g;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n"
        "vaddw.x %1, $vf0, $vf0w\n"
        "vadday.x ACC, %0, %0y\n"
        "vmaddz.x %0, %1, %0z" : "+j"(d), "=j"(t));
    __asm__("vsqrt Q, %0x\n"
        "vwaitq\n"
        "vaddq.x %0, $vf0, Q" : "+j"(d));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(d));
    return g;
}
static inline void InitDli(DLI *pdli, DL *pdl)
{
    pdli->m_pdl = pdl;
    pdli->m_ppv = (void **)pdl;
    pdli->m_ibDle = pdl->ibDle;
    pdli->m_pdliNext = s_pdliFirst;
    s_pdliFirst = pdli;
}
static inline void *PvNextDli(DLI *pdli)
{
    void *pv = *pdli->m_ppv;
    pdli->m_ppv = (void **)((char *)pv + pdli->m_ibDle);
    return pv;
}

// name: SafeHouse port (UpdateSwActivation 0x147F40)
void UpdateSwActivation(struct SW *psw) asm("UpdateSwActivation__FP2SW");
void UpdateSwActivation(struct SW *psw)
{
    DLI dli;
    qword posCm, posPo;
    float sCm, sPo;     /* how far the camera / the player moved since the stop was reset */
    int grfCm;
    void *ppo;
    void *pnode;
    posCm = g_cm.posCm;
    grfCm = g_cm.grfCm;
    ppo = PloPlayerPo__FP2SW();
    if (ppo)
        posPo = PosOfLo__FP2LO(ppo);
    else
        posPo = posCm;
    sCm = GDist(posCm, psw->posCmLast);
    sPo = GDist(posPo, psw->posPoLast);
    if (D_002BD450 < sCm || D_002BD450 < sPo || grfCm != psw->grfCmLast) {
        psw->pnodeStop = 0;
        psw->grfCmLast = grfCm;
        psw->posCmLast = posCm;
        psw->posPoLast = posPo;
    }
    InitDli(&dli, &psw->dlQueued);
    while ((pnode = PvNextDli(&dli)) != psw->pnodeStop) {
        struct LO *plo = ((struct LONODE *)pnode)->ploRoot;
        int fIn;
        switch ((int)((plo->grf << 8) >> 60)) {
        case LOST_Never:
            fIn = 0;
            func_00147EC8(psw, pnode);
            break;
        case LOST_Always:
            fIn = 1;
            func_00147EC8(psw, pnode);
            break;
        case LOST_Radius:
            if (!(grfCm & ((unsigned char *)plo)[0x2D])) {
                fIn = 0;
                goto leave;
            } else {
                float d;   /* the distance past the radius */
                d = GDist(PosOfLo__FP2LO(plo), posCm) - plo->sRadius;
                fIn = d < 0.0f;
                if (D_002BD450 < __builtin_fabsf(d) - sCm) {
                leave:
                    func_00147EE8(psw, pnode);
                }
            }
            break;
        case LOST_RadiusPlayer:
            if (!(grfCm & ((unsigned char *)plo)[0x2D])) {
                fIn = 0;
            } else {
                float d;   /* the distance past the radius */
                d = GDist(PosOfLo__FP2LO(plo), posPo) - plo->sRadius;
                fIn = d < 0.0f;
                if (D_002BD450 < __builtin_fabsf(d) - sPo)
                    func_00147EE8(psw, pnode);
            }
            break;
        }
        if (fIn != FFindDlEntry__FP2DLPv(psw->dlActive, pnode)) {
            if (fIn) {
                AppendDlEntry__FP2DLPv(psw->dlActive, pnode);
                plo->pvt->pfnRegister((struct LO *)((char *)plo + plo->pvt->d23));
            } else {
                plo->pvt->pfnUnregister((struct LO *)((char *)plo + plo->pvt->d22));
                RemoveDlEntry__FP2DLPv(psw->dlActive, pnode);
            }
        }
    }
    s_pdliFirst = dli.m_pdliNext;
}
