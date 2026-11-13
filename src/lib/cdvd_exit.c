// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// volatile store/load keep Sony's source order (store of -1 before the sema-id load)
extern int D_002C6754;
extern volatile int D_002C67A0;
extern int D_002C6760;
extern int D_002C6768;
extern int D_002C676C;
extern int D_002C6770;
int SignalSema(int);
int DeleteSema(int);
int DIntr(void);
int EIntr(void);
int sceSifRemoveCmdHandler(unsigned int);
void cdvd_exit(void)
{
    int r;
    if (D_002C6754) {
        D_002C67A0 = -1;
        SignalSema(*(volatile int *)&D_002C6760);
    }
    DeleteSema(D_002C6768);
    DeleteSema(D_002C676C);
    DeleteSema(D_002C6770);
    DeleteSema(D_002C6760);
    r = DIntr();
    sceSifRemoveCmdHandler(0x80000012);
    if (r) EIntr();
}
