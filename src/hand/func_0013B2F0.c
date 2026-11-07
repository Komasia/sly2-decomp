typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct M { int x0; char pad[0x2C]; qword v30; char pad2[4]; int x44; };
struct P { char pad[0x150]; int x150; };
extern qword g_normalZ;
int FAbsorbSoWkr__FP2SOP3WKR(struct P *p, struct M *pm);
qword PosOfLo__FP2LO(void *p);
void RecordHit__FP3ALOG9VU_VECTORT1(struct P *p, qword pos, qword n);
int FIsBasicDerivedFrom__FP5BASIC3CID(int n, int k);
void ExpireIn__FP3ALOf(struct P *p, float g);
static __inline__ qword VLen(qword c)
{
    qword l, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(l), "=&j"(one) : "j"(c));
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(l) : "j"(l));
    return l;
}
// name: SafeHouse port (FAcceptContactProjectile)
int FAcceptContactProjectile__FP3ALOP5CTMSG(struct P *p, struct M *pm)
{
    int r;
    if (p->x150 == 1)
        return 0;
    r = FAbsorbSoWkr__FP2SOP3WKR(p, pm);
    if (r && (pm->x44 & 8)) {
        VU u;
        VU *pu;
        register qword n __asm__("vf1");
        qword k;
        qword c = pm->v30;
        qword l;
        float gl;
        __asm__("" : "=r"(k) : "0"(g_normalZ));
        l = VLen(c);
        __asm__("qmfc2.ni %0, %1" : "=r"(gl) : "j"(l));
        pu = &u;
        if (gl < 1e-4f) {
            n = k;
        } else {
            qword rn;
            __asm__("vdiv Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, Q" : "=j"(rn) : "j"(c), "j"(l));
            n = rn;
        }
        pu->q = n;
        RecordHit__FP3ALOG9VU_VECTORT1(p, PosOfLo__FP2LO(p), u.q);
        if (FIsBasicDerivedFrom__FP5BASIC3CID(pm->x0, 0x4F))
            ExpireIn__FP3ALOf(p, 0.25f);
        else
            ExpireIn__FP3ALOf(p, 0.0f);
    }
    return r;
}
