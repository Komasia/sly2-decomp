struct CLOCK { float t; };
extern struct CLOCK g_clock;
struct S { char pad[0x4CC]; int x4CC; char pad1[0x1080 - 0x4D0]; float t1080; char pad2[0x10E4 - 0x1084]; int x10E4; char pad3[0x13D0 - 0x10E8]; int k; };
void GetActorCmTarget__FP5ACTORP9ACTORPOSE(struct S *p, int *pf);
void GetJtThrowCpdefi__FP7JTTHROWP6CPDEFI(void *p, int *pf);
void func_0019EA00(void *p, int *pf);
// name: SafeHouse port (GetMurrayCpdefi)
void GetMurrayCpdefi__FP6MURRAYP9ACTORPOSE(struct S *p, int *pf)
{
    if (p->k != 0 && p->k != 16 && p->x4CC) p->t1080 = g_clock.t;
    GetActorCmTarget__FP5ACTORP9ACTORPOSE(p, pf);
    switch (p->k) {
    case 11:
        if (p->x10E4 != 4) break;
    case 3: case 9: case 12:
        *pf |= 1;
        break;
    case 15: GetJtThrowCpdefi__FP7JTTHROWP6CPDEFI((char *)p + 0x1910, pf); break;
    case 20: func_0019EA00((char *)p + 0xF50, pf); break;
    }
}
