struct VTE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VTE *vt; };
struct P { struct O *po; char pad[0x9C - 4]; int n9C; int pad2; int nA4; };
void *PsndNewPlain__Fi(int n);
void SetSource__4CSndPv(void *p, void *q);
void RunTriggerList__FP2LOi(struct P *p, int n);
void SetTriggerState__FP2LOi(struct P *p, int n);
// name: SafeHouse port (EnterPad)
void EnterPad__FP2LO(struct P *p)
{
    struct O *o = p->po;
    struct VTE *e = &o->vt[3];
    ((void (*)(void *, int, int, int, int, int))e->pfn)((char *)o + e->d, 5, 0, 0, 0, 0);
    if (!p->n9C) {
        struct O *o2 = p->po;
        SetSource__4CSndPv(PsndNewPlain__Fi(2), o2);
    }
    RunTriggerList__FP2LOi(p, 0);
    if (!p->nA4) SetTriggerState__FP2LOi(p, 2);
    {
        struct O *o3 = p->po;
        struct VTE *e3 = &o3->vt[4];
        ((void (*)(void *, int, void *))e3->pfn)((char *)o3 + e3->d, 6, p);
    }
}
