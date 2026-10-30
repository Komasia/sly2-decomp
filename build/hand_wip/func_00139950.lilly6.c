// T1650 (Claude agent for Lilly, 2026-10-25): as lilly5 but qmtc2 vf27 carried by a fake "+m"(*pvMin) output (no copy, qmtc2 reads a1 like the target); frame 0xD0 vs 0xC0, aligned 25. Not a direction worth keeping: the asm lies about writing *pvMin.
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
typedef struct { float x, y, z, w; } V;
struct CLOCK { float t; float dt; };
extern struct CLOCK D_002DDED0;
float func_0011CF60(float);

int func_00139950(M4 *pm, qword dt, qword *pa, qword *pb, qword *pc, int c, int k, qword *pvMin, qword *pvMax)
{
    register qword v24 __asm__("vf24"); /* microprogram input */
    float t;
    float g;
    int cDead = 0;
    int j = -1;
    int i;
    int sync;

    __asm__("qmtc2.ni %1, $vf27" : "+m"(*pvMin) : "r"(dt));
    __asm__("lqc2 $vf28, %0" : "+m"(pm->r[3]));
    __asm__("lqc2 $vf25, %0" : "+m"(*pvMax));
    t = D_002DDED0.t;
    __asm__("lqc2 $vf31, %0" : "+m"(pm->r[0]));
    __asm__("lqc2 $vf30, %0" : "+m"(pm->r[1]));
    __asm__("lqc2 $vf29, %0" : "+m"(pm->r[2]));
    __asm__("lqc2 $vf26, %0" : "+m"(*pvMin));
    for (i = 0; i < c; i++) {
        if (((V *)&pb[i])->w <= t) {
            cDead++;
            continue;
        }
        v24 = pb[i];
        __asm__("lqc2 $vf23, %0" : "+m"(pa[i]));
        __asm__ __volatile__("vcallms 0x10" : : "j"(v24));
        j++;
        pc[j] = pc[i];
        if (k == 2) {
            __asm__("mtc1 %1, %0" : "=f"(g) : "r"(dt));
            ((V *)&pc[j])->w = func_0011CF60(((V *)&pc[i])->w + ((V *)&pc[i])->z * g);
        }
        __asm__ __volatile__("cfc2.i %0, $vi0" : "=r"(sync));
        __asm__("sqc2 $vf22, %0" : "=m"(pb[j]));
        __asm__("sqc2 $vf21, %0" : "=m"(pa[j]));
    }
    __asm__("sqc2 $vf26, %0" : "=m"(*pvMin));
    __asm__("sqc2 $vf25, %0" : "=m"(*pvMax));
    return cDead;
}
