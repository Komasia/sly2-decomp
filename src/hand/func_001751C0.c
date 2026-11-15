struct JOBMOVE { char pad[0x3C]; int nAnim; };
void Init__7JOBMOVE(struct JOBMOVE *pjob);
/* JOBSTRIKE::Init: a JOBMOVE with animation 3. */
// name: SafeHouse port (JOBSTRIKE::Init)
void Init__9JOBSTRIKE(struct JOBMOVE *pjob) { Init__7JOBMOVE(pjob); pjob->nAnim = 3; }
