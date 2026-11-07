struct M { int cb; int a; };
struct S { char pad[0x144]; int x; int c; int *a; };
void LoadShapeFromBrx__FP5SHAPEP18CBinaryInputStream(struct S *p, void *q);
void LoadKeyRecordFromBrx__FP18CBinaryInputStreamPUc(void *q, int *p);
int func_00117BD0(void *q);
int *PvAllocSwImpl__Fi(struct M *pm);
// name: SafeHouse port (LoadShapeKeysFromBrx)
void LoadShapeKeysFromBrx__FP2LOP18CBinaryInputStream(struct S *p, void *q)
{
    int i = 0;
    int n;
    struct M m;
    LoadShapeFromBrx__FP5SHAPEP18CBinaryInputStream(p, q);
    LoadKeyRecordFromBrx__FP18CBinaryInputStreamPUc(q, &p->x);
    n = func_00117BD0(q);
    m.a = 0x10;
    m.cb = n * 4;
    p->c = n;
    p->a = PvAllocSwImpl__Fi(&m);
    for (; i < p->c; i++) LoadKeyRecordFromBrx__FP18CBinaryInputStreamPUc(q, &p->a[i]);
}
