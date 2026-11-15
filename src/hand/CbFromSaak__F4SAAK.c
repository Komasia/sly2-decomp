/* PabilFind (SafeHouse gang.cpp, orig 0x136A28; the Sly 1 name CbFromSaak is a shape match): the address of
 * Bentley's ability record of id saak (BENTLEY::aabil at +0x1824 + 0xC i: ids 5, 7, 9, 11, 13, 4), 0 for other ids. */
int CbFromSaak__F4SAAK(char *p, int saak)
{
    switch (saak) {
    case 5: return (int)(p + 0x1824);
    case 7: return (int)(p + 0x1830);
    case 9: return (int)(p + 0x183c);
    case 11: return (int)(p + 0x1848);
    case 13: return (int)(p + 0x1854);
    case 4: return (int)(p + 0x1860);
    }
    return 0;
}
