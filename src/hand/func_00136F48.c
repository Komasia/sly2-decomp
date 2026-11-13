typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float a[4]; } QF;
struct PO { char pad[0x1A8]; float g1A8; char pad1[0x10B8 - 0x1AC]; int x10B8; };
struct E { float f0; int pad[2]; float fC; int pad2[2]; void *p18; };
struct S { struct PO *po; int state; int x8; int xC; int x10; int x14; float g18; float g1C; char a20[0x10]; float g30; float g34;
    struct E ae[6]; char pad[0xE0 - 0x38 - 6 * 28]; void *pvE0; void *pvE4; };
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
extern qword D_002A2DD0;
void ChooseAttackTarget__FP5ACTORfUifP6VECTORPvPG9VU_VECTORf(struct PO *, int, void *, int *, QF *, float, float, float);
qword ConvertPos__FP2LOT0G9VU_VECTOR(void *, struct PO *, qword);
void func_002046B0(struct PO *, qword);
void TurnActorNow__FP5ACTOR(struct PO *);
void RecalcBlend__FP6ASEGBL(void *);
void ApplyAsegCur(void *, struct PO *, int, void **, float, float) asm("ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA");
void DemoteAsegaOnXf__FiiP2XF(void *, struct PO *, int);
void SetAsegaSeekTime__FP5ASEGAf(void *, float);
static __inline__ float Clamp(float g, float gMin, float gMax)
{
    if (g < gMin)
        return gMin;
    if (gMax < g)
        return gMax;
    return g;
}
// name: SafeHouse port (SetBentleySubMode)
void SetBentleySubMode__FP7BENTLEYi(struct S *ps, int state)
{
    void *pv;
    float dt;
    if (state == ps->state)
        return;
    if (ps->state == -1) {
        int f;
        QF v;
        QF r;
        float g;
        ps->g18 = g_clock.t;
        ps->xC = 0;
        ps->x10 = 0;
        ps->x14 = 0;
        g = 1.5f;
        if (state == 0)
            g = 3.15f;
        ChooseAttackTarget__FP5ACTORfUifP6VECTORPvPG9VU_VECTORf(ps->po, 2, ps->a20, &f, &v, ps->po->g1A8, 0.15f, g);
        if (f) {
            ps->g1C = Clamp((v.a[2] - ps->g30) / (ps->g34 - ps->g30), 0.0f, 1.0f);
        } else {
            ps->g1C = 0.5f;
        }
        r.q = ConvertPos__FP2LOT0G9VU_VECTOR(ps->pvE4, ps->po, D_002A2DD0);
        ps->x8 = 0.0f < r.a[1] ? 1 : 0;
        if (state == 0 && f) {
            func_002046B0(ps->po, v.q);
            TurnActorNow__FP5ACTOR(ps->po);
        }
    }
    ps->state = state;
    dt = 0.0f;
    switch (state) {
    case -1:
        pv = 0;
        break;
    case 0:
    case 1:
    case 2: {
        struct E *pe = &ps->ae[state * 2 + ps->x8];
        pe->f0 = 1.0f - ps->g1C;
        pv = pe->p18;
        pe->fC = ps->g1C;
        dt = 0.06666667f;
        RecalcBlend__FP6ASEGBL(pv);
        break;
    }
    }
    ApplyAsegCur(pv, ps->po, 1, &ps->pvE0, g_clock.t - ps->g18, 1.0f);
    if (!ps->pvE0)
        return;
    if (ps->x10)
        DemoteAsegaOnXf__FiiP2XF(ps->pvE0, ps->po, ps->po->x10B8);
    if (ps->pvE0 && dt != 0.0f)
        SetAsegaSeekTime__FP5ASEGAf(ps->pvE0, g_clock.t + dt);
}
