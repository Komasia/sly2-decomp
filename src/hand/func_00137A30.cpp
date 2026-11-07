// NewBlend (Claude agent laneBE2, 2026-10-23): MATCH. Built from build/hand_wip/NewBlend.fresh14.cpp:
// the E3-loop "r"(0x10) asm removed, one allocation-only empty asm on the i*4 giv, one register pin (mF31 in s5),
// and the not-found slot written as `pentNew = &pxNew->aent[pxNew->c++];`.
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
X *PloNew(int a, void *p, int b, int c) asm("PloNew__F3CIDP2SW3OIDi");
void *PvAllocSwImpl(const AREQ &req) asm("PvAllocSwImpl__Fi");
void *PvAllocSwCopyImpl(const AREQ &req, void *pv) asm("PvAllocSwCopyImpl__FiPv");
void *PvAllocStackClearImpl(const AREQ &req) asm("PvAllocStackClearImpl__Fi");
void *PvAllocSwClearImpl(const AREQ &req) asm("PvAllocSwClearImpl__Fi");
OBJ *PtrkpNew(int id) asm("PtrkpNew__Fi");
OBJ *PtrkgNew(int id) asm("PtrkgNew__Fi");
void GetAsegChannelTarget(X *px, void *p, ENT *pent, int *pa, void **ppb) asm("GetAsegChannelTarget__FP4ASEGP3ALOP7ASEGCHNPP3ALOPP2XF");
qword VecXfValue(void *pa, void *pb) asm("VecXfValue__FP2XFP7MATRIX4");
void func_00256EE0(X *px, int n);
void RecalcBlend(X *px) asm("RecalcBlend__FP6ASEGBL");
void NewBlend(void *p, int cb, int c, ELEM *aelem, int n, int *pa, int *pb, X **ppx) asm("NewBlend__FP3ALOiiP4ELEMiPiT5Pv");
}
#define PELEM(i) ((ELEM *)((char *)aelem + (i) * cb))
// name: SafeHouse port (NewBlend)
void NewBlend(void *p, int cb, int c, ELEM *aelem, int n, int *pa, int *pb, X **ppx)
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
        X *pxNew = PloNew(0x6E, p, -1, -1);
        pxNew->Init();
        pxNew->cb = cb;
        pxNew->cElem = c;
        pxNew->aelem = aelem;
        pxNew->n = n;
        pxNew->ae3 = (E3 *)PvAllocSwImpl(AREQ(n * 12));
        for (int ie = 0; ie < n; ie++) {
            E3 *pe3 = &pxNew->ae3[ie];
            pe3->a = pa[ie];
            int b = pb[ie];
            pe3->b = b;
            pe3->pv = PvAllocSwImpl(AREQ(b * 8));
        }
        
        if (pxCopy) {
            pxNew->pxD8 = pxCopy;
            pxNew->x98 = pxCopy->x98;
            pxNew->x9C = pxCopy->x9C;
            pxNew->xA0 = pxCopy->xA0;
            { void *pvOld = pxCopy->xA4; pxNew->xA4 = PvAllocSwCopyImpl(AREQ(pxCopy->xA0 << 4), pvOld); }
            pxNew->xA8 = pxCopy->xA8;
            pxNew->xAC = pxCopy->xAC;
        }
        {
            int cTotal = 0;
            for (i = 0; i < c; i++) {
                if (PELEM(i)->px) cTotal += PELEM(i)->px->c;
            }
            pxNew->aent = (ENT *)PvAllocStackClearImpl(AREQ(cTotal * 8));
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
                pentNew = &pxNew->aent[pxNew->c++];
                pentNew->n = (*(unsigned *)pent << 12) >> 12;
                pentNew->k = pent->k;
            found:
                register unsigned mF31 asm("$21") = 0x80000000;  /* register pin: mF31 in s5 like the target (global alloc otherwise gives s5 to &req) */
                if (pent->f31 >= 0) {
            if (!pentNew->pobj) {
            int a; void *pv;
            pobj = PtrkpNew(5);
            GetAsegChannelTarget(pxNew, p, pentNew, &a, &pv);
            pobj->q10 = VecXfValue(pv, pv);
            pobj->px = pxNew;
            pobj->ae3 = pxNew->ae3;
            pobj->apobj = (OBJ **)PvAllocSwClearImpl(AREQ(c * 4));
            pentNew->pobj = pobj;
            } else pobj = pentNew->pobj;
                } else {
            if (!pentNew->pobj) {
            pobj = PtrkgNew(2);
            pobj->px = pxNew;
            pobj->ae3 = pxNew->ae3;
            pobj->apobj = (OBJ **)PvAllocSwClearImpl(AREQ(c * 4));
            pentNew->pobj = pobj;
            *(unsigned *)pentNew |= mF31;
            } else pobj = pentNew->pobj;
                }
                pobj->apobj[i] = pent->pobj;
                __asm__("" : : "r"(i * 4));  /* empty asm, allocation only: one more ref on the i*4 giv */
            }
        }
        { ENT *aentOld = pxNew->aent; pxNew->aent = (ENT *)PvAllocSwCopyImpl(AREQ(pxNew->c * 8), aentOld); }
        pxNew->x6C = pxFirst->x6C;
        pxNew->g78 = pxFirst->g78;
        pxNew->xD4 = -1;
        if (pxName) func_00256EE0(pxNew, pxName->x0);
        pe = aelem;
        for (i = 0; i < c; i++) {
            pe->g = (pe->px == pxFirst) ? 1.0f : 0.0f;
            pe = (ELEM *)((char *)pe + cb);
        }
        RecalcBlend(pxNew);
        *ppx = pxNew;
    }
}
