/* func_001F2688 (0x1F2688): set SO::gUnk13c; the bounds record mirrors it when this SO owns the record. */
#include "so.h"

void func_001F2688(SO *pso, float g)
{
    SOBOUNDS *psobounds = pso->psobounds;

    pso->gUnk13c = g;
    if (psobounds != NULL && psobounds->pso == pso)
        psobounds->gUnk20 = g;
}
