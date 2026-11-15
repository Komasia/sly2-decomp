/* func_00208920 (0x208920): adds a class to the guard's excluded classes (at most 5). */
#include "stepguard.h"
void func_00208920(struct GUARD *pguard, int cid) { if ((uint)pguard->ccidExcluded < 5) pguard->acidExcluded[pguard->ccidExcluded++] = cid; }
