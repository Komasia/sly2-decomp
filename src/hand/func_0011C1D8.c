/* A 4x4 matrix transposed (SafeHouse bif.cpp: "matrix-transpose: 0x11C1D8, all of the 4x4"): 0x11C8E8 on 4 x 4. */
void func_0011C8E8(int crow, int ccol, void *pmatSrc, void *pmatDst);

void *func_0011C1D8(void *pmatDst, void *pmatSrc)
{
    func_0011C8E8(4, 4, pmatSrc, pmatDst);
    return pmatDst;
}
