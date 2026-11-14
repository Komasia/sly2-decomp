/* class: NAVREGION (SafeHouse spawner.cpp / navlink.cpp: "0x1C0920 = 0x1BF110 on +0xE0"): whether pos is over one of
 * the region's walkable triangles - ItriNav (0x1BF110) on its +0xE0 part, as a flag. */
typedef int qword __attribute__((mode(TI)));   /* a VU_VECTOR in one register */
typedef struct NAV NAV;          /* the 2D BSP the named Nav functions work on */
typedef struct NAVSEG NAVSEG;
typedef struct VECTOR VECTOR;
typedef struct NAVREGION {
    /* 0x00 */ char pad0[0xe0];
    /* 0xe0 */ char nav[0x20];   /* its walkable area (BSP) */
} NAVREGION;
int ItriNav__FP9NAVREGIONG9VU_VECTORi(void *pnav, qword pos, int fl);

int func_001C0920(NAVREGION *preg, qword pos, int fl)
{
    return ItriNav__FP9NAVREGIONG9VU_VECTORi(preg->nav, pos, fl) != 0;
}
