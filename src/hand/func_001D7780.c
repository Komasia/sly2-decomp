/* class: the safe house, class 0x46 (SafeHouse po.cpp RefSetSafeHouseStates, the splice method 0x10F648 of option
 * 1339): set the states the safe house's select may show from an argument list of at most 6 oids (count +0x220,
 * oids +0x224), then go to the current state if allowed, else the next (func_001D77D0(psh, 0)). */
typedef int OID;
typedef struct CRef { int tagk; int tag; } CRef;
struct SAFEHOUSE {
    /* 0x000 */ char pad0[0x220];
    /* 0x220 */ int coidAllowed;
    /* 0x224 */ OID aoidAllowed[6];
};
void func_002013D8(CRef *pref, void *pvArgs, int cMin, int cMax, int *pc, OID *aoid);   /* read an oid list argument */
void Decref(CRef *pref) asm("Decref__4CRef");
void func_001D77D0(struct SAFEHOUSE *psh, int dState);

void func_001D7780(struct SAFEHOUSE *psh, void *pvArgs)
{
    CRef ref;
    func_002013D8(&ref, pvArgs, 6, 6, &psh->coidAllowed, psh->aoidAllowed);
    Decref(&ref);
    func_001D77D0(psh, 0);
}
