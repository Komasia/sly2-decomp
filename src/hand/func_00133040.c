#include "dl.h"
/* A deferred call queued in the world's list (D_003E0E80 = SW +0x39F0) in time order: the form ppair (one more
 * reference) for plo at time t; a call without an object (the scripts' schedule-callback, SafeHouse gamebif.cpp bif
 * 105) gets a new id from the counter SW +0x3D6C, others -1. Entries come from the slot heap SW +0x39FC. */
struct DEFEV { float t; int plo; int *ppair; int id; DLE dle; };
struct SWC { char pad[0x3d6c]; int cid; };   /* the schedule-callback id counter */
struct SW { char pad[0x39fc]; int slotheapDefev; };
extern struct SWC g_sw;
extern struct DL D_003E0E80;   /* g_sw + 0x39F0: the deferred calls */
struct DEFEV *func_0011CCC0(void *);
void func_0011A0C0(struct DL *, struct DEFEV *, struct DEFEV *);
struct DEFEV *func_00133040(struct SW *psw, int plo, int *ppair, float t) {
    struct DEFEV *pdefev;
    struct DEFEV *pdefevPrev;
    struct DEFEV *pdefevCur;
    (*ppair)++;   /* CPair cref */
    pdefev = func_0011CCC0(&psw->slotheapDefev);
    pdefev->plo = plo;
    if (!plo) pdefev->id = ++g_sw.cid;
    else pdefev->id = -1;
    pdefev->ppair = ppair;
    pdefev->t = t;
    pdefev->dle.next = 0;
    pdefevPrev = 0;
    for (pdefevCur = D_003E0E80.head; pdefevCur; pdefevCur = pdefevCur->dle.next) {
        if (pdefevCur->t > pdefev->t) break;
        pdefevPrev = pdefevCur;
    }
    func_0011A0C0(&D_003E0E80, pdefevPrev, pdefev);
    return pdefev;
}
