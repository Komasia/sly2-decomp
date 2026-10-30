// laneZ2 v1 (Claude agent, 2026-10-30): microprogram 0x10 register ABI bound inside the VU helpers.
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
typedef struct { float x, y, z, w; } V;
struct CLOCK { float t; float dt; };
extern struct CLOCK D_002DDED0;
float func_0011CF60(float);

/* VU0 microprogram 0x10: vf23/vf24 = pa/pb entries, vf27 = dt, vf28..vf31 = matrix rows 3..0,
   vf25/vf26 = running max/min (updated in place). Results land in vf21/vf22. */
static __inline__ void CallMs10(qword a, qword b, qword dt, const M4 *m, qword vmin, qword vmax)
{
    register qword v23 __asm__("vf23") = a;
    register qword v24 __asm__("vf24") = b;
    register qword v27 __asm__("vf27") = dt;
    register qword v31 __asm__("vf31") = m->r[0];
    register qword v30 __asm__("vf30") = m->r[1];
    register qword v29 __asm__("vf29") = m->r[2];
    register qword v28 __asm__("vf28") = m->r[3];
    register qword v26 __asm__("vf26") = vmin;
    register qword v25 __asm__("vf25") = vmax;
    __asm__ __volatile__("vcallms 0x10" : : "j"(v23), "j"(v24), "j"(v27), "j"(v31), "j"(v30),
        "j"(v29), "j"(v28), "j"(v26), "j"(v25));
}

static __inline__ void SyncMs10(qword *pa, qword *pb)
{
    int sync;
    register qword v21 __asm__("vf21");
    register qword v22 __asm__("vf22");
    __asm__ __volatile__("cfc2.i %0, $vi0" : "=r"(sync), "=j"(v21), "=j"(v22));
    *pb = v22;
    *pa = v21;
}

int func_00139950(M4 *pm, qword dt, qword *pa, qword *pb, qword *pc, int c, int k, qword *pvMin, qword *pvMax)
{
    float t = D_002DDED0.t;
    qword vmin = *pvMin;
    qword vmax = *pvMax;
    M4 m = *pm;
    float g;
    int cDead = 0;
    int j = -1;
    int i;

    for (i = 0; i < c; i++) {
        if (((V *)&pb[i])->w <= t) {
            cDead++;
            continue;
        }
        CallMs10(pa[i], pb[i], dt, &m, vmin, vmax);
        j++;
        pc[j] = pc[i];
        if (k == 2) {
            __asm__("mtc1 %1, %0" : "=f"(g) : "r"(dt));
            ((V *)&pc[j])->w = func_0011CF60(((V *)&pc[i])->w + ((V *)&pc[i])->z * g);
        }
        SyncMs10(&pa[j], &pb[j]);
    }
    *pvMin = vmin;
    *pvMax = vmax;
    return cDead;
}
