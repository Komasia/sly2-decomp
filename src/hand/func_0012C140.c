/* TRKPA::Setup (keys {g, dgIn, dgOut}): the record's segment around its parameter, built axis by axis (axes
 * without keys stay at v with zero slope); a track with no keys gives the segment [0, 1] over the record's own
 * g0 / g1. State 2 (fixed) when the segment does not move, else 1. Layout: SafeHouse port (aseg.h, lo.h XF). */
typedef int qword __attribute__((mode(TI)));
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
int FFloatsNear(float a, float b, float eps) asm("FFloatsNear__Ffff");
extern qword D_002A2DD0;   /* the zero vector */
static __inline__ int FVecsNear(qword a, qword b)
{
    return FFloatsNear(GetX(a), GetX(b), 1e-4f) && FFloatsNear(GetY(a), GetY(b), 1e-4f) &&
           FFloatsNear(GetZ(a), GetZ(b), 1e-4f);
}
typedef struct KEYA3 { float g; float dgIn; float dgOut; } KEYA3;
typedef struct TRKPA { int pvtbl; int ckey; float *at; KEYA3 *aakey[3]; int pad18[2]; float v[4]; } TRKPA;
typedef union VQ { float af[4]; qword q; } VQ;
typedef struct XF {
    char pad[0x80];
    float g0;          /* field: SafeHouse port */
    float g1;          /* field: SafeHouse port */
    float *pg;         /* field: SafeHouse port - the parameter (&g0 when unset) */
    float *pdgScale;   /* field: SafeHouse port - its rate (&g1 when unset) */
    char pad90[0x9A - 0x90];
    short state;       /* field: SafeHouse port */
    char pad9C[0xC0 - 0x9C];
    VQ pos0;           /* field: SafeHouse port (aseg[0..3]) */
    VQ vel0;
    VQ pos1;
    VQ vel1;
} XF;
int IkeyFind__5TRKPAf(TRKPA *ptrk, float g);
// name: SafeHouse port (TRKPA::Setup)
void Setup__5TRKPAP2XF(TRKPA *ptrk, XF *pxf)
{
    int ikey;
    unsigned int iaxis;
    int fStill;
    if (ptrk->ckey) {
        ikey = IkeyFind__5TRKPAf(ptrk, *pxf->pg);
        pxf->g0 = ptrk->at[ikey - 1];
        pxf->g1 = ptrk->at[ikey];
    } else {
        pxf->pg = &pxf->g0;
        pxf->g1 = 1.0f;
        pxf->pdgScale = &pxf->g1;
        pxf->g0 = 0;
    }
    for (iaxis = 0; iaxis < 3; iaxis++) {
        KEYA3 *akey = ptrk->aakey[iaxis];
        if (akey) {
            KEYA3 *pkey0 = &akey[ikey - 1];
            KEYA3 *pkey1 = &akey[ikey];
            pxf->pos0.af[iaxis] = pkey0->g;
            pxf->vel0.af[iaxis] = pkey0->dgOut;
            pxf->pos1.af[iaxis] = pkey1->g;
            pxf->vel1.af[iaxis] = pkey1->dgIn;
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
