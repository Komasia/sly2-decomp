typedef struct { float a[8]; } __attribute__((aligned(16))) T;
typedef struct { float a[16]; } __attribute__((aligned(16))) O;
struct S { char pad[0x7C]; float f7C; float f80; float f84; float f88; };
void func_002162D8(struct S *p, O *po, T *pt);
void func_00216750(struct S *p, O *po, void *q);
void func_002166B0(struct S *p, T *pt, void *q)
{
    T t = *pt;
    O o;
    p->f80 = t.a[3];
    p->f7C = t.a[0];
    t.a[0] *= p->f88;
    t.a[5] += p->f84 * t.a[3];
    t.a[3] *= p->f88;
    func_002162D8(p, &o, &t);
    func_00216750(p, &o, q);
}
