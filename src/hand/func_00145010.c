/* JOBCOMPANION::Init (AIJOB vt slot 7): the companion's defaults: no state, the follow point predicted 0.25 s ahead,
 * near / far distances 250 / 350 with animation speeds 1 / 1.2. Layout: SafeHouse port (actorai.h JOBCOMPANION). */
struct JOBCOMPANION {
    /* 0x00 */ char pad[0x60];
    /* 0x60 */ int st;           /* field: SafeHouse port */
    /* 0x64 */ float tSt;        /* field: SafeHouse port */
    /* 0x68 */ float dtPredict;  /* field: SafeHouse port */
    /* 0x6c */ float sNear;      /* field: SafeHouse port */
    /* 0x70 */ float sFar;       /* field: SafeHouse port */
    /* 0x74 */ float svNear;     /* field: SafeHouse port */
    /* 0x78 */ float svFar;      /* field: SafeHouse port */
};
void Init__5AIJOB(struct JOBCOMPANION *pjob);
// name: SafeHouse port (JOBCOMPANION::Init)
void Init__12JOBCOMPANION(struct JOBCOMPANION *pjob)
{
    Init__5AIJOB(pjob);
    pjob->st = -1;
    pjob->dtPredict = 0.25f;
    pjob->sNear = 250.0f;
    pjob->sFar = 350.0f;
    pjob->svNear = 1.0f;
    pjob->svFar = 1.2f;
}
