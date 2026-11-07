struct E { int id; char pad[0x18]; int c; void *a[3]; };
struct S { char pad[0x23C]; int c; struct E *ae; struct E *pe; };
void func_001F6A68(struct S *p);
void ShowAloGlobs__FP3ALOi(struct S *p, void *pv);
// name: SafeHouse port (SetPickupLootKind)
void SetPickupLootKind__FP2LOi(struct S *p, int id)
{
    int i, n;
    {
    int j; struct E *pe;
    n = p->c;
    for (j = 0; ; j++) {
        if (j >= n) {
            p->pe = p->ae;
            break;
        }
        pe = &p->ae[j];
        if (id == pe->id) {
            p->pe = pe;
            break;
        }
    }
    }
    func_001F6A68(p);
    for (i = 0; i < p->pe->c; i++) ShowAloGlobs__FP3ALOi(p, p->pe->a[i]);
}
