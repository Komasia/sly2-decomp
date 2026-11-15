typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
/* the actor: its STEP::vecVel */
struct ALOVEL { char pad[0x190]; qword vecVel; };
union FLOATWORD { float value; int bits; };
struct ASEGBLS { char pad[0x40]; union FLOATWORD gScale; };
struct ASEGBL;
struct GAIT { struct ALOVEL *palo; struct ASEGBL *pasegbl; int pad[2]; float uWeight0; char pad2[0x50 - 0x14]; float uWeight1; int paseg1; };
void RecalcBlend__FP6ASEGBL(struct ASEGBL *pasegbl);
struct ASEGBLS *func_0020BB48(struct GAIT *pgait);
qword VecGaitVelocity__FP4GAIT(struct GAIT *pgait);
static inline void InitScalar(U *value,int bits) {
    register int word __asm__("$2")=bits;
    register qword r __asm__("vf2");
    __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(word));
    value->q=r;
}
static inline qword Negate(qword vecVel,U *value) {
    register qword scalar __asm__("vf1");
    register qword result __asm__("vf3");
    __asm__("qmtc2.ni %1,%0" : "=j"(scalar) : "r"(-1.0f));
    value->q=scalar;
    __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(result) : "j"(vecVel),"j"(value->q));
    return result;
}
/* SetGaitMix (0x20BB58): the mix of the gait's second clip (none without one), the blend recalculated, and the
 * actor's STEP::vecVel the negated gait velocity times the blend's scale. */
// name: SafeHouse port (SetGaitMix)
void SetGaitMix__FP4GAITf(struct GAIT *pgait, float uMix)
{
    struct ALOVEL *palo;
    U b, a;
    qword q, r1, r2;
    if (pgait->paseg1 == 0) {
        pgait->uWeight1 = 0.0f;
        pgait->uWeight0 = 1.0f;
    } else {
        pgait->uWeight1 = uMix;
        pgait->uWeight0 = 1.0f - uMix;
    }
    RecalcBlend__FP6ASEGBL(pgait->pasegbl);
    palo = pgait->palo;
    InitScalar(&a,func_0020BB48(pgait)->gScale.bits);
    b = a;
    q = VecGaitVelocity__FP4GAIT(pgait);
    r1=Negate(q,&b);
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r2) : "j"(a.q), "j"(r1));
    palo->vecVel = r2;
}
