typedef int qword __attribute__((mode(TI)));
typedef struct M4 { qword r[4]; } M4;
typedef struct P { char pad[0xA0]; struct P *xA0; } P;
void *s1_memset(void *, int, int) asm("memset");
void PredictXf__FP2XFPvP7MATRIX4f(P *, M4 *, M4 *, float);
M4 MulMatrix4__FP7MATRIX4T0Pv(M4 *, M4 *);

static inline void AddM4(M4 *d, M4 *a, M4 *b)
{
    int i;
    for (i = 0; i < 4; i++) {
        qword r;
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a->r[i]), "j"(b->r[i]));
        d->r[i] = r;
    }
}

// name: SafeHouse port (PredictXfChain)
void PredictXfChain__FP2XFT0PvP7MATRIX4f(P *first, P *end, M4 *pA, M4 *pB, float f)
{
    M4 m1, m2, a, b, s, t1, t2;
    P *p;

    if (pB)
        b = *pB;
    else
        s1_memset(&b, 0, 0x40);
    if (pA)
        a = *pA;
    else {
        float *pf = (float *)&a;
        s1_memset(&a, 0, 0x40);
        pf[0] = pf[5] = pf[10] = pf[15] = 1.0f;
    }
    for (p = first; p != end; p = p->xA0) {
        PredictXf__FP2XFPvP7MATRIX4f(p, &m1, &m2, f);
        t1 = MulMatrix4__FP7MATRIX4T0Pv(&m1, &b);
        t2 = MulMatrix4__FP7MATRIX4T0Pv(&m2, &a);
        AddM4(&s, &t1, &t2);
        b = s;
        s = MulMatrix4__FP7MATRIX4T0Pv(&m1, &a);
        a = s;
    }
    if (pA)
        *pA = a;
    if (pB)
        *pB = b;
}
