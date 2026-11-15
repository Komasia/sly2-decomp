/* StartupMemMgr (0x1AE168, Sly 1 memory.c): the world heap starts at the end of the executable (D_0047220F, aligned
 * down to 16), the stack heap is empty at 32 MB (0x2000000, growing down), no stack frames, the stack's critical
 * section. */
extern char g_bEnd __asm__("D_0047220F");  /* the end of the executable */
#define PV_RAM_TOP ((void *)0x02000000)
extern void *s_pvWorldMin, *s_pvWorldMac, *s_pvStackMin, *s_pvStackMac;
extern int s_ipvStackCur;
extern char s_critsectStack;
void InitCritSect(void *p) asm("InitCritSect__FP8CRITSECT");
void StartupMemMgr(void) __asm__("StartupMemMgr__Fv");
void StartupMemMgr(void)
{
    void *end = (void *)((int)&g_bEnd & ~0x0f);
    s_pvWorldMin = s_pvWorldMac = end;
    s_pvStackMin = s_pvStackMac = PV_RAM_TOP;
    s_ipvStackCur = -1;
    InitCritSect(&s_critsectStack);
}
