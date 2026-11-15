/* func_00173158: a spawner's Init (CID_SPAWNER): the LO Init, then spawning range 5500 with the edge, range and
 * occlusion checks on, and the far waits 30 / 50 s. */
#include "h2_spawner.h"
void InitLo__FP2LO(SPAWNER *pspawner);
void func_00173158(SPAWNER *pspawner) { InitLo__FP2LO(pspawner); pspawner->sPlanar = 5500.0f; pspawner->fEdge = pspawner->fOcclusion = pspawner->fRange = 1; pspawner->dtWaitFar = 30.0f; pspawner->dtUntilFar = 50.0f; }
