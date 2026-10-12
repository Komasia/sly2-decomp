struct S { char pad[0x1C4]; char dl[0x24]; int f1e8; };
void func_001E5D80(struct S *p);
void func_0011A1F8(void *pdl, int ib);
void func_001BC050(struct S *p)
{
    func_001E5D80(p);
    p->f1e8 = -1;
    func_0011A1F8(p->dl, 0x1D0);
}
