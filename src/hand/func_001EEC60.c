/* class: the AI job stack (SafeHouse aijob.cpp: the stack 0x1EEC60..0x1EF850; called by InitStep for the actor's
 * +0x26C stack): its first word set. */
struct JOBSTACK {
    /* 0x0 */ void *p0;
};

void func_001EEC60(struct JOBSTACK *pstack, void *p)
{
    pstack->p0 = p;
}
