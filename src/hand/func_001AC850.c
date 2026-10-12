int func_002441C0(int a, int b, int c);
void func_001AB098(void *p, int r, int n, int d);
struct S { char pad[0xFD5C]; char x[4]; };
void func_001AC850(struct S *p, int a, int b, int c, int d)
{
    func_001AB098(p->x, func_002441C0(a, b, c), 5, d);
}
