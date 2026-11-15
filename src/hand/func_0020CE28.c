/* func_0020CE28 (0x20CE28): WATCHA init (the guard's fall watcher, +0x498): its guard, no state, on. */
struct WATCHA { void *pguard; int st; float t; int fOn; };
void func_0020CE28(struct WATCHA *pwatch, void *pguard) { pwatch->pguard = pguard; pwatch->st = -1; pwatch->fOn = 1; }
