/* FLoInParentChain (0x1A6AF8): whether ploAncestor is the LO itself or one of its parents (+0x10). */
struct O { char pad[0x10]; struct O *x10; };
// name: SafeHouse port (FLoInParentChain)
int FLoInParentChain__FP2LOT0(struct O *plo, struct O *ploAncestor)
{
    while (plo) {
        if (plo == ploAncestor) break;
        plo = plo->x10;
    }
    return plo != 0;
}
