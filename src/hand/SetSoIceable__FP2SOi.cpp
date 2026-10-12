#include "common.h"
struct SO { char pad[0x148]; ulong a:33; int fIceable:1; ulong c:30; };
void SetSoIceable(SO *pso, int f) { pso->fIceable = f; }
