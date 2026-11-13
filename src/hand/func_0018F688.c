typedef struct { float x, y, z, w; } __attribute__((aligned(16))) VEC;
struct T { char pad[0x18]; float g18; float g1c; };
struct S { char pad[0x150]; struct T *pt; char p1[0x54]; float g; char p2[0x1714]; int n; };
extern char D_002BF4D0[];

void ChooseAttackTarget__FP5ACTORfUifP6VECTORPvPG9VU_VECTORf(struct S *p, float g, int a, void *pv, int *pn, VEC *pq, float h, float k);

float atan2f(float y, float x);
void SetStepPhysHeading__FP3ALOf(struct S *p, float g);
void TurnActorNow__FP5ACTOR(struct S *p);
// name: SafeHouse port (ChooseSlyRushTarget)
void ChooseSlyRushTarget__FP3SLY(struct S *p)
{
    VEC v;
    int n;
    float g;
    if (p->pt && 0.5f < p->pt->g1c) g = p->pt->g18;
    else g = p->g;
    ChooseAttackTarget__FP5ACTORfUifP6VECTORPvPG9VU_VECTORf(p, g, 8, D_002BF4D0, &n, &v, 0.25f, 1.0f);
    p->n = n;
    if (n)
        g = atan2f(v.y, v.x);
    SetStepPhysHeading__FP3ALOf(p, g);
    TurnActorNow__FP5ACTOR(p);
}
