typedef int qword __attribute__((mode(TI)));
struct V { float x, y, z, w; float pad[8]; };
struct O { char pad[0x40]; char sub[0x30]; qword q70; };
struct P { char pad[0x60]; struct O *po; };
struct Out { int n0; int pad[3]; qword q10; qword q20; float g30; float g34; float g38; int n3C; };
struct CLOCK { float t; };
extern struct CLOCK g_clock;
qword VelXfPoint__FP2XFT0G9VU_VECTOR(struct O *, int, qword);
void LevelMatrix3__FP7MATRIX3T0Pv(void *, int, struct V *);
float atan2f(float, float);
// name: SafeHouse port (GetSoCpdefi)
void GetSoCpdefi__FP2SOP6CPDEFI(struct P *p, struct Out *po)
{
    struct O *o = p->po;
    struct V v;
    void *ps;
    qword q = o->q70;
    po->q10 = q;
    ps = o->sub;
    po->q20 = VelXfPoint__FP2XFT0G9VU_VECTOR(o, 0, q);
    LevelMatrix3__FP7MATRIX3T0Pv(ps, 0, &v);
    po->g30 = atan2f(-v.y, -v.x); po->g34 = 100.0f; po->n0 = 0; po->g38 = g_clock.t; po->n3C = 0;
}
