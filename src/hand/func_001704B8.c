/* func_001704B8: close the allocator's current page: the rest of it (up to the next 0x80 boundary) becomes a free
 * block in its size class's list, and the allocation point moves to the boundary. */
struct BLK { int iFirst; int iLim; struct BLK *pblkNext; };   /* a free range */
struct ZPR { int n0; int iCur; int n8; struct BLK *apblkFree[8]; int cblk; struct BLK ablk[1]; };
int func_00170448(int n);
void func_001704B8(struct ZPR *pzpr) {
    struct BLK *pblk;
    int iLim, i;
    if (!(pzpr->iCur & 0x7F)) return;
    pblk = &pzpr->ablk[pzpr->cblk++];
    pblk->iFirst = pzpr->iCur;
    iLim = (pzpr->iCur + 0x7F) & ~0x7F;
    pzpr->iCur = iLim;
    pblk->iLim = iLim;
    i = func_00170448(iLim - pblk->iFirst);
    pblk->pblkNext = pzpr->apblkFree[i];
    pzpr->apblkFree[i] = pblk;
}
