struct JOBMOVE { char pad[0x3C]; int nAnim; };
void Init__7JOBMOVE(struct JOBMOVE *pjob);
/* JOBSTAND::Init: a JOBMOVE with animation 2. */
// name: SafeHouse port (JOBSTAND::Init)
void Init__8JOBSTAND(struct JOBMOVE *pjob) { Init__7JOBMOVE(pjob); pjob->nAnim = 2; }
