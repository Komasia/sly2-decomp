typedef int qword __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } V4 __attribute__((aligned(16)));
typedef struct { char pad[0x148]; unsigned long f148; } A;
typedef struct { float x, y, z, w; int a, b; } E;
typedef struct { A *pa; int pad[3]; V4 v10; float g20; int pad2[8]; E *ae; } S;
extern V4 D_002A2DD0;
void func_001D6310(A *pa);
float func_002599D8(V4 *pv);
float func_002599E0(V4 *pv);
float func_002599E8(V4 *pv);

void func_0016EF00(S *p, int i)
{
    float g = 1000000.0f;
    E *pe;
    V4 v;
    float x, y, z;
    func_001D6310(p->pa);
    p->pa->f148 &= 0xFFFFFFF7FFFFFFFFUL;
    p->v10 = D_002A2DD0;
    p->g20 = g;
    pe = &p->ae[i];
    v = D_002A2DD0;
    x = func_002599D8(&v);
    y = func_002599E0(&v);
    z = func_002599E8(&v);
    pe->x = x;
    pe->y = y;
    pe->z = z;
    pe->w = g;
}
