/* The world's current job (SafeHouse task.cpp SetJobCur, orig 0x00165DC0 / 0x00165DE8 / 0x00165E10): SW +0x3B10 and its
 * oid kept in D_002DEB44 (-1: none). */
struct JOB {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ int oid;
};
struct SW {
    /* 0x0000 */ char pad0[0x3b10];
    /* 0x3b10 */ struct JOB *pjobCur;
};
extern int D_002DEB44;   /* the current job's oid */

void func_00165DE8(struct SW *psw, struct JOB *p)
{
    psw->pjobCur = p;
    if (p != 0) {
        D_002DEB44 = p->oid;
        return;
    }
    D_002DEB44 = -1;
}
