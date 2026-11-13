typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
typedef struct { qword r[3]; } M3;
struct T { M3 m; qword v[3]; };
struct X { char pad[0xE8]; struct T *pt; };
void s1_memcpy(void *d, const void *s, unsigned int cb);
void *s1_memset(void *d, int c, unsigned int cb);
int FInvertMatrix3__FP7MATRIX3T0(struct T *pt, qword *pv);
void AdjustSoMomint__FP2SOf(struct X *p, float s)
{
    struct T *pt = p->pt;
    M3 m;
    U u;
    M3 r;
    __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(s));
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r.r[0]) : "j"(u.q), "j"(pt->m.r[0]));
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r.r[1]) : "j"(u.q), "j"(pt->m.r[1]));
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r.r[2]) : "j"(u.q), "j"(pt->m.r[2]));
    s1_memcpy(&m, &r, sizeof(M3));
    pt->m = m;
    if (!FInvertMatrix3__FP7MATRIX3T0(p->pt, p->pt->v))
        s1_memset(p->pt->v, 0, 0x30);
}
