typedef int qword __attribute__((mode(TI)));
qword func_001A62E8(void *p);
int func_00173610(qword *pq, int a, int b, float f, float g);
int func_0014A478(char *p)
{
    char *q = *(char **)(p + 0x10);
    qword t;
    if (*(int *)(q + 0x208)) return 0;
    t = func_001A62E8(q);
    return func_00173610(&t, 1, 0, 100.0f, -250.0f) == 0;
}
