struct S { char pad[0x2C0]; long fl; char pad2[0xE64 - 0x2C8]; int nE64; };
long func_00207A20(int n);
int func_00208D70(struct S *p)
{
    long m = func_00207A20(0xB) | func_00207A20(0x1D) | func_00207A20(7) | func_00207A20(5) | func_00207A20(6)
           | func_00207A20(0x10) | func_00207A20(1) | func_00207A20(0x16) | func_00207A20(0x2A);
    if (m & p->fl)
        return 0;
    return p->nE64;
}
