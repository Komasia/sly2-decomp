typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct VE { short d; short pad; void (*pf)(void *,float,float,qword *,int); };
struct CV { struct VE *vt; };
struct C { int a; struct CV *pcv; };
struct O { char pad[0x74]; int t; };
struct E { struct O *po; int pad[3]; qword vel; int speed; int pad2[3]; };
struct S { struct E ae[4]; int fInit; };
extern char D_003DD490[];
int func_0015E938(void *p,int n,int h,void *arg);
struct C *func_0012FF10(struct O *,void *,void *,int);

void func_0020C7E0(struct S *p,void *arg)
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
        register qword scalar __asm__("vf1");
        int f;
        o = (struct O *)func_0015E938(D_003DD490,4,(int)e->po,arg);
        e->po = o;
        if (!o)
            continue;
        c = func_0012FF10(o,arg,(void*)1,1);
        c->pcv->vt[3].pf((char *)c->pcv + c->pcv->vt[3].d, 0.0f,1.0f,&v0.q,0);
        c->pcv->vt[3].pf((char *)c->pcv + c->pcv->vt[3].d, *(float *)&o->t,1.0f,&v1.q,0);
        o = (struct O *)o->t;
        __asm__("qmtc2.ni %1, %0" : "=j"(scalar) : "r"(o));
        u.q=scalar;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "0"(v1.q), "j"(v0.q));
        __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(vel) : "0"(scalar), "j"(d));
        __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(r), "=&j"(tmp) : "j"(vel));
        e->vel = vel;
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(s) : "0"(r));
        __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(s));
        e->speed = f;
    } while (++e < p->ae + 4);
    p->fInit = 1;
}
