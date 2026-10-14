typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
typedef struct { int index; float a, b; } TRIREF;
extern void func_00185310(void *p, qword v, int n, TRIREF *pv3, qword *pq1, qword *pq2);
extern float D_002BE918;
static __inline__ qword Bc(float g)
{
    VU u;
    qword s;
    __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(g));
    u.q = s;
    return u.q;
}
static __inline__ qword BcI(int g)
{
    VU u;
    qword s;
    __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(g));
    u.q = s;
    return u.q;
}
static __inline__ qword MAdd2(qword a, qword b, qword sb, qword c, qword sc)
{
    qword r;
    __asm__("vadda.xyzw ACC, %1, $vf0\n\tvmaddax.xyzw ACC, %2, %3x\n\tvmaddx.xyzw %0, %4, %5x"
        : "=j"(r) : "j"(a), "j"(b), "j"(sb), "j"(c), "j"(sc));
    return r;
}
static __inline__ qword MAdd1(qword a, qword b, qword sb)
{
    qword r;
    __asm__("vadda.xyzw ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(sb));
    return r;
}
int func_00185D18(void *p, float g, float h, qword a, qword b, qword c, TRIREF *pv3, qword *pq1, qword *pq2)
{
    TRIREF v3;
    VU q1, q2;
    func_00185310(p, MAdd2(a, b, Bc(h), c, Bc((h * 0.5f) * h)), 0, &v3, &q1.q, &q2.q);
    *pv3 = v3;
    *pq1 = MAdd1(q1.q, q2.q, Bc(g));
    *pq2 = MAdd2(b, c, Bc(h), q2.q, BcI(*(int *)&D_002BE918));
    return 1;
}

typedef char qword_Size[(sizeof(qword)==16)?1:-1];
typedef char VU_Size[(sizeof(VU)==16)?1:-1];
typedef char TRIREF_Size[(sizeof(TRIREF)==12)?1:-1];
typedef char TRIREF_index_Offset[((unsigned)&((TRIREF*)0)->index==0)?1:-1];
typedef char TRIREF_a_Offset[((unsigned)&((TRIREF*)0)->a==4)?1:-1];
typedef char TRIREF_b_Offset[((unsigned)&((TRIREF*)0)->b==8)?1:-1];
