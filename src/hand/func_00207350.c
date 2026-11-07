typedef int qword __attribute__((mode(TI)));
struct O { char pad[0xC0]; void *pc; };
struct S {
    char pad0[0x28]; unsigned long fl28;
    char pad1[0x208 - 0x30]; int n208; char pad1b[0x218 - 0x20C]; qword *pq218;
    char pad2[0x26C - 0x21C]; char x26C[0x34C - 0x26C]; int h34C;
    char pad3[0x48C - 0x350]; int n48C; char pad4[0x498 - 0x490]; void *p498; void *p49C;
    char pad5[0x4A4 - 0x4A0]; int n4A4; char pad6[0x4B0 - 0x4A8]; qword q4B0;
    char pad7[0xF00 - 0x4C0]; struct O *po; char pad8[0xF0C - 0xF04]; int hF0C;
    char pad9[0xFBC - 0xF10]; int kFBC; char padA[0xFD0 - 0xFC0]; char xFD0[0x10];
};
extern qword D_002A2DD0;
void UpdateStep__FP4STEPf(struct S *p);
void UpdateGuardTimedMode__FP5GUARD(struct S *p);
void RefreshGuardTargets__FP5GUARD(struct S *p);
int FKindeDone__FP5KINDE(void *pc);
void SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(struct S *p, struct O *po, int n, qword v);
void UpdateGuardActionAim__FP5GUARD(struct S *p);
void NextPocketPrize__FP2LO(struct S *p);
void UpdateWatchA__FP6WATCHA(void *p);
void UpdateWatchB__FP6WATCHB(void *p);
void UpdateJobs__FP5ACTOR(void *p);
void func_002097E0(void *p);
int func_00131968(int h);
void func_001306A8(int *ph);

void UpdateStepguard__FP9STEPGUARDf(struct S *p)
{
    UpdateStep__FP4STEPf(p);
    if (!((p->fl28 >> 60) & 1))
        return;
    if (p->kFBC == 0xE)
        return;
    UpdateGuardTimedMode__FP5GUARD(p);
    RefreshGuardTargets__FP5GUARD(p);
    if (p->po && FKindeDone__FP5KINDE(p->po->pc))
        SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(p, 0, 0, D_002A2DD0);
    if (p->hF0C)
        UpdateGuardActionAim__FP5GUARD(p);
    if (p->n48C)
        NextPocketPrize__FP2LO(p);
    UpdateWatchA__FP6WATCHA(p->p498);
    UpdateWatchB__FP6WATCHB(p->p49C);
    UpdateJobs__FP5ACTOR(p->x26C);
    func_002097E0(p->xFD0);
    if (p->h34C && func_00131968(p->h34C))
        func_001306A8(&p->h34C);
    if (p->n4A4 && p->n208)
        p->q4B0 = *p->pq218;
}
