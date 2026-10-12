// WIP: &m2 (sp+0x50) gets CSE'd from the memset arg into its own s-reg (s3); target recomputes it into s0 after memset.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int n[4]; } VU;
typedef struct { qword r[3]; } M3;
typedef struct { VU r[4]; } M4;
extern M3 D_002A2D00;
struct S { char pad[0x60]; void *p60; char pad1[0x160 - 0x64]; float x, y, z; };
qword func_001A6F00(int a, struct S *p, qword q);
void func_00256D18(VU *pv, qword q);
void *func_002333B4(void *p, int c, int n);
void func_00230CD0(void *p, int a, M4 *pm1, M4 *pm2);
qword func_0011BFB8(M4 *pm);
void func_00228C18(struct S *p, qword v, qword *ppos, qword *prot)
{
    VU q;
    M4 m1, m2;
    M3 *pmI;
    M4 *pm;
    q.q = func_001A6F00(0, p, v);
    q.f[2] = 0.0f;
    pmI = &D_002A2D00;
    pm = &m1;
    func_00256D18(&m1.r[3], q.q);
    pm->r[0].q = pmI->r[0];
    pm->r[1].q = pmI->r[1];
    pm->r[2].q = pmI->r[2];
    m1.r[2].n[3] = 0;
    m1.r[1].n[3] = 0;
    m1.r[0].n[3] = 0;
    pm->r[3].f[3] = 1.0f;
    func_002333B4(&m2, 0, 0x40);
    {
        M4 *pm2 = &m2;
        m2.r[3].f[0] = p->x;
        m2.r[3].f[1] = p->y;
        m2.r[3].f[2] = p->z;
        func_00230CD0(p->p60, 0, pm, pm2);
        if (ppos) *ppos = m2.r[3].q;
        if (prot) *prot = func_0011BFB8(pm2);
    }
}
