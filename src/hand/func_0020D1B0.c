/* func_0020D1B0 (0x20D1B0): WATCHB init (the guard's water watcher, +0x49C): its guard, no state, on. */
struct WATCHB { void *pguard; int st; float t; void *plo; int fOn; };
void func_0020D1B0(struct WATCHB *pwatch, void *pguard) { pwatch->pguard = pguard; pwatch->st = -1; pwatch->fOn = 1; }
