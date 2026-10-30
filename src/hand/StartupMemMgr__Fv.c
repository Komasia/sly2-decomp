extern char D_0047220F;
extern void *D_002F6380, *D_002F6384, *D_002F6388, *D_002F638C;
extern int D_002F639C;
extern char D_002F6390;
void func_0021F028(void *p);
void StartupMemMgr(void) __asm__("StartupMemMgr__Fv");
void StartupMemMgr(void)
{
    void *end = (void *)((int)&D_0047220F & ~0x0f);
    D_002F6380 = D_002F6384 = end;
    D_002F6388 = D_002F638C = (void *)0x02000000;
    D_002F639C = -1;
    func_0021F028(&D_002F6390);
}
