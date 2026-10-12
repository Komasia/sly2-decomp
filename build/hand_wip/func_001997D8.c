typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
typedef union { struct { M3 m; qword pos; } s; float f[16]; int n[16]; } M4;
typedef struct { float f[28]; } HIT;
struct S0 { char pad[0x10]; long x10; char pad2[0x60-0x18]; struct S0 *x60; };
struct EC2 { char pad[0x34]; struct S0 *x34; char pad2[0x70-0x38]; long x70; };
struct C { char pad[0xEC]; struct EC2 *xec; };
struct L { int x0; struct L *x4; int x8; struct C *xc; };
struct EC { char pad[0x64]; struct L *x64; };
struct O { char pad[0xEC]; struct EC *xec; };
struct P { struct O *x0; };
extern qword D_002A2DC0;
extern qword D_002A2DB0;
void func_0011E2D8(qword a, qword b, qword c, qword *pm);
void func_00256D18(qword *pq, qword q);
void func_001995D8(struct P *p, M4 *pm, int n, qword *apt);
int func_0014C6A0(struct S0 *s, qword a, qword b, int n, HIT *ph);
int func_001997D8(struct P *p, qword q1, qword q2)
{
    M3 m;
    M4 m4;
    qword apt[22];
    HIT hit;
    struct L *l;
    int c = 0;
    m.r[0] = q2;
    func_0011E2D8(q2, D_002A2DC0, D_002A2DB0, &m.r[1]);
    func_00256D18(&m4.s.pos, q1);
    m4.s.m = m;
    m4.n[3] = m4.n[7] = m4.n[11] = 0;
    m4.f[15] = 1.0f;
    func_001995D8(p, &m4, 22, apt);
    for (l = p->x0->xec->x64; l; l = l->x4) {
        int i;
        if (l->xc->xec->x70 & 4)
            continue;
        for (i = 0; i < 22; i += 2) {
            struct S0 *s;
            for (s = l->xc->xec->x34; s; s = s->x60) {
                if (s->x10 & (1L << 48))
                    continue;
                if (func_0014C6A0(s, apt[i], apt[i + 1], 1, &hit) <= 0)
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
