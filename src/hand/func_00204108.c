/* (Claude agent) clock dt word loaded via ClockPage/ClockWord asm (same form as src/hand/func_001CF0A0.cpp, lw into the lui register); volatile on the lw keeps it after the v1E0 lqc2. */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
typedef struct { float x,y,z; } VECTOR3;
typedef struct { qword row[3]; } M3;
union FLOATWORD { float value; int bits; };
extern struct { float t; union FLOATWORD delta; } g_clock;
/* the rotation record (SO +0x5C) */
struct XFROT { char pad[0xB0]; qword angularVelocity; char pad2[0x30]; qword angularForce; };
/* the STEP fields used here */
struct STEP { char pad[0x5C]; struct XFROT *pxfRot; char pad2[0x1A4 - 0x60]; int nMotion; char pad3[8]; M3 matHeading; qword posTarget; char pad4[0x1F4 - 0x1F0]; float xBrake, yBrake, zBrake, uBrake; };
void ApplyAloGravity__FP3ALO(struct STEP *pstep);
static inline int ClockWord(char*page){int word;__asm__ volatile("lw %0,%%lo(%2)(%1)":"=r"(word):"r"(page),"i"(&g_clock.delta.bits),"m"(*(const int*)(page-0x212C)));return word;}
static inline char*ClockPage(){register char*page __asm__("$2");__asm__("lui %0,%%hi(%1)":"=r"(page):"i"(&g_clock.delta.bits));return page;}
void BrakeAloRotation__FP3ALOP7MATRIX3Pf(struct STEP *,M3 *,VECTOR3 *);
static inline void InitScalar(U *value,int bits) {
    register qword scalar __asm__("vf4");
    __asm__("qmtc2.ni %1,%0" : "=j"(scalar) : "r"(bits));
    value->q=scalar;
}
/* UpdateStepPhysMotion (0x204108): STEP vt slot 70: gravity, then the motion mode's rotation (STEP::nMotion). */
// name: SafeHouse port (UpdateStepPhysMotion)
void UpdateStepPhysMotion__FP3ALO(struct STEP *pstep)
{
    ApplyAloGravity__FP3ALO(pstep);
    switch (pstep->nMotion) {
    case 0: { /* STEPMOTION_Brake: brake the rotation in the heading frame */
        VECTOR3 v;
        float uBrake = pstep->uBrake;
        v.z = pstep->zBrake;
        v.x = pstep->xBrake * uBrake;
        v.y = pstep->yBrake * uBrake;
        BrakeAloRotation__FP3ALOP7MATRIX3Pf(pstep, &pstep->matHeading, &v);
        break;
    }
    case 1: { /* STEPMOTION_Target: angular force += (posTarget - angular velocity) / dt */
        register struct XFROT *pxfRot __asm__("$3") = pstep->pxfRot;
        U u;
        register qword dw __asm__("vf3");         register qword dwForce __asm__("vf2");
        char*page=ClockPage();
        int word;
        dw=pstep->posTarget;
        word=ClockWord(page);
        dwForce = pxfRot->angularForce;
        __asm__("vsub.xyzw %0,%0,%1" : "+j"(dw) : "j"(pxfRot->angularVelocity));
        InitScalar(&u,word);
        __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %0, $Q" : "+j"(dw) : "j"(u.q));
        __asm__("vadd.xyzw %0,%0,%1" : "+j"(dwForce) : "j"(dw));
        pxfRot->angularForce=dwForce;
        break;
    }
    case -1: /* STEPMOTION_None */
        break;
    }
}
