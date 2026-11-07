struct X { char pad[0x18]; float af[4]; };
void UpdateClockRate__FP5CLOCK(struct X *p);
// name: SafeHouse port (SetClockFactor)
void SetClockFactor__FP5CLOCKif(struct X *p, int i, float f)
{
    p->af[i] = f;
    UpdateClockRate__FP5CLOCK(p);
}
