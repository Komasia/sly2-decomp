/* class: JOBCOMPANIONATTACK, Bentley's (cid 0xC4) attack job, Init (AIJOB vt slot 7): the base init, then no state (-1, complete).
 * Layout: SafeHouse port (actorai.h JOBCOMPANIONATTACK; actorai.cpp: orig 0x145CD0 / 0x1461C8 / 0x1466C0). */
struct JOBCOMPANIONATTACK {
    /* 0x00 */ char pad0[0x30];
    /* 0x30 */ int st;   /* field: SafeHouse port - -1 complete */
};
void Init__5AIJOB(struct JOBCOMPANIONATTACK *pjob);
void func_001461C8(struct JOBCOMPANIONATTACK *pjob)
{
    Init__5AIJOB(pjob);
    pjob->st = -1;
}
