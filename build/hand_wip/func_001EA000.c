typedef int qword __attribute__((mode(TI)));
struct VEC { float x, y, z, w; } __attribute__((aligned(16)));
struct SEG { float a, b; };
struct O { char pad[0xE4]; int fE4; };
struct PV { char pad[0x114]; int n114; };
struct S { struct O *po; int c4; struct SEG *aseg; int cC; struct SEG aseg10[16]; int c90; struct PV **apv; int n98; };
struct X { char pad[0x40]; float a; float b; char pad2[0x18]; } __attribute__((aligned(16)));
struct G { char pad[0x3D70]; int n3D70; };
extern struct G D_003DD490;
extern float D_002C367C;
float func_001E6620(struct O *);
float func_001E6648(struct O *);
void func_001E6F10(struct O *, float, qword *, qword *);
void *func_001E9F50(qword);
int func_001BD560(void *, struct O *, float, int, qword *, float *);
void *func_002333B4(void *, int, unsigned int);
int func_0014C9F8(int, struct X *, int, struct X *, int, struct X *, int);
void func_001EA000(struct S *ps)
{
    struct VEC pos;
    struct X ax[16];
    struct X ay[16];
    float segStart,segEnd;
    struct SEG *aseg;
    struct SEG *asegSrc;
    int cseg,c,i,j,k,n;
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
            if (func_001BD560(pv, ps->po, t, 0, 0, &segStart) == 3)
                segStart = tStart;
            if (func_001BD560(pv, ps->po, t, 1, 0, &segEnd) == 3)
                segEnd = tEnd;
            ps->po->fE4 = fSave;
            pseg = &aseg[cseg];
            fNew = 1;
            while (aseg < pseg) {
                struct SEG *previous=pseg-1;
                if (previous->b < segStart)
                    break;
                pseg=previous;
                if (pseg->a < segStart) {
                    fNew = 0;
                    break;
                }
            }
            idx = pseg - aseg;
            cseg = idx + 1;
            if (!((unsigned)cseg < 17))
                cseg = idx;
            if (fNew) {
                pseg->a = segStart;
                pseg->b = segEnd;
            }
            t = segEnd;
        }
        t += D_002C367C;
    }
    for (i = 0; i < c; i++) {
        func_002333B4(&ax[i], 0, 0x60);
        ax[i].a = asegSrc[i].a;
        ax[i].b = asegSrc[i].b;
    }
    for (j = 0; j < cseg; j++) {
        func_002333B4(&ay[j], 0, 0x60);
        ay[j].a = aseg[j].a;
        ay[j].b = aseg[j].b;
    }
    n = func_0014C9F8(cseg, ay, c, ax, 0x10, ay, 0);
    for (k = 0; k < n; k++) {
        aseg[k].a = ay[k].a;
        aseg[k].b = ay[k].b;
    }
    if (n >= 2 && ps->po->fE4 && ps->aseg10[0].a == tStart && ps->aseg10[n - 1].b == tEnd) {
        ps->aseg10[0].a = ps->aseg10[n - 1].a - tEnd;
        ps->aseg10[n - 1].b = ps->aseg10[0].b + tEnd;
    }
    ps->cC = n;
    ps->n98 = ++D_003DD490.n3D70;
}

#define OFF(T,f) ((unsigned)&((T*)0)->f)
typedef char layout0[(sizeof(void*)==4)?1:-1];
typedef char layout1[(sizeof(qword)==16)?1:-1];
typedef char layout2[(__alignof__(qword)==16)?1:-1];
typedef char layout3[(sizeof(struct VEC)==16)?1:-1];
typedef char layout4[(__alignof__(struct VEC)==16)?1:-1];
typedef char layout5[(sizeof(struct SEG)==8)?1:-1];
typedef char layout6[(OFF(struct SEG,a)==0)?1:-1];
typedef char layout7[(OFF(struct SEG,b)==4)?1:-1];
typedef char layout8[(sizeof(struct X)==0x60)?1:-1];
typedef char layout9[(__alignof__(struct X)==16)?1:-1];
typedef char layout10[(OFF(struct X,a)==0x40)?1:-1];
typedef char layout11[(OFF(struct X,b)==0x44)?1:-1];
typedef char layout12[(sizeof(struct S)==0x9C)?1:-1];
typedef char layout13[(OFF(struct S,po)==0)?1:-1];
typedef char layout14[(OFF(struct S,c4)==4)?1:-1];
typedef char layout15[(OFF(struct S,aseg)==8)?1:-1];
typedef char layout16[(OFF(struct S,cC)==0xC)?1:-1];
typedef char layout17[(OFF(struct S,aseg10)==0x10)?1:-1];
typedef char layout18[(OFF(struct S,c90)==0x90)?1:-1];
typedef char layout19[(OFF(struct S,apv)==0x94)?1:-1];
typedef char layout20[(OFF(struct S,n98)==0x98)?1:-1];
typedef char layout21[(OFF(struct O,fE4)==0xE4)?1:-1];
typedef char layout22[(OFF(struct PV,n114)==0x114)?1:-1];
typedef char layout23[(OFF(struct G,n3D70)==0x3D70)?1:-1];
