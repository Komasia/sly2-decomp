/* func_002097E0 (0x2097E0): MOVEREF update: the current move job steers (its vt slot 11). */
#include "vtbl.h"
struct AIJOB { int unk_0x00, unk_0x04, unk_0x08; VTENT *pvt; };
void func_002097E0(struct AIJOB **ppjob) { struct AIJOB *pjob = *ppjob; if (pjob) { VTENT *pvte = &pjob->pvt[11]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjob, pvte)); } }
