/* func_00162448: a job's Init (class 132 / 0x84 JOB, virtual slot 6): the LO Init, the suck times 480 / 720 s,
 * no name / description strings and no oidAC..nB4, then its +0x80 part (0x11A050, 0x84). Field names: SafeHouse
 * task.h JOB (field: SafeHouse port). */
#include "so.h"

void InitLo__FP2LO(LO *p);
void func_0011A050(void *, int);

typedef struct JOB {
    /* 0x000 */ LO lo;
    /* 0x050 */ char unk_0x50[0x1c];
    /* 0x06c */ int idName;
    /* 0x070 */ int idDesc;
    /* 0x074 */ char unk_0x74[0xc];
    /* 0x080 */ char unk_0x80[0x1c];
    /* 0x09c */ float tSuckStart;
    /* 0x0a0 */ float tSuckEnd;
    /* 0x0a4 */ char unk_0xa4[0x8];
    /* 0x0ac */ int oidAC;
    /* 0x0b0 */ int nB0;
    /* 0x0b4 */ int nB4;
} JOB;

void func_00162448(JOB *pjob)
{
    InitLo__FP2LO(&pjob->lo);
    pjob->tSuckStart = 480.0f;
    pjob->tSuckEnd = 720.0f;
    pjob->idName = -1;
    pjob->idDesc = -1;
    pjob->oidAC = -1;
    pjob->nB0 = -1;
    pjob->nB4 = -1;
    func_0011A050(pjob->unk_0x80, 0x84);
}
