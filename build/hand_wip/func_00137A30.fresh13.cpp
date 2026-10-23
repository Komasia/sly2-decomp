// fresh13 (Claude agent laneBE, 2026-10-23): aligned 52 -> 43. fresh12 plus `{ ENT *aentOld = pxNew->aent; pxNew->aent = func_001AE238(AREQ(pxNew->c * 8), aentOld); }` (aent loaded before the AREQ stores) and the tail order x6C, g78, xD4.
// fresh12 (Claude agent laneBE, 2026-10-23): aligned 70 -> 52 (positional 183 -> 55). k loop reads `ENT *aent = pxNew->aent` (local before the loop) only for the COMPARE, pentNew = &pxNew->aent[k] (gives the target lw v0 / daddu a3 / daddu a2 chain before the blez), and a commented empty "memory" asm at the not-found exit so c and aent are reloaded from pxNew like the target. Left: pxCopy/0x10 s7/fp swap, main-loop s5/s6/s7/fp, exit sll/addiu order, realloc and x6C/xD4 store order.
// fresh11 (Claude agent laneB24, 2026-10-23): aligned 70 (positional 205 -> 183). fresh10 plus: (1) pel declared at function scope right after pe (`ELEM *pel;` assigned in the main loop): pel now spills to 0x3C and pxFirst/pxName to 0x40/0x44 like the target; (2) `X *pxFirst; X *pxName;` declared first, then `pxName = 0; pxFirst = 0;` (target stores 0x44 first); (3) `int j;` declared at function scope BEFORE `int i;` (j+1/i+1 spill slots 0x48/0x4C now like the target); (4) not-found `pentNew = &pxNew->aent[pxNew->c]; pxNew->c++;` (c reloaded like the target, but gcse PRE still reuses the preheader aent copy, reg 360, instead of reloading 0x60(s2)). Left: pxCopy fp / 0x10 s7 (target s7 / fp; one alloc-only "r"(pxCopy) ref is not enough, two jump it above &req), main-loop s5/s6/s7/fp permutation, aent reload.
// fresh10 (Claude agent laneB23, 2026-10-23): aligned 71 -> 70. fresh9 with the k loop as a plain `for (; k < pxNew->c; k++) { pentNew = &pxNew->aent[k]; if (... == (*(unsigned *)&pxNew->aent[k] & M)) goto found; }` (no pk: c is now loaded once, into the blez register, like the target) and the not-found slot as `{ int cNew = pxNew->c++; pentNew = &pxNew->aent[cNew]; }` (the c store now kills the aent value, so aent is reloaded from 0x60(s2) like the target; but c is now reused instead of reloaded).
// fresh9 (Claude agent laneB23, 2026-10-23): aligned 82 -> 71. Each f31 branch tests the field directly: `if (!pentNew->pobj) { create...; pentNew->pobj = pobj; } else pobj = pentNew->pobj;` (target bnez v0 + daddu s0,v0 in the slot), and the `*(unsigned *)pentNew |= mF31` belongs INSIDE the f31<0 create block (the target skips it when pobj exists).
// fresh8 (Claude agent laneB22, 2026-10-23): aligned 92 -> 82. k loop as `k = 0; if (k < pxNew->c) { ENT *pk = pxNew->aent; do { pentNew = &pxNew->aent[k]; if (match(pent, pk)) goto found; k++, pk++; } while (k < pxNew->c); }`: pentNew computed every iteration gives the target loop body exactly (sll k,3 + addu s1 in the beq slot), and the if/do-while gives the c-first preheader. Left: c read twice (v0 for blez, copied to t0; target one lw t0) and aent copied twice (t0 -> a2, a3; target v0 -> a3 -> a2), spill slots 0x3C/0x44.
// fresh7 (Claude agent laneB20, 2026-10-23): aligned 101 -> 92. (1) The f31 mask as a local `unsigned mF31 = 0x80000000` set at found: and used for the late `|=`: the target sets lui s5 before the bltz and keeps it across the calls; this also gets pel SPILLED (madd $zero / sw 0x3C-ish) like the target. (2) k loop with a walking pk for the compare (pent first) and pentNew = &pxNew->aent[k] only in the found branch: sll/addu in the loop like the target. Left: slots (pel 0x44 vs 0x3C, i+1/j+1 swapped), s5/s6/s7/fp permutation, the not-found path reuses the pre-loop aent (target reloads 0x60(s2)).
// fresh6 (Claude agent laneB19, 2026-10-23): aligned 106 -> 101. A commented empty asm with an allocation-only "r"(0x10) at the top of the E3 loop body: loop.c merges it with the ctor's 0x10 movable, the hoisted pseudo gets 5 refs and beats c, so c is SPILLED to 0x30 like the target (prologue and E3 loop now match apart from regs). Cause: update_equiv_regs doubles REG_LIVE_LENGTH of a REG_EQUIV-constant pseudo (the loop-hoisted 0x10), so without the asm it loses to c. Left: 0x10 in s7 / pxCopy in fp (target fp / s7); pxFirst/pxName slots 0x3C/0x40 (target 0x44/0x40, target has a pel spill at 0x3C).
// fresh5 (Claude agent laneB18, 2026-10-23): aligned 111 -> 106. pentNew->n = (*(unsigned *)pent << 12) >> 12 gives the target sll/srl n copy (the 0xFFFFF mask is no longer hoisted into s6). Left: c still in fp (target spills c to 0x30).
// fresh4 (Claude agent laneB17, 2026-10-23): aligned 127 -> 111. fresh3 first loop (pe = PELEM(i) per iteration) + fresh2 index-form cTotal loop (PELEM(i)->px). Left: c in fp (target spills c to 0x30; loop.c DOES hoist the E3-loop 0x10 (reg 183) but global alloc gives fp to c, so reload rematerialises it), main loop pel = PELEM(i) via mtlo/madd in the target, c*4 sll inside the i loop (target fp).
// fresh3 (Claude agent laneB16, 2026-10-23): FRESH first half (aligned 139 overall vs fresh2 127, but the first loop is closer:
// 24 vs 36 positional diffs before 0x137B1C). First loop: `pe = PELEM(i)` at the top of each iteration, then pe->px read
// at every use: this alone gives the target's pointer giv (a0 = aelem, px at 4(a0)), the movz for pxFirst/pxName and the
// pe->px reloads in the bnel slots, with no volatile. A PXS struct for pxFirst/pxName also gives the reloads, but puts it
// at sp+0 (target: spill slots 0x40/0x44, so they are spilled pseudos). cTotal loop as a walking pe. Left: c in fp
// (target spills c to 0x30, so every later slot is 4 lower), the E3-loop 0x10 is not hoisted into fp; AREQ ctor order /
// default-arg form: no gain. Second half is fresh2's.
typedef int qword __attribute__((mode(TI)));
struct AREQ { int cb; int cbAlign; AREQ(int c) { cb = c; cbAlign = 0x10; } };
class FRAME { public: FRAME(); ~FRAME(); int a[4]; };
struct OBJ;
struct ENT { unsigned n : 20; unsigned k : 10; unsigned f30 : 1; signed f31 : 1; OBJ *pobj; };
struct E3 { int a; int b; void *pv; };
struct X;
struct OBJ { int x0; X *px; E3 *ae3; OBJ **apobj; qword q10; };
struct XB {
    int x0; int pad4[2];
    virtual void f1(); virtual void f2(); virtual void f3(); virtual void f4(); virtual void f5();
    virtual void f6(); virtual void f7(); virtual void f8(); virtual void Init();
};
struct X : XB {
    char pad[0x5C - 0x10]; int c; ENT *aent; char pad64[0x6C - 0x64]; int x6C; int pad70[2]; float g78;
    char pad7C[0x98 - 0x7C]; int x98, x9C, xA0; void *xA4; int xA8, xAC;
    char padB0[0xC0 - 0xB0]; int cb; int cElem; struct ELEM *aelem; int n; E3 *ae3; int xD4; X *pxD8;
};
struct XV { virtual void f1(); virtual void f2(); virtual void f3(); virtual void f4(); virtual void f5();
            virtual void f6(); virtual void f7(); virtual void f8(); virtual void Init(); };
