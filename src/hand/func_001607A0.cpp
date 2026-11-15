// func_001607A0 (Sly 1 frm.c StartupFrame): start the frame system: the VU1 interrupt handler (func_00167F78 on
// interrupt 5), the two frame semaphores (frames to render: 0 of 2; frames free: 2 of 2), the two pending-release
// lists of the open frame (objects linked at +0x454, buffers at +0x1090) and the render thread.
#include "dl.h"
extern "C" void func_00234700(int intc, int (*pfn)(), int next);   /* add an interrupt handler */
extern "C" void func_00235178(int intc);                          /* enable the interrupt */
extern "C" void InitDl(DL *pdl, int ib) asm("InitDl__FP2DLi");
extern "C" void StartThread_2355E0(int tid, int arg) asm("StartThread_2355E0");
extern "C" int func_00167F78();
int SemaCreate(int cInit, int cMax);
extern int D_002DEB18;   /* frames to render */
extern int D_002DEB1C;   /* frames free to build */
extern DL D_002DEAF0;    /* objects to release after the frame */
extern DL D_002DEB00;    /* buffers to free after the frame */
extern int D_004425D4;   /* the render thread */
extern "C" void func_001607A0()
{
    func_00234700(5, func_00167F78, 0);
    func_00235178(5);
    D_002DEB18 = SemaCreate(0, 2);
    D_002DEB1C = SemaCreate(2, 2);
    InitDl(&D_002DEAF0, 0x454);
    InitDl(&D_002DEB00, 0x1090);
    StartThread_2355E0(D_004425D4, 0);
}
