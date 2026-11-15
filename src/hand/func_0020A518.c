/* func_0020A518 (0x20A518, option 301): adds a region the guard may go in (at most 8). */
#include "stepguard.h"
void func_0020A518(struct GUARD *pguard, int region) { if (pguard->cRegion < 8) pguard->aRegion[pguard->cRegion++] = region; }
