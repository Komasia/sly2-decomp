/* class: JOBPURSUE (called by its Update): whether the job's +0x30 is unset (-1). */
typedef struct JOBPURSUE {
    /* 0x00 */ char pad0[0x30];
    /* 0x30 */ int n30;
} JOBPURSUE;

int func_0017B7F8(JOBPURSUE *pjob)
{
    return pjob->n30 == -1;
}
