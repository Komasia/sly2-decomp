typedef unsigned int uint;
uint NLog2(uint value)
{
    uint log2 = 0;
    uint bit = 1;
    while (bit < value && log2 < 31)
    {
        bit <<= 1;
        log2++;
    }
    return log2;
}
