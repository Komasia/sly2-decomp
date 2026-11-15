/* func_001733C8: add a spawn point to a spawner (at most 16). */
#include "h2_spawner.h"
void func_001733C8(SPAWNER *pspawner, qword pos) { register int cpos __asm__("$3"); register int i __asm__("$6"); i = pspawner->cpos; if (i < 16) { register qword *apos __asm__("$4"); register int ib __asm__("$2"); apos = pspawner->apos; ib = i * 16; cpos = i + 1; pspawner->cpos = cpos; *(qword *)(ib + (int)apos) = pos; } }
