void func_001F4FA8(void *p);
void AddJumpLedgeContacts__FP5ACTOR(void *p);
void AddInteractContacts__FP5ACTOR(void *p);
void AddClimbContacts__FP5ACTOR(void *p);
// name: SafeHouse port (RegisterActorContacts)
void RegisterActorContacts__FP3ALO(char *p)
{
    func_001F4FA8(p);
    if (*(int *)(p + 0x2DC) != -1) AddJumpLedgeContacts__FP5ACTOR(p + 0x2C0);
    if (*(int *)(p + 0x4CC) != -1) AddInteractContacts__FP5ACTOR(p + 0x4C0);
    if (*(int *)(p + 0xF54) != -1) AddClimbContacts__FP5ACTOR(p + 0xF50);
}
