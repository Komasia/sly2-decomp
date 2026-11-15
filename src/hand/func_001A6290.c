/* func_001A6290 (0x1A6290): whether the LO answers to an oid: its own (+0x18) or one of its entries at the head of
 * its names list (+0x3C). */
struct NSE { int x0; struct NSE *pnseNext; int oid; int xc; void *plo; };  /* +0x3C: the names list (entries owned by the LO come first) */
struct S { char pad[0x18]; int oid; char pad2[0x20]; struct NSE *pnseFirst; };
int func_001A6290(struct S *plo, int oid)
{
    struct NSE *pnse;
    if (plo->oid == oid) return 1;
    for (pnse = plo->pnseFirst; pnse && pnse->plo == plo; pnse = pnse->pnseNext)
        if (pnse->oid == oid) return 1;
    return 0;
}
