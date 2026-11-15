/* func_00173398: add a proxy oid to a spawner (at most 8). */
#include "h2_spawner.h"
void func_00173398(SPAWNER *pspawner, int oid) { if (pspawner->coidProxy < 8) { pspawner->aoidProxy[pspawner->coidProxy++] = oid; } }
