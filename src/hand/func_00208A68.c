/* func_00208A68 (0x208A68): adds a class to the guard's immediate classes (at most 2). */
#include "stepguard.h"
void func_00208A68(struct GUARD *pguard, int cid) { if ((uint)pguard->ccidImmediate < 2) pguard->acidImmediate[pguard->ccidImmediate++] = cid; }
