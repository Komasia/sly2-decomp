/* wip: ~18 diffs: func_0012FF10 arg setup order (a3 before a0), f13/a2 order in vcalls, VF numbering
   (target u->vf1, v0->vf2, v1->vf3, tmp->vf4), lui s6 order. */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct VE { short d; short pad; void (*pf)(void *, qword *, int, float, float); };
struct CV { struct VE *vt; };
struct C { int a; struct CV *pcv; };
struct O { char pad[0x74]; int t; };
struct E { struct O *po; int pad[3]; qword vel; int speed; int pad2[3]; };
struct S { struct E ae[4]; int fInit; };
extern char D_003DD490[];
struct O *func_0015E938(void *p, int n, struct O *h, int arg);
struct C *func_0012FF10(struct O *po, int arg, int a, int b);

void func_0020C7E0(struct S *p, int arg)
{
    struct E *e;
    if (p->fInit)
        return;
    e = p->ae;
    do {
        struct O *o;
        struct C *c;
        U v0, v1;
        U u;
        qword d, vel, r, tmp, s;
        int f;
        o = func_0015E938(D_003DD490, 4, e->po, arg);
        e->po = o;
        if (!o)
            continue;
        c = func_0012FF10(o, arg, 1, 1);
        c->pcv->vt[3].pf((char *)c->pcv + c->pcv->vt[3].d, &v0.q, 0, 0.0f, 1.0f);
        c->pcv->vt[3].pf((char *)c->pcv + c->pcv->vt[3].d, &v1.q, 0, *(float *)&o->t, 1.0f);
        o = (struct O *)o->t;
        __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(o));
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(v1.q), "j"(v0.q));
        __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(vel) : "j"(d), "j"(u.q));
        __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(r), "=&j"(tmp) : "j"(vel));
        e->vel = vel;
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(s) : "j"(r));
        __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(s));
        e->speed = f;
    } while (++e < p->ae + 4);
    p->fInit = 1;
}
