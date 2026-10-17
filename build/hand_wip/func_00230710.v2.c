/* WIP (Claude agent sony7) v2: aligned 50 (v1 75): the x94 test of the func_00230310 branch is also a switch with 'case 6: case 7:' (M3 path) first, like the target layout.
   Left: target stores the f-vector/result qwords to stack (0x10/0x0 in the CA18 path, 0x90 in the M3 path) = memory locals; M3 path stores the 3 rows 3x (0xA0.., 0x30.., 0x0..) = M3 by-value helper return copies; frame 0x130 vs 0x1A0. */
typedef int qword __attribute__((mode(TI)));
typedef struct M4 { qword r[4]; } M4;
typedef struct M3 { qword r[3]; } M3;
typedef struct VT { short d; short pad; void (*pfn)(); } VT;
typedef struct O { char pad[0x18]; VT *vt; } O;
typedef struct P {
    qword r[4];
    char pad40[0x90 - 0x40];
    O *x90;
    int x94;
    short x98;
    char pad9A[0xB0 - 0x9A];
    qword xB0;
} P;
int func_00230310(int);
M4 *func_0022C8C0(M4 *, P *, qword);
M4 *func_0022CB90(M4 *, P *, M4 *, qword, qword);
M4 *func_0022CC00(M4 *, P *, qword);
M4 *func_0022CCD0(M4 *, P *, M4 *, qword);
M3 *func_0011B570(M3 *, qword);
qword func_0022CA18(P *, P *);
qword *func_00256D18(qword *, qword);
void *func_002333B4(void *, int, int);

void func_00230710(P *p, M4 *pm, M4 *pm2, float f)
{
    if (p->x90) {
        qword q[2];
        M4 t;
        ((void (*)(void *, qword *, qword *))p->x90->vt[5].pfn)((char *)p->x90 + p->x90->vt[5].d, &q[0], &q[1]);
        func_0022C8C0(&t, p, q[0]);
        *pm = t;
        switch (p->x94) {
        case 6: case 7:
            func_0022CB90(&t, p, pm, q[0], q[1]);
            break;
        default:
            func_0022CC00(&t, p, q[1]);
            break;
        }
        *pm2 = t;
    } else if (func_00230310(p->x98)) {
        switch (p->x94) {
        case 6: case 7: {
        M3 r;
        qword fq, v, a, b, c;
        M4 t;
        M3 u;
        __asm__("mfc1 %0, %1" : "=r"(fq) : "f"(f));
        __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(v) : "j"(p->xB0), "j"(fq));
        func_0011B570(&r, v);
        __asm__("vmulax.xyz $ACC, %1, %2x\n\tvmadday.xyz $ACC, %3, %2y\n\tvmaddz.xyz %0, %4, %2z" : "=j"(a) : "j"(r.r[0]), "j"(p->r[0]), "j"(r.r[1]), "j"(r.r[2]));
        __asm__("vmulax.xyz $ACC, %1, %2x\n\tvmadday.xyz $ACC, %3, %2y\n\tvmaddz.xyz %0, %4, %2z" : "=j"(b) : "j"(r.r[0]), "j"(p->r[1]), "j"(r.r[1]), "j"(r.r[2]));
        __asm__("vmulax.xyz $ACC, %1, %2x\n\tvmadday.xyz $ACC, %3, %2y\n\tvmaddz.xyz %0, %4, %2z" : "=j"(c) : "j"(r.r[0]), "j"(p->r[2]), "j"(r.r[1]), "j"(r.r[2]));
        u.r[0] = a; u.r[1] = b; u.r[2] = c;
        func_00256D18(&pm->r[3], p->r[3]);
        pm->r[0] = u.r[0]; pm->r[1] = u.r[1]; pm->r[2] = u.r[2];
        ((float *)pm)[15] = 1.0f;
        ((float *)pm)[11] = 0;
        ((float *)pm)[7] = 0;
        ((float *)pm)[3] = 0;
        func_0022CCD0(&t, p, pm, p->xB0);
        *pm2 = t;
        break; }
        default: {
        qword q = func_0022CA18(p, p);
        qword fq, v;
        M4 t;
        __asm__("mfc1 %0, %1" : "=r"(fq) : "f"(f));
        __asm__("vadda.xyzw $ACC, $vf0, %1\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(v) : "j"(q), "j"(p->xB0), "j"(fq));
        func_0022C8C0(&t, p, v);
        *pm = t;
        func_0022CC00(&t, p, p->xB0);
        *pm2 = t;
        break; }
        }
    } else {
        *pm = *(M4 *)p->r;
        func_002333B4(pm2, 0, 0x40);
    }
}
