// name: SafeHouse port (gadget.h NActorPower, orig 0x1441A0)
int NActorPower__FP5ACTOR(char *p)
{
    int *q = *(int **)(p + 0x12FC);
    if (!q) return *(int *)(p + 0x1300);
    return *q;
}
