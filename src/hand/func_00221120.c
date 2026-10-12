struct S { char pad[0x10C]; int x; };
int func_00221120(struct S *p, int **pp)
{
    if (!p->x) return 0;
    *pp = &p->x; return 1;
}
