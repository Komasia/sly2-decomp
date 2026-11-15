/* SetLoVisible (0x1A6E80): sets or clears the visible bit (bit 3) of the LO's +0x40 flags (held in the word, or
 * through the pointer it holds when bit 0 is clear). SafeHouse activate.h. */
struct S { char pad[0x40]; unsigned int x40; };
static inline void SetFlag(struct S *p, unsigned int fl)
{
    unsigned int v = p->x40;
    if ((v ^ 1) & 1) *(unsigned int *)v |= fl;
    else p->x40 = v | fl;
}
static inline void ClearFlag(struct S *p, unsigned int fl)
{
    unsigned int v = p->x40;
    if ((v ^ 1) & 1) *(unsigned int *)v &= ~fl;
    else p->x40 = v & ~fl;
}
// name: SafeHouse port (activate.h SetLoVisible, orig 0x1A6E80, vt slot 21)
#define GRF40_VISIBLE 8
void SetLoVisible__FP2LOi(struct S *plo, int fVisible)
{
    if (fVisible) SetFlag(plo, GRF40_VISIBLE);
    else ClearFlag(plo, GRF40_VISIBLE);
}
