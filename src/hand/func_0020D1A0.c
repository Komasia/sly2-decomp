/* func_0020D1A0 (0x20D1A0): the fall watcher on again (SafeHouse kind2.cpp). */
struct WATCHA {
    /* 0x0 */ char pad0[0xc];
    /* 0xc */ int fOn;
};

void func_0020D1A0(struct WATCHA *pwatch)
{
    pwatch->fOn = 1;
}
