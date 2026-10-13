typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct VE { short d; short pad; void (*pf)(void *, float, float, qword *, int); };
struct CV { struct VE *vt; };
struct C { int a; struct CV *pcv; };
struct V3 { float x, y, z; };
struct S { int h; void *po; float a; float b; float c; float ca; float cb; int dist; struct V3 v; int pad; int f; };
extern char D_003DD490[];
int func_0015E938(void *p, int n, int h, void *arg);
float *func_0012F938(void *po, int n);
struct C *func_0012FF10(void *po, void *arg, void *value, int check);

void func_0020BD88(struct S *p, void *arg)
{
    float *pa, *pb, *pc;
    struct C *c;
    U v0, v1, v2;
    qword d;
    int n;
    float h;
    if (p->f)
        return;
    if (!p->po) {
        p->po = (void*)func_0015E938(D_003DD490, 4, p->h, arg);
        if (!p->po)
            return;
    }
    pa = func_0012F938(p->po, 0x22);
    if (!pa)
        return;
    pb = func_0012F938(p->po, 0x23);
    if (!pb)
        return;
    pc = func_0012F938(p->po, 0x24);
    if (!pc)
        return;
    p->a = *pa;
    p->b = *pb;
    p->c = *pc;
    p->cb = p->c - p->b;
    p->ca = p->c - p->a;
    c = func_0012FF10(p->po, arg, (void*)1, 1);
    if (!c)
        goto initialized;
    c->pcv->vt[3].pf((char *)c->pcv + c->pcv->vt[3].d, p->a, 1.0f, &v0.q, 0);
    c->pcv->vt[3].pf((char *)c->pcv + c->pcv->vt[3].d, p->c, 1.0f, &v1.q, 0);
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(v0.q), "j"(v1.q));
    h = p->c;
    h -= p->a;
    h *= 0.5f;
    __asm__("vmul.xy %0, %0, %0\n\tvaddy.x %0, %0, %0y\n\tvsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(n) : "j"(d));
    p->dist = n;
    c->pcv->vt[3].pf((char *)c->pcv + c->pcv->vt[3].d, p->a + h, 1.0f, &v2.q, 0);
    {
        struct V3 *pv = &p->v;
        pv->x = 0;
        pv->y = 0;
        pv->z = (-v2.f[2] + v0.f[2]) / (h * h * 0.5f);
    }
initialized:
    p->f = 1;
}
