typedef int qword __attribute__((mode(TI)));
qword PosOfLo__FP2LO(void *);
int PregionAt__FG9VU_VECTORi(qword, int);
void SetAloRegion__FP3ALOP9NAVREGION(void *, int);
// name: SafeHouse port (UpdateAloRegion)
void UpdateAloRegion__FP3ALO(void *p) { SetAloRegion__FP3ALOP9NAVREGION(p, PregionAt__FG9VU_VECTORi(PosOfLo__FP2LO(p), 1)); }
