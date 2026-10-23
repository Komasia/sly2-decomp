/* fresh1 (Claude agent, 2026-10-23): aligned 30 (was 40). Non-volatile qmfc2, split vsqrt asm, gZ qmfc2+pextuw in one asm with an unused t operand, vsub operands (b,a). Left: VF numbering in vsub/dot blocks, D_002BD2A0/D_002BBB60 load scheduling before div. Old note: ~40 diffs: structure right; VF register numbering, prologue scheduling (daddu s4,t0 in jal delay), dot/div block scheduling */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct Q3 { float a, b, c; };
struct O { char pad[0x18]; float g18; float g1C; };
struct P { char pad[0x150]; struct O *p150; };
struct S { struct P *p; };
extern struct Q3 D_002BD280, D_002BD290, D_002BD2A0, D_002BD2B0;
extern float D_002BBB60[2];
qword func_001A62E8(void *p);
qword func_0011E1A0(float a, float b, float c);
static __inline__ float GQuad(float g, struct Q3 *pq)
{
    return pq->a + g * (pq->b + g * pq->c);
}
static __inline__ float GClamp(float g, float lo, float hi)
{
    float r;
    if (g < lo) r = lo;
    else if (hi < g) r = hi;
    else r = g;
    return r;
}
static __inline__ qword ToGpr(qword v)
{
    qword r;
    __asm__("qmfc2.ni %0, %1" : "=r"(r) : "j"(v));
    return r;
}
static __inline__ float GetZ(qword v)
{
    qword t = ToGpr(v);
    float g;
    __asm__("pextuw %0, $0, %1" : "=r"(g) : "r"(t));
    return g;
}
static __inline__ qword VSub(qword a, qword b)
{
    qword d;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    return d;
}
void func_001428D8(struct P *p, void *po, struct S *ps, float *pgXY, float *pgZ)
{
    U a;
    U d;
    qword t;
    float gXY, gZ, dXY, dZ;
    qword b;
    a.q = func_001A62E8(p);
    dXY = dZ = 0.0f;
    b = func_001A62E8(po);
    {
        qword tt;
        __asm__("vsub.xyzw %1, %3, %2\n\tsqc2 %1, %0" : "=m"(d.q), "=j"(tt) : "j"(b), "j"(a.q));
    }
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(t) : "j"(d.q));
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(t) : "j"(t));
    __asm__("qmfc2.ni %0, %1\n\tpextuw %0, $0, %0" : "=r"(gZ) : "j"(d.q), "j"(t)); /* unused "j"(t): allocation/order-only operand */
    __asm__("qmfc2.ni %0, %1" : "=r"(gXY) : "j"(t));
    if (ps->p == p) {
        dXY = GQuad(gXY, &D_002BD280);
        dZ = GQuad(gZ, &D_002BD290);
    }
    if (p->p150 && 1e-4f < gXY) {
        qword v, l, one, m;
        float c, s;
        v = func_0011E1A0(p->p150->g18, p->p150->g1C, 0.0f);
        __asm__("vmul.xyz %0, %1, %2" : "=j"(m) : "j"(v), "j"(d.q));
        __asm__("vaddw.x %0, $vf0, $vf0w" : "=j"(one));
        __asm__("vadday.x ACC, %1, %1y\n\tvmaddz.x %0, %2, %1z" : "=j"(l) : "j"(m), "j"(one));
        __asm__("qmfc2.ni %0, %1" : "=r"(c) : "j"(l));
        __asm__ __volatile__("nop");
        c = c / gXY;
        s = GClamp(GQuad(c, &D_002BD2A0), D_002BBB60[0], D_002BBB60[1]);
        dXY += s * GQuad(gXY, &D_002BD2B0);
    }
    gXY += dXY;
    gZ += dZ;
    if (pgXY)
        *pgXY = gXY;
    if (pgZ)
        *pgZ = gZ;
}
