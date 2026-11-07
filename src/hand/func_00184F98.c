typedef int qword __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } VEC;
extern float D_002BE910;
qword PosOfLo__FP2LO(void *a, void *b);
void func_00184F98(void *a, void *b, VEC *p)
{
    *(qword *)p = PosOfLo__FP2LO(a, b);
    p->z += D_002BE910;
}
