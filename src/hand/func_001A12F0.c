struct G { char pad[0x1030]; int x1030; };
struct S { struct G *pg; int n; };
int func_00131968(int);
void EndDamageReaction__FP5ACTOR(struct S *);
// name: SafeHouse port (UpdateDamageTransitions)
void UpdateDamageTransitions__FP5ACTOR(struct S *p)
{
    int n;
    do {
        n = p->n;
        if (func_00131968(p->pg->x1030))
            EndDamageReaction__FP5ACTOR(p);
    } while (p->n != -1 && p->n != n);
}
