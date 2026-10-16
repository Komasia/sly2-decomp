// wip (Claude agent): 24/89 - only prologue scheduling (clock.t lui/lwc1 hoisted to top; target keeps source load order m3,vmax,t,m0..2,vmin).
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
typedef struct { float x, y, z, w; } V;
struct CLOCK { float t; float dt; };
extern struct CLOCK D_002DDED0;
float func_0011CF60(float);

int func_00139950(M4 *pm, qword dt, qword *pa, qword *pb, qword *pc, int c, int k, qword *pvMin, qword *pvMax)
{
    register qword vdt __asm__("vf27") = dt;
    register qword m3 __asm__("vf28") = pm->r[3];
    register qword vmax __asm__("vf25") = *pvMax;
    float t = D_002DDED0.t;
    register qword m0 __asm__("vf31") = pm->r[0];
    register qword m1 __asm__("vf30") = pm->r[1];
    register qword m2 __asm__("vf29") = pm->r[2];
    register qword vmin __asm__("vf26") = *pvMin;
    register qword v21 __asm__("vf21");
    register qword v22 __asm__("vf22");
    register qword v23 __asm__("vf23");
    register qword v24 __asm__("vf24");
    float g;
    int cDead = 0;
    int j = -1;
    int i;
    int sync;

    for (i = 0; i < c; i++) {
        if (((V *)&pb[i])->w <= t) {
            cDead++;
            continue;
        }
        v24 = pb[i];
        v23 = pa[i];
        __asm__ __volatile__("vcallms 0x10" : "=j"(v21), "=j"(v22), "=j"(vmax), "=j"(vmin)
            : "j"(v23), "j"(v24), "j"(vdt), "j"(m0), "2"(vmax), "3"(vmin));
        j++;
        pc[j] = pc[i];
        if (k == 2) {
            __asm__("mtc1 %1, %0" : "=f"(g) : "r"(dt));
            ((V *)&pc[j])->w = func_0011CF60(((V *)&pc[i])->w + ((V *)&pc[i])->z * g);
        }
        __asm__ __volatile__("cfc2.i %0, $vi0" : "=r"(sync) : "j"(v21), "j"(v22), "j"(m1), "j"(m2), "j"(m3));
        pb[j] = v22;
        pa[j] = v21;
    }
    *pvMin = vmin;
    *pvMax = vmax;
    return cDead;
}
