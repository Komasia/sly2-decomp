struct E { float t; int k; int x8; int xC; };
struct Q { char pad[0xA0]; int c; struct E *ae; };
struct B { int pad[3]; virtual void Begin(); virtual void End(); };
struct P : B { int x10; struct Q *pq; int x18; float g1C; float g20; char pad2[0x40 - 0x24]; float g40;
    char pad3[0x50 - 0x44]; int i50; };
struct G { P *p; G(P *pp) : p(pp) { p->Begin(); } ~G() { p->End(); } };
extern "C" {
void func_00131290(struct P *p, struct E *pe);
int func_00131968(struct P *p);
}
static inline int FGe(float a, float b) { return b < a || a == b; }
static inline int FGe2(float a, float b) { return b < a || (a == b); }
static inline int FEq(float a, float b) { return a == b; }
extern "C" void func_00130F88(struct P *p)
{
    if (p->pq->c) {
    G g(p);
    p->g20 = p->g1C;
    while (!func_00131968(p)) {
        struct Q *pq = p->pq;
        int i = p->i50;
        float t = p->g20;
        struct E *pe;
        float t2;
        if (i < pq->c && ((pe = &pq->ae[i])->t < (t2 = t) || (t2 == pe->t && 0.0f < p->g40))) {
            p->i50 = i + 1;
            func_00131290(p, pe);
        } else if (p->i50 > 0 && (t < p->pq->ae[p->i50 - 1].t || (t == p->pq->ae[p->i50 - 1].t && p->g40 < 0.0f))) {
            p->i50 = p->i50 - 1;
            func_00131290(p, &p->pq->ae[p->i50]);
        } else {
            p->g1C = t;
            break;
        }
    }
    }
}
