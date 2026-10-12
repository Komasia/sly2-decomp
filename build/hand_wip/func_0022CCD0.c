// WIP 14 diffs: VU part matches except lqc2 order of out rows 0/1 and the stack temp copies order; float stores: x (mtc1) is stored first in ours.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int n[4]; } VU;
typedef struct { qword r[3]; } M3;
typedef struct { VU r[4]; } M4;
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static __inline__ M3 MulMM(M3 *pa, M3 *pb)
{
    M3 r;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z" : "=j"(r.r[0]) : "j"(pa->r[0]), "j"(pa->r[1]), "j"(pa->r[2]), "j"(pb->r[0]));
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z" : "=j"(r.r[1]) : "j"(pa->r[0]), "j"(pa->r[1]), "j"(pa->r[2]), "j"(pb->r[1]));
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z" : "=j"(r.r[2]) : "j"(pa->r[0]), "j"(pa->r[1]), "j"(pa->r[2]), "j"(pb->r[2]));
    return r;
}
void *func_002333B4(void *p, int c, int n);
M4 *func_0022CCD0(M4 *pm, void *pv, M3 *pmB, qword v)
{
    func_002333B4(pm, 0, 0x40);
    pm->r[0].f[1] = GetZ(v);
    pm->r[2].f[0] = GetY(v);
    pm->r[2].f[1] = -GetX(v);
    pm->r[1].f[0] = -GetZ(v);
    pm->r[1].f[2] = GetX(v);
    pm->r[0].f[2] = -GetY(v);
    *(M3 *)pm = MulMM((M3 *)pm, pmB);
    pm->r[2].n[3] = 0;
    pm->r[1].n[3] = 0;
    pm->r[0].n[3] = 0;
    return pm;
}
