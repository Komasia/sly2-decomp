// Copy a position to each linked mesh record.
typedef int qword __attribute__((mode(TI)));
struct V { float x, y, z; char pad[0xC]; };
struct T { char pad[0x14]; };
struct N { struct T *pt; char pad[8]; struct N *next; };
struct S { char pad[0xBC]; struct T *aBC; char padc0[4]; struct V *aC4; char padc8[0x14]; struct N *xDC; };
float func_00259D98(qword *pq);
float func_00259DA8(qword *pq);
float func_00259DC0(qword *pq);
void func_0021C5F8(struct S *p, qword q)
{
    struct N *n;
    for (n = p->xDC; n; n = n->next) {
        struct V *pv = (struct V*)((n->pt - p->aBC)*sizeof(struct V)+(int)p->aC4);
        qword t = q;
        float x = func_00259D98(&t);
        float y = func_00259DA8(&t);
        float z = func_00259DC0(&t);
        pv->x = x;
        pv->y = y;
        pv->z = z;
    }
}
