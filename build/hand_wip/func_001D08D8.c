typedef int qword __attribute__((mode(TI)));
typedef struct { float x, y, z; } __attribute__((aligned(16))) VECTOR;
typedef struct { float mat[3][4]; } __attribute__((aligned(16))) MATRIX3;
typedef struct {
    char pad0[0x40];
    MATRIX3 x40;
} OBJ;
void func_001CE9B8(OBJ *);
float func_0011D448(float, float);
MATRIX3 func_0011B7E0(qword);
/* only diff: -1.0f / 1.0f constants get f21/f20 instead of f20/f21 */
void func_001D08D8(OBJ *p)
{
    VECTOR v;
    float x, y, z;
    func_001CE9B8(p);
    x = func_0011D448(-1.0f, 1.0f);
    y = func_0011D448(-1.0f, 1.0f);
    z = func_0011D448(0.1f, 0.9f);
    v.x = x;
    v.y = y;
    v.z = z + 0.1f;
    p->x40 = func_0011B7E0(*(qword *)&v);
}
