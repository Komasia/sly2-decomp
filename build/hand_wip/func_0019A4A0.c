typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q)); return z; }
struct C { char pad[0x88]; float g88; };
struct B { char pad[0xE8]; struct C *pc; };
struct S { struct B *pb; };
typedef struct { short d; short pad; void *(*pfn)(void *, int); } VTE;
struct O { char pad[0xC]; VTE *vt; };
qword func_001A62E8(void *p);
qword func_0022D348(void *p, int n, qword q);
int func_0019A400(struct S *p, qword a, qword b, qword c, qword d, float *pg);
void func_00117120(float tMax, float t, float s, qword a, qword va, qword b, qword vb, qword *pp, qword *pv, qword *pa);
static __inline__ float LenXY(qword v)
{
    float r;
    __asm__("vmul.xy %0, %0, %0\n\tvaddy.x %0, %0, %0y" : "+j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(v));
    __asm__("qmfc2.ni %0, %1" : "=r"(r) : "j"(v));
    return r;
}
static inline float GMax(float a, float b) { return a > b ? a : b; }
void func_0019A4A0(struct S *p, qword a, struct O *o, qword b, qword c, float *pt, float *pg, qword *pv, qword *pw)
{
    U u0, v10, v20, s;
    float at[2];
    qword q;
    U uq;
    qword r;
    qword pos = func_001A62E8(p->pb);
    void *x = o->vt[32].pfn((char *)o + o->vt[32].d, 0);
    q = func_0022D348(x, 0, b);
    uq.q = q;
    if (!func_0019A400(p, pos, a, b, q, at)) {
        float dz = GetZ(a) - GetZ(q);
        float g = p->pb->pc->g88;
        float t1 = -dz / g;
        float h;
        t1 = GMax(t1, 0.0f);
        { float th = t1 * 0.5f; h = GetZ(pos) - GetZ(b) + (g * th * t1 + dz * t1); }
        if (pt) *pt = t1;
        if (pg) *pg = 1010000.0f - h;
        return;
    }
    {
        float tt = 0.15f < at[0] ? 0.15f : at[0];
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(uq.q), "j"(c));
        __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(tt));
        __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(u0.q) : "j"(b), "j"(uq.q), "j"(s.q));
    }
    if (pt) *pt = at[0];
    if (pg) {
        float d1, d2;
        func_00117120(at[0], 0.0f, 1.0f, pos, a, u0.q, r, 0, 0, &v10.q);
        d1 = LenXY(v10.q);
        func_00117120(at[0], at[0], 1.0f, pos, a, u0.q, r, 0, 0, &v20.q);
        d2 = LenXY(v20.q);
        d1 = (d1 + d2) * (at[0] * 0.5f);
        *pg = d1 < 1000000.0f ? d1 : 1000000.0f;
    }
    if (pv) *pv = u0.q;
    if (pw) *pw = r;
}
