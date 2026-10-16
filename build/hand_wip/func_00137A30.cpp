typedef int qword __attribute__((mode(TI)));
struct AREQ { int cb; int cbAlign; };
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
void *func_001AE1D0(AREQ *preq);
void *func_001AE238(AREQ *preq, void *pv);
void *func_001AE378(AREQ *preq);
void *func_001AE2A0(AREQ *preq);
OBJ *func_0012B3B0(int id);
OBJ *func_0012CB98(int id);
void func_0012FE58(X *px, void *p, ENT *pent, int *pa, void **ppb);
qword func_0022CA18(void *pa, void *pb);
void func_00256EE0(X *px, int n);
void func_001384C0(X *px);
void func_00137A30(void *p, int cb, int c, ELEM *aelem, int n, int *pa, int *pb, X **ppx);
}
#define PELEM(i) ((ELEM *)((char *)aelem + (i) * cb))
void func_00137A30(void *p, int cb, int c, ELEM *aelem, int n, int *pa, int *pb, X **ppx)
{
    X *pxFirst = 0;
    X *pxName = 0;
    X *pxCopy = 0;
    int i;
    ELEM *pe = aelem;
    for (i = 0; i < c; i++) {
        X *px = pe->px;
        if (px) {
            if (!pxFirst) pxFirst = px;
            if (!pxCopy && (px->x98 || px->xA8 || px->xA0)) pxCopy = pe->px;
            if (!pxName) pxName = pe->px->x0 ? pe->px : 0;
        }
        pe = (ELEM *)((char *)pe + cb);
    }
    if (!pxFirst) { *ppx = 0; return; }
    {
        FRAME frame;
        AREQ req;
        X *pxNew = func_0013E3C8(0x6E, p, -1, -1);
        pxNew->Init();
        pxNew->cb = cb;
        pxNew->cElem = c;
        pxNew->aelem = aelem;
        pxNew->n = n;
        req.cb = n * 12; req.cbAlign = 0x10;
        pxNew->ae3 = (E3 *)func_001AE1D0(&req);
        for (i = 0; i < n; i++) {
            E3 *pe3 = &pxNew->ae3[i];
            pe3->a = pa[i];
            pe3->b = pb[i];
            req.cb = pb[i] * 8; req.cbAlign = 0x10;
            pe3->pv = func_001AE1D0(&req);
        }
        if (pxCopy) {
            pxNew->pxD8 = pxCopy;
            pxNew->x98 = pxCopy->x98;
            pxNew->x9C = pxCopy->x9C;
            pxNew->xA0 = pxCopy->xA0;
            req.cb = pxCopy->xA0 << 4; req.cbAlign = 0x10;
            pxNew->xA4 = func_001AE238(&req, pxCopy->xA4);
            pxNew->xA8 = pxCopy->xA8;
            pxNew->xAC = pxCopy->xAC;
        }
        {
            int cTotal = 0;
            for (i = 0; i < c; i++) {
                if (PELEM(i)->px) cTotal += PELEM(i)->px->c;
            }
            req.cb = cTotal * 8; req.cbAlign = 0x10;
            pxNew->aent = (ENT *)func_001AE378(&req);
            pxNew->c = 0;
        }
        for (i = 0; i < c; i++) {
            ELEM *pel = PELEM(i);
            int j;
            if (!pel->px) continue;
            for (j = 0; j < pel->px->c; j++) {
                ENT *pent = &pel->px->aent[j];
                ENT *pentNew;
                OBJ *pobj;
                int k;
                if (pent->f30) continue;
                for (k = 0; k < pxNew->c; k++) {
                    if ((*(unsigned *)&pxNew->aent[k] & 0x3FFFFFFF) == (*(unsigned *)pent & 0x3FFFFFFF)) {
                        pentNew = &pxNew->aent[k];
                        goto found;
                    }
                }
                pentNew = &pxNew->aent[pxNew->c++];
                pentNew->n = pent->n;
                pentNew->k = pent->k;
            found:
                if (pent->f31 >= 0) {
                    pobj = pentNew->pobj;
                    if (!pobj) {
                        int a; void *pv;
                        pobj = func_0012B3B0(5);
                        func_0012FE58(pxNew, p, pentNew, &a, &pv);
                        pobj->q10 = func_0022CA18(pv, pv);
                        pobj->px = pxNew;
                        pobj->ae3 = pxNew->ae3;
                        req.cb = c * 4; req.cbAlign = 0x10;
                        pobj->apobj = (OBJ **)func_001AE2A0(&req);
                        pentNew->pobj = pobj;
                    }
                } else {
                    pobj = pentNew->pobj;
                    if (!pobj) {
                        pobj = func_0012CB98(2);
                        pobj->px = pxNew;
                        pobj->ae3 = pxNew->ae3;
                        req.cb = c * 4; req.cbAlign = 0x10;
                        pobj->apobj = (OBJ **)func_001AE2A0(&req);
                        pentNew->pobj = pobj;
                    }
                }
                pentNew->f31 = 1;
                pobj->apobj[i] = pent->pobj;
            }
        }
        req.cb = pxNew->c * 8; req.cbAlign = 0x10;
        pxNew->aent = (ENT *)func_001AE238(&req, pxNew->aent);
        pxNew->x6C = pxFirst->x6C;
        pxNew->xD4 = -1;
        pxNew->g78 = pxFirst->g78;
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
