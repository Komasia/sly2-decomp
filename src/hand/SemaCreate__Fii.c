struct SemaParam { int count; int maxCount; int initCount; int numWaitThreads; unsigned int attr; unsigned int option; };
void *s1_memset(void *p, int c, int n);
int CreateSema(struct SemaParam *sp);
int SemaCreate__Fii(int initCount, int maxCount)
{
    struct SemaParam sp;
    s1_memset(&sp, 0, sizeof(sp));
    sp.initCount = initCount;
    sp.maxCount = maxCount;
    return CreateSema(&sp);
}
