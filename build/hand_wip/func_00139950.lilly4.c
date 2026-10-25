// T1646 asm-only form (no register variables): aligned 43. Frame +0x10, different allocation, and the bc1fl delay slot (lqc2 vf24) is not filled because reorg stops at asm statements.
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
typedef struct { float x, y, z, w; } V;
struct CLOCK { float t; float dt; };
extern struct CLOCK D_002DDED0;
float func_0011CF60(float);

int func_00139950(M4 *pm, qword dt, qword *pa, qword *pb, qword *pc, int c, int k, qword *pvMin, qword *pvMax)
{
    float t;
    float g;
    int cDead = 0;
    int j = -1;
    int i;
    int sync;

    __asm__ __volatile__("qmtc2 %0, vf27" : : "r"(dt));
    __asm__ __volatile__("lqc2 vf31, %0" : : "m"(pm->r[0]));
    __asm__ __volatile__("lqc2 vf30, %0" : : "m"(pm->r[1]));
    __asm__ __volatile__("lqc2 vf29, %0" : : "m"(pm->r[2]));
    __asm__ __volatile__("lqc2 vf28, %0" : : "m"(pm->r[3]));
    __asm__ __volatile__("lqc2 vf26, %0" : : "m"(*pvMin));
    __asm__ __volatile__("lqc2 vf25, %0" : : "m"(*pvMax));
    t = D_002DDED0.t;
    for (i = 0; i < c; i++) {
        if (((V *)&pb[i])->w <= t) {
            cDead++;
            continue;
        }
        __asm__ __volatile__("lqc2 vf24, %0" : : "m"(pb[i]));
        __asm__ __volatile__("lqc2 vf23, %0" : : "m"(pa[i]));
        __asm__ __volatile__("vcallms 0x10");
        j++;
        pc[j] = pc[i];
        if (k == 2) {
            __asm__("mtc1 %1, %0" : "=f"(g) : "r"(dt));
            ((V *)&pc[j])->w = func_0011CF60(((V *)&pc[i])->w + ((V *)&pc[i])->z * g);
        }
        __asm__ __volatile__("cfc2.i %0, $vi0" : "=r"(sync));
        __asm__ __volatile__("sqc2 vf22, %0" : "=m"(pb[j]));
        __asm__ __volatile__("sqc2 vf21, %0" : "=m"(pa[j]));
    }
    __asm__ __volatile__("sqc2 vf26, %0" : "=m"(*pvMin));
    __asm__ __volatile__("sqc2 vf25, %0" : "=m"(*pvMax));
    return cDead;
}
