// fresh3 (Claude agent, laneB4, 2026-10-23): aligned 6 -> 2. VU_FLOATM ctor as asm("lw %0, %1" : "=r"(q) : "m"(f)) gives the target's lw v1 / sq 0x20 / lq v0 spill sequence. "=&j" on vmulx gives 2 (g reload vf3, target vf1); without & it is 3 (vel/g vf1/vf2 swapped).
// fresh2 (Claude agent, 2026-10-23): aligned 10 -> 6. g is a register pseudo that the target SPILLS (slot 0x20 = spill slot, allocated last): implicit VU_FLOATM copy ctor + an allocation-only duplicate "j"(f.q) operand on the vmulx asm (VF class, all call-clobbered -> spilled across GetVel); v is a block-scoped union so it reuses the param-copy slot 0x0; ctor input is the float itself ("0"(f)). Left: ours lwc1+mfc1 (target lw v1 into the output reg, then the copy reloads lq from the spill slot), and vel/g VF numbers swapped (vf1/vf2).
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); }
};
struct VU_VECTOR {
    qword q;
    VU_VECTOR(const qword &v) { q = v; }
};
struct VU_FLOATM {
    qword q;
    VU_FLOATM(const float &f) { __asm__("lw %0, %1" : "=r"(q) : "m"(f)); }
};
static inline qword operator*(VU_VECTOR v, VU_FLOATM f)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=&j"(r) : "j"(v.q), "j"(f.q), "j"(f.q));
    return r;
}
static inline qword operator*(VU_VECTOR v, VU_FLOAT f)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v.q), "j"(f.q));
    return r;
}
struct MATRIX3 { qword r[3]; };
static inline qword operator*(const MATRIX3 &m, VU_VECTOR v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
        : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(v.q));
    return r;
}

#define V4(a) virtual void a##0(); virtual void a##1(); virtual void a##2(); virtual void a##3();
struct BASE { int x0, x4, x8; };
struct P : BASE {
    V4(a) V4(b) V4(c) V4(d) V4(e) V4(f) V4(g) V4(h)
    virtual qword GetVel();            /* 33 */
    virtual void v34();
    virtual void SetVel(qword v);      /* 35 */
};
struct PX {
    char pad[0x190];
    qword v190;
    char pad1A0[0x10];
    MATRIX3 m1B0;
    char pad1E0[0x1030 - 0x1E0];
    int a1030;
    int a1034[(0x10DC - 0x1034) / 4];
    int x10DC;
};
struct Q {
    virtual void v1();
    virtual void v2();
    virtual void Eval(int n, qword *pv, float g0, float g1);
};
struct R { int x0; Q *pq; };
struct X { char pad[0x78]; float g78; };
struct S { P *p; int k; float t; int kCur; X *px0; X *px1; };
struct CLOCK { float t; float dt; };
extern "C" {
extern CLOCK D_002DDED0;
extern float D_002BC9B8;
void func_002046F0(P *p, int n);
R *func_0012FF10(X *px, P *p, int a, int b);
void func_001F15B8(void *pv);
void func_001305B8(X *px, P *p, int n, void *pv, float g0, float g1);
}
#define PXOF(p) ((PX *)(p))

extern "C" void func_001375D0(S *s, int k)
{
    X *px;
    if (k == s->k)
        return;
    s->k = k;
    px = 0;
    s->t = D_002DDED0.t;
    if (k == -1) {
        VU_FLOATM g(D_002BC9B8);
        qword vel = s->p->GetVel();
        qword r = VU_VECTOR(vel) * g;
        s->p->SetVel(r);
        return;
    }
    if (k >= -1) if (k < 2) {
        union { qword q; } v;
        if (k == 0)
            px = s->px0;
        else
            px = s->px1;
        func_002046F0(s->p, PXOF(s->p)->x10DC);
        func_0012FF10(px, s->p, 1, 1)->pq->Eval(0, &v.q, 0.0f, px->g78);
        s->p->SetVel(PXOF(s->p)->m1B0 * VU_VECTOR(v.q));
        PXOF(s->p)->v190 = VU_VECTOR(v.q) * VU_FLOAT(-1.0f);
        s->kCur = k;
    }
    func_001F15B8(PXOF(s->p)->a1034);
    func_001305B8(px, s->p, 1, &PXOF(s->p)->a1030, 0.0f, 1.0f);
}
