struct E { int a; int b; void *o; int k; float ag[3]; };
struct S { char pad[0x288]; float g288; char pad2[0x2A8 - 0x28C]; int c; struct E ae[8]; };
int func_001F0638(void *o);
void ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(int a, int b, int c, int d, void **ppo);
int func_00152680(int j);
void SetSmaGoal__FP3SMA3OID(void *o, int n);
// name: SafeHouse port (UpdateDanceCrowd)
void UpdateDanceCrowd__FP5DANCE(struct S *p)
{
    int i, j;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        if (!pe->o)
            continue;
        if (func_001F0638(pe->o)) {
            ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(0, 0, -1, 0, &pe->o);
            pe->k = -1;
        } else {
            for (j = 0; j < 3; j++) {
                if (pe->ag[j] <= p->g288) {
                    SetSmaGoal__FP3SMA3OID(pe->o, func_00152680(j));
                    pe->k = j;
                    break;
                }
            }
        }
    }
}
