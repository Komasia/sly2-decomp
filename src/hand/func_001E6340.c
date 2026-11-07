struct Q { char pad[0x4C]; int st; };
struct S { char pad[0x17C]; struct Q *pq; };
void StepRopeSpring__FP4ROPE(struct Q *q);
void StepRopeTrail__FP4ROPE(struct Q *q);
void func_001A5E80(struct S *p);
// name: SafeHouse port (UpdatePath17)
void UpdatePath17__FP2LO(struct S *p)
{
    if (p->pq) {
        switch (p->pq->st) {
        case 0:
        case 3:
            StepRopeSpring__FP4ROPE(p->pq);
            break;
        case 1:
        case 2:
            StepRopeTrail__FP4ROPE(p->pq);
            break;
        }
    } else {
        func_001A5E80(p);
    }
}
