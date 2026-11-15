/* CFindObjects: find the objects of an oid as seen from ploCtx: the context's ancestors are numbered (ips) for the
 * match, then every object of the oid in the world's hash and every instance alias of it (skipping objects already
 * found) is matched (MatchSwObject__FP2SWP2LOPviT1T2iPiPP2LOT7). Returns the count, clamped to cMax unless GRFFIND_CountAll. */
#include "h2_find.h"
typedef struct LO LO;
struct LO {
    char pad[0x10];
    LO *paloParent;
    char pad14[4];
    int oid;
    LO *ploNextHash;        /* the next object in the oid's hash bucket */
    char pad20[0xC];
    signed char ips;        /* the find's ancestor depth */
    char pad2D[0xF];
    void *pnsn;             /* its namespace node */
};
typedef struct ALIAS {      /* an instance alias in the world's alias hash */
    int x0;
    void *pnsn;
    int oid;
    struct ALIAS *paliasNext;
    LO *plo;
} ALIAS;
extern void *D_003E139C;    /* the world's namespace node */
extern LO **func_0015E380(void *psw, int oid);
extern ALIAS **func_0015E3C0(void *psw, int oid);
extern void MatchSwObject__FP2SWP2LOPviT1T2iPiPP2LOT7(void *psw, LO *plo, void *pnsn, unsigned int grf, LO *ploCtx, void *pnsnCtx, int cMax, int *pc, LO **aplo, int *pips);
// name: SafeHouse port (CFindObjects)
int CFindObjects__FP2SWi3OIDP2LOPviPP2LO(void *psw, int grf, int oid, LO *ploCtx, void *pnsnCtx, int cMax, LO **aplo)
{
    volatile int unused; /* unreferenced stack slot at 0x10 in the original */
    int cplo;
    int ips;
    LO *plo;
    int fCountAll;
    LO *p;
    ALIAS *palias;
    if (oid == -1 || (!ploCtx && (grf & FINDK_Mask) != FINDK_Any))
        return 0;
    if (!pnsnCtx)
        pnsnCtx = ploCtx ? ploCtx->pnsn : D_003E139C;
    cplo = 0;
    switch (grf & FINDK_Mask) {
    case FINDK_Below:
    case FINDK_Ancestors:
    case FINDK_Nearest: {
        int i = 0;
        p = ploCtx;
        plo = p;
        fCountAll = grf & GRFFIND_CountAll;
        for (; p; p = p->paloParent)
            p->ips = ++i;
        ips = 0x7FFFFFFF;
        break;
    }
    default:
        plo = 0;
        fCountAll = grf & GRFFIND_CountAll;
        break;
    }
    func_0015E380(psw, oid);
    for (p = *func_0015E380(psw, oid); p; p = p->ploNextHash) {
        if (p->oid == oid)
            MatchSwObject__FP2SWP2LOPviT1T2iPiPP2LOT7(psw, p, p->pnsn, grf, ploCtx, pnsnCtx, cMax, &cplo, aplo, &ips);
    }
    func_0015E3C0(psw, oid);
    for (palias = *func_0015E3C0(psw, oid); palias; palias = palias->paliasNext) {
        LO *ploAlias;
        if (palias->oid != oid)
            continue;
        ploAlias = palias->plo;
        if (!ploAlias)
            continue;
        if (ploAlias->oid == oid) {   /* already found through the hash? */
            int i;
            for (i = 0; i < cplo; i++)
                if (aplo[i] == palias->plo)
                    break;
            if (i < cplo)
                continue;
        }
        MatchSwObject__FP2SWP2LOPviT1T2iPiPP2LOT7(psw, palias->plo, palias->pnsn, grf, ploCtx, pnsnCtx, cMax, &cplo, aplo, &ips);
    }
    for (p = plo; p; p = p->paloParent)
        p->ips = 0;
    if (!fCountAll && cMax < cplo)
        cplo = cMax;
    return cplo;
}
