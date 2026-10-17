// (Claude agent, big12) fresh4: clean rewrite of the curtain/BSP height query.
typedef int qword __attribute__((mode(TI)));
typedef unsigned short ushort;
struct V { float x, y, z, w; };
union UQ { qword q; float f[4]; };
struct EDGE { ushort ivA, ivB, pad4, iface; EDGE *next; };
struct FACE { qword eq; EDGE *pedge; int x14; int grf; int x1C; };
struct NODE { NODE *a, *b; FACE *face; };
struct O {
    char pad0[0x68]; int x68, x6C, cnode; NODE *anode;
    char pad78[0x1C]; qword *avert; int x98; FACE *aface;
    char padA0[0xC8]; O *psrc; char pad16C[0xC]; int frame, fHit; float dz;
};
struct CAM { char pad[0x90]; qword pos; char padA0[0x404]; int frame; };
struct REQ { int cb, align; };
struct FRAME { int x[4]; };
struct WORLD;
extern CAM D_002DDF40;
union FI { float f; int i; };
extern FI D_002C4490;
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
{ qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(i)); return r; }
static inline qword AddUp(qword base, qword up, qword k)
{ qword r; __asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(base), "j"(up), "j"(k)); return r; }
static inline qword Sub(qword a, qword b)
{ qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
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
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(d) : "0"(d));
    __asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q" : "=j"(r) : "j"(d), "j"(v));
    return r;
}
static inline float LenXY(qword v)
{
    qword d, l;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(l) : "j"(d));
    return F(l);
}
static inline float ZOf(qword v)
{ float z; __asm__("pextuw %0,$zero,%1" : "=r"(z) : "r"(v)); return z; }
static inline float PlaneDist(UQ &r, UQ &one, qword plane, qword pos)
{
    qword g, o;
    func_002564B8(&r);
    func_002564B8(&one);
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddaz.x ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w"
            : "=j"(g), "=&j"(o) : "j"(plane), "j"(pos));
    r.q = g;
    one.q = o;
    return F(g);
}

extern "C" void func_0022A220(O *po)
{
    UQ corner[4];
    UQ side[4];
    UQ tmp;
    FRAME frame;
    UQ nrm;
    int cpso;
    O **apso;
    int cface;
    FACE **ppface;

    CAM *pcam = &D_002DDF40;
    if (po->frame == pcam->frame)
        return;
    po->frame = pcam->frame;
    qword posCam = pcam->pos;
    O *psrc = po->psrc;
    if (!psrc)
        psrc = po;
    qword posSrc = func_001A62E8(psrc);
    po->fHit = 0;
    po->dz = 0.0f;

    qword k = QI(D_002C4490.i);
    tmp.q = k;
    qword up = D_002A2DC0;
    corner[2].q = AddUp(posCam, up, k);
    corner[1].q = AddUp(posSrc, up, k);
    corner[0].q = posSrc;
    corner[3].q = posCam;
    func_00119308(&tmp, posCam, posSrc, corner[1].q);
    qword plane = tmp.q;
    qword posA, posB;

    int *pcpso = &cpso;
    O ***papso = &apso;
    int i;
    for (i = 0; i < 4; i++) {
        qword edge = Sub(corner[(i + 1) % 4].q, corner[i].q);
        func_002564C0(&nrm);
        nrm.q = plane;
        func_00119390(&side[i], Normalize(Cross(edge, plane)), corner[i].q);
    }

    func_001AE478(&frame);
    REQ *preq = (REQ *)&tmp;
    preq->cb = 0x10000;
    preq->align = 16;
    FACE **apface = (FACE **)func_001AE318(preq);

    k = QI(D_002C4490.i);
    tmp.q = k;
    func_0020FAA0(&D_003DD490, Min(posCam, posSrc), AddUp(Max(posCam, posSrc), D_002A2DC0, k),
                  func_0014F030, 0, pcpso, papso);

    qword dpos = Sub(posSrc, posCam);
    float sMax = ZOf(dpos) / LenXY(dpos);
    float sBase = sMax;

    for (int ipso = 0; ipso < cpso; ipso++) {
        O *pso = apso[ipso];
        cface = 0x4000;
        ppface = apface;
        int res = func_00118D08(pso->anode, pso->anode + pso->cnode, 4, corner, &cface, &ppface);
        if (res == 1)
            continue;
        if (res == 0) {
            func_001AE4A0(&frame, 2);
            return;
        }
        int c = ppface - apface;
        UQ d[6][2];
        for (int j = 0; j < c; j++) {
            for (EDGE *pe = apface[j]->pedge; pe; pe = pe->next) {
                if (!(pso->aface[pe->iface].grf & 0x4000))
                    continue;
                posA = pso->avert[pe->ivA];
                posB = pso->avert[pe->ivB];
                float gA = PlaneDist(d[0][0], d[0][1], plane, posA);
                float gB = PlaneDist(d[1][0], d[1][1], plane, posB);
                if (0.0f < gA && 0.0f < gB)
                    continue;
                if (gA < 0.0f && gB < 0.0f)
                    continue;
                float u = gA / (gA - gB);
                qword qa = Q(1.0f - u), qb = Q(u);
                tmp.q = qa;
                tmp.q = qb;
                qword posX;
                __asm__("vmulax.xyzw ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x" : "=j"(posX) : "j"(posA), "j"(posB), "j"(qa), "j"(qb));
                int fIn = 0;
                if (PlaneDist(d[2][0], d[2][1], side[0].q, posX) < 0.0f &&
                    PlaneDist(d[3][0], d[3][1], side[1].q, posX) < 0.0f &&
                    PlaneDist(d[4][0], d[4][1], side[2].q, posX) < 0.0f &&
                    PlaneDist(d[5][0], d[5][1], side[3].q, posX) < 0.0f)
                    fIn = 1;
                if (fIn) {
                    qword dx = Sub(posX, posCam);
                    float s = ZOf(dx) / LenXY(dx);
                    if (sMax < s)
                        sMax = s;
                }
            }
        }
        for (int k = 0; k < c; k++)
            apface[k]->grf &= ~0x4000;
    }
    po->fHit = 1;
    po->dz = (sMax - sBase) * LenXY(Sub(posCam, posSrc));
    func_001AE4A0(&frame, 2);
}
