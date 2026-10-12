/* 2 diffs: the two local stores (sw sp,4 / sw zero,0) are swapped around the vtable load */
typedef struct { short d; short pad; void *pfn; } VTE;
struct S { char pad[0xC]; VTE *vt; };
#define VT(p, n, T) ((T)(p)->vt[n].pfn)
void func_00206820(struct S *p)
{
    int a;
    int *pa;
    a = 0;
    pa = &a;
    VT(p, 27, void (*)(void *, int))((char *)p + p->vt[27].d, 0);
    VT(p, 3, void (*)(void *, int, int, int, int **, int))((char *)p + p->vt[3].d, 0xF, 0, 1, &pa, 0);
    VT(p, 26, void (*)(void *, int))((char *)p + p->vt[26].d, 0);
    VT(p, 3, void (*)(void *, int, int, int, int **, int))((char *)p + p->vt[3].d, 0xE, 0, 1, &pa, 0);
}
