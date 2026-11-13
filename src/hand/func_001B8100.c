struct S { char pad[0x13D0]; int n; char pad2[0x17F4 - 0x13D4]; int f17f4; };
int NActorPaused(struct S *p) asm("NActorPaused__Fv");
int func_001B8100(struct S *p)
{
    int v = NActorPaused(p);
    if (v != -1) return v;
    switch (p->n) {
    case 1: case 12:
        return 1;
    case 9:
        if (p->f17f4) v = 1;
        return v;
    }
    return -1;
}
