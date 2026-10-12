typedef int qword __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } VEC;
extern float D_002BE910;
qword func_001A62E8(void *a, void *b);
void func_00184F98(void *a, void *b, VEC *p)
{
    *(qword *)p = func_001A62E8(a, b);
    p->z += D_002BE910;
}
