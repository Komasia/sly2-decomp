typedef struct DL { void *pvFirst; void *pvLast; int ibDle; } DL;
typedef struct OBJ OBJ;
typedef struct VT { struct { short d; short pad; void (*pfn)(void *, int, int, int, int, int); } a[8]; } VT;
struct OBJ {
    char pad[0xC];
    VT *vt;
    char pad10[0x40 - 0x10];
    int x40;
    char pad44[0x54 - 0x44];
    void *x54;
    int pad58;
    DL dl;
    char pad68[0x6C - 0x68];
    int x6C;
    int x70;
    int x74;
    int x78;
    int x7C;
};
void func_001E02C0(OBJ *);
void *PrunNew__FP2LOPvP3RUN(OBJ *, void *, int);
void RunRun__FP4PRUN(void *);
int FIsDlEmpty__FP2DL(DL *);
void StopScptImpl__FP2LO(OBJ *);
void func_001A6CA8(OBJ *, int);
// name: SafeHouse port (StartScptImpl)
void StartScptImpl__FP2LOi(OBJ *p, int n)
{
    int fl;
    if (p->x74)
        return;
    p->x6C = n;
    p->x74 = 1;
    p->x78 = 0;
    p->vt->a[3].pfn((char *)p + p->vt->a[3].d, 5, 0, 0, 0, 0);
    if (!p->x74)
        return;
    if (p->x7C) {
        func_001E02C0(p);
        p->x7C = 0;
    }
    RunRun__FP4PRUN(PrunNew__FP2LOPvP3RUN(p, p->x54, 0));
    if (!p->x74)
        return;
    if (FIsDlEmpty__FP2DL(&p->dl)) {
        StopScptImpl__FP2LO(p);
        return;
    }
    fl = p->x40;
    if ((fl ^ 1) & 1)
        fl = *(int *)fl;
    if (fl & 2)
        return;
    func_001A6CA8(p, 1);
    if ((p->x40 ^ 1) & 1)
        *(int *)p->x40 |= 2;
    else
        p->x40 |= 2;
    p->x78 = 1;
}
