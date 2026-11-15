struct JOBMOVE { char pad[0x30]; int st; char pad2[0xC]; void *pkinde; };
void Update__5AIJOB(struct JOBMOVE *pjob);
int FKindeDone__FP5KINDE(void *pjob);
void SetMoveState__7JOBMOVEi(struct JOBMOVE *pjob, int n);
/* JOBMOVE::Update: while playing, end (state 1) when the kind entry is done. */
// name: SafeHouse port (JOBMOVE::Update)
void Update__7JOBMOVE(struct JOBMOVE *pjob) {
    int stOld;
    Update__5AIJOB(pjob);
    do {
        stOld = pjob->st;
        if (stOld == 0 && FKindeDone__FP5KINDE(pjob->pkinde)) SetMoveState__7JOBMOVEi(pjob, 1);
    } while (stOld != pjob->st);
}
