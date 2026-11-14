/* class: GUARD (SafeHouse guardstart.cpp: 0x103F40 -> 0x20A100, the guard's station - +0xF68 the object, +0xF70 the
 * point in its frame; a running station job (0x9C) in state 16 gets them too). */
typedef int qword __attribute__((mode(TI)));
struct LO;
struct JOBSTATIONREC {
    /* 0x00 */ char pad0[0x30];
    /* 0x30 */ struct LO *plo;
    /* 0x34 */ char pad34[0x40 - 0x34];
    /* 0x40 */ qword pos;
};
struct JOB9C {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ struct JOBSTATIONREC *prec;
    /* 0x1c */ char pad1c[0x30 - 0x1c];
    /* 0x30 */ int st;
};
struct GUARD {
    /* 0x000 */ char pad0[0x26c];
    /* 0x26c */ char stack[4];         /* SafeHouse port: the job stack */
    /* 0x270 */ char pad270[0xf68 - 0x270];
    /* 0xf68 */ struct LO *ploStation;   /* field: SafeHouse port */
    /* 0xf6c */ int padf6c;
    /* 0xf70 */ qword posStation;        /* field: SafeHouse port - in the object's frame */
};
struct JOB9C *PjobFind__FP5GUARDPv(void *pstack, int cid);

void func_0020A100(struct GUARD *pguard, struct LO *plo, qword pos)
{
    struct JOB9C *pjob;
    pguard->ploStation = plo;
    pguard->posStation = pos;
    pjob = PjobFind__FP5GUARDPv(pguard->stack, 0x9C);
    if (pjob != 0) {
        struct LO *ploStation = pguard->ploStation;
        if (ploStation != 0 && pjob->st == 0x10) {
            struct JOBSTATIONREC *prec = pjob->prec;
            prec->plo = ploStation;
            prec->pos = pguard->posStation;
        }
    }
}
