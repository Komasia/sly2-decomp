/* JOBB0::FDone (SafeHouse aijobs.h "bool FDone() const { return stHeld == -1; } // orig 0x17A9C0"): the held state
 * is over. */
struct JOBB0 {
    /* 0x00 */ char pad0[0x30];
    /* 0x30 */ int stHeld;   /* field: SafeHouse port */
};

// name: SafeHouse port (JOBB0::FDone; mangled like FDone__11JOBNAVPOINT)
int FDone__5JOBB0(struct JOBB0 *pjob)
{
    return pjob->stHeld == -1;
}
