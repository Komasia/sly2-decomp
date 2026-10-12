void func_00215CA8(void *p, int a);
int func_00215D40(void *p);
int func_00215E30(void *p)
{
    int n = 0;
    func_00215CA8(p, 0);
    while (func_00215D40(p))
        n++;
    return n;
}
