int FArrived__9JOBFOLLOW(void *p);
int func_00144EE8(char *p)
{
    char *q = *(char **)(p + 0x18);
    int r = 0;
    if (FArrived__9JOBFOLLOW(q) || *(int *)(q + 0x4C) == 2) r = 1;
    return r;
}
