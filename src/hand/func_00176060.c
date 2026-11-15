struct GUARD { char pad[0x3CC]; void *ptargetrec; int pad2; int fSees; };
struct JOBPURSUE { char pad[0x10]; struct GUARD *pguard; char pad2[0x2C]; int fActing; };
int FTargetrecExpired__FP9TARGETREC(void *pjob);
/* JOBPURSUE::FLost: whether the pursued target is lost: not while acting (+0x40) or while the guard still sees it
 * (+0x3D4), else when its target record expired. */
// name: SafeHouse port (JOBPURSUE::FLost)
int FLost__9JOBPURSUE(struct JOBPURSUE *pjob) { int fLost; if (pjob->fActing) fLost = 0; else if (pjob->pguard->fSees) fLost = 0; else fLost = FTargetrecExpired__FP9TARGETREC(pjob->pguard->ptargetrec); return fLost; }
