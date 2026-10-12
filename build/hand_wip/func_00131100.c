struct VTE { short d; short pad; void (*pfn)(); };
struct E { float t; int k; int x8; int xC; };
struct Q { char pad[0xA0]; int c; struct E *ae; };
struct P { int pad[3]; struct VTE *vt; int x10; struct Q *pq; int x18; float g1C; float g20; char pad2[0x40 - 0x24]; float g40;
    char pad3[0x50 - 0x44]; int i50; };
struct G { struct P *p; };
void func_00131290(struct P *p);
int func_00131968(struct P *p);
void func_00131100(struct P *p)
{
    if (p->pq->c) {
        struct G g;
        g.p = p;
        __asm__ __volatile__("" : : "r"(&g) : "memory");
        ((void (*)(void *))p->vt[1].pfn)((char *)p + p->vt[1].d);
        p->g20 = p->g1C;
        while (!func_00131968(p)) {
            struct Q *pq = p->pq;
            int i = p->i50;
            float t = p->g20;
            register struct E *pe __asm__("$5");
            if (i < pq->c && (pe = (struct E *)((char *)pq->ae + (i << 4)))->t <= t && 0.0f <= p->g40) {
                p->i50 = i + 1;
            } else if (p->i50 > 0 && t <= p->pq->ae[p->i50 - 1].t && p->g40 < 0.0f) {
                i = p->i50 - 1;
                p->i50 = i;
                pe = &p->pq->ae[i];
            } else {
                p->g1C = t;
                break;
            }
            switch (pe->k) {
            case 7: case 8: case 11: case 13: case 14: case 15: case 16:
            case 21: case 22: case 23: case 24:
                func_00131290(p);
                break;
            }
        }
        { struct P *po = g.p; ((void (*)(void *))po->vt[2].pfn)((char *)po + po->vt[2].d); }
    }
}
