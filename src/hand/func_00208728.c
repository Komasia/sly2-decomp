struct GUARD { char pad[0x394]; int ccidTarget; int acidTarget[1]; };
void *s1_memmove(void *pvDst, void *pvSrc, int cb) asm("memmove");
/* RemoveTargetClass (0x208728): removes a class from the guard's target classes (moving on after each removal, as the
 * game does). */
// name: SafeHouse port (RemoveTargetClass)
void RemoveTargetClass__FPvi(struct GUARD *pguard, int cid)
{
    int icid;
    for (icid = 0; icid < pguard->ccidTarget; icid++) {
        if (pguard->acidTarget[icid] == cid) {
            s1_memmove(pguard->acidTarget + icid, pguard->acidTarget + icid + 1, (pguard->ccidTarget - icid) * 4 - 4);
            pguard->ccidTarget--;
        }
    }
}
