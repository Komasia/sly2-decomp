typedef int qword __attribute__((mode(TI)));
typedef struct MATRIX3 { qword a[3]; } MATRIX3;
extern qword g_normalZ;
MATRIX3 BuildRotateMatrixAxis__FP7MATRIX3fG9VU_VECTOR(qword v, float g);
struct S { char pad[0x1A8]; float g; int pad2; MATRIX3 m; };
// name: SafeHouse port (SetStepPhysHeading)
void SetStepPhysHeading__FP3ALOf(struct S *p, float g) { p->g = g; p->m = BuildRotateMatrixAxis__FP7MATRIX3fG9VU_VECTOR(g_normalZ, g); }
