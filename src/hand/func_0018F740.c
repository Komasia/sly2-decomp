typedef int qword __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) VEC;
struct S { char pad[0x1A8]; float g; char p1[0x1714]; int n; };
extern char D_002BF4E0[];
void ChooseAttackTarget__FP5ACTORfUifP6VECTORPvPG9VU_VECTORf(struct S *p, int a, void *pv, int *pn, VEC *pq, float g, float h, float k);
void func_002046B0(struct S *p, qword q);
void TurnActorNow__FP5ACTOR(struct S *p);
// name: SafeHouse port (ChooseSlyAirSwingTarget)
void ChooseSlyAirSwingTarget__FP3SLY(struct S *p)
{
    VEC v;
    int n;
    ChooseAttackTarget__FP5ACTORfUifP6VECTORPvPG9VU_VECTORf(p, 4, D_002BF4E0, &n, &v, p->g, 0.25f, 3.15f);
    p->n = n;
    if (n) {
        func_002046B0(p, *(qword *)&v);
        TurnActorNow__FP5ACTOR(p);
    }
}
