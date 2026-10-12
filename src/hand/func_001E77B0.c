typedef int qword __attribute__((mode(TI)));
void func_001E6F60(void *a, int b, int c, qword *pq, int d, int e, int f);
qword func_001E77B0(void *a, int b)
{
    qword q;
    func_001E6F60(a, b, 0, &q, 0, 0, 0);
    return q;
}
