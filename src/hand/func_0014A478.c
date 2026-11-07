typedef int qword __attribute__((mode(TI)));
qword PosOfLo__FP2LO(void *p);
int FDropOnGround__FP6VECTORffiPv(qword *pq, int a, int b, float f, float g);
// name: SafeHouse port (JOBCHASE::FAirborne)
int FAirborne__8JOBCHASE(char *p)
{
    char *q = *(char **)(p + 0x10);
    qword t;
    if (*(int *)(q + 0x208)) return 0;
    t = PosOfLo__FP2LO(q);
    return FDropOnGround__FP6VECTORffiPv(&t, 1, 0, 100.0f, -250.0f) == 0;
}
