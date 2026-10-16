/* v2 (Claude agent, logic audit): fixed logic -- the p->c>0 block is inside if(poTop) (target beqz s4 -> epilogue). 38/116 remaining: fAny xori flag form + temps. */
struct VTE { short d; short pad; void (*pfn)(void *, ...); };
struct O { int pad[3]; struct VTE *vt; };
struct E { int prio; struct O *po; int a; int b; };
struct P { char pad[0x30C]; int c; struct E ae[8]; char pad2[0x390 - 0x390]; float t; };
struct CLOCK { float t; float dt; };
extern struct CLOCK D_002DDED0;
void func_0014E4C8(struct P *p, int grf, int prio, struct O *po, int a, int b)
{
    struct E e;
    struct E *peOut;
    struct E *pe;
    int i;
    struct O *poTop = 0;
    int aTop = 0;
    int bTop = 0;
    e.prio = prio;
    e.po = po;
    e.a = a;
    e.b = b;
    peOut = p->ae;
    pe = p->ae;
    for (i = 0; i < p->c; i++, pe++) {
        if ((!(grf & 1) || e.prio == pe->prio) &&
            (!(grf & 2) || e.po == pe->po) &&
            (!(grf & 4) || e.a == pe->a) &&
            (!(grf & 8) || e.b == pe->b)) {
            struct O *o = pe->po;
            if (i == 0) {
                poTop = o;
                aTop = pe->a;
                bTop = pe->b;
            }
            {
                struct VTE *v = &o->vt[5];
                ((void (*)(void *, int))v->pfn)((char *)o + v->d, pe->b);
            }
        } else {
            *peOut++ = *pe;
        }
    }
    p->c = peOut - p->ae;
    if (poTop) {
        struct VTE *v = &poTop->vt[3];
        ((void (*)(void *, int, int))v->pfn)((char *)poTop + v->d, aTop, bTop);
    if (p->c > 0) {
        struct O *o;
        struct VTE *v;
        p->t = D_002DDED0.t;
        o = p->ae[0].po;
        v = &o->vt[2];
        ((void (*)(void *, int, int))v->pfn)((char *)o + v->d, p->ae[0].a, p->ae[0].b);
    }
    }
}
