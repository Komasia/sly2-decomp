typedef int qword __attribute__((mode(TI)));
int func_0014C6D8(void *p, int n, qword a, qword b, int c, float *d);
int func_0014C6A0(char *p, qword a, qword b, int c, float *d)
{
    return func_0014C6D8(p, *(int *)(p + 0x74), a, b, c, d);
}