struct ELEM { float g; X *px; };
extern "C" {
X *func_0013E3C8(int a, void *p, int b, int c);
void *func_001AE1D0(const AREQ &req);
void *func_001AE238(const AREQ &req, void *pv);
void *func_001AE378(const AREQ &req);
void *func_001AE2A0(const AREQ &req);
OBJ *func_0012B3B0(int id);
OBJ *func_0012CB98(int id);
void func_0012FE58(X *px, void *p, ENT *pent, int *pa, void **ppb);
qword func_0022CA18(void *pa, void *pb);
void func_00256EE0(X *px, int n);
void func_001384C0(X *px);
void func_00137A30(void *p, int cb, int c, ELEM *aelem, int n, int *pa, int *pb, X **ppx);
}
#define PELEM(i) ((ELEM *)((char *)aelem + (i) * cb))
struct PXS { X *pxFirst; X *pxName; };
void func_00137A30(void *p, int cb, int c, ELEM *aelem, int n, int *pa, int *pb, X **ppx)
{
    ELEM *pe;
    ELEM *pel;
    X *pxFirst;
    X *pxName;
    X *pxCopy = 0;
    pxName = 0;
    pxFirst = 0;
    int j;
    int i;
    for (i = 0; i < c; i++) {
        pe = PELEM(i);
        if (pe->px) {
            if (!pxFirst) pxFirst = pe->px;
            if (!pxCopy && (pe->px->x98 || pe->px->xA8 || pe->px->xA0)) pxCopy = pe->px;
            if (!pxName) pxName = pe->px->x0 ? pe->px : 0;
        }
    }
    if (!pxFirst) { *ppx = 0; return; }
    {
        FRAME frame;
        X *pxNew = func_0013E3C8(0x6E, p, -1, -1);
        pxNew->Init();
        pxNew->cb = cb;
        pxNew->cElem = c;
        pxNew->aelem = aelem;
        pxNew->n = n;
        pxNew->ae3 = (E3 *)func_001AE1D0(AREQ(n * 12));
        for (int ie = 0; ie < n; ie++) {
            __asm__("" : : "r"(0x10));  /* empty asm, allocation only: extra refs on the hoisted 0x10 pseudo so it outranks c in global alloc (c is spilled to 0x30 like the target) */
            E3 *pe3 = &pxNew->ae3[ie];
            pe3->a = pa[ie];
            int b = pb[ie];
            pe3->b = b;
            pe3->pv = func_001AE1D0(AREQ(b * 8));
        }
        if (pxCopy) {
            pxNew->pxD8 = pxCopy;
            pxNew->x98 = pxCopy->x98;
            pxNew->x9C = pxCopy->x9C;
            pxNew->xA0 = pxCopy->xA0;
            pxNew->xA4 = func_001AE238(AREQ(pxCopy->xA0 << 4), pxCopy->xA4);
            pxNew->xA8 = pxCopy->xA8;
            pxNew->xAC = pxCopy->xAC;
        }
        {
            int cTotal = 0;
            for (i = 0; i < c; i++) {
                if (PELEM(i)->px) cTotal += PELEM(i)->px->c;
            }
            pxNew->aent = (ENT *)func_001AE378(AREQ(cTotal * 8));
            pxNew->c = 0;
        }
        for (i = 0; i < c; i++) {
            pel = PELEM(i);
            if (!pel->px) continue;
            for (j = 0; j < pel->px->c; j++) {
                ENT *pent = &pel->px->aent[j];
                ENT *pentNew;
                OBJ *pobj;
                int k;
                if (pent->f30) continue;
                k = 0;
                ENT *aent = pxNew->aent;
                for (; k < pxNew->c; k++) {
                    pentNew = &pxNew->aent[k];
                    if ((*(unsigned *)pent & 0x3FFFFFFF) == (*(unsigned *)&aent[k] & 0x3FFFFFFF))
                        goto found;
                }
                __asm__ __volatile__("" : : : "memory");  /* empty asm barrier: the target reloads c and aent from pxNew here instead of reusing the loop registers */
                pentNew = &pxNew->aent[pxNew->c];
                pxNew->c++;
                pentNew->n = (*(unsigned *)pent << 12) >> 12;
                pentNew->k = pent->k;
            found:
                unsigned mF31 = 0x80000000;
                if (pent->f31 >= 0) {
            if (!pentNew->pobj) {
            int a; void *pv;
            pobj = func_0012B3B0(5);
            func_0012FE58(pxNew, p, pentNew, &a, &pv);
            pobj->q10 = func_0022CA18(pv, pv);
            pobj->px = pxNew;
            pobj->ae3 = pxNew->ae3;
            pobj->apobj = (OBJ **)func_001AE2A0(AREQ(c * 4));
            pentNew->pobj = pobj;
            } else pobj = pentNew->pobj;
                } else {
            if (!pentNew->pobj) {
            pobj = func_0012CB98(2);
            pobj->px = pxNew;
            pobj->ae3 = pxNew->ae3;
            pobj->apobj = (OBJ **)func_001AE2A0(AREQ(c * 4));
            pentNew->pobj = pobj;
            *(unsigned *)pentNew |= mF31;
            } else pobj = pentNew->pobj;
                }
                pobj->apobj[i] = pent->pobj;
            }
        }
        { ENT *aentOld = pxNew->aent; pxNew->aent = (ENT *)func_001AE238(AREQ(pxNew->c * 8), aentOld); }
        pxNew->x6C = pxFirst->x6C;
        pxNew->g78 = pxFirst->g78;
        pxNew->xD4 = -1;
        if (pxName) func_00256EE0(pxNew, pxName->x0);
        pe = aelem;
        for (i = 0; i < c; i++) {
            pe->g = (pe->px == pxFirst) ? 1.0f : 0.0f;
            pe = (ELEM *)((char *)pe + cb);
        }
        func_001384C0(pxNew);
        *ppx = pxNew;
    }
}
