/* func_001A5E80 (0x1A5E80): LO vt slot 17, the base: clears bit 2 of the LO's +0x40 flags (held in the word or
 * through the pointer it holds when bit 0 is clear) unless its parent has that bit. */
struct T { unsigned int x0; };
struct O;
struct S { char pad[0x10]; struct O *x10; char pad2[0x2C]; unsigned int x40; };
struct O { char pad[0x40]; struct T *x40; };
static inline void ClearFlag(struct S *plo, unsigned int fl)
{
    unsigned int v = plo->x40;
    if ((v ^ 1) & 1) *(unsigned int *)v &= ~fl;
    else plo->x40 = v & ~fl;
}
#define GRF40_4 4
void func_001A5E80(struct S *plo)
{
    if (!plo->x10 || !(plo->x10->x40->x0 & GRF40_4)) ClearFlag(plo, GRF40_4);
}
