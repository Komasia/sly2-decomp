struct S { char pad[0x204]; int f204; char pad2[0x13d0 - 0x208]; int st; };
int GrfActorStance__FP5ACTOR(struct S *);
// name: SafeHouse port (GrfBentleyXp)
int GrfBentleyXp__FP3ALO(struct S *p) {
    if (p->f204) return 0;
    switch (p->st) {
    case 13: return 0;
    case 8: return 5;
    case 14: return 0xf;
    }
    return GrfActorStance__FP5ACTOR(p);
}
