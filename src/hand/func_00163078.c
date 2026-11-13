struct S { char pad[0xB0]; int fb0; int fb4; void *fb8; void *fbc; void *fc0; int fc4; char pad2[0xCC - 0xC8]; void *fcc; };
void UpdateLo__FP2LO(struct S *p);
int FSpriteAnimPlaying__FP2LOi(void *p, int n);
void JobCompleteClose__FP3JOB(struct S *p);
void JobCompleteNext(struct S *p) asm("JobCompleteNext__FP3JOB");
void SetJobSeq__FP3JOBi(struct S *p, int n);
// name: SafeHouse port (UpdateJob)
void UpdateJob__FP2LO(struct S *p)
{
    UpdateLo__FP2LO(p);
    switch (p->fc4) {
    case 1:
        if (!FSpriteAnimPlaying__FP2LOi(p->fb8, p->fb0)) {
            JobCompleteClose__FP3JOB(p);
            if (p->fc0 || p->fcc)
                SetJobSeq__FP3JOBi(p, 3);
            else
                SetJobSeq__FP3JOBi(p, 2);
        }
        break;
    case 2:
        if (!FSpriteAnimPlaying__FP2LOi(p->fb8, p->fb4)) {
            JobCompleteNext(p);
            SetJobSeq__FP3JOBi(p, 0);
        }
        break;
    case 3:
        if (!FSpriteAnimPlaying__FP2LOi(p->fbc, 0x30F))
            JobCompleteNext(p);
        break;
    }
}
