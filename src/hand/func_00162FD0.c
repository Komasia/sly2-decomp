struct LO { char pad[0x40]; int fl; };
struct S { char pad[0xC0]; void *pc0; char pad2[0xCC - 0xC4]; struct LO *pcc; };
extern char D_002E1E88[];
int func_001A4E70(void *p);
void func_001A4E80(void *p);
void RequestTaskState__FP4TASKii(void *p, int n, struct S *ps);
void TriggerExit__FP4EXIT(struct LO *plo);
// name: SafeHouse port (task.cpp JobCompleteNext, "// 0x162FD0"; same body)
void JobCompleteNext(struct S *p) asm("JobCompleteNext__FP3JOB");
void JobCompleteNext(struct S *p)
{
    char *pv = D_002E1E88;
    if (func_001A4E70(pv)) {
        func_001A4E80(pv);
    } else if (p->pc0) {
        RequestTaskState__FP4TASKii(p->pc0, 4, p);
    } else if (p->pcc) {
        struct LO *plo = p->pcc;
        int v = plo->fl;
        if ((v ^ 1) & 1)
            *(int *)v |= 0x100;
        else
            plo->fl = v | 0x100;
        TriggerExit__FP4EXIT(p->pcc);
    }
}
