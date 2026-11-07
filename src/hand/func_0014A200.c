void Enter__5AIJOB(void *p);
void SetState__8JOBCHASEi(void *p, int n);
extern float g_clock;
// name: SafeHouse port (JOBCHASE::Enter)
void Enter__8JOBCHASE(char *p)
{
    Enter__5AIJOB(p);
    SetState__8JOBCHASEi(p, 0);
    *(float *)(p + 0x48) = g_clock;
    *(int *)(*(char **)(p + 0x10) + 0x4A4) = 0;
}
