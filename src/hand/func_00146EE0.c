void Exit__5AIJOB(void *p);
void func_001B6078(void *p, int n);
// name: SafeHouse port (JOBMURRAYRAGE::Exit)
void Exit__13JOBMURRAYRAGE(char *p)
{
    Exit__5AIJOB(p);
    *(int *)(*(char **)(p + 0x10) + 0x1AC0) = 0;
    func_001B6078(*(void **)(p + 0x10), 0);
}
