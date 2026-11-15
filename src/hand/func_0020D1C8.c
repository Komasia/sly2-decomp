/* func_0020D1C8 (0x20D1C8): WATCHB reset: on, state 0. */
struct WATCHB { void *pguard; int st; float t; void *plo; int fOn; };
void SetWatchB__FP6WATCHBi(struct WATCHB *pwatch, int st);
void func_0020D1C8(struct WATCHB *pwatch) { pwatch->st = -1; pwatch->fOn = 1; SetWatchB__FP6WATCHBi(pwatch, 0); }
