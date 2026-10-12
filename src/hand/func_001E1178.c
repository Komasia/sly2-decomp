union U { int n; float g; void *pv; };
struct CMD { int kind; int b; int n8; int nC; union U a[7]; };
struct CMD *func_001E01F8(void *pq, int kind, int b);
void func_001E1178(void *pq, int a, int b, int c, int d, float f, float g, float h)
{
    struct CMD *p = func_001E01F8(pq, 0x36, 1);
    p->a[0].n = a; p->a[1].n = b; p->a[2].n = c; p->a[3].n = d;
    p->a[4].g = f; p->a[5].g = g; p->a[6].g = h;
}
