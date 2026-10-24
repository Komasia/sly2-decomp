// (Lilly agent, T1635) WIP: 18/441 words differ (aligned 14; lilly41 was 28/21). Not a match. See notes/220000.md "T1635".
// New vs lilly41: LenXY now ends in FQ (compiler qmfc2 + asm mtc1) for the in-loop and tail uses (LenXYF keeps F for the first use);
// prologue statement order tmp.q=k first. Left: sqc2 order c2/k (2 words), cpso/len v0<->a0 swap (4), vertex block regs (11), gB mtc1/sqc2 swap (2).
// (Lilly agent, T1627) WIP: aligned 21 / 441 insns (exact count; 28 words differ). Not a match. See notes/220000.md "T1627".
// New vs lilly36 (57): j-loop head via empty-asm dependency (jx), pointer local pc for corner[], clean loop indexed by j,
// Normalize asm2+asm3 fused (fixes the loop-1 s1/s2 swap), ZOf fused qmfc2+pextuw in the first use only.
// (Lilly agent, T1626, = lilly35 unchanged; ~35 more variants gave no gain, see notes/220000.md "T1626") (T1611) WIP: aligned 57 / 443 insns (target 441). Not a match. See notes/220000.md "T1611".
// vs lilly33 (63): the ONE register pin below (rr in a2) reproduces the target prologue exactly (por a2,zero,v0 / sq a2,0x190 / qmtc2 a2,vf5)
// without the empty asm. Remaining: prologue sqc2 store order (3 lines), loop-1 s1/s2 swap, j-loop head (j in a0 in the target),
// the edge-flag beqz delay slot (addiu a0), and the vertex address regs (target ivA=a2, ivB=a1, base=v1, loads into v0/v1).
typedef int qword __attribute__((mode(TI)));
typedef unsigned short ushort;
struct V { float x, y, z, w; };
union UQ { qword q; float f[4]; };
struct EDGE { ushort ivA, ivB, pad4, iface; EDGE *next; };
struct FACE { qword eq; EDGE *pedge; int x14; int grf; int x1C; };
struct NODE { NODE *a, *b; FACE *face; };
struct TREE { int x0, x4, cnode; NODE *anode; };
struct O {
    char pad0[0x68]; TREE tree;
    char pad78[0x1C]; qword *avert; int x98; FACE *aface;
    char padA0[0xC8]; O *psrc; char pad16C[0xC]; int frame, fHit; float dz;
};
struct CAM { char pad[0x90]; qword pos; char padA0[0x404]; int frame; };
struct P4 { qword q; };
struct REQ { int cb, align; };
struct FRAME { int x[4]; };
struct WORLD;
extern CAM D_002DDF40;
extern int D_002C4490;
extern qword D_002A2DC0;
extern WORLD D_003DD490;
extern "C" {
qword func_001A62E8(O *);
void func_00119308(UQ *, qword, qword, qword);
void func_00119390(UQ *, qword, qword);
UQ *func_002564C0(UQ *);
UQ *func_002564B8(UQ *);
FRAME *func_001AE478(FRAME *);
void func_001AE4A0(FRAME *, int);
void *func_001AE318(REQ *);
int func_0014F030(void *, O *);
void func_0020FAA0(WORLD *, qword, qword, int (*)(void *, O *), void *, int *, O ***);
int func_00118D08(NODE *, NODE *, int, UQ *, int *, FACE ***);
}
static inline float F(qword q)
{ int i; float f; __asm__("qmfc2.ni %0,%1" : "=r"(i) : "j"(q)); __asm__("mtc1 %1,%0" : "=f"(f) : "r"(i)); return f; }
static inline qword Q(float f)
{ qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(f)); return r; }
static inline qword QI(int i)
{ qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "rV"(i)); return r; }
static inline qword AddUp(qword base, qword up, qword k)
{ qword r; __asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(base), "j"(up), "j"(k)); return r; }
static inline qword Sub(qword a, qword b)
{ qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword SubV(qword a, qword b)
{ qword r; __asm__ volatile("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Max(qword a, qword b)
{ qword r; __asm__("vmax.xyz %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Min(qword a, qword b)
{ qword r; __asm__("vmini.xyz %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Cross(qword a, qword b)
{ qword r; __asm__("vopmula.xyz ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Normalize(qword v)
{
    qword d, one, r;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %1,$vf0,Q\n\tvdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q" : "=&j"(r), "+j"(d) : "j"(v));
    return r;
}
static inline float ZOf(qword v)
{ int t; float z; __asm__("qmfc2.ni %0,%1\n\tpextuw %0,$zero,%0" : "=r"(t) : "j"(v)); __asm__("mtc1 %1,%0" : "=f"(z) : "r"(t)); return z; }
static inline float ZOfP(qword v)
{ float z; __asm__("pextuw %0,$zero,%1" : "=r"(z) : "r"(v)); return z; }
static inline float FQ(qword q)
{ float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static inline float FG(qword q)
{ float f; __asm__("qmfc2.ni %0,%1" : "=r"(f) : "j"(q)); return f; }
static inline float FO(qword q)
{ int i; float f; __asm__("qmfc2.ni %1,%2\n\tmtc1 %1,%0" : "=f"(f), "=&r"(i) : "j"(q)); return f; }
static inline float FX(qword q)
{ int i; float f; __asm__("qmfc2.ni %0,%1" : "=r"(i) : "j"(q)); __asm__("mtc1 %1,%0" : "=f"(f) : "r"(i)); return f; }
static inline float LenXY(qword v)
{
    qword d, l;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(l) : "j"(d));
    return FQ(l);
}
static inline float LenXYF(qword v)
{
    qword d, l;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(l) : "j"(d));
    return F(l);
}
static inline float PlaneDistA(UQ &r, UQ &one, qword plane, qword pos)
{
    qword g, o;
    func_002564B8(&r);
    func_002564B8(&one);
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddaz.x ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w"
            : "=j"(g), "=j"(o) : "j"(plane), "j"(pos));
    float f = FG(g);
    one.q = o;
    r.q = g;
    return f;
}

static inline float PlaneDistB(UQ &r, UQ &one, qword plane, qword pos)
{
    qword g, o;
    func_002564B8(&r);
    func_002564B8(&one);
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddaz.x ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w"
            : "=j"(g), "=j"(o) : "j"(plane), "j"(pos));
    float f = FQ(g);
    __asm__("" : "+j"(g), "+j"(o));
    one.q = o;
    r.q = g;
    return f;
}

static inline float PlaneDistS(UQ &r, UQ &one, qword plane, qword pos)
{
    qword g, o;
    func_002564B8(&r);
    func_002564B8(&one);
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddaz.x ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w"
            : "=j"(g), "=j"(o) : "j"(plane), "j"(pos));
    float f = FQ(g);
    one.q = o;
    r.q = g;
    return f;
}


static inline float ZOfN(qword v, int n)
{ qword t; float z; __asm__("qmfc2.ni %0,%1\n\tpextuw %0,$zero,%0" : "=r"(t) : "j"(v));
  __asm__("mtc1 %1,%0" : "=f"(z) : "r"(t)); return z; }
static inline float LenXYFN(qword v, int n)
{
    qword d, l;
    int i; float f;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(l) : "j"(d));
    __asm__("qmfc2.ni %0,%1" : "=r"(i) : "j"(l));
    __asm__("mtc1 %1,%0" : "=f"(f) : "r"(i), "r"(n), "r"(n), "r"(n), "r"(n), "r"(n), "r"(n));
    return f;
}

extern "C" void func_0022A220(O *po)
{
    UQ corner[4];
    UQ side[4];
    UQ tmp;
    FRAME frame;
    UQ nrm;
    struct { int cpso; O **apso; int cface; FACE **ppface; } L;
#define cpso L.cpso
#define apso L.apso
#define cface L.cface
#define ppface L.ppface

    CAM *pcam = &D_002DDF40;
    if (po->frame == pcam->frame)
        return;
    po->frame = pcam->frame;
    qword posCam = pcam->pos;
    O *psrc = po->psrc;
    register qword rr asm("$6");   // pin: PosLoWorld result lives in a2 (3rd arg of func_00119308); later uses reload from the 0x190 slot
    if (psrc)
        rr = func_001A62E8(psrc);
    else
        rr = func_001A62E8(po);
    qword posSrc = rr;
    po->fHit = 0;
    po->dz = 0.0f;

    qword up = D_002A2DC0;
    qword k = QI(D_002C4490);
    corner[2].q = AddUp(posCam, up, k);
    corner[3].q = posCam;
    corner[1].q = AddUp(posSrc, up, k);
    tmp.q = k;
    corner[0].q = posSrc;
    func_00119308(&tmp, posCam, posSrc, corner[1].q);
    qword plane = tmp.q;
    P4 pvA, pvB;

    int i;
    FACE **apface;
    int ipso;
    int c;
    int j;
    EDGE *pe;
    for (i = 0; i < 4; i++) {
        UQ *pc = corner;
        qword edge = Sub(pc[(i + 1) % 4].q, pc[i].q);
        func_002564C0(&nrm);
        nrm.q = plane;
        func_00119390(&side[i], Normalize(Cross(edge, plane)), pc[i].q);
    }
    ipso = 0;    func_001AE478(&frame);
    REQ *preq = (REQ *)&tmp;
    preq->cb = 0x10000;
    preq->align = 16;
    apface = (FACE **)func_001AE318(preq);
    qword k2 = QI(D_002C4490);
    tmp.q = k2;
    func_0020FAA0(&D_003DD490, Min(posCam, posSrc), AddUp(Max(posCam, posSrc), D_002A2DC0, k2),
                  func_0014F030, 0, &cpso, &apso);
    qword dpos = Sub(posSrc, posCam);
    int nso = cpso;
    float sMax = ZOfN(dpos, nso) / LenXYFN(dpos, nso);
    float sBase = sMax;
    for (; ipso < cpso; ipso++) {
        O *pso = apso[ipso];
        cface = 0x4000;
        ppface = apface;
        TREE *ptree = &pso->tree;
        int res = func_00118D08(ptree->anode, ptree->anode + ptree->cnode, 4, corner, &cface, &ppface);
        switch (res) { case 0: func_001AE4A0(&frame, 2); return; case 1: continue; case 2: break; }
        c = ppface - apface;
        UQ d[6][2];
        for (j = 0; j < c; ) {
            pe = apface[j]->pedge;
            int jx = j;
            __asm__("" : "+r"(jx) : "r"(pe));
            int jn = jx + 1;
            for (; pe; pe = pe->next) {
                FACE *pfa = &pso->aface[pe->iface];
                if (!(pfa->grf & 0x4000))
                    continue;
                int ia = pe->ivA;
                int ib = pe->ivB;
                P4 *av = (P4 *)pso->avert;
                P4 *pa = (P4 *)(((int)ia << 4) + (int)av);
                P4 *pb = (P4 *)(((int)ib << 4) + (int)av);
                P4 ta = *pa;
                P4 tb = *pb;
                pvA = ta;
                pvB = tb;
                float gA = PlaneDistA(d[0][0], d[0][1], plane, pvA.q);
                float gB = PlaneDistB(d[1][0], d[1][1], plane, pvB.q);
                if (0.0f < gA && 0.0f < gB)
                    continue;
                if (gA < 0.0f && gB < 0.0f)
                    continue;
                float u = gA / (gA - gB);
                qword qa = Q(1.0f - u);
                tmp.q = qa;
                qword qb = Q(u);
                tmp.q = qb;
                qword posX;
                __asm__("vmulax.xyzw ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x" : "=j"(posX) : "j"(pvA.q), "j"(pvB.q), "j"(qa), "j"(qb));
                int fIn = 0;
                if (PlaneDistS(d[2][0], d[2][1], side[0].q, posX) < 0.0f &&
                    PlaneDistS(d[3][0], d[3][1], side[1].q, posX) < 0.0f &&
                    PlaneDistS(d[4][0], d[4][1], side[2].q, posX) < 0.0f &&
                    PlaneDistS(d[5][0], d[5][1], side[3].q, posX) < 0.0f)
                    fIn = 1;
                if (fIn) {
                    qword dx = Sub(posX, posCam);
                    float s = ZOfP(dx) / LenXY(dx);
                    if (sMax < s)
                        sMax = s;
                }
            }
            j = jn;
        }
        for (j = 0; j < c; j++)
            apface[j]->grf &= ~0x4000;
    }
    po->fHit = 1;
    po->dz = (sMax - sBase) * LenXY(Sub(posCam, posSrc));
    func_001AE4A0(&frame, 2);}
