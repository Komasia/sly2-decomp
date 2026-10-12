typedef int qword __attribute__((mode(TI)));
struct SEG { float a, b; };
struct O { char pad[0xE4]; int fE4; };
struct PV { char pad[0x114]; int n114; };
struct S { struct O *po; int c4; struct SEG *aseg; int cC; struct SEG aseg10[16]; int c90; struct PV **apv; int n98; };
struct X { char pad[0x40]; float a; float b; char pad2[0x18]; };
struct G { char pad[0x3D70]; int n3D70; };
extern struct G D_003DD490;
extern float D_002C367C;
float func_001E6620(struct O *);
float func_001E6648(struct O *);
void func_001E6F10(struct O *, float, qword *, int);
void *func_001E9F50(qword);
int func_001BD560(void *, struct O *, int, int, float, float *);
void *func_002333B4(void *, int, int);
int func_0014C9F8(int, struct X *, int, struct X *, int, struct X *, int);
void func_001EA000(struct S *ps)
{
    struct VEC { float x, y, z, w; } __attribute__((aligned(16))) pos;
    struct X ax[16];
    struct X ay[16];
    struct SEG seg;
    struct SEG *aseg;
    struct SEG *asegSrc;
    int cseg, c, i, n;
    float tStart, t, tEnd;
    {
        int k;
        for (k = 0; k < ps->c90; k++)
            if (ps->n98 < ps->apv[k]->n114)
                break;
        if (k >= ps->c90)
            return;
    }
    aseg = ps->aseg10;
    cseg = 0;
    tStart = func_001E6620(ps->po);
    t = tStart;
    tEnd = func_001E6648(ps->po);
    asegSrc = ps->aseg;
    c = ps->c4;
    while (t < tEnd) {
        void *pv;
        func_001E6F10(ps->po, t, (qword *)&pos, 0);
        pv = func_001E9F50(*(qword *)&pos);
        if (pv) {
            int fSave = ps->po->fE4;
            struct SEG *pseg;
            int fNew;
            int idx;
            ps->po->fE4 = 0;
            if (func_001BD560(pv, ps->po, 0, 0, t, &seg.a) == 3)
                seg.a = tStart;
            if (func_001BD560(pv, ps->po, 1, 0, t, &seg.b) == 3)
                seg.b = tEnd;
            ps->po->fE4 = fSave;
            pseg = &aseg[cseg];
            fNew = 1;
            while (aseg < pseg) {
                if (pseg[-1].b < seg.a)
                    break;
                pseg--;
                if (pseg->a < seg.a) {
                    fNew = 0;
                    break;
                }
            }
            idx = pseg - aseg;
            cseg = idx + 1;
            if (!((unsigned)cseg < 17))
                cseg = idx;
            if (fNew) {
                pseg->a = seg.a;
                pseg->b = seg.b;
            }
            t = seg.b;
        }
        t += D_002C367C;
    }
    for (i = 0; i < c; i++) {
        func_002333B4(&ax[i], 0, 0x60);
        ax[i].a = asegSrc[i].a;
        ax[i].b = asegSrc[i].b;
    }
    for (i = 0; i < cseg; i++) {
        func_002333B4(&ay[i], 0, 0x60);
        ay[i].a = aseg[i].a;
        ay[i].b = aseg[i].b;
    }
    n = func_0014C9F8(cseg, ay, c, ax, 0x10, ay, 0);
    for (i = 0; i < n; i++) {
        aseg[i].a = ay[i].a;
        aseg[i].b = ay[i].b;
    }
    if (n >= 2 && ps->po->fE4 && ps->aseg10[0].a == tStart && ps->aseg10[n - 1].b == tEnd) {
        ps->aseg10[0].a = ps->aseg10[n - 1].a - tEnd;
        ps->aseg10[n - 1].b = ps->aseg10[0].b + tEnd;
    }
    ps->cC = n;
    ps->n98 = ++D_003DD490.n3D70;
}
