/* CFindObjectsByClass: find the objects of class cid (or derived) as seen from ploCtx: the context's ancestors or
 * children, every object of the class family (the world's per-class lists, cid .. 198 while derived), or - for the
 * other kinds - those lists matched against the context's namespace (func_0015E3E8). Returns the count, clamped to
 * cMax unless GRFFIND_CountAll. */
#include "h2_find.h"
typedef struct LO LO;
struct LO {
    char pad[0x10];
    LO *paloParent;
    char pad14[0xC];
    LO *ploNextClass;       /* the next object in its class's list */
    LO *ploSibling;         /* the next child of its parent */
    int x28;
    signed char ips;        /* the find's ancestor depth */
    char x2D;
    long nsk : 4;
    unsigned long b : 8;
    unsigned int fActive : 1;
    char pad30[0x34];
    LO *ploChildFirst;
    char pad68[8];
    LO *ploChildActiveEnd;  /* where the active children end */
};
typedef struct BUCKET { LO *plo; int a, b; } BUCKET;
extern int FIsBasicDerivedFrom__FP5BASIC3CID(LO *plo, int cid);
extern BUCKET *func_0015E3A8(void *psw, int cid);
extern int func_0015E988(int cidBase, int cid);
extern void func_0015E3E8(void *psw, LO *plo, void *pnsn, unsigned int grf, LO *ploCtx, void *pnsnCtx, int cMax, int *pc, LO **aplo, int *pips);
// name: SafeHouse port (CFindObjectsByClass)
int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(void *psw, int grf, int cid, LO *ploCtx, int cMax, LO **aplo)
{
    volatile int unused;
    int cplo;
    int ips;
    LO *plo;
    int fCountAll;
    LO *p;
    int cidT;
    if (cid == -1 || (!ploCtx && (grf & FINDK_Mask) != FINDK_Any))
        return 0;
    cplo = 0;
    switch (grf & FINDK_Mask) {
    case FINDK_Ancestors:
        fCountAll = grf & GRFFIND_CountAll;
        for (p = ploCtx->paloParent; p; p = p->paloParent) {
            if (!FIsBasicDerivedFrom__FP5BASIC3CID(p, cid))
                continue;
            if ((grf & GRFFIND_Active) && p->fActive == 0)
                continue;
            if (cplo < cMax)
                aplo[cplo] = p;
            cplo++;
        }
        break;
    case FINDK_Children: {
        LO *ploEnd = 0;
        if (grf & GRFFIND_Active)
            ploEnd = ploCtx->ploChildActiveEnd;
        fCountAll = grf & GRFFIND_CountAll;
        for (p = ploCtx->ploChildFirst; p != ploEnd; p = p->ploSibling) {
            if (!FIsBasicDerivedFrom__FP5BASIC3CID(p, cid))
                continue;
            if (cplo < cMax)
                aplo[cplo] = p;
            cplo++;
        }
        break;
    }
    case FINDK_Any: {
        int cidT = cid;
        fCountAll = grf & GRFFIND_CountAll;
        for (; cidT < 199 && func_0015E988(cidT, cid); cidT++) {
            func_0015E3A8(psw, cidT);
            for (p = func_0015E3A8(psw, cidT)->plo; p; p = p->ploNextClass) {
                if ((grf & GRFFIND_Active) && p->fActive == 0)
                    continue;
                if (cplo < cMax)
                    aplo[cplo] = p;
                cplo++;
            }
        }
        break;
    }
    default:
        switch (grf & FINDK_Mask) {
        case FINDK_Below:
        case FINDK_Ancestors:
        case FINDK_Nearest:
        case FINDK_Any: {
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
        for (cidT = cid; cidT < 199 && func_0015E988(cidT, cid); cidT++) {
            func_0015E3A8(psw, cidT);
            for (p = func_0015E3A8(psw, cidT)->plo; p; p = p->ploNextClass)
                func_0015E3E8(psw, p, 0, grf | GRFFIND_AnyNs, ploCtx, 0, cMax, &cplo, aplo, &ips);
        }
        for (p = plo; p; p = p->paloParent)
            p->ips = 0;
        break;
    }
    if (!(grf & GRFFIND_CountAll) && cMax < cplo)
        cplo = cMax;
    return cplo;
}
