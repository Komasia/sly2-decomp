struct CRITSECT { int cEnter; int thread; int sema; };
extern "C" int GetThreadId(void);
extern "C" int func_00234A60(int sema);

void EnterCritSect(CRITSECT *pcritsect)
{
    int threadId = GetThreadId();

    if (threadId != pcritsect->thread)
    {
        func_00234A60(pcritsect->sema);
        pcritsect->thread = threadId;
        pcritsect->cEnter = 1;
    }
    else
    {
        pcritsect->cEnter++;
    }
}
