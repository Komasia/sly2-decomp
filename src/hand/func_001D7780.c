/* class: the safe house, class 0x46 (SafeHouse po.cpp RefSetSafeHouseStates, the splice method 0x10F648 of option
 * 1339): set the states the safe house's select may show from an argument list of at most 6 oids (into +0x220 /
 * +0x224), then go to the current state if allowed, else the next (func_001D77D0(psh, 0)). */
typedef struct CRef { int tagk; int tag; } CRef;
struct SAFEHOUSE {
    /* 0x000 */ char pad0[0x220];
    /* 0x220 */ int allowed220;     /* the allowed states list (SafeHouse: "+0x220 / +0x224") */
    /* 0x224 */ int allowed224;
};
void func_002013D8(CRef *pref, void *pvArgs, int cMin, int cMax, int *pa, int *pb);   /* read an oid list argument */
void Decref(CRef *pref) asm("Decref__4CRef");
void func_001D77D0(struct SAFEHOUSE *psh, int dState);

void func_001D7780(struct SAFEHOUSE *psh, void *pvArgs)
{
    CRef ref;
    func_002013D8(&ref, pvArgs, 6, 6, &psh->allowed220, &psh->allowed224);
    Decref(&ref);
    func_001D77D0(psh, 0);
}
