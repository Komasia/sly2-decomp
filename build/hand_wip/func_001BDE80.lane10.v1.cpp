// Complete WIP: 92/217 instructions differ.
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
struct CTX;
extern "C" CTX*func_001AE478(CTX*);
extern "C" void func_001AE4A0(CTX*,int);
struct CTX { CTX(){(void)func_001AE478(this);}~CTX(){func_001AE4A0(this,2);} };
struct AREQ { int cb; int align; AREQ(int c, int a) { cb = c; align = a; } };
struct DL { void *pvFirst; void *pvLast; int ibDle; };
struct DLI { DL *pdl; void **ppv; int ibDle; DLI *pdliNext; };
struct X;
struct VT { short d; short pad; void *pfn; };
struct X { int x0, x4, x8; VT *vt; char pad[0xE4 - 0x10]; int xE4; int c; char pad2[0xF4 - 0xEC]; qword *apos;
           char pad3[0x190 - 0xF8]; int x190; char pad4[0x1C0 - 0x194]; int x1C0; DL dl; char pad5[0x1D8 - 0x1D0]; X*x1D8; };
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
static inline qword MulPt(M4*m,qword*point){
 qword out;
 __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(out):"j"(m->r[0]),"j"(m->r[1]),"j"(m->r[2]),"j"(m->r[3]),"j"(*point));return out;
}
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

#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef char CTX_Size[sizeof(CTX)==1?1:-1];
typedef char M4_Size[sizeof(M4)==64?1:-1];
typedef char AREQ_Size[sizeof(AREQ)==8?1:-1];
typedef char DL_Size[sizeof(DL)==12?1:-1];
typedef char DLI_Size[sizeof(DLI)==16?1:-1];
typedef char VT_Size[sizeof(VT)==8?1:-1];
typedef char X_vt_Offset[FIELD_OFFSET(X,vt)==12?1:-1];
typedef char X_xE4_Offset[FIELD_OFFSET(X,xE4)==228?1:-1];
typedef char X_c_Offset[FIELD_OFFSET(X,c)==232?1:-1];
typedef char X_apos_Offset[FIELD_OFFSET(X,apos)==244?1:-1];
typedef char X_x190_Offset[FIELD_OFFSET(X,x190)==400?1:-1];
typedef char X_x1C0_Offset[FIELD_OFFSET(X,x1C0)==448?1:-1];
typedef char X_dl_Offset[FIELD_OFFSET(X,dl)==452?1:-1];
typedef char X_x1D8_Offset[FIELD_OFFSET(X,x1D8)==472?1:-1];
typedef char VT_d_Offset[FIELD_OFFSET(VT,d)==0?1:-1];
typedef char VT_pfn_Offset[FIELD_OFFSET(VT,pfn)==4?1:-1];
typedef char AREQ_cb_Offset[FIELD_OFFSET(AREQ,cb)==0?1:-1];
typedef char AREQ_align_Offset[FIELD_OFFSET(AREQ,align)==4?1:-1];
typedef char DL_pvFirst_Offset[FIELD_OFFSET(DL,pvFirst)==0?1:-1];
typedef char DL_pvLast_Offset[FIELD_OFFSET(DL,pvLast)==4?1:-1];
typedef char DL_ibDle_Offset[FIELD_OFFSET(DL,ibDle)==8?1:-1];
typedef char DLI_pdl_Offset[FIELD_OFFSET(DLI,pdl)==0?1:-1];
typedef char DLI_ppv_Offset[FIELD_OFFSET(DLI,ppv)==4?1:-1];
typedef char DLI_ibDle_Offset[FIELD_OFFSET(DLI,ibDle)==8?1:-1];
typedef char DLI_pdliNext_Offset[FIELD_OFFSET(DLI,pdliNext)==12?1:-1];
extern "C" void func_001BDE80(int n, X **ap)
{
    int c = 0;
    int i, j, k;
    qword *apos;
    X *pNew;
    for (int i0 = 0; i0 < n; i0++) c += ap[i0]->c - 1;
    CTX ctx;
    apos = (qword *)Alloc(c << 4);
    int polygon = 0;
    if (n > 0) {
    k = -16;
    do {
        X*px=ap[polygon];
        M4 m=*GetMat(px);
        j = 0;
        if (j < px->c - 1) {
            qword *pw = (qword*)((unsigned)k + (unsigned)apos);
            do { k += 16; *++pw = MulPt(&m,&px->apos[j]); j++; } while (j < px->c - 1);
        }
    } while (++polygon < n);
    }
    pNew = func_001BDA00();
    func_001BDBF0(pNew, c, apos);
    {
        qword sum = D_002A2DD0;
        qword k2;
        union { qword q; float f[4]; } u;
        for(int sumIndex=pNew->c-2;sumIndex>=0;--sumIndex)
            __asm__("vadd.xyzw %0,%0,%1":"+j"(sum):"j"(pNew->apos[sumIndex]));
        __asm__("qmtc2.ni %1, %0" : "=j"(k2) : "r"((float)(pNew->c - 1)));
        __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %0, $Q" : "+j"(sum), "+j"(k2) : "j"(k2));
        void (*pfn)(X *, qword) = (void (*)(X *, qword))pNew->vt[29].pfn;
        pfn((X *)((char *)pNew + pNew->vt[29].d), (u.q = k2, sum));
        int pointIndex = pNew->c;
        while (--pointIndex >= 0) {
            qword point=pNew->apos[pointIndex];
            __asm__("vsub.xyzw %0,%0,%1":"+j"(point):"j"(sum));
            pNew->apos[pointIndex]=point;
        }
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
