#include "stepguard.h"
struct JOBINVESTIGATE { char pad[0x10]; struct GUARD *pguard; };
qword PosOfLo__FP2LO(struct GUARD *pjob);
qword PosNoise__14JOBINVESTIGATE(struct JOBINVESTIGATE *pjob);
static inline float Dist(qword a, qword b) {
    qword d;
    float f;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xy %0, %1, %1
	vaddy.x %0, %0, %0y" : "=j"(d) : "j"(d));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
    return f;
}
/* JOBINVESTIGATE::FNear: whether the guard is near enough the noise: always for a guard that cannot move there (+0xFE8
 * bit 1 clear, or kind 2); else when the noise is within the guard's leash (+0xE74, its distance + 50). */
// name: SafeHouse port (JOBINVESTIGATE::FNear)
int FNear__14JOBINVESTIGATE(struct JOBINVESTIGATE *pjob) {
    struct GUARD *pguard = pjob->pguard;
    struct GUARD *ploLeash;
    float d;
    if (!(pguard->grfMove & 2) || pguard->nSearchKind == 2) return 1;
    ploLeash = pguard->ploLeash;
    if (!ploLeash) return 0;
    d = Dist(PosOfLo__FP2LO(ploLeash), PosOfLo__FP2LO(pjob->pguard));
    if (Dist(PosNoise__14JOBINVESTIGATE(pjob), PosOfLo__FP2LO(pjob->pguard)) < d + 50.0f) return 1;
    return 0;
}
