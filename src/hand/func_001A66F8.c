/* func_001A66F8 (0x1A66F8): clears bits in the LO's +0x40 flags (held in the word, or through the pointer it holds
 * when bit 0 is clear); see func_001A66C8. */
struct S { char pad[0x40]; unsigned int x40; };
void func_001A66F8(struct S *plo, unsigned int fl)
{
    unsigned int v = plo->x40;
    if ((v ^ 1) & 1) *(unsigned int *)v &= ~fl;
    else plo->x40 = v & ~fl;
}
