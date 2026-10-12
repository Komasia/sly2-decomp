extern int D_002BFB28[];
struct S { int x0; int x4; char pad[0xCC]; void *a[1]; };
void *func_001A23F8(struct S *p, int *pout)
{
    int i; void *r = 0; for (i = p->x4; i != -1 && (r = p->a[i]) == 0; i = D_002BFB28[i]) ; *pout = 0; return r;
}
