/* SetStepPhysHeading (0x204660): sets the STEP's heading and its rotation about z. */
typedef int qword __attribute__((mode(TI)));
typedef struct MATRIX3 { qword a[3]; } MATRIX3;
extern qword g_normalZ;
MATRIX3 BuildRotateMatrixAxis__FP7MATRIX3fG9VU_VECTOR(qword vecAxis, float rad);
/* the STEP fields used here */
struct STEP { char pad[0x1A8]; float radHeading; int pad2; MATRIX3 matHeading; };
// name: SafeHouse port (SetStepPhysHeading)
void SetStepPhysHeading__FP3ALOf(struct STEP *pstep, float rad) { pstep->radHeading = rad; pstep->matHeading = BuildRotateMatrixAxis__FP7MATRIX3fG9VU_VECTOR(g_normalZ, rad); }
