/* class: ACTOR (SafeHouse scpt.cpp: a script waits on it until the throw controller is back in state -1). */

#include "actor.h"
int func_001424C0(struct ACTOR *pactor)
{
    return pactor->stThrow == -1;
}
