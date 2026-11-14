extern char D_002DA9D0[];
struct P { char pad[0x30]; int n30; };
struct O { int n0; int n4; int pad8; void *pC; char pad10[0x10]; int n20; int h24; struct P *p28; int *p2C; int n30; char pad34[0xC]; };
void *s1_memset(void *p, int c, int n) asm("memset");
void ApplyAsegCur(int a, int b, int c, int *ph, float f, float g) asm("ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA");
void func_001333C0(int h, struct O *po);
// name: SafeHouse port (StartK3)
void StartK3__FP5KIND3iiP6K3PLAY(struct P *p, int a, int b, struct O *po)
{
    s1_memset(po, 0, sizeof(*po));
    s1_memset(po, 0, sizeof(*po));
    po->p28 = p;
    po->n20 = a;
    po->pC = D_002DA9D0;
    po->n30 = b;
    po->n0 = 0;
    po->n4 = 0;
    ApplyAsegCur(p->n30, a, b, &po->h24, 0.0f, 1.0f);
    func_001333C0(po->h24, po);
    po->p2C = &p->n30;
}
