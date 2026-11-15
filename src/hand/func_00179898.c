/* JOBHIT3::Enter (0xA3, knocked out): the hit's entry from the guard's third kind array (+0xC10) by the hit's kind,
 * then JOBHIT's enter; the first time only: the tasks' event 0x18 (knocked out by the current player) or 0x17, the
 * guard's coins spilled (its own count +0x3D8 when set, else half, rounded up, of the coins (oid 0x2B3) still in its
 * pocket) at its drop point, the world's object filter recomputed and its detector cleared.
 * func_00179898 (Claude agent lane G2, 2026-10-24). CoinsToDrop() is an inline whose else arm starts with the
 * for-init `n = 0` (keeps the target's bltz/then-first layout). posDrop is read into q before the call. */
#include "h2_aijobs.h"

struct SW;
struct DETECTOR;
extern struct SW g_sw;
extern struct SW g_game;
extern char D_002DE578[];               /* the pickups' drop state */
#define OID_Coin 0x2B3
/* a pocket entry; field: SafeHouse port (POCKET) */
struct POCKETE { int oid; int pad[2]; int c; };
struct GUARD {
    /* 0x000 */ char pad0[0xEC];
    /* 0x0ec */ void *pEC;
    /* 0x0f0 */ char padF0[0x330 - 0xF0];
    /* 0x330 */ int fKnockedOut;        /* field: SafeHouse port (f330) - the one-time knockout notification */
    /* 0x334 */ char pad334[0x3D8 - 0x334];
    /* 0x3d8 */ int cCoinDrop;          /* field: SafeHouse port (n3D8) - the coins it drops (-1: from its pocket) */
    /* 0x3dc */ char pad3DC[4];
    /* 0x3e0 */ qword posDrop;          /* field: SafeHouse port (+0x3E0) - where they drop from (local) */
    /* 0x3f0 */ int n3F0;               /* field: SafeHouse port - the charms' count (default -200) */
    /* 0x3f4 */ char pad3F4[0x404 - 0x3F4];
    /* 0x404 */ struct POCKETE apockete[(0x484 - 0x404) / 16];   /* field: SafeHouse port (the pocket) */
    /* 0x484 */ int cpockete;
    /* 0x488 */ int ipockete;           /* the first one still held */
    /* 0x48c */ char pad48C[0xF64 - 0x48C];
    /* 0xf64 */ struct DETECTOR *pdet;  /* field: SafeHouse port */
};
struct KINDE { int k; int pad[3]; };
int IbitLow__FUi(unsigned int grf);
void Enter__6JOBHIT(JOBHIT *pjob);
struct LO *PloPlayerPo__FP2SW(struct SW *psw);
void BroadcastTaskEvent__FP2SWiP2LO(struct SW *psw, int nEvent, struct GUARD *pguard);
qword ConvertPos__FP2LOT0G9VU_VECTOR(struct GUARD *ploFrom, void *ploTo, qword pos);
void DropPickups__FP6VECTORG9VU_VECTORiiP2LO(void *pdrop, qword pos, int cCoin, int cCharm, struct GUARD *pguard);
void RecalcSwOxfFilterForObject__FP2SWP2SO(struct SW *psw, struct GUARD *pso);
void func_00153FF8(struct DETECTOR *pdet);
static inline int CoinsToDrop(struct GUARD *pguard) {
    int n, i;
    if (pguard->cCoinDrop >= 0) {
        n = pguard->cCoinDrop;
    } else {
        for (i = pguard->ipockete, n = 0; i < pguard->cpockete; i++) {
            struct POCKETE *ppockete = &pguard->apockete[i];
            if (ppockete->oid == OID_Coin) n += ppockete->c;
        }
        n = (n + 1) / 2;
    }
    return n;
}
// SafeHouse port: JOBHIT3::Enter (aihit.cpp "orig: 0x00179868 / 0x00179898 / 0x00179A20")
void func_00179898(JOBHIT *pjob) {
    int cCoin;
    struct GUARD *pguard;
    /* &pguard->aakinde[2][IbitLow(kind)] */
    struct KINDE *pkinde = (struct KINDE *)((char *)pjob->jobmove.aijob.pguard + (IbitLow__FUi(pjob->grfKind) * 16 + 0xC10));
    pjob->jobmove.pkinde = pkinde;
    if (pkinde->k == -1) pjob->jobmove.pkinde = 0;
    Enter__6JOBHIT(pjob);
    pguard = pjob->jobmove.aijob.pguard;
    if (pguard->fKnockedOut == 0) {
        pguard->fKnockedOut = 1;
        if (pjob->psource == PloPlayerPo__FP2SW(&g_sw))
            BroadcastTaskEvent__FP2SWiP2LO(&g_game, 0x18, pjob->jobmove.aijob.pguard);
        else
            BroadcastTaskEvent__FP2SWiP2LO(&g_game, 0x17, pjob->jobmove.aijob.pguard);
        cCoin = CoinsToDrop(pjob->jobmove.aijob.pguard);
        {
            qword posLocal = pjob->jobmove.aijob.pguard->posDrop;
            qword pos;
            /* Empty barrier: the target re-reads pguard for arg0 after loading posLocal instead of reusing the register. */
            __asm__ __volatile__("" ::: "memory");
            pos = ConvertPos__FP2LOT0G9VU_VECTOR(pjob->jobmove.aijob.pguard, 0, posLocal);
            DropPickups__FP6VECTORG9VU_VECTORiiP2LO(D_002DE578, pos, cCoin, pjob->jobmove.aijob.pguard->n3F0, pjob->jobmove.aijob.pguard);
        }
        RecalcSwOxfFilterForObject__FP2SWP2SO(&g_sw, pjob->jobmove.aijob.pguard);
        func_00153FF8(pjob->jobmove.aijob.pguard->pdet);
    }
}

typedef char layout_POCKETE[(sizeof(struct POCKETE)==16)?1:-1];
typedef char layout_GUARD_prefix[(sizeof(struct GUARD)==0xF70)?1:-1];
typedef char layout_GUARD_align[(__alignof__(struct GUARD)==16)?1:-1];
typedef char layout_GUARD_fKnockedOut[((unsigned)&((struct GUARD*)0)->fKnockedOut==0x330)?1:-1];
typedef char layout_GUARD_cCoinDrop[((unsigned)&((struct GUARD*)0)->cCoinDrop==0x3d8)?1:-1];
typedef char layout_GUARD_posDrop[((unsigned)&((struct GUARD*)0)->posDrop==0x3e0)?1:-1];
typedef char layout_GUARD_n3F0[((unsigned)&((struct GUARD*)0)->n3F0==0x3f0)?1:-1];
typedef char layout_GUARD_apockete[((unsigned)&((struct GUARD*)0)->apockete==0x404)?1:-1];
typedef char layout_GUARD_cpockete[((unsigned)&((struct GUARD*)0)->cpockete==0x484)?1:-1];
typedef char layout_GUARD_ipockete[((unsigned)&((struct GUARD*)0)->ipockete==0x488)?1:-1];
typedef char layout_GUARD_pdet[((unsigned)&((struct GUARD*)0)->pdet==0xf64)?1:-1];
typedef char layout_JOBHIT_psource[((unsigned)&((JOBHIT*)0)->psource==0x50)?1:-1];
typedef char layout_JOBHIT_grfKind[((unsigned)&((JOBHIT*)0)->grfKind==0x5c)?1:-1];
