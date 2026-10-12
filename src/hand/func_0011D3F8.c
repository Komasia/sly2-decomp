int func_0011D3C0(void);

int func_0011D3F8(int nLow, int nHi)
{
    int nRand = func_0011D3C0();
    int nBase = nLow - 1;
    return nLow + nRand % (nHi - nBase);
}
