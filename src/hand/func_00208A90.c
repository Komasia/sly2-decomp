/* func_00208A90 (0x208A90): removes a class from the guard's immediate classes (moving on after each removal, as the game does). */
struct GUARD { char pad[0x3C0]; int ccidImmediate; int acidImmediate[1]; };
void *s1_memmove(void *pvDst, void *pvSrc, int cb) asm("memmove");
void func_00208A90(struct GUARD *pguard, int cid)
{
    int icid;
    for (icid = 0; icid < pguard->ccidImmediate; icid++) {
        if (pguard->acidImmediate[icid] == cid) {
            s1_memmove(pguard->acidImmediate + icid, pguard->acidImmediate + icid + 1, (pguard->ccidImmediate - icid) * 4 - 4);
            pguard->ccidImmediate--;
        }
    }
}
