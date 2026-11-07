struct S { char pad[0x24]; int x24; char pad2[0x1C0]; int x1e8; int x1ec; };
void SetMenuState__FP4MENUi(struct S *p, int n);
// name: SafeHouse port (BackReplaced)
void BackReplaced__FP4MENU(struct S *p)
{
    if (p->x1e8 == 7) {
        SetMenuState__FP4MENUi(p, 3);
        p->x1ec = p->x24 - 1;
    }
}
