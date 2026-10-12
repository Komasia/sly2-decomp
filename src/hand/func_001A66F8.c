struct S { char pad[0x40]; unsigned int x40; };
void func_001A66F8(struct S *p, unsigned int fl)
{
    unsigned int v = p->x40;
    if ((v ^ 1) & 1) *(unsigned int *)v &= ~fl;
    else p->x40 = v & ~fl;
}
