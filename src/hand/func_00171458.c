/* class: JOBSCRIPT-like command job (SafeHouse aijobs.h FDone() { return !pcmd; }, orig 0x171458): no command left. */
struct CMD;
struct JOBCMD {
    /* 0x00 */ char pad0[0x38];
    /* 0x38 */ struct CMD *pcmd;   /* field: SafeHouse port */
};

int func_00171458(struct JOBCMD *pjob)
{
    return pjob->pcmd == 0;
}
