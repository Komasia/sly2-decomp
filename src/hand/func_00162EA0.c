struct S { char pad[0x64]; void *f64; };
struct T { char pad[0x7C]; struct S *ps; };
extern struct T *D_003E0FA0;
extern char g_game[];
void ResetJob__FP3JOB(struct S *p);
void ChangeTaskState__FP4TASKi(void *p, int n);
void func_00163CE0(struct T *p);
void BroadcastTaskEvent__FP2SWiP2LO(void *p, int n, struct S *ps);
void func_00162908(struct S *p);
// name: SafeHouse port (RestartJob)
void RestartJob__FP3JOB(struct S *p)
{
    ResetJob__FP3JOB(p);
    ChangeTaskState__FP4TASKi(p->f64, 1);
    if (D_003E0FA0 && D_003E0FA0->ps == p)
        func_00163CE0(D_003E0FA0);
    BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x1F, p);
    func_00162908(p);
}
