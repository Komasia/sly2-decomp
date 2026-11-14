/* class: ZONE (SafeHouse cmworld.cpp: option 190's getter - the current camera entry's +0x70). */
struct ZONECME {
    /* 0x00 */ int n0;
    /* 0x04 */ char pad4[0x70 - 4];
    /* 0x70 */ float coefX;   /* SafeHouse port: vecCoefY = (g, g, 1) */
};
struct ZONE {
    /* 0x000 */ char pad0[0x118];
    /* 0x118 */ struct ZONECME *pcmeCur;   /* the current camera entry */
};

float func_00221980(struct ZONE *pzone)
{
    return pzone->pcmeCur->coefX;
}
