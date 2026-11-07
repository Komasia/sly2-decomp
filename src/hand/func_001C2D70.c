struct S { char pad[0x150]; char *p150; int x; void *p158; };
void RenderSoSelf__FP2SOP2CMP2RO(struct S *p);
void AppendAloExtraDraws__FP5SCENEP3ALOff(void *p, void *q, float a, float b);
// name: SafeHouse port (CollectPocketDraws)
void CollectPocketDraws__FP5SCENE(struct S *p)
{
    RenderSoSelf__FP2SOP2CMP2RO(p);
    if (p->p158) AppendAloExtraDraws__FP5SCENEP3ALOff(p->p158, p->p150 + 0x40, 1.0f, 1.0f);
}
