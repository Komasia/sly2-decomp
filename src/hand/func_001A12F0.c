struct G { char pad[0x1030]; int x1030; };
struct S { struct G *pg; int n; };
int FAsegaRetracted(int) asm("FAsegaRetracted__FP5ASEGA");
void EndDamageReaction__FP5ACTOR(struct S *);
// name: SafeHouse port (UpdateDamageTransitions)
void UpdateDamageTransitions__FP5ACTOR(struct S *p)
{
    int n;
    do {
        n = p->n;
        if (FAsegaRetracted(p->pg->x1030))
            EndDamageReaction__FP5ACTOR(p);
    } while (p->n != -1 && p->n != n);
}
