struct E { int n; int a[11]; };
struct S { char pad[0x5C]; int c; struct E *ae; };
void OnLoRemove__FP2LO(struct S *p);
void ReleaseSlot__FP7SPAWNERP4SLOTii(struct S *p, struct E *pe, int a, int b);
// name: SafeHouse port (OnRemoveSpawner)
void OnRemoveSpawner__FP2LO(struct S *p) {
    int i;
    OnLoRemove__FP2LO(p);
    if (!p->ae) return;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i]; if (pe->n) ReleaseSlot__FP7SPAWNERP4SLOTii(p, pe, 0, 0);
    }
}
