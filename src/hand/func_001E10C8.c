union U { int n; float g; void *pv; };
struct CMD { int kind; int b; int n8; int nC; union U a[4]; };
struct CMD *func_001E01F8(void *pq, int kind, int b);
void func_001E10C8(void *pq, int a, int b, int c, float g)
{
    struct CMD *p = func_001E01F8(pq, 0x34, 1);
    p->a[0].n = a; p->a[1].n = b; p->a[2].n = c; p->a[3].g = g;
}
