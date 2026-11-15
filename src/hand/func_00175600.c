struct JOBACT { char pad[0x18]; void *pchild; char pad2[0x18]; int st; char pad3[8]; int fTriggered; };
void Update__5AIJOB(struct JOBACT *pjob);
int FJobDone(struct JOBACT *pjob) asm("FJobDone__FP5AIJOB");
int func_00174FB8(void *pjob);
void SetActState__6JOBACTi(struct JOBACT *pjob, int stNew);
/* JOBACT::Update: while not done: acting (0) goes on to 1 once triggered (+0x40), either ends (-1) when the child
 * move is done. */
// name: SafeHouse port (JOBACT::Update)
void Update__6JOBACT(struct JOBACT *pjob) {
    int stOld;
    Update__5AIJOB(pjob);
    do {
        if (FJobDone(pjob)) return;
        stOld = pjob->st;
        switch (stOld) {
        case 0:
            if (pjob->fTriggered) SetActState__6JOBACTi(pjob, 1);
            else if (func_00174FB8(pjob->pchild)) SetActState__6JOBACTi(pjob, -1);
            break;
        case 1:
            if (func_00174FB8(pjob->pchild)) SetActState__6JOBACTi(pjob, -1);
            break;
        }
    } while (stOld != pjob->st);
}
