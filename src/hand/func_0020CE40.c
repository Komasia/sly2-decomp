/* func_0020CE40 (0x20CE40): WATCHA reset: on, state 0 (on the ground). */
struct WATCHA { void *pguard; int st; float t; int fOn; };
void SetWatchA__FP6WATCHAi(struct WATCHA *pwatch, int st);
void func_0020CE40(struct WATCHA *pwatch) { pwatch->st = -1; pwatch->fOn = 1; SetWatchA__FP6WATCHAi(pwatch, 0); }
