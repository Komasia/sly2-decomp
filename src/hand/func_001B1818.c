typedef int qword __attribute__((mode(TI)));
typedef struct { qword a[3]; } MATRIX3;
struct S { char pad[0x1D8]; float g; int pad2; MATRIX3 mat; };
extern qword D_002A2DC0;
MATRIX3 func_0011B500(qword v, float g);
void func_001B1818(struct S *p, float g)
{
    p->g = g;
    p->mat = func_0011B500(D_002A2DC0, g);
}
