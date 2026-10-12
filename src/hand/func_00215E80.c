struct S { int a; char *pch; };
void func_00215CA8(struct S *p, int a);
int func_00215D40(struct S *p);
void func_00215E80(struct S *p, int n)
{
    func_00215CA8(p, 0);
    while (func_00215D40(p) && n != 0)
        n--;
    *p->pch = 0;
}
