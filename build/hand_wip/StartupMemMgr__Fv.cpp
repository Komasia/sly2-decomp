struct CRITSECT { int a[3]; };
extern char D_0047220F;
extern void *D_002F6380, *D_002F6384, *D_002F6388, *D_002F638C;
extern int D_002F639C;
extern CRITSECT D_002F6390;
void InitCritSect(CRITSECT *p);
void StartupMemMgr()
{
    void *end = (void *)((int)&D_0047220F & ~0x0f);
    D_002F6380 = end; //P
    D_002F6384 = end; //P
    D_002F6388 = (void *)0x02000000; //P
    D_002F638C = (void *)0x02000000; //P
    D_002F639C = -1; //P
    InitCritSect(&D_002F6390);
}
