struct VTE { short d; short pad; void (*pfn)(); };
struct P { char pad[0xC]; struct VTE *vt; char pad2[0xDFC - 0x10]; int nDFC; int *pnE00; char pad3[0x12FC - 0xE04]; int *pn12FC; int n1300; int pad4; int n1308; };
extern char D_002A4E18[];
extern char D_002A4E20[];
int *PnProgressSlot__FPvi(void *p, char *name, int n);
void func_00144188(struct P *p, int n);
void func_001441C0(struct P *p, int n);
// name: SafeHouse port (StartPlayerCounters)
void StartPlayerCounters__FP5ACTORi(struct P *p, int f)
{
    struct VTE *e = &p->vt[103];
    p->pnE00 = PnProgressSlot__FPvi(((void *(*)(void *))e->pfn)((char *)p + e->d), D_002A4E18, 0);
    {
        struct VTE *e2 = &p->vt[103];
        p->pn12FC = PnProgressSlot__FPvi(((void *(*)(void *))e2->pfn)((char *)p + e2->d), D_002A4E20, 0);
    }
    if (*p->pnE00 == 0 || f) {
        func_00144188(p, p->nDFC);
        func_001441C0(p, p->n1300);
        p->n1308 = 0;
    }
}
