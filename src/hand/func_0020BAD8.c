typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
extern qword D_002A2DD0;
struct C { int pad; float g; };
struct B { int pad[2]; struct C *pc; };
struct ASEGBL { char pad[0xD0]; struct B *pb; };
/* one of the gait's two clips (0x40 bytes from +0x10): its blend weight, root velocity, length */
struct GAITSEG { float uWeight; int pad[3]; qword vel; int pad2; float tLength; char pad3[0x40 - 0x28]; };
struct GAIT { int pad; struct ASEGBL *pasegbl; int pad2[2]; struct GAITSEG aseg[2]; };
/* VecGaitVelocity (0x20BAD8): the gait's velocity: its two clips' root velocities weighted by their blend weights and
 * their lengths over the blend's length. Field names: SafeHouse port (actanim.h GAIT). */
// name: SafeHouse port (VecGaitVelocity)
qword VecGaitVelocity__FP4GAIT(struct GAIT *pgait)
{
    struct B *pb = pgait->pasegbl->pb;
    float tBlend=pb->pc->g;
    qword velSum = D_002A2DD0;
    struct GAITSEG *pseg = pgait->aseg;
    unsigned int i;
    for (i = 0; i < 2; i++) {
        U u;
        __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(pseg->uWeight * (pseg->tLength / tBlend)));
        __asm__("vadda.xyzw $ACC, %0, $vf0\n\tvmaddx.xyzw %0, %1, %2x" : "+j"(velSum) : "j"(pseg->vel), "j"(u.q));
        pseg++;
    }
    return velSum;
}
