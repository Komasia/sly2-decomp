typedef struct { char *pch; char *pchOut; } ENT;
typedef struct { int c; ENT *a; int x8; int xC; } TBL;
typedef struct { int a[4]; } ALLOC;
extern struct G { char pad[0x4640]; int f; } g_sw;
extern ALLOC *__11CLinearHeapiPUc(ALLOC *, int, int);
extern char *func_0013E368(struct G *, char *);
extern int s1_strlen(char *) asm("strlen");
extern char *PchzAllocCopy__FP4HEAPPci(ALLOC *, char *, int);

void func_00210BE0(TBL *p)
{
    ALLOC al;
    int i;
    if (g_sw.f == 0)
        return;
    __11CLinearHeapiPUc(&al, p->x8, p->xC);
    for (i = 0; i < p->c; i++) {
        ENT *e = &p->a[i];
        e->pchOut = func_0013E368(&g_sw, e->pch);
        if (s1_strlen(e->pchOut))
            e->pchOut = PchzAllocCopy__FP4HEAPPci(&al, e->pchOut, 4);
        else
            e->pchOut = 0;
    }
}
