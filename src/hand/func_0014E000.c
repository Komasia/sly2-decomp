struct T { char pad[0xE4]; int nE4; char pad2[0x110 - 0xE8]; int n110; float g114; char pad3[0x120 - 0x118]; };
int func_0014E000(struct T **ppa, struct T **ppb)
{
    struct T *a = *ppa;
    struct T *b = *ppb;
    int d = b->n110 - a->n110;
    if (d) return d;
    d = b->nE4 - a->nE4;
    if (d) return d;
    if (a->g114 < b->g114) return -1;
    if (b->g114 < a->g114) return 1;
    return a - b;
}
