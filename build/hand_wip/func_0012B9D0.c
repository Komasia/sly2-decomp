/* 25 diff: a[i-1] fields CSE'd as (base-0x30) reg; target uses negative offsets from &a[i]; pk[-1] form gives -0x8000 legitimize */
typedef int qword __attribute__((mode(TI)));
typedef struct VECTOR3 { float x, y, z; } VECTOR3;
typedef union V3Q { VECTOR3 v; qword q; } V3Q;
typedef struct KEY { VECTOR3 pos; float t; qword dposIn; qword dposOut; } KEY;
typedef struct T { int pad; int c; KEY *a; } T;
int func_0012B6D8(T *t, float g);
void func_00117120(qword a, qword da, qword b, qword db, void *pv, void *pdv, void *p3, float dt, float t, float dtScale);
void func_0012B9D0(T *t, void *pv, void *pdv, float g, float dtScale)
{
    int i = func_0012B6D8(t, g);
    V3Q u0, u1;
    u0.v = t->a[i - 1].pos;
    u1.v = t->a[i].pos;
    func_00117120(u0.q, t->a[i - 1].dposOut, u1.q, t->a[i].dposIn, pv, pdv, 0, t->a[i].t - t->a[i - 1].t, g - t->a[i - 1].t, dtScale);
}
