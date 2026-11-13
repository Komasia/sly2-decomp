struct O { char pad[0x30]; int n30; };
struct E { int k; int h; struct O *po; };
int FAsegaRetracted(struct O *po) asm("FAsegaRetracted__FP5ASEGA");
int FSmaRetracted(struct O *po) asm("FSmaRetracted__FP3SMA");
int FK2Done(struct O *po) asm("FK2Done__FP6K2PLAY");
int FK3Done(struct O *po) asm("FK3Done__FP6K3PLAY");
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
        if (!pe->po || FSmaRetracted(pe->po) || !pe->po->n30)
            f = 1;
        break;
    case 2:
        f = 0;
        if (!pe->po || FK2Done(pe->po))
            f = 1;
        break;
    case 3:
        f = 0;
        if (!pe->po || FK3Done(pe->po))
            f = 1;
        break;
    case -1:
    default:
        f = 1;
        break;
    }
    return f;
}
