/* The world's current task (SafeHouse task.cpp SetTaskCur, orig 0x00165DC0 / 0x00165DE8 / 0x00165E10): SW +0x3B14 and its
 * oid kept in D_002DEB48 (-1: none). */
struct TASK {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ int oid;
};
struct SW {
    /* 0x0000 */ char pad0[0x3b14];
    /* 0x3b14 */ struct TASK *ptaskCur;
};
extern int D_002DEB48;   /* the current task's oid */

void func_00165E10(struct SW *psw, struct TASK *p)
{
    psw->ptaskCur = p;
    if (p != 0) {
        D_002DEB48 = p->oid;
        return;
    }
    D_002DEB48 = -1;
}
