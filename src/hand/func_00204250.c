/* OnStepXpNew (0x204250): STEP vt slot 55: prepare a new contact: reset its friction/response and set the limits for kind 14; for the
   side-facing kinds add a horizontal response contact (kind 10) through PxpAddSw__FP3SOET0P6VECTORG9VU_VECTORT3iiiPvf. */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct ENDPOINT { void *shape, *owner, *object, *lo; qword pos; qword local; int pad[4]; };
struct XP { struct ENDPOINT ae[2]; U normal; float distance, friction, response; int xpk; float lower, upper; int tag; struct XP *next; };
struct SOPHYS { char pad[0xD0]; float mass; };
struct STEP { char padE8[0xE8]; struct SOPHYS *psophys; char padEC[0x258 - 0xEC]; void *psoeCustom; };
extern char g_sw[];
extern qword D_002A2DA0;
extern float D_002C3C60[], D_002C3C90;   /* the sign of each contact side; the floor friction */
void func_001F4FB0(void);   /* the base new-contact handler (nothing) */
void PxpAddSw__FP3SOET0P6VECTORG9VU_VECTORT3iiiPvf(void *pw, void *a, void *b, qword pos, qword dir, int k, int pxp, int y, struct XP **out, float g);

/* The endpoint positions are passed by address (like C++ const VECTOR & operands): the address
   then comes out as offset + x, and the second read of the other position is a reload. */
static inline qword Sub(const qword *pa, const qword *pb)
{
    qword a = *pa, b = *pb, r;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Scale(qword a, float g)
{
    qword k;
    U u;
    __asm__("qmtc2.ni %1,%0" : "=j"(k) : "r"(g));
    u.q = k;
    __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(a) : "j"(a), "j"(k));
    return a;
}
static inline float Dot(qword a, qword b)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=&j"(d), "=&j"(one) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0,%1" : "=r"(g) : "j"(d));
    return g;
}
static inline void Normal(U *v, qword fallback)
{
    qword a = v->q;
    register qword d __asm__("vf1"); /* the one pin: the length/result lives in vf1 (as in FHackSoHit__FP2LOP5CTMSG) */
    qword one;
    float len;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=&j"(d), "=&j"(one) : "j"(a));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0,%1" : "=r"(len) : "j"(d));
    if (len < 0.0001f)
        d = fallback;
    else
        __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(d) : "j"(d), "j"(a));
    v->q = d;
}
static inline qword AddScaled(const qword *pa, qword b, float g)
{
    qword a = *pa, k;
    U u;
    __asm__("qmtc2.ni %1,%0" : "=j"(k) : "r"(g));
    u.q = k;
    __asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x" : "=j"(a) : "j"(b), "j"(k), "0"(a));
    return a;
}

// name: SafeHouse port (OnStepXpNew)
void OnStepXpNew__FP3ALOP2XPi(struct STEP *pstep, struct XP *pxp, int ixpd)
{
    U dir, diff, point;
    float d;
    float sign;
    int xpk;
    func_001F4FB0();
    xpk = pxp->xpk;
    pxp->friction = 0.0f;
    pxp->response = 0.0f;
    if (xpk == 14) {
        if (pxp->normal.f[2] > 0.7f) {
            pxp->friction = D_002C3C90;
            pxp->lower = pstep->psophys->mass * -4500.0f;
            pxp->upper = pstep->psophys->mass * 9000.0f;
        } else
            pxp->upper = pstep->psophys->mass * 9000.0f;
        return;
    }
    if (xpk != 3) {
        if (ixpd != 1)
            return;
        if (xpk != ixpd && xpk != 4 && xpk != 5 && xpk != 6)
            return;
    }
    sign = D_002C3C60[ixpd];
    if (sign * pxp->normal.f[2] > 0.0f) {
        /* horizontal direction of the (side-signed) normal */
        dir.q = Scale(pxp->normal.q, sign);
        dir.f[2] = 0.0f;
        Normal(&dir, D_002A2DA0);
        /* project this endpoint onto the other along that direction */
        diff.q = Sub(&pxp->ae[ixpd].pos, &pxp->ae[1 - ixpd].pos);
        d = Dot(diff.q, dir.q);
        point.q = AddScaled(&pxp->ae[1 - ixpd].pos, dir.q, d);
        PxpAddSw__FP3SOET0P6VECTORG9VU_VECTORT3iiiPvf(g_sw, pstep->psoeCustom, pxp->ae[1 - ixpd].shape, point.q, dir.q, 10, 0, 0, &pxp->next, d);
    }
}
