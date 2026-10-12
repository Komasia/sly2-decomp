#include "common.h"
struct SO { char pad[0xD0]; ulong a:34; int fIgnoreLocked:1; ulong c:29; };
void SetSoIgnoreLocked(SO *pso, int f) { pso->fIgnoreLocked = f; }
