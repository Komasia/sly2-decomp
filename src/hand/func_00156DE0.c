#include "vtbl.h"
struct O { int a[3]; VTENT *vt; };
struct S { char pad[0xE0]; int c; struct O *ao[1]; };
int func_00156870(struct O *o);
void *s1_memmove(void *dst, void *src, int cb) asm("memmove");
void func_00156DE0(struct S *p, int f)
{
    int i;
    for (i = 0; i < p->c;) {
        struct O **ppo = &p->ao[i];
        struct O *o = *ppo;
        if (f || func_00156870(o)) {
            VTENT *e = &o->vt[2];
            ((void (*)())e->pfn)(VT_THIS(o, e));
            s1_memmove(ppo, ppo + 1, (p->c - i) * sizeof(struct O *) - sizeof(struct O *));
            p->c--;
        } else {
            i++;
        }
    }
}
