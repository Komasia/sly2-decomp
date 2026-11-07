void func_001F4FA8(void *p);
void func_001991A0(void *p);
void AddInteractContacts__FP5ACTOR(void *p);
void func_0019E950(void *p);
// name: SafeHouse port (RegisterActorContacts)
void RegisterActorContacts__FP3ALO(char *p)
{
    func_001F4FA8(p);
    if (*(int *)(p + 0x2DC) != -1) func_001991A0(p + 0x2C0);
    if (*(int *)(p + 0x4CC) != -1) AddInteractContacts__FP5ACTOR(p + 0x4C0);
    if (*(int *)(p + 0xF54) != -1) func_0019E950(p + 0xF50);
}
