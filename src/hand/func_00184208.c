typedef int qword __attribute__((mode(TI)));
qword func_001A62E8(void *a, void *b);
void func_00184208(void *a, void *b, qword *p)
{
    if (p) *p = func_001A62E8(a, b);
}
