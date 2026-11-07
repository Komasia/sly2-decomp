struct S { char pad[0x1030]; void *p; char pad2[0x190C - 0x1034]; void *q; };
extern char D_002C09F8[];
void DemoteAsegaOnAlo__FP5ASEGAP3ALOiPv(void *a, struct S *p, int n, void *s);
void func_001B6078(struct S *p, int n);
// name: SafeHouse port (EndMurrayPunch)
void EndMurrayPunch__FP6MURRAY(struct S *p)
{
    DemoteAsegaOnAlo__FP5ASEGAP3ALOiPv(p->p, p, 5, D_002C09F8);
    p->q = p->p;
    p->p = 0;
    func_001B6078(p, 0);
}
