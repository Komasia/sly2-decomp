typedef int qword __attribute__((mode(TI)));
extern struct { float t; float dt; } g_clock;
extern float D_002C3DB8;   /* the time between alarms */
extern struct { char pad[0x4030]; int pnoisetmplAlarmDefault; } g_sw;
/* a noise: the alarm's target place, the target, its kind */
struct NOISE { char pad[0x30]; qword posTarget; char pad2[4]; void *ploTarget44; char pad3[0xC]; int nKind; };
struct GUARD { char pad[0xE60]; int pnoisetmplAlarm; char pad2[0xF44 - 0xE64]; float tF44; };
qword PosOfLo__FP2LO(void *plo);
void PnoiseNew__FP9NOISETMPLG9VU_VECTORiP6VECTOR(int pnoisetmpl, qword pos, struct GUARD *ploOwner, struct NOISE **ppnoise);
struct NOISE *func_00156698(int pnoisetmpl, qword pos, struct GUARD *ploOwner);
/* RaiseGuardAlarm (0x20B140): a pursuing guard raises an alarm about its target: a kind-4 noise at the guard (from
 * its alarm template +0xE60, else the world's), with the target and its place; the next alarm not before
 * D_002C3DB8 from now (+0xF44). */
// name: SafeHouse port (RaiseGuardAlarm)
void RaiseGuardAlarm__FP5GUARDP2LO(struct GUARD *pguard, void *ploTarget)
{
    struct NOISE *pnoise;
    qword posTarget = PosOfLo__FP2LO(ploTarget);
    pnoise = 0;
    if (pguard->pnoisetmplAlarm)
        PnoiseNew__FP9NOISETMPLG9VU_VECTORiP6VECTOR(pguard->pnoisetmplAlarm, PosOfLo__FP2LO(pguard), pguard, &pnoise);
    else
        pnoise = func_00156698(g_sw.pnoisetmplAlarmDefault, PosOfLo__FP2LO(pguard), pguard);
    pnoise->posTarget = posTarget;
    pnoise->ploTarget44 = ploTarget;
    pnoise->nKind = 4;
    pguard->tF44 = g_clock.t + D_002C3DB8;
}
