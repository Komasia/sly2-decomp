typedef int qword __attribute__((mode(TI)));
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
int FFloatsNear(float a, float b, float eps) asm("FFloatsNear__Ffff");
extern qword D_002A2DD0;
static __inline__ int FVecsNear(qword a, qword b)
{
    return FFloatsNear(GetX(a), GetX(b), 1e-4f) && FFloatsNear(GetY(a), GetY(b), 1e-4f) &&
           FFloatsNear(GetZ(a), GetZ(b), 1e-4f);
}
typedef struct KEYA2 { float g; float dg; } KEYA2;
typedef struct TRKPA { int pvtbl; int ckey; float *at; KEYA2 *aakey[3]; int pad18[2]; float v[4]; } TRKPA;
typedef union VQ { float af[4]; qword q; } VQ;
typedef struct XF {
    char pad[0x80];
    float g0;
    float g1;
    float *pg;
    float *pdgScale;
    char pad90[0x9A - 0x90];
    short state;
    char pad9C[0xC0 - 0x9C];
    VQ pos0;
    VQ vel0;
    VQ pos1;
    VQ vel1;
} XF;
int func_0012C708(TRKPA *ptrk, float g);
void func_0012C768(TRKPA *ptrk, XF *pxf)
{
    int ikey;
    unsigned int iaxis;
    int fStill;
    if (ptrk->ckey) {
        ikey = func_0012C708(ptrk, *pxf->pg);
        pxf->g0 = ptrk->at[ikey - 1];
        pxf->g1 = ptrk->at[ikey];
    } else {
        pxf->pg = &pxf->g0;
        pxf->g1 = 1.0f;
        pxf->pdgScale = &pxf->g1;
        pxf->g0 = 0;
    }
    for (iaxis = 0; iaxis < 3; iaxis++) {
        KEYA2 *akey = ptrk->aakey[iaxis];
        if (akey) {
            KEYA2 *pkey0 = &akey[ikey - 1];
            KEYA2 *pkey1 = &akey[ikey];
            pxf->pos0.af[iaxis] = pkey0->g;
            pxf->vel0.af[iaxis] = pkey0->dg;
            pxf->pos1.af[iaxis] = pkey1->g;
            pxf->vel1.af[iaxis] = pkey1->dg;
        } else {
            pxf->pos0.af[iaxis] = ptrk->v[iaxis];
            pxf->vel0.af[iaxis] = 0;
            pxf->pos1.af[iaxis] = ptrk->v[iaxis];
            pxf->vel1.af[iaxis] = 0;
        }
    }
    fStill = FVecsNear(pxf->pos0.q, pxf->pos1.q) && FVecsNear(D_002A2DD0, pxf->vel0.q) &&
        FVecsNear(D_002A2DD0, pxf->vel1.q);
    pxf->state = fStill ? 2 : 1;
}
