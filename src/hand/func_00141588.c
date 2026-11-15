/* PosActorFocus: the point the camera follows on the actor: the climb's while climbing (+0xF54 set); else its position
 * raised by its height (+0x1048) over its support (+0x208: from +0x238) or, when airborne (jump state 0x14) or not the
 * camera's focus, over +0x248; the camera's focus on the ground uses the smoothed focus height (+0x104C). */
typedef int qword __attribute__((mode(TI)));
struct CM { char pad[0x260]; void *ploFocus; char pad2[0x300 - 0x264]; int n300; };
extern struct CM g_cm;
struct V { float x, y, z; } __attribute__((aligned(16)));
void func_0019E9D8(void *pactor, struct V *ppos);
qword PosOfLo__FP2LO(void *pactor);
// name: SafeHouse port (PosActorFocus)
void PosActorFocus__FP5ACTORP9ACTORPOSE(char *pactor, struct V *ppos)
{
    float z;
    if (*(int *)(pactor + 0xF54) != -1) {
        func_0019E9D8(pactor + 0xF50, ppos);
        return;
    }
    *(qword *)ppos = PosOfLo__FP2LO(pactor);
    if (*(int *)(pactor + 0x208)) {
        z = *(float *)(pactor + 0x238) + *(float *)(pactor + 0x1048);
    } else if (*(int *)(pactor + 0x2DC) == 0x14 || g_cm.n300 != 0 || g_cm.ploFocus != pactor) {
        ppos->z += *(float *)(pactor + 0x248) + *(float *)(pactor + 0x1048);
        return;
    } else {
        z = *(float *)(pactor + 0x104C);
    }
    ppos->z = z;
}
