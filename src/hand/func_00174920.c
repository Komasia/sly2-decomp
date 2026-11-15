struct JOBMOVE { char pad[0x30]; int st; int pad2[2]; int nAnim; };
void Init__5AIJOB(struct JOBMOVE *pjob);
/* JOBMOVE::Init: the base init, animation 0, no state. */
// name: SafeHouse port (JOBMOVE::Init)
void Init__7JOBMOVE(struct JOBMOVE *pjob) { Init__5AIJOB(pjob); pjob->nAnim = 0; pjob->st = -1; }
