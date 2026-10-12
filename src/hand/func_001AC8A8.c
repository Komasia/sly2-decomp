int func_002442D8(int a, int b, int c);
void func_001AB098(void *p, int r, int n, int d);
struct S { char pad[0xFD5C]; char x[4]; };
void func_001AC8A8(struct S *p, int a, int b, int c, int d)
{
    func_001AB098(p->x, func_002442D8(a, b, c), 6, d);
}
