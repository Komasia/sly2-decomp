struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a[3]; struct VTE *vt; };
struct S { char pad[0xE0]; int c; struct O *ao[1]; };
int func_00156870(struct O *o);
void *func_002332B8(void *dst, void *src, int cb);
void func_00156DE0(struct S *p, int f)
{
    int i;
    for (i = 0; i < p->c;) {
        struct O **ppo = &p->ao[i];
        struct O *o = *ppo;
        if (f || func_00156870(o)) {
            struct VTE *e = &o->vt[2];
            e->pfn((char *)o + e->d);
            func_002332B8(ppo, ppo + 1, (p->c - i) * sizeof(struct O *) - sizeof(struct O *));
            p->c--;
        } else {
            i++;
        }
    }
}
