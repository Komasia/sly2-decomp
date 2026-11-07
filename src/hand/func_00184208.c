typedef int qword __attribute__((mode(TI)));
qword PosOfLo__FP2LO(void *a, void *b);
void func_00184208(void *a, void *b, qword *p)
{
    if (p) *p = PosOfLo__FP2LO(a, b);
}
