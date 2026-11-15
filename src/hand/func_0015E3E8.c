/* func_0015E3E8: CFindObjects' match of one candidate object: unless GRFFIND_AnyNs, its namespace node must be
 * related to the context's namespace chain (by the object's namespace kind: 0 the same group, -1 on the chain, 1 any);
 * then the find kind decides (below the context, a child of it, a deeper ancestor's, the nearest namespace - which
 * restarts the list when a nearer one turns up - or anywhere); matches go into aplo up to cMax, *pc counts them all.
 * The context's ancestors carry their depth (ips: 1 the context) during the find. */
#include "h2_find.h"
typedef struct LO LO;
struct LO {
    char pad[0x10];
    LO *paloParent;
    char pad14[0x14];
    int x28;
    signed char ips;        /* the find's ancestor depth (0: not an ancestor of the context) */
    char x2D;
    long nsk : 4;           /* the namespace kind */
    unsigned long b : 8;
    unsigned int fActive : 1;
};
typedef struct NSN { void *pv; struct NSN *pnsnNext; } NSN;   /* a namespace chain node */
extern int func_001C9950(void *pv);   /* the node's group */
void func_0015E3E8(void *psw, LO *plo, NSN *pnsn, unsigned int grf, void *ploCtx, NSN *pnsnCtx, int cMax, int *pc, LO **aplo, int *pips)
{
    LO *p;
    if (!(grf & GRFFIND_AnyNs)) {
        NSN *q;
        switch (plo->nsk) {
        case 0:
            q = pnsnCtx;
            while (1) {
                if (!q)
                    return;
                if (func_001C9950(q->pv) == func_001C9950(pnsn->pv))
                    break;
                if (grf & GRFFIND_NsFirst)
                    return;
                q = q->pnsnNext;
            }
            break;
        case -1:
            while (pnsnCtx != pnsn) {
                if (!pnsnCtx || (grf & GRFFIND_NsFirst))
                    return;
                pnsnCtx = pnsnCtx->pnsnNext;
            }
            break;
        case 1:
            break;
        }
    }
LMatch:
    switch (grf & FINDK_Mask) {
    case FINDK_Children:
        if (plo->paloParent == ploCtx)
            goto LAdd;
        return;
    case FINDK_Below:
        for (p = plo; p; p = p->paloParent) {
            if (p->ips == 0)
                continue;
            if (p->ips == 1)
                goto LAdd;
            return;
        }
        return;
    case FINDK_Ancestors:
        if (plo->ips >= 2)
            goto LAdd;
        return;
    case FINDK_Nearest: {
        for (p = plo; p; p = p->paloParent) {
            int i = p->ips;
            if (i != 0 && i < *pips) {
                if ((grf & GRFFIND_Active) && plo->fActive == 0)
                    return;
                *pips = i;
                *pc = 0;
                goto LAdd2;
            }
        }
        if (*pips != 0x7FFFFFFF || p)
            return;
        goto LAdd;
    }
    case FINDK_Any:
    LAdd:
        if ((grf & GRFFIND_Active) && plo->fActive == 0)
            return;
    LAdd2:
        if (*pc < cMax)
            aplo[*pc] = plo;
        (*pc)++;
        break;
    }
}
