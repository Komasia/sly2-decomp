/* Sly 2 version takes a base pointer in $a0 and saak in $a1 and returns a pointer into it. */
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
