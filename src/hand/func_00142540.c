/* SetActorFollow: the actor's AI jobs (+0x26C) cleared; with an object to follow, a new follow job (0xC2) with it and
 * the vector, started (vt slot 8). */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct JOB { char pad[0xC]; VTENT *vt; char pad2[0x30 - 0x10]; int ploFollow; char pad3[0x40 - 0x34]; qword vec; };
void ClearJobs__FP5ACTOR(void *pactor);
struct JOB *func_00205438(void *pactor, int n);
// name: SafeHouse port (SetActorFollow)
void SetActorFollow__FP5ACTORiG9VU_VECTOR(char *pactor, int ploFollow, qword vec)
{
    struct JOB *pjob;
    VTENT *e;
    ClearJobs__FP5ACTOR(pactor + 0x26C);
    if (ploFollow) {
        pjob = func_00205438(pactor, 0xC2);
        pjob->ploFollow = ploFollow;
        pjob->vec = vec;
        e = &pjob->vt[8];
        ((void (*)(void *))e->pfn)(VT_THIS(pjob, e));
    }
}
