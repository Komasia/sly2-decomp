// v3 (Claude agent, laneC27 2026-10-23): 29 -> 28, no asm tricks in VU_FLOAT. The ctor is plain C (`union { float f; qword q; } u; u.f = f; q = u.q;`), and the alloc-only "j"(s.q) is gone. The VU_FLOAT temp is now built BEFORE the MulM3 like the target (target: mfc1/qmtc2 vf4 then sqc2 vf4,0x40 ahead of the 0x190 load), but the union lives in memory (swc1 0x40) where the target keeps it in a register. In branch 2 the target loads g68 with a plain `lw v1` and does `sq v1,0x80`, which means a TImode register value built from an SI/SF load. A float/int union plus `q = u.i` gives that lw, but with 3 extension copies (39). TI unions (float or int member) always go to the stack. The int-union input on the asm ctor: 31-32.
// v2 (Claude agent, laneC25 2026-10-23): aligned 32 -> 29. One allocation-only repeated "j"(s.q) on the AddScaled asm makes the VU_FLOAT temp a VF-class pseudo (target: vf4 in branch 1, spilled to 0x80 in branch 2, frame 0xE0 now matches), and the ctor ties a float input ("0"(f)) so no daddu copy. Left: branch 1 schedule/VF numbers (target lwc1 g68 first, rows vf6/vf5/vf3, s vf4), branch 2 lwc1+mfc1 for g68 (target lw v1 directly). Param order (b, s, a)/(b, a, s): 42.
// NEAR MISS (Claude agent): 56/133. Logic complete. Branch 2 VU_FLOAT(g68) lives in s0 (target spills to 0x80, frame 0xE0); branch 1 VU_FLOAT goes mfc1->GPR moves (target mfc1->qmtc2 vf4).
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
extern qword D_002A2DC0;
qword func_001A62E8(void *p);
M3 *func_001A6318(void *p);
M3 func_0011B500(qword axis, float g);
int func_00132B10(void *p, int k);
E *func_00145AA8(P *p);
int func_001C02D0(E *pe, qword r, qword v, B *pb);
void func_001E6180(B *pb);
void func_00178D90(void *p, B *pb, int n);
void func_001457A8(P *p);
}
struct VU_FLOAT { qword q; VU_FLOAT(const VU_FLOAT &s) { q = s.q; } VU_FLOAT(float f) { union { float f; qword q; } u; u.f = f; q = u.q; } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };

static inline qword AddScaled(VU_VECTOR a, VU_FLOAT s, VU_VECTOR b)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a.q), "j"(b.q), "j"(s.q)); /* repeated "j"(s.q): allocation-only operand (Claude agent), makes the VU_FLOAT temp prefer a VF reg (spilled to 0x80 in branch 2, frame 0xE0) */
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

void func_001457A8(P *p)
{
    union { M4 m4; struct { M3 m; qword pos; } s; } u;
    p->q50 = func_001A62E8(p->po);
    if (func_00132B10(p->po, 0x33)) {
        O *po = p->po;
        u.s.m = func_0011B500(D_002A2DC0, po->g1A8);
        u.s.pos = AddScaled(p->q50, VU_FLOAT(-p->g68), MulM3(u.s.m, po->q190));
    } else {
        O *po;
        u.s.m = *func_001A6318(p->po);
        po = p->po;
        u.s.pos = AddScaled(p->q50, VU_FLOAT(p->g68), po->pvt->pfn((O *)((char *)po + po->pvt->d)));
    }
    u.s.pos = Add(u.s.pos, MulM3(u.s.m, p->q40));
    {
        A *pa = p->pa;
        B *pb = pa->pb;
        D *pd = pa->pc ? pa->pc->pd : 0;
        E *pe = pd ? pd->pe : 0;
        qword r = func_001A62E8(pa);
        if (!pe) {
            pb->k = 2;
            pb->pq[0] = r;
            pb->pq[1] = u.s.pos;
            func_001E6180(pb);
        } else if (func_00145AA8(p) != pe) {
            func_001C02D0(pe, r, r, pb);
        } else if (!func_001C02D0(pe, r, u.s.pos, pb)) {
            func_001C02D0(pe, r, r, pb);
        }
        func_00178D90(p->p18, pb, 0);
    }
}
