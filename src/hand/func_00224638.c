struct S { char pad[0x150]; int a; char pad2[8]; int k; };
// name: SafeHouse port (FCarryLands)
int FCarryLands__FP7CARRYRT(struct S *p)
{
    switch (p->k) {
    case 4: return p->a == 1;
    default: return 0;
    case 5: case 7: case 9: case 11: case 13: case 26: case 37: case 41: return 1;
    }
}
