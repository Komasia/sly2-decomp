extern char D_0047220F;
extern void *s_pvWorldMin, *s_pvWorldMac, *s_pvStackMin, *D_002F638C;
extern int s_ipvStackCur;
extern char s_critsectStack;
void func_0021F028(void *p);
void StartupMemMgr(void) __asm__("StartupMemMgr__Fv");
void StartupMemMgr(void)
{
    void *end = (void *)((int)&D_0047220F & ~0x0f);
    s_pvWorldMin = s_pvWorldMac = end;
    s_pvStackMin = D_002F638C = (void *)0x02000000;
    s_ipvStackCur = -1;
    func_0021F028(&s_critsectStack);
}
