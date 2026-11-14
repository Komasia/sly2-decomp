/* class: NAVREGION (SafeHouse nav.cpp: 0x1C1440's cached triangle record): the 0x40-byte record cleared, its indices
 * from the region's count +0x100 less 2, +0x20 -1. */
struct NAVREGION {
    /* 0x000 */ char pad0[0x100];
    /* 0x100 */ int c;
};
struct NAVCACHE {
    /* 0x00 */ char pad0[0x20];
    /* 0x20 */ int n20;
    /* 0x24 */ int i24, i28, i2C, i30;
    /* 0x34 */ char pad34[0x40 - 0x34];
};
void *memset(void *, int, unsigned int);

void func_001C1440(struct NAVREGION *preg, struct NAVCACHE *pcache)
{
    int iA;
    int iB;
    memset(pcache, 0, 0x40);
    iA = preg->c - 2;
    pcache->i28 = iA;
    pcache->i24 = iA;
    iB = preg->c - 2;
    pcache->n20 = -1;
    pcache->i30 = iB;
    pcache->i2C = iB;
}
