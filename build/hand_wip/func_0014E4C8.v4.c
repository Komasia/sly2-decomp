/* v4 (Claude agent, 2026-10-17): aligned 31 -> 20. In the match block read pe->po directly (`poTop = pe->po;` under i == 0, and `struct O *o = pe->po;` only inside the vt[5] call block) instead of one `o` copy shared by both. Left: compare temps a0/a1 (ours v1/v0), e.b / aTop store order around the blez, struct-copy regs. */
/* v3 (Claude agent): ((grf ^ 1) & 1) gives the xori flag; poTop/aTop/bTop zeroed after e init. 28 diffs left: poTop/bTop s4/s5 swap, a0-a2 vs v0/v1 temps. */
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
    struct O *poTop;
    int aTop;
    int bTop;
    e.prio = prio;
    e.po = po;
    e.a = a;
    e.b = b;
    poTop = 0;
    aTop = 0;
    bTop = 0;
    peOut = p->ae;
    pe = p->ae;
    for (i = 0; i < p->c; i++, pe++) {
        if ((((grf ^ 1) & 1) || e.prio == pe->prio) &&
            (!(grf & 2) || e.po == pe->po) &&
            (!(grf & 4) || e.a == pe->a) &&
            (!(grf & 8) || e.b == pe->b)) {
            if (i == 0) {
                poTop = pe->po;
                aTop = pe->a;
                bTop = pe->b;
            }
            {
                struct O *o = pe->po;
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
