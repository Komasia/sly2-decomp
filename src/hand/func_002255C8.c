typedef int qword __attribute__((mode(TI)));
struct T { char pad[0x80]; qword v; };
struct O { char pad[0xE8]; struct T *t; };
struct Q { int a; struct O *o; };
struct S { char pad[0x1B0]; void *x; };
extern qword D_002A2DD0;
extern char D_002C43D0[], D_002C43E0[];
void AccelAloPos__FP3ALOG9VU_VECTOR(struct O *o, qword v);
qword PosOfLo__FP2LO(void *p);
void AccelAloTowardPosition__FP3ALOG9VU_VECTORP3CLQT1T2(struct O *o, qword v, void *a, qword b, void *c);
// name: SafeHouse port (ApplyExtractorHook)
void ApplyExtractorHook__FP3ALOT0(struct S *p, struct Q *q)
{
    struct O *o = q->o;
    union { qword q; float f[4]; } u;
    qword r, v;

    float m = -1.0f;
    qword s;
    __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(m));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(o->t->v), "j"(s));
    u.q = s;
    AccelAloPos__FP3ALOG9VU_VECTOR(o, r);
    if (p->x) v = PosOfLo__FP2LO(p->x); else v = PosOfLo__FP2LO(p);
    AccelAloTowardPosition__FP3ALOG9VU_VECTORP3CLQT1T2(o, v, D_002C43D0, D_002A2DD0, D_002C43E0);
}
