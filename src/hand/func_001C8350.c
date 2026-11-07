struct S { char pad[0x180]; int x180; char p1[0x198 - 0x184]; int x198; void *x19C; char p2[0x1F0 - 0x1A0]; int x1F0; };
void UpdateSo__FP2SOf(struct S *p);
int func_001DFFD8(void *p);
void SetVaultState__FP2LOi(struct S *p, int n);
void UpdateVaultDial__FP2LO(struct S *p);
void func_001C8188(int f);
// name: SafeHouse port (UpdateVault)
void UpdateVault__FP2LO(struct S *p)
{
    int s;
    UpdateSo__FP2SOf(p);
    do {
        s = p->x180;
        switch (s) {
        case 1:
            if (!p->x19C || !func_001DFFD8(p->x19C))
                SetVaultState__FP2LOi(p, 2);
            break;
        case 2:
            if (!p->x19C || !func_001DFFD8(p->x19C)) {
                if (p->x198 == p->x1F0)
                    SetVaultState__FP2LOi(p, 3);
                else
                    SetVaultState__FP2LOi(p, 4);
            } else {
                UpdateVaultDial__FP2LO(p);
            }
            break;
        case 4:
            if (!p->x19C || !func_001DFFD8(p->x19C))
                SetVaultState__FP2LOi(p, 0);
            break;
        case 3:
            if (!p->x19C || !func_001DFFD8(p->x19C)) {
                func_001C8188(1);
                SetVaultState__FP2LOi(p, 5);
            }
            break;
        }
    } while (p->x180 != s);
}
