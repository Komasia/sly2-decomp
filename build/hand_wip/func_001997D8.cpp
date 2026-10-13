typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];int i[4];};
struct M3 {U r[3];M3(){}M3(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];}M3&operator=(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return *this;}};
struct M4 {M3 m;qword pos;};
typedef union {qword q[7];float f[28];} HIT;
struct S0 { char pad[0x10]; long x10; char pad2[0x60-0x18]; struct S0 *x60; };
struct EC2 { char pad[0x34]; struct S0 *x34; char pad2[0x70-0x38]; long x70; };
struct C { char pad[0xEC]; struct EC2 *xec; };
struct L { int x0; struct L *x4; int x8; struct C *xc; };
struct EC { char pad[0x64]; struct L *x64; };
struct O { char pad[0xEC]; struct EC *xec; };
struct P { struct O *x0; };
extern qword D_002A2DC0;
extern qword D_002A2DB0;
extern "C" void func_0011E2D8(qword a, qword b, qword c, qword *pm);
extern "C" qword *func_00256D18(qword *pq, qword q);
extern "C" void func_001995D8(struct P *p, M4 *pm, int n, qword *apt);
extern "C" int func_0014C6A0(struct S0 *s, qword a, qword b, int n, HIT *ph);
extern "C" int func_001997D8(struct P *p, qword q1, qword q2)
{
    M3 m;
    M4 m4;
    qword apt[22];
    HIT hit;
    struct L *l;
    int c = 0;
    m.r[0].q = q2;
    func_0011E2D8(q2, D_002A2DC0, D_002A2DB0, &m.r[1].q);
    func_00256D18(&m4.pos, q1);
    m4.m = m;
    ((int *)&m4.m)[3] = ((int *)&m4.m)[7] = ((int *)&m4.m)[11] = 0;
    ((float *)&m4.pos)[3] = 1.0f;
    func_001995D8(p, &m4, 22, apt);
    for (l = p->x0->xec->x64; l; l = l->x4) {
        int i;
        if (l->xc->xec->x70 & 4)
            continue;
        qword *cursor=apt;
        for (i = 0; i < sizeof apt / sizeof *apt; i += 2,cursor+=2) {
            struct S0 *s;
            for (s = l->xc->xec->x34; s; s = s->x60) {
                if (s->x10 & (1L << 48))
                    continue;
                if (func_0014C6A0(s, *cursor,*(qword *)((int)(apt+1) + (i << 4)), 1, &hit) <= 0)
                    continue;
                if (i < 4)
                    return 0;
                if (hit.f[16] == 0.0f)
                    return 0;
                if (hit.f[10] > 0.7f)
                    c++;
            }
        }
    }
    return c >= 2;
}
