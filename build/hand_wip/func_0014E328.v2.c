/* near-miss: b (t0) should live in $s5 and the &ae[].b base be spilled to sp+4; ours spills b instead. Also an extra .p2align nop in the search loop. */
struct VTE { short d; short pad; void (*pfn)(void *, ...); };
struct O { int pad[3]; struct VTE *vt; };
struct E { int prio; struct O *po; int a; int b; };
struct P { char pad[0x30C]; int c; struct E ae[8]; char pad2[0x390 - 0x390]; float t; };
struct CLOCK { float t; float dt; };
extern struct CLOCK D_002DDED0;
void *func_002332B8(void *dst, void *src, int cb);
void func_0014E328(struct P *p, int prio, struct O *po, int a, int b)
{
    int i;
    if (p->c < sizeof(p->ae) / sizeof(p->ae[0])) {
        for (i = 0; i < p->c; i++) {
            if (p->ae[i].prio < prio)
                break;
        }
        func_002332B8(&p->ae[i + 1], &p->ae[i], (p->c - i) * sizeof(struct E));
        p->ae[i].prio = prio;
        p->ae[i].po = po;
        p->ae[i].a = a;
        p->ae[i].b = b;
        p->c++;
        {
            struct VTE *e = &po->vt[4];
            ((void (*)(void *, int))e->pfn)((char *)po + e->d, b);
        }
        if (i == 0) {
            if (p->c >= 2) {
                struct O *o = p->ae[1].po;
                struct VTE *e = &o->vt[3];
                ((void (*)(void *, int, int))e->pfn)((char *)o + e->d, p->ae[1].a, p->ae[1].b);
            }
            p->t = D_002DDED0.t;
            {
                struct VTE *e = &po->vt[2];
                ((void (*)(void *, int, int))e->pfn)((char *)po + e->d, a, b);
            }
        }
    }
}
