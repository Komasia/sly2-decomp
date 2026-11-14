/* class: the region's walkable BSP (AstarNav calls it): the index of an element of its +0x4 array of 0x20-byte
 * records. */
typedef struct NAVTRI { char ab[0x20]; } NAVTRI;
typedef struct NAV {
    /* 0x0 */ int n0;
    /* 0x4 */ NAVTRI *atri;
} NAV;

int func_001BF970(NAV *pnav, NAVTRI *ptri)
{
    return ptri - pnav->atri;
}
