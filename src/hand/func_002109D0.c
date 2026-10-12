struct X { char pad[8]; int x8; char padc[0x2C]; int x38; };
extern int D_003E1C38;
struct X *func_00210990(int i);
static inline int FEqual(struct X *a, struct X *b)
{
    if (a == b)
        return 1;
    if (!a || !b)
        return 0;
    return (a->x8 ^ a->x38) == (b->x8 ^ b->x38);
}
int func_002109D0(struct X *px)
{
    int i;
    for (i = 0; i < D_003E1C38; i++) {
        if (FEqual(px, func_00210990(i)))
            return i;
    }
    return -1;
}
