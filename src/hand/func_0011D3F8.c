int NRandom(void) asm("NRandom__Fv");

int NRandInRange__Fii(int nLow, int nHi)
{
    int nRand = NRandom();
    int nBase = nLow - 1;
    return nLow + nRand % (nHi - nBase);
}
