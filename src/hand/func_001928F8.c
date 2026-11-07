typedef struct { short d; short pad; void (*pfn)(void *, int); } VT;
struct O { char pad[0xC]; VT *vt; char pad2[0x1854-0x10]; int x1854; };
struct P {
    struct O *x0; float x4; int x8; int pad0c[2]; int x14; int x18; char pad[0x440-0x1C]; char x440[0x4C4-0x440];
    int x4c4; char pad2[0x500-0x4C8]; int x500;
};
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
void SetInteractState__FP5ACTORi(struct P *p, int n);
void SetSlyMode__FP3SLYi(struct O *o, int n);
void UpdateSlyReach__FP3SLY(struct O *o);
void func_001CCAC0(void *p, int n);
void func_00192A28(struct P *p);
// name: SafeHouse port (StartInteract)
void StartInteract__FP5ACTORii3JTL(struct P *p, int n, int a, int b)
{
    SetInteractState__FP5ACTORi(p, -1);
    p->x8 = n;
    p->x4 = g_clock.t;
    p->x18 = b;
    p->x14 = a;
    p->x0->vt[88].pfn((char *)p->x0 + p->x0->vt[88].d, 2);
    switch (n) {
    case 0: case 13:
        n = 5;
        break;
    case 6:
    {
        struct O *o = p->x0;
        n = 0;
        o->x1854 = a;
        SetSlyMode__FP3SLYi(o, 0);
        UpdateSlyReach__FP3SLY(o);
        break;
    }
    case 5: case 9:
        p->x4c4 = p->x14;
        func_001CCAC0(p->x440, 0);
        n = 0;
        break;
    case 8:
        n = 7;
        func_00192A28(p);
        break;
    case 1:
        n = 0;
        func_00192A28(p);
        break;
    case 11: case 12:
        n = 0;
        p->x500 = 1;
        break;
    default:
        n = 0;
        break;
    }
    SetInteractState__FP5ACTORi(p, n);
}
