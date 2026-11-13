/* JOBMURRAYATTACK::Exit (Murray's attack job, cid 0xC3, AIJOB vt slot 9 = Exit): the base exit, then the actor's attacking flag
 * (+0x10E0 bit 0, set by the job's Enter) cleared. Layout: SafeHouse port (actorai.h JOBCOMPANIONATTACK). */
struct ACTOR {
    /* 0x0000 */ char pad0[0x10e0];
    /* 0x10e0 */ int grf10E0;   /* field: SafeHouse port */
};
struct JOBMURRAYATTACK {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ struct ACTOR *pactor;   /* field: SafeHouse port (AIJOB +0x10) */
};
void Exit__5AIJOB(struct JOBMURRAYATTACK *pjob);

// name: AIJOB vt slot 9 (Exit) of class JOBMURRAYATTACK (cid 0xC3; its Update / Drive are named); SafeHouse port
// (actorai.cpp JOBCOMPANIONATTACK::Exit, orig 0x00145D68 / 0x00146260 / 0x00146758)
void Exit__15JOBMURRAYATTACK(struct JOBMURRAYATTACK *pjob)
{
    Exit__5AIJOB(pjob);
    pjob->pactor->grf10E0 &= ~1;
}
