struct VTE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VTE *vt; char pad2[0x1310 - 0x10]; char sub[4]; int n1314; };
void SetCmFocusObject__FP2LOi(void *p, int a);
void RetractAsegaPp__FPP5ASEGA(void *p);
void func_00144480(struct O *p, int a)
{
    struct VTE *e;
    SetCmFocusObject__FP2LOi(p, a);
    e = &p->vt[105];
    ((void (*)(void *))e->pfn)((char *)p + e->d);
    if (!a) {
        RetractAsegaPp__FPP5ASEGA(p->sub);
        p->n1314 = -1;
    }
}
