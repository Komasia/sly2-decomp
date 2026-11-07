union U { int n; float g; };
struct CMD { int kind; int b; int n8; int nC; union U a[6]; };
struct CMD *PcmdNew__FP4SCPTii(void *pq, int kind, int b);
void func_001E0C08(void *pq, int a, int x, int c, int d, float g, float h)
{
    struct CMD *p = PcmdNew__FP4SCPTii(pq, 0x24, x);
    p->a[0].n = a; p->a[1].g = g; p->a[2].g = h; p->a[3].n = c; p->a[4].n = d; p->a[5].n = 0;
}
