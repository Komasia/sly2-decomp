// Cache eleven Hermite samples of one path segment and the cumulative lengths between them.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f; };
struct M4 { qword a, b, c, d; };
struct S {
    char pad[0xEC]; float *times; float *dist; qword *v; char padF8[8];
    struct M4 mat; qword *in; qword *out; int segment; float lengths[11];
};
void func_00117120(float, float, float, qword, qword, qword, qword, qword *, qword *, qword *);
static inline qword Dir(qword m0, qword m1, qword m2, qword a)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r) : "j"(m0), "j"(m1), "j"(m2), "j"(a) : "memory");
    return r;
}
static inline qword Point(qword m0, qword m1, qword m2, qword m3, qword a)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w" : "=j"(r) : "j"(m0), "j"(m1), "j"(m2), "j"(m3), "j"(a) : "memory");
    return r;
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float Len(qword a)
{
    qword one;
    float f;
    __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "+j"(a), "=&j"(one));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "+j"(a));
    __asm__("qmfc2.ni %0,%1" : "=r"(f) : "j"(a));
    return f;
}
void func_001E5FC8(struct S *p, int i)
{
    union U prev, cur, start, end, a, b;
    struct M4 *m = &p->mat;
    int j;
    float duration, t0;
    const float *time;
    float *len;
    if (i == p->segment) return;
    {
        qword v0 = p->v[i], v1 = p->v[i + 1], o0 = p->out[i], i1 = p->in[i + 1];
        qword m1 = m->b, m2 = m->c, m3 = m->d, m0 = p->mat.a;
        qword bv, ev, sv, av;
        p->lengths[0] = 0;
        time = p->times + i;
        t0 = time[0];
        bv = Dir(m0, m1, m2, i1);
        b.q = bv;
        ev = Point(m0, m1, m2, m3, v1);
        sv = Point(m0, m1, m2, m3, v0);
        av = Dir(m0, m1, m2, o0);
        end.q = ev;
        start.q = sv;
        a.q = av;
    }
    duration = time[1] - t0;
    len = p->lengths;
    for (j = 0; j < 11; j++, len++) {
        float frac = (float)j * 0.1f;
        func_00117120(duration, frac * duration, 1.0f, start.q, a.q, end.q, b.q, &cur.q, 0, 0);
        if (j > 0) *len = len[-1] + Len(Sub(prev.q, cur.q));
        prev.q = cur.q;
    }
    p->segment = i;
}
