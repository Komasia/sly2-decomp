struct CRITSECT { int cEnter; int thread; int sema; };
extern "C" int GetThreadId(void);
extern "C" int WaitSema(int sema) asm("WaitSema");

void EnterCritSect(CRITSECT *pcritsect)
{
    int threadId = GetThreadId();

    if (threadId != pcritsect->thread)
    {
        WaitSema(pcritsect->sema);
        pcritsect->thread = threadId;
        pcritsect->cEnter = 1;
    }
    else
    {
        pcritsect->cEnter++;
    }
}
