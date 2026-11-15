/* RegisterActorContacts: the base contacts, then the ledges of a jump, the interaction's and the climb's when that
 * part has a state (not -1). */
void func_001F4FA8(void *pactor);
void AddJumpLedgeContacts__FP5ACTOR(void *pactor);
void AddInteractContacts__FP5ACTOR(void *pactor);
void AddClimbContacts__FP5ACTOR(void *pactor);
// name: SafeHouse port (RegisterActorContacts)
void RegisterActorContacts__FP3ALO(char *pactor)
{
    func_001F4FA8(pactor);
    if (*(int *)(pactor + 0x2DC) /* jump state */ != -1) AddJumpLedgeContacts__FP5ACTOR(pactor + 0x2C0);
    if (*(int *)(pactor + 0x4CC) /* interaction state */ != -1) AddInteractContacts__FP5ACTOR(pactor + 0x4C0);
    if (*(int *)(pactor + 0xF54) /* climb state */ != -1) AddClimbContacts__FP5ACTOR(pactor + 0xF50);
}
