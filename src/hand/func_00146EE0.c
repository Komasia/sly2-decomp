void func_001EEF78(void *p);
void func_001B6078(void *p, int n);
void func_00146EE0(char *p)
{
    func_001EEF78(p);
    *(int *)(*(char **)(p + 0x10) + 0x1AC0) = 0;
    func_001B6078(*(void **)(p + 0x10), 0);
}
