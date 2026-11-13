struct CLOCK { float t; char pad[0x3C]; float g40; };
struct CM { char pad[0x100]; float g100; char pad1[0x10]; float g114; };
struct P { char pad[0x110]; char a110[0x20]; char a130[0x10]; char a140[0x10]; char a150[0x10]; char pad1[0x1A0 - 0x160]; int x1A0;
    char pad2[0x1B0 - 0x1A4]; char a1B0[0x3B0 - 0x1B0]; int x3B0; char a3B4[0x434 - 0x3B4]; int x434; void *p438; int x43C; float g440; };
extern struct CLOCK g_clock;
extern struct CM g_cm;
extern char D_002DEA28[];
void UnpackHelper(void *pdma, int a, int b, int c, int d, void *ppv) asm("UnpackHelper__4VIFS3UPKiiPiPPUi");
void AddVifUnpack(void *pdma, int a, int b, void *pv, int d) asm("AddVifUnpack__4VIFS3UPKiPvi");
void AddVifUnpackRefs(void *pdma, int a, int b, void *pv, int d, int e) asm("AddVifUnpackRefs__4VIFS3UPKiPviPPPv");
void func_0013A688(struct P *p)
{
    float *pg;
    int *pn;
    char *pdma = D_002DEA28;
    struct CLOCK *pclock;
    UnpackHelper(pdma, 0xC, 1, 5, 0, &pg);
    pclock = &g_clock;
    pg[0] = g_cm.g100;
    pg[1] = g_cm.g114;
    pg[2] = p->g440;
    pg[3] = g_clock.t;
    UnpackHelper(pdma, 0xC, 1, 6, 0, &pn);
    pn[0] = 0;
    if (p->x434)
        pn[0] |= 1;
    pn[1] = p->x3B0;
    pn[2] = p->x1A0;
    *(float *)&pn[3] = pclock->g40;
    AddVifUnpack(pdma, 0xE, p->x3B0, p->a3B4, 0x30 - p->x3B0);
    AddVifUnpack(pdma, 8, 1, p->a130, 1);
    AddVifUnpack(pdma, 8, 1, p->a110, 2);
    AddVifUnpack(pdma, 8, 1, p->a140, 3);
    AddVifUnpack(pdma, 8, 1, p->a150, 4);
    AddVifUnpack(pdma, 0xC, 4, p->p438, 0x30);
    AddVifUnpackRefs(pdma, 0xC, p->x1A0, p->a1B0, 0xF, 0);
}
