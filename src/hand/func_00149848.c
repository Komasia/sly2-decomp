/* class: the volume triggers (SafeHouse trigger.cpp: option 533 -> 0x149848 -> 0x200F58, its objects +0x2C0 / +0x2C4
 * as references in a CRef list). */
struct CRef;
struct TRIGGER {
    /* 0x000 */ char pad0[0x2c0];
    /* 0x2c0 */ int coid;
    /* 0x2c4 */ int *aoid;
};
void func_00200F58(struct CRef *pref, int c, int grf, int *aoid);

struct CRef *func_00149848(struct CRef *pref, struct TRIGGER *ptrigger)
{
    func_00200F58(pref, ptrigger->coid, 0x2002, ptrigger->aoid);
    return pref;
}
