/* 25 diff: 12-byte VECTOR3 by value must be passed as a qword (union) to get the ldl/ldr copy + lq;
   remaining: k0 fields addressed via separate reg instead of negative offsets from k1, scheduling */
typedef int qword __attribute__((mode(TI)));
typedef struct VECTOR3 { float x, y, z; } VECTOR3;
typedef union V3Q { VECTOR3 v; qword q; } V3Q;
typedef struct KEY { VECTOR3 pos; float t; qword dpos; } KEY;
typedef struct T { int pad; int c; KEY *a; } T;
int func_0012BB70(T *t, float g);
void func_00117120(qword a, qword da, qword b, qword db, void *pv, void *pdv, void *p3, float dt, float t, float dtScale);
void func_0012BE68(T *t, void *pv, void *pdv, float g, float dtScale)
{
    int i = func_0012BB70(t, g);
    V3Q u0, u1;
    u0.v = t->a[i - 1].pos;
    u1.v = t->a[i].pos;
    func_00117120(u0.q, t->a[i - 1].dpos, u1.q, t->a[i].dpos, pv, pdv, 0, t->a[i].t - t->a[i - 1].t, g - t->a[i - 1].t, dtScale);
}
