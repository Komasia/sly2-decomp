/* The camera's filter of the world's entries (SafeHouse cm.cpp / marker.cpp: with 0x20FAA0, the entries with a
 * camera hull: their tree's +0x70 positive). */
struct SWENTRY {
    /* 0x00 */ char pad0[0x70];
    /* 0x70 */ int cHull;
};

int func_0014F030(void *pv, struct SWENTRY *pentry)
{
    return pentry->cHull > 0;
}
