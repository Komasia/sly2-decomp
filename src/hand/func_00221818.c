typedef int qword __attribute__((mode(TI)));
struct E { int id; int pad[3]; qword q[8]; };
extern struct E D_002C4120;
struct S { char pad[0x110]; int c; struct E *a; struct E *cur; int x11C; };
void func_00221940(struct S *p, int id);
void func_00221818(struct S *p, int id)
{
    int i;
    struct E *pe;
    func_00221940(p, id);
    if (p->c >= 4) return;
    for (i = 0; i < p->c; i++) {
        if (p->a[i].id == id) {
            p->cur = &p->a[i];
            return;
        }
    }
    if (p->x11C) {
        p->cur = p->a;
        return;
    }
    pe = &p->a[p->c++];
    p->cur = pe;
    if (p->c >= 2)
        *pe = p->a[p->c - 2];
    else
        *pe = D_002C4120;
    p->cur->id = id;
}
