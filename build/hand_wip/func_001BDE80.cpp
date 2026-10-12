typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
struct CTX { int a[4]; CTX(); ~CTX(); };
struct AREQ { int cb; int align; AREQ(int c, int a) { cb = c; align = a; } };
struct DL { void *pvFirst; void *pvLast; int ibDle; };
struct DLI { DL *pdl; void **ppv; int ibDle; DLI *pdliNext; };
struct X;
struct VT { short d; short pad; void *pfn; };
struct X { int x0, x4, x8; VT *vt; char pad[0xE4 - 0x10]; int xE4; int c; char pad2[0xF4 - 0xEC]; qword *apos;
           char pad3[0x190 - 0xF8]; int x190; char pad4[0x1C0 - 0x194]; int x1C0; DL dl; char pad5[0x1D8 - 0x1D0]; int x1D8; };
extern DLI *D_002DD2FC;
extern qword D_002A2DD0;
extern DL D_003E1A40;
extern "C" {
void *func_001AE318(const AREQ &r);
X *func_001BDA00(void);
void func_001BDBF0(X *p, int n, qword *pts);
void func_001BDE18(X *p, X *pNew);
void func_0011A2E8(DL *pdl, void *pv);
void func_0011A220(DL *pdl, void *pv);
void func_001E6180(X *p);
int func_001BC2F8(X *p);
}
static inline void *Alloc(int cb) { return func_001AE318(AREQ(cb, 0x10)); }
static inline qword MulPt(M4 *m, qword v) { qword r; __asm__("vmulax.xyz $ACC, %1, %2x\n\tvmadday.xyz $ACC, %3, %2y\n\tvmaddaz.xyz $ACC, %4, %2z\n\tvmaddw.xyz %0, %5, $vf0w" : "=j"(r) : "j"(m->r[0]), "j"(v), "j"(m->r[1]), "j"(m->r[2]), "j"(m->r[3])); return r; }
static inline M4 *GetMat(X *p) { return ((M4 *(*)(X *))p->vt[31].pfn)((X *)((char *)p + p->vt[31].d)); }
static inline void InitDli(DLI *pdli, DL *pdl)
{
    pdli->pdl = pdl;
    pdli->ppv = (void **)pdl;
    pdli->ibDle = pdl->ibDle;
    pdli->pdliNext = D_002DD2FC;
    D_002DD2FC = pdli;
}
static inline void *PvNextDli(DLI *pdli)
{
    void *pv = *pdli->ppv;
    pdli->ppv = (void **)((char *)pv + pdli->ibDle);
    return pv;
}

extern "C" void func_001BDE80(int n, X **ap)
{
    int c = 0;
    int i, j, k;
    qword *apos;
    X *pNew;
    for (i = 0; i < n; i++)
        c += ap[i]->c - 1;
    CTX ctx;
    apos = (qword *)Alloc(c << 4);
    k = 0;
    for (i = 0; i < n; i++) {
        X *px = ap[i];
        M4 m = *GetMat(px);
        for (j = 0; j < px->c - 1; j++)
            apos[k++] = MulPt(&m, px->apos[j]);
    }
    pNew = func_001BDA00();
    func_001BDBF0(pNew, c, apos);
    {
        qword sum = D_002A2DD0;
        qword k2;
        union { qword q; float f[4]; } u;
        for (j = pNew->c - 2; j >= 0; j--)
            __asm__("vadd.xyzw %0, %0, %1" : "+j"(sum) : "j"(pNew->apos[j]));
        __asm__("qmtc2.ni %1, %0" : "=j"(k2) : "r"((float)(pNew->c - 1)));
        __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %0, $Q" : "+j"(sum) : "j"(k2));
        u.q = k2;
        ((void (*)(X *, qword))pNew->vt[29].pfn)((X *)((char *)pNew + pNew->vt[29].d), sum);
        for (j = pNew->c - 1; j >= 0; j--)
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(pNew->apos[j]) : "j"(pNew->apos[j]), "j"(sum));
    }
    for (i = 0; i < n; i++) {
        X *px = ap[i];
        if (px->x1C0) {
            DLI dli;
            X *pv;
            InitDli(&dli, &px->dl);
            while ((pv = (X *)PvNextDli(&dli)) != 0) {
                func_0011A2E8(&px->dl, pv);
                pv->x1D8 = 0;
                func_001BDE18(pv, pNew);
            }
            ((void (*)(X *))px->vt[9].pfn)((X *)((char *)px + px->vt[9].d));
            func_0011A220(&D_003E1A40, px);
            D_002DD2FC = dli.pdliNext;
        } else {
            func_001BDE18(px, pNew);
        }
    }
    pNew->xE4 = 1;
    func_001E6180(pNew);
    pNew->x190 = func_001BC2F8(pNew);
}
