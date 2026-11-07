struct VTE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VTE *vt; };
void RunTriggerList__FP2LOi(void *p, int n);
// name: SafeHouse port (LeavePad)
void LeavePad__FP2LO(struct O **p)
{
    struct O *o = *p;
    struct VTE *e = &o->vt[3];
    ((void (*)(void *, int, int, int, int, int))e->pfn)((char *)o + e->d, 6, 0, 0, 0, 0);
    RunTriggerList__FP2LOi(p, 1);
    {
        struct O *o2 = *p;
        struct VTE *e2 = &o2->vt[4];
        ((void (*)(void *, int, void *))e2->pfn)((char *)o2 + e2->d, 7, p);
    }
}
