struct S { char pad[0xB0]; int fb0; int fb4; void *fb8; void *fbc; void *fc0; int fc4; char pad2[0xCC - 0xC8]; void *fcc; };
void func_001A5E28(struct S *p);
int func_002121E8(void *p, int n);
void JobCompleteClose__FP3JOB(struct S *p);
void func_00162FD0(struct S *p);
void SetJobSeq__FP3JOBi(struct S *p, int n);
// name: SafeHouse port (UpdateJob)
void UpdateJob__FP2LO(struct S *p)
{
    func_001A5E28(p);
    switch (p->fc4) {
    case 1:
        if (!func_002121E8(p->fb8, p->fb0)) {
            JobCompleteClose__FP3JOB(p);
            if (p->fc0 || p->fcc)
                SetJobSeq__FP3JOBi(p, 3);
            else
                SetJobSeq__FP3JOBi(p, 2);
        }
        break;
    case 2:
        if (!func_002121E8(p->fb8, p->fb4)) {
            func_00162FD0(p);
            SetJobSeq__FP3JOBi(p, 0);
        }
        break;
    case 3:
        if (!func_002121E8(p->fbc, 0x30F))
            func_00162FD0(p);
        break;
    }
}
