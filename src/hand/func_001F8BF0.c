typedef int qword __attribute__((mode(TI)));
struct U { int a, b; int n; float x, y, z, r; int pad; qword q; };
struct V { char pad[0x60]; struct U *pu; };
struct T { char pad[0x98]; short k; char pad2[0xE]; struct V *pv; };
struct S { char pad[0x24]; struct T *pt; };
void func_001F8BF0(struct S *p, int n, qword q, float x, float y, float z, float deg)
{ struct T *pt = p->pt; if (pt->k == 16) { struct U *pu = pt->pv->pu; pu->n = n; pu->x = x; pu->y = y; pu->z = z; pu->r = deg * 0.01745329424738884f; pu->q = q; } }
