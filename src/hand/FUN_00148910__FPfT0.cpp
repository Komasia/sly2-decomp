/* FUN_00148910 (Sly 1 coin.c, unnamed there too): qsort-style comparison of two floats, ascending (never 0). */
int FUN_00148910(float *pf0, float *pf1)
{
    return (*pf0 < *pf1) ? -1 : 1;
}
