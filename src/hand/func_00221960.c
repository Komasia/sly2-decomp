/* class: ZONE (SafeHouse cmworld.cpp: option 190 of the current camera entry, (g, g, 1) at +0x70). */
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

void func_00221960(struct ZONE *pzone, float g)
{
    struct ZONECME *pcme = pzone->pcmeCur;
    pcme->coefY = g;
    pcme->coefX = g;
    pzone->pcmeCur->coefZ = 1.0f;
}
