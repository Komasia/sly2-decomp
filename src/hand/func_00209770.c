/* A step guard's sub-record (called by CloneStepguard__FP9STEPGUARD...): its +0xC object set. */
struct GUARDREC {
    /* 0x0 */ char pad0[0xc];
    /* 0xc */ void *pC;
};

void func_00209770(struct GUARDREC *prec, void *p)
{
    prec->pC = p;
}
