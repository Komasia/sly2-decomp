/* class: NAVREGION (SafeHouse pickup.cpp: "FNavBlocked ... 0x1C0980"): whether the segment a-b leaves the walkable
 * area - FNavBlocked (0x1BF900) on the region's +0xE0 part. */
typedef int qword __attribute__((mode(TI)));   /* a VU_VECTOR in one register */
typedef struct NAV NAV;          /* the 2D BSP the named Nav functions work on */
typedef struct NAVSEG NAVSEG;
typedef struct VECTOR VECTOR;
typedef struct NAVREGION {
    /* 0x00 */ char pad0[0xe0];
    /* 0xe0 */ char nav[0x20];   /* its walkable area (BSP) */
} NAVREGION;
int FNavBlocked__FP9NAVREGIONG9VU_VECTORT1i(void *pnav, qword posA, qword posB, int fl);

int func_001C0980(NAVREGION *preg, qword posA, qword posB, int fl)
{
    return FNavBlocked__FP9NAVREGIONG9VU_VECTORT1i(preg->nav, posA, posB, fl);
}
