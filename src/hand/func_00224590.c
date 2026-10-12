struct S { char pad[0x150]; int x; };
int func_00224590(struct S *p)
{
    switch (p->x) { case 1: case 2: return 1; }
    return 0;
}
