struct S { char pad[0x13C]; int x; };
void func_00221298(struct S *p, int a);
void func_00221268(struct S *p, int x)
{
    if (x != p->x) { p->x = x; func_00221298(p, 0); }
}
