/* func_001DEF98: the world positions of a beam's two endpoints (apos[0], apos[1]): a fixed point is converted from
 * the laser's local space (its XF at +0x60), a path endpoint is evaluated on its path at its current distance.
 * With psLength it also returns the distance between them. */
#include "h3_laser.h"
typedef struct LASER { char unk_so[0x60]; void *pxf; } LASER;   /* SO +0x60: the root XF */
qword PosConvertXfs__FP2XFT0G9VU_VECTOR(void *pxfFrom, int pxfTo, qword pos);
void EvalCrvS(void *pcrv, qword *ppos, int pdpos, float s) asm("EvalCrvS__FP3CRVfP6VECTORT2");
void func_001DEF98(LASER *plaser, LASEREND *pend, qword *apos, float *psLength)
{
    unsigned int iend;
    for (iend = 0; iend < 2; iend++, pend++) {
        switch (pend->kind) {
        case LASERENDK_Point:
            apos[iend] = PosConvertXfs__FP2XFT0G9VU_VECTOR(plaser->pxf, 0, pend->pos);
            break;
        case LASERENDK_Path:
            EvalCrvS(pend->track.pcrv, &apos[iend], 0, pend->track.s);
            break;
        }
    }
    if (psLength) {
        int sLength;   /* |apos[1] - apos[0]|, moved out of the VU as raw float bits */
        __asm__("lqc2 $vf1, %1\n\tlqc2 $vf2, %2\n\tvsub.xyzw $vf2, $vf2, $vf1\n\tvmul.xyz $vf2, $vf2, $vf2\n\tvaddw.x $vf3, $vf0, $vf0w\n\tvadday.x $ACC, $vf2, $vf2y\n\tvmaddz.x $vf2, $vf3, $vf2z\n\tvsqrt $Q, $vf2x\n\tvwaitq\n\tvaddq.x $vf2, $vf0, $Q\n\tqmfc2.ni %0, $vf2" : "=r"(sLength) : "m"(apos[1]), "m"(apos[0]));
        *(int *)psLength = sLength;
    }
}
