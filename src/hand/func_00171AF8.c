/* func_00171AF8: a script job's aim at an object from its guard's position (GetCmdAim with the job's command list). */
typedef int qword __attribute__((mode(TI)));
struct JOBSCRIPT { char pad[0x10]; void *pguard; char pad2[0x1C]; void *pcmdlist; };
qword PosOfLo__FP2LO(void *plo);
void GetCmdAim__FP5GUARDG9VU_VECTORP2LOP6VECTORPf(void *pguard, qword pos, int plo, int ppos, int prad);
void func_00171AF8(struct JOBSCRIPT *pjob, int plo, int ppos, int prad) { GetCmdAim__FP5GUARDG9VU_VECTORP2LOP6VECTORPf(pjob->pcmdlist, PosOfLo__FP2LO(pjob->pguard), plo, ppos, prad); }
