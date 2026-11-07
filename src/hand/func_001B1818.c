typedef int qword __attribute__((mode(TI)));
typedef struct { qword a[3]; } MATRIX3;
struct S { char pad[0x1D8]; float g; int pad2; MATRIX3 mat; };
extern qword g_normalZ;
MATRIX3 BuildRotateMatrixAxis__FP7MATRIX3fG9VU_VECTOR(qword v, float g);
// name: SafeHouse port (SetBirdHeading)
void SetBirdHeading__FP4BIRDf(struct S *p, float g)
{
    p->g = g;
    p->mat = BuildRotateMatrixAxis__FP7MATRIX3fG9VU_VECTOR(g_normalZ, g);
}
