/* func_0015C310 (0x15C310): EXPLG virtual slot 27 (the LO "children list" slot): return the child explosions. */
#include "emitter.h"

int func_0015C310(EXPLG *pexplg, void ***papexpl)
{
    *papexpl = pexplg->apexpl;
    return pexplg->cpexpl;
}
