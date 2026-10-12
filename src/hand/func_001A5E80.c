struct T { unsigned int x0; };
struct O;
struct S { char pad[0x10]; struct O *x10; char pad2[0x2C]; unsigned int x40; };
struct O { char pad[0x40]; struct T *x40; };
static inline void ClearFlag(struct S *p, unsigned int fl)
{
    unsigned int v = p->x40;
    if ((v ^ 1) & 1) *(unsigned int *)v &= ~fl;
    else p->x40 = v & ~fl;
}
void func_001A5E80(struct S *p)
{
    if (!p->x10 || !(p->x10->x40->x0 & 4)) ClearFlag(p, 4);
}
