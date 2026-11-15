#include "step.h"
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct M3 { qword r[3]; };
/* the STEP fields used here */
extern "C" {
M3 *MatJtLo(STEP *pstep) asm("MatJtLo__FP2LO");
qword PosOfLo(STEP *pstep) asm("PosOfLo__FP2LO");
extern int D_002C3CC8[2][3];   /* the corner indices of the two triangles */
}
static inline qword MulX(qword v, VU_FLOAT g) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(g.q)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword LoadVf(qword *pstep) { qword r; __asm__("lqc2 %0, %1" : "=j"(r) : "m"(*pstep)); return r; }
/* func_002057E8 (0x2057E8): the STEP's two floor-support triangles: from the object's position and the four points
 * sSupport along +-x and +-y (MatJtLo rows) around the base probe pposProbe0, by the corner table D_002C3CC8. */
extern "C" void func_002057E8(STEP *pstep, qword aatri[2][3])
{
    qword apos[5];
    qword posProbe = *pstep->pposProbe0;
    qword right = MatJtLo(pstep)->r[0];
    qword forward = LoadVf(&MatJtLo(pstep)->r[1]);
    apos[0] = PosOfLo(pstep);
    float sSupport = pstep->sSupport;
    apos[1] = Add(posProbe, MulX(right, VU_FLOAT(sSupport)));
    apos[2] = Add(posProbe, MulX(forward, VU_FLOAT(sSupport)));
    apos[3] = Add(posProbe, MulX(right, VU_FLOAT(-sSupport)));
    apos[4] = Add(posProbe, MulX(forward, VU_FLOAT(-sSupport)));
    for (unsigned i = 0; i < 2; i++) {
        int *aipos = D_002C3CC8[i];
        qword *ppos = aatri[i];
        for (unsigned j = 0; j < 3; j++)
            ppos[j] = *(qword *)((aipos[j] << 4) + (unsigned int)apos);
    }
}
