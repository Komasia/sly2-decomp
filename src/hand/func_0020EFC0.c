struct S { char pad[0x3D78]; int c; };
void AddGrfusr__Fi(int n);
void func_0020F128(struct S *p);
void func_0020F198(struct S *p);
void func_0020EFC0(struct S *p, int fl)
{
    if (++p->c == 1) AddGrfusr__Fi(2);
    if (fl & 1) func_0020F128(p);
    if (fl & 2) func_0020F198(p);
}
