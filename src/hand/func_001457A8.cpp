// PlanFollow MATCH (Claude agent for Lilly, T1647, 2026-10-25), from v6 (14).
// Branch 1: VU_FLOAT has a user copy ctor (so the temporary lives at 0x40) and its qmtc2 ctor writes a plain qword
// local first, then copies it into q (an asm output straight into the member goes through a second stack temp).
// Branch 2: the VU_FLOAT is loaded with an asm lw from "m"(f) (VU_FLOATM, as in SetSlyDodgeState), and AddScaled takes
// its operands in (a, s, b) order.
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct M4 { qword r[4]; };
struct E;
struct D { char pad[0x10]; E *pe; };
struct C { char pad[0xDC]; D *pd; };
struct B { char pad[0xE8]; int k; char pad2[0xF4 - 0xEC]; qword *pq; };
struct A { char pad[0xE8]; C *pc; char pad2[0x294 - 0xEC]; B *pb; };
struct O;
struct VT { char pad[0x108]; short d; short pad2; qword (*pfn)(O *); };
struct O { char pad[0xC]; VT *pvt; char pad2[0x190 - 0x10]; qword q190; char pad3[0x1A8 - 0x1A0]; float g1A8; };
struct P {
    char pad[0x10]; A *pa; char pad1[4]; void *p18; char pad2[0x30 - 0x1C]; O *po; char pad3[0x40 - 0x34];
    qword q40; qword q50; char pad4[0x68 - 0x60]; float g68;
};
extern "C" {
extern qword g_normalZ;
qword PosOfLo(void *p) asm("PosOfLo__FP2LO");
M3 *MatJtLo(void *p) asm("MatJtLo__FP2LO");
M3 BuildRotateMatrixAxis(qword axis, float g) asm("BuildRotateMatrixAxis__FP7MATRIX3fG9VU_VECTOR");
int FIsBasicDerivedFrom(void *p, int k) asm("FIsBasicDerivedFrom__FP5BASIC3CID");
E *func_00145AA8(P *p);
int FNavPathCrv(E *pe, qword r, qword v, B *pb) asm("FNavPathCrv__FP9NAVREGIONiiP3CRV");
void RecalcCrv(B *pb) asm("RecalcCrv__FP3CRV");
void Follow(void *p, B *pb, int n) asm("Follow__9JOBFOLLOWP3CRVi");
void PlanFollow(P *p) asm("PlanFollow__12JOBCOMPANION");
}
struct VU_FLOAT { qword q; VU_FLOAT(const VU_FLOAT &s) { q = s.q; } VU_FLOAT(float f) { qword t; __asm__("qmtc2.ni %1, %0" : "=j"(t) : "r"(f)); q = t; } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
struct VU_FLOATM { qword q; VU_FLOATM(const float &f) { __asm__("lw %0, %1" : "=r"(q) : "m"(f)); } };

static inline qword AddScaled(VU_VECTOR a, VU_FLOATM s, VU_VECTOR b)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %3, %2x" : "=j"(r) : "j"(a.q), "j"(s.q), "j"(b.q), "j"(s.q)); /* repeated "j"(s.q): allocation-only operand, keeps the lw value VF-class so it is spilled to 0x80 across the call */
    return r;
}

static inline qword AddScaled(VU_VECTOR a, VU_FLOAT s, VU_VECTOR b)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %3, %2x" : "=j"(r) : "j"(a.q), "j"(s.q), "j"(b.q));
    return r;
}

static inline qword MulM3(const M3 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(r) : "j"(v), "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    return r;
}

static inline qword Add(qword a, qword b)
{
    qword r;
    __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}

// name: SafeHouse port (JOBCOMPANION::PlanFollow)
void PlanFollow(P *p)
{
    union { M4 m4; struct { M3 m; qword pos; } s; } u;
    p->q50 = PosOfLo(p->po);
    if (FIsBasicDerivedFrom(p->po, 0x33)) {
        O *po = p->po;
        u.s.m = BuildRotateMatrixAxis(g_normalZ, po->g1A8);
        u.s.pos = AddScaled(p->q50, VU_FLOAT(-p->g68), MulM3(u.s.m, po->q190));
    } else {
        O *po;
        u.s.m = *MatJtLo(p->po);
        po = p->po;
        u.s.pos = AddScaled(p->q50, VU_FLOATM(p->g68), po->pvt->pfn((O *)((char *)po + po->pvt->d)));
    }
    u.s.pos = Add(u.s.pos, MulM3(u.s.m, p->q40));
    {
        A *pa = p->pa;
        B *pb = pa->pb;
        D *pd = pa->pc ? pa->pc->pd : 0;
        E *pe = pd ? pd->pe : 0;
        qword r = PosOfLo(pa);
        if (!pe) {
            pb->k = 2;
            pb->pq[0] = r;
            pb->pq[1] = u.s.pos;
            RecalcCrv(pb);
        } else if (func_00145AA8(p) != pe) {
            FNavPathCrv(pe, r, r, pb);
        } else if (!FNavPathCrv(pe, r, u.s.pos, pb)) {
            FNavPathCrv(pe, r, r, pb);
        }
        Follow(p->p18, pb, 0);
    }
}
