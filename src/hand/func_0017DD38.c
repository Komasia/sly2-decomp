/* JOBGOTO::SetGoal: a new goal, searched for at once (the last search's time reset). */
#include "h2_aijobs.h"

void Search__7JOBGOTO(JOBGOTO *pjob);

// name: SafeHouse port (JOBGOTO::SetGoal)
void SetGoal__7JOBGOTOP4GOAL(JOBGOTO *pjob, GOAL *pgoal)
{
    pjob->goal = *pgoal;
    pjob->tSearch = -3.40282346638528859812e+38f;
    Search__7JOBGOTO(pjob);
}
