// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* PowerOffCB (libcdvd): register the power-off SIF command handler (_sceCd_Poff_Intr). */
#define SIF_CMD_POWEROFF 0x80000012
extern int D_002C6764;              /* busy flag while the handler is being installed */
extern volatile int D_002C6788;     /* power-off handler installed */
int DIntr(void);
int sceSifAddCmdHandler(int, void *, int);
int EIntr(void);
void _sceCd_Poff_Intr(void);

int PowerOffCB(void)
{
    int intr;
    D_002C6764 = 1;
    intr = DIntr();
    sceSifAddCmdHandler(SIF_CMD_POWEROFF, _sceCd_Poff_Intr, 0);
    if (intr) EIntr();
    D_002C6764 = 0;
    D_002C6788 = 1;
    return 1;
}
