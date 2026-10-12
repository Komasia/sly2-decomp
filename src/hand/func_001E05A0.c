union U { int n; float g; };
struct CMD { int kind; int b; int n8; int nC; union U a[6]; };
struct CMD *func_001E01F8(void *pq, int kind, int b);
void func_001E05A0(void *pq, int a, int b, int c, int x, int d)
{
    struct CMD *p = func_001E01F8(pq, 0xD, x);
    p->a[0].n = a; p->a[1].n = b; p->a[2].n = c; p->a[3].n = d;
    if (d) p->b = 1;
}
