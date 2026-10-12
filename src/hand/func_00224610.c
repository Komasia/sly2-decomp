struct S { char pad[0x15C]; int x; };
int func_00224610(struct S *p)
{
    int x = p->x; if (x != 7 && x != 11) return 0; return 1;
}
