/* class: ZONE (SafeHouse cmworld.cpp: the getter of the current camera entry, for the entry's option fields). */
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

struct ZONECME *func_00221958(struct ZONE *pzone)
{
    return pzone->pcmeCur;
}
