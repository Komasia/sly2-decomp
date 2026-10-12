struct VTE { short d; short pad; void (*pfn)(); };
struct E { float t; int k; int x8; int xC; };
struct Q { char pad[0xA0]; int c; struct E *ae; };
struct P { int pad[3]; struct VTE *vt; int x10; struct Q *pq; int x18; float g1C; float g20; char pad2[0x40 - 0x24]; float g40;
    char pad3[0x50 - 0x44]; int i50; };
struct G { struct P *p; };
void func_00131290(struct P *p, struct E *pe);
int func_00131968(struct P *p);
void func_00130F88(struct P *p)
{
    if (p->pq->c) {
        struct G volatile g;
        g.p = p;
        ((void (*)(void *))p->vt[1].pfn)((char *)p + p->vt[1].d);
        p->g20 = p->g1C;
        while (!func_00131968(p)) {
            struct Q *pq = p->pq;
            int i = p->i50;
            float t = p->g20;
            struct E *pe;
            if (i < pq->c && ((pe = &pq->ae[i])->t < t || (t == pe->t && 0.0f < p->g40))) {
                p->i50 = i + 1;
                func_00131290(p, pe);
            } else if (p->i50 > 0 && (t < p->pq->ae[p->i50 - 1].t || (t == p->pq->ae[p->i50 - 1].t && p->g40 < 0.0f))) {
                i = p->i50 - 1;
                p->i50 = i;
                func_00131290(p, &p->pq->ae[i]);
            } else {
                p->g1C = t;
                break;
            }
        }
        { struct P *po = g.p; ((void (*)(void *))po->vt[2].pfn)((char *)po + po->vt[2].d); }
    }
}
