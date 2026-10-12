struct SemaParam { int count; int maxCount; int initCount; int numWaitThreads; unsigned int attr; unsigned int option; };
void *func_002333B4(void *p, int c, int n);
int func_00234A20(struct SemaParam *sp);
int SemaCreate__Fii(int initCount, int maxCount)
{
    struct SemaParam sp;
    func_002333B4(&sp, 0, sizeof(sp));
    sp.initCount = initCount;
    sp.maxCount = maxCount;
    return func_00234A20(&sp);
}
