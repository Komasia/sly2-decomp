/* class: ZONE, its camera options (SafeHouse cmworld.cpp: after the loader 0x220FD0's options, 0x221940): no current
 * entry. */
struct ZONECME {
    /* 0x00 */ char pad0[0x70];
    /* 0x70 */ float coefX;   /* SafeHouse port: vecCoefY = (g, g, 1) */
    /* 0x74 */ float coefY;
    /* 0x78 */ float coefZ;
};
struct ZONE {
    /* 0x000 */ char pad0[0x118];
    /* 0x118 */ struct ZONECME *pcmeCur;   /* the current camera entry */
};

void func_00221940(struct ZONE *pzone)
{
    pzone->pcmeCur = 0;
}
