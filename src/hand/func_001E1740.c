union U { int n; float g; };
struct CMD { int kind; int b; int n8; int nC; union U a[4]; };
struct CMD *func_001E01F8(void *pq, int kind, int b);
void func_001E1740(void *pq, int a, int b, int c, float g)
{
    struct CMD *p = func_001E01F8(pq, 0x4A, 0);
    p->a[0].g = g; p->a[1].n = a; p->a[2].n = b; p->a[3].n = c;
}
