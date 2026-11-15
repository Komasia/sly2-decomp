/* func_0020D178 (0x20D178): the fall watcher off (during a kind-2 flight), back in state 0 (SafeHouse kind2.cpp). */
struct WATCHA {
    /* 0x0 */ char pad0[0xc];
    /* 0xc */ int fOn;
};
void SetWatchA__FP6WATCHAi(struct WATCHA *pwatch, int st, int n);

void func_0020D178(struct WATCHA *pwatch, int n1, int n)
{
    pwatch->fOn = 0;
    SetWatchA__FP6WATCHAi(pwatch, 0, n);
}
