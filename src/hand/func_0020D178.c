/* class: WATCHA, a guard's watcher (SafeHouse kind2.cpp: 0x20D178 disables it): +0xC off, then SetWatchA(p, 0, n). */
struct WATCHA {
    /* 0x0 */ char pad0[0xc];
    /* 0xc */ int fOn;
};
void SetWatchA__FP6WATCHAi(struct WATCHA *pwatch, int n, int n2);

void func_0020D178(struct WATCHA *pwatch, int n1, int n2)
{
    pwatch->fOn = 0;
    SetWatchA__FP6WATCHAi(pwatch, 0, n2);
}
