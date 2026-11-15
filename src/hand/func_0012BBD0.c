/* TRKPK::Setup for one-tangent keys: the transform record gets the key segment around its parameter (times,
 * end points and tangents); state 2 (fixed) when it does not move, else 1 (spline). Layout: SafeHouse port. */
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
typedef struct VECTOR3 { float x, y, z; } VECTOR3;
typedef union V3Q { VECTOR3 v; qword q; } V3Q;
typedef struct KEYP1 { VECTOR3 pos; float t; qword v; } KEYP1;
typedef struct TRKPK { int pvtbl; int ckey; KEYP1 *akey; } TRKPK;
typedef struct XF {
    char pad[0x80];
    float g0;          /* field: SafeHouse port */
    float g1;          /* field: SafeHouse port */
    float *pg;         /* field: SafeHouse port */
    char pad8C[0x9A - 0x8C];
    short state;       /* field: SafeHouse port */
    char pad9C[0xC0 - 0x9C];
    V3Q pos0;          /* field: SafeHouse port (aseg[0..3]) */
    qword vel0;
    V3Q pos1;
    qword vel1;
} XF;
int func_0012BB70(TRKPK *ptrk, float g);
void func_0012BBD0(TRKPK *ptrk, XF *pxf)
{
    int ikey = func_0012BB70(ptrk, *pxf->pg);
    int fStill;
    pxf->g0 = ptrk->akey[ikey - 1].t;
    pxf->pos0.v = ptrk->akey[ikey - 1].pos;
    pxf->vel0 = ptrk->akey[ikey - 1].v;
    pxf->g1 = ptrk->akey[ikey].t;
    pxf->pos1.v = ptrk->akey[ikey].pos;
    pxf->vel1 = ptrk->akey[ikey].v;
    fStill = FVecsNear(pxf->pos0.q, pxf->pos1.q) && FVecsNear(D_002A2DD0, pxf->vel0) &&
            FVecsNear(D_002A2DD0, pxf->vel1);
    pxf->state = fStill ? 2 : 1;
}
