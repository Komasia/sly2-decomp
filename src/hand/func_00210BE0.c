typedef struct { char *pch; char *pchOut; } ENT;
typedef struct { int c; ENT *a; int x8; int xC; } TBL;
typedef struct { int a[4]; } ALLOC;
extern struct G { char pad[0x4640]; int f; } D_003DD490;
extern ALLOC *__11CLinearHeapiPUc(ALLOC *, int, int);
extern char *func_0013E368(struct G *, char *);
extern int func_0021ED28(char *);
extern char *PchzAllocCopy__FP4HEAPPci(ALLOC *, char *, int);

void func_00210BE0(TBL *p)
{
    ALLOC al;
    int i;
    if (D_003DD490.f == 0)
        return;
    __11CLinearHeapiPUc(&al, p->x8, p->xC);
    for (i = 0; i < p->c; i++) {
        ENT *e = &p->a[i];
        e->pchOut = func_0013E368(&D_003DD490, e->pch);
        if (func_0021ED28(e->pchOut))
            e->pchOut = PchzAllocCopy__FP4HEAPPci(&al, e->pchOut, 4);
        else
            e->pchOut = 0;
    }
}
