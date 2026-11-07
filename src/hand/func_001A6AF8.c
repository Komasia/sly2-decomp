struct O { char pad[0x10]; struct O *x10; };
// name: SafeHouse port (FLoInParentChain)
int FLoInParentChain__FP2LOT0(struct O *a, struct O *b)
{
    while (a) {
        if (a == b) break;
        a = a->x10;
    }
    return a != 0;
}
