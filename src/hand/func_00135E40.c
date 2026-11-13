struct S { char pad[0x13d0]; int st; };
int NActorPaused(struct S *) asm("NActorPaused__Fv");
int func_00135E40(struct S *p) {
    int r = NActorPaused(p);
    if (r != -1) return r;
    switch (p->st) {
    case 1: case 5: case 14: return 1;
    }
    return -1;
}
