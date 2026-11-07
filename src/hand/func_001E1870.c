union U { int n; float g; };
struct CMD { int kind; int b; int n8; int nC; union U a[6]; };
struct CMD *PcmdNew__FP4SCPTii(void *pq, int kind, int b);
void func_001E1870(void *pq, int a, int b, int c, int d, int e, int x)
{
    struct CMD *p = PcmdNew__FP4SCPTii(pq, 0x4F, x);
    p->a[1].n = a;
    p->a[3].n = b;
    p->a[2].n = c;
    p->a[4].n = d;
    p->a[0].n = e;
}
