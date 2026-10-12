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
void func_001A6E80(struct S *p, int f)
{
    if (f) SetFlag(p, 8);
    else ClearFlag(p, 8);
}
