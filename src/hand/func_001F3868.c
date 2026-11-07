typedef int qword __attribute__((mode(TI)));
qword func_001A62E8(void *);
int PregionAt__FG9VU_VECTORi(qword, int);
void SetAloRegion__FP3ALOP9NAVREGION(void *, int);
// name: SafeHouse port (UpdateAloRegion)
void UpdateAloRegion__FP3ALO(void *p) { SetAloRegion__FP3ALOP9NAVREGION(p, PregionAt__FG9VU_VECTORi(func_001A62E8(p), 1)); }
