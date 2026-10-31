extern char D_0047220F;
extern void *s_pvWorldMin, *s_pvWorldMac, *s_pvStackMin, *s_pvStackMac;
extern int s_ipvStackCur;
extern char s_critsectStack;
void func_0021F028(void *p);
void StartupMemMgr(void) __asm__("StartupMemMgr__Fv");
void StartupMemMgr(void)
{
    void *end = (void *)((int)&D_0047220F & ~0x0f);
    s_pvWorldMin = s_pvWorldMac = end;
    s_pvStackMin = s_pvStackMac = (void *)0x02000000;
    s_ipvStackCur = -1;
    func_0021F028(&s_critsectStack);
}
