/* class: NAVREGION (SafeHouse aipursuit.cpp: "0x1C0960: its triangles' pieces"): the pieces of the segment a-b on the
 * walkable triangles - CsegNav (0x1BF3D8) on the region's +0xE0 part. */
typedef int qword __attribute__((mode(TI)));   /* a VU_VECTOR in one register */
typedef struct NAV NAV;          /* the 2D BSP the named Nav functions work on */
typedef struct NAVSEG NAVSEG;
typedef struct VECTOR VECTOR;
typedef struct NAVREGION {
    /* 0x00 */ char pad0[0xe0];
    /* 0xe0 */ char nav[0x20];   /* its walkable area (BSP) */
} NAVREGION;
int CsegNav__FP9NAVREGIONG9VU_VECTORT1iP6NAVSEGi(void *pnav, qword posA, qword posB, int cseg, NAVSEG *aseg, int n);

int func_001C0960(NAVREGION *preg, qword posA, qword posB, int cseg, NAVSEG *aseg, int n)
{
    return CsegNav__FP9NAVREGIONG9VU_VECTORT1iP6NAVSEGi(preg->nav, posA, posB, cseg, aseg, n);
}
