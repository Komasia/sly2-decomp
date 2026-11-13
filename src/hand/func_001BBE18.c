/* class: the breakables (SafeHouse breakable.cpp FValidEvent, orig 0x001BBE18: the current event +0x15C is one of the
 * +0x160 events, or -1 - the breakable is not broken yet; see r7_candidates). */
struct BREAKABLE {
    /* 0x000 */ char pad0[0x15c];
    /* 0x15c */ int ievCur;   /* SafeHouse port: icur */
    /* 0x160 */ int cev;
};

int func_001BBE18(struct BREAKABLE *pbrk)
{
    int iev = pbrk->ievCur;
    int fValid = 0;
    if ((iev >= 0 && iev < pbrk->cev) || iev == -1) {
        fValid = 1;
    }
    return fValid;
}
