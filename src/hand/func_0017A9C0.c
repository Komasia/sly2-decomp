/* class: JOBB0 (SafeHouse aijobs.h JOBB0::FDone (stHeld == -1)). */
struct JOBB0 {
    /* 0x00 */ char pad0[0x30];
    /* 0x30 */ int st;
};

int func_0017A9C0(struct JOBB0 *pjob)
{
    return pjob->st == -1;
}
