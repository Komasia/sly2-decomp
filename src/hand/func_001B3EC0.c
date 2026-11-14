struct S { char pad[0x10C]; int x10C; int x110; int x114; char x118[0x48]; char x160[0x20]; char x180[0x10]; };
extern int D_002E1E54, D_002DEDBC;
void Init__10CByteQueueiPv(void *pbq, int cb, unsigned int pv);
void func_001B3040(void *p);
int sceMpegInit(void);
void sceMpegCreate(void *p, int a, int b);
void sceMpegAddStrCallback(void *p, int a, int b, void *fn, struct S *s);
void sceMpegAddCallback(void *p, int a, void *fn, struct S *s);
int func_001B41D0(struct S *p, int n);
void func_001B3388(void);
void func_001B33C8(void);
void func_001B33F0(void);
void func_001B34D0(void);
void func_001B3508(void);
void func_001B3EC0(struct S *p, int a)
{
    p->x114 = a;
    p->x10C = 0;
    Init__10CByteQueueiPv(p->x160, 0x40000, (p->x110 + 0x245A80) | 0x20000000);
    func_001B3040(p->x180);
    sceMpegInit();
    sceMpegCreate(p->x118, p->x110 + 0x98000, 0x1ADA60);
    sceMpegAddStrCallback(p->x118, 0, 0, func_001B3388, p);
    sceMpegAddStrCallback(p->x118, 2, 0, func_001B33C8, p);
    sceMpegAddStrCallback(p->x118, 3, 0, func_001B33C8, p);
    sceMpegAddStrCallback(p->x118, 2, D_002E1E54 + 1, func_001B33C8, p);
    sceMpegAddStrCallback(p->x118, 3, D_002E1E54 + 1, func_001B33C8, p);
    sceMpegAddCallback(p->x118, 1, func_001B33F0, p);
    sceMpegAddCallback(p->x118, 4, func_001B34D0, p);
    sceMpegAddCallback(p->x118, 0, func_001B3508, p);
    while (!func_001B41D0(p, 1)) ;
    D_002DEDBC = 0;
}
