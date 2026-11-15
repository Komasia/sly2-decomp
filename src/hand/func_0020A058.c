typedef struct { int tagk; int tag; } CRef;
void func_002013D8(   /* a list option's values */
    CRef *pref, int refList, int grf, int cnMax, void *pcn, void *an);
void __as__4CRefRC4CRef(CRef *prefDst, CRef *prefSrc);
void Decref(CRef *pr) asm("Decref__4CRef");
struct GUARD { char pad[0xF94]; int cploF98; int aploF98[4]; int cploFAC; int aploFAC[4]; };
/* func_0020A058 (0x20A058, option 426): the guard's two object lists (at most 4 each): +0xF98 the objects it
 * attacks, +0xFAC the ones it turns to when near (SafeHouse guard.h). */
void func_0020A058(struct GUARD *pguard, int refList1, int refList2)
{
    CRef ref;
    CRef refTmp;
    ref.tagk = -1;
    func_002013D8(&refTmp, refList1, 0x2002, 4, &pguard->cploF98, pguard->aploF98);
    __as__4CRefRC4CRef(&ref, &refTmp);
    Decref(&refTmp);
    func_002013D8(&refTmp, refList2, 0x2002, 4, &pguard->cploFAC, pguard->aploFAC);
    __as__4CRefRC4CRef(&ref, &refTmp);
    Decref(&refTmp);
    Decref(&ref);
}
