/* 5 diffs: row copy order (lq r0/r1 vs target); full valid permutation sweep of LoadM4 statements done, best = this. func_0011B720 returns M3 by value. */
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
typedef struct { qword r[4]; } M4;
struct CM { char pad[0x60]; M4 mat; };
void func_0011EFB0(qword v, float *a, float *b, int c);
M3 func_0011B720(float a, float b);
void func_00256D18(qword *p, qword v);
void func_0014DC58(struct CM *p);
static __inline__ void LoadM4(M4 *pm, M3 *pmat)
{
/*S*/    pm->r[1] = pmat->r[1];
/*S*/    ((int *)&pm->r[1])[3] = 0;
/*S*/    pm->r[0] = pmat->r[0];
/*S*/    pm->r[2] = pmat->r[2];
/*S*/    ((int *)&pm->r[2])[3] = 0;
/*S*/    ((int *)&pm->r[0])[3] = 0;
/*S*/    ((float *)&pm->r[3])[3] = 1.0f;
}
void func_0014E1A8(struct CM *p, qword pos, qword tgt, float da, float db)
{
    qword d;
    float a, b;
    M3 m;
    M4 *pm = &p->mat;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(tgt), "j"(pos));
    func_0011EFB0(d, &a, &b, 0);
    m = func_0011B720(a + da, b + db);
    func_00256D18(&p->mat.r[3], pos);
    LoadM4(pm, &m);
    func_0014DC58(p);
}
