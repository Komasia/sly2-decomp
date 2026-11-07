struct S { char pad[0x24]; int x24; char pad2[0x1C0]; int x1e8; int x1ec; };
void SetMenuState__FP4MENUi(struct S *p, int n);
int func_001B0108(struct S *p);
void func_001AF608(struct S *p)
{
    if (p->x1e8 == 7) {
        SetMenuState__FP4MENUi(p, 2);
        if (func_001B0108(p)) p->x1ec = p->x24 = p->x24 - 1;
    }
}
