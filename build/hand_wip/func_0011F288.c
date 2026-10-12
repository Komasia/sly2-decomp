typedef int qword __attribute__((mode(TI)));
typedef struct VECTOR { float x, y, z; } __attribute__((aligned(16))) VECTOR;

extern VECTOR D_002A2DF0;

qword func_0011F288(int cvec, VECTOR *avec)
{
    int ivec;
    qword qRet;
    __asm__ __volatile__("lqc2 $vf2, 0x0(%0)" : : "r"(&D_002A2DF0));
    for (ivec = 0; ivec < cvec; ivec++) {
        __asm__ __volatile__("lqc2 $vf1, 0x0(%0)" : : "r"(&avec[ivec]));
        __asm__ __volatile__("vmini.xyz $vf2, $vf1, $vf2");
    }
    __asm__ __volatile__("qmfc2.ni %0, $vf2" : "=r"(qRet));
    return qRet;
}
