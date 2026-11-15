/* func_00165C28: the qsort order of tasks (job help order): by job depth, then their job's oid (-1: none), then
 * depth, then oid. */
struct JOB { char pad[0x18]; int oid; };
struct TASK { char pad[0x18]; int oid; char pad2[0x7C - 0x1C]; struct JOB *pjob; char pad3[0x100 - 0x80]; int nDepth; int nJobDepth; };
int func_00165C28(struct TASK **pptask1, struct TASK **pptask2)
{
    struct TASK *ptask1 = *pptask1;
    struct TASK *ptask2 = *pptask2;
    int n1, n2;
    if (ptask1->nJobDepth != ptask2->nJobDepth) return ptask1->nJobDepth - ptask2->nJobDepth;
    n1 = ptask1->pjob ? ptask1->pjob->oid : -1;
    n2 = ptask2->pjob ? ptask2->pjob->oid : -1;
    if (n1 != n2) return n1 - n2;
    if (ptask1->nDepth != ptask2->nDepth) return ptask1->nDepth - ptask2->nDepth;
    return ptask1->oid - ptask2->oid;
}
