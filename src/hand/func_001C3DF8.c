/* ClonePo (0x1C3DF8): PO virtual slot 40: SO clone; the clone's PO+0x168 link points at itself. */
#include "po.h"

void CloneSo__FP2SOT0(SO *pso, SO *psoBase);

void ClonePo__FP2POT0(PO *ppo, PO *ppoBase)
{
    CloneSo__FP2SOT0(&ppo->so, &ppoBase->so);
    ppo->ppoUnk168 = ppo;
}
