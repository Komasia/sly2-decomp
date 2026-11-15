struct GUARD { char pad[0xF3C]; int fStriking; };
struct JOBSTRIKE { char pad[0x10]; struct GUARD *pguard; };
void Exit__7JOBMOVE(struct JOBSTRIKE *pjob);
/* JOBSTRIKE::Exit: the base exit; the guard is no longer striking (+0xF3C). */
// name: SafeHouse port (JOBSTRIKE::Exit)
void Exit__9JOBSTRIKE(struct JOBSTRIKE *pjob) { Exit__7JOBMOVE(pjob); pjob->pguard->fStriking = 0; }
