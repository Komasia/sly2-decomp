struct S { char pad[0x38]; int *p; };
void SetBinocState__FP5ACTORi(struct S *, int);
// name: SafeHouse port (CloseBinoc)
void CloseBinoc__FP5ACTOR(struct S *p) {
    if (p->p) {
        switch (*p->p) {
        case 0: case 8: case 9: case 10: return;
        }
    }
    SetBinocState__FP5ACTORi(p, 2);
}
