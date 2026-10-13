typedef struct { float a[8]; } __attribute__((aligned(16))) T;
typedef struct { float a[16]; } __attribute__((aligned(16))) O;
struct S { char pad[0x7C]; float f7C; float f80; float f84; float f88; };
void func_002162D8(struct S *p, O *po, T *pt);
void func_00216750(struct S *p, O *po, void *q);
void func_002166B0(struct S *p, T *pt, void *q)
{
    T t = *pt;
    O o;
    float x=t.a[0],y=t.a[3],g=p->f88,shift=p->f84;
    p->f80=y; p->f7C=x;
    t.a[0] = x*g;
    t.a[3] = y*g;
    t.a[5] += shift*y;
    func_002162D8(p, &o, &t);
    func_00216750(p, &o, q);
}
