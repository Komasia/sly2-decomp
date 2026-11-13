struct S { char pad[0xE0]; int a; int b; char c[0x10]; char d[4]; };
void LoadLoxBaseFromBrx(struct S *p, void *q);
int U32Read(void *q) asm("U32Read__18CBinaryInputStream");
void func_00117FD0(void *q, void *a);
void func_00118220(void *q, void *a, void *b);
void LoadOptionsFromBrx__FPvP18CBinaryInputStream(struct S *p, void *q);
// name: SafeHouse port (LoadVolumeFromBrx)
void LoadVolumeFromBrx__FP2LOP18CBinaryInputStream(struct S *p, void *q)
{
    LoadLoxBaseFromBrx(p, q);
    p->a = U32Read(q);
    func_00117FD0(q, p->d);
    func_00118220(q, p->d, p->c);
    LoadOptionsFromBrx__FPvP18CBinaryInputStream(p, q);
}
