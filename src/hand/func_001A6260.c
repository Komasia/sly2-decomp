/* func_001A6260 (0x1A6260): the last extra oid of the LO's own entries at the head of its names list (+0x3C), -1 if
 * none. */
struct NSE { int x0; struct NSE *pnseNext; int oid; int xc; void *plo; };  /* +0x3C: the names list (entries owned by the LO come first) */
struct S { char pad[0x3C]; struct NSE *pnseFirst; };
int func_001A6260(struct S *plo)
{
    int oid = -1;
    struct NSE *pnse = plo->pnseFirst;
    while (pnse) {
        if (pnse->plo != plo) break;
        oid = pnse->oid;
        pnse = pnse->pnseNext;
    }
    return oid;
}
