/* class: WATCHA, a guard's watcher (SafeHouse kind2.cpp, orig 0x20D1A0: the ordinary falling detection resumed). */
struct WATCHA {
    /* 0x0 */ char pad0[0xc];
    /* 0xc */ int fOn;
};

void func_0020D1A0(struct WATCHA *pwatch)
{
    pwatch->fOn = 1;
}
