struct S { char pad[0x68]; void *f68; char pad2[0x78 - 0x6C]; int f78; };
extern char g_game[];
extern char D_002E65E0[];
void ChangeTaskState__FP4TASKi(void *p, int n);
void BroadcastTaskEvent__FP2SWiP2LO(void *p, int n, struct S *ps);
void func_00162908(struct S *p);
void HudAutoSave(void *p, int n) asm("HudAutoSave__FP4SAVEi");
// name: SafeHouse port (JobCompleteClose)
void JobCompleteClose__FP3JOB(struct S *p)
{
    if (!p->f78)
        ChangeTaskState__FP4TASKi(p->f68, 3);
    BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x20, p);
    func_00162908(p);
    if (!p->f78)
        HudAutoSave(D_002E65E0, 0);
}
