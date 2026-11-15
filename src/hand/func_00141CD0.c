struct E { int a, b, c, d; int pad[4]; };
extern struct E D_002BCD00[];
extern float g_clock;
int NActorPower__FP5ACTOR(void *p);
void SetActorPower__FP5ACTORi(void *p, int a);
// name: SafeHouse port (gadget.h SpendActorPower, orig 0x141CD0)
void SpendActorPower__FP5ACTORi(char *p, int i)
{
    if (i != -1) SetActorPower__FP5ACTORi(p, NActorPower__FP5ACTOR(p) - D_002BCD00[i].d);
    *(float *)(p + 0x1304) = g_clock;
}
