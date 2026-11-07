typedef struct { short d; short pad; void *pfn; } VTE;
struct T { int a; int b; };
extern struct T D_002C3D98[2];
extern char g_game[];
struct S { char pad[0xC]; VTE *vt; char pad2[0x2C0 - 0x10]; long fl; };
struct L { int *pa; int *pb; };
long func_00207A20(int n);
void SetGuardStateMask__FP5GUARDUl(struct S *p, long fl);
int func_002099F0(long m, int a);
void BroadcastTaskEvent__FP2SWiP2LO(void *p, int b, struct S *ps);
// name: SafeHouse port (AddGuardState)
void AddGuardState__FP5GUARDi(struct S *p, int n)
{
    long m = func_00207A20(n);
    struct L l;
    int b;
    unsigned int i;
    SetGuardStateMask__FP5GUARDUl(p, p->fl | m);
    b = -1;
    l.pa = &n;
    l.pb = &b;
    ((void (*)(void *, int, int, int, struct L *, int))p->vt[3].pfn)((char *)p + p->vt[3].d, 7, 0, 2, &l, 0);
    for (i = 0; i < 2; i++) {
        if (func_002099F0(m, D_002C3D98[i].a))
            BroadcastTaskEvent__FP2SWiP2LO(g_game, D_002C3D98[i].b, p);
    }
}
