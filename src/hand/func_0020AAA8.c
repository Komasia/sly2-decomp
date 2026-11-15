/* func_0020AAA8 (0x20AAA8): the guard's action objects found again from their oids (near the guard, cid 4). */
extern char g_sw[];
struct GUARD { char pad[0xEB8]; int aoidAction[8]; int coidAction; int aploAction[8]; int cploAction; };
int PloFindSwNearest__FP2LO3OIDii(void *psw, int cid, int oid, struct GUARD *ploNear);
void func_0020AAA8(struct GUARD *pguard)
{
    int i;
    pguard->cploAction = 0;
    for (i = 0; i < pguard->coidAction; i++) {
        int plo = PloFindSwNearest__FP2LO3OIDii(g_sw, 4, pguard->aoidAction[i], pguard);
        if (plo)
            pguard->aploAction[pguard->cploAction++] = plo;
    }
}
