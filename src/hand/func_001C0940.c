/* class: NAVREGION (SafeHouse nav.h "0x1C0320 / 0x1C0940: the nearest walkable point"): FNavPoint (0x1C0320) on the
 * region's +0xE0 part. */
typedef int qword __attribute__((mode(TI)));   /* a VU_VECTOR in one register */
typedef struct NAV NAV;          /* the 2D BSP the named Nav functions work on */
typedef struct NAVSEG NAVSEG;
typedef struct VECTOR VECTOR;
typedef struct NAVREGION {
    /* 0x00 */ char pad0[0xe0];
    /* 0xe0 */ char nav[0x20];   /* its walkable area (BSP) */
} NAVREGION;
int FNavPoint__FP9NAVREGIONG9VU_VECTORP6VECTOR(void *pnav, qword pos, VECTOR *ppos, int fl);

int func_001C0940(NAVREGION *preg, qword pos, VECTOR *ppos, int fl)
{
    return FNavPoint__FP9NAVREGIONG9VU_VECTORP6VECTOR(preg->nav, pos, ppos, fl);
}
