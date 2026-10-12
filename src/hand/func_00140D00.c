void func_001F4FA8(void *p);
void func_001991A0(void *p);
void func_00193DE8(void *p);
void func_0019E950(void *p);
void func_00140D00(char *p)
{
    func_001F4FA8(p);
    if (*(int *)(p + 0x2DC) != -1) func_001991A0(p + 0x2C0);
    if (*(int *)(p + 0x4CC) != -1) func_00193DE8(p + 0x4C0);
    if (*(int *)(p + 0xF54) != -1) func_0019E950(p + 0xF50);
}
