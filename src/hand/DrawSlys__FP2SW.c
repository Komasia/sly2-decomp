/* DrawSlys: Sly's draw: hanging from a hook (state 3) his cane is put on the hook first, then the actor draw. */
struct SLY {
    /* 0x0000 */ char pad0[0x18c8];
    /* 0x18c8 */ int state;   /* the actor state (3: hanging from a hook) */
};
void DrawSlyHangPlace(struct SLY *psly) asm("DrawSlyHangPlace__FP3SLY");
void DrawActor(struct SLY *psly) asm("DrawActor__FP5ACTOR");

// name: SafeHouse port (DrawSlys)
void DrawSlys__FP2SW(struct SLY *psly)
{
    if (psly->state == 3)
        DrawSlyHangPlace(psly);
    DrawActor(psly);
}
