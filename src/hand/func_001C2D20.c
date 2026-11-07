struct S { char pad[0x168]; void *p168; int a16c; };
extern char D_002C0CB0[];
void func_001F36A8(struct S *p);
void BindLoParts__FP3ALOiPv(struct S *p, int n, void *q);
void ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(void *a, struct S *p, int b, int c, int *pn);
// name: SafeHouse port (PpsmaPocket)
void PpsmaPocket__FP2LO(struct S *p)
{
    func_001F36A8(p);
    BindLoParts__FP3ALOiPv(p, 4, D_002C0CB0);
    ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(p->p168, p, -1, 0, &p->a16c);
}
