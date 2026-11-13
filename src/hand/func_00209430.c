struct O { char pad[0x30]; int n30; };
struct E { int k; int h; struct O *po; };
int FAsegaRetracted(struct O *po) asm("FAsegaRetracted__FP5ASEGA");
int func_001F0638(struct O *po);
int func_0020C0D8(struct O *po);
int func_0020CA98(struct O *po);
// name: SafeHouse port (FKindeDone)
int FKindeDone__FP5KINDE(struct E *pe)
{
    int f;
    switch (pe->k) {
    case 0:
        f = 0;
        if (!pe->po || FAsegaRetracted(pe->po))
            f = 1;
        break;
    case 1:
        f = 0;
        if (!pe->po || func_001F0638(pe->po) || !pe->po->n30)
            f = 1;
        break;
    case 2:
        f = 0;
        if (!pe->po || func_0020C0D8(pe->po))
            f = 1;
        break;
    case 3:
        f = 0;
        if (!pe->po || func_0020CA98(pe->po))
            f = 1;
        break;
    case -1:
    default:
        f = 1;
        break;
    }
    return f;
}
