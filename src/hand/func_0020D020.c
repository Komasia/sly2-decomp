/* FWatchA (0x20D020): whether the guard is falling: not on a floor, not moving on an object, falling allowed
 * (+0x4A0), not held (state 0x13), and no ground found 100 above to 600 below any of five probes around it
 * (D_002C3E00, the line test filtered by 0x20CFC0). Field names: SafeHouse port (guard.cpp FWatchA). */
typedef int qword __attribute__((mode(TI)));
extern qword D_002C3E00[5];   /* the probes in the guard's frame */
extern float D_002C3E50;      /* 100: above */
extern float D_002C3E54;      /* 600: below */
int func_0020CFC0(void);
struct GUARD { char pad[0x208]; int pxpFloor; char pad2[0x4A0 - 0x20C]; int f4A0; char pad3[0xF80 - 0x4A4]; int kMove; };
int FGuardState(struct GUARD *pguard, int st) asm("FGuardState__FP5GUARDi");
qword ConvertPos__FP2LOT0G9VU_VECTOR(struct GUARD *pguard, int ploTo, qword pos);
int FDropOnGround__FP6VECTORffiPv(qword *ppos, float sUp, float sDown, int grf, int (*pfnFilter)(void));
// name: SafeHouse port (FWatchA)
int FWatchA__FP6WATCHA(struct GUARD **ppguard)
{
    struct GUARD *pguard = *ppguard;
    unsigned int iprobe;
    if (pguard->pxpFloor || pguard->kMove != -1 || !pguard->f4A0 || FGuardState(pguard, 0x13))
        return 0;
    iprobe = 0;
    do {
        qword pos = ConvertPos__FP2LOT0G9VU_VECTOR(*ppguard, 0, D_002C3E00[iprobe]);
        if (FDropOnGround__FP6VECTORffiPv(&pos, D_002C3E50, D_002C3E54, 1, func_0020CFC0))
            break;
        iprobe++;
    } while (iprobe < 5);
    return !(iprobe < 5);
}
