/* func_00208700 (0x208700): adds a target class to the guard's list (at most 3). */
struct GUARD { char pad[0x394]; unsigned int ccidTarget; int acidTarget[3]; };
void func_00208700(struct GUARD *pguard, int cid) { unsigned int ccid = pguard->ccidTarget; if (ccid < 3) { int *pcid = &pguard->acidTarget[ccid]; pguard->ccidTarget = ccid + 1; *pcid = cid; } }
