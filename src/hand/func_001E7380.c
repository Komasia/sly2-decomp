typedef int qword __attribute__((mode(TI)));
float func_001E64C8(void *p);
void func_001E6ED8(void *p, qword q, int a, int b, int c, int d, int e, float g);
void func_001E7380(void *p, qword q, int a, int b, int c, int d, int e)
{
    func_001E6ED8(p, q, a, b, c, d, e, func_001E64C8(p));
}
