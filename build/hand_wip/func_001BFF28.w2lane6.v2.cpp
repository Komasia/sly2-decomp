// Route builder: path between two points over a navigation triangle graph.
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
union U {qword q;float f[4];};
struct V;
struct EDGE {V *to; volatile int cost;};
struct V {U pos; int count; EDGE *edges;};
struct TRI {V *v[3];};
struct BSP;
struct G {int pad0[3]; TRI *tris; int nodes; BSP *tree;};
struct REQ {int bytes, align; REQ() {} REQ *Set(int n) {bytes = n; align = 16; return this;}};
extern float D_002C0C04;
extern qword D_002A2DA0;
extern "C" {
TRI *func_001BF1F8(G *, BSP *, qword, int);
qword func_001BFDB0(TRI *, qword);
void func_001AE478(void *);
void func_001AE4A0(void *, int);
void *func_001AE318(REQ *);
void func_001BF980(G *, V *, V *, int, int *, V **);
void func_001BFC18(G *, int *, V **);
int func_001BFF28(G *, qword, qword, int, U *);
}
struct MARK {MARK() {func_001AE478(this);} ~MARK() {func_001AE4A0(this, 2);}};
static inline qword ToVF(qword v) {qword r; int dummy; __asm__("qmtc2.ni %2,%0" : "=j"(r), "=r"(dummy) : "r"(v)); return r;}
static inline int Dist2DI(qword a, qword b) {
    qword d; int r;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(d) : "j"(d));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0,%1" : "=r"(r) : "j"(d));
    return r;
}
static inline float Dist2D(qword a, qword b) {
    qword d; float r;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(d) : "j"(d));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0,%1" : "=r"(r) : "j"(d));
    return r;
}
struct VUF {qword q;};
static inline VUF Splat(const float &f) {VUF s; __asm__("qmtc2.ni %1,%0" : "=j"(s.q) : "r"(*(const int *)&f)); return s;}
static inline qword Offset(qword p, qword axis, VUF s) {qword r; __asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(p), "j"(axis), "j"(s.q)); return r;}
int func_001BFF28(G *g, qword from, qword to, int capacity, U *out)
{
    TRI *first = func_001BF1F8(g, g->tree, from, 1);
    if (!first) return 0;
    qword start = func_001BFDB0(first, from);
    TRI *last = func_001BF1F8(g, g->tree, to, 1);
    if (!last) return 0;
    qword finish = func_001BFDB0(last, to);
    U *write;
    int count;
    if (first == last) {
        out[0].q = from;
        out[1].q = start;
        count = 3;
        write = out + 1;
        out[2].q = finish;
    } else {
        MARK mark;
        write = out + 1;
        V **path = (V **)func_001AE318(REQ().Set(0x200));
        V initial;
        initial.pos.q = start;
        initial.count = 3;
        initial.edges = (EDGE *)func_001AE318(REQ().Set(0x18));
        qword sv = ToVF(start);
        for (int i = 0; i < 3; i++) {
            V *v = first->v[i];
            EDGE *e = &initial.edges[i];
            e->to = v;
            e->cost = Dist2DI(sv, v->pos.q);
        }
        V goal;
        goal.pos.q = finish;
        goal.count = 0;
        goal.edges = 0;
        qword fv = ToVF(finish);
        V *pg = &goal;
        for (int i = 0; i < 3; i++) {
            V *v = last->v[i];
            int n = v->count;
            v->count = n + 1;
            EDGE *e = v->edges + n;
            e->to = pg;
            e->cost = Dist2DI(v->pos.q, fv);
        }
        int found;
        func_001BF980(g, &initial, pg, 128, &found, path);
        if (found >= 3) func_001BFC18(g, &found, path);
        int n = found; if (n > capacity) n = capacity; count = n;
        for (int i = 0; i < count; i++) out[i].q = path[i]->pos.q;
        for (int i = 0; i < 3; i++) last->v[i]->count--;
    }
    {
        U *end = out + count;
        qword prev = out[0].q;
        U *rd = write;
        U *wr = write;
        if (wr < end) {
            float thr = D_002C0C04;
            do {
                int accept = thr < Dist2D(rd->q, prev);
                if (accept) {
                    U *s = rd++;
                    U *d = wr++;
                    prev = s->q;
                    d->q = prev;
                } else rd++;
            } while (rd < end);
        }
        count = wr - out;
    }
    if (count == 1) {
        qword p = out[0].q;
        VUF s = Splat(D_002C0C04);
        out[1].q = p;
        count = 2;
        out[0].q = Offset(p, D_002A2DA0, s);
    }
    return count;
}
