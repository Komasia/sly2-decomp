struct S { char pad[0x204]; int f204; char pad2[0x13D0-0x208]; int n; int reserved; int m; };
int GrfActorStance__FP5ACTOR(struct S *p);
// name: SafeHouse port (GrfMurrayXp)
int GrfMurrayXp__FP3ALO(struct S *p)
{
    if (p->f204) return 0;
    if (p->m == 1 || p->n == 20) return 0;
    return GrfActorStance__FP5ACTOR(p);
}
