typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int n[4]; } VU;
typedef struct { VU r[3]; } M3;
typedef struct { VU r[4]; } M4;
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
struct S { M4 m; char pad[0x94 - 0x40]; int k; };
void *s1_memcpy(void *d, void *s, int n) asm("memcpy");
M3 *BuildEulerMatrix__FP6VECTORG9VU_VECTOR(M3 *pm, qword v);
VU *func_00256D18(VU *pv, qword q);
// name: SafeHouse port (MatXfWithValue)
M4 *MatXfWithValue__FP2XFP7VECTOR4G9VU_VECTOR(M4 *pm, struct S *p, qword v)
{
    switch (p->k) {
    case 0: case 8: case 13: case 14: case 15:
        break;
    case 1: case 4: case 5: case 9: case 10:
        s1_memcpy(pm, p, 0x40);
        __asm__("sw %1,%0" : "=m"(pm->r[3].f[0]) : "r"(v));
        pm->r[3].f[1] = GetY(v);
        pm->r[3].f[2] = GetZ(v);
        break;
    case 2: case 3:
        s1_memcpy(pm, p, 0x40);
        break;
    case 6: case 7: {
        M3 m;
        BuildEulerMatrix__FP6VECTORG9VU_VECTOR(&m, v);
        func_00256D18(&pm->r[3], p->m.r[3].q);
        pm->r[0]=m.r[0];
        pm->r[1]=m.r[1];
        pm->r[2]=m.r[2];
        pm->r[3].f[3] = 1.0f;
        pm->r[2].n[3] = 0;
        pm->r[1].n[3] = 0;
        pm->r[0].n[3] = 0;
        break;
    }
    case 11:
        s1_memcpy(pm, p, 0x40);
        __asm__("sw %1,%0" : "=m"(pm->r[1].f[0]) : "r"(v));
        pm->r[2].f[0] = GetY(v);
        pm->r[2].f[1] = GetZ(v);
        break;
    case 12:
        s1_memcpy(pm, p, 0x40);
        __asm__("sw %1,%0" : "=m"(pm->r[0].f[0]) : "r"(v));
        pm->r[1].f[1] = GetY(v);
        pm->r[2].f[2] = GetZ(v);
        break;
    }
    return pm;
}
