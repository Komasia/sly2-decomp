/* func_002089F0 (0x2089F0): whether plo is of one of the guard's excluded classes. */
struct GUARD { char pad[0x3A8]; int ccidExcluded; int acidExcluded[1]; };
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
int func_002089F0(struct GUARD *pguard, void *plo)
{
    int icid;
    for (icid = 0; icid < pguard->ccidExcluded; icid++) {
        if (FIsBasicDerivedFrom__FP5BASIC3CID(plo, pguard->acidExcluded[icid])) return 1;
    }
    return 0;
}
