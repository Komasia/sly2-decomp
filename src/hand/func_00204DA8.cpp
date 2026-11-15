/* SetStepPhysSize (0x204DA8; Sly 1 SetStepGravityRatio): sets the STEP's size sSize (at least 0.1), scaling its mass by
   old / new and its gravity by new / old.
   Ported from Lilly's personal decomp (T0981). Each VU float is a one-qword struct so it gets the stack home the dead sqc2 go to;
   the gravity is read as a struct member, and the old ratio goes into vf3 straight from memory ("rV"). No register pins. */
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword qw; };
struct VU_VECTOR4 { qword qw; };
struct SOPHYS { char pad[0x80]; struct VU_VECTOR4 dvGravity; char pad90[0x40]; float m; };
struct STEP { char pad[0xE8]; struct SOPHYS *psophys; char padEC[0x260 - 0xEC]; float sSize; };
extern "C" void SetSoMass(struct STEP *pso, float m) asm("SetSoMass__FP2SOf");   /* SetSoMass */

// name: SafeHouse port (SetStepPhysSize)
extern "C" void SetStepPhysSize__FP3ALOf(struct STEP *pstep, float sRequested)
{
    float sNew = 0.1f;
    qword qwScaled;
    sNew = sRequested > sNew ? sRequested : sNew;
    SetSoMass(pstep, pstep->psophys->m * pstep->sSize / sNew);
    {
        struct VU_FLOAT vuR;
        qword qwGrav = pstep->psophys->dvGravity.qw;
        __asm__("qmtc2 %1, %0" : "=j"(vuR.qw) : "r"(sNew));
        __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(qwScaled) : "j"(qwGrav), "j"(vuR.qw));
    }
    {
        struct VU_FLOAT vuOld;
        qword qwResult;
        __asm__("qmtc2 %1, %0" : "=j"(vuOld.qw) : "rV"(*(int *)&pstep->sSize));
        __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(qwResult) : "j"(qwScaled), "j"(vuOld.qw));
        pstep->psophys->dvGravity.qw = qwResult;
    }
    pstep->sSize = sNew;
}
