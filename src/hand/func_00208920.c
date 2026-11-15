/* func_00208920 (0x208920): adds a class to the guard's excluded classes (at most 5). */
struct GUARD { char pad[0x3A8]; unsigned int ccidExcluded; int acidExcluded[5]; };
void func_00208920(struct GUARD *pguard, int cid) { if (pguard->ccidExcluded < 5) pguard->acidExcluded[pguard->ccidExcluded++] = cid; }
