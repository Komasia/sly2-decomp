struct GUARD { char pad[0x58]; int pxf58; int pxf5C; };
struct JOBSTAND { char pad[0x10]; struct GUARD *pguard; char pad2[0x24]; int ploFace; };
void Exit__7JOBMOVE(struct JOBSTAND *pjob);
void SetXfMode__FP3ALOP2XFi(struct GUARD *pguard, int pxf, int xfm);
/* JOBSTAND::Exit: the base exit, the guard's +0x58 transform back to mode 2, and +0x5C too unless the stand faced an
 * object. */
// name: SafeHouse port (JOBSTAND::Exit)
void Exit__8JOBSTAND(struct JOBSTAND *pjob) { Exit__7JOBMOVE(pjob); SetXfMode__FP3ALOP2XFi(pjob->pguard, pjob->pguard->pxf58, 2); if (!pjob->ploFace) SetXfMode__FP3ALOP2XFi(pjob->pguard, pjob->pguard->pxf5C, 2); }
