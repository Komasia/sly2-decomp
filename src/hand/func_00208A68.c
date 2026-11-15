/* func_00208A68 (0x208A68): adds a class to the guard's immediate classes (at most 2). */
struct GUARD { char pad[0x3C0]; unsigned int ccidImmediate; int acidImmediate[2]; };
void func_00208A68(struct GUARD *pguard, int cid) { if (pguard->ccidImmediate < 2) pguard->acidImmediate[pguard->ccidImmediate++] = cid; }
