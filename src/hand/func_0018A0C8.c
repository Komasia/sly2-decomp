typedef int qword __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } VEC;
typedef union { qword q; VEC v; } UV;
struct VTE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VTE *vt; };
struct T { char pad[0x4C]; struct O *po; };
struct S {
    char pad[0xC]; struct VTE *vt; char p0[0x198]; float g1a8; char p1[0x5C]; struct T *pt208;
    char p2[0xE1C]; void *x1028; char p3[8]; void *x1034; char p4[0x4DC]; int x1514; char p5[8];
    char x1520[0x100]; char x1620[0x3B4]; int x19d4, x19d8, x19dc, x19e0; char p6[0xC]; int x19f0, x19f4;
};
#include "clock.h"
int GrfActorLookMask__FP5ACTOR(struct S *p);
void SetSmaMask__FP3SMAUi(void *p, int n);
float GLimitAbs(float g, float h) asm("GLimitAbs__Fff");
void SetStepPhysHeading__FP3ALOf(struct S *p, float g);
void RebuildSlyFootProbe__FP3SLYP2XFfT1P12SLYFOOTPROBEP3XMG(struct S *p, int a, int b, int c, float g, void *pv);
int MatchSlyFootProbe__FP3SLYP12SLYFOOTPROBEP10CTRLSOURCE(struct S *p, void *pv, int n);
int IsmsFindSmOptional(void *p, int n) asm("IsmsFindSmOptional__FP2SM3OID");
void SetSmaState__FP3SMA3OID(void *p, int n);
// name: SafeHouse port (UpdateSlyStanding)
void UpdateSlyStanding__FP3SLY(struct S *p)
{
    struct VTE *e;
    SetSmaMask__FP3SMAUi(p->x1034, GrfActorLookMask__FP5ACTOR(p));
    e = &p->vt[92];
    if (!((int (*)(void *))e->pfn)((char *)p + e->d) && p->pt208) {
        struct O *o = p->pt208->po;
        UV u;
        e = &o->vt[34];
        u.q = ((qword (*)(void *))e->pfn)((char *)o + e->d);
        u.v.z = GLimitAbs(u.v.z, 10.0f);
        SetStepPhysHeading__FP3ALOf(p, p->g1a8 + u.v.z * g_clock.dt);
    }
    if (p->x19f0) {
        RebuildSlyFootProbe__FP3SLYP2XFfT1P12SLYFOOTPROBEP3XMG(p, p->x19d8, p->x19e0, p->x19f0, 5.0f, p->x1520);
        RebuildSlyFootProbe__FP3SLYP2XFfT1P12SLYFOOTPROBEP3XMG(p, p->x19d4, p->x19dc, p->x19f4, 5.0f, p->x1620);
        if ((!MatchSlyFootProbe__FP3SLYP12SLYFOOTPROBEP10CTRLSOURCE(p, p->x1520, p->x19f0) || !MatchSlyFootProbe__FP3SLYP12SLYFOOTPROBEP10CTRLSOURCE(p, p->x1620, p->x19f4)) &&
            !p->x1514 && p->x1028) {
            if (IsmsFindSmOptional(p->x1028, 0x17C) >= 0) SetSmaState__FP3SMA3OID(p->x1034, 0x17C);
            p->x1514 = 1;
        }
    }
}
