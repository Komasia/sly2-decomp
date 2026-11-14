/* An object's group channel word (SafeHouse lo.h: +0x3C's entries, the group in the high half - 0x1C9950 reads it
 * back): the group and the index packed. */
int func_001C9940(int igroup, int i)
{
    return (igroup << 16) | (i & 0xFFFF);
}
