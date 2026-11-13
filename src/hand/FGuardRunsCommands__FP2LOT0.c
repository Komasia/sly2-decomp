/* FGuardRunsCommands (EOPID 319): whether the guard's reactions job (0x9C) is running that command list (its message
 * 5 at +0x30, its list at +0x40). Source: SafeHouse port (scptai.cpp). */
struct LO;
struct JOBREACT {
    /* 0x00 */ char pad0[0x30];
    /* 0x30 */ int nMsg;          /* field: SafeHouse port - the message (5: a command list) */
    /* 0x34 */ char pad34[0x40 - 0x34];
    /* 0x40 */ struct LO *pcmds;  /* field: SafeHouse port */
};
struct JOBREACT *func_00205458(struct LO *pguard, int cid);   /* the guard's job of a class */

// name: SafeHouse port (FGuardRunsCommands)
int FGuardRunsCommands__FP2LOT0(struct LO *pguard, struct LO *pcmds)
{
    struct JOBREACT *pjob = func_00205458(pguard, 0x9C);
    int f = 0;
    if (pjob != 0 && pjob->nMsg == 5)
        f = pjob->pcmds == pcmds;
    return f;
}
