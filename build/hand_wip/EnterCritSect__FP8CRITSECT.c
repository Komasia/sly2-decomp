struct CRITSECT { int cEnter; int thread; int sema; };
int func_00234910(void);
void func_00234A60(int sema);
void EnterCritSect__FP8CRITSECT(struct CRITSECT *pcritsect)
{
    int threadId = func_00234910();
    if (threadId != pcritsect->thread) {
        func_00234A60(pcritsect->sema);
        pcritsect->thread = threadId;
        pcritsect->cEnter = 1;
    } else {
        pcritsect->cEnter++;
    }
}
