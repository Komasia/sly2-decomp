/* 22 diff: real func_00117120 prototype (qwords, floats, ptrs). Left: a[i-1] fields CSEd as base-0x30 reg; u1 copy uses a3 not v1 */
typedef int qword __attribute__((mode(TI)));
typedef struct VECTOR3 { float x, y, z; } VECTOR3;
typedef union V3Q { VECTOR3 v; qword q; } V3Q;
typedef struct KEY { VECTOR3 pos; float t; qword dposIn; qword dposOut; } KEY;
typedef struct T { int pad; int c; KEY *a; } T;
int func_0012B6D8(T *t, float g);
void func_00117120(qword a, qword da, qword b, qword db, float dt, float t, float dtScale, void *pv, void *pdv, int n);
void func_0012B9D0(T *t, void *pv, void *pdv, float g, float dtScale)
{
    int i = func_0012B6D8(t, g);
    V3Q u0, u1;
    u0.v = t->a[i - 1].pos;
    u1.v = t->a[i].pos;
    func_00117120(u0.q, t->a[i - 1].dposOut, u1.q, t->a[i].dposIn, t->a[i].t - t->a[i - 1].t, g - t->a[i - 1].t, dtScale, pv, pdv, 0);
}
