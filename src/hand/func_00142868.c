/* ActorSetLookFlag: the actor's looking around on or off (+0x1148), the next look choice never (FLT_MAX). */
struct ACTOR { char pad[0x1148]; int fLook; float tLookNext; };   /* field: SafeHouse port */
// name: SafeHouse port (ActorSetLookFlag)
void ActorSetLookFlag__FP5ACTORi(struct ACTOR *pactor, int fLook)
{
    pactor->fLook = fLook;
    pactor->tLookNext = 3.40282346638528859812e+38f;
}
