typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct TRI { char d[12]; };
union NODE { qword plane; struct { float x, y, z; unsigned short child[2]; } e; };
struct GRAPH { char pad[12]; TRI *leaves; int count; NODE *nodes; };
struct STATE { NODE *node; TRI *leaf; float t; U plane; };
struct ROW { U a, b, planeA, planeB; float t0, t1; int flags; TRI *leaf; char tail[16]; };
extern "C" void *func_002333B4(void *, int, unsigned int);
extern "C" int func_001BF398(float);
static inline float GetX(const qword &q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static inline float XOf(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static inline float QX(qword q) { float f; __asm__("qmfc2.ni %0,%1" : "=r"(f) : "j"(q)); return f; }
static inline float GetY(const qword &q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static inline qword Make(float x, float y, float z)
{
    U u;
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    u.q = q;
    return u.q;
}
static inline qword Dot(const qword &a, const qword &b)
{
    qword d, one;
    __asm__ volatile("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(a), "j"(b));
    return d;
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
static inline qword VecCombo(VU_FLOAT f1, VU_VECTOR v1, VU_FLOAT f2, VU_VECTOR v2)
{
    qword r;
    __asm__("vmulax.xyzw $ACC,%2,%1x\n\tvmaddx.xyzw %0,%4,%3x" : "=j"(r) : "j"(f1.q), "j"(v1.q), "j"(f2.q), "j"(v2.q));
    return r;
}
static inline VU_VECTOR Lerp(const qword &a, const qword &b, float t) { return VecCombo(VU_FLOAT(1.0f - t), VU_VECTOR(a), VU_FLOAT(t), VU_VECTOR(b)); }

extern "C" int func_001BF3D8(GRAPH *g, qword from, qword to, int capacity, ROW *out, int flags)
{
    STATE st[33];
    STATE *top;
    ROW *prev = 0;
    ROW *cursor = out;
    NODE *nodes = g->nodes;
    NODE *end = nodes + g->count;
    TRI *leaves = g->leaves;
    int mask = (flags & 1) ? 0x8000 : 0x4000;

    func_002333B4(&st[0], 0, sizeof(STATE));
    st[0].node = nodes;
    top = &st[1];
    func_002333B4(top, 0, sizeof(STATE));
    top->t = 1.0f;
    VU_VECTOR fromPlane(Make(GetX(from), GetY(from), -1.0f));
    VU_VECTOR toPlane(Make(GetX(to), GetY(to), -1.0f));
    for (;;) {
        if (st[0].node == end) {
            do {
                if (st[0].leaf) {
                    if (prev && st[0].t == prev->t1 && ((flags & 2) || st[0].leaf == prev->leaf)) {
                        prev->b.q = Lerp(from, to, top->t).q;
                        prev->t1 = top->t;
                        prev->planeB = top->plane;
                    } else {
                        float lo, hi;
                        if (cursor - out >= capacity)
                            return capacity;
                        prev = cursor++;
                        func_002333B4(prev, 0, sizeof(ROW));
                        lo = st[0].t;
                        hi = top->t;
                        prev->flags = 3;
                        prev->a.q = Lerp(from, to, lo).q;
                        prev->b.q = Lerp(from, to, hi).q;
                        prev->t0 = lo;
                        prev->t1 = hi;
                        prev->planeA = st[0].plane;
                        prev->planeB = top->plane;
                        prev->leaf = st[0].leaf;
                    }
                }
                if (top <= &st[1])
                    return cursor - out;
                st[0] = *top--;
            } while (st[0].node == end);
        }
        {
            qword q0 = Dot(st[0].node->plane, fromPlane.q);
            qword q1 = Dot(st[0].node->plane, toPlane.q);
            float d0 = QX(q0);
            float d1 = QX(q1);
            int s0 = func_001BF398(d0);
            int s1 = func_001BF398(d1);
            int neg, pos;
            unsigned int child;
            neg = 0;
            if (s0 == 1 || s1 == 1)
                neg = 1;
            pos = 0;
            if (s0 == 0 || s1 == 0)
                pos = 1;
            if (!neg || !pos) {
                child = st[0].node->e.child[pos];
                if (child & 0x8000) {
                    st[0].node = end;
                    if (child & mask) {
                        child &= 0x3FFF;
                        st[0].leaf = &leaves[child];
                    } else
                        st[0].leaf = 0;
                } else {
                    st[0].node = &nodes[child];
                }
            } else {
                float cross = d0 / (d0 - d1);
                float lo = st[0].t, hi = top->t;
                float dl = lo * d1 + (1.0f - lo) * d0;
                float dh = hi * d1 + (1.0f - hi) * d0;
                int nearNeg;
                if (lo < cross && cross < hi) {
                    unsigned int c;
                    top++;
                    top->t = cross;
                    top->plane.f[0] = st[0].node->e.x;
                    top->plane.f[1] = st[0].node->e.y;
                    top->plane.f[2] = 0.0f;
                    top->plane.f[3] = st[0].node->e.z;
                    c = st[0].node->e.child[dl <= 0.0f];
                    if (c & 0x8000) {
                        top->node = end;
                        if (c & mask) {
                            c &= 0x3FFF;
                            top->leaf = &leaves[c];
                        } else
                            top->leaf = 0;
                    } else {
                        top->leaf = 0;
                        top->node = &nodes[c];
                    }
                }
                nearNeg = 0;
                if (dl < 0.0f || (dl == 0.0f && dh <= 0.0f))
                    nearNeg = 1;
                child = st[0].node->e.child[!nearNeg];
                if (child & 0x8000) {
                    st[0].node = end;
                    if (child & mask) {
                        child &= 0x3FFF;
                        st[0].leaf = &leaves[child];
                    } else
                        st[0].leaf = 0;
                } else {
                    st[0].node = &nodes[child];
                }
            }
        }
    }
}
