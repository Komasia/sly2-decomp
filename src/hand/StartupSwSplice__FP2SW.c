/* StartupSwSplice: the world's splice side on (+0x3A14) with a new root frame (its CRefPtr at +0), added to the
 * garbage collector's roots. Layout: SafeHouse port (splicemap.h SWSPLICE). */
struct CFrame;
struct SW {
    /* 0x0000 */ struct CFrame *pframe;   /* field: SafeHouse port */
    /* 0x0004 */ char pad4[0x3a14 - 0x4];
    /* 0x3a14 */ int fOn;                 /* field: SafeHouse port */
};
struct CFrame *PframeNew(void) asm("PframeNew__Fv");
void func_00256EE0(struct CFrame **ppframe, struct CFrame *pframe);   /* CRefPtr<CFrame> assignment */
void AddRootFrame(struct CFrame *pframe) asm("AddRootFrame__3CGc");

// name: SafeHouse port (StartupSwSplice)
void StartupSwSplice__FP2SW(struct SW *psw)
{
    psw->fOn = 1;
    func_00256EE0(&psw->pframe, PframeNew());
    AddRootFrame(psw->pframe);
}
