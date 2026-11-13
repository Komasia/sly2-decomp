/* The AI job stack (SafeHouse aijob.cpp, orig 0x1EF0D8: a handle's vt slot 9, then 0x1EEED0 on the owner's stack):
 * the count +0x4 lowered. */
struct JOBSTACK {
    /* 0x0 */ void *p0;
    /* 0x4 */ int c;
};

void func_001EEED0(struct JOBSTACK *pstack)
{
    pstack->c--;
}
