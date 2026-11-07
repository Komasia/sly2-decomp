struct S { char pad[0xF80]; int state; int arg; };
void PairActorWith__FP5ACTORP2LOi(struct S *p, int a, int b);
// name: SafeHouse port (DetachGuardMove)
void DetachGuardMove__FP5GUARD(struct S *p)
{
    switch (p->state) {
    case 0:
        PairActorWith__FP5ACTORP2LOi(p, p->arg, 0);
        break;
    case 1:
        PairActorWith__FP5ACTORP2LOi(p, p->arg, 0);
        break;
    case 2:
        PairActorWith__FP5ACTORP2LOi(p, p->arg, 0);
        break;
    case 3:
        PairActorWith__FP5ACTORP2LOi(p, p->arg, 0);
        break;
    }
    p->arg = 0;
    p->state = -1;
}
